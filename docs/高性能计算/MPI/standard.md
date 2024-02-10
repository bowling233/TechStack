# MPI 标准

!!! info "在哪里可以找到标准"

    MPI 标准存档于 [MPI Forum](https://www.mpi-forum.org/docs/)。

!!! tip "在阅读前，最好能具有一点 Fortran 基础。"

本篇笔记基于 [MPI-3.0](https://www.mpi-forum.org/docs/mpi-3.0/mpi30-report.pdf) 标准，选择它的原因有：

- MPI-3.0 发布于 2012 年。到目前，常用的 MPI 实现如 Intel MPI、Nvidia HPC-X、MPICH 均于2021年左右完成了对 MPI-3.0 的完善的支持。
- MPI-3.0 标准是对 MPI 的重大更新，添加了集合通信的非阻塞版本等内容。
- MPI-3.0 标准比前两版完善，提供了不少示例代码作为参考，适合学习。

??? tip "如何查看当前环境支持的 MPI 版本"

    -   使用 `mpirun --version` 可以查看当前环境的版本，再去查阅对应版本文档找到支持的标准版本。
    -   一般 MPI 实现都会自带测试程序，运行测试程序可以显示各种详细信息，其中包括 `MPI Version` 这样的字段，表示当前环境支持的标准版本。
        -   Open MPI: `ompi_info --all`
        -   Intel MPI: `mpirun -n 2 IMB-MPI1 pingpong`
            ```text
            #----------------------------------------------------------------
            #    Intel(R) MPI Benchmarks 2021.4, MPI-1 part
            #----------------------------------------------------------------
            # Date                  : Thu Nov  2 14:43:30 2023
            # Machine               : x86_64
            # System                : Linux
            # Release               : 5.10.0-0.bpo.15-amd64
            # Version               : #1 SMP Debian 5.10.120-1~bpo10+1 (2022-06-13)
            # MPI Version           : 3.1
            ...
            ```
        -   HPC-X：暂时没有在集群上完成测试，大概是在 `/opt/nvidia/hpc_sdk/Linux_x86_64/23.5/examples/MPI/` 这样的地方会提供一些测试程序。

## Chapter 2 MPI Terms and Conventions

### 命名规范

在 C 中，与特定类型有关的函数名字为 `MPI_Class_action_subset`，类型无关的为 `MPI_Action_subset`。

有一些固定的动词常常用于命名：`Create`、`Get`、`Set`、`Delete`、`Is`。

### 过程规范

MPI 的过程定义与语言无关。过程的参数有三种标记：`IN`、`OUT`、`INOUT`。

- `IN` 调用过程中，不会改变该参数
- `OUT` 会改变该参数
- `INOUT` 可能会使用或改变该参数

这些说明并不是死的，比如 `MPI_STATUS_IGNORE` 这样的常量常常被放置在 `OUT` 的参数中。

!!! warning "`OUT` 和 `INOUT` 类型的参数不应当是任何其他参数的别名。"

    比如：

    ```c
    int a[10]; 
    copyIntBuffer( a, a+3, 7);
    ```

    这里，`a+3` 是 `a` 的别名。

### 术语

- 非阻塞：在操作完成之前返回。
    - 完成一词对于操作、请求、通信有不同的含义。
    - 操作完成：用户被允许重新使用操作所涉及的资源，所有输出都被更新了。
    - 请求完成：如果请求是非持久的，那么请求被释放了。如果请求是持久的，那么请求不活跃（inactive）了。
    - 通信完成：相关的操作都完成了。
