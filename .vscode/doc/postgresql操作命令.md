# 1. shell命令行

## 1.1. postgresql的开机启动配置
| 命令 | 功能 | 用户 |
| ------ | ------ | ------ |
| systemctl start postgresql.17.0  | 启动/etc/systemd/system/postgresql.17.0.service | root   |
| systemctl restart postgresql.17.0  | 重启postgresql.17.0.service | root   |
| systemctl stop postgresql.17.0  | 停止postgresql.17.0.service | root   |
| systemctl status postgresql.17.0  | 查询postgresql.17.0.service状态 | root   |
| systemctl enable postgresql.17.0  | 注册postgresql.17.0.service | root   |
| systemctl disable postgresql.17.0  | 注销postgresql.17.0.service | root   |

## 1.2. postgresql的服务启停
| 命令 | 功能 | 用户 |
| ------ | ------ | ------ |
| pg_ctl start -D /usr/local/pgsql/postgres_data  | 启动postgres_data目录的postgres数据库 | postgres   |
| pg_ctl stop -D /usr/local/pgsql/postgres_data  | 停止postgres_data目录的postgres数据库 | postgres   |
| pg_ctl restart -D /usr/local/pgsql/postgres_data  | 重启postgres_data目录的postgres数据库 | postgres   |

## 1.3. postgresql的bin目录下其他工具的使用
| 工具名称       | 用途                                                         | 示例命令                                                     | 用法结构                                                      |
|----------------|--------------------------------------------------------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `createdb`     | 创建新的数据库                                               | `createdb mydatabase`                                        | `createdb [OPTION]... [DBNAME [OWNER]]`                      |
| `dropdb`       | 删除数据库                                                   | `dropdb mydatabase`                                          | `dropdb [OPTION]... [DBNAME]`                                |
| `createuser`   | 创建新的 PostgreSQL 用户                                      | `createuser -U postgres myuser`                              | `createuser [OPTION]... [NAME]`                              |
| `dropuser`     | 删除 PostgreSQL 用户                                         | `dropuser myuser`                                            | `dropuser [OPTION]... [NAME]`                                |
| `initdb`       | 初始化一个新的 PostgreSQL 数据目录                           | `initdb /path/to/new/data/directory`                         | `initdb [OPTION]... [DIRECTORY]`                             |
| `pg_basebackup`| 从一个正在运行的 PostgreSQL 数据库服务器上复制一个基础备份   | `pg_basebackup -D /path/to/backup -h localhost -U postgres`   | `pg_basebackup [OPTION]...`                                  |
| `pg_dump`      | 导出一个数据库的内容                                         | `pg_dump mydatabase > backup.sql`                            | `pg_dump [OPTION]... [DBNAME]`                               |
| `pg_dumpall`   | 导出整个 PostgreSQL 系统的所有数据库的内容                   | `pg_dumpall > all_databases.sql`                             | `pg_dumpall [OPTION]...`                                     |
| `pg_restore`   | 从备份文件中恢复数据库                                       | `pg_restore -d mydatabase backup.sql`                        | `pg_restore [OPTION]... [FILENAME]`                          |
| `pg_upgrade`   | 升级 PostgreSQL 数据库集群                                   | `pg_upgrade -b /path/to/old/bin -B /path/to/new/bin -d old_cluster_dir -D new_cluster_dir` | `pg_upgrade [OPTION]...`                                     |
| `pg_ctl`       | 控制 PostgreSQL 数据库服务器的启动、停止和状态检查             | `pg_ctl start -D /path/to/data/directory -l logfile`          | `pg_ctl [OPTION]... COMMAND [INSTANCE]`                      |
| `pg_isready`   | 检查 PostgreSQL 数据库服务器是否正在运行                     | `pg_isready -h localhost -p 5432`                            | `pg_isready [OPTION]...`                                     |
| `psql`         | 与 PostgreSQL 数据库交互的命令行工具                         | `psql mydatabase`                                            | `psql [OPTION]... [DBNAME]`                                  |
| `pgbench`      | 测试 PostgreSQL 数据库服务器的性能                           | `pgbench -i -s 1 mydatabase`                                 | `pgbench [OPTION]... [DBNAME]`                               |
| `pg_test_fsync`| 测试 PostgreSQL 数据库服务器的 fsync 功能                     | `pg_test_fsync -d /path/to/data/directory`                   | `pg_test_fsync [OPTION]...`                                  |
| `pg_test_timing`| 测试 PostgreSQL 数据库服务器的时间测量功能                     | `pg_test_timing -D /path/to/data/directory`                  | `pg_test_timing [OPTION]...`                                 |
| `pg_controldata`| 显示 PostgreSQL 数据库集群的关键信息                         | `pg_controldata /path/to/data/directory`                     | `pg_controldata [OPTION]... [DIRECTORY]`                     |
| `pg_resetwal`  | 重置 PostgreSQL 数据库集群的 WAL 文件                       | `pg_resetwal /path/to/data/directory`                        | `pg_resetwal [OPTION]... [DIRECTORY]`                        |
| `reindexdb`    | 重建 PostgreSQL 数据库中的索引                               | `reindexdb mydatabase`                                       | `reindexdb [OPTION]... [DBNAME]`                             |
| `vacuumdb`     | 对 PostgreSQL 数据库进行 VACUUM 操作                         | `vacuumdb mydatabase`                                        | `vacuumdb [OPTION]... [DBNAME]`                              |
| `vacuumlo`     | 对 PostgreSQL 大对象进行 VACUUM 操作                         | `vacuumlo mydatabase`                                        | `vacuumlo [OPTION]... [DBNAME]`                              |
| `pg_rewind`    | 快速同步两个 PostgreSQL 数据库实例                           | `pg_rewind --source=localhost --target=/path/to/target/directory` | `pg_rewind [OPTION]... --source=SOURCE --target=TARGET`     |
| `pg_waldump`   | 显示 PostgreSQL 数据库的 WAL 记录                           | `pg_waldump /path/to/wal/file`                               | `pg_waldump [OPTION]... [FILE]`                              |
| `pg_verifybackup`| 验证 PostgreSQL 数据库备份文件的有效性                       | `pg_verifybackup /path/to/backup/directory`                  | `pg_verifybackup [OPTION]... [BACKUP_DIR]`                   |
| `pg_recvlogical`| 接收来自 PostgreSQL 数据库的逻辑复制流                       | `pg_recvlogical --slot=myslot --output-format=csv --file=/path/to/output/file` | `pg_recvlogical [OPTION]... [SLOT]`                          |
| `pg_archivecleanup`| 清理 PostgreSQL 归档文件                                     | `pg_archivecleanup /path/to/archive/directory`               | `pg_archivecleanup [OPTION]... [ARCHIVE_DIRECTORY]`          |
| `pg_checksums` | 计算 PostgreSQL 数据库表的校验和                           | `pg_checksums mydatabase`                                    | `pg_checksums [OPTION]... [DBNAME]`                          |
| `oid2name`     | 显示 PostgreSQL 对象标识符 (OID) 到名字的映射               | `oid2name 16384`                                             | `oid2name [OPTION]... [OID]`                                 |
| `pg_walsummary`| 显示 PostgreSQL 数据库的 WAL 概要信息                       | `pg_walsummary /path/to/data/directory`                      | `pg_walsummary [OPTION]... [DIRECTORY]`                      |

### 1.3.1. `createdb`

| 选项                 | 描述                                                         | 示例命令                                                     |
|----------------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `-U username`        | 指定连接数据库的用户名                                       | `createdb -U postgres mydatabase`                           |
| `-O owner`           | 指定数据库的所有者                                           | `createdb -O user1 mydatabase`                              |
| `-E encoding`        | 指定数据库的字符集编码                                       | `createdb -E UTF8 mydatabase`                               |
| `-T template`        | 指定作为模板的数据库                                         | `createdb -T template0 mydatabase`                          |
| `-l locale`          | 指定数据库的区域设置                                         | `createdb -l en_US.UTF-8 mydatabase`                        |
| `-e`                 | 显示详细的错误消息                                           | `createdb -e mydatabase`                                    |
| `-V`                 | 显示版本信息                                                 | `createdb --version`                                        |

### 1.3.2. `dropdb`

| 选项                 | 描述                                                         | 示例命令                                                     |
|----------------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `-U username`        | 指定连接数据库的用户名                                       | `dropdb -U postgres mydatabase`                             |
| `-h host`            | 指定数据库服务器的主机地址                                   | `dropdb -h localhost mydatabase`                            |
| `-P password`        | 指定数据库用户的密码                                         | `dropdb -P 'mypassword' mydatabase`                         |
| `-e`                 | 显示详细的错误消息                                           | `dropdb -e mydatabase`                                      |
| `-V`                 | 显示版本信息                                                 | `dropdb --version`                                          |

### 1.3.3. `createuser`

| 选项                 | 描述                                                         | 示例命令                                                     |
|----------------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `-U username`        | 指定连接数据库的用户名                                       | `createuser -U postgres newuser`                            |
| `-P`                 | 强制输入密码                                                 | `createuser -P newuser`                                     |
| `-s`                 | 创建超级用户                                                 | `createuser -s newuser`                                     |
| `-r`                 | 创建复制用户                                                 | `createuser -r newuser`                                     |
| `-e`                 | 创建超级用户                                                 | `createuser -e newuser`                                     |
| `-d`                 | 允许用户创建数据库                                           | `createuser -d newuser`                                     |
| `-l`                 | 创建登录用户                                                 | `createuser -l newuser`                                     |
| `-S`                 | 禁止超级用户                                                 | `createuser -S newuser`                                     |
| `-R`                 | 禁止复制用户                                                 | `createuser -R newuser`                                     |
| `-E`                 | 禁止登录用户                                                 | `createuser -E newuser`                                     |
| `-D`                 | 禁止创建数据库                                               | `createuser -D newuser`                                     |
| `-v`                 | 显示详细的进度信息                                           | `createuser -v newuser`                                     |
| `-V`                 | 显示版本信息                                                 | `createuser --version`                                      |

### 1.3.4. `dropuser`

| 选项                 | 描述                                                         | 示例命令                                                     |
|----------------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `-U username`        | 指定连接数据库的用户名                                       | `dropuser -U postgres olduser`                               |
| `-P`                 | 强制输入密码                                                 | `dropuser -P olduser`                                        |
| `-v`                 | 显示详细的进度信息                                           | `dropuser -v olduser`                                        |
| `-V`                 | 显示版本信息                                                 | `dropuser --version`                                         |

### 1.3.5. `initdb`

| 选项                 | 描述                                                         | 示例命令                                                     |
|----------------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `-D directory`       | 指定初始化的数据目录                                         | `initdb -D /path/to/data/directory`                          |
| `-U username`        | 指定数据库超级用户的用户名                                   | `initdb -U postgres`                                         |
| `-E encoding`        | 指定数据库的字符集编码                                       | `initdb -E UTF8`                                             |
| `-l locale`          | 指定数据库的区域设置                                         | `initdb -l en_US.UTF-8`                                      |
| `-w`                 | 强制输入密码                                                 | `initdb -w`                                                  |
| `-v`                 | 显示详细的进度信息                                           | `initdb -v`                                                  |
| `-V`                 | 显示版本信息                                                 | `initdb --version`                                           |

### 1.3.6. `pg_basebackup`

| 选项                 | 描述                                                         | 示例命令                                                     |
|----------------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `-D directory`       | 指定备份的目标目录                                           | `pg_basebackup -D /path/to/backup`                          |
| `-h host`            | 指定数据库服务器的主机地址                                   | `pg_basebackup -h localhost`                                |
| `-U username`        | 指定连接数据库的用户名                                       | `pg_basebackup -U postgres`                                 |
| `-P`                 | 显示进度条                                                   | `pg_basebackup -P`                                          |
| `-v`                 | 显示详细的进度信息                                           | `pg_basebackup -v`                                          |
| `-V`                 | 显示版本信息                                                 | `pg_basebackup --version`                                   |
| `-X method`          | 指定使用的备份方法 (`stream`, `fetch`)                       | `pg_basebackup -X stream`                                   |
| `-Z level`           | 指定压缩级别                                                 | `pg_basebackup -Z 6`                                        |
| `-W`                 | 强制输入密码                                                 | `pg_basebackup -W`                                          |

### 1.3.7. `pg_dump`

| 选项                 | 描述                                                         | 示例命令                                                     |
|----------------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `-h host`            | 指定数据库服务器的主机地址                                   | `pg_dump -h localhost -d mydatabase`                        |
| `-U username`        | 指定连接数据库的用户名                                       | `pg_dump -U postgres -d mydatabase`                         |
| `-d dbname`          | 指定要备份的数据库名称                                       | `pg_dump -d mydatabase`                                     |
| `-f file`            | 将输出写入指定文件                                           | `pg_dump -d mydatabase -f backup.sql`                       |
| `-s`                 | 仅导出表结构，不包含数据                                     | `pg_dump -s -d mydatabase`                                  |
| `-t table`           | 仅导出指定的表                                               | `pg_dump -s -t people -d mydatabase`                        |
| `-T table`           | 不导出指定的表                                               | `pg_dump -s -T people -d mydatabase`                        |
| `-a`                 | 仅导出表数据，不包含结构                                     | `pg_dump -a -d mydatabase`                                  |
| `-O`                 | 不导出拥有者信息                                             | `pg_dump -s -O -d mydatabase`                               |
| `-x`                 | 不导出扩展对象                                               | `pg_dump -s -x -d mydatabase`                               |
| `-v`                 | 显示详细的进度信息                                           | `pg_dump -v -d mydatabase`                                  |
| `-E encoding`        | 指定输出文件的字符集编码                                     | `pg_dump -E UTF8 -d mydatabase`                             |
| `-F format`          | 指定输出文件的格式（`custom`, `tar`, `plain`, `directory`）   | `pg_dump -F t -d mydatabase`                                |
| `-j`                 | 合并多行 SQL 语句为单行                                      | `pg_dump -s -j -d mydatabase`                               |
| `-n schema`          | 仅导出指定模式（schema）                                      | `pg_dump -s -n public -d mydatabase`                        |
| `-N schema`          | 不导出指定模式（schema）                                      | `pg_dump -s -N public -d mydatabase`                        |
| `-Z level`           | 指定压缩级别（仅适用于 custom 格式）                           | `pg_dump -F c -Z 9 -d mydatabase`                           |
| `-y`                 | 在导出的 SQL 文件中包含 DROP DATABASE 语句                     | `pg_dump -y -d mydatabase`                                  |
| `-l`                 | 导出逻辑复制槽信息（仅适用于 custom 格式）                    | `pg_dump -F c -l -d mydatabase`                             |
| `-P`                 | 不导出特权信息                                               | `pg_dump -s -P -d mydatabase`                               |
| `-k`                 | 导出时保留关键字                                             | `pg_dump -s -k -d mydatabase`                               |
| `-I`                 | 不导出索引                                                   | `pg_dump -s -I -d mydatabase`                               |
| `-C`                 | 生成一个自包含的数据库备份                                   | `pg_dump -C -d mydatabase`                                  |
| `-A`                 | 仅导出表空间信息                                             | `pg_dump -A -d mydatabase`                                  |
| `-W`                 | 强制输入密码                                                 | `pg_dump -W -d mydatabase`                                  |
| `--schema-only`      | 仅导出表结构，不包含数据（等同于 `-s`）                       | `pg_dump --schema-only -d mydatabase`                       |
| `--data-only`        | 仅导出表数据，不包含结构（等同于 `-a`）                       | `pg_dump --data-only -d mydatabase`                         |
| `--clean`            | 在导出前删除旧的数据（仅适用于 custom 格式）                    | `pg_dump --clean -F c -d mydatabase`                        |
| `--format`           | 指定输出文件的格式（等同于 `-F`）                             | `pg_dump --format=tar -d mydatabase`                        |
| `--compress`         | 指定压缩级别（等同于 `-Z`）                                   | `pg_dump --compress=9 -F c -d mydatabase`                   |
| `--verbose`          | 显示详细的进度信息（等同于 `-v`）                             | `pg_dump --verbose -d mydatabase`                           |

### 1.3.8. `pg_dumpall`

| 选项                 | 描述                                                         | 示例命令                                                     |
|----------------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `-g`                 | 导出角色（用户）                                             | `pg_dumpall -g`                                              |
| `-s`                 | 导出表结构，不包含数据                                       | `pg_dumpall -s`                                              |
| `-U username`        | 指定连接数据库的用户名                                       | `pg_dumpall -U postgres`                                     |
| `-h host`            | 指定数据库服务器的主机地址                                   | `pg_dumpall -h localhost`                                    |
| `-v`                 | 显示详细的进度信息                                           | `pg_dumpall -v`                                              |
| `-V`                 | 显示版本信息                                                 | `pg_dumpall --version`                                       |
| `-p port`            | 指定数据库服务器的端口                                       | `pg_dumpall -p 5432`                                         |
| `-f file`            | 将输出写入指定文件                                           | `pg_dumpall -f all_databases.sql`                            |

### 1.3.9. `pg_restore`

| 选项                   | 描述                                                         | 示例命令                                                     |
|------------------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `-h HOST`              | 指定恢复到的数据库服务器的主机地址                           | `pg_restore -h localhost -U postgres -d mydatabase -1`       |
| `-U USER`              | 指定用于恢复的数据库用户                                     | `pg_restore -U postgres -d mydatabase -1`                   |
| `-d DBNAME`            | 指定恢复的目标数据库名称                                     | `pg_restore -d mydatabase -1`                               |
| `-f FILE`              | 从指定文件进行恢复                                           | `pg_restore -d mydatabase -f backup.tar`                    |
| `-t TABLE`             | 仅恢复指定的表                                               | `pg_restore -d mydatabase -f backup.tar -t people`          |
| `-T TABLE`             | 不恢复指定的表                                               | `pg_restore -d mydatabase -f backup.tar -T people`          |
| `-s`                   | 仅恢复表结构                                                 | `pg_restore -d mydatabase -f backup.tar -s`                 |
| `-a`                   | 仅恢复表数据                                                 | `pg_restore -d mydatabase -f backup.tar -a`                 |
| `-O`                   | 不恢复拥有者信息                                             | `pg_restore -d mydatabase -f backup.tar -O`                 |
| `-x`                   | 不恢复扩展对象                                               | `pg_restore -d mydatabase -f backup.tar -x`                 |
| `-v`                   | 显示详细的进度信息                                           | `pg_restore -d mydatabase -f backup.tar -v`                 |
| `-E ENCODING`          | 指定输出文件的字符集编码                                     | `pg_restore -d mydatabase -f backup.tar -E UTF8`            |
| `-F FORMAT`            | 指定输入文件的格式（`custom`, `tar`, `plain`, `directory`）   | `pg_restore -d mydatabase -f backup.tar -F t`               |
| `-n SCHEMA`            | 仅恢复指定模式（schema）                                      | `pg_restore -d mydatabase -f backup.tar -n public`          |
| `-N SCHEMA`            | 不恢复指定模式（schema）                                      | `pg_restore -d mydatabase -f backup.tar -N public`          |
| `-Z LEVEL`             | 指定解压级别（仅适用于 custom 格式）                          | `pg_restore -d mydatabase -f backup.tar -F c -Z 9`          |
| `-l`                   | 恢复逻辑复制槽信息（仅适用于 custom 格式）                    | `pg_restore -d mydatabase -f backup.tar -F c -l`            |
| `-P`                   | 不恢复特权信息                                               | `pg_restore -d mydatabase -f backup.tar -P`                 |
| `-k`                   | 恢复时保留关键字                                             | `pg_restore -d mydatabase -f backup.tar -k`                 |
| `-I`                   | 不恢复索引                                                   | `pg_restore -d mydatabase -f backup.tar -I`                 |
| `-c`                   | 创建目标数据库（如果不存在）                                  | `pg_restore -c -d mydatabase -f backup.tar`                 |
| `-w`                   | 交互式确认（密码等）                                         | `pg_restore -d mydatabase -f backup.tar -w`                 |
| `-j NUM`               | 设置并行处理的数量                                            | `pg_restore -d mydatabase -f backup.tar -j 4`               |

### 1.3.10. `pg_upgrade`

| 选项                   | 描述                                                         | 示例命令                                                     |
|------------------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `-c`                   | 进行数据文件检查                                              | `pg_upgrade -c`                                              |
| `-v`                   | 显示详细的进度信息                                           | `pg_upgrade -v`                                              |
| `-s`                   | 指定源 PostgreSQL 数据目录                                    | `pg_upgrade -s /old/datadir`                                 |
| `-S`                   | 指定源 PostgreSQL 数据目录的版本                              | `pg_upgrade -S 9.3`                                          |
| `-d`                   | 指定目标 PostgreSQL 数据目录                                  | `pg_upgrade -d /new/datadir`                                 |
| `-D`                   | 指定目标 PostgreSQL 数据目录的版本                            | `pg_upgrade -D 9.4`                                          |
| `-p PORT`              | 指定端口号                                                    | `pg_upgrade -p 5432`                                         |
| `-P PORT`              | 指定目标端口号                                                | `pg_upgrade -P 5433`                                         |
| `-U USER`              | 指定用于连接数据库的用户名                                    | `pg_upgrade -U postgres`                                     |
| `-l LOGFILE`           | 指定日志文件路径                                              | `pg_upgrade -l /path/to/logfile`                             |
| `-e`                   | 允许错误继续升级过程                                          | `pg_upgrade -e`                                              |
| `-n`                   | 跳过数据文件检查                                              | `pg_upgrade -n`                                              |

### 1.3.11. `pg_ctl`

| 选项                   | 描述                                                         | 示例命令                                                     |
|------------------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `-D DATADIR`           | 指定数据目录                                                 | `pg_ctl -D /var/lib/pgsql/data start`                        |
| `-m FAST`              | 快速停止                                                     | `pg_ctl -D /var/lib/pgsql/data stop -m fast`                |
| `-o OPTIONS`           | 指定启动选项                                                 | `pg_ctl -D /var/lib/pgsql/data start -o "-c listen_addresses='*'"` |
| `-w`                   | 等待直到服务启动或停止                                       | `pg_ctl -D /var/lib/pgsql/data start -w`                     |
| `-l LOGFILE`           | 指定日志文件                                                 | `pg_ctl -D /var/lib/pgsql/data start -l /var/log/pgsql.log`  |
| `-V`                   | 显示版本信息                                                 | `pg_ctl -V`                                                  |
| `-s`                   | 以简单模式运行（不等待）                                      | `pg_ctl -D /var/lib/pgsql/data start -s`                     |
| `-S`                   | 指定服务器标识符（当有多个实例运行时使用）                    | `pg_ctl -D /var/lib/pgsql/data start -S instance1`           |

### 1.3.12. `pg_isready`

| 选项                   | 描述                                                         | 示例命令                                                     |
|------------------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `-h HOST`              | 指定数据库服务器的主机地址                                   | `pg_isready -h localhost`                                   |
| `-p PORT`              | 指定端口号                                                    | `pg_isready -p 5432`                                        |
| `-U USER`              | 指定连接数据库的用户名称                                     | `pg_isready -U postgres`                                    |
| `-q`                   | 安静模式（仅输出结果）                                       | `pg_isready -q`                                             |
| `-d DBNAME`            | 指定数据库名称                                               | `pg_isready -d mydatabase`                                  |

### 1.3.13. `psql`

| 选项                   | 描述                                                         | 示例命令                                                     |
|------------------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `-h HOST`              | 指定数据库服务器的主机地址                                   | `psql -h localhost -U postgres`                             |
| `-p PORT`              | 指定端口号                                                    | `psql -p 5432 -U postgres`                                  |
| `-U USER`              | 指定连接数据库的用户名称                                     | `psql -U postgres`                                          |
| `-d DBNAME`            | 指定连接的数据库名称                                         | `psql -d mydatabase`                                        |
| `-c CMD`               | 执行单条SQL命令后退出                                        | `psql -c "SELECT * FROM users;"`                            |
| `-f FILE`              | 从文件读取SQL命令并执行                                      | `psql -f script.sql`                                        |
| `-v VAR=VALUE`         | 设置变量                                                      | `psql -v user=johndoe`                                      |
| `-q`                   | 安静模式                                                     | `psql -q -c "SELECT * FROM users;"`                         |
| `-t`                   | 只显示查询结果的行                                           | `psql -t -c "SELECT * FROM users;"`                         |
| `-A`                   | 输出无标题头、无边框的纯文本格式                             | `psql -A -c "SELECT * FROM users;"`                         |
| `-w`                   | 自动宽度模式（自动调整列宽）                                 | `psql -w -c "SELECT * FROM users;"`                         |
| `-E`                   | 显示解析器/规划器输出                                         | `psql -E -c "SELECT * FROM users;"`                         |
| `-l`                   | 列出所有数据库                                               | `psql -l`                                                   |
| `-L`                   | 列出所有数据库，带额外信息                                   | `psql -L`                                                   |
| `-h`                   | 显示帮助信息                                                 | `psql -h`                                                   |

### 1.3.14. `pgbench`

| 选项                   | 描述                                                         | 示例命令                                                     |
|------------------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `-h HOST`              | 指定数据库服务器的主机地址                                   | `pgbench -h localhost -U postgres`                          |
| `-p PORT`              | 指定端口号                                                    | `pgbench -p 5432 -U postgres`                               |
| `-U USER`              | 指定连接数据库的用户名称                                     | `pgbench -U postgres`                                       |
| `-d DBNAME`            | 指定连接的数据库名称                                         | `pgbench -d mydatabase`                                     |
| `-i`                   | 初始化数据库                                                 | `pgbench -i -s 10 mydatabase`                               |
| `-c CLIENTS`           | 指定并发客户端数量                                           | `pgbench -c 100 -t 1000 mydatabase`                         |
| `-t TX`                | 指定事务数                                                   | `pgbench -c 100 -t 1000 mydatabase`                         |
| `-r`                   | 随机选取事务                                                 | `pgbench -c 100 -t 1000 -r mydatabase`                      |
| `-s SCALE`             | 设置基准测试的规模因子                                       | `pgbench -i -s 10 mydatabase`                               |
| `-P`                   | 指定预备查询的数量                                           | `pgbench -P 10 -c 100 -t 1000 mydatabase`                   |
| `-l`                   | 输出日志文件                                                 | `pgbench -l logfile -c 100 -t 1000 mydatabase`              |
| `-C`                   | 清除数据库中的 pgbench 表                                    | `pgbench -C mydatabase`                                     |
| `-T`                   | 指定单一事务的持续时间                                       | `pgbench -T 60 -c 100 -t 1000 mydatabase`                   |
| `-j`                   | 并发线程数                                                   | `pgbench -j 4 -c 100 -t 1000 mydatabase`                    |
| `-v`                   | 显示详细的进度信息                                           | `pgbench -v -c 100 -t 1000 mydatabase`                      |

### 1.3.15. `pg_test_fsync`

| 选项                   | 描述                                                         | 示例命令                                                     |
|------------------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `-h HOST`              | 指定数据库服务器的主机地址                                   | `pg_test_fsync -h localhost`                                |
| `-p PORT`              | 指定端口号                                                    | `pg_test_fsync -p 5432`                                     |
| `-U USER`              | 指定连接数据库的用户名称                                     | `pg_test_fsync -U postgres`                                 |
| `-d DBNAME`            | 指定连接的数据库名称                                         | `pg_test_fsync -d mydatabase`                               |
| `-D DATADIR`           | 指定数据目录                                                 | `pg_test_fsync -D /var/lib/pgsql/data`                      |
| `-t TEST`              | 指定测试类型                                                 | `pg_test_fsync -t all`                                      |
| `-r`                   | 强制重新创建数据库                                           | `pg_test_fsync -r`                                          |
| `-v`                   | 显示详细的进度信息                                           | `pg_test_fsync -v`                                          |
| `-q`                   | 安静模式                                                     | `pg_test_fsync -q`                                          |

### 1.3.16. `pg_test_timing`

| 选项                   | 描述                                                         | 示例命令                                                     |
|------------------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `-h HOST`              | 指定数据库服务器的主机地址                                   | `pg_test_timing -h localhost`                               |
| `-p PORT`              | 指定端口号                                                    | `pg_test_timing -p 5432`                                    |
| `-U USER`              | 指定连接数据库的用户名称                                     | `pg_test_timing -U postgres`                                |
| `-d DBNAME`            | 指定连接的数据库名称                                         | `pg_test_timing -d mydatabase`                              |
| `-D DATADIR`           | 指定数据目录                                                 | `pg_test_timing -D /var/lib/pgsql/data`                     |
| `-t TEST`              | 指定测试类型                                                 | `pg_test_timing -t all`                                     |
| `-r`                   | 强制重新创 

### 1.3.17. `pg_controldata`

| 选项                   | 描述                                                         | 示例命令                                                     |
|------------------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `-D DATADIR`           | 指定PostgreSQL的数据目录                                     | `pg_controldata -D /var/lib/postgresql/data`                |
| `-?`                   | 显示帮助信息                                                 | `pg_controldata -?`                                         |

### 1.3.18. `pg_resetwal`

| 选项                   | 描述                                                         | 示例命令                                                     |
|------------------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `-D DATADIR`           | 指定PostgreSQL的数据目录                                     | `pg_resetwal -D /var/lib/postgresql/data`                   |
| `-q`                   | 安静模式                                                     | `pg_resetwal -q -D /var/lib/postgresql/data`                |
| `-Z`                   | 清空所有WAL文件                                             | `pg_resetwal -Z -D /var/lib/postgresql/data`                |
| `-v`                   | 显示详细信息                                                 | `pg_resetwal -v -D /var/lib/postgresql/data`                |

### 1.3.19. `reindexdb`

| 选项                   | 描述                                                         | 示例命令                                                     |
|------------------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `-d DBNAME`            | 指定要重新建立索引的数据库名称                               | `reindexdb -d mydatabase`                                   |
| `-U USER`              | 指定连接数据库的用户名称                                     | `reindexdb -U postgres`                                     |
| `-h HOST`              | 指定数据库服务器的主机地址                                   | `reindexdb -h localhost`                                    |
| `-p PORT`              | 指定端口号                                                    | `reindexdb -p 5432`                                         |
| `-v`                   | 显示详细的进度信息                                           | `reindexdb -v`                                              |
| `-q`                   | 安静模式                                                     | `reindexdb -q`                                              |
| `-f`                   | 强制模式，即使有活动连接也重新建立索引                       | `reindexdb -f -d mydatabase`                                |
| `-s SCHEMA`            | 仅重新建立指定模式下的索引                                   | `reindexdb -s public`                                       |
| `-t TABLE`             | 仅重新建立指定表的索引                                       | `reindexdb -t table_name`                                   |
| `-i INDEX`             | 仅重新建立指定索引                                           | `reindexdb -i index_name`                                   |
| `-a`                   | 重新建立数据库中所有的索引                                   | `reindexdb -a -d mydatabase`                                |

### 1.3.20. `vacuumdb`

| 选项                   | 描述                                                         | 示例命令                                                     |
|------------------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `-d DBNAME`            | 指定要清理的数据库名称                                       | `vacuumdb -d mydatabase`                                    |
| `-U USER`              | 指定连接数据库的用户名称                                     | `vacuumdb -U postgres`                                      |
| `-h HOST`              | 指定数据库服务器的主机地址                                   | `vacuumdb -h localhost`                                     |
| `-p PORT`              | 指定端口号                                                    | `vacuumdb -p 5432`                                          |
| `-v`                   | 显示详细的进度信息                                           | `vacuumdb -v`                                               |
| `-q`                   | 安静模式                                                     | `vacuumdb -q`                                               |
| `-a`                   | 对数据库中的所有表执行 VACUUM 操作                           | `vacuumdb -a -d mydatabase`                                 |
| `-f`                   | 强制模式，即使有活动连接也执行 VACUUM 操作                   | `vacuumdb -f -d mydatabase`                                 |
| `-s SCHEMA`            | 仅对指定模式下的表执行 VACUUM 操作                           | `vacuumdb -s public`                                        |
| `-t TABLE`             | 仅对指定表执行 VACUUM 操作                                   | `vacuumdb -t table_name`                                    |
| `-z`                   | 使用 ANALYZE 更新统计信息                                     | `vacuumdb -z -d mydatabase`                                 |
| `-F`                   | 使用 FULL VACUUM 模式                                        | `vacuumdb -F -d mydatabase`                                 |

### 1.3.21. `vacuumlo`

| 选项                   | 描述                                                         | 示例命令                                                     |
|------------------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `-d DBNAME`            | 指定要清理的大对象的数据库名称                               | `vacuumlo -d mydatabase`                                    |
| `-U USER`              | 指定连接数据库的用户名称                                     | `vacuumlo -U postgres`                                      |
| `-h HOST`              | 指定数据库服务器的主机地址                                   | `vacuumlo -h localhost`                                     |
| `-p PORT`              | 指定端口号                                                    | `vacuumlo -p 5432`                                          |
| `-v`                   | 显示详细的进度信息                                           | `vacuumlo -v`                                               |
| `-q`                   | 安静模式                                                     | `vacuumlo -q`                                               |
| `-a`                   | 对数据库中的所有大对象执行 VACUUM 操作                       | `vacuumlo -a -d mydatabase`                                 |
| `-f`                   | 强制模式，即使有活动连接也执行 VACUUM 操作                   | `vacuumlo -f -d mydatabase`                                 |
| `-l OID`               | 仅对指定大对象OID执行 VACUUM 操作                           | `vacuumlo -l 12345`                                         |

### 1.3.22. `pg_rewind`

| 选项                   | 描述                                                         | 示例命令                                                     |
|------------------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `-D DATADIR`           | 指定PostgreSQL的数据目录                                     | `pg_rewind -D /var/lib/postgresql/data/new`                  |
| `-R REMOTE-DATADIR`    | 指定远程PostgreSQL的数据目录                                 | `pg_rewind -R /var/lib/postgresql/data/old`                  |
| `-P PORT`              | 指定端口号                                                    | `pg_rewind -P 5432`                                          |
| `-U USER`              | 指定连接数据库的用户名称                                     | `pg_rewind -U postgres`                                      |
| `-h HOST`              | 指定数据库服务器的主机地址                                   | `pg_rewind -h localhost`                                     |
| `-v`                   | 显示详细的进度信息                                           | `pg_rewind -v`                                               |
| `-q`                   | 安静模式                                                     | `pg_rewind -q`                                               |
| `-s`                   | 指定同步复制使用的备用端口                                   | `pg_rewind -s 5433`                                          |
| `-c`                   | 检查模式，不执行实际的重放                                   | `pg_rewind -c`                                               |

### 1.3.23. `pg_waldump`

| 选项                   | 描述                                                         | 示例命令                                                     |
|------------------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `-D DATADIR`           | 指定PostgreSQL的数据目录                                     | `pg_waldump -D /var/lib/postgresql/data`                     |
| `-X FILE`              | 解析并转储指定的WAL文件                                      | `pg_waldump -X /var/lib/postgresql/data/pg_xlog/000000010000000000000001` |
| `-v`                   | 显示详细的进度信息                                           | `pg_waldump -v`                                              |
| `-q`                   | 安静模式                                                     | `pg_waldump -q`                                              |

### 1.3.24. `pg_verifybackup`

| 选项                   | 描述                                                         | 示例命令                                                     |
|------------------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `-b BACKUP-DIR`        | 指定备份目录                                                 | `pg_verifybackup -b /var/backups/pg_backup`                  |
| `-D DATADIR`           | 指定PostgreSQL的数据目录                                     | `pg_verifybackup -D /var/lib/postgresql/data`               |
| `-v`                   | 显示详细的进度信息                                           | `pg_verifybackup -v`                                         |
| `-q`                   | 安静模式                                                     | `pg_verifybackup -q`                                         |
| `-l`                   | 显示备份的日志信息                                           | `pg_verifybackup -l`                                         |
| `-t`                   | 测试模式，只验证不恢复                                       | `pg_verifybackup -t`                                         |
| `-r`                   | 恢复模式，验证并恢复备份                                     | `pg_verifybackup -r`                                         |

### 1.3.25. `pg_recvlogical`

| 选项                   | 描述                                                         | 示例命令                                                     |
|------------------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `-D DATADIR`           | 指定PostgreSQL的数据目录                                     | `pg_recvlogical -D /var/lib/postgresql/data`                |
| `-S SLOT_NAME`         | 指定逻辑复制槽名称                                           | `pg_recvlogical -S my_slot`                                 |
| `-h HOST`              | 指定发布者的主机地址                                         | `pg_recvlogical -h publisher_host`                          |
| `-p PORT`              | 指定发布者的端口号                                           | `pg_recvlogical -p 5432`                                    |
| `-U USER`              | 指定连接发布的用户名称                                       | `pg_recvlogical -U replication_user`                        |
| `-W`                   | 交互式请求密码                                              | `pg_recvlogical -W`                                         |
| `-v`                   | 显示详细的进度信息                                           | `pg_recvlogical -v`                                         |
| `-q`                   | 安静模式                                                     | `pg_recvlogical -q`                                         |
| `-s`                   | 启动复制                                                     | `pg_recvlogical -s`                                         |
| `-P`                   | 停止复制                                                     | `pg_recvlogical -P`                                         |
| `-f`                   | 从指定的位置开始复制                                         | `pg_recvlogical -f /path/to/file`                           |
| `-x`                   | 在复制前删除旧的WAL文件                                      | `pg_recvlogical -x`                                         |
| `-d`                   | 指定要复制的数据流类型（例如：`tablespace`、`all`）          | `pg_recvlogical -d all`                                     |

### 1.3.26. `pg_archivecleanup`

| 选项                   | 描述                                                         | 示例命令                                                     |
|------------------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `-D DATADIR`           | 指定PostgreSQL的数据目录                                     | `pg_archivecleanup -D /var/lib/postgresql/data`              |
| `-A ARCHIVE-COMMAND`   | 指定归档命令                                                 | `pg_archivecleanup -A "test ! -f $1"`                        |
| `-v`                   | 显示详细的进度信息                                           | `pg_archivecleanup -v`                                       |
| `-q`                   | 安静模式                                                     | `pg_archivecleanup -q`                                       |
| `-t`                   | 测试模式，仅列出将要执行的操作而不执行它们                    | `pg_archivecleanup -t`                                       |
| `-s START-TIME`        | 指定开始时间                                                 | `pg_archivecleanup -s "2022-01-01 00:00:00"`                 |
| `-e END-TIME`          | 指定结束时间                                                 | `pg_archivecleanup -e "2022-01-31 23:59:59"`                 |
| `-l LOGFILE`           | 指定日志文件                                                 | `pg_archivecleanup -l /var/log/pg_archivecleanup.log`        |

### 1.3.27. `pg_checksums`

| 选项                   | 描述                                                         | 示例命令                                                     |
|------------------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `-D DATADIR`           | 指定PostgreSQL的数据目录                                     | `pg_checksums -D /var/lib/postgresql/data`                   |
| `-v`                   | 显示详细的进度信息                                           | `pg_checksums -v`                                            |
| `-q`                   | 安静模式                                                     | `pg_checksums -q`                                            |
| `-a`                   | 分析模式，计算并验证所有页面的校验和                         | `pg_checksums -a`                                            |
| `-r`                   | 修复模式，为所有块启用校验和                                | `pg_checksums -r`                                            |
| `-c`                   | 检查模式，验证已存在的校验和                                | `pg_checksums -c`                                            |
| `-n`                   | 禁用模式，为所有块禁用校验和                                | `pg_checksums -n`                                            |
| `-l`                   | 列出支持校验和的文件类型                                     | `pg_checksums -l`                                            |

### 1.3.28. `oid2name`

| 选项                   | 描述                                                         | 示例命令                                                     |
|------------------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `-D DATADIR`           | 指定PostgreSQL的数据目录                                     | `oid2name -D /var/lib/postgresql/data`                       |
| `-o OID`               | 指定要转换的对象OID                                          | `oid2name -o 12345`                                          |
| `-n NAME`              | 指定要查找的对象名称                                         | `oid2name -n my_table`                                       |
| `-v`                   | 显示详细的进度信息                                           | `oid2name -v`                                                |
| `-q`                   | 安静模式                                                     | `oid2name -q`                                                |

### 1.3.29. `pg_walsummary`

| 选项                   | 描述                                                         | 示例命令                                                     |
|------------------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `-D DATADIR`           | 指定PostgreSQL的数据目录                                     | `pg_walsummary -D /var/lib/postgresql/data`                  |
| `-v`                   | 显示详细的进度信息                                           | `pg_walsummary -v`                                           |
| `-q`                   | 安静模式                                                     | `pg_walsummary -q`                                           |
| `-s START-TIME`        | 指定开始时间                                                 | `pg_walsummary -s "2022-01-01 00:00:00"`                     |
| `-e END-TIME`          | 指定结束时间                                                 | `pg_walsummary -e "2022-01-31 23:59:59"`                     |
| `-l LOGFILE`           | 指定日志文件                                                 | `pg_walsummary -l /var/log/pg_walsummary.log`                |
| `-w`                   | 显示WAL文件的统计信息                                         | `pg_walsummary -w`                                           |
| `-r`                   | 显示重做统计信息                                             | `pg_walsummary -r`                                           |


# 2. psql命令行

`psql` 是 PostgreSQL 数据库系统的命令行接口工具，用于与 PostgreSQL 数据库进行交互。以下是 `psql` 的一些基本使用说明以及常用命令的概述。

## 2.1. psql 基本用法

### 2.1.1. 连接到数据库
```bash
psql [options] [dbname]
```
- `dbname`: 要连接的数据库名称，默认为用户的登录名。
- `[options]`: 连接数据库的选项，例如 `-h`, `-p`, `-U`, `-d` 等。

## 2.2. 常见选项

| 选项       | 描述                                                         | 示例命令                                                     |
|------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `-h host`  | 指定数据库服务器的主机地址                                   | `psql -h localhost`                                          |
| `-p port`  | 指定端口号                                                    | `psql -p 5432`                                               |
| `-U username` | 指定连接数据库的用户名称                                     | `psql -U postgres`                                           |
| `-d dbname` | 指定数据库名称                                               | `psql -d mydatabase`                                         |
| `-c command` | 执行单条 SQL 命令后退出                                     | `psql -c "SELECT * FROM users;"`                            |
| `-f file`  | 从文件读取 SQL 命令并执行                                   | `psql -f script.sql`                                         |
| `-v VAR=value` | 设置变量                                                     | `psql -v MYVAR=myvalue`                                      |
| `-q`       | 安静模式                                                     | `psql -q`                                                    |
| `-t`       | 只显示查询结果的行                                           | `psql -t`                                                    |
| `-A`       | 输出无标题头、无边框的纯文本格式                             | `psql -A`                                                    |
| `-w`       | 自动宽度模式（自动调整列宽）                                 | `psql -w`                                                    |
| `-E`       | 显示解析器/规划器输出                                         | `psql -E`                                                    |
| `-l`       | 列出所有数据库                                               | `psql -l`                                                    |
| `-L`       | 列出所有数据库，带额外信息                                   | `psql -L`                                                    |
| `-h`       | 显示帮助信息                                                 | `psql -h`                                                    |

## 2.3. psql 内置命令

`psql` 提供了许多内置命令来帮助管理和操作数据库。

### 2.3.1. 连接管理

| 命令       | 描述                                                         | 示例命令                                                     |
|------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `\c [dbname [user]]` | 连接到另一个数据库                                             | `\c mydatabase`                                              |
| `\connect` | 同上                                                         | `\connect mydatabase`                                        |
| `\q`       | 退出 psql                                                     | `\q`                                                         |

### 2.3.2. 数据库列表和选择

| 命令       | 描述                                                         | 示例命令                                                     |
|------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `\l`       | 列出所有数据库                                               | `\l`                                                         |
| `\list`    | 同上                                                         | `\list`                                                      |
| `\d`       | 列出所有表                                                   | `\d`                                                         |
| `\dt`      | 列出所有表                                                   | `\dt`                                                        |
| `\dn`      | 列出所有模式(schema)                                          | `\dn`                                                        |
| `\du`      | 列出所有用户                                                 | `\du`                                                        |
| `\da`      | 列出所有表的访问权限                                         | `\da`                                                        |

### 2.3.3. 查询控制

| 命令       | 描述                                                         | 示例命令                                                     |
|------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `\timing`  | 开启或关闭查询时间记录                                         | `\timing on`                                                 |
| `\echo`    | 控制命令回显                                                 | `\echo on`                                                   |
| `\set`     | 设置会话变量                                                 | `\set VERBOSE on`                                            |
| `\unset`   | 取消设置会话变量                                             | `\unset VERBOSE`                                             |

### 2.3.4. 数据表和索引管理

| 命令       | 描述                                                         | 示例命令                                                     |
|------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `\dt+`     | 列出所有表，并显示附加信息                                   | `\dt+`                                                       |
| `\di`      | 列出所有索引                                                 | `\di`                                                        |
| `\di+`     | 列出所有索引，并显示附加信息                                 | `\di+`                                                       |

### 2.3.5. 其他有用命令

| 命令       | 描述                                                         | 示例命令                                                     |
|------------|--------------------------------------------------------------|--------------------------------------------------------------|
| `\help`    | 查看帮助                                                     | `\help`                                                      |
| `\h [command]` | 显示特定 SQL 命令的帮助                                     | `\h SELECT`                                                  |
| `\password [username]` | 更改用户的密码                                               | `\password`                                                  |
| `\prompt prompt var` | 从用户获取输入值                                             | `\prompt "Enter name" NAME`                                  |
| `\watch`   | 监视模式，自动刷新结果                                       | `\watch`                                                     |
| `\edit`    | 使用默认编辑器编辑 SQL 命令                                 | `\edit`                                                      |
| `\i filename` | 从文件中读取并执行 SQL 命令                                 | `\i script.sql`                                              |
| `\password` | 更改用户的密码                                               | `\password`                                                  |

## 2.4. 示例

- **连接到数据库**:
  ```bash
  psql -h localhost -p 5432 -U postgres -d mydatabase
  ```

- **执行 SQL 命令**:
  ```bash
  psql -c "SELECT * FROM users;"
  ```

- **从文件执行 SQL 命令**:
  ```bash
  psql -f script.sql
  ```

- **列出所有数据库**:
  ```bash
  psql -l
  ```

# 3. SQL命令
