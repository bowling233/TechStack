# MkDocs

* [MkDocs 官方文档](https://www.mkdocs.org/)
* [MkDocs Material 官方文档](https://squidfunk.github.io/mkdocs-material/)

## Installation

按官方文档操作

## Overview

### File layout

* 主页文件命名为 `index.md` 或 `README.md` ，它的 url 就是 `/`
* 以 `.` 开头的文件将被忽略

### Command

指令以 `mkdocs` 开头

* `serve` 在本地打开测试服务器
* `build` 在 `site` 文件夹中存放构建好的网站
* `gh-deploy` 如果这是一个 git 仓库，使用该命令自动部署至 `gh-pages` 分支

### Configuration in `mkdocs.yml`

* 至少应当包含 `site_name`

* `nav` 定义进入全站导航栏的文件



















* MkDocs 决定文档标题的顺序：
  * `nav` 中的定义
  * `title` 元数据
  * 一级标题
  * 文件名

## Writing

### YAML 元数据

模板：

```yaml
---
title: My Document
summary: A brief description of my document.
authors:
    - Waylan Limberg
    - Tom Christie
date: 2018-07-10
some_url: https://example.com
---
```

* `template` 用于指定该页面使用的主题
* 

### Plugins: tags

```yaml
---
tags:
  - HTML5
  - CSS
---
```

