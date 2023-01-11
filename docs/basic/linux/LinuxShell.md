---
tags:
  - Ongoing

---

# Linux Shell

Linux 拥有许多命令解释器，如 `bash`、`zsh` 和 `fish`。它们有许多共同的特性，因此就合并在一个文档中介绍。

## Shell

本节介绍关于 Shell 的通用知识。

### Shell 是命令解释器和编程语言

- 作为命令解释器（command interpreter），Shell 对用户输入的命令进行解释，调用相应的程序。Shell 建立了用户和操作系统之间的接口。
- 作为编程语言，Shell 命令可以安排在一个文件中供以后执行，称为 Shell 脚本。

### Shell 特性

- 通配符：这是一些对 Shell 具有特殊意义的字符，用于构造模式。
- 设备无关I/O：输入输出可以被重定向，并且可以重定向到任何合适的设备。
- 函数：可以编写函数，Shell 将它们放在内存中。Shell 还用内部方式存储函数，这样不必耗费大量时间解释命令。
- 作业控制：允许用户同时运行多个作业，进行前后台切换。

### 术语表

| English | Chinese |
| - | - |
| terminal | 终端 |
| terminal emulator | 终端模拟器 |
| textual virtual console | 文本界面虚拟控制台 |
| CLI (Command Line Interface) | 命令行界面 |
| pseudograhpical interface | 伪图形界面 |

### 错误纠正

使用 `stty` 可以查看当前终端的键位设置。

- 擦除字符：++backspace++，++delete++，++ctrl+h++。
- 删除单词：++ctrl+w++
- 删除一行：++ctrl+u++，++ctrl+x++
- 终止执行：
  - 发送中断信号（terminal interrupt signal）：++ctrl+c++，++delete++ 
  - 挂起程序：ctrl+z++
  -

```bash
command [arg1] [arg2] [arg3] ...
```

- `[]` 表示参数是可选的。
- `-`(hyphen) 开头的参数被称为 options 或 flags。这些选项也可以有自己的参数，并且不是可选的。
  - 选项通常使用空格与其参数分开，比如 `gcc -o prog prog.c`。
  - 也有使用等号的，比如 `diff --width=60 filea fileb`。

参数的具体使用方法受程序影响，使用 `--help` 一般能获得程序参数的使用介绍。

以下是一些常用选项：

| Name | Mean |
| - | - |
| `-h` | display `--human-readable` file sizes |



## bash

几乎所有 Linux 发行版自带的 Shell 都是 `bash`，多数脚本也都基于 `bash` 运行。因此一定要熟练掌握 `bash` 的使用。

### 重定向

重定向用于将文件导入到命令、将输出写入到文件。

-   输入重定向

| 符号      | 作用                           |
| --------- | ------------------------------ |
| <         | 将文件作为命令的标准输入       |
| << 分界符 | 从标准输入读入，直到遇到分界符 |

-   输出重定向

| 符号         | 作用                                     |
| ------------ | ---------------------------------------- |
| >            | 将标准输出重定向到文件（清空文件内容）   |
| 2>           | 将错误输出重定向到文件（清空文件内容）   |
| >>           | 将标准输出重定向到文件（追加）           |
| 2>>          |                                          |
| >> 文件 2>&1 | 将标准输出和错误输出重定向到文件（追加） |
| &>>          | 同上                                     |

### 管道

管道命令符 `|` 的作用是将前一个命令的输出作为后一个命令的输入

### 通配符

| 符号 | 作用                       |
| ---- | -------------------------- |
| `*`  | 匹配零个或多个字符         |
| `?`  | 匹配单个字符               |
| `[]` | 匹配中括号内的任意一个字符 |
|      | 匹配任意一个数字           |
| `{}` | 创建文件时使用，           |

中括号相关：

| 符号          | 作用       |
| ------------- | ---------- |
| `[A-Z]`       |            |
| `[a-Z]`       |            |
| `[0-9]`       |            |
| `[[:alpha:]]` |            |
| `[[:alnum:]]` | 字母和数字 |
| `[[:punct:]]` | 标点符号   |

### 转义字符

| 符号    | 作用                           |
| ------- | ------------------------------ |
| `\`     | 使后面的一个字符变为单纯的字符 |
| `''`    | 纯字符串                       |
| `""`    | 替换变量                       |
| `` ` `` | 执行其中的命令，用返回值替换   |

### 别名

使用 `alias 别名=命令` 创建别名，用 `unalias` 取消别名。

### 内部命令

使用 `type [commandName]` 来判断一个命令是否是内部命令。

### 环境变量

Linux 中，变量名称一般都是大写的。

<!-- prettier-ignore-start -->
!!! tip "为什么不将当前目录添加到 `$PATH` 中呢？"
    
    如果黑客在常用目录中放置了与常用命令同名的木马文件，这就麻烦了。

    一名态度谨慎、有经验的运维人员，接手一台 Linux 系统后在执行命令前会先检查 `PATH` 变量是否有可疑目录。
<!-- prettier-ignore-end -->

使用 `env` 命令查看系统中所有环境变量。

下表列出了重要的环境变量。

| Name         | Function                                   |
| ------------ | ------------------------------------------ |
| HOME         | home directory of the user                 |
| SHELL        | name of current using shell                |
| HISTSIZE     | number of lines of the output of `history` |
| HISTFILESIZE | number of saved history commands           |
| MAIL         | where mails are saved                      |
| LANG         | system language name                       |
| RANDOM       | generate a random number                   |
| PS1          | Bash 提示符                                |
| PATH         |                                            |
| EDITOR       | user default text editor                   |

环境变量会因为用户身份和 shell 的不同而具有不同的值。使用 `export` 命令可以将一个变量提升为全局变量。

## 编写 Shell 脚本

### 基本结构

- 脚本声明（`#!`）
- 注释（`#` 开头）
- 命令

### 一些变量

| Name | Content |
|- | - |
| `$0` | Name of the script |
| `${num}` | Arguments |
| `$*` | All arguments |
| `$?` | Return value of the last command |
| `$#` | Number of arguments |

### 测试语句

```
[ expression ]
```

注意条件表达式两侧必须有一个空格。

表达式执行后，结果储存在 `$?` 中。

- 逻辑运算符

| Name | Function |
| - | - |
| `&&` | the 

- 文件测试


| Name | Function |
| - | - |
| -d | Is a directory |
| -e | Exist |
| -f | Is file |
| -r | Has the right to read |
| -w | Has the right to write |
| -x | Has the right to execute |



