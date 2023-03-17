---
tags:
    - Doing
---

# Linux 基础

<!-- prettier-ignore-start -->
!!! abstract
    
    这是给计算机小白的 Linux 入门笔记。参考教材是[《Linux 就该这么学》](https://www.linuxprobe.com/docs/LinuxProbe.pdf)。
    
    这本书是个人认为写得较好的中文 Linux 教程，但它的受众主要是服务器运维人员，面向 RHCE8 考试。
    
    本篇笔记主体依照该书编写，且将其实际应用在 WSL 和 Debian 系 Linux 上，更加贴近同学们的日常使用环境。
<!-- prettier-ignore-end -->

## 写在前面：学习是件苦差事

<!-- prettier-ignore-start -->
??? note "如果说学习Linux系统真的很简单，那必定是骗子的谎言"

    > 摘自《Linux 就该这么学》前言
    > 
    > 学习是一件痛苦的事情。如果说学习Linux系统真的很简单，那必定是骗子的谎言，起码这不能给您带来高薪。在每天起床后的几分钟时间里，大脑都会陷入斗争状态—是该聊会儿天呢，还是要追个美剧呢，还是看一下那本可怕的《Linux就该这么学》呢？这个时候，请不要忘记自己最初的梦想。十年后的你，一定会感激现在拼命努力学习的自己。身为作者，我的使命就是让这本书对得起您为此花费的时间、精力和金钱，让您每学完一个章节都是一次进步。

    不得不承认，初学 Linux 的经历可能相当痛苦。**减轻痛苦的方式有以下几种**：

    - 【重要】找到好的教程。坚决摒弃百度搜索得到的教程，转而使用谷歌搜索。CSDN 上的教程也往往不靠谱，主要原因是过于老旧（除了考试题目，还真蛮靠谱的，毕竟考试题目也老得要死），因此所有问题一律上谷歌。**跟着错误教程走的痛苦不亚于删掉重装**。
    - 找会使用 Linux 的同学帮忙。他很可能有与你一样的经历。
    - 学会阅读文档（特别是英文文档）。其实比记叙文阅读简单，只要熟悉计算机专业相关的词汇就好了。

    ==接下来，跟着《Linux就该这么学》和这篇笔记，开始 Linux 之旅吧。==
<!-- prettier-ignore-end -->

## 万事开头难：安装 WSL 和 C/C++ 环境

安装和配置环境可能对大多数人来说都是很折磨的一段经历。面对复杂的命令行和奇奇怪怪的报错，因为没有相关知识而无从下手，寻找教程却往往无法解决自己的问题。这里也仅能提供一些参考，实际安装时还是可能出现各种各样的情况。

**最后更新日期：2023 年 03 月 14 日**，本教程可能因为时间关系而不再适用。

### WSL 部分

<!-- prettier-ignore-start -->
!!! info "参考资料"
    
    - [教程：在 Windows 上用 WSL 优雅开发](https://dowww.spencerwoo.com/1-preparations/1-1-installation.html)
    - [Microsoft Docs: Install Linux on Windows with WSL](https://learn.microsoft.com/en-us/windows/wsl/install)
<!-- prettier-ignore-end -->

#### 0. 关于选择 Linux 版本

初学者无脑选择 Ubuntu 即可。初学时不要接触 Debian 和 ArchLinux，会变得不幸🤨。

#### 1. **重要**：在 BIOS 中开启内核虚拟化。一般电脑都是默认开启的。

请根据你正在使用的主板厂商自行检索如何进入 BIOS，进入 BIOS 后 AMD CPU 找 AMD Secure Virtual Machine (AMD SVM)选项开启，Intel CPU 找 Intel Virtualization Technology (Intel VT-x)选项开启。

<!-- prettier-ignore-start -->
??? failure "如果没有开启，可能遇到以下错误"
    
    - 0x80370102
<!-- prettier-ignore-end -->

#### 2. 开启支持 WSL2 的系统组件

使用管理员身份打开 PowerShell，输入以下命令。

```powershell
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
```

重启电脑

#### 3. 在应用商店中下载并安装以下两款软件：

-   [Ubuntu on Windows](https://apps.microsoft.com/store/detail/ubuntu-on-windows/9NBLGGH4MSV6)。也可以选择带 LTS 的版本，更加稳定，但可能功能落后。
-   [Windows Subsystem for Linux](https://www.microsoft.com/store/productId/9P9TQF7MRM4R)。该软件提供 GUI 支持，让你可以不借助远程桌面直接运行 Linux 中的图形应用程序，并且会把 Linux 中的程序显示在你的开始菜单中。相当于消除了 Linux 和 Windows 间的图形壁垒。否则你可能只能使用命令行。

#### 4. 检查 WSL 版本是否为 WSL2。

```powershell
wsl --list --verbose
```

如果 `VERSION` 列是 `2`，则不用进行以下操作。否则执行以下命令，其中 `<distro>` 是你的 WSL 版本名称（出现在刚刚的 `NAME` 列）：

```powershell
wsl --set-version <Distro> 2
```

再次检查版本是否为 WSL2。重启。

#### 5. 启动 WSL。

<!-- prettier-ignore-start -->
??? failure "你大概率会遇到一个报错"
    
    出现报错，末尾附上了一个含有 `aka.ms` 的链接。这是因为需要更新 WSL 内核。按住 ++ctrl++ 同时点击该链接，跳转到微软的文档，点击下载下载 Linux 内核更新包，安装，再启动 WSL 即可。
    
<!-- prettier-ignore-end -->

#### 6. 设置用户名和密码。

以后当你执行安装软件等操作时，都需要输入密码。

#### 7. 换源。

默认情况下 Linux 系统从国外的官方源获取软件包，但是在国内速度很慢。最好换成学校的镜像站，速度起飞，再也无需漫长的等待。

-   [浙江大学开源镜像站](http://mirrors.zju.edu.cn/)

执行以下命令即可：

```bash
sudo sed -i 's@//.*archive.ubuntu.com@//mirrors.zju.edu.cn@g' /etc/apt/sources.list
```

<!-- prettier-ignore-start -->
??? note "手动换源"

    1. 确认你的 Linux 版本

        ??? note "如何确认 Linux 版本"
    
        - 使用 `cat /etc/issue`。

        ```
        Ubuntu 22.04.2 LTS \n \l
        ```

        - 使用 `lsb_release -a`。如果你安装的是 Debian 系统，则默认没有安装该命令。

        ```
        No LSB modules are available.
        Distributor ID: Ubuntu
        Description:    Ubuntu 22.04.2 LTS
        Release:        22.04
        Codename:       jammy
        ```

    2. 进入镜像站，找到你对应的系统和版本。

    3. 用镜像站提供的文本覆盖 `/etc/apt/sources.list`。
<!-- prettier-ignore-end -->

#### 8. 更新源和软件。

这是初次安装 Linux 系统时一定要做的一件事，先把系统的各种软件更新到最新。

```bash
sudo apt update && sudo apt upgrade
```

#### 9. 安装 C/C++ 编译工具包

```bash
sudo apt install build-essential
sudo apt install gcc g++ gdb
```

#### 恭喜你，完成了 WSL 的安装

至此，基本的 Linux 编程环境已经安装完成。下一节我们讲述**命令行**的基本操作。

<!-- prettier-ignore-start -->
??? note "杂谈：命令行到底是什么？"
    
    不少同学初学时有这样的疑惑：**为什么我们要使用这个黑色的窗口，往里面输入各种奇奇怪怪的命令？**这里简单聊一聊这个问题。

    - 在计算机的早期并没有图形界面，我们只能通过一个一个的命令来控制计算机。
        - 现在你是计算机专业的学生，会经常接触到更为底层的东西，比如与操作系统内核交互，它们并没有提供图形界面，所以要熟悉使用命令行。 
        - **【重要】你以后在工作中会经常使用 Linux 系统，目前大部分网络服务器都使用 Linux 系统。特别是你将来要从事服务器运维工作时，Linux 会成为你的入职门槛。**
    - 命令行和图形界面、快捷键一样，都是**操作系统和应用的一种方式**。
        - 与图形界面（GUI）主要使用鼠标、图像等直观视觉交互方式不同，命令行通常需要用户**记忆操作的命令**。
        - 对于图形界面，用户点击某个图标就能启动某个程序；对于命令行，用户输入某个程序的名字（可以看做一个命令）就能**启动某个程序**。

    在 Linux 系统中使用命令行有以下优势：

    - 能够使用各种方便的工具

    举一个例子：按指定格式批量重命名文件。按我们日常使用 Windows 的习惯，在量少的时候你会一个个手动更改，量大的时候你会去网上找小工具。而在 Linux 系统的命令行界面，你只需要一行命令：

    ```bash
    rename mod adb *
    ```

    上面这行命令的作用是把当前目录下所有文件名中含有 `mod` 字符串的替换成 `adb`。是不是很方便呢？

    - 运行速度快

    命令行界面要较图形用户界面节约计算机系统的资源。在熟记命令的前提下，使用命令行界面往往要较使用图形用户界面的操作速度要快。

    - 自动化

    你可以编写脚本实现各种繁杂的、机械的操作。

    此外，《Linux 就该这么学》 的**前言**部分简要介绍了 Linux 系统的历史、开源精神和相关概念、为什么要学习 Linux 的问题，有兴趣可以看一看。
<!-- prettier-ignore-end -->

### VSCode 和 Windows Termial 部分

下载并安装 Visual Studio Code。


## 命令行基础

<!-- prettier-ignore-start -->
!!! abstract

    本节对应《Linux 就该这么学》第二章。

    书中不少命令面向运维人员，了解即可。必须掌握的我会在笔记中提示。**所谓掌握，你知道它能干嘛就行，用法记不下来就算了，反正随时可用 `man` 命令查询**。  
<!-- prettier-ignore-end -->

命令行（Command Line Interface, CLI）又称为文本字符界面。

这里我们解释几个名词的意思：Console（控制台）、Terminal（终端）、Shell（命令解释器）、Prompt（提示符）。

<!-- prettier-ignore-start -->
!!! note "Console、Terminal 和 Shell 的区别"
    
    - 我们打开 Windows 的那个「小黑框」，实际上就是打开了一个**终端（Terminal）**。
    - 在终端里面「输入命令，得到结果」的交互程序，就是**命令行解释器（Shell）**。
        - 在 Windows 里用的 Shell 一般是 `PowerShell`，你应该见过它不少次了。
        - 在 Linux 中默认使用 `bash`，但我更推荐使用 `fish`，深入学习后你会使用 `zsh` 体验更多扩展功能。

    所以，我们是在**终端**里与**命令行解释器**交互。能理解到这里就行了。（就是说这个窗口不是运行命令解释器的，命令解释器运行在 WSL 里面）。

    - 控制台 Console 则是相对古老的概念，是大型机**物理意义上面的独立终端**，我们在这里先不探讨这个话题。
    - 当你没有输入命令时显示的那一段文本，如 `bowling@desktop:~$`、`PS C:\Users\bowling>`，它们叫**做命令提示符 Prompt**。顾名思义，提示你输入命令。
<!-- prettier-ignore-end -->

==OK，接下来我们翻到《Linux 就该这么学》第二章（P65），学习一些基本的命令行操作。==

### 2.1 强大好用的 Shell

学完该节你应该了解了以下东西是什么：

- 系统内核
- 用户与硬件的中间有哪几层东西
- Shell 是什么

### 2.2 执行命令的必备知识

记得把书中的命令都在自己电脑上试一试。

学完该节你应该了解了以下东西是什么：

- 命令的基本格式
- 学会使用 `man` 获取命令帮助，怎么在 `man` 中翻页，怎么离开 `man`。

书中介绍了**额外的 4 个快捷键**，这里补充一点，可以试一试，挺好用的。

<!-- prettier-ignore-start -->
!!! note "终端常用的控制按键"
    
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
    -   ++ctrl+y++：粘贴刚刚使用 ++ctrl+u++ 或 ++ctrl+w++ 删除的文字
<!-- prettier-ignore-end -->

### 2.3 常用系统工作命令

你应该知道以下命令是用来干什么的：

- `echo`
- `date`
- `reboot`
- `poweroff`
- `wget`

### 2.4 系统状态检测命令

你应该知道以下命令是用来干什么的：

- `who`
- `ping`
- `history`

### 2.5 查找定位文件命令

你应该知道以下命令是用来干什么的：

- `pwd`
- `cd`
- `ls`
- `tree`
    - 这个命令可能没有预先安装，那就安装一下：`sudo apt install tree`。
- `find`
- `locate`
- `whereis`
- `which`

### 2.6 文本编辑命令

你应该知道以下命令是用来干什么的：

- `cat`
- `more`
- `head`
- `tail`
- `tr`
- `wc`
- `stat`
- `grep`
- `cut`
- `diff`
- `uniq`
- `sort`

### 2.7 文件目录管理命令

- `touch`
- `mkdir`
- `cp`
- `mv`
- `rm`
- `file`
- `tar`

### 补充：TLDR 工具

本章结束，你应该已经在命令行中尝试了不少命令了，应该已经挺习惯命令行操作了。接下来介绍一个工具 `tldr`。它比 `man` 更加实用。

> TL;DR 的意思就是**太长不看**（too long; didn't read）。你已经见过十分冗长的 `man` 页面，我也挺讨厌它的。`tldr` 工具为我们提炼出其中的精华，直接给出常用的用法，更适合日常使用时查询。

- 安装 `tldr`

```bash
sudo apt install tldr
```

初次安装 `tldr` 后，输入 `tldr -u` 更新帮助信息，否则就无法得到帮助。

<!-- prettier-ignore-start -->
!!! tip "如果没有执行成功"
    
    `tldr` 的帮助手册托管在 GitHub 上，因此你可能需要连接 VPN。
<!-- prettier-ignore-end -->

更新完成后，试试输入 `tldr [想要查询的命令]`，比如 `tldr mv`。

是不是很实用、很简洁？比起 `man` 更好用？

这个教程到这里就应该结束了。你已经认识了命令行的基本概念，**学会用 `man` 和 `tldr` 获取帮助**，也就意味着掌握了所有命令了。

如果你并不打算进一步熟悉 Linux 系统，可以不用阅读接下来的内容。

## 管道符、重定向与环境变量

## Vim 编辑器与 Shell 命令脚本

## 用户身份与文件权限

**分割线，下面的内容还在整理中**

---

**分割线，下面的内容还在整理中**



Shell 执行一条命令分为以下几个步骤：

1. **路径**。用户输入的是绝对路径或相对路径吗？是的话直接执行相应程序。
2. **别名**。用户输入的是用 `alias` 命令创建的别名？
3. **内部命令**。用户输入的是解释器的内部指令吗？是的话直接执行。
4. **查找**。系统在 `PATH` 变量定义的路径中查找命令文件。

更多关于 Shell 的内容请见 [Linux 命令解释器](LinuxShell.md)。

### man

其实 `man` 使用的是 `less`。此处介绍的即为 `less` 的操作。`less` 的操作和 `vim` 十分相似。

-   `q` 退出
-   `j` `k` 移动行
-   `f` `b` 移动页（记忆：forward 和 backward）
-   `g` `G` 跳至文件头尾（可指定行数）
-   `/`：从上至下搜索关键词
-   `?`：从下至上搜索关键词
-   `n`：定位到下一个关键词
-   `N`：定位到上一个关键词

`man` 的帮助信息也没有很固定的结构，`DESCRIPTION` 部分能让你快速知道这个程序能干什么，一般先读一下这边的内容。

<!-- prettier-ignore-start -->
!!! tip "No manual entry for <package>?"
    
    没有帮助手册可能是因为没有安装。比如 GCC 8 的帮助手册 `gcc-doc` 没有被 Debian 10 包括。参见 [What packages the man pages for GCC on Debian 10 Buster / Testing?](https://unix.stackexchange.com/questions/523079/what-packages-the-man-pages-for-gcc-on-debian-10-buster-testing) 
<!-- prettier-ignore-end -->

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
