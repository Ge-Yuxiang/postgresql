/*-------------------------------------------------------------------------
 *
 * main.c
 *	  Stub main() routine for the postgres executable.
 *
 * This does some essential startup tasks for any incarnation of postgres
 * (postmaster, standalone backend, standalone bootstrap process, or a
 * separately exec'd child of a postmaster) and then dispatches to the
 * proper FooMain() routine for the incarnation.
 *
 *
 * Portions Copyright (c) 1996-2024, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 *
 * IDENTIFICATION
 *	  src/backend/main/main.c
 *
 *-------------------------------------------------------------------------
 */
#include "postgres.h"

#include <unistd.h>

#if defined(WIN32)
#include <crtdbg.h>
#endif

#if defined(__NetBSD__)
#include <sys/param.h>
#endif

#include "bootstrap/bootstrap.h"
#include "common/username.h"
#include "port/atomics.h"
#include "postmaster/postmaster.h"
#include "tcop/tcopprot.h"
#include "utils/help_config.h"
#include "utils/memutils.h"
#include "utils/pg_locale.h"
#include "utils/ps_status.h"


const char *progname;
static bool reached_main = false;


static void startup_hacks(const char *progname);
static void init_locale(const char *categoryname, int category, const char *locale);
static void help(const char *progname);
static void check_root(const char *progname);


/*
 * 任何 PostgreSQL 服务器进程都从这里开始执行。
 */
int
main(int argc, char *argv[])
{
	bool		do_check_root = true;

	reached_main = true;

	/*
	 * 如果当前平台支持，设置一个捕获器，如果backend或postmaster进程因致命信号或异常而崩溃时会被调用。
	 */
#if defined(WIN32)
	pgwin32_install_crashdump_handler(); // 捕获 postmaster 的异常
#endif

	progname = get_progname(argv[0]); // 提取程序实际调用名

	/*
	 * 根据平台启动相应的特殊操作
	 */
	startup_hacks(progname); // 根据平台启动相应的特殊操作

	/*
	 * 保存原始的 argc/argv 值, 以防止它被后续的 ps_display 操作破坏。在这种情况下，save_ps_display_args
	 * 会制作并返回 argv[] 数组的新副本。
	 *
	 * save_ps_display_args 还可能移动环境字符串以腾出额外的空间。因此，这应该在启动时
	 * 尽早完成，以避免与可能会保存 getenv() 结果指针的代码产生纠缠。
	 */
	argv = save_ps_display_args(argc, argv); // 保存原始的 argc/argv 值, 以防止它被后续的 ps_display 操作破坏

	/*
	 * 启动基本子系统：error and memory管理
	 *
	 * 从此点之后的代码允许使用 elog/ereport，尽管消息的本地化可能不会立即生效，
	 * 而且在加载 GUC 设置之前，消息只会输出到 stderr。
	 */
	MemoryContextInit();

	/*
	 * 设置区域信息
	 */
	set_pglocale_pgservice(argv[0], PG_TEXTDOMAIN("postgres"));

	/*
	 * 在主控进程中，吸收环境值 LC_COLLATE 和 LC_CTYPE。单个后端稍后会根据 pg_database 更改这些设置，
	 * 但主控进程不能这样做。如果我们让这些设置为 "C"，那么主控进程中的消息本地化可能不会很好。
	 * LC_COLLATE 和 LC_CTYPE 是 C 语言环境变量的一部分，用于定义程序的行为
	 * LC_COLLATE 控制字符串排序和比较的方式
	 * LC_CTYPE 定义了字符分类和转换规则
	 */
	init_locale("LC_COLLATE", LC_COLLATE, "");
	init_locale("LC_CTYPE", LC_CTYPE, "");

	/*
	 * LC_MESSAGES 将在 GUC 选项处理期间稍后设置，但我们在这里设置它以使启动错误消息能够本地化。
	 */
#ifdef LC_MESSAGES
	init_locale("LC_MESSAGES", LC_MESSAGES, "");
#endif

	/*
	 * 我们总是将这些设置为 "C"，除了在 pg_locale.c 中临时更改；请参阅该文件以获取解释。
	 */
	init_locale("LC_MONETARY", LC_MONETARY, "C");
	init_locale("LC_NUMERIC", LC_NUMERIC, "C");
	init_locale("LC_TIME", LC_TIME, "C");

	/*
	 * 现在我们已经尽可能地从区域环境吸收了信息，移除任何 LC_ALL 设置，以便由 pg_perm_setlocale 安装的环境变量有效。
	 */
	unsetenv("LC_ALL");

	/*
	 * 在做其他事情之前捕获标准选项，特别是我们在坚持不是以 root 用户身份运行之前。
	 */
	if (argc > 1)
	{
		if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-?") == 0)
		{
			help(progname); //显示 pg_ctl --help的内容
			exit(0);
		}
		if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-V") == 0)
		{
			fputs(PG_BACKEND_VERSIONSTR, stdout); //显示 pg_ctl --version的内容
			exit(0);
		}

		/*
		 * 除了上述选项之外，我们还允许以 root 用户身份调用 "--describe-config" 和 "-C var"。
		 * 这是相对安全的，因为这些都是只读活动。-C 的情况很重要，因为 pg_ctl 可能在仍然持有管理员权限的情况下尝试调用它。
		 * 注意，虽然 -C 通常可以在任何 argv 位置，如果你想绕过 root 检查，必须将其放在第一位。这减少了我们可能误将其他模式的 -C 开关解释为主控/PostgreSQL 的风险。
		 */
		if (strcmp(argv[1], "--describe-config") == 0)
			do_check_root = false;
		else if (argc > 2 && strcmp(argv[1], "-C") == 0)
			do_check_root = false;
	}

	/*
	 * 确保我们不是以 root 用户身份运行，除非对于所选选项来说是安全的。
	 */
	if (do_check_root)
		check_root(progname);

	/*
	 * 根据第一个参数调度到各种子程序之一。
	 */

	if (argc > 1 && strcmp(argv[1], "--check") == 0)
		BootstrapModeMain(argc, argv, true);
	else if (argc > 1 && strcmp(argv[1], "--boot") == 0)
		BootstrapModeMain(argc, argv, false);   // 启动引导程序
#ifdef EXEC_BACKEND
	else if (argc > 1 && strncmp(argv[1], "--forkchild", 11) == 0)
		SubPostmasterMain(argc, argv);
#endif
	else if (argc > 1 && strcmp(argv[1], "--describe-config") == 0)
		GucInfoMain(); //sky 打印postgresql.conf的配置参数
	else if (argc > 1 && strcmp(argv[1], "--single") == 0)
		PostgresSingleUserMain(argc, argv,
							   strdup(get_user_name_or_exit(progname))); //以单用户模式启动
	else
		PostmasterMain(argc, argv); // 启动守护进程
	/* 上述函数不应该返回 */
	abort();
}



/*
 * Place platform-specific startup hacks here.  This is the right
 * place to put code that must be executed early in the launch of any new
 * server process.  Note that this code will NOT be executed when a backend
 * or sub-bootstrap process is forked, unless we are in a fork/exec
 * environment (ie EXEC_BACKEND is defined).
 *
 * XXX The need for code here is proof that the platform in question
 * is too brain-dead to provide a standard C execution environment
 * without help.  Avoid adding more here, if you can.
 */
static void
startup_hacks(const char *progname)
{
	/*
	 * Windows-specific execution environment hacking.
	 */
#ifdef WIN32
	{
		WSADATA		wsaData;
		int			err;

		/* Make output streams unbuffered by default */
		setvbuf(stdout, NULL, _IONBF, 0);
		setvbuf(stderr, NULL, _IONBF, 0);

		/* Prepare Winsock */
		err = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (err != 0)
		{
			write_stderr("%s: WSAStartup failed: %d\n",
						 progname, err);
			exit(1);
		}

		/*
		 * By default abort() only generates a crash-dump in *non* debug
		 * builds. As our Assert() / ExceptionalCondition() uses abort(),
		 * leaving the default in place would make debugging harder.
		 *
		 * MINGW's own C runtime doesn't have _set_abort_behavior(). When
		 * targeting Microsoft's UCRT with mingw, it never links to the debug
		 * version of the library and thus doesn't need the call to
		 * _set_abort_behavior() either.
		 */
#if !defined(__MINGW32__) && !defined(__MINGW64__)
		_set_abort_behavior(_CALL_REPORTFAULT | _WRITE_ABORT_MSG,
							_CALL_REPORTFAULT | _WRITE_ABORT_MSG);
#endif							/* !defined(__MINGW32__) &&
								 * !defined(__MINGW64__) */

		/*
		 * SEM_FAILCRITICALERRORS causes more errors to be reported to
		 * callers.
		 *
		 * We used to also specify SEM_NOGPFAULTERRORBOX, but that prevents
		 * windows crash reporting from working. Which includes registered
		 * just-in-time debuggers, making it unnecessarily hard to debug
		 * problems on windows. Now we try to disable sources of popups
		 * separately below (note that SEM_NOGPFAULTERRORBOX did not actually
		 * prevent all sources of such popups).
		 */
		SetErrorMode(SEM_FAILCRITICALERRORS);

		/*
		 * Show errors on stderr instead of popup box (note this doesn't
		 * affect errors originating in the C runtime, see below).
		 */
		_set_error_mode(_OUT_TO_STDERR);

		/*
		 * In DEBUG builds, errors, including assertions, C runtime errors are
		 * reported via _CrtDbgReport. By default such errors are displayed
		 * with a popup (even with NOGPFAULTERRORBOX), preventing forward
		 * progress. Instead report such errors stderr (and the debugger).
		 * This is C runtime specific and thus the above incantations aren't
		 * sufficient to suppress these popups.
		 */
		_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
		_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
		_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
		_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
		_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
		_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
	}
#endif							/* WIN32 */
}


/*
 * Make the initial permanent setting for a locale category.  If that fails,
 * perhaps due to LC_foo=invalid in the environment, use locale C.  If even
 * that fails, perhaps due to out-of-memory, the entire startup fails with it.
 * When this returns, we are guaranteed to have a setting for the given
 * category's environment variable.
 */
static void
init_locale(const char *categoryname, int category, const char *locale)
{
	if (pg_perm_setlocale(category, locale) == NULL &&
		pg_perm_setlocale(category, "C") == NULL)
		elog(FATAL, "could not adopt \"%s\" locale nor C locale for %s",
			 locale, categoryname);
}



/*
 * Help display should match the options accepted by PostmasterMain()
 * and PostgresMain().
 *
 * XXX On Windows, non-ASCII localizations of these messages only display
 * correctly if the console output code page covers the necessary characters.
 * Messages emitted in write_console() do not exhibit this problem.
 */
static void
help(const char *progname)
{
	printf(_("%s is the PostgreSQL server.\n\n"), progname);
	printf(_("Usage:\n  %s [OPTION]...\n\n"), progname);
	printf(_("Options:\n"));
	printf(_("  -B NBUFFERS        number of shared buffers\n"));
	printf(_("  -c NAME=VALUE      set run-time parameter\n"));
	printf(_("  -C NAME            print value of run-time parameter, then exit\n"));
	printf(_("  -d 1-5             debugging level\n"));
	printf(_("  -D DATADIR         database directory\n"));
	printf(_("  -e                 use European date input format (DMY)\n"));
	printf(_("  -F                 turn fsync off\n"));
	printf(_("  -h HOSTNAME        host name or IP address to listen on\n"));
	printf(_("  -i                 enable TCP/IP connections (deprecated)\n"));
	printf(_("  -k DIRECTORY       Unix-domain socket location\n"));
#ifdef USE_SSL
	printf(_("  -l                 enable SSL connections\n"));
#endif
	printf(_("  -N MAX-CONNECT     maximum number of allowed connections\n"));
	printf(_("  -p PORT            port number to listen on\n"));
	printf(_("  -s                 show statistics after each query\n"));
	printf(_("  -S WORK-MEM        set amount of memory for sorts (in kB)\n"));
	printf(_("  -V, --version      output version information, then exit\n"));
	printf(_("  --NAME=VALUE       set run-time parameter\n"));
	printf(_("  --describe-config  describe configuration parameters, then exit\n"));
	printf(_("  -?, --help         show this help, then exit\n"));

	printf(_("\nDeveloper options:\n"));
	printf(_("  -f s|i|o|b|t|n|m|h forbid use of some plan types\n"));
	printf(_("  -O                 allow system table structure changes\n"));
	printf(_("  -P                 disable system indexes\n"));
	printf(_("  -t pa|pl|ex        show timings after each query\n"));
	printf(_("  -T                 send SIGABRT to all backend processes if one dies\n"));
	printf(_("  -W NUM             wait NUM seconds to allow attach from a debugger\n"));

	printf(_("\nOptions for single-user mode:\n"));
	printf(_("  --single           selects single-user mode (must be first argument)\n"));
	printf(_("  DBNAME             database name (defaults to user name)\n"));
	printf(_("  -d 0-5             override debugging level\n"));
	printf(_("  -E                 echo statement before execution\n"));
	printf(_("  -j                 do not use newline as interactive query delimiter\n"));
	printf(_("  -r FILENAME        send stdout and stderr to given file\n"));

	printf(_("\nOptions for bootstrapping mode:\n"));
	printf(_("  --boot             selects bootstrapping mode (must be first argument)\n"));
	printf(_("  --check            selects check mode (must be first argument)\n"));
	printf(_("  DBNAME             database name (mandatory argument in bootstrapping mode)\n"));
	printf(_("  -r FILENAME        send stdout and stderr to given file\n"));

	printf(_("\nPlease read the documentation for the complete list of run-time\n"
			 "configuration settings and how to set them on the command line or in\n"
			 "the configuration file.\n\n"
			 "Report bugs to <%s>.\n"), PACKAGE_BUGREPORT);
	printf(_("%s home page: <%s>\n"), PACKAGE_NAME, PACKAGE_URL);
}



static void
check_root(const char *progname)
{
#ifndef WIN32
	if (geteuid() == 0)
	{
		write_stderr("\"root\" execution of the PostgreSQL server is not permitted.\n"
					 "The server must be started under an unprivileged user ID to prevent\n"
					 "possible system security compromise.  See the documentation for\n"
					 "more information on how to properly start the server.\n");
		exit(1);
	}

	/*
	 * Also make sure that real and effective uids are the same. Executing as
	 * a setuid program from a root shell is a security hole, since on many
	 * platforms a nefarious subroutine could setuid back to root if real uid
	 * is root.  (Since nobody actually uses postgres as a setuid program,
	 * trying to actively fix this situation seems more trouble than it's
	 * worth; we'll just expend the effort to check for it.)
	 */
	if (getuid() != geteuid())
	{
		write_stderr("%s: real and effective user IDs must match\n",
					 progname);
		exit(1);
	}
#else							/* WIN32 */
	if (pgwin32_is_admin())
	{
		write_stderr("Execution of PostgreSQL by a user with administrative permissions is not\n"
					 "permitted.\n"
					 "The server must be started under an unprivileged user ID to prevent\n"
					 "possible system security compromises.  See the documentation for\n"
					 "more information on how to properly start the server.\n");
		exit(1);
	}
#endif							/* WIN32 */
}

/*
 * At least on linux, set_ps_display() breaks /proc/$pid/environ. The
 * sanitizer library uses /proc/$pid/environ to implement getenv() as it wants
 * to work independent of libc. When just using undefined and alignment
 * sanitizers, the sanitizer library is only initialized when the first error
 * occurs, by which time we've often already called set_ps_display(),
 * preventing the sanitizer libraries from seeing the options.
 *
 * We can work around that by defining __ubsan_default_options, a weak symbol
 * libsanitizer uses to get defaults from the application, and return
 * getenv("UBSAN_OPTIONS"). But only if main already was reached, so that we
 * don't end up relying on a not-yet-working getenv().
 *
 * As this function won't get called when not running a sanitizer, it doesn't
 * seem necessary to only compile it conditionally.
 */
const char *__ubsan_default_options(void);
const char *
__ubsan_default_options(void)
{
	/* don't call libc before it's guaranteed to be initialized */
	if (!reached_main)
		return "";

	return getenv("UBSAN_OPTIONS");
}
