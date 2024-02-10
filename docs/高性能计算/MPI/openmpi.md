# Open MPI

!!! info "参考资料"

    [Open MPI: Videos: General information](https://www.open-mpi.org/video/?category=general)

    该系列视频介绍了 Open MPI 内部的整体框架。

## Open MPI 的编译和构建

参考上面的 EasyBuild Tech Talk I - Part 1 的后半部分内容。

!!! warning "If you think you understand linkers you don't understand anything about linkers."

## Process Management Interface (PMI)

!!! info "参考资料"

    [Slurm: PMIx - Exascale Process Management Interface](https://slurm.schedmd.com/SLUG15/PMIx.pdf)

> PMI enables Resource Managers (RMs) to use their infrastructure to implement advanced support for MPI application acting like RTE daemons.

我们已经知道，集群一般都会有一个像 `slurm` 这样的 Resource Manager（RM）来管理集群资源。PMI 使得 RM 可以使用自己的基础设施来实现对 MPI 应用的高级支持，就像 RTE 守护进程一样。

一般不需要在意 PMI 版本的选择，直到进程数达到 10k 级别才会产生明显影响。

## Tip

!!! tip "框架的兼容性问题"

    各个环境中内嵌的模块版本可能不同，因此常常会引发如下的 Warning:

    ```text
    [1698908851.361644] [GPU01:22592:0]    ucp_context.c:1470 UCX  WARN  UCP version is incompatible, required: 1.15, actual: 1.8 (release 0 /lib/libucp.so.0)
    ```

    这通常是无关紧要的。这些模块的设计都是 version compatible 的，即使版本不同，大部分情况下也可以正常工作。如果版本差异过大，可能会出现问题。

Open MPI 支持多种网络模块，最常用的是 [Unified Communication X (UCX) communication library](https://www.openucx.org/)。如果发现了可用的 InfiniBand 设备，Open MPI 会自动使用 UCX PML。
