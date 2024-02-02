# Lab 2.5 SIMD Vectorization

<!-- prettier-ignore-start -->
!!! info "参考资料"

    - [C/C++指令集介绍以及优化（主要针对SSE优化）_指令集优化_LoveMIss-Y的博客-CSDN博客](https://blog.csdn.net/qq_27825451/article/details/103934359)
<!-- prettier-ignore-end -->

## 为什么要使用 SIMD 指令？

除了 SIMD 对数据进行并行操作外，处理器还可能提供融合乘法加法（Fused Multiply-Add, FMA）指令，可以在一条指令中同时执行乘法和加法。这使得我们可以方便得进行这样的计算：

$$
z = x + y \times a
$$

使用特殊的函数（被称为 Intrinsics）或者直接写汇编指令，我们可以利用这些指令集来最大化并行性。

下面的伪代码对比展示了使用 SIMD 指令和不使用 SIMD 指令的数组计算过程

<!-- prettier-ignore-start -->
=== "without SIMD"
    ```
    for each f in array
    {
        load f to floating-point register
        calculate the square root
        write the result from the register to memory
    }
    ```
=== "with SIMD"
    ```
    for each N floats in array
    {
        load N floats to SIMD register
        calculate N square roots in one operation
        store N results from the register to memory
    }
    ```
<!-- prettier-ignore-end -->

这似乎有点像循环展开。

## x86 架构下的各类 SIMD 指令集简介

### MMX 指令集

具有 `mm0-mm7` 8 个 64 位寄存器，并非独立，而是复用了一些浮点数寄存器。

三个步骤：

- 从整数值创建打包整数，载入 `mmx` 寄存器
- 用 MMX 指令集计算
- 从 `mmx` 获得结果，存入内存

### SSE 指令集

<!-- prettier-ignore-start -->
!!! info "参考资料"

    - [SSE指令集学习笔记 - 吴俊贤的博客](https://packagewjx.github.io/2018/11/12/sse-note/)
<!-- prettier-ignore-end -->

具有从 `xmm0-xmm7` 8 个 128 位寄存器。后来在 x86-64 架构下，扩展到 16 个 128 位寄存器 `xmm0-xmm15`。

相比于 MMX 指令集，SSE 加入了浮点支持。以下是 SSE 指令集几个版本的主要特点：

- SSE：将 MMX 指令集的 64 位寄存器扩展到 128 位，支持了浮点数运算。
- SSE2：支持了 64 位双精度浮点数和整型数据（完全覆盖了 MMX 指令集），同时避免了占用浮点数寄存器。额外的 8 个寄存器正是在该版本被加入。
- SSE3：寄存器局部位之间的运算、浮点数到整数的转换、超线程支持。
- SSE4：新增了一些多媒体指令集

### AVX 指令集

具有 `ymm0-ymm15` 16 个 256 位寄存器。

- AVX：将 SSE 指令集的 128 位寄存器扩展到 256 位并做一些增强。
- AVX2：新增 256 位整数向量操作等。
- AVX-512：将 256 位寄存器扩展到 512 位。

## AVX 指令集详解

因为本次实验我选用了 AVX2 指令集，所以仅对其进行详细介绍。

<!-- prettier-ignore-start -->
!!! info "参考资料"

    - [Intel AVX2](https://www.intel.com/content/www/us/en/docs/cpp-compiler/developer-guide-reference/2021-8/intrinsics-for-avx2.html)
<!-- prettier-ignore-end -->

### 编译

在 C/C++ 中使用 AVX 指令集，应当使用 `immintrin.h` 头文件。如果你安装了 Visual Studio，MSVC 一般会提供这个头文件。你可能在搜索资料的过程中了解到 AVX 指令集的头文件是 `avxintrin.h`，但不应当直接使用它，原因如下：

> `avxintrin.h` from gcc8.2 has an ifdef for # error "Never use `<avxintrin.h>` directly; include `<immintrin.h>` instead.".
>
> 使用 `intrin.h` 则自动引入编译器支持的所有 Intrinsic 头文件。

使用 `__AVX__` 和 `__AVX2__` 宏可以判断是否支持 AVX 和 AVX2 指令集。使用 `gcc` 编译时应当添加 `-mavx` 和 `-mavx2` 参数。你可以尝试分别添加这两个参数，然后看看上面的两个宏有没有定义。

### 数据类型

Intrinsics 的数据类型命名格式为 `_m<size><type>`，列举如下：

`_m64`、`_m128`、`_m128d`、`_m128i`、`_m256`、`_m256d`、`_m256i`、`_m512`、`_m512d`、`_m512i`

这些数据常常被叫做向量（Vector）数据类型。

### 指令

Intrinsics 指令的命名格式为：

```
_mm_<intrin_op>_<suffix>
```

- `intrin_op` 是指令操作的名称，如 `add`、`sub` 等。
    - 加载和存储：`load`、`store`、`loadu`、`storeu`。带 `u` 的表示不对齐。
    - 广播：`load1`、`set1`、`setzero`。`load1` 从内存中加载一个值，然后将其复制到所有向量元素中；`set1` 将一个值复制到所有向量元素中；`setzero` 将所有向量元素置零。
    - 算术：`mul` 向量相乘。
- `suffix` 是指令操作的数据类型
    - 第一个或前两个字符表面数据是：(p)acked（打包）、(e)xtended (p)acket（扩展打包）、(s)calar（标量）
    - 其余的表示数据类型，举例如下
        - `d`：双精度浮点数
        - `i128`：有符号 128 位整数
        - `u64`：无符号 64 位整数

示例请参考 [Naming and Usage Syntax](https://www.intel.com/content/www/us/en/docs/cpp-compiler/developer-guide-reference/2021-8/naming-and-usage-syntax.html)。

AVX 指令的命名格式为：

```
_mm256_<intrin_op>_<suffix>(<data type> <parameter1>, <data type> <parameter2>, <data type> <parameter3>) 
```

使用例：

```c
double a[4] = {1.0, 2.0, 3.0, 4.0};
__m256d v = _mm256_loadu_pd(a);
__m256d t = _mm256_set_pd(4.0, 3.0, 2.0, 1.0);
double b[4];
_mm256_storeu_pd(b, _mm256_add_pd(v, t));
```

后两行命令是等价的。你可以发现，数据在寄存器中是逆序存储的。打包的值以从右到左的顺序存储在寄存器中。

![](https://www.intel.com/content/dam/docs/us/en/developer-guide-reference/2021-8/37551013-74CE-4842-AF87-0E3612E24EC6-low.jpg)

从寄存器中取出数据的命令为 `_mm256_storeu_pd`，它的参数是一个 `double` 指针和一个 `__m256d` 类型的寄存器，这点可以从名字上看出。

### 矩阵乘法实例







