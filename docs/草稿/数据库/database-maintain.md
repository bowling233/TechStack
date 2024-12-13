# 数据库：配置与维护

## MySQL

!!! quote

    - [初次安装密码](https://dev.mysql.com/doc/refman/8.0/en/data-directory-initialization.html#data-directory-initialization-password-assignment)
    - [MySQL 8.0 Reference Manual  /  MySQL Server Administration](https://dev.mysql.com/doc/refman/8.0/en/server-administration.html)
    - [配置文件语法](https://dev.mysql.com/doc/refman/8.0/en/option-files.html#:~:text=the%20command%20line.-,Option%20File%20Syntax,-The%20following%20description)
    - [Systemd 管理 MySQL](https://dev.mysql.com/doc/refman/8.0/en/using-systemd.html)

| program | description |
| --- | --- |
| `mysql` | command-line client |
| `mysqld` | server daemon |
| `mysqladmin` | server administration |
| `mysqldump` | backup and restore |

### 安装

- 安装后首先查看配置文件如 `/etc/mysql`，了解如何访问、日志位置。如果之后的过程中 `mysqld` 没有期望的输出，一般是放到日志去了。
- 初始化：可选择要不要生成随机密码，密码会在日志中。使用 Docker 部署时也会在日志中生成随机密码。

```bash
mysqld --initialize
mysql -u root -p

mysqld --initialize-insecure
mysql -u root --skip-password

ALTER USER 'root'@'localhost' IDENTIFIED BY 'root-password';
```

- 修改配置文件后检查：

```bash
mysqld --defaults-file=./my.cnf-test --validate-config
```

- `root` 默认认证方式似乎是 `auth_plugin` 而不是密码，初次安装后一般都连接不上。可以使用 `sudo mysql` 进入（这不需要密码），然后执行下面的命令修改密码为 `root`：

```mysql
ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'root';
```

### 使用

- 连接命令：`mysql`
    - `-u root` 指定用户
    - `-p` 要求密码
    - `--socket /var/run/mysqld/mysqld.sock` 可能找不到默认的 socket 文件，此时需要查询 `journalctl mysql` 找到
- 使用 MySQL WorkBench 提供 GUI 操作界面

### 维护

- 基本维护命令：

```sql
SHOW DATABASES; TABLES; STATUS;
SHOW CREATE DATABASE some_db; TABLE some_table;
SHOW GRANTS; ERORRS; WARNINGS;
DESCRIBE some_table; SHOW COLUMNS FROM some_table;
USE some_db;
HELP some_command;
```

- 注释：`--` 开头
- 如果只需查看某个信息但它太长了，可以使用 `\G` 结尾，这样会以列的形式显示。比如查看 `SHOW CREATE TABLE some_table\G`：

```text
mysql> show create table orders \G
*************************** 1. row ***************************
       Table: orders
Create Table: CREATE TABLE `orders` (
  `order_num` int NOT NULL AUTO_INCREMENT,
  `order_date` datetime NOT NULL,
  `cust_id` int NOT NULL,
  PRIMARY KEY (`order_num`),
  KEY `fk_orders_customers` (`cust_id`),
  CONSTRAINT `fk_orders_customers` FOREIGN KEY (`cust_id`) REFERENCES `customers` (`cust_id`)
) ENGINE=InnoDB AUTO_INCREMENT=20010 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci
1 row in set (0.00 sec)
```

## PostgreSQL

!!! quote

    - [PostgreSQL: Downloads](https://www.postgresql.org/download/)

### Docker 安装和使用

```yaml
# Use postgres/example user/password credentials
services:

  db:
    image: postgres
    restart: always
    # set shared memory limit when using docker-compose
    shm_size: 128mb
    environment:
      POSTGRES_PASSWORD: example

  adminer:
    image: adminer
    restart: always
    ports:
      - 8080:8080
```

```bash
```


