# Lecture 6 GPU and CUDA API

Date: 2023/07/09

这次课程我们使用 NVIDIA DLI 平台学习 CUDA。课程链接在[这里](https://courses.nvidia.com/courses/course-v1:DLI+C-AC-01+V1/about)，使用 Jupiter Notebook 环境。这也是我第一次使用 Jupiter 的教程，深刻地感受到它的方便之处。

## Part 1 使用 CUDA 加速 C/C++ 程序

一些基础知识：

- `nvidia-smi`: 用于查询 NVIDIA GPU 设备的状态。SMI 是 Systems Management Interface（系统管理界面）的缩写。
- `.cu`: CUDA 源文件扩展名

一个典型的 GPU 函数如下：

- `__global__ void GPUFunction()`: GPU function, called by CPU
- `GPUFunction<<<1,1>>>();`: Call GPU function
    - `<<< NUMBER_OF_BLOCKS, NUMBER_OF_THREADS_PER_BLOCK>>>`
- `cudaDeviceSynchronize();`: Wait for GPU function to finish
- Compile command is similar to `gcc`:

```bash
nvcc -arch=sm_70 -o hello-gpu 01-hello/01-hello-gpu.cu -run
```

Index of threads and blocks:

- `threadIdx.x`: Index of thread in block
- `blockIdx.x`: Index of block in grid
- `blockDim.x`: Number of threads per block
- `gridDim.x`: Number of blocks per grid
- `threadIdx.x + blockIdx.x * blockDim.x`: Global index of thread

Memory Management:

- `cudaMallocManaged(&a, N * sizeof(int));`: Allocate memory on GPU
- `cudaFree(a);`: Free memory on GPU
- `a` is available on both CPU and GPU

Choice of numbers of blocks and threads:

- Regarding to the hardware characteristics of GPU, the number of blocks should be a multiple of the number of SMs (Streaming Multiprocessors), and the number of threads per block should be a multiple of the number of CUDA cores per SM. The number is usually `32` or `64`. The max size of a block is `1024` threads.

```c
// Assume `N` is known
int N = 100000;

// Assume we have a desire to set `threads_per_block` exactly to `256`
size_t threads_per_block = 256;

// Ensure there are at least `N` threads in the grid, but only 1 block's worth extra
size_t number_of_blocks = (N + threads_per_block - 1) / threads_per_block;

some_kernel<<<number_of_blocks, threads_per_block>>>(N);

__global__ some_kernel(int N)
{
  int idx = threadIdx.x + blockIdx.x * blockDim.x;

  if (idx < N) // Check to make sure `idx` maps to some value within `N`
  {
    // Only do work if it does
  }
}
```

- Total number of threads in a grid is `blockDim.x * gridDim.x`

```c
__global void kernel(int *a, int N)
{
  int indexWithinTheGrid = threadIdx.x + blockIdx.x * blockDim.x;
  int gridStride = gridDim.x * blockDim.x;

  for (int i = indexWithinTheGrid; i < N; i += gridStride)
  {
    // do work on a[i];
  }
}
```

Error handling:

- `cudaError_t` is an enum type, which is used to represent the status of CUDA API calls.

```c
cudaError_t err;
err = cudaMallocManaged(&a, N)                    // Assume the existence of `a` and `N`.

if (err != cudaSuccess)                           // `cudaSuccess` is provided by CUDA.
{
  printf("Error: %s\n", cudaGetErrorString(err)); // `cudaGetErrorString` is provided by CUDA.
}
```

- `cudaGetLastError()` returns the last error from a runtime call. This is usually used for functions that don't return error codes.

```c
/*
 * This launch should cause an error, but the kernel itself
 * cannot return it.
 */

someKernel<<<1, -1>>>();  // -1 is not a valid number of threads.

cudaError_t err;
err = cudaGetLastError(); // `cudaGetLastError` will return the error from above.
if (err != cudaSuccess)
{
  printf("Error: %s\n", cudaGetErrorString(err));
}
```

The tutorial provided us with a wrapped error handling function:

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

  checkCuda( cudaDeviceSynchronize() )
}
```

### Challenge 1: Vector Addition

### Challenge 2: Matrix Multiplication

Here we will learn to use CUDA datatype `dim3` to represent the dimensions of a grid and a block.

```c
dim3 threads_per_block(16, 16, 1);
dim3 number_of_blocks(16, 16, 1);
someKernel<<<number_of_blocks, threads_per_block>>>();
```

And now we can use other components of `gridDim` and `blockDim`. For example, `blockDim.y`, `threadIdx.y`, `blockIdx.y`, etc.

### Challenge 3: Heat Conduction

## Part 2 使用 CUDA C/C++ 统一内存和 Nsight Systems (nsys) 管理加速应用程序内存

> reference: https://docs.nvidia.com/cuda/cuda-c-best-practices-guide/index.html#memory-optimizations
>
> Nsight Systems命令行分析器
>

使用 Nsight Systems命令行分析器 (nsys) 分析被加速的应用程序的性能。
利用对流多处理器的理解优化执行配置。
理解统一内存在页错误和数据迁移方面的行为。
使用异步内存预取减少页错误和数据迁移以提高性能。
采用循环式的迭代开发加快应用程序的优化加速和部署。

GPU Hardware properties:

```c
int deviceId;
cudaGetDevice(&deviceId);                  // `deviceId` now points to the id of the currently active GPU.

cudaDeviceProp props;
cudaGetDeviceProperties(&props, deviceId); // `props` now has many useful properties about the active GPU device.
```




## Part 3 Asynchronous Streaming and Visual Analysis of Accelerated C/C++ Applications

### Nsight Systems

生成报告：

```bash
nsys profile --stats=true -o test-report ./my_report
```

### CUDA 流

```c
cudaStream_t stream;   // CUDA流的类型为 `cudaStream_t`
cudaStreamCreate(&stream); // 注意，必须将一个指针传递给 `cudaCreateStream`

someKernel<<<number_of_blocks, threads_per_block, 0, stream>>>();   // `stream` 作为第4个EC参数传递

cudaStreamDestroy(stream); // 注意，将值（而不是指针）传递给 `cudaDestroyStream`
```

### 手动内存分配和复制

回忆我们已经学过的 `cudaMallocManaged` 和 `cudaMemPrefetchAsync` 函数。



```c

