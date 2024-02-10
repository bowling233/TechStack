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

```bash
apptainer pull docker://alpine
apptainer shell lolcow_latest.sif
apptainer run/exec lolcow_latest.sif
./lolcow_latest.sif
apptainer exec --bind /data:/mnt lolcow_latest.sif cat /mnt/cow_advice.txt
```

### 文件

Apptainer 自动挂载这些目录：`/home/$USER`, `/tmp`, `$PWD`。

使用 `--bind` 挂载其他目录。

### Nvidia 支持

在命令中添加 `--nv` 参数即可。

## 构建

（待补充）
