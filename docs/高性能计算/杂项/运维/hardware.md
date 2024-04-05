# 硬件：设备

## RAID

| RAID等级 | 最少硬盘 | 最大容错 | 可用容量 | 读取性能 | 写入性能 |             安全性             |
| :------: | :------: | :------: | :------: | :------: | :------: | :----------------------------: |
| 单一硬盘 |  (参考)  |    0     |    1     |    1     |    1     |               无               |
|   JBOD   |    1     |    0     |    n     |    1     |    1     |         无（同RAID 0）         |
|    0     |    2     |    0     |    n     |    n     |    n     | 一个硬盘异常，全部硬盘都会异常 |
|    1     |    2     |   n-1    |    1     |    n     |    1     |        高，一个正常即可        |
|    5     |    3     |    1     |   n-1    |   n-1    |   n-1    |            中下至中            |
|    6     |    4     |    2     |   n-2    |   n-2    |   n-2    |  中至中高,仅安全性较RAID 5高   |
|    10    |    4     |          |          |          |          |               高               |
|    50    |    6     |          |          |          |          |               高               |
|    60    |    8     |          |          |          |          |               高               |

## ZFS

ZFS 中的 RAID 简单地分为三种容忍度：

- Single-parity：与 RAID-5 类似
- Double-parity：与 RAID-6 类似
- Triple-parity：能够容忍三个硬盘的故障

```bash
ls /dev/disk/by-id
zpool create tank raidz ata-ST2000DM001-1CH164_Z2F0WBH8 ata-ST2000DM001-1CH164_Z1E5B3FZ ata-ST2000DM001-1CH164_Z1F3HW2S ata-ST2000DM001-1CH164_Z2F0WAN4 wwn-0x5000c5006441f38a wwn-0x5000c5007ce9ae69 ata-ST2000DM001-1ER164_W4Z0XS4C
zfs list
mkdir -p /ocean
zfs create -o mountpoint=/data ocean/data
zfs set xattr=sa dnodesize=auto ocean/data
zfs set sharenfs="rw=172.25.0.0/16" ocean/data
showmount -e 127.0.0.1
```