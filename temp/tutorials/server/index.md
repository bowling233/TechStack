# 云服务器综合教程

<!-- prettier-ignore-start -->
!!! abstract
    
    与云服务器有关的内容散布在各个分区的笔记中，这里提供一些零散点的汇总以及相关笔记的索引。
<!-- prettier-ignore-end -->

## 书籍

-   [Linux 应用大全：服务器架设](../../books/LinuxServer.md)

## 第一件事

服务器到手的第一件事：创建安全的管理员账户，禁用 `root` 账户的密码登录。

### 创建用户账户并分配权限

```bash
useradd --create-home --groups {{group1,group2,...}} --shell {{path/to/shell}} {{username}}
```

要让该用户有 `sudo` 权限，将其加入到 `root` 或 `sudo` 用户组中。

### SSH 配置

<!-- prettier-ignore-start -->
!!! info "参考资料"
    
    - [SSH config file for OpenSSH client](https://www.ssh.com/academy/ssh/config)
<!-- prettier-ignore-end -->

-   向 `/root/.ssh/authorized_keys` 添加本地主机的 SSH 密钥

-   在 `/etc/ssh/sshd_config` 中禁用 `root` 账户的密码登录

```title='sshd_config'
PermitRootLogin = prohibit-password
```

-   重启 `sshd` 守护进程

```bash
sudo systemctl restart ssh.service
sudo systemctl restart sshd.service
```

## 搭建各种服务

-   [Syncthing 服务器搭建](Syncthing.md)
-   [Calibre-Web 电子图书馆](Library.md)

## 注意事项

-   一般会为每个部署的 Web 应用创建一个单独的用户。

## 参考资料

-   [Nginx 极简教程](https://dunwu.github.io/nginx-tutorial/#/nginx-quickstart)
