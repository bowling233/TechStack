# oneAPI

> <https://www.intel.com/content/www/us/en/docs/mpi-library/developer-reference-linux/2021-11/overview.html>

## 安装

### Spack

oneAPI 的包在 Spack 中均以 `intel-oneapi-` 开头，选择需要的安装即可。有些包名相同但中间没有 `oneapi`，大概率是废弃的包。

### 从官网下载安装

通过官网下载安装的需要执行脚本 `oneapi/setvars.sh` 加载环境变量，会列出加载了的组件，`vtune`、`itac` 等分析工具也会被加载。

## 运行

对 Intel MPI 来说，`mpirun` 是 `mpiexec.hydra` 的包装。其选项有全局选项和局部选项之分，在一次运行多个 MPI 程序时可以分别指定，但我们平时不会这样做，因此不做区分。可以编写文件保存选项，使用 `-configfile` 指定配置文件，`#` 注释。`./mpiexec.conf` 会自动加载。

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
