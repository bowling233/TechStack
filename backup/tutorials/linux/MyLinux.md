# Bowling 的 Linux 使用随记

## Windows 与 Linux 共存方案

我所考虑的事情是：系统及其软件应当与数据分离存放。我的台式机是这样配置的：

| 硬盘类型和大小 | 用途           | 分区格式 |
| -------------- | -------------- | -------- |
| NVme SSD 500GB | Windows 系统盘 | ReFS     |
| NVme SSD 256GB | Linux 系统盘   | Btrfs    |
| SATA SSD 1TB   | 数据交换盘     | exFAT    |

-   `exFAT` 泛用性最广，主流操作系统都能直接读写。
-   Ubuntu 能直接挂载 NTFS 格式分区，Windows 安装 [WinBtrfs](https://github.com/maharmstone/btrfs) 后可以自动挂载 Btrfs 格式分区。
- 将数据集中存储于交换盘，避免在两个系统之间同步数据的麻烦。这样使用任何一个系统都能编辑最新的数据。
    - Windows 和 Linux 都能直接使用 Syncthing 保持同步文件夹与其他终端最新。
    - Linux 下也能通过 [OneDrive Client for Linux](https://github.com/abraunegg/onedrive) 实现 OneDrive 文件夹到云的同步。

