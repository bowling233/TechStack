# 基础：作为计算机科学与技术专业的学生，需要掌握哪些能力？

<!-- prettier-ignore-start -->
!!! info 
    [HobbitQia：如何让自己看上去、闻上去都像一个 CS 人](https://blog.hobbitqia.cc/p/5948019b.html)
<!-- prettier-ignore-end -->

-   学会阅读英文
-   学会使用英文
-   学会搜索
    -   做一个优秀的 Google 程序员，做一个优秀的 Stack Overflow 程序员。
-   学会提问
    -   遇到一个问题，你首先应该进行自己的思考，其次进行搜索，最后进行提问。
    -   提问时，要提供关于问题足够的信息。
-   学会学习
    -   要懂得主动阅读帮助文档和教程。
-   学会协作
    -   掌握一些协作工具，比如：Git。

## 学会协作

在学习 CS 的过程中，最重要的事情或许是学会协作，然而课堂并不会教你如何与他人协作。与他人协作需要掌握两项基本技能：协作工具和代码美学。

### 协作工具

<!-- prettier-ignore-start -->
!!! quote "不错的学习资料"
    
    - 1 分钟上手 git：[git - 简明指南](https://rogerdudler.github.io/git-guide/index.zh.html)
    - 学习使用 GitHub：[GitHub Quickstart](https://docs.github.com/en/get-started/quickstart/hello-world) | [中文版：GitHub 快速入门](https://docs.github.com/zh/get-started/quickstart/hello-world)
    - 深入理解 Git：[Pro Git](https://git-scm.com/book/en/v2) | [中文版](https://www.progit.cn/)
<!-- prettier-ignore-end -->

### 代码美学

初学者在学习编程时，往往对代码格式不够重视。特别是国内众多初学者使用 Dev-C++ 学习编程，编辑器不支持自动格式化，向他人展示代码时看起来十分费劲。

<!-- prettier-ignore-start -->
!!! tip "更换编辑器"
    
    请抛弃 Dev-C++，**使用 VSCode** 作为代码编辑器。
<!-- prettier-ignore-end -->

VSCode 自带的代码格式化功能已经能够满足大部分情况下的需求。当你学习得更深入，需要跨编辑器、与他人合作时，就可以使用 EditorConfig 来统一代码风格了。

<!-- prettier-ignore-start -->
??? note "EditorConfig"
    
    - [EditorConfig](https://editorconfig.org/)
    
    > EditorConfig helps maintain consistent coding styles for multiple developers working on the same project across various editors and IDEs. The EditorConfig project consists of a file format for defining coding styles and a collection of text editor plugins that enable editors to read the file format and adhere to defined styles. EditorConfig files are easily readable and they work nicely with version control systems.
    
    以下编辑器为 EditorConfig 提供支持：
    
    - 集成的支持：GitHub、GitLab、IntelliJ IDEA、Visual Studio
    - 需要插件：Atom、CodeBlocks、Emacs、Notepad++、Vim、Visual Studio Code
    
    EditorConfig 主要有一下属性可以配置：
    
    - `indent_style`: set to `tab` or `space` to use hard tabs or soft tabs respectively.
    - `indent_size`: a whole number defining the number of columns used for each indentation level and the width of soft tabs (when supported). When set to tab, the value of tab_width (if specified) will be used.
    - `end_of_line`: set to `lf`, `cr`, or `crlf` to control how line breaks are represented.
    - `charset`: set to `latin1`, `utf-8`, `utf-8-bom`, `utf-16be` or `utf-16le` to control the character set.
    - `trim_trailing_whitespace`: set to `true` to remove any whitespace characters preceding newline characters and `false` to ensure it doesn't.
    - `insert_final_newline`: set to `true` to ensure file ends with a newline when saving and `false` to ensure it doesn't.
    - `root`: special property that should be specified at the top of the file outside of any sections. Set to `true` to stop .editorconfig files search on current file.
<!-- prettier-ignore-end -->

## 使用 Linux 系统

- [Youtube: Why Linux Is Better For Programming](https://youtu.be/otDOHt_Jges)

总结一下：

1. 安全：因为 Linux 是开源的，所以它是安全的。你能解释其中的逻辑吗？
2. 优化工作流：包管理器
3. 无需重启：很多 Linux 服务器不间断运行了几年，其间没有重启也没有遇到失败。
4. 强大的实用工具：grep、wget、cron 等。
5. 自动化
6. 性能
7. 有用的错误信息：而不是 Oops! Something went wrong.
8. 自定义

<!-- prettier-ignore-start -->
!!! tip "开始使用 Linux"

    在你开始使用 Linux 前，最好使用虚拟机、云服务器或 WSL 体验一段时间。当你发现自己在 Linux 上花费的时间越来越多时，你就可以尝试真正安装 Linux 系统了。
<!-- prettier-ignore-end -->

## 基础技能

<!-- prettier-ignore-start -->
!!! info

    - [MIT: The Missing Semester of Your CS Education](https://missing.csail.mit.edu/)
<!-- prettier-ignore-end -->

MIT 开设的课程介绍了 CS 人需要熟练掌握的一些技能。这里简单记录一下我学到了些什么。

### 第一节：课程概述和 Shell 简介

本节课告诉你设立这门课的动机、整个课程的结构，以及简要介绍一下 Shell 的使用。

在本节课学习了 Shell 的基本概念、在 Shell 中导航以及使用管道。

### 第二节：Shell 工具和脚本

#### Shell 工具

首先，学会使用 [`tldr`](linux/LinuxUtility.md#tldr) 和 [`man`](linux/LinuxBasic.md#man)。掌握了这两个工具就相当于掌握了所有工具的使用方法。日常使用 `tldr` 足够。

了解一些常用工具：`find` 查找文件，`locate` 使用索引查找文件（速度快一些，由系统内核每天更新数据库，只能查找文件名），`grep` 查找文件内容，`history` 查找历史命令。

- `grep` 的常用标记：
    - `-C` **C**ontent 附带数字，获取匹配行的上下文。
    - `-i` in**v**ert 反转匹配。
    - `-R` **Recursively** 递归查找一个目录。

这些工具功能都挺强大的，但往往速度慢，使用难度大。有很多替代品值得一试，它们需要额外安装。

- `fd-find` 是 `find` 的替代品，它的命令是 `fdfind`。它提供了带颜色的输出、支持正则表达式等功能。
- `ripgrep` 是 `grep` 的替代品，它的命令是 `rg`。它提供了带颜色的输出和简单易用的命令，速度也更快。
- `autojump` 能够让你快速跳转到最近的工作文件或目录。默认安装后你应当使用 `autojump` 命令，参考暗转指南能够替换为方便的 `j` 命令。命令 `j` 跳转到包含给定模式的文件夹，`jc` 限定于子文件夹。
- `tree` 让你得到工作目录的结构。还有更完善的文件管理器如 `nnn` 等。

<!-- prettier-ignore-start -->
!!! tip "工具"
    
    重要的是，你知道这些问题可以使用这些工具解决。至于你具体选择哪个工具，这并不重要。
<!-- prettier-ignore-end -->

++ctrl+r++ 能够反向搜索历史命令。持续按该组合键将不断回溯命令。

比搜索历史命令更好的是 shell 的自动补全。综合使用下来 `fish` 的补全体验最好，`zsh` 也能够通过插件开启。

#### Shell 脚本

基于 `bash`。

首先学习 shell 变量，以及使用单、双引号的字符串有什么不同。双引号的字符串会被展开，单引号不会。

简单的 Shell 脚本需要了解：如何编写函数、如何使用参数、判断和控制、通配符等。
