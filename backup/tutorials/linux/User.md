# 用户身份与权限

## 基本命令

- `id` 显示用户的详细信息

## sudo

### `/etc/sudoers`

The **sudoers file** is a file Linux and Unix administrators use to allocate system rights to system users.

不同 Linux 发行版的 `sudoers` 文件有微小差异。比如 Fedora 中没有 `sudo` 用户组，Ubuntu 和 Debian 会自动创建。

允许用户组成员无密码使用 `sudo` 可以这样做：`%group ALL=(ALL) NOPASSWD: ALL`
