---
tags:
    - Doing
---

# Linux 基础

这里包含了以下知识：系统内核、终端、解释器等概念简介，Shell 的简单使用，一些基础命令。

## 基础概念

-   内核与系统

Linux **内核**是由 Linux Torvalds 维护，提供硬件抽象层、硬盘和文件系统控制及多任务功能的系统核心程序。

Linux **发行套件系统**是我们常说的 Linux 操作系统，是 Linux 内核与各种常用软件的集合产品。

我们一般不会直接编辑内核，而是通过基于系统调用接口开发出的程序或服务管理计算机。

-   各种 Linux 发行版

这里列出一些发行版的第三方中文指南，它们往往比官方文档容易入门。

[Debian 系 Linux 快速入门与参考](https://blog.ddupan.top/Chinaskills-Debian/)

[ArchLinux 指南](https://arch.icekylin.online/)

RedHat/CentOS/Fedora：《Linux 就该这么学》

-   软件

在**包管理器**（如 `dpkg`）诞生之前，软件采用源码包的方式安装，很多服务程序仅提供源代码，需要自行编译并解决超多**依赖关系**。包管理器建立了统一的数据库文件，记录软件的详细信息并自动分析依赖关系，但问题还是需要运维人员自行解决。

**软件仓库**（如 `apt`）根据用户需求分析软件包及依赖关系，自动从服务器下载软件包。

| 项目         | `Debian` | `Red Hat`                                   |
| :----------- | :------- | :------------------------------------------ |
| 二进制软件包 | `deb`    | `rpm`                                       |
| 包管理程序   | `dpkg`   | `rpm`                                       |
| 软件仓库     | `apt`    | `yum` ( RHEL 7 之前 ) `dnf` ( RHEL 8 之后 ) |

-   初始化进程

一台电脑开机需要经过：BIOS - Boot Loader - 加载系统内核 - 内核初始化 - 启动**初始化进程** 这样一系列操作。

初始化进程是 Linux 系统第一个进程，为用户提供合适的工作环境。初始化工作包括：挂载文件系统和交换分区、启动各类服务进程等。这些被称作单元（Unit）。

当前主流的初始化进程服务是 `systemd`，广泛应用于 `Debian`、`RedHat` 和 `Arch`。使用 `systemctl` 管理服务。

## 基础使用

### Shell

Shell 称为**命令解释器**。命令的一般格式是：`命令名称 [命令参数] [命令对象]`，注意对象一般在最后。命令参数有长格式和短格式两种，分别以 `--` 和 `-` 作为前缀。

<!-- prettier-ignore-start -->
!!! note "终端常用的控制字符"
    
    作业：
    
    -   ++ctrl+c++：**终结**前台作业
    -   ++ctrl+z++：**暂停**前台作业
    -   ++ctrl+d++：从一个 Shell 中**登出**
    -   ++ctrl+r++：搜索历史命令（fish 中无效）
    
    编辑：
    
    -   ++ctrl+l++：清除屏幕
    -   ++ctrl+u++：删除整行输入
    -   ++ctrl+w++：删除一个词
    -   ++ctrl+a++：移动至行首
    -   ++ctrl+e++：移动至行末
    -   ++ctrl+v++：允许插入控制字符
    -   ++ctrl+y++：粘贴之前使用 ++ctrl+u++ 或 ++ctrl+w++ 删除的文字
<!-- prettier-ignore-end -->

Shell 执行一条命令分为以下几个步骤：

1. **路径**。用户输入的是绝对路径或相对路径吗？是的话直接执行相应程序。
2. **别名**。用户输入的是用 `alias` 命令创建的别名？
3. **内部命令**。用户输入的是解释器的内部指令吗？是的话直接执行。
4. **查找**。系统在 `PATH` 变量定义的路径中查找命令文件。

更多关于 Shell 的内容请见 [Linux 命令解释器](LinuxShell.md)。

### man

其实 `man` 使用的是 `less`。此处介绍的即为 `less` 的操作。`less` 的操作和 `vim` 十分相似。

- `q` 退出
- `j` `k` 移动行
- `f` `b` 移动页（记忆：forward 和 backward）
- `g` `G` 跳至文件头尾（可指定行数）
-   `/`：从上至下搜索关键词
-   `?`：从下至上搜索关键词
-   `n`：定位到下一个关键词
-   `N`：定位到上一个关键词

`man` 的帮助信息也没有很固定的结构，`DESCRIPTION` 部分能让你快速知道这个程序能干什么，一般先读一下这边的内容。

<!-- prettier-ignore-start -->
!!! tip "No manual entry for <package>?"
    
    没有帮助手册可能是因为没有安装。比如 GCC 8 的帮助手册 `gcc-doc` 没有被 Debian 10 包括。参见 [What packages the man pages for GCC on Debian 10 Buster / Testing?](https://unix.stackexchange.com/questions/523079/what-packages-the-man-pages-for-gcc-on-debian-10-buster-testing) 
<!-- prettier-ignore-end -->

### 系统工作

-   `echo`
    -   如何提取变量？
-   `date`
    -   这个命令在你为文件名打时间戳等时候很好用。
    -   `-s`
    -   如何写时间格式字符串？`+%...`
    -   什么是：Unix time？
-   `reboot` 和 `poweroff`：只能用 `root` 用户运行这两个命令
-   `wget [option] URL`
    -   `-b` background 后台下载
    -   `-P` 指定目录
    -   `-c` continue 断点续传
    -   `-p` page 页面内所有资源
    -   `-r` recursive
-   `ps [option]`
    -   `-a` all 所有进程
    -   `-u` user 用户和其他信息
    -   `-x` 没有控制终端的进程
    -   用例：`ps aux | grep {{string}}`
    <!-- prettier-ignore-start -->
    !!! info "进程状态"
    
    -   R: running 运行或运行队列等待。
    -   S: sleep 休眠，等待条件或信号脱离状态。
    -   D: 不响应系统异步信号 不能被 `kill` 中断。
    -   Z: zombie 已终止，但进程描述符存在，需要父进程调用系统函数释放。
    -   T: ternimated 收到停止信号后停止。
    <!-- prettier-ignore-end -->
-   `top`
-   `pidof [option] [name]`
-   `kill [option] [PID]`
-   `killall [option] [name]`

<!-- prettier-ignore-start -->
!!! tip "多进程程序"
    
    复杂软件的服务程序由多个进程协同为用户提供服务，此时使用 `killall` 最为方便。
<!-- prettier-ignore-end -->

### 系统状态

-   `ifconfig [网络设备] [option]`: network **i**nter**f**ace **config**urator
    -   该命令属于 `net-tools` 包，一般不会默认安装
    -   你知道这些信息在哪吗？网卡名称、IP 地址、MAC 地址
-   `uname [-a]`: print system information
-   `uptime` 查看系统负载信息
    -   平均负载值最好控制在什么范围？
-   `free [-h]`: display amount of free and used memory in the system
-   `who`
-   `last [option]`
    -   注意，这些信息可能被修改，不应当轻信
-   `history`
    -   `-c`
    -   如何用 `!` 重复执行某一次命令？
-   `sos report`
    -   `sosreport` 命令现在已经替换为 `sos` 命令
    -   在需要输入的地方敲击回车即可。

### 工作目录命令

-   `pwd`
-   `cd`
-   `ls`

### 文本文件命令

-   `cat [option] [file]`
    -   `-n`
-   `more [option] [file]`
    -   适用于长文本，底部百分比提示阅读进度。使用回车键或空格键向下翻页。
-   `head [option] [file]`
    -   `-n [num]`
-   `tail [option] [file]`
    -   `-f` 打印最新的行，持续读文件。
-   `tr [origin] [suppliment]` 替换字符
    -   `tr [a-z] [A-Z]`
-   `wc [option] [text]`
    -   `-l, -w, -c`
-   `stat [file]`
-   `cut [option] [text]`
    -   `-d <sign>`
    -   `-f <num>`
    -   解释 `cut -d: -f1 file`
-   `diff [option] [file]`
    -   `-q` = `--brief`
    -   `-c`

### 文件目录命令

-   `touch [option] [file]`
    -   `-a, -m, -d`
    -   atime, mtime, ctime 是什么？access, modify, create
-   `mkdir [option] [directory]`
    -   `-p`
-   `cp`
    -   `-p, -r, -i`
    -   `-a` = `-pdr`
-   `mv`
-   `rm`
    -   `-f, -r`
-   `dd [option]`
    -   `if`
    -   `of`
    -   `bs`
    -   `count`
    -   例子：`dd if=/dev/zero of=560_file count=1 bs=560M`
    -   dd 的功能非常强大，甚至可以压制光盘镜像：`dd if=/dev/cdrom of=xxx.iso`
-   `file [file]`

<!-- prettier-ignore-start -->
!!! tip "一切皆文件"
    
    在 Linux 系统中，文本、目录、设备等一切都称为文件，因此不能但凭后缀知道具体文件类型，可以使用 `file` 来了解。
    
    `.d` 结尾的常常是附属的配置文件夹。
<!-- prettier-ignore-end -->

### 打包压缩与搜索

-   `tar [option] [file]`
    -   `.tar`, `.tar.gz`, `.tar.bz2`
    -   `-c, -x`
    -   `-t`
    -   `-z, -j`
    -   `-v`
    -   `-f`
    -   `-C`
    -   `-czvf, -xzvf`
-   `grep [option] [file]`
    -   `-n, -v`
    -   `-b, -i`
-   `find [start-point...] [expression]`
    -   `find` 的 `[expression]` 部分功能强大，可以执行条件运算（即最常用的按条件搜索文件）和执行动作等。
    -   例：`find /etc -name "host*" -print`
    -   `-exec {command} \;`
