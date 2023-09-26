# 矩阵计算（第 4 版）

Matrix Computation (4th Edition)

| Author                             | Year |
| :--------------------------------- | :--- |
| Gene H. Golub, Charles F. Van Loan | 2013 |

## 第 1 章 矩阵乘法

<!-- prettier-ignore-start -->
!!! abstract "本章内容"

    - 基本算法与记号
        - 分块矩阵
        - 基本问题：$C=C+AB$
    - 结构与效率：有特殊性质的矩阵有高效的算法
        - 对称矩阵可以节省一半的存储空间
        - 稀疏矩阵有高效的算法
    - 分块矩阵及其算法
    - 快速矩阵-向量乘法
        - 矩阵的分块结构是递归的，矩阵的块可以被好好利用来代表整个矩阵。
        - 这些算法能用于快速傅立叶变换、三角变换、小波变换等。
    - 向量化和局部性：当矩阵非常大时，局部性原理的重要性愈发凸显。
    - 并行矩阵乘法
<!-- prettier-ignore-end -->

### 1.1 基本算法与记号

在本节，我们练习如何分别用算法和线性代数的语言描述问题，并理解两种表达方式之间的关系。

<!-- prettier-ignore-start -->
!!! example "举个例子"

    计算点乘：

    - 算法描述：$s=0; for i=1:n, s=s+x(i)*y(i); end$
    - 代数描述：$s=x^Ty$
<!-- prettier-ignore-end -->

除了线性代数中基本的矩阵运算，我们又引入了按元素乘法（Hadamard Product）等运算记号。在相应的运算前面加上一点来表示按元素运算，如：$.*$ 和 $./$。

还有一个重要的运算：$y=ax+y$，这里的等号的意义是赋值。这一运算实在是太常用，于是有了简称：**_Saxpy_**（scalar $a$ $x$ plus $y$，在 LAPACK 中使用的术语）。数据处理中我们常常用这一运算更新数据。类似地还有 **_Gaxpy_**（**_g_**eneralized s**_axpy_**，$y=y+Ax$）。

<!-- prettier-ignore-start -->
!!! question "gaxpy 的算法"

    请思考 Gaxpy 的算法。首先，它的时间复杂度是多少？接着分别按行、按列进行思考，这两种方法有什么不同？代数上的表现形式是什么？
<!-- prettier-ignore-end -->

本书还使用类似 Numpy 切片的标记来表示矩阵分块的元素，如矩阵的第 $k$ 行表示为 $A(k,:)$，第 $k$ 列表示为 $A(:,k)$。**试试用这种记号来表示上面的算法，可以去掉一层循环**。这就引入了向量化的思想。

<!-- prettier-ignore-start -->
!!! question "练习：Outer Product Update"

    使用向量化的方法，分别按行、按列描述 $A=A+xy^T$ 的算法。这两种方式都应该使用 saxpy 运算。
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
!!! question "练习：矩阵乘法的向量化表示"

    分别用 saxpy 和 outer product 表示 $2\times 2$ 矩阵乘法：

    $$
    \begin{bmatrix}
     1 & 2\\
     3 & 4
    \end{bmatrix}
    \begin{bmatrix}
     5 & 6\\
     7 & 8
    \end{bmatrix}
    =
    \left [ 
    5\begin{bmatrix}
     1\\
     3
    \end{bmatrix} 
    +
    7\begin{bmatrix}
     2\\
     4
    \end{bmatrix},
    6\begin{bmatrix}
     1\\
     3
    \end{bmatrix} 
    +
    8\begin{bmatrix}
     2\\
     4
    \end{bmatrix}
    \right ]=\begin{bmatrix}
     1\\
    3
    \end{bmatrix}\begin{bmatrix}
     5 &6
    \end{bmatrix}
    +
    \begin{bmatrix}
     2\\
    4
    \end{bmatrix}\begin{bmatrix}
     7 &8
    \end{bmatrix}
    $$

    这两种方法性能等级不同，将在 1.5 中进行分析。
<!-- prettier-ignore-end -->

接下来我们分析 $C=C+AB$ 问题。通常的解决方法是 **ijk** 算法，即三层循环，时间复杂度为 $O(mnr)$。接下来请思考，这三层循环的顺序可以有几种组合？对于这几种组合，它的内层循环是点乘还是 saxpy？这些组合的性能如何？

请尝试理解下面这张表格：

| Loop Order | Inner Loop |   Inner Two Loops    |  Inner Loop Data Access  |
| :--------: | :--------: | :------------------: | :----------------------: |
|    ijk     |    dot     |   vector \* matrix   |  A by row, B by column   |
|    jik     |    dot     |   matrix \* vector   |  A by row, B by column   |
|    ikj     |   saxpy    |      row gaxpy       |    B by row, C by row    |
|    jki     |   saxpy    |     column gaxpy     | A by column, C by column |
|    kij     |   saxpy    |  row outer product   |    B by row, C by row    |
|    kji     |   saxpy    | column outer product | A by column, C by column |
