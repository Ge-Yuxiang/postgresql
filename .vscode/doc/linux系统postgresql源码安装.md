Linux 上安装PostgreSQL-源码编译安装（超详细版）

# 1. 服务器资源配置

## 1.1. 服务器配置
- **操作系统**：CentOS Linux 7 (Core)
- **CPU**：4核
- **内存**：8GB
- **磁盘**：100GB

## 1.2. 最小配置
- **CPU**：至少 2 核心
- **内存**：至少 2 GB
- **硬盘**：至少 10 GB 空间，推荐使用 SSD 以提高性能
- **网络**：100 Mbps
- **适用场景**：这种配置适用于轻量级的测试，如功能验证、小型应用的开发等。

## 1.3. 推荐配置
- **CPU**：4 核心或以上
- **内存**：8 GB 或以上
- **硬盘**：50 GB 或更多的 SSD 空间
- **网络**：1 Gbps
- **适用场景**：这种配置适用于更加接近生产环境的测试，包括性能测试、大规模数据处理等。

# 2. 官网 PostgreSQL 安装包介绍

## 2.1. 下载地址
- **官方网站**：[PostgreSQL: File Browser](https://ftp.postgresql.org/pub/source/v17.0/)

## 2.2. 文件介绍
1. **postgresql-17.0.tar.bz2**：PostgreSQL 17.0 版本的源代码压缩包，使用 bzip2 压缩。
2. **postgresql-17.0.tar.bz2.md5**：包含 postgresql-17.0.tar.bz2 文件的 MD5 校验值。
3. **postgresql-17.0.tar.bz2.sha256**：包含 postgresql-17.0.tar.bz2 文件的 SHA-256 校验值。
4. **postgresql-17.0.tar.gz**：PostgreSQL 17.0 版本的源代码压缩包，使用 gzip 压缩。
5. **postgresql-17.0.tar.gz.md5**：包含 postgresql-17.0.tar.gz 文件的 MD5 校验值。
6. **postgresql-17.0.tar.gz.sha256**：包含 postgresql-17.0.tar.gz 文件的 SHA-256 校验值。

## 2.3. 压缩格式对比
- **.bz2（Bzip2）格式**：
  - **压缩率**：通常情况下，Bzip2 压缩算法提供了相对较高的压缩率，可以生成较小的文件。
  - **解压速度**：Bzip2 解压速度相对较慢。
  - **使用场景**：适用于希望文件体积尽可能小的情况，例如在网络上下载文件，以减小传输时间和节省带宽。
  - **解压命令**：`tar -jxvf postgresql-17.0.tar.bz2`

- **.gz（Gzip）格式**：
  - **压缩率**：Gzip 也提供了很好的压缩率，虽然通常略逊于 Bzip2，但在大多数情况下仍然足够。
  - **解压速度**：Gzip 的解压速度相对较快。
  - **使用场景**：适用于需要在短时间内解压大文件的情况，例如在安装软件时。
  - **解压命令**：`tar -zxvf postgresql-17.0.tar.gz`

# 3. 依赖环境配置

1. 安装 wget
   ```sh
   [root@localhost /]# yum -y install wget
   ```

2. 下载 PostgreSQL 14 的源代码包
   ```sh
   $ wget https://ftp.postgresql.org/pub/source/v17.0/postgresql-17.0.tar.gz
   ```

3. 安装编译 PostgreSQL 所需的依赖库
   ```sh
   $ sudo apt-get install perl libperl-dev python3 python-is-python3 python-dev-is-python3 build-essential zlib1g-dev libreadline-dev libssl-dev gcc g++ gdb cmake bear
   ```
   依赖包说明：
   | 序号 | 依赖包名称         | 说明                                                                 |
   |------|--------------------|----------------------------------------------------------------------|
   | 1    | perl-ExtUtils-Embed | 这个包用于嵌入Perl代码到C程序中。在PostgreSQL中，它可能被用于某些与Perl相关的扩展或自定义脚本功能。 |
   | 2    | readline-devel     | 这是readline库的开发版本，提供了命令行编辑和历史记录的功能。对于PostgreSQL，它使得使用交互式命令行工具（如psql）更加方便。 |
   | 3    | zlib-devel         | 这是zlib压缩库的开发版本，用于数据压缩和解压缩。在PostgreSQL中，它用于优化数据存储和传输。 |
   | 4    | pam-devel          | 这是Pluggable Authentication Modules（PAM）的开发包，用于集成多种认证技术。在PostgreSQL中，PAM可以用于用户认证。 |
   | 5    | libxml2-devel      | 这是libxml2库的开发版本，它提供了XML的支持。在PostgreSQL中，它用于处理XML数据格式的功能。 |
   | 6    | libxslt-devel      | 这是libxslt库的开发版本，用于XSLT转换。在PostgreSQL中，可能用于转换XML数据。 |
   | 7    | openldap-devel     | 这是OpenLDAP的开发包，用于LDAP协议的支持。在PostgreSQL中，它可以用于集成LDAP-based的用户认证。 |
   | 8    | python-devel       | 这是Python语言的开发包，可能用于支持Python编写的数据库脚本或扩展。 |
   | 9    | gcc-c++            | 这是GNU C++编译器，用于编译C++代码。它可能用于编译PostgreSQL中的某些C++编写的部分或扩展。 |
   | 10   | openssl-devel      | 这是OpenSSL库的开发版本，提供加密和SSL/TLS支持。在PostgreSQL中，它用于确保数据传输的安全性。 |
   | 11   | cmake              | 这是一个跨平台的安装（构建）系统，用于控制软件编译和测试的过程。在某些PostgreSQL的扩展或自定义安装中可能会用到。 |

# 4. 源码编译

1. 解压源代码包
   ```sh
   $ tar -xzf postgresql-17.0.tar.gz /media/skylinux/sky_code/postgresql-17.0
   ```

2. 进入解压后的目录
   ```sh
   $ cd /media/skylinux/sky_code/postgresql-17.0
   ```
3. 创建postgresql的编译目录
   ```sh
   $ mkdir -p /media/skylinux/sky_code/postgresql-17.0/build
   ```

4. 配置 PostgreSQL 安装选项
   ```sh
   $ CFLAGS="-g -O0" ./configure --prefix=/media/skylinux/sky_code/postgresql-17.0/build --with-perl --with-python --with-openssl --with-includes=/usr/local/ssl/include --with-libraries=/usr/local/ssl/lib --enable-debug
   ```

   配置参数
   | 参数 | 说明 |
   |------|------|
   | `CFLAGS="-g -O0"` | 设置编译器标志，其中 `-g` 表示生成调试信息，`-O0` 表示关闭优化。 |
   | `--prefix=/media/skylinux/sky_code/postgresql-17.0` | 指定 PostgreSQL 安装的根目录。安装完成后，PostgreSQL 的可执行文件、库文件、配置文件等将被安装到 `/media/skylinux/sky_code/postgresql-17.0` 目录及其子目录下。 |
   | `--with-perl` | 启用对 Perl 的支持。这允许 PostgreSQL 使用 Perl 语言编写函数和触发器。需要确保系统上已安装 `perl` 和 `perl-ExtUtils-Embed`。 |
   | `--with-python` | 启用对 Python 的支持。这允许 PostgreSQL 使用 Python 语言编写函数和触发器。需要确保系统上已安装 `python` 和 `python-devel`。 |
   | `--with-openssl` | 启用对 OpenSSL 的支持。这允许 PostgreSQL 使用 SSL/TLS 加密连接，确保数据传输的安全性。需要确保系统上已安装 `openssl` 和 `openssl-devel`。 |
   | `--with-includes=/usr/local/ssl/include` | 指定包含头文件的目录。告诉配置脚本在哪里找到 OpenSSL 的头文件。如果 OpenSSL 安装在非标准位置，需要指定这个选项。 |
   | `--with-libraries=/usr/local/ssl/lib` | 指定库文件的目录。告诉配置脚本在哪里找到 OpenSSL 的库文件。如果 OpenSSL 安装在非标准位置，需要指定这个选项。 |
   | `--enable-debug` | 启用调试模式。这会生成更多的调试信息，并可能包含额外的调试功能。 |

5. 编译安装PostgreSQL
   ```sh
   $ bear -- make
   $ sudo make install
   ```
   使用bear拦截make命令的编译过程，并生成一个包含编译命令的JSON文件生成compile_commands.json

6. 创建本地目录和postgresql编译目录的软连接
   ```sh
   $ sudo ln -sf /media/skylinux/sky_code/postgresql-17.0/build /usr/local/pgsql
   ```

7. 安装contrib目录的工具
   ```sh
   $ cd /media/skylinux/sky_code/postgresql-17.0/contrib
   $ make
   $ sudo make install
   ```

8. 创建用户组postgres、用户postgres
   ```sh
   sudo groupadd postgres
   sudo useradd -g postgres -m -s /bin/bash postgres
   sudo passwd postgres
   
   sudo chown -R postgres:postgres /home/postgres
   sudo chmod 700 /home/postgres
   ```

9.  配置可执行环境参数和路径
   1. 所有用户生效：修改/etc/bash.bashrc，添加下面几行
      ```sh
      $ sudo vim /etc/bash.bashrc
      ```

      ```shell
      export PGUSER=postgres
      export PGGROUP=postgres
      export PGHOME=/usr/local/pgsql
      export PGDATA=$PGHOME/postgres_data
      export PATH=$PGHOME/bin:$PATH
      export LD_LIBRARY_PATH=$HOME/lib:$LD_LIBRARY_PATH
      ```

      ```sh
      $ sudo source /etc/bash.bashrc
      ```
   2. 当前用户postgres生效：修改~/.bashrc，添加下面几行
      ```sh
      $ su postgres
      ```

      ```shell
      export PGDATA=$PGHOME/postgres_data
      export PATH=$HOME/.local/bin:$HOME/bin:$PATH
      ```

      ```sh
      $ source ~/.bashrc
      ```

# 5. 配置数据库
1. 切换到带创建数据库的用户postgres，并创建主目录
   ```sh
   $ mkdir -p $PGDATA
   $ chown postgres:postgres $PGHOME/postgres_data
   ```

2. 创建 PostgreSQL 数据库集群
   ```sh
   $ $PGHOME/bin/initdb -D $PGDATA
   ```

3. 配置postgresql参数
   1. 修改$PGDATA目录下postgresql.conf文件，该文件配置PostgreSQL数据库服务器的相应的参数
      ```vim
      # - Connection Settings -
      listen_addresses = '*'          # what IP address(es) to listen on;
                                              # comma-separated list of addresses;
                                              # defaults to 'localhost'; use '*' for all
                                              # (change requires restart)
      port = 5432                             # (change requires restart)
      max_connections = 100                   # (change requires restart)
      unix_socket_directories = '/tmp'        # comma-separated list of directories
                                        # (change requires restart)

      # This is used when logging to stderr:
      logging_collector = on          # Enable capturing of stderr, jsonlog,
                                              # and csvlog into log files. Required
                                              # to be on for csvlogs and jsonlogs.
                                              # (change requires restart)

      # These are only used if logging_collector is on:
      log_directory = 'log'                   # directory where log files are written,
                                              # can be absolute or relative to PGDATA
      log_filename = 'postgresql-%Y-%m-%d_%H%M%S.log'        # log file name pattern,
                                                              # can include strftime()
      ```
   2. 修改$PGDATA目录下pg_hba.conf 文件，该文件配置对数据库的访问权限
      ```vim
      # IPv4 local connections:
      host    all             all             127.0.0.1/32            trust
      host    all             all             0.0.0.0/0               trust
      ```

4. 启动 PostgreSQL 数据库服务
   ```sh
   $ $PGHOME/bin/pg_ctl start -D $PGDATA -l logfile
   ```

5. 验证 PostgreSQL 是否正常运行
   ```sh
   $  $PGHOME/bin/psql -U postgres
   ```

6. 停止PostgreSQL数据库服务
   ```sh
   $ $PGHOME/bin/pg_ctl stop -D $PGDATA -l logfile
   ```

如果能够连接到数据库并获得 `postgres=#` 提示符，则说明 PostgreSQL 已经安装并正常运行了。

# 6. 设置postgresql开机自启动
1. 在/etc/systemd/system目录下新建配置文件postgresql.service，内容如下
   ```service
   [Unit]

   # 简短描述
   Description=postgresql.service  

   # 在network.target服务之后运行，这里可以不要
   After=network.target

   [Service]
   Type=forking
   # 服务的类型，常用的有 simple（默认类型） 和 forking。默认的 simple 类型可以适应
   于绝大多数的场景，因此一般可以忽略这个参数的配置。而如果服务程序启动后会通过 fork 系统调用创建子进程，然后关闭应用程序本身进程的情况，则应该将 Type 的值设置为 forking，否则 systemd 将不会跟踪>子进程的行为，而认为服务已经退出。 系统调用pg后>会创建子进程，然后关闭本身进程，所以这里选择forKing进行子进程跟踪
   #运行程序的用户和群组
   User=postgres
   Group=postgres
   # 工作目录
   WorkingDirectory=/usr/local/pgsql
   # 启动命令
   ExecStart=/usr/local/pgsql/bin/pg_ctl start -D /usr/local/pgsql/postgres_data
   # 重新加载
   ExecReload=/usr/local/pgsql/bin/pg_ctl restart -D /usr/local/pgsql/postgres_data
   # 停止程序
   ExecStop=/usr/local/pgsql/bin/pg_ctl stop -D /usr/local/pgsql/postgres_data
   # 是否给服务分配独立的临时空间，需要
   PrivateTmp=true

   [Install]
   WantedBy=multi-user.target
   #和前面的 Wants 作用相似，只是后面列出的不是服务所依赖的模块，而是依赖当前服务的
   模块。
   ```

2. 使用systemctl命令启用PostgreSQL服务，使其在系统启动时自动启动
   ```sh
   sudo systemctl enable postgresql.service
   ```
3. 启动PostgreSQL服务
   ```sh
   sudo systemctl start postgresql.service
   ```
4. 检查 PostgreSQL 服务状态
   ```sh
   sudo systemctl status postgresql.service
   sudo systemctl is-active postgresql.service
   ```

# 7. 启动数据库服务
1. PostgreSQL服务
   ```sh
   [root@localhost start-scripts]# service postgresql start
   Starting PostgreSQL: ok
   ```

2. PostgreSQL 服务，确认是否启动成功
   ```sh
   [root@localhost start-scripts]# ps -ef | grep postgres
   ```

3. 查看 PostgreSQL 监听端口
   ```sh
   [root@localhost start-scripts]# netstat -ltnup | grep post
   ```

# 8. 测试本地连接

1. 切换到 postgres 用户
   ```sh
   [root@localhost start-scripts]# su postgres
   Last login: Wed Dec 13 15:13:04 CST 2023 on pts/0
   [postgres@localhost ~]$ psql -h localhost
   psql (17.0)
   Type "help" for help.
   ```

2. 列出所有数据库
   ```sql
   postgres=# \l
                     List of databases
      Name    |  Owner   | Encoding |  Collate   |   Ctype    |   Access privileges   
   -----------+----------+----------+------------+------------+-----------------------
    postgres  | postgres | UTF8     | en_US.UTF-8| en_US.UTF-8| 
    template0 | postgres | UTF8     | en_US.UTF-8| en_US.UTF-8| =c/postgres          +
              |          |          |            |            | postgres=CTc/postgres
    template1 | postgres | UTF8     | en_US.UTF-8| en_US.UTF-8| =c/postgres          +
              |          |          |            |            | postgres=CTc/postgres
   (3 rows)
   ```