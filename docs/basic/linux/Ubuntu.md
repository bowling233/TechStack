---
tags:
  - Ongoing

---

# Ubuntu 日常使用指南

目前我在笔记本上使用 Ubuntu 作为主力系统。Ubuntu 一定是最容易上手和使用的 Linux 系统。深入使用了一段时间后，发现 Windows 上常用的软件都能在 Ubunut 上找到替代品。以下记录一下我做了哪些配置来提升 Ubuntu 的使用体验。

## 代理

我们首先要保证网络畅通，才能进行各种各样的配置。一些简单的命令可以通过设置 `clash` 代理来完成。

### Clash

不要 `apt isntall clash`，你会安装上一个好像是 Haskell 制作程序的东西。

我们将使用 Clash for Windows，这是一个基于 Clash 和 Electron 的 Windows、Linux 和 macOS 通用的 clash 客户端。

<!-- prettier-ignore-start -->
!!! info "参考资料"

    - [GitHub 主页：Clash for Windows](https://docs.cfw.lbyczf.com/)
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

    ``yaml
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

-   [QQ](https://im.qq.com/linuxqq/index.shtml)。推荐直接在 Ubuntu 应用商店中下载。目前 Linux QQ 界面十分简洁，基本功能足够完善。
-   [钉钉](https://page.dingtalk.com/wow/z/dingtalk/simple/ddhomedownlaod#/)。在官网下载 Linux 客户端，仅有 `deb` 安装包。使用体验与 Windows 版几乎一致。
-   [Typora](https://typora.io/#linux)。Typora 的 apt 源在国内无法解析（猜测是 `.io` 域名问题），安装过程的代理设置十分艰难。推荐直接下载 `deb` 安装包。没有 Windows 版的一体化界面。
-   [搜狗输入法](http://shurufa.sogou.com/linux)。中文输入功能完善，比 Ubuntu 自带输入法智能太多。
-   [emote](https://github.com/tom-james-watson/emote)。Linux 的 emoji 输入面板，挺方便的。
-   [Tabby](https://tabby.sh/)。目前我见过最好看、方便配置的跨平台终端，甚至提供了 [Web app](https://app.tabby.sh/)。GNOME 自带的终端在使用 zsh 的 powerlevel10k 主题时可能出现问题，tabby 则对各种功能都提供了完善的支持，比如可以保管 ssh 秘钥、记录上次退出时的终端状态等，资源占用也不高。
-   [Lollypop](https://wildskyf.github.io/lollypop-web/)。音乐播放器，比自带的 RhythomBox 好看很多，对于专辑等也有不错的管理。

<!-- prettier-ignore-start -->
!!! note "更多软件"

    这些软件也不错，但并不推荐。它们的功能较少或不太完善、界面不够美观或很久没有更新。

    - [Amberol](https://flathub.org/apps/details/io.bassi.Amberol)。音乐播放器，极致简洁，比 Lollypop 好看一些，但只支持播放列表，播放体验并不好。
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
??? info "什么是 `.desktop` 文件？"

    - [](https://specifications.freedesktop.org/desktop-entry-spec/latest/index.html#introduction)

    Both the KDE and GNOME desktop environments have adopted a similar format for "desktop entries", or configuration files describing how a particular program is to be launched, how it appears in menus, etc. It is to the larger community's benefit that a unified standard be agreed upon by all parties such that interoperation between the two environments, and indeed any additional environments that implement the specification, becomes simpler.
<!-- prettier-ignore-end -->

把需要自动启动的 `.desktop` 文件拷贝到 `~/.config/autostart` 即可实现自动启动。

<!-- prettier-ignore-start -->
!!! info "参考资料"

    [Ask Ubuntu: Extract icon from appimage](https://askubuntu.com/questions/1115321/extract-icon-from-appimage)。
    [Ask Ubuntu: How can I add new autostart programs in Lubuntu?](https://askubuntu.com/questions/81383/how-can-i-add-new-autostart-programs-in-lubuntu)
<!-- prettier-ignore-end -->

## 使用技巧

-   窗口飘到屏幕外去了

按 ++alt+space++ 跳出窗口选项菜单。参见 [StackOverflow: Window appears off screen on ubuntu](https://stackoverflow.com/questions/12477435/window-appears-off-screen-on-ubuntu)。
