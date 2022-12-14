---
tags:
  - Ongoing
---

# VSCode

VSCode 是一款强大的编辑器，好好掌握它的使用能极大提高生产力。以下仅记录自己经常使用的功能。

## 配置

在 Linux 中配置 VSCode 简单而自然，请参考 [Dev on WSL](https://dowww.spencerwoo.com/3-vscode/3-0-intro.html)。如果你仍然希望在 Windows 上编译，那么请参考 [知乎：Visual Studio Code 如何编写运行 C、C++ 程序？](https://www.zhihu.com/question/30315894/answer/154979413)。

以下是一些配置用快捷键：

| 组合                   | 用途           |
| ---------------------- | -------------- |
| ++ctrl+k++, ++ctrl+s++ | 查询快捷键映射 |
| ++ctrl+shift+p++       | 命令面板                                                |
| ++ctrl+comma++         | 用户设置                                                |

### 配置细节：关于 `.vscode` 中的那些文件

??? question "什么是 build 和 compile？"
    Build（构建）通常包含了将源代码转换为可执行文件的整个过程。其中 **包括编译**、链接和汇编从而生成可供你在自己的系统上运行的可执行二进制文件。它是将编译和链接以及其它可能的任务（如创建安装程序）组合在一起的一系列操作。其中，“链接”是指将对象代码与库组合为原始可执行文件的行为。

在 VSCode 中，build 被译为“生成”。

* `tasks.json`：用于编译，参考官方文档 [Tasks](https://code.visualstudio.com/docs/editor/tasks)。

Tasks 的目的是将各种自动化项目构建系统（如 Make 等），通过命令行聚合到 VSCode 中。

在 VSCode 中配置的一般顺序如下：首先在 `tasks.json` 中编写自己的 task，然后在命令面板中选择 **Configure Default Build Task** 设置某个 task 为默认选项，此后便可以使用 ++ctrl+shift+b++ 执行任务。

???+ info "配置文件详解"
    ```json
    {
    "version": "2.0.0",
    "tasks": [
        {
            "type": "cppbuild",
            "label": "C/C++: gcc.exe 生成活动文件",
            "command": "C:\\mingw64\\bin\\gcc.exe",
            "args": [
                "-fdiagnostics-color=always",
                "-g",
                "${file}",
                "-o",
                "${fileDirname}\\${fileBasenameNoExtension}.exe"
            ],
            "options": {
                "cwd": "${fileDirname}"
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": "build",
            "detail": "调试器生成的任务。"
        }
      ]
    }
    ```
    这是 VSCode 默认生成于 Windows 中的执行文件。还是比较容易读懂它的作用是什么的。为了可移植性，我将 `command` 更改为 `gcc`，经过测试在 Windows 和 Linux 上均可用。其他东西基本不需要动，接下来你需要学习 [gcc](../linux/tools/gcc.md)。


在 VSCode 文档中看到，一个 task 能基于不同系统定义不同操作。我已经在自己的配置文件中为 Linux 和 Windows 做好了配置。

!!! note
    我的配置文件中没有特定绝对路径，这是为了方便移植，不用更改文件。这依赖于系统变量 PATH 的设定。请将其设定好，并在命令行中测试。

    在 Bash 中，PATH 没有自动包含工作目录，需要加 `./` 来运行程序，甚至还要赋予执行权限；而 Windows 会自动包含。


* `launch.json`：用于调试（执行编译好的文件），参考官方文档 [Debug](https://code.visualstudio.com/docs/editor/debugging)。

VSCode 利用扩展来支持调试。

* 综上，程序编译、运行、调试的快捷键：

| 组合             | 用途 |
| ---------------- | ---- |
| ++ctrl+shift+b++ | 运行生成任务 |




### 插件

必备插件：

* MS-CEINTL.vscode-language-pack-zh-hans
* formulahendry.code-runner
    * 请在 `settings.json` 配置：`"code-runner.runInTerminal": true, // 设置成false会在“输出”中输出，无法输入`

语言依赖：

* C/C++/C#
    * `ms-vscode.cpptools`
* Java
* Markdown/Latex
    * `yzhang.markdown-all-in-one`
* YAML
    * `redhat.vscode-yaml` 
* 汇编
    * `13xforever.language-x86-64-assembly` 为 x86 系列汇编语言提供支持。

Web 开发一条龙：

* HTML/CSS
    * `esbenp.prettier-vscode` 所有 Web 开发人员都应当使用这个代码格式化插件！
* JavaScript
    * `mgmcdermott.vscode-language-babel` 为现代 JavaScript 提供更好的高亮，适用于 React.js 等。
* Edge 支持
    * 请参考 [知乎：用于 VS Code 的 Edge 开发工具扩展太棒了](https://zhuanlan.zhihu.com/p/567519551)
    * `ms-edgedevtools.vscode-edge-devtools`
    * `ritwickdey.LiveServer`

以下是我喜欢的插件、主题等：

* `adpyke.codesnap` 代码图片
    * `pnp.polacode` 有点问题，兼容性不是很好
* `Equinusocio.vsc-community-material-theme` 非常好看的主题
    * `equinusocio.vsc-material-theme-icons` 配套图标
* `ms-vscode.hexeditor` 二进制编辑器


## 快捷键

我在 VSCode 中使用 Vim 插件映射快捷键，因此这里不记录关于编辑操作的快捷键。详见 [Vim](Vim.md)。

!!! danger
    安装 Vim 插件后，VSCode 自己的 ++ctrl++ 的快捷键基本都不再可用。但是，Vim 很多 Ctrl 类快捷键非常不常用，因此可以配置 Vim 插件不处理该类快捷键，为使用 VSCode 本身的快捷键提供方便。我的配置如下

    ```json
        "vim.handleKeys": {
        "<C-a>": false,
        "<C-f>": false,
        "<C-k>": false}
    ```

> From: [VSCode Shortcuts for Windows](https://code.visualstudio.com/shortcuts/keyboard-shortcuts-windows.pdf)

* 非常常用，一定要掌握

| 组合                   | 功能                                                    |
| ---------------------- | ------------------------------------------------------- |
| 命令和窗口操作         |                                                         |
| ++ctrl+p++             | 快速打开文件                                            |
| ++ctrl+shift+n++       | 新的实例/窗口（这和简悦的快捷键冲突，请关闭简悦快捷键） |
| ++ctrl+shift+w++       | 关闭实例/窗口                                           |
| ++ctrl+tab++           | 切换tab（在同一组中）                                   |
| ++ctrl+f4++ | 关闭 tab |
| ++ctrl+1++             | 切换组（Vim 分割窗口将新建组）                          |
| ++ctrl+k++, ++ctrl+w++ | 关闭组                                                  |
| 文档操作               |                                                         |
| ++shift+alt+f++        | 格式化文档                                              |
| 程序运行与调试         |                                                         |
| ++ctrl+alt+n++         | 运行代码（Run code）                                    |

* 比较常用

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
|                                                |                                                |
| ++ctrl+shift+t++                               | 打开关闭的文件         |
| ++shift+alt+0++                                | 切换纵向、横向排列     |
| ++ctrl+backslash++                             | Split editor           |
| ++ctrl+shift+page-up++                         | Move editor left/right |
| 文档                                           |                        |
| 内置终端                                       |                        |
| ++ctrl+grave++                                 | 展示终端               |
| ++ctrl+shift+grave++                           | 新终端                 |
| ++ctrl+arrow-up++                              | 滚动到上下个命令       |
| ++shift+page-up++                              | Scroll page up/dow     |