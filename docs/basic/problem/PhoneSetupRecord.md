# 手机折腾记

因为鸿蒙系统无法通过谷歌安全认证，我的华为手机的谷歌服务处于瘫痪状态。于是我翻出了破旧的 Redmi 6，刷上了 MIUI Global，真正拥有了一部在“墙外”的手机。

## Redmi 6 刷机

怕刷 Lineage OS 把手机折腾坏，于是选择了 MIUI Global，它配备了完整的谷歌套件。小米持续开放 ROM 下载对极客真是太友好了。

### 解锁 BootLoader

小米和红米手机一直都支持解锁 BootLoader。请按照官网教程解锁：

- [Official: MIUI unlock](http://www.miui.com/unlock/index.html)

按开机键+音量下键或使用 ADB 命令将手机重启到 BootLoader 模式。

<!-- prettier-ignore-start -->
??? info "安装 ADB"
    
    - Ubuntu: `sudo apt install android-tools-adb`
    - Windows: [Android SDK Platform Tools ZIP file for Windows](https://dl.google.com/android/repository/platform-tools-latest-windows.zip)

    参考：[Xda: How to install ADB on Windows, macOS, and Linux](https://www.xda-developers.com/install-adb-windows-macos-linux/)
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
??? info "ADB 基本使用"
    
    - `adb devices` 列出连接的设备
    - `adb shell` 连接手机 shell
    - `adb reboot` 让手机重启到指定模式：bootloader|recovery|sideload|sideload-auto-reboot
<!-- prettier-ignore-end -->

解锁完成后，再次让手机启动到 bootloader。

### 下载 ROM 并刷入

- [MIUI ROM Latest Downloads](https://xiaomifirmwareupdater.com/miui/)

在该网站下载合适的 ROM 包，类型选择 Fastboot，文件扩展名为 `.tgz`。下载后逐层解压。

- [Official: Xiaomi Flash Tool](https://www.xiaomiflash.com/)

下载小米官方线刷工具。该工具只能在 Windows PC 上运行。

安装线刷工具，驱动会自动安装。接下来按以下步骤操作：

1. 点击“加载设备”。如果手机连接正常则会显示在列表中。
2. 选择解压的 ROM 包文件夹，如果选择不正确则会弹窗提示找不到脚本。
3. 在窗口最下方调整选项，不要选择“全部清除并加锁”，这会让手机重新上锁。
4. 刷机。

### 开机

如果在手机初始设置过程中连接网络，则谷歌服务请求更新的环节无法通过（除非你的路由器有代理）。因此，推荐长按电源键开启飞行模式，在无网络环境下完成初始设置，进入系统，安装好代理软件后再登录账号。

### 用 ADB 命令行删除 ROM 厂商内置软件

- [XDA: How to uninstall carrier/OEM bloatware without root access](https://www.xda-developers.com/uninstall-carrier-oem-bloatware-without-root-access/)

```
adb shell # 连接手机终端
pm list packages # 列出应用包名
pm uninstall -k --user 0 NameOfPackage # 卸载应用包
```

你也可以在谷歌商店下载 App Inspector 在手机上查阅每个应用的信息，知道包名是对应哪个应用。

## 使用手机作为安全工具

### 谷歌账号管理

当你第一次在具有谷歌套件的手机上登录时，谷歌将会信任这个手机并将其作为安全管理器。当你再次在新设备上登录时，谷歌不会再提供向手机、邮箱发送验证码的选项，仅提供使用信任的手机或平板设备进行验证。

如果你登录的第一台手机设备不能使用了怎么办？比如在鸿蒙系统上使用 MicroG 登录谷歌账号，再安装谷歌套件后会因为设备未经谷歌安全认证而无法连接到谷歌服务器、闪退。这时可以在常用的电脑上登录 [Google Accounts](https://accounts.google.com)，删除对应的手机设备。于是你又可以使用短信验证码登录了。

### 无密码账户

- [Apple: Apple、谷歌与微软承诺拓展对 FIDO 标准的支持，以加速普及免密码登录](https://www.apple.com.cn/newsroom/2022/05/apple-google-and-microsoft-commit-to-expanded-support-for-fido-standard/)
- [Google: One step closer to a passwordless future](https://blog.google/technology/safety-security/one-step-closer-to-a-passwordless-future/)

<!-- prettier-ignore-start -->
!!! note "What is passwordless authentication?"
    
    Passwordless authentication is a form of **multi-factor authentication (MFA)** that replaces passwords with two or more verification factors secured and encrypted on a user’s device, such as a fingerprint, facial recognition, a device pin, or a cryptographic key. The credentials never leave the device, eliminating the risk of phishing. These alternatives are based on new industry standards developed by members of the Fast ID Online (FIDO) Alliance.
<!-- prettier-ignore-end -->

删除密码后，可以使用无密码方法登录，比如 Microsoft Authenticator、Windows Hello、物理密钥和短信代码。

### 两步验证

- [Bilibili: 两步验证的原理是什么？](https://www.bilibili.com/video/BV1Rp411f78Q/)

Google Authenticator 是目前最为通用的两步验证器，几乎所有支持两步验证的站点都对其提供了支持。

Telegram 则采取了不同的两步验证策略，为密码 + SMS，并用邮箱作为恢复手段。
