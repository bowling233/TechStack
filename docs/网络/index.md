# 网络

## 模型

实际在工业中，使用的是 TCP/IP 模型。

=== "OSI 参考模型"

    | 层级 | 名称 | 功能 | 协议 |
    | ---- | ---- | ---- | ---- |
    | L7 | 应用层（Application Layer） | 提供用户接口，用于访问网络服务 | HTTP、FTP、SMTP |
    | L6 | 表示层（Presentation Layer） | 数据格式转换、数据加密、数据压缩 | ASCII、EBCDIC |
    | L5 | 会话层（Session Layer） | 建立、管理、终止会话连接 | SSL |
    | L4 | 传输层（Transport Layer） | 可靠通信：隐藏通信实现的细节，提供高可靠的端到端的数据传输服务 | TCP、UDP |
    | L3 | 网络层（Network Layer） | 路由功能：定义终端间连接和传输路径的选择 | IP |
    | L2 | 数据链路层（Data-link Layer） | 数据传输：使用物理层地址（如 MAC 地址），提供数据帧（Frame）传输服务 | IEEE 802.2、帧中继 |
    | L1 | 物理层（Physical Layer） | 物理连接：提供比特流传输服务 | IEEE 802.3、FDDI |

=== "TCP/IP 分层模型"

    | 层级 | 名称 | 地址 | 网络硬件 |
    | ---- | ---- | ---- | ---- |
    | L4 | 应用层（Application Layer） |  | L7 交换机、防火墙、代理 |
    | L3 | 传输层（Transport Layer） | 端口号 | L4 交换机、防火墙 |
    | L2 | 网际层（Internet Layer） | IP 地址 | L3 交换机、路由器 |
    | L1 | 网络接口层（Network Interface Layer） | MAC 地址 | L2 交换机 |