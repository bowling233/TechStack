# OpenMP/MPI

OpenMP 在单节点上处理密集型计算，MPI 在多节点之间通信。

## OpenMP

使用 OpenMP 无需配置环境，只需要编译器支持即可。OpenMP 使用增量式开发的方式，即在已有串行程序上增加指令即可变成并行程序。

- 使用 gcc 编译 OpenMP 程序：带上 `-fopenmp` 即可。

在 MacOS 上编译 OpenMP 程序：

- 使用 Homebrew 安装 OpenMP：`brew install libomp`
- 使用 clang 编译 OpenMP 程序：`clang -Xclang -fopenmp -L/opt/homebrew/opt/libomp/lib -I/opt/homebrew/opt/libomp/include -lomp omptest.c -o omptest`

### 基本框架

- 头文件 `omp.h`
    - 应当在包含该头文件前检查 `_OPENMP` 是否定义。已定义则可包含。

```C
#ifdef _OPENMP
    #include <omp.h>
#endif
```

- 该线程的编号，称为 rank，用 `omp_get_thread_num()` 获取
- 总线程数，用 `omp_get_num_threads()` 获取

### 指令

以 `#pragma omp` 开头，后面是指令，指令后面是子句。

指令：

- `parallel`

子句：

- `num_threads(thread_count)`

几个要点：

- 隐式 barrier
- fork-join 模型，每个线程有自己的 PC、stack，局部变量私有。
- 标准输出共享，没有调度，因此打印顺序不确定。

### 典例：计算梯形积分

- 串行版本：`for` 循环计算每个子区间。
- 第一版并行
    - 弄成一个函数，每个函数计算其中 `n/thread_count` 个子区间。函数内根据自己的 `rank` 计算自己的区间。
    - 为避免 **race condition**，向该函数传入放置全局变量的指针，使用 `critical` 指令标记临界区，这样每次只有一个线程更新全局变量。
    - 如果不能整除，应该报错，否则会少算一些梯形的面积。


### 作用域

这里的作用域是指能访问变量的线程的集合。线程组都能就是共享，单个线程就是私有。

- 在 `parallel` 块之前的都是默认共享的。（块结束时值也不会变成开始时的值。）
- 块中的变量为私有。

### `reduction` 子句

`reduction` 子句可用于 `parallel` 块。语法：`reduction(<operator>:<varibale list)`。

用例：

```C
#pragma omp parallel num_threads(thread_count) \
    reduction(+: global_result)
    global_result += Local_trap();
```

它其实是以下步骤的简化表达：

- 创建私有变量存储每个线程的结果。
- 在临界区中将私有变量的值归约。

能够被归约的操作符显然应该是可交换的，有：

```
+ * & | ^ && ||
```

虽然减法也算归约操作符，但它不符合交换律和结合律，因此计算结果不统一，不应当使用。此外，**浮点数**也不满足结合律，需要谨慎使用。

### `for` 子句

`parallel for` 指令只能并行化一些 `for` 循环，大部分实现都是把循环划分成 `m/thread_count` 个大块。它有一些使用条件：

- `for` 语句确定，即不能 `for(;;)`
- 其中不能有 `if break` 这样的分支，这给循环提供了一个特殊的出口。
- `index` 变量只能被 `for` 语句的增量部分修改。

满足这些条件的循环能够在执行前确定迭代次数。如果不满足会报错如 `invalid exit from OpenMP structured block`。

此外，具有**数据依赖**的循环也不应当被并行化，虽然**编译器不会报错**。比如在一个数组上用循环计算斐波那契数列，可能得到如下结果：

```
1   1   2   3   5   8   0   0   0   0   0
```

想一想这是为什么？

### `private` 子句

`private` 子句列举是私有的变量，即每个线程都有该变量的副本。

私有变量的初始值是不确定的，在块结束后的值也是不确定的。

### `default` 子句

使用 `default(none)` 可以让编译器要求我们明确块内使用的每个变量的作用域。共享的应使用 `shared` 子句列出。

通常由程序员明确每个变量的作用域是好的，能够避免出错。

### 排序



### 循环调度

如果函数调用的时间与参数有关，我们有时不应当将循环均分给每个线程，应当采取调度策略。

### 常用函数

- `omp_get_thread_num()`
- `omp_get_num_threads()`
- `omp_get_max_threads()`
- `omp_get_wtime()`
- `omp_set_num_threads()`

OpenMPmay try to use all available cpus if not set.

## MPI

MPI 基础笔记已记录在 AIPP 笔记中。这里重点记录在集群上配置 MPI 的经历。

集群上能够使用的 MPI 实现有：

- OpenMPI
- Intel MPI
- nvhpc-hpcx

我选择使用 Intel MPI 相关套件进行配置。首先加载相关环境：

```bash
source ../intel/oneapi/setvars.sh
```

### 编译

加载好环境后，我们可以使用 GCC 的 `mpicc`、`mpicxx`、`mpifc`、`mpif90`、`mpigcc` 等进行编译。但为了凸显用的是 Intel 环境，还是用 Intel 的编译器比较好，有：

- `mpiicc`
- `mpicpc`
- `mpiifort`

使用 `icc` 编译时，可能会提示 `icc` 将被弃用。这时使用 `--cc=icx` 即可。完整的编译选项如下：

```bash
mpiicc sample.c -o my_prog -cc=icx -qopenmp -O3
mpiicpc sample.c -o my_prog -cxx=icpx -qopenmp -O3
```

与使用 GCC 编译的选项会有一些区别，比如 `-fopenmp` 变成了 `-qopenmp`。

### 运行

使用 `sbatch` 脚本提交运行。

但是有时候会需要调试，这时使用 `salloc` 分配到节点资源，然后 SSH 到指定的节点，使用调试器。

基本的运行指令如下：

```bash
mpiexec -n 8 -ppn 2 my_prog
```

然而我们使用 slurm 进行管理，此时不需要指定进程数、节点数。MPI 实现会自动读取 slurm 这类资源管理器的环境。

我在网上找到了几种调试的方式，列举如下：

- `mpirun` 附带调试参数（来自官方文档 MPI Library），如：
    - `mpirun -gdb`
    - `mpiexec -idb`
- `gdb-oneapi`（来自官方文档 C++ Compiler），这个不太适用 MPI 相关程序。
- 

### profiling

MPI Library 提供了 `-gtool` 选项来与其他工具聚合使用。比如 vTune 可以这样用：

```bash
mpirun -n 3 ./myprog : -n 1 vtune -c advanced-hotspots -r ah -- ./myprog
mpirun -n 8 -gtool "vtune -collect hotspots -r result:3,5-7" ./myprog
mpirun -n 16 -gtool "gdb:3,5,7-9=attach" ./myprog
```

#### 使用 ITAC

应当使用 Intel MPI 编译。需要添加 `-g -trace` 选项。前者允许源代码级别的 profiling，后者开启 ITAC trace 收集器。推荐使用 `-O3` 优化。

在 slurm 脚本中添加 `export VT_PCTRACE=1` 以开启源代码 profiling。

运行成功后将得到一系列的 `<executable>.stf.*` 文件。使用 `traceanalyzer <executable>.stf` 打开即可。

#### 使用 vTune

添加 `-g` 选项以开启源代码级别 profiling。

值得注意的是，vTune 不支持在多个节点之间收集数据。因此应当指定 `-N 1`。

使用 `amplxe-cl` 运行你的程序。比如：

```bash
srun amplxe-cl –r new_dir_name –collect hotspots -no-auto-finalize -- ./mpi_code.exe
```

结果将保存在 `new_dir_name` 中。


