# LinuxTools

## 帮助

### tldr

* 安装 `tldr` 后，首先需要运行 `tldr -r` 获取最新数据库

## 系统管理

* [[sudo]]
* [[ssh]]

用户管理工具见[[Linux用户]]

## 网络

* `ifupdown` 网络管理器： Debian 的默认管理器

### NetworkManager

Debian 最小安装不会携带 NetworkManager，GUI 安装则会

* `apt install network-manager`
* `nmcli`
* `nmtui`
* `systemctl status network-manager`