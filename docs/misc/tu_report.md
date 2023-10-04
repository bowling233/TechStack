# 如何写一份精美的实验报告

<!-- prettier-ignore-start -->
!!! tip "两个要点"

    - 一份实验报告，最重要的是其内容，其次才是版面。
    - 工具并不重要，熟练掌握一种工具即可。
<!-- prettier-ignore-end -->

下面是常用的写作工具：

| 工具     | 上手难度 | 复杂排版难易度            | 备注                   |
| -------- | -------- | ------------------------- | ---------------------- |
| Word     | 简单     | 复杂                      | 可能会显得你不太专业   |
| LaTeX    | 复杂     | 简单                      | 学术论文等正式场合必备 |
| Markdown | 简单     | 简单（只需要 Typora）即可 | 大多数人的选择         |

总结：要写出一份**_精美的_**小论文，首选的工具是 LaTeX。对于简单的报告，使用 Markdown 即可。

## Markdown 高级语法

Markdown 基础语法非常简单，这里不再介绍。使用 Typora 的主题可以实现多种多样的排版效果，请参考 [Typora 主题](https://theme.typora.io/)。

这里简单介绍一下将 Markdown 文档发布到网页上可能会使用的交叉引用功能。

## 如何使用 LaTeX

-   方法 1：使用在线的 Overleaf

推荐新手使用该方法。Overleaf 在线提供了完善的 LaTeX 环境，不会遇到在本地配置环境时的各种问题。但有不少朋友吐槽它偶尔断连，导致自己丢失了一部分编辑的内容。因此请确保在网络环境通畅的情况下使用 Overleaf，并养成及时保存的习惯。

-   方法 2：在本地安装 TeX Live

在系统上按指南安装 [TeX Live](https://www.tug.org/texlive/)。如果你不熟悉命令行，就请教身边的会命令行的人，让他们帮你安装叭。

TeX Live 是什么？LaTeX 是一种**排版格式**，有很多种**排版引擎**如 `pdflatex`、`xelatex`、`lualatex` 可以将 `.tex` 编译成 `.pdf` 文件。LaTeX 的基本功能很简洁，我们使用各种**宏包**为 LaTeX 添加更多功能，如 `amsmath` 包提供数学公式增强、`graphicx` 包提供图片功能。TeX Live 是一个 **LaTeX 文档生成系统**，把各种引擎和宏包都打包起来了。

## 基本概念

### 命令和环境

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

### 简单语法

<!-- prettier-ignore-start -->
!!! info 

    [Learn LaTeX in 30 minutes](https://www.overleaf.com/learn/latex/Learn_LaTeX_in_30_minutes)
<!-- prettier-ignore-end -->

内容包括 LaTeX 文档的基本结构、基本语法、注释、字体（粗体、斜体 `\textit`、下划线、强调 `\emph`）、图片（图片路径 `\graphicspath{{path1/}}`、插入图片 `\includegraphics`、标题、标签和引用）、列表、数学公式（行内、展示模式）、段落和换行、摘要、章和节、表格 `tabular` 与 `table`、TOC（目录 `\tableofcontents`）、

值得提醒的是，在 LaTeX 中，展示模式的公式不推荐使用 `$$` 标记，简单的请使用 `\[` 标记，多行等复杂公式请使用公式环境如 `displaymath` 和 `equation`。换行与段落的不同也应当注意，换行后仍停留在同一段落中。

### 字符

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
-   其他文本符号 $\P{} \S{} \copyright{} \pounds{} \textregistered{} \texttrademark{}$

4. 断行断页

-   `~`输入一个不会断行的空格（用于人名、图标名等）
-   断行：**并非另起一段**`\\[length]`（可用于表格、公式）`\newline`（文本）
-   断页：`\newpage`（双栏中另起一栏）,`\clearpage`

## 基础组件

### 封面 Cover

<!-- prettier-ignore-start -->
!!! info 

    [Stack Exchange: How can I design a book cover?](https://tex.stackexchange.com/questions/17579/how-can-i-design-a-book-cover)
<!-- prettier-ignore-end -->

```latex
\clearpage
%% temporary titles
% command to provide stretchy vertical space in proportion
\newcommand\nbvspace[1][3]{\vspace*{\stretch{#1}}}
% allow some slack to avoid under/overfull boxes
\newcommand\nbstretchyspace{\spaceskip0.5em plus 0.25em minus 0.25em}
% To improve spacing on titlepages
\newcommand{\nbtitlestretch}{\spaceskip0.6em}
\pagestyle{empty}
\begin{center}
\bfseries
\nbvspace[1]
\Huge
{\nbtitlestretch\huge
Main Title}

\nbvspace[1]
\normalsize

Prject No. \\
Some information 
\nbvspace[1]
\small BY\\
\Large Author\\[0.5em]
\footnotesize Student ID: \\
Teacher: 

\nbvspace[2]

Accomplished on \today \\
\nbvspace[3]
\normalsize

Made\\
\large
With \LaTeX
\nbvspace[1]
\end{center}
```

### 页边距 Margin

<!-- prettier-ignore-start -->
!!! info

    [Overleaf: Page size and margins](https://www.overleaf.com/learn/latex/Page_size_and_margins)
<!-- prettier-ignore-end -->

LaTeX 默认页边距较大，常用窄边距设置如下：

```latex
\usepackage{geometry}
 \geometry{
 a4paper,
 total={170mm,257mm},
 left=20mm,
 top=20mm,
 }
```

### 首行缩进 Indent

<!-- prettier-ignore-start -->
!!! info 

    [Stack Exchange: No indent in the first paragraph in a section?](https://tex.stackexchange.com/questions/39227/no-indent-in-the-first-paragraph-in-a-section)
<!-- prettier-ignore-end -->

```latex
\usepackage{indentfirst}
```

### 引用 Reference

要按国标 GB/T 7714-2015 规定，则在导言区设置：

```latex
\usepackage{gbt7714}
\bibliographystyle{gbt7714-numerical}
```

即可。

### 表格 Table

#### 表格对齐

<!-- prettier-ignore-start -->
!!! info 

    [Stack Exchange: Right alignment of column in table column](https://tex.stackexchange.com/questions/199744/right-alignment-of-column-in-table-column)
<!-- prettier-ignore-end -->

导言区新建列类型：

```latex
\newcolumntype{R}[1]{>{\RaggedLeft\arraybackslash}p{#1}}
```

正文：

```latex
\begin{table}[h!]
    \begin{tabular}{R{1.5cm} R{2.5cm} p{5cm} p{4cm}}
        \toprule
        类型        & 标识符          & 参数                            & 描述           \\
        \midrule
        void&OutputData&(char *fileName)&向指定文件输出数据      \\
        \bottomrule
    \end{tabular}
\end{table}
```

#### 三线表

<!-- prettier-ignore-start -->
!!! info 

    [知乎：LaTeX保姆级教程|插入三线表](https://zhuanlan.zhihu.com/p/440498868)
<!-- prettier-ignore-end -->

三线表可以使用 `booktabs` 宏包，三条线分别是 `\toprule`、`\midrule`、`\bottomrule`。

```latex hl_lines="4 6 9"
%preamble \usepackage{booktabs}
\begin{table}[h!]
    \begin{tabular}{llll}
        \toprule
        1 & 2 & 3 & 4\\
        \midrule
        1 & 2 & 3 & 4\\
        1 & 2 & 3 & 4\\
        \bottomrule
    \end{tabular}
\end{table}
```

#### 跨页表格

<!-- prettier-ignore-start -->
!!! info 

    [Overleaf: Longtable](https://www.overleaf.com/learn/latex/Tables#Long_tables)
<!-- prettier-ignore-end -->

#### 复杂的单元格边框

<!-- prettier-ignore-start -->
!!! info 

    [](https://tex.stackexchange.com/questions/112343/complex-table-cell-border)
<!-- prettier-ignore-end -->

一般使用 `hhline` 或 `makecell` 宏包。请自行查阅文档。

## 代码相关

### 代码清单 Code List

<!-- prettier-ignore-start -->
!!! info 

    [Overleaf：Code listing](https://www.overleaf.com/learn/latex/Code_listing)
<!-- prettier-ignore-end -->

在导言区加入以下设置：

```latex
\usepackage{listings}
\usepackage{xcolor}
\definecolor{codegreen}{rgb}{0,0.6,0}
\definecolor{codegray}{rgb}{0.5,0.5,0.5}
\definecolor{codepurple}{rgb}{0.58,0,0.82}
\definecolor{backcolour}{rgb}{0.95,0.95,0.92}
\lstdefinestyle{mystyle}{
    backgroundcolor=\color{backcolour},
    commentstyle=\color{codegreen},
    keywordstyle=\color{magenta},
    numberstyle=\tiny\color{codegray},
    stringstyle=\color{codepurple},
    basicstyle=\ttfamily\footnotesize,
    breakatwhitespace=false,
    breaklines=true,
    captionpos=b,
    keepspaces=true,
    numbers=left,
    numbersep=5pt,
    showspaces=false,
    showstringspaces=false,
    showtabs=false,
    tabsize=2
}
\lstset{style=mystyle}
```

在正文中使用 `lstlisting` 环境，指定语言和描述：

```latex
\begin{lstlisting}[language=Python, caption=Python example]
import numpy as np

def incmatrix(genl1,genl2):
    m = len(genl1)
    n = len(genl2)
    M = None #to become the incidence matrix
    VT = np.zeros((n*m,1), int)  #dummy variable

    #compute the bitwise xor matrix
    M1 = bitxormatrix(genl1)
    M2 = np.triu(bitxormatrix(genl2),1)

    for i in range(m-1):
        for j in range(i+1, m):
            [r,c] = np.where(M2 == M1[i,j])
            for k in range(len(r)):
                VT[(i)*n + r[k]] = 1;
                VT[(i)*n + c[k]] = 1;
                VT[(j)*n + r[k]] = 1;
                VT[(j)*n + c[k]] = 1;

                if M is None:
                    M = np.copy(VT)
                else:
                    M = np.concatenate((M, VT), 1)

                VT = np.zeros((n*m,1), int)

    return M
\end{lstlisting}
```

或者从外部文件中导入代码：

```latex
\lstinputlisting[language=Octave]{BitXorMatrix.m}
```

### 算法描述 Algorithm

<!-- prettier-ignore-start -->
!!! info 

    [Overleaf：Algorithms](https://www.overleaf.com/learn/latex/Algorithms)
<!-- prettier-ignore-end -->

一般使用 `algorithm2e` 宏包，配置 `linesnumbered` 和 `ruled` 选项能显示行号和类似三线表的边框。

导言区：

```latex
\usepackage[linesnumbered, ruled]{algorithm2e}
%% This declares a command \Comment
%% The argument will be surrounded by /* ... */
\SetKwComment{Comment}{/* }{ */}
```

正文：

```latex
\begin{algorithm}
\caption{An algorithm with caption}\label{alg:two}
\KwData{$n \geq 0$}
\KwResult{$y = x^n$}
$y \gets 1$\;
$X \gets x$\;
$N \gets n$\;
\While{$N \neq 0$}{
  \eIf{$N$ is even}{
    $X \gets X \times X$\;
    $N \gets \frac{N}{2}$ \Comment*[r]{This is a comment}
  }{\If{$N$ is odd}{
      $y \gets y \times X$\;
      $N \gets N - 1$\;
    }
  }
}
\end{algorithm}
```

可以在 `algorithm` 环境中使用 `caption`、`ref` 等命令。环境中的每一行（除了 `{}`
表示的块的开始和结尾）都需要以 `\;` 结尾。

## 特殊组件

### 流程图 Flow Chart

<!-- prettier-ignore-start -->
!!! info 

    [Overleaf: Creating Flowcharts](https://www.overleaf.com/learn/latex/LaTeX_Graphics_using_TikZ%3A_A_Tutorial_for_Beginners_(Part_3)%E2%80%94Creating_Flowcharts)
<!-- prettier-ignore-end -->

导言区新建基本组件：

```latex
\usepackage{tikz}
\usetikzlibrary{shapes.geometric, arrows}

\tikzstyle{startstop} = [rectangle, rounded corners, 
minimum width=3cm, 
minimum height=1cm,
text centered, 
draw=black, 
fill=red!30]

\tikzstyle{io} = [trapezium, 
trapezium stretches=true, % A later addition
trapezium left angle=70, 
trapezium right angle=110, 
minimum width=3cm, 
minimum height=1cm, text centered, 
draw=black, fill=blue!30]

\tikzstyle{process} = [rectangle, 
minimum width=3cm, 
minimum height=1cm, 
text centered, 
text width=3cm, 
draw=black, 
fill=orange!30]

\tikzstyle{decision} = [diamond, 
minimum width=3cm, 
minimum height=1cm, 
text centered, 
draw=black, 
fill=green!30]
\tikzstyle{arrow} = [thick,->,>=stealth]
```

正文：

```latex
\begin{tikzpicture}[node distance=2cm]

\node (start) [startstop] {Start};
\node (in1) [io, below of=start] {Input};
\node (pro1) [process, below of=in1] {Process 1};
\node (dec1) [decision, below of=pro1, yshift=-0.5cm] {Decision 1};

\node (pro2a) [process, below of=dec1, yshift=-0.5cm] {Process 2a
text text text text
text text text 
text text text};

\node (pro2b) [process, right of=dec1, xshift=2cm] {Process 2b};
\node (out1) [io, below of=pro2a] {Output};
\node (stop) [startstop, below of=out1] {Stop};

\draw [arrow] (start) -- (in1);
\draw [arrow] (in1) -- (pro1);
\draw [arrow] (pro1) -- (dec1);
\draw [arrow] (dec1) -- node[anchor=east] {yes} (pro2a);
\draw [arrow] (dec1) -- node[anchor=south] {no} (pro2b);
\draw [arrow] (pro2b) |- (pro1);
\draw [arrow] (pro2a) -- (out1);
\draw [arrow] (out1) -- (stop);

\end{tikzpicture}
```

### 散点图 Scatter Plot

<!-- prettier-ignore-start -->
!!! info 

    - [Overleaf: Pfgplots package](https://www.overleaf.com/learn/latex/Pgfplots_package)
    - [PGFplots Manual: Use Cases involving Scatter Plots](https://tikz.dev/pgfplots/tutorial3)
<!-- prettier-ignore-end -->

一个例子：

```latex
% Preamble: \pgfplotsset{width=7cm,compat=1.18}
\begin{tikzpicture}
\begin{axis}
    \addplot [
        scatter,
        only marks,
        point meta=explicit symbolic,
        scatter/classes={
            a={mark=square*,blue},
            b={mark=triangle*,red},
            c={mark=o,draw=black}% <-- don't add comma
        },
    ] table [meta=label] {
        x      y        label
        0.1    0.15     a
        0.45   0.27     c
        0.02   0.17     a
        0.06   0.1      a
        0.9    0.5      b
        0.5    0.3      c
        0.85   0.52     b
        0.12   0.05     a
        0.73   0.45     b
        0.53   0.25     c
        0.76   0.5      b
        0.55   0.32     c
    };
\end{axis}
\end{tikzpicture}
```