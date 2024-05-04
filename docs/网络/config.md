# 网络配置

## 基础

只需要知道最基础的手动配置即可，成功连上网络后即可使用 NetworkManager 等自动化工具。

=== "Debian"

    - 网络接口：`/sys/class/net`
    - 网络接口配置：`/etc/network/interfaces`

    ```text title="/etc/network/interfaces"
    auto eth0
    allow-hotplug eth0
    iface eth0 inet static
        address 192.168.1.2/24
        gateway 192.168.1.1
    iface eth0 inet manual
        pre-up ifconfig $IFACE up
        post-down ifconfig $IFACE down
    iface eth0 inet6 dhcp
    iface eth0 inet6 auto
    ```

    - 域名解析：`/etc/resolv.conf`
        - 如果使用 `resolvconf`，则变成一个符号链接。
    - DHCP 客户端：`/etc/dhcp/dhclient.conf`
    
    !!! warning "坑点"

        > Some outdated guides instruct to restart the networking service to apply changes to /etc/network/interfaces, however this was deprecated because it is possible that not all interfaces will be restarted. Instead use ifup and ifdown to apply changes to each interface.

        重启 `networking` 服务可能导致部分接口未重启。

=== "RedHat"

## NetworkManager

!!! info "[RedHat: Becoming Friends with NetworkManager](https://www.redhat.com/sysadmin/becoming-friends-networkmanager)"

> attempts to make networking configuration and operation as painless and automatic as possible

NetworkManager 是一个系统网络服务，用于自动检测和配置网络设备。它可以自动管理各种网络连接。

手动配置网络十分繁琐，且发行版之间有不同。NetworkManager 自动化程度更高，可移植性也更好。

!!! warning "如果已在 `/etc/network/interfaces` 中配置了网络接口，NetworkManager 不会进行管理。"

NetworkManager 将网络抽象为设备和连接：

- 设备：物理设备，如网卡。
- 连接：设备的配置，如 IP 地址、DNS 服务器等。可以创建多个连接，但每个设备只能有一个连接。配置保存在 `/etc/NetworkManager/system-connections`

NetworkManager 提供多种交互方式：

- 命令行：`nmcli`
- 文本界面：`nmtui`
- 库：`libnm`
