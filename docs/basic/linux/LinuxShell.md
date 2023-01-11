---
tags:
  - Ongoing

---

# Linux Shell

Linux 拥有许多命令解释器，如 `bash`、`zsh` 和 `fish`。它们有许多共同的特性，因此就合并在一个文档中介绍。这里同样介绍终端、控制台等与文本界面有关的内容。

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

## 文本界面


### 历史

参考资料：

- [控制台、终端和 Shell 的关系](https://www.eet-china.com/mp/a46011.html)。
- [Unix 终端系统（TTY）是如何工作的？](https://waynerv.com/posts/how-tty-system-works/)
- [TTY: under the hood](https://www.yabage.me/2016/07/08/tty-under-the-hood/)

1970 年以前，K&R 开发 UNIX 系统，他们打算让该系统支持多用户，于是使用了电传打字机（teletype，简称 tty）做终端设备。

终端是通过线缆连接在主机上的，主机上还有一个直接集成的特殊终端，称为**控制台**。控制台只能被管理员使用，可以做一些普通终端不能做的事情。比如，打印系统启动失败的信息。

上面这些都是历史了。在现在的 Linux 中已经淡化了控制台和终端的区别，我们都是通过虚拟控制台与计算机交互。

### 术语表

| English | Chinese | Explanation |
| - | - | - |
| terminal | 终端 | 处理计算机输入输出的一套设备 |
| console | 控制台 | 显示系统消息的终端就是控制台，Linux 默认所有虚拟终端都是控制台 |
| terminal emulator | 终端模拟器 | 图形界面中用于呈现命令行界面的窗口，打开它就能和 Shell 交互 |
| textual virtual console | 文本界面虚拟控制台 | |
| CLI (Command Line Interface) | 命令行界面 | |
| pseudograhpical interface | 伪图形界面 | |
| prompt | 提示符 | | 

### 终端

- 本地终端：显示器+键盘就是本地终端。
- 串口终端：通过串口将主机连接到另外一个具有显示器和键盘的主机，通过终端模拟程序将这台主机的显示器和键盘借给串口对端的主机，这就是串口终端。
- 远程终端：由 TCP/IP 承载，如 telnet 和 ssh。这是伪终端，因为它们没有关联任何物理设备。

### 登录

使用文本设备登录前，系统显示一条 issue 消息（存放在 `/etc/issue`），说明系统版本。

随后是登录提示符，登录成功后显示 shell 提示符。shell 提示符前可能有一条简短的“当日消息（the message of the day）”，存放在 `/etc/motd`。

### 虚拟控制台

旧的系统包含多个物理控制台设备，现在一个主机模拟了多个控制台，称为虚拟控制台。Linux 系统默认情况下有 6 个虚拟控制台处于活动状态，它们是 `/dev/tty1-6`，而 `/dev/tty0` 是当前虚拟控制台的别名。在 X 窗口系统下，使用 ++ctrl+alt+f1++ 可以切换到对应的控制台，`tty1` 和 `tty2` 都是 X 窗口系统，其余是虚拟字符终端。

### 系统控制台

`/dev/console`，用于接收系统消息。系统消息不会发送到 `tty`，而是发送给 `console`。

## 终端操作

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



