# CUDA

Programming Massively Parallel Processors

<!-- prettier-ignore-start -->
!!! abstract "简介"

    这是我学习 CUDA 的笔记。主要参考内容是《Programming Massively Parallel Processors》这本书，同时参考其他资料，将与 CUDA 有关的知识持续集成到该笔记中。笔记仅为方便复习使用，不适合初学者。
<!-- prettier-ignore-end -->

## 基本概念

- 微处理器的并行计算有两种发展轨迹：多核与多线程。
    - CPU 主要走多核路线，目标是在将串行程序移动到多核处理器上时保持执行速度。它使用较为复杂的控制逻辑和缓存机制来提高单线程程序的性能，但这两个功能对峰值计算吞吐量的提升没有帮助。
    - GPU 主要走多线程路线，目标是**提高并行程序的吞吐量**。GPU 的内存带宽比 CPU 高很多、能执行海量的浮点运算。
- CUDA 是一种 **heterogeneous** computing platform，即**异构**计算平台，它允许 CPU 和 GPU 协同工作，以提高计算性能。

一些与历史有关的：

- 以前 GPU 专用于图形处理时，所有程序都应当适配图形应用程序接口如 OpenGL、Direct3D。并行编程人员必须将并行处理的数据对应到像素、图元等图形学概念上，才能充分利用 GPU 的并行计算能力。这种技术称为 GPGPU（General-Purpose computing on Graphics Processing Units）。
- 以前的 GPU 主要支持单精度浮点运算，然而众多科学应用要求双进度浮点运算。现在的专业 GPU 的双进度浮点运算已经接近单精度浮点运算的性能（以前只有高端 CPU 能达到），并且还支持融合运算（fused multiply-add，FMA），进一步减少误差。

CUDA GPU 的结构：

- 一个 GPU 由多个 SM（Streaming Multiprocessor）组成，每个 SM 由多个 SP（Streaming Processor）组成。
- 内存：
    - 以前主要是 GDDR SDRAM（Graphics Double Data Rate Synchronous Dynamic Random-Access Memory），作为 Global Memory。应用于图像处理时它存储纹理、帧缓冲区等图形数据，应用于并行计算时提供很高的带宽和很低的延迟。
    - 更新的架构使用了 HBM（High Bandwidth Memory），它提供更高的带宽。
- 总线：
    - PCIE（Peripheral Component Interconnect Express）总线，用于连接 GPU 和 CPU。
    - NVLINK，用于连接 GPU 和 GPU。

## CUDA 基础编程：数据并行

<!-- prettier-ignore-start -->
!!! note "为什么是数据并行"

    数据并行是并行应用程序可伸缩性的主要来源，我们通常很容易从串行程序中提取出数据并行性。任务并行性（task parallelism）则需要对算法进行重构，这是一项复杂的工作。我们会在讲解流（stream）时介绍任务并行性。
<!-- prettier-ignore-end -->

一个 CUDA C 程序中有主机 host（即 CPU）和设备 device（即 GPU）两部分。主机代码在 CPU 上运行，设备代码在 GPU 上运行，如下图所示：



### 内存

CUDA 设备上的 Global Memory 能够被 host 访问、传输数据。除了 Global Memory，还有 Constant Memory、Shared Memory、Register、Texture Memory 等设备内存类型。

<!-- prettier-ignore-start -->
::cards::

[
  {
    "title": "`cudaMalloc()`",
    "content": "
                Address of a pointer<br>
                Size",
  },
  {
    "title": "cudaFree()",
    "content": "Pointer",
  },
  {
    "title": "cudaMemcpy()",
    "content": "
                Destination pointer<br>
                Source pointer<br>
                Size<br>
                Direction<br>
                方向可以是 `cudaMemcpyHostToDevice` 或 `cudaMemcpyDeviceToHost`",
  },

]

::/cards::
<!-- prettier-ignore-end -->

### 错误处理

每个 CUDA API 调用都会返回一个错误码，以下是简单的写法：

```c
cudaError_t err = cudaMalloc(&dev_a, size);
if (err != cudaSuccess) {
    printf("%s in %s at line %d\n", cudaGetErrorString(err), __FILE__, __LINE__);
    exit(EXIT_FAILURE);
}
```

还可以写成一个更完善的宏来使用：

```c
#include <stdio.h>
#include <assert.h>

inline cudaError_t checkCuda(cudaError_t result)
{
  if (result != cudaSuccess) {
    fprintf(stderr, "CUDA Runtime Error: %s\n", cudaGetErrorString(result));
    assert(result == cudaSuccess);
  }
  return result;
}

int main()
{

/*
 * The macro can be wrapped around any function returning
 * a value of type `cudaError_t`.
 */

  checkCuda( cudaDeviceSynchronize() );
}
```

### 线程

每次启动内核时生成的一系列线程称为 grid。每个 grid 被组织成一系列的 block，其中的每个 block 大小相同。

一些内部变量：

- block
    - `blockDim`：block 的维度，即 block 中线程的数量。有 `x`、`y`、`z` 三个成员。
    - `blockIdx`：block 的索引。有 `x`、`y`、`z` 三个成员。
- thread
    - `threadIdx`：thread 的索引。有 `x`、`y`、`z` 三个成员。

这些内部变量常常由特定的硬件寄存器存放。

每个核函数的自动变量都是线程私有的。

常用公式：

- `blockIdx.x * blockDim.x + threadIdx.x`：线程的全局索引。
- `ceil((float)N / block_size)`：block 的数量。
- `(N + block_size - 1) / block_size`：block 的数量

CUDA 函数声明关键字：

| | Executed on | Callable from |
| --- | --- | --- |
| `__device__` | Device | Device |
| `__global__` | Device | Host |
| `__host__` | Host | Host |

- 注意双下划线
- 不加关键字默认为 `__host__`
- 可以同时使用 `__host__ __device__`，编译器将生成该函数的两个版本。在 Host 中将调用 Host 版本，在 Device 中调用 Device 版本。







