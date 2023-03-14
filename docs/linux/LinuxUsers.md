---
tags:
    - Doing
---

# Linux 用户

## 用户

-   一个用户想要登陆，它必须有什么？
    -   必要的文件、目录、权限、一个密码

Linux 一般有一下用户身份

| UID   | 类型   | 说明                                               |
| ----- | ------ | -------------------------------------------------- |
| 0     | root   | 管理员                                             |
| 1-999 | system | 默认服务由独立的系统用户运行，避免提权操作产生破坏 |
| 1000+ | user   | 管理员创建的普通用户                               |

## 用户组

用户的创建过程中

-   会自动创建一个同名的**基本用户组**
-   可以被归入**扩展用户组**

## 安全

为了保证安全，可以禁用 `root` 用户：`sudo passwd -l root`，解锁可再次使用

值得注意：

-   非 `root` 账户的 `$PATH$` 默认没有 `/sbin` 和 `/usr/sbin` ，无法执行一些管理工具。
-   使用[[../../../../TechStack/docs/basic/linux/LinuxTool/sudo]]时，`$PATH` 会加入一系列 `sbin` 目录

## 本地用户管理

-   `/etc/passwd`：用户清单
-   `/etc/shadow`：用户密码
-   `/etc/group`：群组

用户管理工具

-   `useradd` 添加用户

    -   常用参数 `-d(directory), -e(expire), -u(UID), -g(group), -G, -N, -s(shell)`

        -   分配 ID，设置默认 shell，在 `shadow` 文件中放置 `!` 来阻止无密码用户登陆，创建 home 目录（拷贝 `/etc/skel`，包括 `bash` 等启动文件）

        -   `useradd -g 1105 -c "Max R." max`：
        -   `useradd -s /sbin/nologin apache`：禁止登陆的用户
        -   `useradd -G sudo admin`：具有 sudo 组的用户

-   `userdel` 删除用户

    -   常用参数 `-f, -r`
        -   `userdel -r debian`：完全移除用户（包括 home 和邮箱目录）

-   `usermod` 修改用户信息

    -   常用参数 `-c(comment), -d, -m(move), -e, -g, -G, -L(lock), -U(unlock), -s, -u`
        -   `usermod debian -aG sudo`：将用户加入 sudo 组
        -   `usermod -e "12/31/07" max`：设置用户有效期

-   `passwd` 设置用户密码

    -   常用参数 `-l, -u, --stdin, -d(允许空密码）, -e(强制登录时修改密码), -S(密码是否锁定以及加密算法名称)`

-   `chpasswd` 批量修改用户密码
-   `id` 显示用户和组信息

组管理工具

-   `groupadd`
-
