# POP Tools Profiler

## 安装 Profiler 工具

远程环境中，安装 Score-P 和 Scalasca 即可。如果是本地集群（具有可视化环境）可以配置 Cube。

安装过程基本都是：

1. 下载解压
2. `./configure --prefix=/path/to/install`
3. `make -j`
4. `make install`

需要注意，在 `./configure` 阶段，可能需要添加各种依赖项（如果没有自动检测到的话）。

## 编译项目

在所有编译命令前面加上 `scorep` 即可。

## 运行和结果分析

- `scan` 运行。这里还有一些具体的选项。

运行后会输出简短的信息，并给出 trace 信息的文件名。

- `square -s` 分析文件，并给出 `.score` 等文件。
- 使用 Cube 可视化分析

