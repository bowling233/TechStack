---
tags:
    - Doing
---

# Linux 基础

## 基础概念

-   用户-程序或服务-系统调用接口-内核-硬件

### 终端

-   Terminal：终端模拟器
    -   Windows Terminal, Fluent Terminal, Hyper ...
-   Shell：命令解释器
    -   bash, zsh, fish ...
    -
-

## 基础命令

### Shell

以下列出了 Shell 中常用的控制字符。

作业：

-   ++ctrl+c++：终结一个前台作业
-   ++ctrl+z++：暂停前台作业
-   ++ctrl+d++：从一个 Shell 中登出
-   ++ctrl+r++：搜索历史命令

编辑：

-   ++ctrl+l++：清除屏幕
-   ++ctrl+u++：删除整行输入
-   ++ctrl+w++：删除光标左侧的所有字符
-   ++ctrl+a++：移动至行首
-   ++ctrl+e++：移动至行末
-   ++ctrl+v++：允许插入控制字符
-   ++ctrl+y++：粘贴之前使用 ++ctrl+u++ 或 ++ctrl+w++ 删除的文字

-   [command] + `&`：后台执行命令

### man

基本操作：

-   `/`：从上至下搜索关键词
-   `?`：从下至上搜索关键词
-   `n`：定位到下一个关键词
-   `N`：定位到上一个关键词

帮助信息结构：

-   NAME
-   SYNOPSIS
-   DESCRIPTION
-   **EXAMPLES**
-   OVERVIEW
-   DEFAULTS
-   **OPTIONS**
-   ENVIRONMENT
-   FILES
-   SEE ALSO
-   HISTORY

### 系统工作

-   `echo`
    -   如何提取变量？
-   `date`
    -   `-s`：设置系统时间
    -   如何写时间格式字符串？`+%...`
    -   格式参数：`%t, %H, %I, %M, %S, %j, %m, %d`
    -   什么是：Unix time？
-   `reboot`
-   `poweroff`
-   `wget [option] URL`
    -   `-b` background
    -   `-P` 指定目录
    -   `-c` continue
    -   `-p` page
    -   `-r` recursive
-   `ps [option]`
    -   `-a`
    -   `-u`
    -   `-x`
    -   [[Linux进程]]
    -   几个信息：`TTY, STAT`
-   `top`
-   `pidof [option] [name]`
-   `kill [option] [PID]`
-   `killall [option] [name]`

### 系统状态

-   `ifconfig [webdevice] [option]`: configure a network interface
    -   该命令从属于 `net-tools` 包，一般不会默认安装
    -   你知道这些信息在哪吗？网卡名称、IP 地址、MAC 地址
-   `uname [-a]`: print system information
-   `uptime`: tell how long the system has been running
    -   平均负载值是什么？它的数值最好控制在什么范围？
-   `free [-h]`: display amount of free and used memory in the system
-   `who`: show who is logged on
-   `last [option]`: show a listing of last logged in users
    -   注意，这些信息可能被修改，不应当轻信
-   `history [clear]`
    -   如何用 `!` 重复执行某一次命令？
-   `sos report`
    -   `sosreport` 命令现在以及替换为 `sos` 命令

### 工作目录命令

-   `pwd`
-   `cd`
-   `ls`

### 文本文件命令

-   `cat [option] [file]`
    -   `-n`
-   `more [option] [file]`
    -   如何向下翻页？
-   `head [option] [file]`
    -   `-n [num]`
-   `tail [option] [file]`
    -   `-f`
-   `tr [origin] [suppliment]`: translate or delete

    -   `tr [a-z] [A-Z]`
    -

-   `wc [option] [text]`: word count

    -   `-l, -w, -c`

-   `stat [file]`
-   `cut [option] [text]`

    -   `-d <sign>`
    -   `-f <num>`
    -   `cut` 提取文本的方式是怎样的？解释 `cut -d: -f1 file`

-   `diff [option] [file]`
    -   `-q, --brief`
    -   `-c`

### 文件目录命令

-   `touch [option] [file]`
    -   `-a, -m, -d`
    -   atime, mtime, ctime 是什么？
-   `mkdir [option] [directory]`
    -   `-p`
-   `cp [option] [origin] [dest]`
    -   `-p, -r, -i, -a`
-   `mv [option] [origin] [dest]`
-   `rm [option] [file]`
    -   `-f, -r`
-   `dd [option]`

    -   `if`
    -   `of`
    -   `bs`
    -   `count`
    -   例子：`dd if=/dev/zero of=560_file count=1 bs=560M`
    -   dd 的功能非常强大，比如它甚至可以压制光盘镜像：`dd if=/dev/cdrom of=xxx.iso`

-   `file [file]`

### 打包压缩与搜索

-   `tar [option] [file]`
    -   `.tar`, `.tar.gz`, `.tar.bz2`
    -   `-c, -x, -t, -z, -j, -v, -f, -p, -P, -C`
    -   `-czvf, -xzvf`
-   `grep [option] [file]`
    -   `-b, -c, -i, -n, -v`
-   `find [path] condition operation`
    -   例：`find /etc -name "host*" -print`
    -   `-exec {command} \;`

## 不同的 Linux 发行版

### Debian

> 参考教程：
>
> [](https://blog.ddupan.top/Chinaskills-Debian/)
>
> [Debian 管理员手册](https://www.debian.org/doc/manuals/debian-handbook/)

-   软件包管理
    -   二进制软件包 `deb`
    -   包管理程序 `dpkg`
    -   软件仓库 `apt`
-   系统信息
    -   `/etc/debian_version`
    -   SELinux：支持但不默认安装

#### `deb` 软件包

-   `deb` 是什么？
    -   一个简单的打包，可以被 `tar` 等处理
    -   `deb` 有什么？
-   如何查看软件包的**元信息**？
-   `dpkg` 是什么？
    -   一个包管理工具，面向管理员
    -   如何使用 `dpkg` 安装、卸载软件包？
    -   如何用 `dpkg` 查询 `deb` 信息？本机信息？
-   `apt` 是什么？
    -   `sources.list` 的语法格式是？
