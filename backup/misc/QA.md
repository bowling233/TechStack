# 问题记录

!!! abstract "简介"

    这里收集各种经常遇到的问题~

## 写代码

### C/C++

- Windows 系统下找不到某些系统调用函数

> 比如 [How to print time difference in accuracy of milliseconds and nanoseconds from C in Linux?](https://stackoverflow.com/questions/16275444/how-to-print-time-difference-in-accuracy-of-milliseconds-and-nanoseconds-from-c) 中的系统调用 `clock_gettime()` 其属于 POSIX 规范，Windows 不支持。在 POSIX 版 Mingw32-gcc 中可以使用，但是在 Windows 版 Mingw32-gcc 中无法使用。
> 解决方法：更换为 POSIX 版以兼容更多类 Linux 特性。

## 系统

### Linux

#### 硬件

!!! tips "遇到固件问题怎么办？"

    - 首先，查看发行版的手册，寻找解决固件问题的解决办法。
    - 更新 BIOS 版本。
    - 更新 Linux 内核。
    - 使用驱动检查工具。

- Debian 安装后无法启动，报错 `hdaudio hdaudioC0D2: Unable to configure, disabling` 等。

> Debian 使用的 Linux 内核太老，无法识别新核芯显卡。
> 在 Grub 的内核命令行中添加 `nomodeset`。进入系统后，升级 Linux 内核到最新的可用版本。
>
> ```shell
> sudo apt install linux-image-<flavour>
> ```
>
>
>
> ??? info "相关的 Linux 内核原码"
>
>     - [Github](https://github.com/torvalds/linux/blob/v5.7/sound/hda/hdac_i915.c#L140)
>
>     ```c
>     if (!IS_ENABLED(CONFIG_MODULES) ||
>          !request_module("i915")) {
>       /* 60s timeout */
>       wait_for_completion_timeout(&bind_complete,
>             msecs_to_jiffies(60 * 1000));
>      }
>     ```
>
>     这 1 分钟的等待错误在 2019 年得到修复，但是最近的 Debian 版本似乎仍然没有采用修复完成的内核。
>
>
>
> > Debian Wiki 关于显卡问题的简要提示：
> >
> > If you get a fixed low resolution (like 1024 x 768) with no choice of higher resolution in GUI and/or xorg-server log errors with missing device (like (EE) open /dev/dri/Card0 no such file or device) and/or non starting display manager (sddm etc), **make sure that your kernel is up to date (as the kernel has to recognize the graphics device)**. Also make sure that the appropriate firmware packages are up to date.
> >
> > 注意：Linux 内核负责识别显卡。
>
>
>
> !!! info "参考资料"
>
>     - [Debian Wiki: GraphicsCard](https://wiki.debian.org/GraphicsCard)
>     - [Debian Wiki: HowToUpgradeKernel](https://wiki.debian.org/HowToUpgradeKernel)
>
>

- 声卡不识别或声音设备仅有 `dummy output`

> 升级 BIOS。
>
>
> !!! info "参考资料"
>
>     - [Unix & Linux: Realtek ALC1220 audio chipset on Linux Mint 18.1](https://unix.stackexchange.com/questions/373777/realtek-alc1220-audio-chipset-on-linux-mint-18-1)
>
>

#### 文件系统

- 自动挂载的磁盘必须使用 root 写文件

> 原因：自动挂载到了 root 用户下
>
> 在挂载点下查看文件属性可以发现：
>
> ```bash
> $ ls -lah
> drwxr-xr-x 1 root    root   30 Mar 27 20:47 ./
> ```
>
> 并且无法使用 `chown` 更改目录所有者
>
> 解决办法：更改 `fstab` 文件
>
> 在 `OPTION` 列添加 `uid=1000` 即可将磁盘挂载到自己用户下。

#### 远程桌面

- 使用 Gnome 取代 xfce4 进行远程桌面：

> - 安装 `gnome-session`
>
> - 向 `~/.xsession` 写入 `gnome-session`
>
> 更多相关资料参见：
>
> - [Connected to GNOME desktop environment instead of ubuntu-gnome custom version · Issue #1723 · neutrinolabs/xrdp](https://github.com/neutrinolabs/xrdp/issues/1723)
> - [Setting gnome as desktop environment in .xsession - Ask Ubuntu](https://askubuntu.com/questions/584681/setting-gnome-as-desktop-environment-in-xsession)
> - [Ubuntu Xrdp 远程登录需要输入很多次密码授权来"创建/移除"色彩管理设备 - 9yu.cc](https://9yu.cc/index.php/archives/27/)
> - [seahorse - How can I stop being prompted to unlock the 'default' keyring on boot? - Ask Ubuntu](https://askubuntu.com/questions/867/how-can-i-stop-being-prompted-to-unlock-the-default-keyring-on-boot)

### Windows

#### 系统美化

- TranslucentTB 失效

> Windows11 限制了 Feature ID 编号为 26008830 的功能，对应的就是任务栏的状态。修复方法参考[知乎](https://www.zhihu.com/question/522335111/answer/2938550118)

- 隐藏的网络设备占用了静态 IP 地址：

> 见 [Error message when you try to set an IP address on a network adapter](https://learn.microsoft.com/en-us/troubleshoot/windows-server/networking/error-message-when-you-set-ip-address)，解决方法为使系统显示隐藏的网络设备并将其卸载。或者选择 No 并继续配置静态 IP 地址。

## 软件

### Git

![fatal: CRLF would be replaced by LF](https://toub.es/2012/05/28/fatal-crlf-would-be-replaced-by-lf/firstcommit.png)

- [git 多平台统一换行符](https://juejin.cn/post/6844903591258357773)

> - 增加配置文件 .gitattributes
>
> 虽然通过设置了 git 全局参数解决了问题，但是作为团队协作的话，并不能保证所有人都正确配好了。git 提供了.gitattributes 文件解决了这个问题。在项目根目录新建.gitattributes 文件，添加一下内容：
>
> `* text eol=lf`
>
> 通过这种方式避免有人没有设置 core.autocrlf 参数，并且将该文件加入版本控制中。
>
> 另外根据需要 .gitattributes 文件可以在项目不同目录中创建，而一些非文本文件可以设置为二进制文件，不用考虑换行符问题。
>
> - 项目已有内容转换换行符
>
> 对于项目已有内容如何进行转换呢，推荐使用 dos2unix 工具。最后使用编辑器的时候也确保换行符设置正确。

- [ssh 连接被拒 Connection refused](https://askubuntu.com/questions/610940/ssh-connect-to-host-github-com-port-22-connection-refused)

> 一般情况下应该是被 GFW 墙了导致的，可以尝试使用代理或者 VPN。如果还不行，可能是 22 端口被封，可以将 `git://` 链接改为 `ssh://` 链接，走 443 端口，如下：
>
> ```
> ssh://git@ssh.github.com:443/yourname/reponame.git
> ```
>
> 此外，可以查看 ssh 详细信息确定问题所在：
>
> ```
> ssh -vT -p 443 git@ssh.github.com
> ```

- [.gitignore 无效](https://stackoverflow.com/questions/25436312/gitignore-not-working)

>

### Syncthing

- [Is putting a Git workspace in a synced folder really a good idea?](https://forum.syncthing.net/t/is-putting-a-git-workspace-in-a-synced-folder-really-a-good-idea/1774)

> I’ve put my whole documents folder in syncthing and this includes a couple of git workspaces. Never had any problems. It might cause problems if you switch between computers very quickly, but as long as syncthing has time to sync it shouldn’t cause problems. One of the advantages I found is that when you switch between computers you are always in the same branch. And like you said you can commit when it actually make sense instead of everytime you leave your computer.

### VSCode

- [Compile multiple .c and .h files](https://github.com/microsoft/vscode-cpptools/issues/5502)

> Your filepath has a space (``) in it, so you will need to surround the full command in quotes, but doing so will escape the \* and it will not be used as a wildcard.
>
> I cant seem to find a way to escape the spaces in ${fileDirname}, but that will fix the command.

### Markdown

- [Obsidian 配合 Typora 使用](https://crazt.moe/archives/54/)
- 在 Markdown 中隐藏内容

```HTML
<details><summary>提示</summary>答案</details>
```

## Web

### 服务器

- blocked CORS policy: No 'Access-Control-Allow-Origin' header is present on the requested resource

> 我托管在 GitHub Pages 的笔记本希望向我用 Nginx 自建的 CDN 服务器请求资源，但 CDN 服务器的返回没有 CORS 头。**源站请求目标站，目标站必须允许源站请求它，不然浏览器就会拦截。**
> 参考 [https://enable-cors.org/server_nginx.html](https://enable-cors.org/server_nginx.html) 进行配置即可。
