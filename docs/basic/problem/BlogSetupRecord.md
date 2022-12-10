# Blog 搭建记录

## 服务器配置

### 控制台

在[服务器控制台](https://home.console.aliyun.com/home/dashboard/ProductAndService)，检查以下端口的开启情况：

* `22` 用于 `SSH` 远程登陆
* `80` 用于 `HTTP` 访问

> 有些情况下你可能需要重置云盘等，参考服务器手册即可

### 系统配置

使用 SSH 远程登陆 root 用户，第一件事是：`apt update && apt upgrade`

* `update` 获取所有源的包信息。如果不执行该命令，你会发现 apt 提示找不到软件。

接下来，安装常用的工具。我一般会安装：

* `fish`
* `tldr`
* `git`

## 本地 Hexo 配置

注意：Hexo 的这些配置应当在你写博客的本地机器上进行，而不是你部署博客网站的服务器上进行。

参考[Hexo官方文档](https://hexo.io/zh-cn/docs/)完成安装

### npm 换源

换元的命令是：`npm config set registry http://mirrors.cloud.tencent.com/npm/ --global`

在本地机器上配置 npm 环境时我被网络环境折腾了好久。可以多积累一些软件源，这样方便根据不同的网络环境更换：

* 官方源：`https://registry.npmjs.org/`
* 淘宝源：`https://registry.npm.taobao.org/`
* cnpm 源：`https://r.cnpmjs.org/`
* 腾讯源：`https://mirrors.cloud.tencent.com/npm/`
* npmMirror源：`https://skimdb.npmjs.com/registry/`

当然，你也可以安装 `nrm` 来管理你的 npm 源，命令是 `npm install -g nrm` 。但首先要能连上一个 npm 源。`nrm ls` 命令列出一些可用源。

> 还有可能出现的错误：`UNABLE_TO_VERIFY_LEAF_SIGNATURE`
>
> http://stackoverflow.com/questions/20747817/error-unable-to-verify-leaf-signature-phonegap-installation
>
> 解决：**npm config set strict-ssl false**
>
> 还是可能出错，这时只需把上面的所有源换成非https即可
>
> 再继续出错，则在各项 config 的命令后面加上 `--g`

## Hexo 和 git 自动部署配置

本节将涉及Linux系统权限和用户管理、SSH密钥等内容。

> 参考教程：[Hexo部署到阿里云服务器ECS](https://blog.csdn.net/qq_38733240/article/details/108140565)

### 分配 git 用户

分配 git 用户时，目录的权限非常重要。

* git 的家目录

在家目录中，特别要注意使用 root 用户创建的文件。比如我使用 root 用户创建了 .ssh 配置文件免密钥登陆，但权限并没有给 git 用户，因此远程密钥登陆持续失败。配置好密钥登陆后，可以把 git 用户的密码改成随机生成的强密码，保证安全。也可以配置取消密码登陆：

```
# /etc/ssh/sshd_config
PasswordAuthentication no//禁止密码登陆
ChallengeResponseAuthentication no
```

* git 的工作目录

在自动部署的过程中， git 用户会操作两个目录：网站目录和仓库目录。这两个目录的权限都要给到：

```bash
chown -R git:git /path/to/repo
chmod -R 755 /path/to/repo
```