# 数据库：系统概念

## 关系型数据库

!!! abstract "知识结构"

    主要依据的书籍为：

    - MySQL Crash Course 入门
    - MySQL Cookbook 深入理解

    可以按两种方式梳理 MySQL 的知识：

    - 语句
    - 对象

    需要掌握的语句：

    ```text
    SHOW, CREATE, SELECT, ...
    ```

    需要掌握的对象：

    - 数据库
    - 表
    - 函数
    - 视图
    - 存储过程
    - 游标
    - 事务

### 数据类型

==todo==

### 语句

- `CREATE`：知道数据库、表、视图、索引、过程、用户怎么创建

    ```mysql
    # 数据库
    CREATE DATABASE databasename;
    # 表
    CREATE TABLE tablename
    (
        column datatype [NULL|NOT NULL] [CONSTRAINTS],
        #...
    );
    # 视图
    CREATE [OR REPLACE] VIEW viewname
    AS
    SELECT 
    #...
    ;
    # 索引
    CREATE INDEX indexname
    ON tablename (column [ASC|DESC], ...);
    # 过程
    CREATE PROCEDURE procedurename( [parameters] )
    BEGIN
    #...
    END;
    # 用户
    CREATE USER username[@hostname]
    [IDENTIFIED BY [PASSWORD] 'password'];
    ```

- `SELECT`：

    ```mysql
    SELECT columnname [AS name], ...
    FROM tablename, ...
    [WHERE
    GROUP BY 
    HAVING 
    ORDER BY columnname [ASC|DESC]
    LIMIT start OFFSET offset];
    ```

    - 变种：
        - `SELECT DISTINCT` 应用于所有选择的列
        - `SELECT Concat(a, 'b', ...)` 拼接字段，可以结合 `RTrim()` 等函数
    - `ORDER BY`
        - 可以使用非检索列
    - `WHERE`
        - 操作符 `= <> != < <= > >=` `BETWEEN AND` `IS NULL` `IN (val1, val2, ...)`
        - 组合子句：`AND OR`，最好使用圆括号
        - 取反：`NOT` 可用于 `IN`、`BETWEEN`、`EXISTS` 子句
        - `LIKE` 匹配整个列（完全匹配）
            - 通配符：`%` 任意字符任意次数，但不匹配 `NULL`；`_` 单个字符。
        - `REGEXP` 在列值内进行匹配（部分匹配）
            - `.` 任意单字符
            - `a|b` 其中之一
            - `[abC]` 其中一个字符，`[^abC]` 否定，`[a-z]` 范围，`[:alnum:]` 字符类
            - `\\` 前导匹配特殊字符和元字符，如 `\\n`，自身为 `\\\`

                !!! question "为什么是两个斜杠"

                    MySQL 自己解释一个，正则表达式库解释另一个。

            - 重复元字符：`*` 0 或多个，`+` 1 或多个，`?` 0 或 1，`{n}` 指定数目，`{n,m}` 指定范围。用例：`[[:digit:]]{4}`
            - 定位符：`^` 开始，`$` 结尾，`[[:<:]] [[:<:]]` 词开始结尾

        !!! note "`NULL` 的比较"

            MySQL 使用三值逻辑 —— TRUE, FALSE 和 UNKNOWN。任何与 NULL 值进行的比较都会与第三种值 UNKNOWN 做比较。这个“任何值”包括 NULL 本身！也就是说：`NULL = NULL` 是错的。
            
            应当使用 IS NULL 和 IS NOT NULL 两种操作来对 NULL 特殊判断。

- `ALTER TABLE tablename` 仅列出部分常用：
  
    ```mysql
    ALTER TABLE tbl_name
      [alter_option [, alter_option] ...]
      [partition_options];
    alter_option: {
        table_options
      | ADD [COLUMN] col_name column_definition
            [FIRST | AFTER col_name]
      | DROP {CHECK | CONSTRAINT} symbol
      | ALTER {CHECK | CONSTRAINT} symbol [NOT] ENFORCED
      | CHANGE [COLUMN] old_col_name new_col_name column_definition
            [FIRST | AFTER col_name]
      | DROP [COLUMN] col_name
      | DROP {INDEX | KEY} index_name
      | DROP PRIMARY KEY
      | DROP FOREIGN KEY fk_symbol
      | LOCK [=] {DEFAULT | NONE | SHARED | EXCLUSIVE}
      | MODIFY [COLUMN] col_name column_definition
            [FIRST | AFTER col_name]
      | ORDER BY col_name [, col_name] ...
      | RENAME COLUMN old_col_name TO new_col_name
      | RENAME {INDEX | KEY} old_index_name TO new_index_name
      | RENAME [TO | AS] new_tbl_name
    }
    table_option: {
        AUTOEXTEND_SIZE [=] value
      | AUTO_INCREMENT [=] value
      | AVG_ROW_LENGTH [=] value
      | ENGINE [=] engine_name
      | ENGINE_ATTRIBUTE [=] 'string'
      | INSERT_METHOD [=] { NO | FIRST | LAST }
      | UNION [=] (tbl_name[,tbl_name]...)
    }
    ```

### 视图

视图是虚拟的表，使用时动态检索数据，本质上是一个包装的查询，可以用与表基本相同的方式利用。

视图的常用场景：

- 存储一个基础的查询，多次使用
- 结合计算字段，对数据进行格式化
- 过滤不想要的数据

使用方法：

- 可以嵌套
- 不能索引
- 可以和表一起使用，比如和表联结
- 可以 `ORDER BY`

具体操作：

```sql
CREATE VIEW view_name AS;
SHOW CREATE VIEW view_name;
CREATE OR REPLACE VIEW view_name AS;
```

更新视图：视图的更新是对基础表的更新。只要出现了分组、联结、子查询、并等操作，就不能更新视图。大部分视图都是不能更新的。

### 函数

```sql
Concat()
# 文本
Left, Right; Length; Locate, SubString; Lower, Upper; LTrim, Trim, RTrim; Soundex
# 日期
Date, Time, Year, Month, Day, Hour, Minute, Second; Now, CurDate, CurTime; AddDate, AddTime; DateDiff; Date_Add, Date_Format; DayOfWeek
# 数值
Abs, Cos, Exp, Mod, Pi, Rand, Sin, Sqrt, Tan
```

!!! note "日期"

    如果要的是日期，请使用Date() 比如，存储的order_date 值为2005-09-01 11:30:05，则WHERE order_date = '2005-09-01'失败。

!!! note "字符"

    建议使用 `CHAR_LENGTH` 而不是 `LENGTH`，因为 `LENGTH` 对特殊字符可能返回意想不到的结果。比如对于 `¥`，前者返回 1，后者返回 2。

### 触发器

触发器是一些语句，在事件发生时自动执行。MySQL 触发器能够相应 `DELETE`、`INSERT`、`UPDATE` 事件。

```sql
CREATE TRIGGER trigger_name
BEFORE|AFTER DELETE|INSERT|UPDATE
ON table_name
FOR EACH ROW
BEGIN
    -- ...
END;
```

- 对于每个表每个事件只允许一个触发器，因此每个表最多有 6 个触发器。
- 如果 `BEFORE` 触发器失败，操作不执行；如果操作失败，`AFTER` 触发器不执行。

### 联结

很多子查询都可以使用联结完成。

自联结很简单，用别名理解即可。

#### 内部联结 `INNER JOIN`

内部联结得到笛卡尔积。传递给 `ON` 的条件和直接使用 `WHERE` 建立联结相同：

```mysql
SELECT * FROM a, b WHERE a.a = b.a;
SELECT * FROM a INNER JOIN b ON a.a=b.a;
```

用于联结的列会重复出现。手动指定需要的列就是所谓的“自然联结”。

#### 外部联结 `LEFT|RIGHT OUTER JOIN`

需要包含没有关联行的那些行时，使用外部联结。`LEFT|RIGHT` 指定从哪一侧的表格选择所有行。

```mysql
SELECT * FROM a LEFT OUTER JOIN b ON a.a=b.a;
```

#### 交叉联结 `CROSS JOIN`

### 约束

#### 外键

##### `ON` 子句

可以在外键被 `UPDATE` 或 `DELETE` 时指定操作：

- `RESTRICT` 默认，拒绝操作
- `CASCADE` 级联操作，删除或更新主表的行时，从表的行也会被删除或更新
- `SET NULL` 从表的外键列被设置为 `NULL`

#### `INSERT`

- `NEW` 关键字引用新插入的行
- `AUTO_INCREMENT` 在 `INSERT` 执行后才生成值

建议：

- `BEFORE` 用于数据验证和净化
- `AFTER` 用于日志记录和数据审计

#### `DELETE`

- `OLD` 关键字引用被删除的行，全只读

#### `UPDATE`

- `OLD` 关键字引用被更新的行，全只读
- `NEW` 关键字引用新插入的行

### 事务

#### 使用

事务处理（transaction processing）用于维护数据库完整性，确保一批操作要么全部执行，要么全部不执行。

三个术语：Rollback、Commit、Savepoint

!!! warning "无法回退 `CREATE` 或 `DROP`"

!!! warning "`DROP DATABASE` 等语句无法作为事务的一部分"

执行一条 `ROLLBACK` 或 `COMMIT` 意味着事务结束。

```mysql
# Example1 回退
SELECT * FROM table;
START TRANSACTION;
DELETE FROM table;
SELECT * FROM table;
ROLLBACK;
SELECT * FROM table;

# Example2 多表一致性
START TRANSACTION;
DELETE FROM table1 WHERE id=1;
DELETE FROM table2 WHERE id=1;
COMMIT;

# Example3 保存点
START TRANSACTION;
DELETE FROM table1 WHERE id=1;
SAVEPOINT delete1;
DELETE FROM table2 WHERE id=1;
ROLLBACK TO delete1;
COMMIT;
```

#### 锁

### 安全

#### 用户

```mysql
USE mysql;
SELECT user, host FROM user;
CREATE USER 'username'@'hostname' IDENTIFIED BY 'password';
RENAME USER 'oldname' TO 'newname';
DROP USER 'username'@'hostname';
SHOW GRANTS FOR 'username'@'hostname';
GRANT SELECT, INSERT, UPDATE, DELETE ON databasename.tablename TO 'username'@'hostname';
REVOKE SELECT, INSERT, UPDATE, DELETE ON databasename.tablename FROM 'username'@'hostname';
SET PASSWORD FOR 'username'@'hostname' = PASSWORD('newpassword');
```

### 聚合与分组

```sql
AVG, COUNT, MAX, MIN, SUM
```

- 可为这些函数指定DISTINCT
- 如果在GROUP BY子句中嵌套了分组，数据将在最后规定的分组上进行汇总。
- 除聚集计算语句外，SELECT语句中的每个列都必须在GROUP BY子句中给出。

> 🤔这一点是合理的，因为如果有某一列被选择，却不对它进行分组，那它的值要怎么显示？

#### 组合查询

- 多个SELECT语句之间使用UNION合成一个结果返回
- 显然，每个查询的列、表达式等必须相同、兼容
- 会自动去除重复行，使用UNION ALL保留。WHERE无法实现这种。
- UNION组合只能使用一条ORDER BY，出现在最后的SELECT之后。

#### 全文本搜索

- 原理是为指定列中的词创建索引，搜索针对这些词进行。快速决定匹配和频率等。
- 只有 MyISAM 引擎支持，而 InnoDB 不支持
- 创建表时使用 `FULLTEXT` 子句

    ```sql
    CREATE TABLE a
    (
        FULLTEXT(a_column)
    ) ENGINE=MyISAM;
    ```

- 用 `Match()` 和 `Against()` 执行全文本搜索

    ```sql
    WHERE Match(note_text) Against('rabbit');
    ```

    - 这一表达式给出全文本搜索的 rank
- 查询扩展 `WITH QUERY EXPANSION`
- 布尔文本搜索 `IN BOOLEAM MODE`，全文本布尔操作符查表
- 此外有一些使用上的说明，比如出现频率过高的词自动忽略、短词自动忽略、中日文等无词分隔符的语言无法搜索等

### 数据修改

插入：

```sql
INSERT INTO table() VALUE (), (), ...;
```

- 除了 `VALUE`，`SELECT` 的结果也可以插入，且 SQL 不关心返回的列名，只关心位置，这样可以从不同表中导入数据

更新：

```sql
UPDATE table
SET col=newval, col=newval, ...
WHERE condition;
```

- 可以使用子查询
- 若发生错误则该更新的**全部操作**被取消，`UPDATE IGNORE` 忽略错误

删除：

```sql
DELETE table
WHERE condition;

TRUNCATE TABLE;
```

!!! warning "SQL 没有撤销按钮"

### 表操作

`CREATE TABLE`

- `PRIMARY KEY ()` 关键字指定主键，可以是多个列
- `AUTO_INCREMENT` 自动增量
    - 在 `INSERT` 时仍然可以指定值，且后续增量将基于该值
    - `SELECT last_insert_id();` 获得最后一个 `AUTO_INCREMENT` 值
- `NOT NULL` 不允许空值
- `DEFAULT value` 默认值，只能是常量
- `ENGINE=` 指定引擎
    - 外键不能跨引擎
    - 如果需要事务处理，使用 InnoDB
    - 其余情况都可以用 MyISAM
    - MEMORY 引擎：临时表，存放于内存

`DROP TABLE`

`RENAME TABLE a TO b, c TO d, ...;`

### 存储过程

```mysql
CREATE PROCEDURE proc_name(
    OUT p1 INT,
    OUT p2 DECIMAL(5,2)
)
BEGIN
    -- ...
    SELECT *
    INTO p1
    FROM table;
END;

CALL proc_name(@p1, @p2);
SELECT @p1, @p2;
SHOW PROCEDURE STATUS LIKE 'proc_name';
```

存储过程的重点在于业务规则和智能处理。

```mysql
CREATE PROCEDURE proc_name(
) COMMENT 'some comment'
BEGIN

    DECLARE var_name INT;
    DECLARE CONTINUE HANDLER FOR SQLEXCEPTION
    BEGIN
        ROLLBACK;
    END;

    START TRANSACTION;
    -- ...
    COMMIT;

    IF condition THEN
        -- ...
    ELSEIF condition THEN
        -- ...
    ELSE
        -- ...
    END IF;
END;
```

### 游标

游标是一个指向结果集的指针，可以用于遍历结果集。使用流程：

- 声明游标
- 打开游标（真正执行查询）
- 检索数据
- 关闭游标

```mysql
DECLARE cur_name CURSOR FOR SELECT * FROM table;
OPEN cur_name;
FETCH cur_name INTO var1, var2;
DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = 1;
REPEAT
    FETCH cur_name INTO var1, var2;
UNTIL done END REPEAT;
```

