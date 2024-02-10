# 基础服务配置

这里介绍即使不是超算的 Linux 服务器也常用的基础服务的配置。

## 前置工具

- `systemctl`：管理服务

| 参数 | 说明 |
|:----:|:----:|
| `start` | 启动服务 |

- `ps`：查看进程

```bash
ps -A | grep ssh # 查看所有进程中包含 ssh 的进程
ps aux # 查看所有进程

```

## SSH

### 配置文件

仅展示关键选项

- 服务端：

```text title="/etc/ssh/sshd_config"
PasswordAuthentication no # 禁止密码登录
PermitEmptyPasswords no # 禁止空密码登录
PubkeyAuthentication yes # 允许密钥登录
PermitRootLogin no # 禁止 root 登录
DenyUsers root Dino # 禁止特定用户登录
Banner /etc/ssh/banner # Authentication 前显示的信息
AllowTcpForwarding no # 禁止 TCP 转发
AllowAgentForwarding no # 禁止 Agent 转发
X11Forwarding yes # 允许 X11 转发

Match Group root # 以下选项仅对 root 用户组生效
AllowTcpForwarding yes # 允许 TCP 转发
```

- 客户端：

```text title="~/.ssh/config"
Host GitHub # 自定义主机名
    HostName github.com # 主机地址
    User git
    IdentityFile ~/.ssh/github_rsa
    IdentitiesOnly yes
    Port 22
    AddKeysToAgent yes
    UseKeychain yes
```

```text title="/etc/ssh/ssh_config
# 同上，全局用
```

关键用法：端口转发、密钥登录。

### 其他坑点

- 守护进程服务名称可能不是 `sshd` 而是 `ssh`。

## VNC

在 Windows 上我们更经常见到 RDP，而 Linux 上设置 VNC 似乎更为常见。
