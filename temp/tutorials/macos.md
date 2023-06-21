# macOS 使用笔记

## 使用习惯

初次使用 macOS 时需要注意以下几个点，习惯之后能大大提高效率：

-   **菜单栏（Menu Bar）**：所有软件的选项都在菜单栏中，不习惯的时候常常会觉得找不到软件的配置选项。
-   **触摸板手势**：基础手势已经很好用，在网上还可以找到教程开启更多手势，强烈推荐开启三指拖拽功能。
-   **Spotlight**：按住 ++cmd+space++ 可以打开。这是 macOS 自带的搜索功能，可以快速打开应用程序和文件。
-   **键盘**：
    -   macOS 的快捷键与其他系统有些许不同，比如 ++cmd+x++ 不再能够剪切文件，而应当用 ++cmd+c++ 复制文件，然后用 ++cmd+opt+v++ 粘贴文件。可以在网上查找 macOS 常用快捷键的教程。
    -   MacBook 上的 ++cmd++ 键基本替代了 ++ctrl++ 的功能，而 ++ctrl++ 在各种终端中仍能正常使用。
-   在访达中使用空格预览文件：选中文件后按空格键即可预览文件，再按一次空格键即可关闭预览。访达的预览功能能预览大多数常用文件，打开速度非常快。在不需要编辑文件时是非常好的选择。
-   配置你的访达：在访达工具栏右键可以配置工具栏，加入如删除文件等常用按钮可以提升效率。


## 终端

在 Mac 上使用第三方终端的体验都很不错，个人觉得好用的有几个：

-   [iTerm2](https://iterm2.com/) 为 macOS 定制的终端，可配置的选项很多，适合喜欢折腾的人。
-   [Tabby](https://tabby.sh/) 一个跨平台终端，简单易用，颜值也很高。
-   [Termius](https://termius.com/) 跨平台 SSH 客户端，全面支持各类远程操作（包括端口转发、密钥同步、自动补全等）。

使用 Ubuntu 后会很怀念 ++ctrl+alt+t++ 打开终端的快捷键。在 Mac 上也能为各种自动化操作设置快捷键，见 [知乎：macOS 中怎样快速调出终端？](https://www.zhihu.com/question/20692634)。当然也可以使用 ++cmd+space++ 通过 Spotlight 搜索快速打开终端。

## 必备工具

-   [Rectangle](https://rectangleapp.com/) 快捷键管理窗口。免费版功能已经足够。
-   [Keka](https://www.keka.io/en/) 压缩解压缩工具。访达仅支持 zip 格式，Keka 支持更多格式。
    -   为了获得最好的体验，请进行以下设置（软件中有详细步骤指引）：启用访达扩展、设置为默认工具、给予主文件夹和外部卷访问权限。
-   [IINA](https://iina.io/) macOS 上最好的视频播放器。
-   [Cheetsheet](https://www.mediaatelier.com/CheatSheet/) 快捷键备忘录。按住 ++cmd++ 键不放，可以显示当前应用程序的快捷键。

## KISS 原则

个人认为，使用 macOS 时应当遵守 **Keep It Simple, Stupid** 原则。macOS 本身就是一个很简洁的系统，不需要过多的配置和软件，否则会降低效率。

以我的日常使用为例：

-   出门携带 MacBook Air + MatePad，它们的续航足以让我持续工作一整天。需要工作的时候使用 MacBook，需要阅读和思考时使用 MatePad。
-   宿舍放置一台 Windows 主机，作为远程桌面备用。台式 Windows 倒是不用 Keep Simple，而是把各种环境都配全，作为一个综合的工作站，毕竟等到需要使用的时候再配置总是异常煎熬。
-   备用一台双系统笔记本，Ubuntu 作为主力系统，Windows 作为备用系统，仅装配 Office 等基础软件。需要用到这两个系统时携带（如 Vivado 等软件）。

## Homebrew

Homebrew 相当于 Linux 中的包管理器，可以方便地安装、卸载、更新软件包。

-   [Homebrew Documentation](https://docs.brew.sh/)
-   [A Beginner’s Guide to Homebrew. | Medium](https://medium.com/@kkworden/a-beginners-guide-to-homebrew-4b665956a74)

简单做一些笔记：

-   Homebrew 中的几个用语：`tap` 是一个 GitHub 仓库，当它被 `tapped` 时就可以从该仓库安装软件包；`cellar` 是软件包安装在本地的位置；`formula` 是一个软件包或库，Homebrew 会保留其的多个版本；`cask` 是一个应用程序。

以下是基本命令：

-   `brew install <formula>`：安装软件包
-   `brew uninstall <formula>`：卸载软件包
-   `brew search <formula>`：搜索软件包
-   `brew list`：列出已安装的软件包
-   `brew update`：更新 Homebrew
-   `brew upgrade`：更新已安装的软件包
-   `brew cleanup`：清理旧版本的软件包
-   `brew tap <user>/<repo> <URL>`：添加 tap

## 更多小技巧

- [在 Mac 上玩转 PDF 文件的技巧](https://www.bilibili.com/video/BV1ss4y1A7kz)
    - 讲解了使用预览工具进行 PDF 页面管理、**签名**等操作的方法。

## 问题解决

- 快捷键失效

通常是某些软件快捷键冲突了。比如 GoldenDict 默认开启了 ++cmd+c+c++ 翻译剪贴板中内容的快捷键，这会导致全局的 ++cmd+c++ 失效。

- IINA 音量规格化

设置-音量-最大音量：最高可以扩大到 1000%。参见：[GitHub Issue](https://github.com/iina/iina/issues/2511)

