# 硬件：接口

硬件接口种类繁多，本文仅介绍我在 HPC 集群维护中遇过到的一些接口。

## 硬盘类

!!! info "参考资料"

    -   [Identification of a hard drive’s interface type and means for its connection to a computer](https://www.ufsexplorer.com/articles/how-to/connect-drive/)

### 硬盘本身

硬盘本身的接口，常用的有 SATA、SAS、U.2、M.2 等。

::cards::

[
  {
    "title": "SATA",
    "content": "硬盘上 SATA 接口一侧为电源接口，另一侧为数据接口。<br>
                SATA 是最为常见的硬盘接口，但因其速度限制将逐渐被淘汰。<br>
                SATA I: 1.5 Gbit/s<br>
                SATA II: 3 Gbit/s<br>
                SATA III: 6 Gbit/s",
    "image": "attachment/disk_interface_sata.jpg"
  },
  {
      "title": "SAS",
      "content": "SAS 是目前企业级硬盘常见的接口，它能够兼容 SATA，同时支持了 PCIe 通道。<br>
                  图中展示的是 SAS-1.1 接口，它的一面引脚兼容 SATA，另一面引脚提供了第二路信号通道。<br>
                  SAS-1: 3 Gbit/s<br>
                  SAS-4: 22.5Gbit/s<br>
                  SAS-5: 45Gbit/s<br>",
      "image": "attachment/disk_interface_sas.png"
  },
  {
      "title": "U.2 (SFF-8639)",
      "content": "",
      "image": "attachment/disk_interface_u.2.jpg"
  },
  {
      "title": "M.2",
      "content": "",
      "image": "attachment/disk_interface_m2.jpg"
  }
]

::/cards::

#### SAS

::cards::

[
  {
    "title": "SAS 兼容性列表",
    "content": "",
    "image": "attachment/SAS_compatible.jpg"
  },
  {
    "title": "SAS引脚定义",
    "content": "",
    "image": "attachment/SAS_pinouts.jpg"
  },

]

::/cards::

从上面的引脚图可以看出，SATA 引脚数较少。SAS 能够向下兼容 SATA。

目前的 SAS 标准（SFF-8639）已经完整利用了 SAS 接口的双面引脚，可以提供 PCIe x4 通道。

!!! info "关于 SAS 接口的更多信息"

    可以查看 [SAS Connector Identification Guide](https://www.tape-drive-repair.com/sas-connector-guide/)。

SFF-8639
SFF-8643

### 主板和扩展卡上的接口

::cards::

[
  {
    "title": "SATA",
    "content": "",
    "image": "../attachments/board_interface_sata.jpg"
  },

]

::/cards::

## 网络类

### 电口

### 光口

!!! info "参考资料"

    -   [](https://cleerline.com/2021/10/14/fiber-ports/)

### InfiniBand

## PCI/PCIe

### PCIe
