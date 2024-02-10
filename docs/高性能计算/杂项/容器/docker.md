# Docker

## 基础概念

- Docker Image 和 Container：
    - Image 可以看作是一个模板，定义了容器如何被实例化。
    - Container 是 Image 的一个实例。一个 Image 可以运行多个 Container。
- Docker Registry：集中存放 Image 的地方。Docker Hub 是 Docker 官方提供的 Registry。
- Docker Repository：每个 Repository 包含多个 Image。

| 命令 | 作用 |
| :--- | :---: |
| `docker images` | 列出本地 Image |
| `docker ps -a` | 列出所有 Container |
| `docker pull {name}:{tag}` | 下载 Image |
| `docker run --name {container_name} -d -p {host_port}:{container_port} {name}:{tag}` | 运行 Image |
| `docker start/stop {container_id}` | 启动/停止 Container |
| `docker logs {container_id}` | 查看 Container 日志 |

## 网络：端口绑定

Container 中的应用程序运行在一个虚拟的网络环境中，与宿主机隔离。如果想要访问 Container 中的应用程序，需要将宿主机的端口与 Container 的端口绑定。

!!! example "将 Nginx 容器绑定到 8080 端口"

    ```bash
    docker run -d -p 8080:80 nginx
    ```

    这样，就可以通过 `http://localhost:8080` 访问 Nginx 了。

## 构建 Image

（TODO，不打算写了，因为基本不会自己构建。）
