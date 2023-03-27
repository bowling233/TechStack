# Linux 系统疑难问题解答

## 安装、驱动问题

<!-- prettier-ignore-start -->
!!! tips "遇到固件问题怎么办？"
    
    - 首先，查看发行版的手册，寻找解决固件问题的解决办法。
    - 更新 BIOS 版本。
    - 更新 Linux 内核。
    - 使用驱动检查工具。
<!-- prettier-ignore-end -->

### Debian 安装后无法启动，报错 `hdaudio hdaudioC0D2: Unable to configure, disabling` 等。

- 原因：

Debian 使用的 Linux 内核太老，无法识别新核芯显卡。

<!-- prettier-ignore-start -->
??? info "相关的 Linux 内核原码"
    
    - [Github](https://github.com/torvalds/linux/blob/v5.7/sound/hda/hdac_i915.c#L140)

    ```c
    if (!IS_ENABLED(CONFIG_MODULES) ||
		    !request_module("i915")) {
			/* 60s timeout */
			wait_for_completion_timeout(&bind_complete,
						   msecs_to_jiffies(60 * 1000));
		}
    ```

    这 1 分钟的等待错误在 2019 年得到修复，但是最近的 Debian 版本似乎仍然没有采用修复完成的内核。
<!-- prettier-ignore-end -->

- 解决办法：

> Debian Wiki 关于显卡问题的简要提示：
> 
> If you get a fixed low resolution (like 1024 x 768) with no choice of higher resolution in GUI and/or xorg-server log errors with missing device (like (EE) open /dev/dri/Card0 no such file or device) and/or non starting display manager (sddm etc), **make sure that your kernel is up to date (as the kernel has to recognize the graphics device)**. Also make sure that the appropriate firmware packages are up to date.
> 
> 注意：Linux 内核负责识别显卡。

在 Grub 的内核命令行中添加 `nomodeset`。进入系统后，升级 Linux 内核到最新的可用版本。

```shell
sudo apt install linux-image-<flavour>
```

<!-- prettier-ignore-start -->
!!! info "参考资料"
    
    - [Debian Wiki: GraphicsCard](https://wiki.debian.org/GraphicsCard)
    - [Debian Wiki: HowToUpgradeKernel](https://wiki.debian.org/HowToUpgradeKernel)

<!-- prettier-ignore-end -->

### 声卡不识别或声音设备仅有 `dummy output`

- 环境：

微星迫击炮 B660M 主板，Ubuntu 23.04。

- 原因：

可能是使用微星迫击炮 B660M 主板，

- 解决方法：

升级 BIOS。

<!-- prettier-ignore-start -->
!!! info "参考资料"
    
    - [Unix & Linux: Realtek ALC1220 audio chipset on Linux Mint 18.1](https://unix.stackexchange.com/questions/373777/realtek-alc1220-audio-chipset-on-linux-mint-18-1)
<!-- prettier-ignore-end -->