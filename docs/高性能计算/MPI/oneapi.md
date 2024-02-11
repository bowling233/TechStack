# oneAPI

> <https://www.intel.com/content/www/us/en/docs/mpi-library/developer-reference-linux/2021-11/overview.html>

## 安装

## 运行

对 Intel MPI 来说，`mpirun` 是 `mpiexec.hydra` 的包装。
其选项有全局选项和局部选项之分，在一次运行多个 MPI 程序时可以分别指定，但我们平时不会这样做，因此不做区分。
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

## 性能分析

oneAPI 有几个工具可以用来分析性能：`vtune`、`traceanalyzer`、

!!! warning "一些老旧的命令"

    如 `amplxe-cl` 等工具已经被 `vtune` 取代，这里不再介绍。

### VTune

!!! info "参考资料"

    https://www.intel.com/content/www/us/en/docs/vtune-profiler/get-started-guide/2024-0/linux-os.html

服务器端一般没有 GUI，本地 VTune 远程调试也需要将远程服务器 SSH 设置为无密码登陆（我们一般不会这样做）。因此常见的调试流程是：

- 在服务器端运行数据收集
- （可能）在服务器上完成数据处理
- 下载到本地，使用 GUI 工具查看结果

```bash
vtune -collect hotspots -r result -- ./a.out
vtune -report summary -r result
```

上面的两行命令分别执行了数据收集和数据处理，其中 `-collect` 选项指定了收集的数据类型，`-r` 选项指定了结果保存的文件夹，`--` 后面是要运行的程序及其参数。`-report` 选项指定了数据处理的类型，`-r` 选项指定了数据处理的结果文件夹。

[VTune Profiler CLI Cheat Sheet](https://www.intel.com/content/dam/develop/external/us/en/documents/vtune-profiler-cheat-sheet.pdf) 是 Intel 官方提供的 VTune 命令行工具的速查表，已经涵盖了大部分常用的功能。详细的使用方法可以查看 VTune Profiler User Guide 中的 Command Line Interface 章节。

<embed src="../attachment/vtune-profiler-cheat-sheet.pdf" style="width:100%; height:60vh;" type="application/pdf">
