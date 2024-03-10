# Apptainerer

!!! info "参考资料"

    -   [Quick Start | Apptainer](https://apptainer.org/docs/user/main/quick_start.html)
    -   [Introduction to Apptainer/Singularity | HSF Software Training](https://hsf-training.github.io/hsf-training-singularity-webpage/)
    -   [Containers on the Research Computing Clusters | Princeton Research Computing](https://researchcomputing.princeton.edu/support/knowledge-base/apptainer)

## 安装

对于 Debian 类系统，Apptainer 在 GitHub 发布了 `.deb` 包，下载安装即可。

使用下面的命令测试 Apptainer 是否能正常使用：

```bash
apptainer --debug run docker://alpine
```

## 使用

Apptainer 使用 `.sif` 格式的容器镜像，因此拉取 Docker 镜像时会多一步转换，完成后会在当前目录下生成 `.sif` 文件。

`run exec shell` 命令常用参数：

- `--nv` 或 `--nvccli`：CUDA 支持
- `--bind /source:/target`：挂载目录。Apptainer 自动挂载这些目录：`/home/$USER`, `/tmp`, `$PWD`。

```bash title="基础命令"
apptainer pull docker://nvcr.io/nvidia/hpc-benchmarks:24.03
apptainer shell --nv ./hpc-benchmarks_24.03.sif
apptainer run --nv ./hpc-benchmarks_24.03.sif /workspace/hpcg.sh --dat /workspace/hpcg-linux-x86_64/sample-dat
apptainer run --nv ./hpc-benchmarks_24.03.sif nsys profile --trace=cuda,openmp,nvtx,cublas --sample=system-wide /workspace/hpcg.sh --dat ~/hpcg/hpcg-nsys.dat
```

## 构建

（待补充）
