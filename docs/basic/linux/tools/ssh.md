---
tags:
  - Todo
---

# ssh: OpenSSH remote login client

*   OpenSSH（OpenBSD Secure Shell）: 

## 基本用法

>   From: MIT 6.NULL

`ssh` 最基本的用法就是远程登陆、远程执行命令、文件传输。

* 远程登陆：`ssh username@server`
* `ssh` 支持 **管道**。你可以把本地输出传送到远程主机，也可以把远程主机的输出传送到本地：`ssh username@server ls | grep PATTERN`

使用 `ssh-key` 可以免密登陆：

* 使用 `ssh-keygen` 生成密钥：

    ```bash
    ssh-keygen -a 100 -t ed25519 -f ~/.ssh/id_ed25519
    ```

    * `-a` 指定了迭代次数
    * `-t` 指定了加密方法，常用 `rsa`，近来推荐 `ed25519`
    * `-f` 指定了密钥文件的存储位置
      !!! danger
        应当为密钥指定密码，防止他人获取密钥文件后直接使用。
    * `-p` 更改密钥密码
    * `-y` 读入一个私钥，输出一个公钥。用于验证是否存在密钥。

* 使用 `ssh-copy-id` 将密钥添加到远程主机

  ```bash
  ssh-copy-id -i .ssh/id_ed25519 foobar@remote
  ```

  * 不指定参数将添加所有密钥
  * `-i` 指定密钥文件
  * `-p` 指定端口

使用 `SSH` 

* 使用 `ssh-agent` 可以暂存解密的密钥
    * `ssh-agent` 将解密的密钥暂存在内存中，直到指令删除或进程结束。
