# 从 GCC 到 CMake

<!-- prettier-ignore-start -->
!!! abstract "通过本教程你能学会什么？"
    
    - 了解程序的编译过程
    - 解决编译和链接中的问题
    - 学会使用调试器诊断程序的错误
    - 接触 Make、CMake 等构建工具
<!-- prettier-ignore-end -->

## GCC 和 LLVM 简介

简单来说：
- `gcc` 是最通用的编译器，它由开源社区提供支持，但由于历史原因，它有一些奇怪的功能和实现，有时会引起困惑。
- `clang` 是一个较新的编译器，它最初由苹果公司开发（你在 macOS 上使用的 `gcc` 就是 `clang` 的别名）。它提供了比 `gcc` 更好的编译体验。

`gcc` 和 `clang` 如今作为成熟的编译器，在初学和日常使用时基本没有任何区别。考虑到通用性，我们选择主讲 `gcc`。

<!-- prettier-ignore-start -->
??? note "一张表格简要总结 GCC 和 LLVM 的不同"
    
    | 项目 | GCC | LLVM |
    | - | - | - |
    | 编译器 | `gcc` | `clang` |
    | 链接器 | `ld` | `lld` |
    | 调试器 | `gdb` | `lldb` |
    | 构建工具 | `make` | `cmake` |
    | 支持 | GNU | Google, Microsoft, Apple, Intel 等|

<!-- prettier-ignore-end -->

## 编译过程

让我们先来了解一下编译步骤。



## 使用 gdb 调试程序

<!-- prettier-ignore-start -->
!!! info "参考资料"

    - [GDB Tutorial - A Walkthrough with Examples](https://www.cs.umd.edu/~srhuang/teaching/cmsc212/gdb-tutorial-handout.pdf)
<!-- prettier-ignore-end -->

- 在 gcc 中添加调试选项

为了使用 gdb 进行调试，我们需要在 gcc 的编译参数中添加 `-g`。

```bash
gcc [flags] -g <sources files> -o <output>
```

- 启动gdb

```bash
gdb prog1.x
```

你会得到这样的提示符，说明你进入了调试器。

```gdb
(gdb)
```

这是 gdb 的交互式终端，和你在 Linux 系统中用的功能一致，比如可以查询历史命令、自动补全等。

<!-- prettier-ignore-start -->
!!! note "gdb 中的命令"
    
    | 命令 | 功能 |
    | - | - |
    | `help [command]` | 获取命令帮助 |
    | `file [program]` | 加载指定文件进行调试 |
    | `run` | 运行已经加载的程序 |
<!-- prettier-ignore-end -->

- 调试




<!-- prettier-ignore-start -->
!!! quote
    [GCC and Make Compiling, Linking and Building C/C++ Applications](https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html)
<!-- prettier-ignore-end -->

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

<!-- prettier-ignore-start -->
??? info "关于 mingw-w64 版本的疑惑"

    可以参看操作系统方面的笔记。
    
    `posix` 和 `win32`：不用疑惑，那些东西只影响是否能使用 `<thread>` 头文件。当你配置环境的时候，离学这东西还有很远。
    
    `sjlj` 和 `seh`：与错误处理系统（exception handling systems）有关。在现代系统上，选择 `seh` 即可。
<!-- prettier-ignore-end -->

## 基本知识

<!-- prettier-ignore-start -->
??? info "编译工具流"

    ![Preprocessor, Compiler, Assembler and Linker](https://www3.ntu.edu.sg/home/ehchua/programming/cpp/images/GCC_CompilationProcess.png)
    
    接下来分步使用这些工具链：
    
    1. 预处理（Pre-processing）：`cpp hello.c > hello.i`
    2. 编译（compilation）：`gcc -S hello.i`
    3. 汇编（Assembly）：`as -o hello.o hello.s`
    4. 链接（Linker）：`ld -o hello.exe hello.o ...libraries...`
<!-- prettier-ignore-end -->

### `gcc` 命令

命令格式：`gcc [options] file...`，注意文件放在最后面。文件可以是源代码、目标代码……

| Option    | Usuage                                            |
| --------- | ------------------------------------------------- |
| `-o`      | **o**utput executable filename                    |
| `-Wall`   | **all W**arning                                   |
| `-g`      | additional debug information provided for `gdb`   |
| `-c`      | **c**ompile into *object file*`.o`                |
| `-shared` | compile to dynamic link library (`.dll` or `.so`) |
| `-v`      | **v**erbose output                                |

<!-- prettier-ignore-start -->
!!! info

    当输入文件后缀为 `.o` 时，`gcc` 使用 `ld` 来执行链接。关于连接库的更多信息请看参考资料。
<!-- prettier-ignore-end -->

多文件编程只需要把文件依次放在后面就好了。但通常，我们单独编译，最后再一起链接（模块化编程）

### 拆解 GCC 编译过程

GCC 将源代码编译为可执行程序有四个步骤：

1. 预处理器：`cpp hello.c > hello.i`
2. 编译：`gcc -S hello.i`
3. 汇编：`as -o hello.o hello.s`
4. 链接：`ld -o hello.exe hello.o ...libraries...`

### 链接

| 名称   | Windows                       | Linux                  |
| ------ | ----------------------------- | ---------------------- |
| 静态库 | `.lib`                        | `.a` (achive)          |
| 共享库 | `.dll` (dynamic link library) | `.so` (shared objects) |

- 静态库：机器码在链接时直接拷贝到程序中。
- 共享库：链接时，只在程序中创建一个表。程序执行前，操作系统将需要的机器码载入内存，这就是**动态链接**。一个共享库能被多个程序共享，多数操作系统也允许共享库在内存中的拷贝被共享。因此共享库可以节省存储空间和内存，GCC 默认链接到共享库。

### PATH

| 文件       | 参数指定         | 环境变量                                      |
| ---------- | ---------------- | --------------------------------------------- |
| 可执行文件 |                  | PATH                                          |
| 头文件     | -I*dir*          | CPATH<br />C_INCLUDE_PATH, CPLUS_INCLUDE_PATH |
| 库文件     | -L*dir*, -l*lib* | LIBRARY_PATH                                  |

- 库文件的名称：在 Unix 系统中，名为 `libxxx.a` 的库通过参数 `-lxxx` 指定，不需要 `lib ` 前缀和 `.a` 后缀。在 Windows 系统中指定完整的文件名。



<!-- prettier-ignore-start -->
!!! info "辅助工具"

    -   检查目标文件或可执行文件
        -   `file` 确认文件类型，可以显示可执行文件的详细信息。
        -   `nm` 列出符号表（symbol table）
            -   用于检查某个文件是否定义了某个函数。
            -   `T` 表示函数已定义，`U` 表示函数未定义，需要链接。
        -   `ldd` 列出需要的共享库。
<!-- prettier-ignore-end -->

