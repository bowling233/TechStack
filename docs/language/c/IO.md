# 关于输入输出和文件的一切

<!-- prettier-ignore-start -->
!!! abstract

    先介绍《C Primer Plus》中讲解的关于文件的基础知识，再叙述 C 标准库中关于文件的实现。
    
<!-- prettier-ignore-end -->

## 让我们先了解一下 C 的输入输出模型

### 缓冲

<!-- prettier-ignore-start -->
!!! note "缓冲输入"
    
    用户输入的字符被收集并储存在缓冲区（buffer）中，**按下 ++enter++ 键后**程序才能使用用户输入的字符。

    - 完全缓冲：仅缓冲区填满时才发送内容、刷新缓冲区，通常用于**文件输入**。
    - 行缓冲：出现换行符时刷新缓冲区，通常用于**键盘输入**。
<!-- prettier-ignore-end -->

与之对应地，无缓冲输入的程序能够立即使用用户输入的内容。

C 标准规定：**输入是缓冲的**。

<!-- prettier-ignore-start -->
??? info "我可以更改输入方式吗？"
    
    UNIX 库中有 `ioctl()` 函数用于指定待输入的类型，但这不属于 C 标准。

    ANSI C 中，可以使用 `setbuf()` 和 `setvbuf()` 控制缓冲，但受限于系统的设置。
<!-- prettier-ignore-end -->

### 流

C 库提供的输入输出方式称为**标准 I/O**，它们是建立在操作系统提供的**底层 I/O** 上的。底层 I/O 之间常常会有一些差异：

<!-- prettier-ignore-start -->
!!! note "各个系统的文件差异"

    | 差异 | UNIX | Windows | MacOS |
    | - | - | - | - |
    | 换行符 | `\n`<br /> LF | `\r\n` <br />CRLF | `\n` (较早的 MacOS 使用 `\r`)<br />LF |
    | 文件结束符 | `^D` | `^Z` | `^D` |

    注：如 `^Z` 代表 `Ctrl+Z`，你可以使用该组合键结束键盘输入。

    文件结尾也不一定由文件结束符标记。事实上，UNIX 系统储存文件大小信息，依据文件大小信息决定文件末尾。
<!-- prettier-ignore-end -->

从概念上看，C 处理的是**流**而不是文件。不同属性和不同种类的输入，由属性更统一的**流**来表示。

<!-- prettier-ignore-start -->
!!! note "流"
    
    打开文件的过程就是把**流与文件相关联**，读写都通过流来完成。
<!-- prettier-ignore-end -->

`getchar()` 和 `scanf()` 等函数读取到文件结尾时会返回一个特殊的值 `EOF`，在 `stdio.h` 中定义了：

```C
#define EOF (-1)
```

你能解释为什么要把它定为 `-1` 吗？

## 字符输入输出

<!-- prettier-ignore-start -->
!!! note "函数和它们的功能"
    
    | 功能 | 函数 | 失败返回值 |
    | - | - | - |
    | `int getchar(void)`<br /> `int getc(FILE *stream)` <br /> `int fgetc(FILE *stream)` | 单字符输入 | EOF |
    | `char *fgets(char *s, int size, FILE *stream)` | 字符串输入 | NULL |
    | `int ungetc(int c, FILE *stream)` | 放回缓冲输入 | EOF |

    注意：以上函数都将字符从缓冲区中的 `unsigned char` 类型转换为 `int` 类型。

    那么这是否会造成 EOF 不能被识别，而是被看作字符呢？
<!-- prettier-ignore-end -->


<!-- prettier-ignore-start -->
!!! note "关于 `getchar()` 函数"
    
    它的返回值是 `int` 类型而非 `char` 类型，值得注意。
<!-- prettier-ignore-end -->

### 换行符问题

这是一个典型的问题：`scanf()` 函数，除了 `%c` 以外的转换说明，都不会读取空白字符（空格、制表符和回车）。

<!-- prettier-ignore-start -->
!!! note "写一个安全的输入函数"
    
    ```C
    char * s_gets(char* st, int n)
    {
        char * ret_val;
        int i = 0;

        ret_val = fgets(st, n, stdin);
        if (ret_val)
        {
            while (st[i] != '\n' && st[i] != '\0)
                i++;
            if (st[i] == '\n')
                st[i] = '\0';
            else //must have words[i] == '\0'
                while (getchar() != '\n')
                    continue;
        }
        return ret_val;
    }
    ```

    这个函数来自《C Primer Plus》，也是书中 13 章以后一直使用的输入函数。这个函数示范了如何使用安全的 `fgets()` 函数，并**将输入统一**，并处理剩余的字符。

    在涉及行的输入时，一定要注意统一行结尾的形式。这对于换行符，特别是**文件结尾处薛定谔的换行符**，有很大作用。
<!-- prettier-ignore-end -->

### 检查输入

可以用于检查输入的方式有以下几种：

1. `scanf()` 的返回值。


## 文件输入输出

## 标准库

