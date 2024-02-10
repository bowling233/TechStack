---
tags:
    - 完善
---

# Android/Harmony OS

## adb

- `adb devices`
- `adb install/uninstall`
- `adb reboot [bootloader|recovery|sideload|sideload-auto-reboot]`
- `adb shell`

进入 Shell 后有一些常用的工具，具体用法请查看工具自带的帮助。

- `dumpsys` 查询系统、服务状态。如 `battery` 等。
- `wm` 窗口管理器，控制显示方面。
    - `size [reset|WxH|WdpxHdp]`
    - `user-rotation [free|lock] [orientation]`
- `settings` 管理各项系统设置。
    - `list [system|secure|global]`
    - `put NAMESPACE KEY VALUE`
- `pm` 包管理器
    - `list packages`
