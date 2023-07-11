# Linux 使用杂记

<!-- prettier-ignore-start -->
!!! abstract "简介"

    Ubuntu 一定是最容易上手和使用的 Linux 系统。深入使用了一段时间后，发现 Windows 上常用的软件都能在 Ubuntu 上找到替代品。以下是我在使用 Ubuntu 作为主力系统期间的一些记录。
<!-- prettier-ignore-end -->

## 代理

保证网络畅通才能进行各种各样的配置，一些简单的命令可以通过设置 `clash` 代理来完成。

### Clash

不要 `apt install clash`，你会安装上一个好像是 Haskell 制作程序的东西。

我们将使用 Clash for Windows，这是一个基于 Clash 和 Electron 的 Windows、Linux 和 macOS 通用的 clash 客户端。

<!-- prettier-ignore-start -->
!!! info "参考资料"

    - [Docs for clash for Windows](https://docs.cfw.lbyczf.com/)
<!-- prettier-ignore-end -->

按照 [在 Linux 上使用 Clash 作代理](https://einverne.github.io/post/2021/03/linux-use-clash.html) 的安装步骤，将 CFW 客户端放进 `/usr/local/bin`，这样就能在命令行中使用 `clash` 来运行 CFW 了。

从你的代理商处获取 clash 配置文件，替换掉 `~/.config/clash/config.yaml`。

在命令行中运行 `clash`，你可能看见如下输出：

```text
INFO[0000] Mixed(http+socks) proxy listening at: 127.0.0.1:7890
INFO[0000] RESTful API listening at: [::]:9090
```

第一行是 clash 的代理监听地址，第二行是 clash 的 API 监听地址。把你的系统代理设置为第一行的地址即可。

<!-- prettier-ignore-start -->
??? note "为 CFW 设置开机启动、配置 UI 界面"

    首先将配置文件移动到 `/etc` 下：
    
    ```bash
    sudo mv ~/.config/clash /etc
    ```
    
    下载 [yacd: Yet Another Clash Dashboard](https://github.com/haishanh/yacd) 的压缩包并解压到 `/etc/clash/ui`。
    
    在 `config.yaml` 中修改并添加添加：
    
    ```yaml
    external-control: 127.0.0.1:9090
    external-ui: ui
    ```
    
    访问 `127.0.0.1:9090/ui` 就可以看到 Clash 的图形界面啦。
    
    使用 `vim` 增加 systemd 配置：`sudo vim /etc/systemd/system/clash.service`，内容如下：
    
    ```text
    [Unit]
    Description=Clash Daemon
    
    [Service]
    ExecStart=/usr/local/bin/clash -d /etc/clash/
    Restart=on-failure
    
    [Install]
    WantedBy=multi-user.target
    ```
    
    启用服务：
    
    ```bash
    sudo systemctl enable clash.service
    sudo systemctl start clash.service
    ```
    
    查看日志：
    
    ```bash
    journalctl -e -u clash.service
    ```    
<!-- prettier-ignore-end -->

### 为 APT 设置代理

<!-- prettier-ignore-start -->
!!! quote "参考资料"
    
    - [How to Set the Proxy for APT on Ubuntu 18.04](https://www.serverlab.ca/tutorials/linux/administration-linux/how-to-set-the-proxy-for-apt-for-ubuntu-18-04/)
    - [Configure proxy for APT? - Ask Ubuntu](https://askubuntu.com/questions/257290/configure-proxy-for-apt)
<!-- prettier-ignore-end -->

## 同步

### Syncthing

按 [Syncthing 官方文档](https://apt.syncthing.net/) 完成 Syncthing 的安装。

接下来配置 Syncthing 服务，官方已经创建好服务文件 `/lib/systemd/system/syncthing@.service`，只需开启即可：

```bash
sudo systemctl enable syncthing@username.service
sudo systemctl start syncthing@username.service
```

接下来你可以访问 `127.0.0.1:8384` 看到 Syncthing Web UI 的界面。

要在服务器端配置，请参见：[Syncthing 同步服务器搭建记录](../problem/SyncthingConf.md)。

### Onedrive

使用开源免费的 [OneDrive Client for Linux](https://github.com/abraunegg/onedrive) 进行同步。请仔细阅读项目说明并按照说明完成安装。完成安装后，输入 `onedrive --version` 测试你是否正确完成安装。

接下来使用 [OneDriveGUI](https://github.com/bpozdena/OneDriveGUI) 来配置账户和查看同步情况。

## 各种软件

### 使用命令行安装 `.deb` 软件包

```bash
sudo apt install ./xxx.deb
sudo dpkg -i ./xxx.deb
```

<!-- prettier-ignore-start -->
!!! note "APT vs dpkg"
    
    - `apt` 会自动下载并安装依赖项，`dpkg` 不会。
    - `apt` 使用 `dpkg` 进行软件安装。
<!-- prettier-ignore-end -->

### 社交

-   [QQ](https://im.qq.com/linuxqq/index.shtml)。推荐直接在 Ubuntu 应用商店中下载。目前 Linux QQ 界面十分简洁，基本功能足够完善。
-   [钉钉](https://page.dingtalk.com/wow/z/dingtalk/simple/ddhomedownlaod#/)。在官网下载 Linux 客户端，仅有 `deb` 安装包。使用体验与 Windows 版几乎一致。

### 办公

- [WPS Office](https://www.wps.com/office/linux/)。很实用，比 Libre Office 符合国人的使用习惯。

-   [Typora](https://typora.io/#linux)。Typora 的 apt 源在国内无法解析（猜测是 `.io` 域名问题），安装过程的代理设置十分艰难。推荐直接下载 `deb` 安装包。没有 Windows 版的一体化界面。
-   [搜狗输入法](http://shurufa.sogou.com/linux)。中文输入功能完善，比 Ubuntu 自带输入法智能太多。
-   [emote](https://github.com/tom-james-watson/emote)。Linux 的 emoji 输入面板，挺方便的。
-   [Tabby](https://tabby.sh/)。目前我见过最好看、方便配置的跨平台终端，甚至提供了 [Web app](https://app.tabby.sh/)。GNOME 自带的终端在使用 zsh 的 powerlevel10k 主题时可能出现问题，tabby 则对各种功能都提供了完善的支持，比如可以保管 ssh 秘钥、记录上次退出时的终端状态等，资源占用也不高。
-   [Pomodoro](https://gnomepomodoro.org/)。GNOME 上的番茄计时器，简单实用，使用体验非常棒。

### 娱乐

-   [Lollypop](https://wildskyf.github.io/lollypop-web/)。音乐播放器，比自带的 RhythomBox 好看很多，对于专辑等也有不错的管理。
-   `Spotify`。很好的在线音乐平台。
-   `VLC media player`。视频播放器。

### 美化

- [Hidamari](https://github.com/jeffshee/hidamari)。视频桌面。

### 其他

- `Deluge`。轻量级 BT 客户端，比 qBittorrent 功能简洁，占用少很多。
- [`tabby` 终端](https://tabby.sh/)，目前我见过最好看，同时方便配置的跨平台终端，甚至提供了 [Web app](https://app.tabby.sh/)。GNOME 自带的终端在使用 zsh 的 powerlevel10k 主题时可能出现问题，tabby 则对各种功能都提供了完善的支持。在我的 Ubuntu 上运行时，资源占用也不高。

<!-- prettier-ignore-start -->
!!! note "更多软件"

    这些软件也不错，但并不推荐。它们的功能较少或不太完善、界面不够美观或很久没有更新。
    
    - [Amberol](https://flathub.org/apps/details/io.bassi.Amberol)。音乐播放器，极致简洁，比 Lollypop 好看一些，但只支持播放列表，播放体验并不好。
    - qBittorrent。AppImage 格式的 qBittorrent 内存占用极高，卡顿明显，不推荐使用。
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
??? danger "Linux 上的安卓子系统"

    不要试图在 Linux 上运行安卓子系统，会变得不幸。
    
    如果你对安卓应用有重度需求，可以尝试 [Waydroid](https://waydro.id/) 项目。它使用 LineageOS 的安卓镜像，比 Anbox 新，对当前的安卓应用有较好的兼容性。
<!-- prettier-ignore-end -->


### 使用 Appimage 格式的软件

<!-- prettier-ignore-start -->
!!! info "什么是 AppImage ？"

    参见官方文档：[AppImage 让 Linux 应用随处运行](https://appimage.org/)。
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
!!! tip "好习惯"

    把所有 AppImage 文件放在 `~/Application` 或 `/opt` 下，一些工具会自动扫描这些文件夹。
<!-- prettier-ignore-end -->

使用 [`appimaged`](https://github.com/probonopd/go-appimage) 能够自动扫描 AppImage 文件并创建 `.desktop` 文件。

<!-- prettier-ignore-start -->
??? note "什么是 `.desktop` 文件？"

    - [Desktop Entry Specification](https://specifications.freedesktop.org/desktop-entry-spec/latest/index.html#introduction)
    
    Both the KDE and GNOME desktop environments have adopted a similar format for "desktop entries", or configuration files describing how a particular program is to be launched, how it appears in menus, etc. It is to the larger community's benefit that a unified standard be agreed upon by all parties such that interoperation between the two environments, and indeed any additional environments that implement the specification, becomes simpler.
<!-- prettier-ignore-end -->

把需要自动启动的 `.desktop` 文件拷贝到 `~/.config/autostart` 即可实现自动启动。

<!-- prettier-ignore-start -->
!!! info "参考资料"

    - [Ask Ubuntu: Extract icon from appimage](https://askubuntu.com/questions/1115321/extract-icon-from-appimage)。
    - [Ask Ubuntu: How can I add new autostart programs in Lubuntu?](https://askubuntu.com/questions/81383/how-can-i-add-new-autostart-programs-in-lubuntu)
<!-- prettier-ignore-end -->

## 使用技巧

-   窗口飘到屏幕外去了

按 ++alt+space++ 跳出窗口选项菜单。参见 [StackOverflow: Window appears off screen on ubuntu](https://stackoverflow.com/questions/12477435/window-appears-off-screen-on-ubuntu)。

-   桌面管理

[知乎：平铺式窗口管理器真的好用吗？](https://www.zhihu.com/question/447039478)

Ubuntu 自带的 Gnome 也有不少方便使用的快捷键，详见：[Useful keyboard shortcuts](https://help.gnome.org/users/gnome-help/stable/shell-keyboard-shortcuts.html.en)

- 高分屏缩放

GNOME 显示配置只能 100% 或 200%，使用 Fractional Scaling 效果很差。实测设置字体缩放效果最：`gsettings set org.gnome.desktop.interface text-scaling-factor 1.1`，对于我的 15.6 英寸笔记本来说 1.1 是最舒适的比例。然而这只是对 GNOME 相关软件进行了缩放，有些软件还需要手动设置。

> 参考：[https://prinsss.github.io/setting-up-manjaro-linux/](https://prinsss.github.io/setting-up-manjaro-linux/)

- 查看电脑功耗

```bash
awk '{print $1*10^-6 " W"}' /sys/class/power_supply/BAT0/power_now
```

或者安装 `powertop` 查看详细的硬件、软件功耗情况。

- 驱动更新

Ubuntu 安装时不一定装上了最新的推荐驱动（独立显卡一般都没有装），使用该命令可以安装最新的推荐驱动，更好地管理硬件。

```bash
sudo ubuntu-drivers autoinstall
```

- 自动挂载其他文件系统

更改 `/etc/fstab` 文件。该文件的配置可以参考 [fstab - Debian](https://wiki.debian.org/fstab)。

- 字体

当你在 Ubuntu 上打开他人的 Office 文档时，常常遇到字体缺失的问题。Ubuntu 自带的字体比 Windows 少很多，中文更是寥寥无几。在 [W7DF.com](https://www.w7df.com/) 可以下载各个版本 Windows 的标准字体包，将其解压到 `~/.fonts` 即可。

- 双系统时间不一致

```bash
timedatectl set-local-rtc 1 --adjust-system-clock
```

Windows 将硬件时间看做系统时间，而 Linux 将硬件时间看做 UTC 时间，在此基础上加上时区成为系统时间。

- 合盖不休眠

Ubuntu 默认合盖休眠，虽然开盖恢复时间挺快，但恢复蓝牙需要一段时间。如果正在播放音频，就会社死。设置系统处理电源行为可以参考 [简书：Ubuntu 笔记本设置合盖不休眠](https://www.jianshu.com/p/3fe469fc60c9)。



### 终端重度使用者

- [Lynx](https://lynx.invisible-island.net/) 使用终端浏览网页。

测试下来，大部分国外网站对终端纯文本界面有较好的兼容性。国内网站使用终端浏览就是依托答辩。

与 Lynx 同类的还有 links 等。

`brwosh` 是一个更现代化的文本浏览器，能够渲染页面上的 JavaScript 等元素。依赖 Firefox，需要下载二进制文件使用。

### 校内网络和远程桌面

<!-- prettier-ignore-start -->
!!! note "IPv6"
    

    使用 IPv6 的特定端口时，应当把地址用方括号括起来，否则会和端口号混在一起导致错误。正确的表示如：`[2402:f000:1:801::8:28]:8080`。
<!-- prettier-ignore-end -->

在 CC98 上可以找到前辈们的各种分享，真是帮大忙了。然而，还是有很多东西要自己试过才知道能不能起效。以下是我设置时参考的一些帖子：

<!-- prettier-ignore-start -->
??? info "CC98上的参考贴"

    * [win10校园网自建VPN & 自动重连脚本（PowerShell）](https://www.cc98.org/topic/5076398)，实测可用。
    * [有线网进阶操作全攻略——自动重连、多拨、远程桌面、IPv6 隧道、DDNS、自建内网穿透……](https://www.cc98.org/topic/5055830)，包含了很多内容，尚未详细研究。
    * [在家如何搞学术：远程桌面、ssh、跳板机攻略（针对Win10）](https://www.cc98.org/topic/5483684)
    * [使用 Clash+ZJU Rule 提升你的 ZJU 科学上网体验！](https://www.cc98.org/topic/5257184)，Clash 用户值得一试。
    * [校外使用rvpn连接内网Windows 10电脑](https://www.cc98.org/topic/5482686)，主要涉及更改默认端口。
<!-- prettier-ignore-end -->

- 更改端口：在内网（特别是相同子网）访问时，不需要更改端口。如果出现找不到设备，很可能是因为 RDP 协议的 `3389` 端口被校网出于安全原因禁用了。

未解决的问题是：

-   通过 rvpn 在校外连接电脑的远程桌面。初步判断为手机端网卡 IPv6 功能不完善（查询是有 IPv6 网址的，但是联不通）。
-   被控端，连接 l2tp 后无法被远程桌面连接，断开后可以。

拆机修理过程中，我弄断了笔记本无线网卡的天线，不得不被迫体验一把 Ubuntu 连有线网络。目前个人尝试下来，GUI 界面最好使用 GNOME 自带的 VPN，CLI 最好使用求是潮的 [zjunet](https://github.com/QSCTech/zjunet)。如果会使用 CLI，那么 `zjunet` 不需要我过多介绍，你能自己了解它的使用方法（阅读 README 和使用 `-h`）。以下介绍 GNOME 的配置。

首先，Linux 发行版基本都不会附带 L2TP 协议支持，所以必须先用无线联网，或在其他电脑上下载好相关软件包。在 Ubuntu 中使用图形界面的 `network-manager` 时，需要：

```bash
sudo apt install network-manager-l2tp network-manager-l2tp-gnome
```

安装完成后，重启。在 VPN 界面可以创建 L2TP VPN，网关填写 `10.5.1.9`。在 PPP 选项中，“身份验证”全选，安全性及压缩仅勾选 BSD 和 Deflate。配置就完成啦！

<!-- prettier-ignore-start -->
??? note "网关选哪个？"

    在 L2TP VPN 的网关配置中，应当填写 `10.5.1.9` 或 `10.5.1.10` （玉湖测试通过）。注意，网关和 Windows 中的 VPN 服务器不一样。`lns.zju.edu.cn` 、 `10.0.2.72` 和 `10.0.2.73` （VPN 服务器的 IP）都是不行的。

??? info "CC98上的参考贴"

    * [CC98：2019年ubuntu图形界面连接vpn，不再需要命令行](https://www.cc98.org/topic/4848071)
    * [CC98：记录一下Linux下有线接校网](https://www.cc98.org/topic/5394591) 王重阳老师的这个配置我试了不行，不知道是什么原因，或许是教师允许使用的协议不同？
<!-- prettier-ignore-end -->

### 蓝牙连接

<!-- prettier-ignore-start -->
??? info "blueman"
    
    一个管理蓝牙设备的软件 `blueman`，在 GitHub 有 [项目主页](https://github.com/blueman-project/blueman)，可以通过它监测各个蓝牙设备的连接状况。
<!-- prettier-ignore-end -->

首先，需要在 `/etc/bluetooth/main.conf` 中找到并修改如下值，才能连接蓝牙耳机：

```conf
ControllerMode = dual
```

连接成功后，试听了歌曲感觉音质很差，怀疑是蓝牙编码的问题。Ubuntu 自带 `SBC` 编码，而现在的蓝牙耳机至少都是 `AAC` 起步。于是查找资料，了解了一些 Linux 音频系统的知识。

Ubuntu 的音频由 [`pluseaudio`](https://wiki.archlinux.org/title/PulseAudio) 管理。插件 [`pulseaudio-modules-bt`](https://github.com/EHfive/pulseaudio-modules-bt) 为 `pluseaduio` 提供了 AAC、LDAC 等蓝牙编解码器。但该插件仓库作者已经不再维护，PPA 源也仅支持到 Ubuntu 20.04。查看 Issue 得知作者已经转移到 [`PipeWire`](https://wiki.archlinux.org/title/PipeWire)，经过一番查找，我也找到了使用 PipeWire 支持高质量音频编码的博客：[在 Ubuntu 21.10 上启用蓝牙 LDAC/AAC/AptX 高质量音频编码支持](https://kenvix.com/post/setup-ubuntu-21-10-ldac/)。

按照博客安装完成后，我的蓝牙设置选项中并无 AAC 编码可选。阅读 [Gist：Enable PipeWire on Ubuntu 22.04](https://gist.github.com/the-spyke/2de98b22ff4f978ebf0650c90e82027e) 发现 AAC 支持需要使用 [PPA：pipewire-extra-bt-codecs](https://launchpad.net/~aglasgall/+archive/ubuntu/pipewire-extra-bt-codecs)，按说明完成安装后，就可以选用 AAC 编码了。虽然监控显示蓝牙传输仍只有 30 KB/S，但音质已经好很多了。

<!-- prettier-ignore-start -->
??? info "参考"
    
    * [知乎：如何让Ubuntu系统支持LDAC，APTX，AAC编码（提升蓝牙音质）](https://zhuanlan.zhihu.com/p/132409283)
    * [Bilibili：耳机性能基础自测](https://www.bilibili.com/video/BV16t411N7tS/)，可以测试你的蓝牙连接性能有多好。
<!-- prettier-ignore-end -->

### 



## 参考资料

什么？你说不够你看！这里还有一些大佬调教他们的 Linux 系统的记录，可以看一看：

- [Manjaro Linux 踩坑调教记录](https://prinsss.github.io/setting-up-manjaro-linux/)

