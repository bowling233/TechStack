# TCP/IP Illustrated, Volume 1: The Protocols

## TCP

### TCP 思想

#### 重传（Retransmission）

在有损信道上保证数据可靠传输有两种思路：一种是使用纠错码纠正传输中发生的错误，另一种是尝试重传。TCP 采用的是第二种思路。原因是实际传输中不是简单的信道，而是多级信道，会发生的错误不仅有比特错误，还有丢包、乱序等问题。TCP 使用下面的方法保证数据可靠传输：

- 接收方回复 ACK 确认收到的数据。
- 使用校验和检查数据是否损坏。
- 使用序列号（sequence number）解决乱序和重复包问题。

#### 滑动窗口（Sliding Window）

为了提高吞吐量，TCP 需要允许多个数据包同时在网络中传输，这就需要解决流量控制和拥塞控制问题。TCP 使用窗口机制解决这些问题。“窗口”是一个很形象的描述：把会话中的数据包排成一列，只看其中某个区间，就像透过窗户看风景一样。随着过去的数据包被确认，窗口向未来的方向“滑动”，允许发送方发送更多的数据包。发送方和接收方都有窗口。

<figure markdown="span"><center>
![tcp_window](tii1.assets/tcp_window.png)
</center><figcaption>
TCP 窗口
<br /><small>
TCP/IP 详解 卷 1：协议
</small></figcaption></figure>

#### 流量控制（Flow Control）

TCP 流控有两种方式：

- 基于速率（rate-based）：发送方根据接收方的接收速率调整发送速率。
- 基于窗口（window-based）：接收方发送 window advertisement/update 调整发送方窗口大小。假设中间过程无损，传输速率可以通过 $\frac{包大小\times 窗口大小}{RTT}$ 计算，因此可以通过调整窗口大小来调整传输速率。

传输过程中，如果路由器等网络设备的缓存不足以支持相应的传输速率，也会导致数据包丢失，这涉及拥塞控制（Congestion Control），暂不作介绍。

### TCP 原理

- TCP 向上层应用提供全双工（full-duplex）的字节流（byte stream）服务，将字节流分割成 IP 包发送。
    - TCP 传递到 IP 层的数据单元称为 TCP 报文段（segment）。
    - TCP 报头一般长度为 20 字节，最大长度为 60 字节。包含固定的源端口、目的端口、序列号、确认号、头部长度、保留位、标志位、窗口大小、校验和、紧急指针，以及可选的选项字段。
        - 序列号（sequence number）是报文内容中第一个字节在字节流中的偏移量。出于安全考虑，第一次握手时的初始序列号（initial sequence number，ISN）是随机的。
        - 确认号（acknowledgment number）是接收方期望接收的下一个字节的序列号。
        - TCP 包类型如下：

            | 类型 | 描述 |
            | --- | --- |
            | CWR | Congestion Window Reduced，发送方降低发送速率 |
            | ECE | ECN Echo，表明接收方支持 ECN |
            | URG（罕见） | Urgent，紧急指针有效 |
            | ACK | Acknowledgment，确认号有效 |
            | PSH（罕见） | Push，接收方应该尽快交付数据（到应用） |
            | RST | Reset，重置连接 |
            | SYN | Synchronize，同步序列号以初始化连接 |
            | FIN | Finish，结束连接 |

        - 校验和涵盖 TCP 报头和数据，还包括 IP 报头中的某些字段。
        - 常用的选项字段是最大报文段长度（Maximum Segment Size，MSS），标明希望收到的最大 TCP 报文段长度。
- ACK 是累积的（cumulative），表示该序号之前的所有数据都已经收到，这能一定程度上应对 ACK 丢包问题。
    - 该性质可以用于拥塞控制，参考 dupliate ACK。
    - 现代 TCP 有 SACK 选项（Selective Acknowledgement），可以更精确地指定丢失的数据包。
- 建立连接三次握手、断开连接四次握手、半开放（half-open）与半关闭（half-close）状态
