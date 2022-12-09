# :simple-smartthings: 杂项

* Syncthing 和 git 共用问题

参考 [Syncthing Forum](https://forum.syncthing.net/t/is-putting-a-git-workspace-in-a-synced-floder-really-a-good-idea) 上的帖子。只要不在设备间快速切换，就不会有问题。因为阿里云服务器无法直连 GitHub，我决定只在电脑的 Windows 系统上进行部署。

* Windows 安装 Python 环境

参考 [知乎](https://zhuanlan.zhihu.com/p/38603105) 的教程。官网下载 Python 安装包。注意，在 Windows 命令行中，所有 `python` 的命令都以 `py` 执行。安装 `pip` ：下载 pip 安装脚本，解压后运行 `py setup.py install`。完成安装后在系统 `PATH` 中添加 `pip` （在我安装完后已自动添加）。输入 `py -m pip --version` 返回版本号说明安装成功。

此后，所有 pip 的命令全部改成：`py -m pip <command>`，所有 Python 包的执行命令也改成以 `py -m` 开头。

> -m mod : run library module as a script (terminates option list)