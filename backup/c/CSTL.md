---
tags:
  - Todo
---

# C 标准库

!!! quote "参考书籍"

    《C 标准库》

## 概述

C 库的设计是与实现是一个很宏大的工程，需要长期的使用和大量的代码阅读才能比较好地理解。我是初次接触库文件，仅简单记忆一些库文件的设计规则。库的测试和一些细节内容就暂不学习了。

### 来自 C 标准的一些内容

- 保留标识符：所有以下划线加一个大写字母或两条下划线开头的标识符都被保留
- 库函数的使用
    - 如果函数参数是无效值（函数定义域外的值、程序地址空间外的指针、空指针），则行为未定义。
    - 任何一个函数可能又作为宏实现了。即使作为宏实现了，也允许获得该函数的地址。
    - 函数的任何宏定义可以通过用括号把函数名字括住来局部抑制它，或者使用 `#undef` 移除宏定义。
    - 通常情况下，对作为宏实现的库函数使用任何表达式作为参数都是安全的。
    - 如果一个库函数不引用头文件中的任何类型定义，那么不用包含它的相关头文件就能使用它。

### 命名空间

- ![image-20230103184959111](assets/image-20230103184959111.png) 图中左侧命名空间掩盖右边的命名空间。
- 块：引入两个命名空间，分别是所有名字（类型定义、函数、数据对象和枚举常量）和标记（枚举、结构和联合）。
- 结构或联合：引入一个命名空间，其中包括所有成员的名字。
- 声明函数原型：引入一个命名空间，其中包括所有参数名
- 定义函数：引入一个命名空间，其中包括所有标号的名字。

### 库的实现和编程风格

- 库中每个可见函数都占据着单独的 C 源文件，文件名就是函数名。
- C 源文件名至多有 8 个小写字母。
- 隐藏的名字都以下划线加一个大写字母开头。
- 隐藏的函数和数据对象通常占据以 `x` 开头命名的 C 源文件。
- 尽可能在嵌套里层的函数中声明数据对象。
- 在每个函数的左大括号后面写上注释。
- 可见函数的定义中，函数名用一对括号括住，阻止宏识别和展开。
