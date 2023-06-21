# VSCode

<!-- prettier-ignore-start -->
!!! abstract

    **放弃 Dev-C++，转向 😎VSCode**，你就已经迈入了计算机学科的大门🥳。

    VSCode 是一款强大的**编辑器**，好好掌握它的使用能极大提高生产力。
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
!!! info "资料来源"
    
    - [VSCode 官方文档](https://code.visualstudio.com/docs)。
    - Visual Studio Code 权威指南（这本书大部分也是翻译官方文档）。
<!-- prettier-ignore-end -->

## 配置编程环境

使用 VSCode 的第一步应该就是配置语言环境了。这里给出一些参考资料，不详细介绍配置步骤。

<!-- prettier-ignore-start -->
!!! info "配置 C/C++ 编程环境"
    
    - Windows 系统：[知乎：Visual Studio Code 如何编写运行 C、C++ 程序？](https://www.zhihu.com/question/30315894/answer/154979413)。
    - 使用 WSL：[Dev on WSL](https://dowww.spencerwoo.com/3-vscode/3-0-intro.html)。
    - 使用 Linux：同上。
<!-- prettier-ignore-end -->

以下是一些配置用快捷键：

| 组合                   | 用途           |
| ---------------------- | -------------- |
| ++ctrl+k++, ++ctrl+s++ | 查询快捷键映射 |
| ++ctrl+shift+p++       | 命令面板       |
| ++ctrl+comma++         | 用户设置       |

`Code Runner` 插件提供了开箱即用的代码编译运行功能，只需按 ++ctrl+alt+n++ 即可运行，无需进行其他配置。

### 插件

必备插件：

-   中文语言包
-   Code Runner：一键运行代码
    -   请在 `settings.json` 配置：`"code-runner.runInTerminal": true, // 设置成false会在“输出”中输出，无法输入`
-   Prettier：代码格式化

<!-- prettier-ignore-start -->
!!! tip "内心OS"
    所有人都应该用 Prettier 格式化代码！！！
<!-- prettier-ignore-end -->

以下是我喜欢的插件、主题等：

-   `adpyke.codesnap` 代码截图
-   `Equinusocio.vsc-community-material-theme` 非常好看的主题
    -   `equinusocio.vsc-material-theme-icons` 配套图标
-   `ms-vscode.hexeditor` 二进制编辑器

### 杂项

-   烦人的自动补全

在写程序代码时，自动补全能极大地提高效率，但在撰写文档过程中常常相反。比如在 Markdown 中开启代码建议，则常常会跳出前面出现过的句子等，按下 ++enter++ 键就直接键入了，非常智障。但关闭代码建议后，自定义的用户代码片段也不会自动跳出。最好的解决方法是：指定 ++tab++ 键为接受代码建议的按键。更多代码建议的信息，请参考 [StackOverflow](https://stackoverflow.com/questions/38832753/how-to-disable-intellisense-in-vs-code-for-markdown)。

-   标题栏

在 Linux 系统上安装 VSCode 可能会出现很厚的标题栏。在 `settings.json` 中设置

```json
"window.titleBarStyle": "custom"
```

即可隐藏系统自带标题栏。你还可以进一步隐藏菜单栏，设置 `"window.menuBarVisibility"` 即可，参考 [CSDN](https://blog.csdn.net/qq_28120673/article/details/81544136)。

-   用户代码片段

你可以在 VSCode 中配置用户代码片段，为常用的代码片段提供便捷的智能输入。[Snippet Generator](https://snippet-generator.app/) 是一个用户代码片段生成器。

<!-- prettier-ignore-start -->
??? note "我的代码片段"
    
    ```json title="markdown.json"
    {
	"mkdocs-admonition-normal": {
		"prefix": "ad-normal",
		"body": [
			"<!-- prettier-ignore-start -->",
			"!!! $1 \"$2\"",
			"    $3",
			"<!-- prettier-ignore-end -->"
		],
		"description": "mkdocs-admonition-normal"
	},
	"mkdocs-admonition-collapsible": {
		"prefix": "ad-collapsible",
		"body": [
			"<!-- prettier-ignore-start -->",
			"??? $1 \"$2\"",
			"    $3",
			"<!-- prettier-ignore-end -->"
		],
		"description": "mkdocs-admonition-collapsible"
	},
	"mkdocs-admonition-expanded": {
		"prefix": "ad-expanded",
		"body": [
			"<!-- prettier-ignore-start -->",
			"???+ $1 \"$2\"",
			"    $3",
			"<!-- prettier-ignore-end -->"
		],
		"description": "mkdocs-admonition-expanded"
	},
	"mkdocs-tabs": {
		"prefix": "tab",
		"body": [
			"<!-- prettier-ignore-start -->",
			"=== \"$1\"",
			"    $2",
			"=== \"$3\"",
			"    $4",
			"<!-- prettier-ignore-end -->"
		],
		"description": "mkdocs-tabs"
	},
	"prettier-ignore-start": {
		"prefix": "start-prettier",
		"body": [
			"<!-- prettier-ignore-start -->"
		],
		"description": "prettier-ignore-start"
	},
	"prettier-ignore-end": {
		"prefix": "end-prettier",
		"body": [
			"<!-- prettier-ignore-end -->"
		],
		"description": "prettier-ignore-end"
	}
    }
    ```

    这些代码片段为 Markdown 中插入 MkDocs 模块提供了较为方便的方式。
<!-- prettier-ignore-end -->

## 快捷键

我在 VSCode 中使用 Vim 插件映射快捷键，详见 [Vim](Vim.md)。VSCode 所支持的编辑操作，在 Vim 中全都有，应当多了解 Vim 如何实现这些编辑。

<!-- prettier-ignore-start -->
!!! danger
    安装 Vim 插件后，VSCode 自己的 ++ctrl++ 开头的快捷键基本都不再可用。但是，Vim 很多 Ctrl 开头快捷键非常不常用，因此可以配置 Vim 插件不处理该类快捷键，为使用 VSCode 本身的快捷键提供方便。我的配置如下

    ```json
        "vim.handleKeys": {
        "<C-a>": false,
        "<C-f>": false,
        "<C-k>": false}
    ```
<!-- prettier-ignore-end -->

- daohang


> From: [VSCode Shortcuts for Windows](https://code.visualstudio.com/shortcuts/keyboard-shortcuts-windows.pdf)

-   非常常用，一定要掌握

| Keys                   | Function            |
| ---------------------- | ------------------- |
| Windows and Tabs       |                     |
| ++ctrl+k++, ++z++      | Zen Mode            |
| ++ctrl+p++             | Quick Open          |
| ++ctrl+shift+t++       | Reopen Closed File  |
| ++ctrl+shift+n++       | New Instance        |
| ++ctrl+shift+w++       | Close Instance      |
| ++ctrl+tab++           | Switch Tabs         |
| ++ctrl+f4++            | Close Tab           |
| ++ctrl+1++             | Switch to nth Group |
| ++ctrl+k++, ++ctrl+w++ | Close group         |
| Editing                |                     |
| ++shift+alt+f++        | Format File         |
| ++shift+alt++          | Column Selection    |
| ++alt+left-button++    | Insert Cursor       |
| Running and Debugging  |                     |
| ++ctrl+alt+n++         | Code Runner         |
| ++ctrl+shift+b++       | Build Task          |
| ++f5++                 | Debugging           |
| ++shift+f5++           | Stop Debugging      |
| ++f9++                 | Add Breakpoint      |

-   比较常用

| Keys                 | Function                                   |
| -------------------- | ------------------------------------------ |
| ++shift+alt+0++      | Toggle editor layout (horizontal/vertical) |
| ++ctrl+backslash++   | Split editor                               |
| Terminal             |                                            |
| ++ctrl+grave++       | Show integrated terminal                   |
| ++ctrl+shift+grave++ | create new terminal                        |
| ++ctrl+arrow-up++    | Scroll up to last command                  |
| ++shift+page-up++    | Scroll page up                             |
| Side Bar             |                                            |
| ++ctrl+shift+e++     | Explorer                                   |
| ++ctrl+shift+f++     | Search through files                       |
| ++ctrl+shift+j++     | Advanced search                            |
| ++ctrl+shift+h++     | Substitute through files                   |
| ++ctrl+alt+enter++   | Execute substitute                         |

## 高级主题

学习接下来的内容，你将成为 VSCode 大师。

### 配置文件

> [Docs: User and Workspace Settings](https://code.visualstudio.com/docs/getstarted/settings)

VSCode 提供几种层次的配置文件：

- 用户
- 工作区
- 文件夹

更细分层次的配置文件会覆盖上一级层次的配置文件。

编辑配置文件有两种方法：

- 设置编辑器：按下 ++ctrl+comma++ 打开。
- 编辑 JSON 文件：
    - 在命令面板中选择 `Preferences: Open Settings (JSON)`。
    - 点击设置编辑器中右上角的 Open Settings (JSON) 按钮。

还可以为其他方面指定设置：

- 为特定的语言指定设置：
    - 在命令面板中选择 `Preferences: Configure Language Specific Settings`。
    - 在 JSON 文件中设置。

有一些设置项指定了可执行文件的路径，为了保证安全，这些项只能在用户级别设置：

- `git.path`
- `terminal.integrated.shell.linux`
- `terminal.integrated.shell.osx`
- `terminal.integrated.shell.windows`

后面三项分别指定了在不同系统中使用的集成终端。比如我一般在终端使用 `zsh`，而在集成终端使用简单的 `fish`。

<!-- prettier-ignore-start -->
??? note "常用的配置项"
    
    | 设置项 | 功能 |
    | - | - |
    | `"editor.formatOnPaste": true` | 自动格式化粘贴内容 |
    | `"window.zoomLevel"` | 窗口缩放等级 |
    | `"editor.fontFamily": 'Fira Code',` <br /> `"editor.fontLigatures": true` | 设置连体字，其中 `Fira Code` 是 VSCode 开发团队常用的字体之一 |
    | `"files.autoSave": "afterDelay",` <br /> `"files.autoSaveDelay": 1000` | 设置自动保存 |
<!-- prettier-ignore-end -->


### `.vscode` 中的那些文件

-   `tasks.json`：用于项目生成任务，参考官方文档 [Tasks](https://code.visualstudio.com/docs/editor/tasks)。

<!-- prettier-ignore-start -->
??? question "什么是 build？"

    Build（构建）通常包含了将源代码转换为可执行文件的整个过程。其中 **包括编译**、链接和汇编从而生成可供你在自己的系统上运行的可执行二进制文件。它是将编译和链接以及其它可能的任务（如创建安装程序）组合在一起的一系列操作。其中，“链接”是指将对象代码与库组合为原始可执行文件的行为。
    在 VSCode 中，build 被译为“生成”。
<!-- prettier-ignore-end -->

Tasks 的目的是将各种自动化项目构建系统（如 Make 等），通过命令行聚合到 VSCode 中。

在 VSCode 中配置的一般顺序如下：首先在 `tasks.json` 中编写自己的 task，然后在命令面板中选择 **Configure Default Build Task** 设置某个 task 为默认选项，此后便可以使用 ++ctrl+shift+b++ 执行任务。

<!-- prettier-ignore-start -->
??? info "tasks示例"

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
<!-- prettier-ignore-end -->

-   `launch.json`：用于调试（执行编译好的文件），参考官方文档 [Debug](https://code.visualstudio.com/docs/editor/debugging)。

VSCode 利用语言对应的扩展来支持调试。不同的调试器支持的配置也不同，以下以 `gdb` 调试器为例。

<!-- prettier-ignore-start -->
??? info "launch实例"

    ```json
    {
        "version": "0.2.0",
        "configurations": [
            {//Windows 和 Linux 通用，gdb 调试
                "name": "gdb",
                "type": "cppdbg",
                "request": "launch",
                "program": "${fileDirname}\\${fileBasenameNoExtension}",
                "args": [],
                "stopAtEntry": false,
                "cwd": "${fileDirname}",
                "environment": [],
                "externalConsole": false,
                "MIMode": "gdb",
                "miDebuggerPath": "gdb",
                "setupCommands": [
                    {
                        "description": "将反汇编风格设置为 Intel",
                        "text": "-gdb-set disassembly-flavor intel",
                        "ignoreFailures": true
                    }
                ],
                "preLaunchTask": "build",
            }
        ]
    }
    ```
<!-- prettier-ignore-end -->

## VSCode 的背后

了解这些内容，你将能够为 VSCode 的开发做出贡献。

