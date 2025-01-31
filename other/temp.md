# 临时笔记






## Linux GUI

Debian 目前支持的桌面环境，除 KDE 和 Xfce 外，均 fork 自 GNOME，包括 LXDE、LXQT、MATE 和 Cinnamon 等。GNOME KDE 是未来的选择。

## 容器

### 软件包

Docker 官方和 Debian APT 的打包策略不同。

在 Debian APT 中，相关软件包说明如下：

- `docker.io` 守护进程
- `docker-cli` 命令行工具
- `docker-compose` 服务编排工具（独立命令 `docker-compose`）

在官方仓库，相关软件包如下：

- `docker-ce` 守护进程
- `docker-ce-cli` 命令行工具
- `docker-compose-plugin` 作为 Docker CLI 的插件（子命令 `docker compose`）

目前，Debian 源中的 `docker-compose` 仍然是 v1 版本（Python 编写），而官方仓库中的 `docker-compose-plugin` 是 v2 版本（Go 编写）。Debian 团队正在努力将 v2 版本打包到源中。最新进展可见 [Debian Bug Report](https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=1040417)。截止 2024 年 7 月，v2 版本的 Go 依赖处理仍在进行中。

OpenWRT 上的 docker-compose 也是 v1 版本。

