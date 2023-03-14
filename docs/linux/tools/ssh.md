---
tags:
    - Todo
---

# ssh: OpenSSH remote login client

-   OpenSSH（OpenBSD Secure Shell）:

## 基本用法

> From: MIT 6.NULL

`ssh` 最基本的用法就是远程登陆、远程执行命令、文件传输。

-   远程登陆：`ssh username@server`。
-   `ssh` 支持 **管道**。你可以把本地输出传送到远程主机，也可以把远程主机的输出传送到本地：`ssh username@server ls | grep PATTERN`。

使用 `ssh-key` 可以免密登陆：

-   使用 `ssh-keygen` 生成密钥：

    ```bash
    ssh-keygen -a 100 -t ed25519 -f ~/.ssh/id_ed25519
    ```

    -   `-a` 指定了迭代次数。
    -   `-t` 指定了加密方法，常用 `rsa`，近来推荐 `ed25519`。
    -   `-f` 指定了密钥文件的存储位置。
        !!! danger
        应当为密钥指定密码，防止他人获取密钥文件后直接使用。
    -   `-p` 更改密钥密码。
    -   `-y` 读入一个私钥，输出一个公钥。用于验证是否存在密钥。

-   使用 `ssh-copy-id` 将密钥添加到远程主机：

    ```bash
    ssh-copy-id -i .ssh/id_ed25519 foobar@remote
    ```

    -   不指定参数将添加所有密钥。
    -   `-i` 指定密钥文件。
    -   `-p` 指定端口。

使用 `SSH` 拷贝文件的三种方法：

-   少量语句：`ssh + tee`，例如 `cat localfile | ssh remote_server tee serverfile`。
-   单个文件：`scp`，例如 `scp path/to/local_file remote_host:path/to/remote_file`。
-   多个文件：`rsync`，语法和 `scp` 类似，但是能够避免重复拷贝、支持断点续传（使用 `--partial` 参数）。

## 进阶用法

-   使用 `ssh-agent` 可以暂存解密的密钥
    -   `ssh-agent` 将解密的密钥暂存在内存中，直到指令删除或进程结束。

## 端口转发

> 预置知识：Linux 网络设备

很多软件常默认监听本地端口，因此我们通常要把远程主机上的端口转发到本地的端口。比如，远程主机上运行的服务器监听 `8888` 端口，我们可以使用 `ssh -L 9999:localhost:8888 foobar@remote_server` 来把远程主机上的 `8888` 端口转发到本地主机的 `localhost:9999` 上。下面的两张图直接解释了本地端口转发和远程端口转发的过程。

![Local Port Forwarding](https://i.stack.imgur.com/a28N8.png%C2%A0)

```bash
ssh -L [bind address:]port:host:hostport destination
```

![Remote Port Forwarding](https://i.stack.imgur.com/4iK3b.png%C2%A0)

```bash
ssh -R [bind address:]port:host:hostport destination
```

!!! question "两种转发方式的异同"

    如果远程主机上的端口已经被占用（比如在运行服务器程序），那么此时不应该运行远程端口转发，而应该将本地端口转发到远程主机。

    按下 ++ctrl+d++ （登出 Shell）可以结束端口转发。
