# 手机折腾记

因为鸿蒙系统无法通过谷歌安全认证，我的华为手机的谷歌服务处于瘫痪状态。于是我翻出了破旧的 Redmi 6，刷上了 MIUI Global，真正拥有了一部在“墙外”的手机。

## Redmi 6 刷机

怕刷 Lineage OS 把手机折腾坏，于是选择了 MIUI Global，它配备了完整的谷歌套件。小米持续开放 ROM 下载对极客真是太友好了。

### 解锁 BootLoader

小米和红米手机一直都支持解锁 BootLoader。请按照官网教程解锁：

-   [Official: MIUI unlock](http://www.miui.com/unlock/index.html)

按开机键+音量下键或使用 ADB 命令将手机重启到 BootLoader 模式。

<!-- prettier-ignore-start -->
??? note "安装 ADB"
    
    - Ubuntu: `sudo apt install android-tools-adb`
    - Windows: [Android SDK Platform Tools ZIP file for Windows](https://dl.google.com/android/repository/platform-tools-latest-windows.zip)

    参考：[Xda: How to install ADB on Windows, macOS, and Linux](https://www.xda-developers.com/install-adb-windows-macos-linux/)
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
??? note "ADB 基本使用"
    
    - `adb devices` 列出连接的设备
    - `adb shell` 连接手机 shell
    - `adb reboot` 让手机重启到指定模式：bootloader|recovery|sideload|sideload-auto-reboot
<!-- prettier-ignore-end -->

解锁完成后，再次让手机启动到 bootloader。

### 下载 ROM 并刷入

-   [MIUI ROM Latest Downloads](https://xiaomifirmwareupdater.com/miui/)

在该网站下载合适的 ROM 包，类型选择 Fastboot，文件扩展名为 `.tgz`。下载后逐层解压。

-   [Official: Xiaomi Flash Tool](https://www.xiaomiflash.com/)

下载小米官方线刷工具。该工具只能在 Windows PC 上运行。

安装线刷工具，驱动会自动安装。接下来按以下步骤操作：

1. 点击“加载设备”。如果手机连接正常则会显示在列表中。
2. 选择解压的 ROM 包文件夹，如果选择不正确则会弹窗提示找不到脚本。
3. 在窗口最下方调整选项，不要选择“全部清除并加锁”，这会让手机重新上锁。
4. 刷机。

### 开机

如果在手机初始设置过程中连接网络，则谷歌服务请求更新的环节无法通过（除非你的路由器有代理）。因此，推荐长按电源键开启飞行模式，在无网络环境下完成初始设置，进入系统，安装好代理软件后再登录账号。

## 手机管理

### 用 ADB 命令行删除 ROM 厂商内置软件

-   [XDA: How to uninstall carrier/OEM bloatware without root access](https://www.xda-developers.com/uninstall-carrier-oem-bloatware-without-root-access/)

```
adb shell # 连接手机终端
pm list packages # 列出应用包名
pm uninstall -k --user 0 NameOfPackage # 卸载应用包
```

你也可以在谷歌商店下载 App Inspector 在手机上查阅每个应用的信息，知道包名是对应哪个应用。

<!-- prettier-ignore-start -->
!!! danger "删除系统应用时务必查询应用信息"
    
    Android 系统组件一定不能卸载，MIUI 系统核心组件替换时必须小心。

    如：`com.android.provider.` 开头的，大部分是 Android 系统 API 接口提供者，应当保留。`com.android.` 开头的部分软件被 UI 产商替换，可以尝试更改为自己需要的。但一定要注意备份。
    
    当你准备抛弃 MIUI 并使用 Google 套件替换系统功能时，请先退出小米账号，解除手机和小米账号的绑定，再卸载和小米云服务有关的组件。否则将面临手机被锁定且因为缺少服务组件无法解锁的窘境。

    !!! info "参考资料"
        
        - [MIUI 13 System Apps 清单](https://gist.github.com/mcxiaoke/0a4c639d04e94c45eb6c787c0f98940a)
        - [Android 开发者文档：日历提供程序概览](https://developer.android.com/guide/topics/providers/calendar-provider)
        - [备份你的应用：How do I get an apk file from an Android device?](https://stackoverflow.com/questions/4032960/how-do-i-get-an-apk-file-from-an-android-device)
        - [备份你的数据：Backup android app, data included, no root needed, with adb](https://gist.github.com/AnatomicJC/e773dd55ae60ab0b2d6dd2351eb977c1)

??? success "误删系统组件导致系统崩溃、被锁或无法开机"

    只要你的手机 Bootloader 仍然保持解锁状态，就有无损修复的机会。

    我删除了小米云服务、小米账号以及相关 SDK 后重启手机，手机即显示“Device Locked”，需要输入绑定的小米账号的密码才能解锁。可是，SDK 都被删除了，输入密码也无法登录，显示 `RPC Error`。而且，手机进入锁定状态会自动关闭 ADB 等功能，手机系统处于无法动弹的状态。

    以下是我的修复步骤：

    1. 电脑登录 [小米云服务](https://i.mi.com/)，解除对应设备的找回设备功能。
    2. 使用物理按键将手机重启至 Fastboot 模式，使用 MIUI 官方线刷工具，以保留数据的方式刷入系统镜像，以补上 MIUI 关键组件。
    3. 重启手机，此时仍处于锁定状态。连接网络，稍等一下，手机就自动解锁了（小米服务器向手机发送解绑指令）。
<!-- prettier-ignore-end -->


<!-- prettier-ignore-start -->
!!! note "Harmony OS"

    上面的命令行在 Harmony OS 3 亲测可用。大卸特卸了一番。很难想象，华为在一个“华为视频”中就集成了 `com.huawei.himove.partner1`、`com.huawei.himovie.partner2`、`com.tencent.qqlivehuawei`、`com.sohu.sohuvideo.emplayer`、`com.huawei.himovie` 五个恶心东西。
<!-- prettier-ignore-end -->

### 应用商店

-   Google Play Store：纯净，易用，但需要全套谷歌服务。
-   Apkpure：非常全面，但下载的软件广告捆绑较多。
-   F-Droid：提供 FOSS（Free and Open Source Software）软件，有一些工具值得挖掘。
-   酷安：国内软件较全面。

### 有趣的工具

-   Iriun Webcam：将手机作为电脑摄像头。需要电脑安装对应软件。
-   JuiceSSH：手机远程终端，功能全面，对 Unicode 有很好的支持。
-   IP Lite 和 IP Tools：网络工具，后一个功能更多但有广告。两者都有付费版。

## 使用手机作为安全工具

### 谷歌账号管理

当你第一次在具有谷歌套件的手机上登录时，谷歌将会信任这个手机并将其作为安全管理器。当你再次在新设备上登录时，谷歌不会再提供向手机、邮箱发送验证码的选项，仅提供使用信任的手机或平板设备进行验证。

如果你登录的第一台手机设备不能使用了怎么办？比如在鸿蒙系统上使用 MicroG 登录谷歌账号，再安装谷歌套件后会因为设备未经谷歌安全认证而无法连接到谷歌服务器、闪退。这时可以在常用的电脑上登录 [Google Accounts](https://accounts.google.com)，删除对应的手机设备。于是你又可以使用短信验证码登录了。

### 无密码账户

-   [Apple: Apple、谷歌与微软承诺拓展对 FIDO 标准的支持，以加速普及免密码登录](https://www.apple.com.cn/newsroom/2022/05/apple-google-and-microsoft-commit-to-expanded-support-for-fido-standard/)
-   [Google: One step closer to a passwordless future](https://blog.google/technology/safety-security/one-step-closer-to-a-passwordless-future/)

<!-- prettier-ignore-start -->
!!! note "What is passwordless authentication?"
    
    Passwordless authentication is a form of **multi-factor authentication (MFA)** that replaces passwords with two or more verification factors secured and encrypted on a user’s device, such as a fingerprint, facial recognition, a device pin, or a cryptographic key. The credentials never leave the device, eliminating the risk of phishing. These alternatives are based on new industry standards developed by members of the Fast ID Online (FIDO) Alliance.
<!-- prettier-ignore-end -->

删除密码后，可以使用无密码方法登录，比如 Microsoft Authenticator、Windows Hello、物理密钥和短信代码。

### 两步验证

-   [Bilibili: 两步验证的原理是什么？](https://www.bilibili.com/video/BV1Rp411f78Q/)

Google Authenticator 是目前最为通用的两步验证器，几乎所有支持两步验证的站点都对其提供了支持。

Telegram 则采取了不同的两步验证策略，为密码 + SMS，并用邮箱作为恢复手段。
