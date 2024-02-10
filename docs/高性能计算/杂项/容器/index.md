# Container

!!! info "参考资料"

    -   [Containers on the Research Computing Clusters | Princeton Reseach Computing](https://researchcomputing.princeton.edu/support/knowledge-base/apptainer)

使用容器可以免去配置环境的烦恼，且一般不会损失性能。在 HPC 领域，常用的容器技术有 Docker 和 Apptainer（前身为 Singularity）。Apptainer 是专门为 HPC 领域设计的容器技术，可以直接使用 Docker 镜像，不需要 root 权限（更加安全）。

- [Docker](docker.md)
- [Apptainer](apptainer.md)

近期，Nvidia 提供了独家的容器技术 [Nvidia Container Toolkit](https://github.com/NVIDIA/nvidia-container-toolkit)，以 Docker Engine 为基础，提供了在容器中使用 GPU 的能力。目前，Nvidia Container Toolkit 仅支持 Docker，不支持 Apptainer。
