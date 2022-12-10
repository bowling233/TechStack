---
tags:
  - Doing
---

# Latex学习笔记

参考书籍：`doing-lshort-zh-cn.pdf`

## Ch1. Latex基本概念

* 代码编译
  * `xelatax name(.tex)`
  * 注意：文档保存为**UTF-8**编码
* 命令和代码结构
  1. 反斜杠开头及其后的**一串字母**，以任意非字母符号 **（空格、数字、标点）** 为界限：`\begin`
  2. 反斜杠及其后单个**非字母字符**：`\$`
  * 大小写敏感：`\LaTeX`
  * **形式1**的命令忽略其后所有空格，如需引入空格请在命令后加`{}`或插入`\ `（代表一个空格）：`\TeX{}`
  * 命令参数
    * `[]`：可选参数
    * `{}`：必选参数
    * `*`：命令效果
    * 单字符作为参数可不加`{}`：如`\frac12`与`\frac{1}{2}`
* 环境
  * 一对`\begin{}[]{}`和`\end{}`
  * 有些命令对其后所有内容产生作用，若需限制作用范围需要**分组`{}`**，组中的命令作用范围限制在组内
* 源代码结构

```latex
\documentclass{}
%导言区
\begin{document}
%正文
\end{document}
%此后内容被忽略
```

### Latex宏包

1. 文档类
   1. 标准文档类：article, report, book
      1. 字号：10-12pt
      2. 纸型：a4paper, *letterpaper*, a5paper, b5paper
      3. 双页排版：twoside (book) 使奇偶页页眉页脚、页边距不同
      4. 双栏：twocolmn
      5. 章节开始页：openright (book), openany (report)
      6. 方向：landscape
      7. 标题页：titlepage
      8. 行间公式左对齐：fleqn 默认居中
      9. 公式编号左置：leqno
      10. 草稿模式：draft 溢出部分插入黑色方块，插图、超链接受影响
   2. 基础文档类：proc, **slides**, minimal
   3. ctexart, ctexrep, ctexbook
2. 宏包使用
   1. 一次性调用无需指定参数的多个宏包
   2. 帮助文档：`texdoc <pkg-name>`
3. LaTeX其他文件
   1. `.bib`：参考文献数据库
   2. `.aux`：主辅助文件，记录交叉引用、目录、参考文献引用等
4. 多文件组织
   1. 每章内容单独写一个文件
   2. 读入时另起一页：`\include{<filename>}`，不带`.tex`。windows路径也使用正斜杠
   3. 纯插入：`\input{<filename>}`
   4. 技巧：**导言区**内容较多时，单独放置一个文件

### LaTeX术语

* 引擎：排版编译器
  * pdfTEX, XeTeX
* 格式：一组代码集
  * LaTeX
* 编译命令
  * latex: 调用pdfTEX生成dvi
  * pdflatex：调用pdfTEX生成pdf
  * xelatex：调用XeTeX生成pdf

## Ch.2 LaTeX排版文字

* ASCII和扩展编码时期：inputenc宏包支持了pdfLaTeX的源代码编码处理
* UTF-8时期：现行XETEX和LuaTEX直接编译，需要借助`fontspec`宏包调用适当字体。某些语言断词规则需要更复杂的宏包支持


### 中文排版

两个问题：

* 中文字体支持
* 中文排版规则

**ctex**宏包封装了CJK, xeCJK, luatexja等中文包，**无需考虑排版引擎**，能够识别操作系统和TEX中安装的中文字体，无需额外配置

### LaTeX字符

1. 空格和分段
  * 连续的多个空白字符视为一个空格
  * 换行符视为一个空格
  * 多个空行视为一个空行
  * `\par`行末分段
2. 特殊字符
  * `# $ % & { } _ ^ ~ \`
  * 注意：`\\`是手动换行，`\`应当使用`\textbackslash`
  * 西文排版中的连字现象
3. 西文标点
  * 单引号``和'`输入
  * 双引号```和''`输入
  * 其实，中西文引号使用Unicode中同一码位
  * 连字号`-`、短破折号`--`（数字）、长破折号`---`（单词）
  * 省略号`\dots`
  * 其他文本符号$\P{} \S{} \copyright{} \pounds{} \textregistered{} \texttrademark{}$
4. 断行断页
  * `~`输入一个不会断行的空格（用于人名、图标名等）
  * 断行：**并非另起一段**`\\[length]`（可用于表格、公式）`\newline`（文本）
  * 断页：`\newpage`（双栏中另起一栏）,`\clearpage`

## Ch.3 文档元素

章节、目录、列表、图表、交叉引用、脚注

### 章节和目录

chapter, section, subsection, subsubsection, paragraph, subparagraph

变体类型：

* `[short title]`：目录和页眉页脚
* `*`：不生成目录项

目录：`\tableofcontents`，生成单独一章/节，标题默认为Contents，默认不写入目录。生成目录一般需要编译两次

补充目录项：`\addcontentsline{toc}{<level>}{<title>}`

目录有关宏包：titletoc, tocloft

文档结构划分：`\appendix`，book还提供了`\frontmatter`, `\mainmatter`, `\backmatter`划分页码

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

