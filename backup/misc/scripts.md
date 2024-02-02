# 各类脚本语言备忘录

在日常工作中，如果能够熟练使用脚本语言，可以大大提高工作效率。本文档主要记录一些脚本语言的使用方法。

本文档不是教程，只是对所学知识的简单总结，方便复习使用。初学者请参考其他教程。

## Makefile

<!-- prettier-ignore-start -->
::cards::

[
  {
    "title": "GNU Make 常用参数",
    "content": "
                `-f` `--file=file` 指定文件 <br>
                `-n` `--dry-run` 打印命令但不执行 <br>
                `-s` `--silent` 不打印执行的命令 <br>
                ",
  },
  {
    "title": "基础语法",
    "content": "
                1. ++tab++ 缩进 <br>
                2. `\\` 换行 <br>
                3. `#` 注释
                4. `@` 不打印执行的命令 <br>
                5. `;` 上一条命令将作用于下一条命令 <br>",
  },
  {
    "title": "基础变量",
    "content": "
                1. 创建变量 `obj = main.o kdb.o` <br>
                2. 引用变量 `$(obj)` <br>
                3. ",
  },
  {
    "title": "特殊变量",
    "content": "
                1. `VPATH` 文件搜索路径，`:` 分隔 <br>",
  },
  {
    "title": "关键字",
    "content": "
                1. `vpath <pattern> <dir>` 清除/指定类型文件搜索路径 <br>
                2. ",
  },
  {
    "title": "通配符",
    "content": "
                1. `*` <br>
                2. `?` <br>
                3. `%` <br>",
  },
  {
    "title": "自动化变量",
    "content": "
                1. `$@` 目标文件 <br>
                2. `$<` 第一个依赖文件 <br>
                3. `$^` 所有依赖文件 <br>
                4. `$?` 比目标文件更新的依赖文件 <br>
                5. `$*` 不包含后缀的目标文件 <br>",
  },
  {
    "title": "函数",
    "content": "
                1. 使用函数 `$(function arguments)` <br>
                2. `subst <from>,<to>,<text>` 替换 <br>
                3. `patsubst <pattern>,<replacement>,<text>` 模式替换 <br>
                4. `strip <string>` 去除空格 <br>",
  },
  {
    "title": "",
    "content": "",
  },
  {
    "title": "",
    "content": "",
  },

]

::/cards::
<!-- prettier-ignore-end -->

- 静态模式

```makefile
<targets...>: <target-pattern>: <prereq-patterns...>
    <commands>
objects = foo.o bar.o

all: $(objects)

$(objects): %.o: %.c
    $(CC) -c $(CFLAGS) $< -o $@

```

## Bash

## CMake

<!-- prettier-ignore-start -->
!!! info "[CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)"
<!-- prettier-ignore-end -->

基本结构：

```cmake
cmake_minimum_required()
project()
add_executable()
```

