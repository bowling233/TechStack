# OpenMP/MPI

OpenMP 在单节点上处理密集型计算，MPI 在多节点之间通信。

## OpenMP

OpenMP 是一种并行编程模型，它可以在单个节点上并行执行计算密集型任务。OpenMP 通过将任务分解为多个线程来实现并行化，每个线程都可以在单个节点上运行。OpenMP 通过使用 `#pragma` 指令来实现并行化，这些指令告诉编译器如何将任务分解为多个线程。OpenMP 也可以通过环境变量来控制线程数。

- 使用 gcc 编译 OpenMP 程序: `gcc -fopenmp -o omptest omptest.c`

在 MacOS 上编译 OpenMP 程序：

- 使用 Homebrew 安装 OpenMP: `brew install libomp`
- 使用 clang 编译 OpenMP 程序: `clang -Xclang -fopenmp -L/opt/homebrew/opt/libomp/lib -I/opt/homebrew/opt/libomp/include -lomp omptest.c -o omptest`
- 