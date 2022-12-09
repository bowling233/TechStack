---
tags:
  - Done
---

# 代理

## Clash 和 proxychains

> 参考文章：[Clash on Linux](https://einverne.github.io/post/2021/03/linux-use-clash.html) 
> [proxychains](https://einverne.github.io/post/2017/02/terminal-sock5-proxy.html) 
> [GitHub: Clash for Linux](https://github.com/wanhebin/clash-for-linux)

由于某些原因，GitHub 在国内无法直接连接，服务器端也是这样。为了流畅使用 git ，需要为 Linux 系统配置代理。以 Clash for linux 为例：

1. 在项目 GitHub 首页，按照安装说明安装好 Clash。
2. 阅读教程，参考 sh 脚本内容得知：应当从服务商处获得 `config.yaml`，使用该配置文件启动 Clash。
3. 注意配置文件中 `socks` 的端口，在接下来 proxychains 的设置中需要配置到对应的端口。
4. 按教程修改 `proxychains.conf`，映射对应端口。
5. 在需要代理的命令前加上 `proxychains`，命令即可通过代理转发。

## hosts

因为使用 [GitHub: GitHub520](https://github.com/521xueweihan/GitHub520) 无效，所以才使用了代理的方法。在该 hosts 中，GitHub 的 IP 地址为 `20.205.243.166`，我始终无法连接。使用代理，发现我可以连接的 IP 是：`192.30.255.112`。这时，在 hosts 文件中配置好 IP，也可以不使用代理。