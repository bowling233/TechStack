---
tags:
  - Ongoing
---

# Ch2. 信息的表示和处理

<!-- prettier-ignore-start -->
!!! abstract
    
    本章主要讲解一些和字节编码有关的基础知识，为下一章阅读汇编代码和二进制数据奠定基础。
<!-- prettier-ignore-end -->

-   十六进制表示法：
    -   熟记 `A, C, F` 的二进制表示即可。
-   寻址和字节顺序
    -   Intel 机器一般采用小端法：最低位字节放在最前面。
    -   Android 和 iOS 都只能采用小端法。
    - 在这些方面，字节顺序会产生影响：通过网络传送二进制数据、检查机器级程序和编写规避**类型系统**的程序时。
-   字长
    -   我们常说的“32 位”等，指的是计算机的字长，即指针变量的标称长度。
    -   我们说程序是“32 位”或“64 位”时，指的是程序编译时的配置。

<!-- prettier-ignore-start -->
!!! note

	指针的强制类型转换并不会改变指针的值，只是告诉**编译器**以另一种类型看待该指针。根据书本的描述中，指针和类型系统都由编译器所控制。
<!-- prettier-ignore-end -->

- 布尔代数
    - 掌握简单的四种布尔运算即可。深入的学习在“离散数学及其应用”课程中。
    - 位向量常用于为集合编码。
    - 偶尔见到利用 `a^a=0` 性质编写的三变量交换程序，这是一个技巧，但请不要用在生产环境中。
    - 需要掌握的技能是：如何根据已有的布尔函数，构造所需的布尔函数。我目前使用的方法主要是观察真值表寻找关系。
- 