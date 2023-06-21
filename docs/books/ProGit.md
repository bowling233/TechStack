---
tags:
  - Ongoing
---

# 精通 Git

ProGit 读书笔记

## Ch1. 入门

<!-- prettier-ignore-start -->
!!! abstract
    
    Git 是什么？
<!-- prettier-ignore-end -->

- Git 由 Linux 社区开发，能有效地处理 Linux 内核这样的大型项目。
- Git 将数据作为一个**快照流**。后续章节会讲解快照流的优势。
- Git 的大部分操作在本地进行，使用 SHA-1 散列（40 个十六进制字符）校验文件。
- **Git 的大部分操作只增加数据**。

### 三种状态

- Committed
- Modified
- Staged

### 三种区域

- Git 仓库（项目元数据、对象数据库）
- 工作目录（从仓库中单次检出的一个版本）
- 暂存区（Git 目录中的一个文件）

### 基础设施

Git 有三种层次的配置

- `/etc/gitconfig`：系统中所有用户和参数的值，用 `--system` 修改
- `~/.gitconfig` 或 `.config/git/config`：用户，用 `--global` 修改
- `.git/config`：单个仓库

每一级覆盖上一级设置。

安装后做的第一件事是设置用户名和电子邮件：`user.name` 和 `user.email`。

- `core.editor` 编辑器

- `git config --list` 列出 Git 找到的所有变量。重复出现的值会使用最后一个。
- `git config <key>` 查看某个键的值。

### 获取帮助

- `git help <verb>`
- `git <verb> --help`
- `man git-<verb>`

## Ch2. Git 基础
