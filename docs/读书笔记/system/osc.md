# Operating System Concepts

## 第二章：操作系统结构

### 2.8 操作系统结构

本节介绍了宏、微内核等设计结构，结合具体操作系统的例子。

- 宏内核（monolithic）：
    - 编写简单，内核内部通信快，性能好。但调试和维护困难。
    - 例子：
        - 原始 UNIX 是宏内核，扩展后成为层次化的。
        - Linux、Windows
- 层次化（layered）：
    - 在计算机网络中取得成功。
    - 但事实上没有操作系统这样设计，因为：
        - 难以正确划分层次。
        - 层次间调用开销大。
- 微内核：
    - 内核仅提供最基本服务，如：IPC、内存管理、CPU 调度。
    - 例子：
        - Windows NT 第一版为微内核，但比 Windows 95 性能差很多；Windows NT 4.0 将更多用户空间的服务移到内核，性能提高。到 Windows XP，整体架构变得更偏向宏内核。
        - 苹果 macOS 和 iOS 的内核 Darwin 是微内核。
        - 鸿蒙 OS 是微内核。
- 模块（module）
    - 内核支持在启动时或运行时加载内核模块（loadable kernel modules，LKM）。
    - 是在现代操作系统上最为常见的一种设计。

事实上现代操作系统都是混合架构的，不会严格遵循某种设计结构。

本节剩余部分介绍了 Darwin 和 Android，旁注甚至还介绍了 WSL 的原理。

- Darwin：源码在 [:simple-github: apple-oss-distributions/xnu](https://github.com/apple-oss-distributions/xnu)，描述如下：

    > **XNU kernel is part of the Darwin operating system** for use in macOS and iOS operating systems. XNU is an acronym for X is Not Unix. XNU is **a hybrid kernel combining the Mach kernel** developed at Carnegie Mellon University **with components from FreeBSD and a C++ API** for writing drivers called IOKit. XNU runs on x86_64 and ARM64 for both single processor and multi-processor configurations.

### 2.10 调试操作系统

本节主要介绍 BCC/eBPF。
