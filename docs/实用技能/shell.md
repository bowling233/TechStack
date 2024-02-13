---
tags:
    - 完善
---

# Shell

Linux、Windows、Android 等操作系统的 Shell 备忘。

## Windows

在 Windows 控制台上，Linux 中能用的控制字符基本都不能用，只有鸡肋的 ++ctrl+c++、++ctrl+a++、++ctrl+v++ 等。操作 Windows 终端还是使用全尺寸键盘比较舒适。

### `cmd.exe`

作为 Windows 系统的远古命令解释器，只具有很少的命令，使用 `help` 就可以查看。

除了内置命令，还有一些实用工具：

- 开关机：
    - `shutdown`
        - 立即关机：`shutdown /p /f`
        - 重启并自动登录并锁定：`shutdown /sg`
- 系统管理：
    - `chkdsk`：检查磁盘
    - `diskpart`：磁盘分区
    - `dism`：Windows 映像管理工具
    - `sfc`：系统文件检查
- 进程管理：
    - `tasklist`：列出进程
    - `taskkill`：结束进程
- 网络：
    - `ipconfig`：网络配置
    - `netstat`：网络状态
    - `net`：网络配置
    - `route`：路由表

### PowerShell

PowerShell 与其他 Shell 的一个显著区别是它的命令名称，一般为 `Verb-Noun` 格式，比如 `Get-Command`。

#### 关机

```PowerShell
Stop-Computer -Force -ComputerName localhost 
```

#### 获取帮助

```PowerShell
Update-Help
Get-Verb
Get-Command -Name -Verb -Noun [pattern]
Get-Help
help -Full
```

`help` 相当于 `Get-Help | more`。

!!! tip "需要找什么命令直接查询即可，比如服务相关就查 `Get-Command -Name Service`"

#### 对象

在 PowerShell 中，命令的结果作为对象传递，比如 `Get-Process` 返回 `System.Diagnostics.Process` 对象。这些是常用的操作对象的命令：

```PowerShell
Get-Member -MemberType
Select-Object -First n -Property Name, Source
Where-Object [condition]
```

类型的成员的种类（MemberType）可以是属性（Property），也可以是方法（Method）。比如 `Get-Service` 返回的 `System.ServiceProcess.ServiceController` 具有 `close()` 方法，可以直接调用：

```PowerShell
(Get-Service -Name w32time).Stop()
```

#### 变量

创建一个 `PSCustomObject` 类型的变量，具有 `Name` 成员，属性为 `w32time`（这是一个字符串 `System.String`）。

```PowerShell
$CustomObject = [pscustomobject]@{
 Name = 'w32time'
 }
```

#### 管道

PowerShell 管道可以对对象进行很多操作，不过在 Linux 中我们最熟悉的是文本处理。可以使用 `Get-Content` 和 `Out-File` 来进行：

```PowerShell
'Background', 'Windows' | Out-File -FilePath $env:TEMP\services.txt
Get-Content -Path .\LineNumbers.txt
Get-Item -Path .\LineNumbers.txt | Get-Content -Tail 1
```

#### 脚本执行权限

`ExecutionPolicy` 影响脚本能否执行，在客户端系统上一般都设置为 `Restricted`，任何脚本都无法执行。

```PowerShell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned
```

#### 更多

常用的比较运算符，和 bash 差不多：

```PowerShell
'PowerShell' -eq 'powershell'
-eq
-ceq #case sensitive
-gt
```

一个控制片段：

```PowerShell
$number = Get-Random -Minimum 1 -Maximum 10
do {
  $guess = Read-Host -Prompt "What's your guess?"
  if ($guess -lt $number) {
    Write-Output 'Too low!'
  } elseif ($guess -gt $number) {
    Write-Output 'Too high!'
  }
}
while ($guess -ne $number)
```

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
