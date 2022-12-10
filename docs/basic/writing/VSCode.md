---
tags:
  - Ongoing
---

# VSCode

VSCode 是一款强大的编辑器，好好掌握它的使用能极大提高生产力。

## 快捷键

我在 VSCode 中使用 Vim 插件映射快捷键，因此这里不记录关于编辑操作的快捷键。详见 [Vim](Vim.md)。

!!! danger
    安装 Vim 插件后，VSCode 自己的 ++ctrl++ 的快捷键（特别是 ++ctrl+k++ 系列）基本都不再可用。以下表格中也略去了那些快捷键。

> From: [VSCode Shortcuts for Windows](https://code.visualstudio.com/shortcuts/keyboard-shortcuts-windows.pdf)

* 窗口和设置

| 组合                  | 功能                                                    |
| --------------------- | ------------------------------------------------------- |
| ++ctrl+shift+p++      | 命令面板                                                |
| ++ctrl+p++            | 快速打开文件                                            |
| ++ctrl+shift+n++      | 新的实例/窗口（这和简悦的快捷键冲突，请关闭简约快捷键） |
| ++ctrl+shift+w++      | 关闭实例/窗口                                           |
| ++ctrl+comma++        | 用户设置                                                |
| ++ctrl+k++,++ctrl+s++ | 快捷键设置（不可用）                                    |

* 窗口

| 组合                                           | 功能                   |
| ---------------------------------------------- | ---------------------- |
| ++ctrl+shift+e++                               | 文件导航栏聚焦         |
| ++ctrl+shift+f++                               | 文件搜索栏             |
| ++ctrl+shift+j++                               | 展开文件详细搜索栏     |
| ++ctrl+shift+h++                               | 文件替换栏             |
| ++ctrl+alt+enter++ | 确认替换操作 |
| 上面这些东西，应该在熟练Vim后转而使用Vim的方法 | 当然，使用 VSCode 也能有全局更改这样方便的能力 |
| ++f5++                                         | 调试                   |
| ++shift+f5++                                   | 停止调试               |
| 窗口布局                                       |                        |
| ++ctrl+tab++                                   | 切换tab                |
| ++ctrl+shift+t++                               | 打开关闭的文件         |
| ++shift+alt+0++                                | 切换纵向、横向排列     |
| ++ctrl+backslash++                             | Split editor           |
| ++ctrl+shift+v++                               | Open Markdown preview  |
| ++ctrl+shift+page-up++                         | Move editor left/right |
| 文档                                           |                        |
| ++shift+alt+f++                                | Format document        |
| 内置终端                                       |                        |
| ++ctrl+grave++                                 | 展示终端               |
| ++ctrl+shift+grave++                           | 新终端                 |
| ++ctrl+arrow-up++                              | 滚动到上下个命令       |
| ++shift+page-up++                              | Scroll page up/dow     |