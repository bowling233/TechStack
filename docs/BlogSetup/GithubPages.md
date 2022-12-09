---
tags:
  - Done
---



# GitHub Pages

* [GitHub Pages](https://pages.github.com/)

## Overview

GitHub Pages 分为两种：**用户或企业网站** 和 **项目网站**。一个 GitHub 账户可以有一个 **用户或企业网站** 和无限个 **项目网站**。

### 用户或企业网站

* 域名是：`username.github.io`，仓库名同域名
* 网站直接部署在仓库内的 `master` 分支

### 项目网站

* 地址是：`username.github.io/repo`
* 可以选择其中的一个分支部署

## Custom Domain

* [GitHub Docs](https://docs.github.com/en/pages/configuring-a-custom-domain-for-your-github-pages-site)

* GitHub Pages 支持两种域名：子域名 `xxx.example.com` 和顶级域名（Apex Domain）`example.com`。

* 当你为**用户或企业网站**配置了自定义域名后，你的所有项目域名前缀也会被更换。比如，自定义域名为 `www.example.com`，则子项目域名变为 `www.example.com/sub`

!!! note "与域名有关的问题"
        * 子域名是通过 DNS 服务器的 `CNAME` 记录配置的。
        * 顶级域名是通过 DNS 服务器的 `A` 记录（ALIAS）配置的。
        * DNS 改变可能花费 24 小时才生效。

### Configuration

* 确保你在 **配置DNS服务之前** 向 GitHub Pages 添加自定义域名。

### Verification

* 按照 GitHub Pages 的指导，在 DNS 解析中给域名添加 TXT 记录，然后验证。
