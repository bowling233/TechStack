---
tags:
    - Ongoing
---

# gcc

!!! quote
[GCC and Make from NTU](https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html)

GCC, formerly for "GNU C Compiler", has grown over times to support many languages such as C (gcc), C++ (g++), Objective-C, Objective-C++, Java (gcj), Fortran (gfortran), Ada (gnat), Go (gccgo), OpenMP, Cilk Plus, and OpenAcc. It is now referred to as "GNU Compiler Collection".

GCC is a key component of so-called "GNU Toolchain", for developing applications and writing operating systems. The GNU Toolchain includes:

1. GNU Compiler Collection (GCC): a compiler suite that supports many languages, such as C/C++ and Objective-C/C++.
2. GNU Make: an automation tool for compiling and building applications.
3. GNU Binutils: a suite of binary utility tools, including linker and assembler.
4. GNU Debugger (GDB).
5. GNU Autotools: A build system including Autoconf, Autoheader, Automake and Libtool.
6. GNU Bison: a parser generator (similar to lex and yacc).

GCC is portable and run in many operating platforms. GCC (and GNU Toolchain) is currently available on all Unixes. They are also ported to Windows (by Cygwin, MinGW and MinGW-W64). GCC is also a cross-compiler, for producing executables on different platform.

## Windows 上的 GCC 套件

首先你需要了解一些 Windows 上 GNU 编译器相关的知识。不想了解的话，无脑选择已编译好的下载即可。下载地址在 [SourceForge](https://sourceforge.net/projects/mingw-w64/files/)，选择 `x86_64-posix-seh` 版本即可。

??? info "关于 mingw-w64 版本的疑惑"
可以参看操作系统方面的笔记。

    `posix` 和 `win32`：不用疑惑了，那些东西只影响是否能使用 `<thread>` 头文件。当你配置环境的时候，离学这东西还有很远。

    `sjlj` 和 `seh`：与错误处理系统（exception handling systems）有关。在现代系统上，选择 `seh` 即可。

## 基本知识

??? info "编译工具流"
![Preprocessor, Compiler, Assembler and Linker](https://www3.ntu.edu.sg/home/ehchua/programming/cpp/images/GCC_CompilationProcess.png)
接下来分步使用这些工具链：

    1. 预处理（Pre-processing）：`cpp hello.c > hello.i`
    2. 编译（compilation）：`gcc -S hello.i`
    3. 汇编（Assembly）：`as -o hello.o hello.s`
    4. 链接（Linker）：`ld -o hello.exe hello.o ...libraries...`

### `gcc` 命令

命令格式：`gcc [options] file...`，注意文件放在最后面。文件可以是源代码、目标代码……

| 选项      | 作用                                                 |
| --------- | ---------------------------------------------------- |
| `-o`      | 输出文件名                                           |
| `-Wall`   | all Warning                                          |
| `-g`      | 生成附加的调试信息，供 `gdb` 使用                    |
| `-c`      | 仅 compile，操作 `.c` 源代码文件，生成 `.o` 目标文件 |
| `-shared` | 编译为动态链接库（`.dll` 或 `.so`（Unix）等）        |
| `-v`      | verbose 冗长的输出信息                               |

!!! info
`gcc` 使用 `ld` 来执行链接。关于连接库的更多信息请看参考资料。

多文件编程只需要把文件依次放在后面就好了。但通常，我们单独编译，最后再一起链接（模块化编程）

### 辅助工具

-   检查目标文件或可执行文件
    -   `file` 确认文件类型，可以显示可执行文件的详细信息。
    -   `nm` 列出的符号表（symbol table）
        -   用于检查某个文件是否定义了某个函数。
    -   `ldd` 列出需要的共享库。
