# Ubuntu 系统折腾记

2022.12.21-23 这几天，组装了新的台式机，同时给笔记本更换了电池，也将系统从 Windows11 开发者预览版回退到 Windows10 LTSC。笔记本安装双盘双系统，以 Ubuntu 作为主系统。两台机子都是打扫干净，从零开始配置。以下浅记录一下这几天的折腾记录。

## Ubuntu 配置

本来打算装 Debian 的，但是在台式机和笔记本上都因为驱动问题以失败告终（耗费了我半天的时间）。经历过这些后，我更倾向于支持 Arch Linux “实用性大于意识形态”的选择。Ubuntu 果然是最适合新手的 Linux（需要 GUI、作为独立系统的安装的情况下）。

Ubuntu 安装按一般流程走即可，

### 网络和远程桌面

在 CC98 上可以找到前辈们的各种分享，真是帮大忙了。然而，还是有很多东西要自己试过才知道能不能起效。以下是我设置时参考的一些帖子：

??? info "CC98上的参考贴"

    * [PowerShell 自动脚本](https://www.cc98.org/topic/5076398)

关于 Linux 上代理/VPN 相关的内容，直接写在 [代理](../../webdev/webserver/Proxy.md) 中了。

### 蓝牙连接

一个方便的管理蓝牙设备的软件 `blueman`，在 GitHub 有 [项目主页](https://github.com/blueman-project/blueman)，可以通过它监测各个蓝牙设备的连接状况。

首先，需要在 `/etc/bluetooth/main.conf` 中找到并修改如下值，才能连接蓝牙耳机（至少我的 Huawei FreeBuds 4i 是这样的）：

```conf
ControllerMode = dual
```

### 杂七杂八的

* `gnome-tweaks` 是一个用于优化 GNOME 的小工具，我也不知道它能有什么用。


## 硬件部分

### 台式机组装

这个台式机是因为看上了华硕的 AP201 机箱配的，具体配置如下：

* 机箱：华硕 AP201
* 主板：微星 B66OM 迫击炮 WIFI DDR4
* 处理器：Intel Core i5-12400
* 内存：镁光 16 GB 普条
* 电源：酷冷至尊 GX750 白色版
* 固态硬盘：三星 980 PRO 500 GB +  MZVLW256HEHP
* 机械硬盘：Hitachi 4 TB x2
* 散热器：九州风神 AK400 HW
* 