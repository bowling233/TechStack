# Lecture 6 GPU and CUDA API

Date: 2023/07/09

We learn CUDA on NVIDIA DLI platform. You can find the tutorial [here](https://courses.nvidia.com/courses/course-v1:DLI+C-AC-01+V1/about). Environment is Jupiter Notebook.

## Part 1 Accelerate program using CUDA C/C++

- `nvidia-smi`: NVIDIA Systems Management Interface program, used to monitor and manage NVIDIA GPU devices.

```
$ nvidia-smi
Sun Jul  9 04:22:35 2023       
+-----------------------------------------------------------------------------+
| NVIDIA-SMI 440.33.01    Driver Version: 440.33.01    CUDA Version: 10.2     |
|-------------------------------+----------------------+----------------------+
| GPU  Name        Persistence-M| Bus-Id        Disp.A | Volatile Uncorr. ECC |
| Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |
|===============================+======================+======================|
|   0  Tesla T4            On   | 00000000:00:1E.0 Off |                    0 |
| N/A   32C    P8     9W /  70W |      0MiB / 15109MiB |      0%      Default |
+-------------------------------+----------------------+----------------------+
                                                                               
+-----------------------------------------------------------------------------+
| Processes:                                                       GPU Memory |
|  GPU       PID   Type   Process name                             Usage      |
|=============================================================================|
|  No running processes found                                                 |
+-----------------------------------------------------------------------------+
```

- `.cu`: CUDA source file
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
