---
tags:
    - Doing
---

# Latex 学习笔记

<!-- prettier-ignore-start -->
!!! abstract "摘要"
    
    以下两份参考文献是我主要的 Latex 学习来源，都写得太好了，而且方便查询。因此本笔记仅作 cheatsheet 式的记录，使用方法请查询以下文献：

    - [Overleaf Documentation](https://www.overleaf.com/learn)
    - [111 分钟了解 Latex（lshort 的中文版）](https://texdoc.org/serve/lshort-zh-cn.pdf/0)

    还有一些其它内容，比如三线标、副标题等各种东西，大部分来自 StackOverflow 或知乎。
<!-- prettier-ignore-end -->

## 如何使用 LaTeX

- 方法 1：使用在线的 Overleaf

推荐新手使用该方法。Overleaf 在线提供了完善的 LaTeX 环境，不会遇到在本地配置环境时的各种问题。但有不少朋友吐槽它偶尔断连，导致自己丢失了一部分编辑的内容。因此请确保在网络环境通畅的情况下使用 Overleaf，并养成及时保存的习惯。

- 方法 2：在本地安装 'TeX Live'

在系统上按指南安装 [`TeX Live`](https://www.tug.org/texlive/)。如果你不熟悉命令行，就请教身边的会命令行的人，让他们帮你安装叭。

`TeX Live` 是什么？LaTeX 是一种**排版格式**，有很多种**排版引擎**如 `pdflatex`、`xelatex`、`lualatex` 可以将 `.tex` 编译成 `.pdf` 文件。LaTeX的基本功能很简洁，我们使用各种**宏包**为 LaTeX 添加更多功能，如 `amsmath` 包提供数学公式增强、`graphicx` 包提供图片功能。`TeX Live` 是一个**LaTeX 文档生成系统**，把各种引擎和宏包都打包起来了。

## 基本概念

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

## 必学内容

对应 LaTeX Basics 部分。

### Overleaf

- [Learn LaTeX in 30 minutes](https://www.overleaf.com/learn/latex/Learn_LaTeX_in_30_minutes)

内容包括 LaTeX 文档的基本结构、基本语法、注释、字体（粗体、斜体 `\textit`、下划线、强调 `\emph`）、图片（图片路径 `\graphicspath{{path1/}}`、插入图片 `\includegraphics`、标题、标签和引用）、列表、数学公式（行内、展示模式）、段落和换行、摘要、章和节、表格 `tabular` 与 `table`、TOC（目录 `\tableofcontents`）、

值得提醒的是，在 LaTeX 中，展示模式的公式不推荐使用 `$$` 标记，简单的请使用 `\[` 标记，多行等复杂公式请使用公式环境如 `displaymath` 和 `equation`。换行与段落的不同也应当注意，换行后仍停留在同一段落中。

## 数学

## 图表

## 参考文献和引用

## 文档结构

### [分区和章节](https://www.overleaf.com/learn/latex/Sections_and_chapters)

不同文档类型的文档结构不同。`section` 在所有文档类型中都可用。`chapter` 和 `part` 在 report 和 book 类型中可用。

最多有 7 层文档分区。从上至下为：`part`, `chapter`, `section`, `subsection`, `subsubsection`, `paragraph`, `subparagraph`。

在文档分区命令后加 `*` 号使该分区不编号，如 `\section*{Intro}`。不编号的分区需要手动加入到文档目录中，下面这条命令应当放置在正文中、不编号分区前：

```latex
\addcontentsline{toc}{section}{Intro}
```

稍后在[目录](#目录)小结详解该命令。

`subsubsection` 默认无编号，可以用命令设置编号：`\setcounter{secnumdepth}{3}`。

<!-- prettier-ignore-start -->
??? note "宏包 `titlesec`"

    使用 `titlesec` 宏包可以自定义标题的样式，这里展示两个常用的命令：

    ```latex
    \titleformat{<command>}[<shape>]{<format>}{<label>}{<sep>}{<before-code>}[<after-code>]
    \titlespacing{<command>}{<left>}{<before-sep>}{<after-sep>}
    \titlespacing*{}%带星号的版本取消了紧跟在标题后的段落的缩进。
    %例子
    \titleformat
    {\chapter} % command，即对应的分区命令
    [display] % shape
    {\bfseries\Large\itshape} % format
    {Story No. \ \thechapter} % label
    {0.5ex} % sep
    {
        \rule{\textwidth}{1pt}
        \vspace{1ex}
        \centering
    } % before-code
    [
    \vspace{-0.5ex}%
    \rule{\textwidth}{0.3pt}
    ] % after-code
    \titlespacing{\section}{12pc}{1.5ex plus .1ex minus .2ex}{1pc}
    ```

    > 回忆：方括号中为可选的参数
<!-- prettier-ignore-end -->


### [目录](https://www.overleaf.com/learn/latex/Table_of_contents)

使用 `\tableofcontents` 命令创建目录。

目录的默认标题是 Contents，可以使用 `\renewcommand*\contentsname{TOC Title}` 命令更改。

> 如果启用了 `babel` 包支持多语言，那么这条命令应当放置在 `\addto\captionsenglish{ }` 命令中。将 `english` 替换为你需要的语言。

### [交叉引用分区、公式和图表](https://www.overleaf.com/learn/latex/Cross_referencing_sections%2C_equations_and_floats)

前文的[图表](#图表)小结中，我们使用了 `\label{}` 命令为图表创建标签。使用 `\ref{}` 命令引用打好标签的元素：

```latex
\begin{figure}
%...
\label{fig:leaf}
\end{figure}
\ref{fig:leaf}
```

要引用分区，我们在分区命令后紧跟一个 `\label{}` 命令创建一个标识符，同样使用 `\ref{}` 命令引用它。公式也是一样。

`\ref{}` 命令显示引用的元素的编号，`\pageref{}` 命令则显示对应的页码。

<!-- prettier-ignore-start -->
!!! note "编译交叉引用文档"
    
    在本地 LaTeX 环境编译时，如果希望交叉引用正常工作，需要**将文档编译两次**。第一次编译时，会报 warning 提示符号未定义，在生成的 pdf 中数字显示为 `??`。第二次编译即完成交叉引用，显示正常。
    
    或者使用这个命令：

    ```bash
    latexmk -pdf main.tex
    ```

    !!! note "`latexmk` 简介"
        
        `latexmk` 工具用于自动化 LaTeX 文档的生成。有一些常用命令如下：

        - `-xelatex`, `-lualatex` 使用对应的引擎处理文件。
<!-- prettier-ignore-end -->

### [术语表](https://www.overleaf.com/learn/latex/Indices)

`imakeidx` 包能够为大型文档，如 book 类型，生成术语表。在导言区使用 `\makeindex` 命令让，在文中的关键词后使用 `\index{keywords}` 标记关键词，在文末使用 `\printindex` 命令打印术语表。

每个条目可以创建子条目，使用 `\index{keyword!subEntry}` 即可，它会自动归在 `keyword` 条目下。

对 `\makeindex` 传参数可以格式化术语表，如：

```latex
\makeindex[columns=3, title=Alphabetical Index]
```

### [生词表](https://www.overleaf.com/learn/latex/Glossaries)

### [符号表](https://www.overleaf.com/learn/latex/Glossaries)

### [管理大型项目](https://www.overleaf.com/learn/latex/Management_in_a_large_project)

### [管理多文件项目](https://www.overleaf.com/learn/latex/Multi-file_LaTeX_projects)

### [超链接](https://www.overleaf.com/learn/latex/Hyperlinks)

`hyperref` 包提供了各类超链接功能。

- `\herf{https://www.com}{Title}` 隐式链接，显示标题。
- `\url{https://www.com}` 显式链接，直接显示原始链接。

## 格式化

## 字体

## 展示



## 常用技巧

### 零散

- `blindtext` 包提供生成大量测试文本的功能
    - `\Blindtext`

### 表单类

```latex


```

分割线：以下的内容还没有进行整理

---


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
