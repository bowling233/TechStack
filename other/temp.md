# 临时笔记

## [HdrHistogram](https://hdrhistogram.github.io/HdrHistogram/)

Designed for recoding histograms of value measurements in latency and performance sensitive applications.

[HdrHistogram: A better latency capture method](https://psy-lob-saw.blogspot.com/2015/02/hdrhistogram-better-latency-capture.html)

## Prefetch

## VSCode

阅读源码时跳转：

| 跳转 | macOS | Windows |
| --- | --- | --- |
| 上一个光标位置 | ++ctrl+-++ | ++alt+right++ |
| 下一个光标位置 | ++ctrl+shift+-++ | ++alt+left++ |
| 定义 | ++F12++ | ++F12++ |

## APT

[Can I remove KDE software without uninstalling the Plasma desktop environment?](https://discuss.kde.org/t/can-i-remove-kde-software-without-uninstalling-the-plasma-desktop-environment/7826)

The packages kde-baseapps, kde-plasma-desktop, and kde-standard are meta-packages, designed solely to depend on a set of individual packages. Such as what makes up a complete desktop environment and set of applications (kde-standard), a minimal core set (kde-plasma-desktop), or even a subsection of components (kde-baseapps).

These meta-packages don’t include software, libraries, or files themselves. When you want to remove something that is included in one of these lists, it has to be removed as well as the app. Otherwise they will cause that app to be reinstalled the next time there is an update. It is OK for these to be removed, though it is usually a good idea to make sure that they are present when performing a distribution upgrade. Re-installing the top-level kde-standard would take care of that here., iirc.

As to Kwrite also being removed, that is because both Kate and Kwrite are two different forms of the same application, and all share the same bits, so they have set things to depend on each other here.

In your case here, kate is a core part of the metapackage kde-baseapps, which is required by kde-plasma-desktop, which is required by kde-standard. Confusing, yes. But so is accounting, which is sort of what I compare it to.

## 命令行工具

- `mc` Midnight Commander 文件管理

## Wake on LAN

https://superuser.com/questions/86576/how-does-wol-wake-on-lan-work

### Magic Packet 包格式

https://superuser.com/questions/1066619/what-is-a-magic-packet-for-waking-a-computer

https://web.archive.org/web/20141006072000/http://support.amd.com/TechDocs/20213.pdf

Wake on Magic Packet causes the network card to awaken the computer when it receives a magic packet. A packet is considered "magic" when it contains FF FF FF FF FF FF (six instances of the largest possible byte value) followed by sixteen instances of the card's six-byte MAC address. That sequence can appear anywhere within the frame, so the packet can be sent over any higher-level protocol. Usually, UDP is used, but sometimes raw frames with EtherType 0x0842 are used.

### 硬件支持选项

https://superuser.com/questions/205468/ethtool-wol-what-does-wake-on-physical-activity-actually-mean-and-how-can

p  Wake on phy activity
u  Wake on unicast messages
m  Wake on multicast messages
b  Wake on broadcast messages
a  Wake on ARP
g  Wake on MagicPacket(tm)
s  Enable SecureOn(tm) password for MagicPacket(tm)
d  Disable (wake on nothing).  This option clears  all  previous
   options.

## GDB

- 断点：

    ```text
    b function
    b +offset
    b -offset
    b linenum
    b filename:linenum
    b filename:function
    b *address

    info b

    clear
    clear function
    delete [breakpoints] [range..]
    # delete 2
    ```

## Vivado

Erro: 

```text
application-specific initialization failed: couldn't load file "librdi_commontasks.so": libtinfo.so.5: cannot open shared object file: No such file or directory
```

https://adaptivesupport.amd.com/s/question/0D52E00006hptD5SAI/installing-vivado-20181-on-fedora-28?language=en_US

```shell
sudo ln -s /lib/x86_64-linux-gnu/libtinfo.so.6 /lib/x86_64-linux-gnu/libtinfo.so.5
```

## genymotion

https://www.reddit.com/r/linux4noobs/comments/bj7ezk/genymotion_increase_internal_storage_space/

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

### Docker 原理

!!! quote

    - [A Deep dive into Docker Storage - Medium](https://medium.com/geekculture/docker-storage-1dd3db3ded4c)

- 镜像构建
    - Docker 镜像构建为前后端架构：Buildx 为客户端，BuildKit 为服务端。
- 存储
    - 默认情况
        - 位于 `/var/lib/docker`，卸载时不会自动清除。
        - 层次化结构，由 Image 层（只读）和 Container 层（运行时数据，可写）组成。如果需要修改 Image 层数据，采用 copy-on-write 方式。
        - 与容器强绑定，容器删除后数据也消失。
    - 持久化存储
        - Volume：
            - 在 `/var/lib/docker/volumes` 下创建，不随容器消失。
            - 可以放置在远端存储。
            - 使用 `docker volume` 命令操作，
        - Bind mount：
            - 挂载宿主机的文件系统。
            - 允许挂载 NFS（使用 Docker 自己的 NFS 驱动，即不需要在宿主机上挂载）。
- 网络
    - 网络对容器透明，它只能看到一个具有 IP 地址的网络接口、网关、路由表和 DNS 服务。
    - 在 Linux 上，Docker 使用 iptables 实现网络。目前有迁移到 nftables 的计划。
    - Docker 自动为 `FORWARD` 链添加 `DROP` 策略，阻止宿主机作为路由器。如果需要，应当手动添加规则。
    - 支持的网络驱动有：`bridge`（默认）、`host`、`none`、`overlay`、`ipvlan`、`macvlan`。
    - `bridge`：部署时建议使用用户定义的 `bridge` 网络。
        - 默认网桥 `bridge`：
            - 自动创建，容器默认连接到该网桥。
            - 容器间只能通过 IP 地址通信。需要使用 `--link` 参数在双方创建连接才能使用自动 DNS。
            - 必须停止容器才能移出默认网桥。
        - 用户定义 `bridge`：
            - 自动 DNS 功能：容器可以使用 IP 地址或**容器名**相互沟通。
            - 热插拔：不需要关闭容器即可移动到其他网络。

    !!! note "Compose 中的网络"

        Compose 会自动为应用创建一个网络，容器可以通过服务名相互访问。

    - `host`：
        - 端口映射不生效。
    - 端口映射：
        - Docker 使用 iptables 进行相关 NAT、PNAT 和 masquerade 操作。
        - 默认情况下所有外部主机都能访问公开端口，如果需要限制，需要自己写 iptables 规则。
        - IPv6 下可能配置为直连路由。
        - `-p host:docker`
- 容器
    - 重启策略：`no`、`always`、`unless-stopped`、`on-failure`。

### 基础

```shell
docker pull <image>
docker run --name <container_name> <image>
```

`compose.yaml`

命令：

```shell
docker compose up
docker compose down
docker compose logs
docker compose ps
```

```shell
docker compose up --detach
docker compose restart
docker compose down
docker compose logs
docker compose ps
docker compose pull
```

```yaml title="docker-compose.yml"
services:
  frontend:
    image: example/webapp
    ports:
      - "443:8043"
    networks:
      - front-tier
      - back-tier
    configs:
      - httpd-config
    secrets:
      - server-certificate

  backend:
    image: example/database
    volumes:
      - db-data:/etc/data
    networks:
      - back-tier
```


Refer to [riscv timer的基本逻辑](https://wangzhou.github.io/riscv-timer%E7%9A%84%E5%9F%BA%E6%9C%AC%E9%80%BB%E8%BE%91/) for RISC-V.

### Docker-Compose

本节重点讲解 Docker Compose v1 和 v2 的区别，以便在不同环境中迁移。[](https://docs.docker.com/compose/releases/migrate/)

- v2 版本将 compose 作为 docker 的子命令而非独立工具，能够直接使用 docker 根命令上相关的配置。
- v2 版本生成的容器名从 `_` 改为 `-` 连接，能够用于 DNS，在网络中方便地访问。v1 不行。

### API

/run/docker/docker.sock
/run/podman/podman.sock
/run/user/${UID}/podman/podman.sock
systemctl --user enable podman.sock
