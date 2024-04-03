# MPI 使用 

## 介绍

=== "OpenMPI"

    !!! info "参考资料"

        [Open MPI: Videos: General information](https://www.open-mpi.org/video/?category=general)

        该系列视频介绍了 Open MPI 内部的整体框架。

    - 编译和构建

    参考上面的 EasyBuild Tech Talk I - Part 1 的后半部分内容。

    !!! warning "If you think you understand linkers you don't understand anything about linkers."

    ## Process Management Interface (PMI)

    !!! info "参考资料"

        [Slurm: PMIx - Exascale Process Management Interface](https://slurm.schedmd.com/SLUG15/PMIx.pdf)

    > PMI enables Resource Managers (RMs) to use their infrastructure to implement advanced support for MPI application acting like RTE daemons.

    我们已经知道，集群一般都会有一个像 `slurm` 这样的 Resource Manager（RM）来管理集群资源。PMI 使得 RM 可以使用自己的基础设施来实现对 MPI 应用的高级支持，就像 RTE 守护进程一样。

    一般不需要在意 PMI 版本的选择，直到进程数达到 10k 级别才会产生明显影响。

    !!! tip "框架的兼容性问题"

        各个环境中内嵌的模块版本可能不同，因此常常会引发如下的 Warning:

        ```text
        [1698908851.361644] [GPU01:22592:0]    ucp_context.c:1470 UCX  WARN  UCP version is incompatible, required: 1.15, actual: 1.8 (release 0 /lib/libucp.so.0)
        ```

        这通常是无关紧要的。这些模块的设计都是 version compatible 的，即使版本不同，大部分情况下也可以正常工作。如果版本差异过大，可能会出现问题。

    Open MPI 支持多种网络模块，最常用的是 [Unified Communication X (UCX) communication library](https://www.openucx.org/)。如果发现了可用的 InfiniBand 设备，Open MPI 会自动使用 UCX PML。

=== "oneAPI"

    > <https://www.intel.com/content/www/us/en/docs/mpi-library/developer-reference-linux/2021-11/overview.html>

    - Spack

    oneAPI 的包在 Spack 中均以 `intel-oneapi-` 开头，选择需要的安装即可。有些包名相同但中间没有 `oneapi`，大概率是废弃的包。

    - 从官网下载安装

    通过官网下载安装的需要执行脚本 `oneapi/setvars.sh` 加载环境变量，会列出加载了的组件，`vtune`、`itac` 等分析工具也会被加载。

## 概念

### 调度算法

- Round-Robin 时间片轮转：将相等长度的时间片按照不变的顺序依次分配给每个进程，且在处理所有进程时不考虑任何优先级。

==todo==

### 绑定

==todo==

## 运行

=== "OpenMPI"

    `mpirun` `mpiexec` `orterun` 是同一个命令。

    `mpirun` 也可以运行多个程序，指定全局、局部选项，这里不作介绍。

    OpenMPI 使用 Slot 作为资源分配单位，有多少个 Slot 就可以运行多少个进程。

    - 默认：处理器核数。
    - 使用超线程核心数：用 `--use-hwthread-cpus` 开启，常见为 2 倍处理器核数。可以在 `lscpu` 中的 `Thread(s) per core` 查看。
    - 资源管理器调度：从资源管理器获取 Slot 数。
    - 需要注意：Slot 数和硬件没有关系，可能比硬件核数多，也可能比硬件核数少。

=== "Intel MPI"

    对 Intel MPI 来说，`mpirun` 是 `mpiexec.hydra` 的包装。其选项有全局选项和局部选项之分，一般以 `g` 开头的参数是全局选项，下文不对全局和局部选项分别介绍。
    
    可以编写文件保存选项，使用 `-configfile` 指定配置文件，`#` 注释。`./mpiexec.conf` 会自动加载。

    - 环境变量
        - `-genv <ENVVAR> <val>` 指定运行时环境变量，常用的有：`OMP_`
        - `-genvall, -genvnone` 控制是否传递环境变量
    - profiling:
        - `-trace` `-aps` `-mps`
    - 设备：
        - `iface`
    - 运行参数：
        - `-n, -np` 进程数
        - `-env` 环境变量
        - `-path` 可执行文件

### 资源管理器

下文以 Slurm 为例。

#### 角色

#### 与 MPI 的交互

MPI 与资源管理器可以通过三种方式交互：

- Slurm 启动 MPI 并行程序，并通过 PMI API（Process Management Interface）调用执行初始化。
- Slurm 分配资源，然后由 `mpirun` 基于 Slurm 的基础设施启动并行程序。`srun` 就是这种方式。
- Slurm 分配资源，然后由 `mpirun` 通过 SSH 等其他机制启动并行程序。这种方式下，Slurm 无法进行资源管控和追踪。

#### 命令行与脚本运行

命令行使用 `srun` 执行，脚本使用 `sbatch` 提交。脚本内可以含有 `#SBATCH` 开头的指令，附带任意命令行参数。遇到第一个非注释行后停止解析参数。

我个人习惯在脚本中定义所有参数以便于管理，下面是一般模板：

```bash
#!/bin/bash
#SBATCH --job-name=mpi_test --output=%x.%j.out
#SBATCH --time=04:00:00 --partition=RM
#SBATCH --nodes=2 --ntasks-per-node=1 --cpus-per-task=40
export OMP_NUM_THREADS=${SLURM_CPUS_PER_TASK}
set -x
date
time mpirun -np $SLURM_NTASKS
```

其中 `--cpus-per-task` 在 OpenMP 时使用，`--ntasks-per-node` 一般设置为 1。注意上面使用环境变量传递参数，避免手动修改多处。

有时为了提高效率，还会将文件拷贝到计算节点上：

```bash
sourcedir=$PROJECT/regcm/ompi
RC=1
n=0
while [[ $RC -ne 0 && $n -lt 20 ]]; do
    rsync -aP $sourcedir $LOCAL/
    RC=$?
    let n=n+1
    sleep 10
done

destdir=$PROJECT/regcm/results/ompi64.4p
mkdir -p $destdir
RC=1
n=0
while [[ $RC -ne 0 && $n -lt 20 ]]; do
    rsync -aP $LOCAL/ $destdir
    RC=$?
    let n=n+1
    sleep 10
done
```

#### 其他工具

- `sinfo`
- `squeue`
    - `-u <user>`
- `scontrol`
- `sacct -j <jobid>`：查看任务的详细信息
    - `--json` 按 JSON 格式输出所有信息
    - `--long` 输出所有信息，但一般乱成一团看不了
