# HPC BenchMark

HPC 比赛通常会有一个 LINPACK 环节，要求在机器上跑出尽可能快的结果。了解一下 BenchMark 的算法细节是有必要的。

## HPCG

!!! info "参考文献"

    - [(2014) NVIDIA Technical Blog: Optimizing the High Performance Conjugate Gradient Benchmark on GPUs](https://arc.net/l/quote/jnlsbgft)
    - [(2018) GENKU's Blog: CG 和 PCG 算法实现和分析](https://blog.genkun.me/post/cg-pcg-implementation/)
    - [(2019) SX-Aurora Vector Engine: HPCG Performance Efficiency on VE at 5.99%](https://sx-aurora.github.io/posts/hpcg-tuning/)

简单概括：HPCG 使用预处理共轭梯度算法求解稀疏矩阵。比起 HPL，它更加侧重于内存和网络性能。

HPCG 算法中有三个重点：

- 预处理 $w=M^{-1}y$，这里使用的 SYMGS 方法难以并行化
- 稀疏矩阵-向量乘积 $Ay$，容易并行化，遵循经典的矩阵乘法的并行化方法即可
- 向量内积

这些操作都 BLAS1 或 BLAS2 级别，计算密度低。
