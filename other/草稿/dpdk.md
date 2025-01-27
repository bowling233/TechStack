# DPDK



## 问题记录

### 编译相关

- 编译 DPDK 时

    ```text
    Generating drivers/rte_common_ionic.pmd.c with a custom command
    FAILED: drivers/rte_common_ionic.pmd.c
    ...
    Exception: elftools module not found
    ```

    解决方法：`pip` 安装 `pyelftools` 模块

## 其他相关知识

- DMA 机制：包括 IOVA、VFIO 等。
- Linux 内存管理机制：包括 Hugepage、NUMA 等。
- Linux 资源分配机制：包括 cgroup 等。
- 基础线程库 pthread。

- Non-Uniform Memory Access (NUMA)：非一致性内存访问。
    - 与 UMA 相比的优劣：内存带宽增大，需要编程者考虑局部性
    - 每块内存有
        - home：物理上持有该地址空间的处理器
        - owner：持有该块内存值（写了该块内存）的处理器
    - Linux NUMA：https://docs.kernel.org/mm/numa.html
        - Cache Coherent NUMA
        - 硬件资源划分为 node
            - 隐藏了一些细节，不能预期同个 node 上的访存效率相同
            - 每个 node 有自己的内存管理系统
            - Linux 会尽可能为任务分配 node-local 内存
            - 在足够不平衡的条件下，scheduler 会将任务迁移到其他 node，造成访存效率下降
        - Memory Policy
    - Linux 实践
        - `numactl`
        - `lstopo`

- Hugepage
    - 受限于 TLB 大小，Hugepage 会减少 TLB miss
    - 场景：随机访存、大型数据结构
    - https://www.evanjones.ca/hugepages-are-a-good-idea.html
    - https://rigtorp.se/hugepages/
    - 

