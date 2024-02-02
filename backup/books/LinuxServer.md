---
tags:
  - Ongoing
---

# Linux 应用大全：服务器架设

| 出版社         | 作者 | 年份 |
| -------------- | ---- | ---- |
| 人民邮电出版社 | 於岳 | 2014 |

本书先介绍了 Linux 网络配置文件和网络命令，然后讲述了 OpenSSH、DHCP、Nginx 等服务器配置的知识。我只挑选了一些自己需要的章节。

阅读本书前，读者应当具有基本的 Linux 服务器使用经历，具备一定的计算机网络知识。

## Ch1. Linux 网络配置

<!-- prettier-ignore-start -->
!!! tip "本书使用的 Linux 发行版"
    
    本书使用的 Linux 发行版应该是 CentOS / RHEL。第一章 `/etc/sysconfig/network-scripts/ifcfg-eth0` 在 Debian 系系统中对应的路径为 `/etc/NetworkManager/`。在 WSL 中其路径又发生了变化。
<!-- prettier-ignore-end -->

### 1.1 编辑网络配置文件

#### 网络设备相关

在 Debian 类系统中，系统网络设备的配置文件保存在 `/etc/NetworkManager/system-connections` 中。每个网络设备对应一个文件，其中包含回路 IP 地址等信息。

-   `/etc/networks` 网络名和网络地址之间的映射关系。
-   `/etc/protocols` 使用的协议和协议号。
-   `/etc/services` 系统中所有服务的名称、**端口/协议类型、**别名、注释等信息。

```title="/etc/services"
fsp 21/udp  fspd    #xxxx
```

#### 域名解析相关

-   `/etc/resolv.conf` 是域名解析器的配置文件，包含域名服务器、DNS 搜索路径等。
-   `/etc/host.conf` 指定如何解析主机名。
-   `/etc/hosts` 存放一些匹配信息。

```title="resolv.conf"
order bind, hosts
multi on
```

`order` 指定主机名查询的顺序，在上面的配置文件中，先查询 DNS 服务器，再查询 `/etc/hosts` 文件。

### 1.2 Linux 网络命令

-   `ping` 测试连通性，使用 ICMP 协议。
-   `traceroute` 数据包到达主机的路径
-   `mii-tool` 查看网卡的工作模式。虚拟设备如 `lo`、`virbr0` 等可能不支持操作。
-   `ifconfig` 显示和配置网络接口。
-   `ifdown` 关闭网络接口
-   `ifup` 开启网络接口

<!-- prettier-ignore-start -->
!!! tip
    
    这些命令中的 `if` 都是 interface 的缩写。
<!-- prettier-ignore-end -->

-   `netstat` 显示网络状态信息：网络连接、路由表、接口统计等。
-   `arp` 修改 ARP 缓存条目。

<!-- prettier-ignore-start -->
!!! info "ARP Cache"
    
    Address Resolution Protocol，即 MAC 地址解析缓存。
<!-- prettier-ignore-end -->

-   `rpcinfo` 显示使用 protmap 注册的程序，并进行 RPC 调用检查是否正常运行。
    -   该命令属于 `rpcbind` 包，一般没有默认安装。
-   `ip` 操纵路由设备和隧道等。

### 高级网络工具

<!-- prettier-ignore-start -->
!!! note "略过"
    
    暂时还没有学习这部分，先跳过啦~
<!-- prettier-ignore-end -->

-   `nmap`

Network Mapper 网络映射器，是一款网络探测和安全审核程序。它使用原始 IP 报文来发现网络上有哪些主机、提供什么服务、有什么服务运行在哪些操作系统上、使用什么类型的报文过滤器/防火墙。

-   `tcpdump`

这是 Linux 系统中强大的网络数据采集分析工具之一，可将网络中传输的数据包的头完全截获下来提供分析。

-   Wireshark

网络数据包分析软件。

### TCP Wrapper 保护机制

<!-- prettier-ignore-start -->
!!! note "略过"
    
    暂时还没有学习这部分，先跳过啦~
<!-- prettier-ignore-end -->

这是一个简单的防火墙机制，定义哪些主机允许或不允许连接到网络服务。依赖于 `/etc/hosts.allow` 和 `/etc/hosts.deny` 两个文件。

### ADSL 连接配置

<!-- prettier-ignore-start -->
!!! note "略过"
    
    这部分的内容已经有些过时，也先跳过啦~
<!-- prettier-ignore-end -->

## OpenSSH

### 回忆基础

-   Secure Shell 是建立在应用层和传输层上的安全协议，能有效防止远程管理过程中的信息泄露问题。
-   SSH 能够代替 telent，可以为 ftp、pop 和 ppp 提供安全通道。

### SSH 工作原理

-   服务端：一个守护进程 `sshd`，响应来自客户端的连接请求。
    -   提供**对远程连接的处理**，包括密钥认证等。
-   客户端：`ssh`、`scp`、`sftp` 等应用程序。

<!-- prettier-ignore-start -->
!!! note "略过"
    
    SSH 服务器配置的内容先跳过啦~
<!-- prettier-ignore-end -->

## Nginx



## 同类参考文献

-   [鸟哥的 Linux 私房菜：服务器架设篇 第三版](http://shouce.jb51.net/vbird-linux-server-3/index-2.html)
