# AP

## CAPWAP 原理

!!! quote

    - [无线 CAPWAP 隧道技术——理论篇 - 锐捷](https://www.ruijie.com.cn/jszl/86721/)

CAPWAP 是 Control And Provisioning of Wireless Access Points Protocol Specification 的缩写，意为无线接入点的控制和配置协议，是无线局域网内最重要的技术之一。从全局角度来看，IEEE 802.11 协议用来解决 STA 和 AP 之间的通信，而 CAPWAP 协议用来解决 AP 与 AC 之间的通信。

CAPWAP 协议用于 AC 对其所关联的 AP 的集中管理和控制，为 AP 和 AC 之间的互通性提供了一个通用封装和传输机制。CAPWAP 协议主要具备以下几个功能：

- AP 对 AC 的自动发现；
- AP 和 AC 的状态机运行和维护；
- AC 对 AP 进行管理、业务配置下发；
- STA 数据封装 CAPWAP 隧道进行转发。

### DTLS 协议

简而言之，DTLS 是基于 UDP 场景下数据包可能丢失或重新排序的现实情况下，为 UDP 定制和改进的 TLS 协议。在 [RFC 5415 - Control And Provisioning of Wireless Access Points (CAPWAP) Protocol Specification](https://datatracker.ietf.org/doc/html/rfc5415#section-2.4) 中强调了 DTLS 与 CAPWAP 之间的紧密关系：

> DTLS is used as a tightly integrated, secure wrapper for the CAPWAP protocol.  In this document, DTLS and CAPWAP are discussed as nominally distinct entities; however, they are very closely coupled, and may even be implemented inseparably.

### CAPWAP 协议报文

CAPWAP 协议有两种类型的报文：CAPWAP 控制报文和数据报文。控制报文主要携带的是信息要素，用于 AC 对于 AP 工作参数的配置和 CAPWAP 隧道的维护；数据报文主要携带终端发送的数据报文，用于传输终端的上层数据。控制报文和数据报文分别传输在不同的 UDP 端口，控制报文使用端口 5246，数据报文使用端口 5247。

## 华三无线终结者

!!! quote

    - [H3C 无线终结者部署手册 -6W103](https://www.h3c.com/cn/d_202208/1677294_30005_0.htm)

- 产生原因：密集房间场景中，信号衰减会导致 AP 信号覆盖的距离受限，同时多个房间共享一个 AP，性能也会遇到瓶颈。
- 华三的方案：采用 AC+WT+WTU 三层组网架构，解决信号覆盖和性能瓶颈的问题，满足大容量、高密度、高信号强度、低成本部署的用户需求，实现每房间的无线千兆接入速率。

![wtu](https://resource.h3c.com/cn/202208/31/20220831_7732991_x_Img_x_png_0_1677294_30005_0.png)

!!! note "没怎么看懂，这哪里创新了，感觉就只是弄了个弱版 AP。"

根据华三产品文档，WTU430-EI 只能工作在 Version 1 模式下：

![version1](https://resource.h3c.com/cn/202208/31/20220831_7733006_x_Img_x_png_9_1677294_30005_0.png)

从配置手册来看，集中转发和本地转发两种模式的差别不大。事实上这两种模式分别对应 RFC 5415 中的 Split MAC、Local MAC 两种 CAPWAP 架构。通过抓包我们看到仅有 STA 的 Association Request/Response 被封装在 CAPWAP 隧道中，而 STA 接入后的报文出现在 VLAN 中，因此可以推测部署采用的是本地转发模式（即 Local MAC 架构）。

VLAN 中的部分数据包是用了 DTLS，但并不是全部，且通信双方 IP 不都在内网，大概只是某些应用在使用？

注意文末 FAQ 中关于 PoE 的说明：

> - WT 能作为普通交换机 PoE 使用吗？
>
>     不能。WT 采用非标准 PoE（24V）给 WTU 供电，WT 直连 WTU 的端口也不能作为普通的网口使用，不能直接接 PC 或直连交换机，只能用来连接 WTU。
>
> - WTU 能直接连接普通 PoE 交换机使用吗？
>
>     不能。WT 采用非标准 PoE（24V）给 WTU 供电，普通 PoE 交换机无法给 WTU 供电，WT 和 WTU 只能配合在一起使用；另外，对于工作在超瘦模式的 WTU，其部分功能也需要 WT 来完成。

## WTU 上线过程

受电后，首先发送几个 LLDP 帧：

```text
System Description = H3C Comware Platform Software, Software Version 7.1.064, Release 2457P31\r\nH3C WTU430-EI\r\nCopyright (c) 2004-2022 New H3C Technologies Co., Ltd. All rights reserved.
    0000 110. .... .... = TLV Type: System Description (6)
    .... ...0 1010 0100 = TLV Length: 164
    System Description: H3C Comware Platform Software, Software Version 7.1.064, Release 2457P31\r\nH3C WTU430-EI\r\nCopyright (c) 2004-2022 New H3C Technologies Co., Ltd. All rights reserved.
```

从不带 VLAN 的控制网络通过 DHCP 获取 IP 地址。

```text
Dynamic Host Configuration Protocol (ACK)
    Message type: Boot Reply (2)
    Hardware type: Ethernet (0x01)
    Hardware address length: 6
    Hops: 0
    Transaction ID: 0xc2f2f8fb
    Seconds elapsed: 0
    Bootp flags: 0x8000, Broadcast flag (Broadcast)
        1... .... .... .... = Broadcast flag: Broadcast
        .000 0000 0000 0000 = Reserved flags: 0x0000
    Client IP address: 0.0.0.0
    Your (client) IP address: 10.181.70.***
    Next server IP address: 0.0.0.0
    Relay agent IP address: 0.0.0.0
    Client MAC address: NewH3CTechno_**:**:** (44:1a:fa:**:**:**)
    Client hardware address padding: 00000000000000000000
    Server host name not given
    Boot file name not given
    Magic cookie: DHCP
    Option: (53) DHCP Message Type (ACK)
        Length: 1
        DHCP: ACK (5)
    Option: (1) Subnet Mask (255.255.254.0)
        Length: 4
        Subnet Mask: 255.255.254.0
    Option: (3) Router
        Length: 4
        Router: 10.181.70.254
    Option: (51) IP Address Lease Time
        Length: 4
        IP Address Lease Time: 1 day (86400)
    Option: (59) Rebinding Time Value
        Length: 4
        Rebinding Time Value: 21 hours (75600)
    Option: (58) Renewal Time Value
        Length: 4
        Renewal Time Value: 12 hours (43200)
    Option: (54) DHCP Server Identifier (10.181.70.254)
        Length: 4
        DHCP Server Identifier: 10.181.70.254
    Option: (43) Vendor-Specific Information
        Length: 17
        Value: 800f0000030ab500220ab500230abbd702
    Option: (255) End
        Option End: 255
    Padding: 00
```

其回复报文中包含 Vendor Specific Option 43。搜索可以发现，华为、华三和思科等都会采用 Option 43 作为 AP 寻找 AC 的方式。

!!! info

    - H3C: [DHCP Option 43 Vendor-Specific Configuration Examples-5W100](https://www.h3c.com/en/Support/Resource_Center/EN/Home/Public/00-Public/Technical_Documents/Configure___Deploy/Configuration_Examples/H3C_CE-10948/#:~:text=If%20a%20DHCP%20client%20requests,can%20associate%20with%20the%20AC.)
    - Huawei: [How to Configure Option 43 When Huawei APs Are Connected to DHCP Servers of Different Vendors](https://support.huawei.com/enterprise/en/doc/EDOC1100202779)
    - Cisco: [Configure DHCP OPTION 43 for Lightweight Access Points](https://www.cisco.com/c/en/us/support/docs/wireless-mobility/wireless-lan-wlan/97066-dhcp-option-43-00.html)

华三支持 Option 43 配置为 PXE 或 ACS 格式。阅读文档示例，我们可以发现这是 PXE 模式：

> To configure a PXE server address sub-option that contains IPv4 AC addresses 10.23.200.1 and 10.23.200.2, use the following settings:
>
> - Sub-option type: `80`.
> - Sub-option length: `0b`. The length of `0000020a17c8010a17c802` is 11 bytes.
> - Sub-option value: `0000020a17c8010a17c802`. `0000` is a fixed part, `02` is the number of IPv4 AC addresses, `0a17c8010a17c802` is AC addresses `10.23.200.1` and `10.23.200.2` in hexadecimal format.
>
> When you configure the PXE server address sub-option in the DHCP address pool view of the DHCP server, the configuration is option 43 hex `800b0000020a17c8010a17c802`.

我们可以解析出三个 AC 的地址分别为：`10.181.0.34`、`10.181.0.35`、`10.187.215.2`。

可以看到，AC 与 AP 处于不同的网段，这意味着 AC 很有可能控制多个网段的 AP。

在完成 DHCP 地址 ARP 后，向所有 AC 发送 CAPWAP-Control - Discovery Request 报文。

Data 报文出现后，也出现了 OpenFlow 协议。

这个控制网络的 DHCP 是公开的，没有执行 MAC 绑定。

在开放无线网 1610 VLAN 中，有多个不同网段的 DHCP 服务器，这点很奇怪。

10.192/193.0.1 回复内容为 requested address not available。192 偶尔回复携带 Option 60 为 android-dhcp-14，193 MSFT 5.0

Juniper 两台 DHCP 服务器回复不带消息。

直接向 VLAN 内丢 DHCP Discover 没有人回复。推测，无线数据所在的这两个 VLAN 都需要经过 AP 的 Association 过程才能得到 DHCP 回复。
