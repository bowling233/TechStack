---
tags:
    - Doing
---

# Latex 学习笔记

参考书籍：`doing-lshort-zh-cn.pdf`

## Ch0. 偷懒

可以使用 Typora 主题将 Markdown 渲染成 Latex 样式，但是其实也没有变简单很多（doge。

## Ch1. Latex 基本概念

-   在系统上按指南安装 [`TeX Live`](https://www.tug.org/texlive/)。

-   编译 Latex 文件
    -   `xelatax name(.tex)`
    -   注意：文档保存为**UTF-8**编码。
-   LaTeX **命令**有以下两种结构：
    1. 反斜杠开头及其后的**一串字母**，以任意非字母符号**（空格、数字、标点）**为界限：`\begin`
    2. 反斜杠及其后单个**非字母字符**：`\$`
    -   注意：命令大小写敏感，如 `\LaTeX`。
    -   **形式 1** 的命令忽略其后所有空格，如需引入空格请在命令后加`{}`或插入`\ `（代表一个空格）：`\TeX{}`
    -   命令参数
        -   `[]`：可选参数
        -   `{}`：必选参数
        -   `*`：可选的效果
        -   单字符作为参数可不加 `{}`：如 `\frac{1}{2}` 可写为 `\frac12` 。
-   环境
    
    -   环境让一些效果在局部生效或**生成特殊的文档元素**。
    -   一对 `\begin{}[]{} `和 `\end{}` 组成一个环境。
    -   有些命令对其后所有内容产生作用，若需限制作用范围需要**分组`{}`**，组中的命令作用范围限制在组内（在后文讲解**字体**时会提到）。
    
-   源代码结构

```latex
\documentclass{} %注释
%导言区：调用宏包，进行全局设置
\begin{document}
%正文
\end{document}
%此后内容被忽略
```

### Latex 宏包和文档类

1. 文档类
    - 标准文档类：article, report, book
    - 基础文档类：proc, **slides**, minimal
    - 可以为文档设置：字号、纸张大小、单双面排版、单双栏排版、横向排版、标题页、公式对齐等等选项。
2. 宏包
    1. 宏包用于扩展 LaTeX 的功能
    2. 一次性调用无需指定参数的多个宏包：`\usepackage{tabularx, makecell, ...}`。
    3. 帮助文档：`texdoc <pkg-name>`

<!-- prettier-ignore-start -->
!!! note "常用的宏包"
    
    1. `amsmath`：数学公式扩展
<!-- prettier-ignore-end -->

### 多文件编辑

除了 `.tex`，我们还会编辑以下格式的文件：

- `.bib`：参考文献数据库

编写比较大型的 LaTeX 文档时，常常将文档的各部分拆分为更小的子文档。多文件组织一般规则如下：

- 每章内容单独写一个文件
- 插入文件的命令：
    - `\include{<filename>}`：插入时会另起一页。
    - `\input{<filename>}`：仅插入。导言区和复杂的图标、代码常常使用该命令。
    - 可以使用相对路径和绝对路径，都使用正斜线分隔路径（Windows 注意）。

<!-- prettier-ignore-start -->
!!! note "小技巧"
    
    使用 `syntonly` 宏包 + `\syntaxonly` 命令，可以不生成文档，仅检查错误，速度很快。
<!-- prettier-ignore-end -->

### LaTeX 术语

-   引擎：编译代码并生成文档的程序
    -   pdfTeX, XeTeX
-   编译命令
    -   `latex`: 调用 pdfTEX 生成 dvi
    -   `pdflatex`：调用 pdfTEX 生成 pdf
    -   `xelatex`：调用 XeTeX 生成 pdf。xelatex 是当前较为方便的中文解决方案。

## Ch.2 LaTeX 排版文字

简要解释一下中文文档排版现在究竟怎么用：

-   现行 XƎTEX 和 LuaTEX 直接编译 UTF-8 编码文档，不再需要 `inputenc` 宏包。
-   XƎTEX 和 LuaTEX 除了直接支持 UTF-8 编码外，还支持直接调用 TrueType / OpenType
    格式的字体。xeCJK 及 luatexja 宏包则在此基础上**封装了对汉字排版细节的处理功能**。
-   ctex 宏包和文档类进一步封装了CJK、xeCJK、luatexja 等宏包，包括ctexart / ctexrep
    / ctexbook。
-   

### 中文排版

两个问题：

-   中文字体支持
-   中文排版规则

**ctex**宏包封装了 CJK, xeCJK, luatexja 等中文包，**无需考虑排版引擎**，能够识别操作系统和 TEX 中安装的中文字体，无需额外配置

### LaTeX 字符

1. 空格和分段

-   连续的多个空白字符视为一个空格
-   换行符视为一个空格
-   多个空行视为一个空行
-   `\par`行末分段

2. 特殊字符

-   `# $ % & { } _ ^ ~ \`
-   注意：`\\`是手动换行，`\`应当使用`\textbackslash`
-   西文排版中的连字现象

3. 西文标点

-   单引号``和'`输入
-   双引号```和''`输入
-   其实，中西文引号使用 Unicode 中同一码位
-   连字号`-`、短破折号`--`（数字）、长破折号`---`（单词）
-   省略号`\dots`
-   其他文本符号$\P{} \S{} \copyright{} \pounds{} \textregistered{} \texttrademark{}$

4. 断行断页

-   `~`输入一个不会断行的空格（用于人名、图标名等）
-   断行：**并非另起一段**`\\[length]`（可用于表格、公式）`\newline`（文本）
-   断页：`\newpage`（双栏中另起一栏）,`\clearpage`

## Ch.3 文档元素

章节、目录、列表、图表、交叉引用、脚注

### 章节和目录

chapter, section, subsection, subsubsection, paragraph, subparagraph

变体类型：

-   `[short title]`：目录和页眉页脚
-   `*`：不生成目录项

目录：`\tableofcontents`，生成单独一章/节，标题默认为 Contents，默认不写入目录。生成目录一般需要编译两次

补充目录项：`\addcontentsline{toc}{<level>}{<title>}`

目录有关宏包：titletoc, tocloft

文档结构划分：`\appendix`，book 还提供了`\frontmatter`, `\mainmatter`, `\backmatter`划分页码

标题页：`\thanks`标题页脚注，`\and`分隔人名

```latex

%preface
\usepackage{makeidx}
\makeindex
\bibliographystyle{plain}

\begin{document}

\maketitle
\tableofcontents

\appendix

\bibliography{books}
\printindex

\end{document}
```

## Ch.4 参考文献

### 获取

很神奇的是，百度学术提供了 BibTex 格式的文献引用，可以直接去上面获取。

GitHub 上也有知网导出 BibTex 的工具：[CNKI_2_BibTeX](https://github.com/Vopaaz/CNKI_2_BibTeX)
