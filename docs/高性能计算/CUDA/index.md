# CUDA

![Overview of CUDA Toolkit](https://docs.nvidia.com/datacenter/tesla/drivers/graphics/cuda-x.png)

CUDA 在实际应用中的整体结构层次如上图所示。HPC 方向主要需要了解 HPC SDK 等较上层的模块，如何使用。涉及运维、功耗控制等方面时，也会涉及驱动中的 NVML 等模块。下面挑选常用的模块作一些介绍：

- [HPC SDK](https://developer.nvidia.com/hpc-sdk)：其实就是把 HPC 常用的子模块打包到了一起。
    - 分析部分包括 Profiles（Nsight） 和 Debugger（cuda-gdb）。
- Nsight：有几个子产品：
    - System：综合分析 CPU、GPU 的性能
    - Compute：kernel profiler，专门调试核函数
    - Graphics：调试、分析 Windows 和 Linux 平台图形应用的性能
- [NVTX (Tools Extension Library)](https://github.com/NVIDIA/NVTX)：C 语言 API，提供 C++ 和 Python 接口。Nsight 等性能分析工具通过该 API 进行测量。我们也可以在程序中使用该 API 进行事件记录等。和 MPI 的 PMPI 有些类似。
- [CUPTI (Profiling Tools Interface)](https://developer.nvidia.com/cupti)：和上面那个功能类似，允许各种测量和性能检测的 API。
- [NVML (NVIDIA Management Library)](https://developer.nvidia.com/nvidia-management-library-nvml)：C 语言 API，监控和管理 NVIDIA GPU 设备。API 分为五个模块：初始化和清理、查询、控制、事件处理、错误报告。库文件 `libnvidia-ml.so`，链接参数 `-lnvidia-ml`。
- [NCCL (NVIDIA Collective Communications Library)](https://developer.nvidia.com/nccl)：C 语言 API，MPI 的替代品。提供多 GPU、多节点通信原语。适用硬件：NVLink、Mellanox Network。
- [cuBLAS (Basic Linear Algebra)](https://developer.nvidia.com/cublas)：提供科学计算和 AI 有关的扩展 API，符合 BLAS 和 GEMM API。
- [cuDNN (Deep Neural Network)](https://developer.nvidia.com/cudnn)：C 语言 API，提供 C++ 接口，提供深度神经网络的相关原语。
