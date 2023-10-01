# 如何写出一份精美的实验报告

一份实验报告，最重要的是其内容，其次才是版面。

要写出一份精美的实验报告，首选的工具是 LaTeX。想要完全学懂 LaTeX 是很难的，也是没有必要的。只需要学会基础语法，遇到需要什么功能时再去网上查找相关资料即可。本文汇总一些我写实验报告时常用的功能模板，仅供参考

## 基础组件

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
!!! info "参考资料"

    [Stack Exchange: Right alignment of column in table column](https://tex.stackexchange.com/questions/199744/right-alignment-of-column-in-table-column)
<!-- prettier-ignore-end -->

导言区新建列类型：

```latex
\newcolumntype{R}[1]{>{\RaggedLeft\arraybackslash}p{#1}}
```

正文：

```latex
\begin{table}[h!]
    \caption{输入输出层接口}
    \resizebox{\textwidth}{!}{
        \begin{tabular}{R{1.5cm} R{2.5cm} p{5cm} p{4cm}}
            \toprule
            类型        & 标识符          & 参数                            & 描述           \\
            \midrule
            void&InputData&(char *fileName)&从指定文件导入数据 \\
            void&OutputData&(char *fileName)&向指定文件输出数据      \\
            \bottomrule
        \end{tabular}
    }
\end{table}
```

#### 三线表

<!-- prettier-ignore-start -->
!!! info "参考资料"

    [知乎：LaTeX保姆级教程|插入三线表](https://zhuanlan.zhihu.com/p/440498868)
<!-- prettier-ignore-end -->

导言区：

```latex
\usepackage{booktabs}
\usepackage{array}
\usepackage{ragged2e}
\newcolumntype{R}[1]{>{\RaggedLeft\arraybackslash}p{#1}}
```

正文：

```latex
\begin{table}[h!]
    \caption{输入输出层接口}
    \resizebox{\textwidth}{!}{
        \begin{tabular}{R{1.5cm} R{2.5cm} p{5cm} p{4cm}}
            \toprule
            类型        & 标识符          & 参数                            & 描述           \\
            \midrule
            void&InputData&(char *fileName)&从指定文件导入数据 \\
            void&OutputData&(char *fileName)&向指定文件输出数据      \\
            \bottomrule
        \end{tabular}
    }
\end{table}
```

## 代码相关

### 代码清单 Code List

<!-- prettier-ignore-start -->
!!! info "参考资料"

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
!!! info "参考资料"

    [Overleaf：Algorithms](https://www.overleaf.com/learn/latex/Algorithms)
<!-- prettier-ignore-end -->

一般使用 `algorithm2e` 宏包，导言区：

```latex
\usepackage[ruled]{algorithm2e}
%% This declares a command \Comment
%% The argument will be surrounded by /* ... */
\SetKwComment{Comment}{/* }{ */}
```

上面的代码块开启了 `ruled` 以显示边框，也写了一个自定义的注释命令 `\Comment`。

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

可以在 `algorithm` 环境中使用 `caption`、`ref` 等命令。环境中的每一行（除了 `{}` 表示的块的开始和结尾）都需要以 `\;` 结尾。



## 特殊组件

### 流程图

<!-- prettier-ignore-start -->
!!! info "参考资料"

    [Overleaf: Creating Flowcharts](https://www.overleaf.com/learn/latex/LaTeX_Graphics_using_TikZ%3A_A_Tutorial_for_Beginners_(Part_3)%E2%80%94Creating_Flowcharts)
<!-- prettier-ignore-end -->

导言区新建基本组件：

```latex
\usepackage{tikz}
\usetikzlibrary{shapes.geometric, arrows}
%define boxes: startstop, io, process, decision, arrow
\tikzstyle{startstop} = [rectangle, rounded corners, minimum width=3cm, minimum height=1cm,text centered, draw=black, fill=red!30]
\tikzstyle{io} = [trapezium, trapezium left angle=70, trapezium right angle=110, minimum width=3cm, minimum height=1cm, text width=3cm, text centered, draw=black, fill=blue!30]
\tikzstyle{process} = [rectangle, minimum width=3cm, minimum height=1cm, text centered, draw=black, fill=orange!30]
\tikzstyle{decision} = [diamond, minimum width=3cm, minimum height=1cm, text centered, draw=black, fill=green!30]
\tikzstyle{arrow} = [thick,->,>=stealth]
```

正文：

```latex
\begin{tikzpicture}[node distance=2cm]
    \node (start) [startstop] {Start};
    \node (init) [process, below of=start] {init()};
    \node (draw) [process, right of=init, xshift = 2cm] {paint()};
    \node (in) [io, below of=draw] {Keyboard or CharEvent};
    \node (dec) [decision, below of=in, yshift=-0.5cm] {KeyValue==?};
    \node (print) [process, below of=dec, yshift=-0.5cm] {printf()};
    \node (handle) [process, right of=dec, xshift=3cm] {Edit Process};
    \node (stop) [startstop, left of=print, xshift=-2cm] {Stop};
    \draw [arrow] (start) -- (init);
    \draw [arrow] (init) -- (draw);
    \draw [arrow] (draw) -- (in);
    \draw [arrow] (in) -- (dec);
    \draw [arrow] (dec) -- node [anchor=south]{otherKey} (handle);
    \draw [arrow] (handle) |- (draw);
    \draw [arrow] (dec) -- node [anchor=west]{VK\_ENTER} (print);
    \draw [arrow] (print) -- (stop);
    \node (timer) [process, below of=init] {startTimer()};
    \node (blink) [process, below of=timer] {show/hideCaret()};
    \draw [arrow] (init) -- (timer);
    \draw [arrow] (timer) -- (blink);
    \node (cancelTimer) [process, right of=print, xshift=3cm] {DestroyWindow()};
    \draw [arrow] (print) -- (cancelTimer);
\end{tikzpicture}
```