# 远程桌面教程

## 准备

!!! note "准备 Windows 专业版"

    请先确认自己的 Windows 版本为专业版。一般笔记本默认安装的系统为家庭版，**不支持被远程控制**。只有 Windows 专业版及以上版本支持**被远程控制**。如果你在 *打开远程桌面* 步骤发现没有远程桌面窗格，说明你的 Windows 版本不支持被远程控制。

- 电脑端：放在宿舍，连上有线网络（建议，连接方法参见 [校网连接指南 - 图灵 2022 学长组资料汇总](https://turing2022.tonycrane.cc/rvpn/#_3)）或者 `ZJUWLAN-Secure`。
- 移动端
    - 安装 ![](http://cdn.bowling233.top/note/img/rd.01.png){: style="height:20px;width:20px"}`Microsoft Remote Desktop`。这是微软开发的远程桌面客户端，使用体验最好。
    - 建议使用连接了蓝牙键鼠的平板，以获得笔记本的体验。触控笔也可。

## 电脑端设置

!!! quote

    参考 98 帖子：[校外使用rvpn连接内网Windows 10电脑](https://www.cc98.org/topic/5482686)

!!! tip "温馨提醒"

    点击图片可以放大查看~

::cards:: cols=2

[
  {
    "title": "01",
    "content": "打开远程桌面功能：按 ++win+r++，输入 `SystemPropertiesRemote.exe`，打开远程桌面功能，如上设置。",
    "image": "http://cdn.bowling233.top/note/img/rd.06.png"
  },
  {
    "title": "02",
    "content": "以管理员模式打开 `PowerShell`：搜索框输入 `Windows PowerShell`，右键，以管理员身份运行。",
    "image": "http://cdn.bowling233.top/note/img/rd.04.png"
  },
  {
    "title": "03",
    "content": "更改远程桌面端口号：逐行输入并运行下面 *03* 代码片段中的命令。可以将 `3390` 更改为你自己的数值（建议为 `65535` 以内的五位数）。",
    "image": "http://cdn.bowling233.top/note/img/rd.05.png"
  },
  {
    "title": "04",
    "content": "获取电脑的 IP 地址：在设置-网络-以太网（有线）或 WLAN 页面中可以找到自己的 IPv6 地址，记录下来。",
    "image": "http://cdn.bowling233.top/note/img/rd.07.png"
  }
]

::/cards::

```powershell title="03"
$portvalue = 3390
Set-ItemProperty -Path 'HKLM:\SYSTEM\CurrentControlSet\Control\Terminal Server\WinStations\RDP-Tcp' -name "PortNumber" -Value $portvalue
New-NetFirewallRule -DisplayName 'RDPPORTLatest-TCP-In' -Profile 'Public' -Direction Inbound -Action Allow -Protocol TCP -LocalPort $portvalue
New-NetFirewallRule -DisplayName 'RDPPORTLatest-UDP-In' -Profile 'Public' -Direction Inbound -Action Allow -Protocol UDP -LocalPort $portvalue
```

??? info "技术细节"

    - 为什么要更改端口号？

    出于安全性考虑，学校屏蔽了远程桌面的默认端口，因此需要更改。

    - 为什么使用 IPv6 地址？

    在校园内网，不同子网段的 IPv4 地址常常不能互连。但 IPv6 地址可以，这可能与校网环境有关。此外 IPv6 地址的租期似乎更长，更加稳定。

## 移动端设置

以安卓平板为例，苹果设备同理。

::cards:: cols=2

[
  {
    "title": "01",
    "content": "打开 `Remote Desktop` 应用，点击右上角的 `+` 号添加远程主机。",
    "image": "http://cdn.bowling233.top/note/img/rd.08.jpg"
  },
  {
    "title": "02",
    "content": "填入 IPv6 地址和端口号，如：`[xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx]:12345`。注意：IPv6 地址用中括号括起来。",
    "image": "http://cdn.bowling233.top/note/img/rd.09.jpg"
  },
  {
    "title": "03",
    "content": "添加自己的微软账户（如果你的电脑登录了微软账户）或本地账户（未使用微软账户）。",
    "image": "http://cdn.bowling233.top/note/img/rd.10.jpg"
  },
  {
    "title": "04",
    "content": "下拉选择需要与电脑共享的设备，一般开启剪贴板共享即可（在电脑和平板之间共享剪贴板）。",
    "image": "http://cdn.bowling233.top/note/img/rd.02.jpg"
  }
]

::/cards::

- 点击保存。
- 点击刚刚添加的远程主机，即可连接。初次连接可能会弹出一些警告窗口，勾选不再提醒并确认即可。
- 享受远程桌面体验吧！

![](http://cdn.bowling233.top/note/img/rd.03.jpg)

如果移动端无法连接，可能是电脑端 IPv6 地址发生了变化，更改地址即可。

## 使用体验

校园内网并不限制带宽，因此使用体验相当不错。笔者在玉泉使用有线网络连接台式机，分别在古籍馆、满人的银泉餐厅进行了测试，在分辨率为 2560\*1600 的情况下仍能保持较低的延迟和卡顿，能够流畅办公。但是在蒙民伟楼等不支持 WiFi6 的场所，人数较多时极为卡顿。

事实上，最关乎体验的还是在于平板端的硬件：键盘和鼠标。因为体积的限制，平板的键盘键位不全，对于习惯使用全尺寸键盘和各种快捷键的人群可能不太友好。比如华为 Matepad11 的键盘右侧 ++ctrl++ 和 ++shift++ 是缺失的，按如 ++ctrl+grave++ 这类快捷键时很不方便。此外，键盘并不直接输入远程电脑，而是先经过华为输入法再被发送。因此，输入 ++ctrl+grave++ 时也必须先切换到英文模式。嘛这些影响的主要是程序员，一般工作如 Word，PPT 那么使用体验并没有很大差别。
