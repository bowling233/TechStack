# Syncthing

在 Linux 服务器上使用 Syncthing

## 安装

按照[官方教程](https://apt.syncthing.net/)安装 Syncthing 的 APT 源。

### 新建用户

使用 `root` 用户运行 `syncthing` 是不合适的，应当创建专门的用户。注意，应当为该用户创建家目录，否则 Syncthing 将因为无处存放配置文件而启动失败。

```bash
useradd --create-home syncthing
```

按照正常方式新建名为 Syncthing 的用户，分配 `~` 作为文件存储目录。

### 配置 Syncthing 服务

执行以下命令将为指定用户设置 Syncthing 服务。

```bash
systemctl enable syncthing@username.service
```

服务默认监听本地端口 `127.0.0.1:8384`。你可以更改配置文件（`$HOME/.config/syncthing/`），使其监听公网地址，或者修改 service 文件（一般存放在 `/etc/systemd/system/multi-user.target.wants/syncthing@syncthing.service`），添加 `-gui-address="0.0.0.0:8384` 参数。但出于安全性考虑，应当使用 SSH 端口转发进行安全的访问。

```powershell
ssh -L 本地端口:localhost:远程端口（默认为8384） username@host
```

### 在服务器防火墙开放 `22000` 端口

<!-- prettier-ignore-start -->
!!! tip
    
    一定要记得在服务器防火墙开放 `22000` 端口。
<!-- prettier-ignore-end -->

Syncthing 默认监听该端口。如果未开启防火墙，则连接状态一般显示为“中继连接”，此时速度非常之慢。开放端口后，一般能够直接建立广域网 TCP 连接。

### 在不同系统之间同步文件

<!-- prettier-ignore-start -->
!!! warning "兼容性问题"
    
    在不同系统之间同步文件可能会出现兼容性问题，特别是嵌套 Git 仓库时，很有可能碰到 CRLF 和 dubious ownership 问题。
<!-- prettier-ignore-end -->

记得为所有跨系统同步的文件夹在所有客户端上都勾选“忽略文件权限”选项。勾选时，如果出现 dubious ownership 错误，可以设置 `git config core.fileMode false` 让 Git 忽略文件模式的改变。注意，该更改可能造成安全性问题，比如基于项目中的二进制文件执行权限等。在重要的项目中谨慎操作。

## 杂项

参考资料：

-   [官方配置文档](https://docs.syncthing.net/users/config.html)
-   [如何在 Debian 11 上安装 Syncthing 远程文件同步软件](https://0xzx.com/2022020423502061657.html)
-   [syncthing-faq](https://www.mankier.com/7/syncthing-faq)
-   [syncthing 使用 nginx 反代理，绑定域名访问](https://www.wenjinyu.me/syncthing-accesses-domain-names-through-nginx-anti-proxy/)


### 忘记 GUI 密码

-   停止 syncthing 服务
-   `syncthing generate --gui-password=myNewPassword --gui-user=newUserName`
-   重新启动 syncthing

或者你可以在 syncthing 的配置文件 `config.xml` 中进行更改：

```xml
<gui enabled="true" tls="false" debugging="false">
   <address>127.0.0.1:8384</address>
   <user>syncguy</user>
   <password>[protected]</password>
   <apikey>[protected]</apikey>
   <theme>default</theme>
</gui>
```
