# Windows

## 远程管理

远程管理 Windows 系统并不容易，特别是使用微软账户时。可能你都不知道应该怎么指定 SSH 的用户名。这里记录我查找到的解决办法。然而 Windows 系统更新频繁，这里的内容可能随时间而不再适用。

### 防火墙

首先查看以下几个地方，它们可能影响你能否从外部网络访问 Windows

- 网络配置文件：是公有网络还是私有网络？每当你接入一个新的网络时，Windows 都会询问配置文件。而防火墙的某些规则对待不同配置文件起不同作用。
- 防火墙规则：有几条重要的规则需要确保可用
    - ICMP：如果你 `ping` 不通，检查该协议相关的防火墙规则是否允许数据包通过
    - 特殊端口：如 22、80 等端口，看你自己需要的服务进行开启

### SSH

如何在 Windows 上启用 OpenSSH Server 请查看官方文档，这里记录登录方法。

- 用户名：使用 `[System.Security.Principal.WindowsIdentity]::GetCurrent().Name` 这条 Powershell 指令查询。当你使用微软账户时，直接使用账户主邮箱（显示在设置中的），比如 `windows@outlook.com`。SSH 命令会有两个 `@`，这没有关系，会正确识别。
- 密码：仅用于临时测试，建议之后更改为密钥登陆。
- 密钥：请自行查看用户目录下的 `sshd_config` 文件，你会发现管理员账户的 `authorized_keys` 存放在另一个目录，而不是用户文件夹下。找到那个目录，添加你的密钥即可。

### RDP

[StackExchange: Unable to access a remote computer through Remote Desktop Connection when using a Microsoft Account](https://superuser.com/questions/1222431/unable-to-access-a-remote-computer-through-remote-desktop-connection-when-using)

上面这个问题的讨论是我能找到的解决办法最全的了。省流如下：

> Further to the above, I believe (from later found articles) that if the user signs in with the Microsoft's account password at least once rather than the PIN the issue may also be fixed. (Have confirmed this as the best fix)

可能当初我们安装系统时，就是直接使用 Microsoft 账户，并随即按照提示设置好了 PIN。上面的回答指出，我们必须至少使用 Microsoft 账户的密码在本机上登录一次后，远程桌面才会接受我们使用 Microsoft 账户密码进行的登录。

设置中 *Require Windows Hello sign-in for Microsoft accounts* 等选项可能也会有影响，具体可以查阅解答。

!!! note "安装 Windows 系统时，请从本地账户开始"

    综合上面的解答和评论来看，安装 Windows 时，先不登录 Microsoft 账号是最好的。

    - 你可以自定义本地账户的名称，否则微软会截取你账户名称的前几个字符，使用户文件夹名称看起来很丑。
    - 不会出现上面远程登录的这些问题。
