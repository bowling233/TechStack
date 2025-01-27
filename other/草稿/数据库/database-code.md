# 数据库：编程

## Java JDBC

### 基础

SQL 程序设计应当关注 API 的以下几点：

- 连接到服务器，选择数据库，断开连接

两步，分别指定 driver、初始化连接并获得 `Connection` 对象。

```java
Class.forName();
DriverManager.getConnection();
```

- 检查错误

发生错误时，MySQL 提供三个值：错误码、描述性信息、五个字符的 SQLSTATE（ANSI ODBC 标准）。

Java 的异常处理是通过捕获异常实现的，最基本地会打印 `printStackTrace()` 指明错误的地方。

`Exception` 对象具有 `getMessage()` 方法。JDBC 方法常抛出 `SQLException` 对象，支持 `getErrorCode()` 和 `getSQLState()` 方法。某些方法产生 `SQLWarning` 对象，积累在一个列表中不会立即抛出，可以闲时打印。

```java
try{

}
catch (Exception e)
{
    e.printStackTrace();
    catch (Exception e)
    {
      System.err.println ("Cannot connect to server");
      System.err.println (e);
      if (e instanceof SQLException)
      {
        printException ((SQLException) e);
      }
    }
}
public static void printException (SQLException e)
{
    System.err.println ("SQLException: " + e.getMessage ());
    System.err.println ("SQLState: " + e.getSQLState ());
    System.err.println ("Vendor code: " + e.getErrorCode ());
}
```

- 执行 SQL 语句，获得结果

SQL 语句分为两类，JDBC 使用不同的调用执行它们。一类返回影响的行数 `int`，使用 `executeUpdate()`，一类返回结果集 `ResultSet`，使用 `executeQuery()`。使用后记得关闭语句和结果集。

结果集一开始指向第一行的前一行，使用 `next()` 方法直到返回假。`getXXX()` 接受列指标或列名。也可以直接获取泛型的 `getObject()`，后续再转换。

结果集元数据 `ResultSetMetaData` 类型通过 `.getMetaData` 获取，再使用 `.getColumnCount()` 获得列数。

```java
Statement s = conn.createStatment();
int count = s.executeUpdate();
s.close();
Statement s = conn.createStatment();
s.executeQuery();
ResultSet rs = s.getResultSet();
ResultSetMetaData md = rs.getMetaData();
int ncols = md.getColumnCount();
int count = 0;
while(rs.next())
{
    int id = rs.getInt(1); // column1
    String name = rs.getString(2); // column2
    //...
    ++count;
}
rs.close();
s.close();
```

- **处理语句中的特殊字符和 NULL 值**（安全问题）
- 辨别结果中的空值

## Go 