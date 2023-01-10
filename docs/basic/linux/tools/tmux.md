---
tags:
    - Done
---

# tmux: terminal multiplexer

!!! info "Reference"

    - [GitHub Wiki](https://github.com/tmux/tmux/wiki/Getting-Started)

tmux 的三大使用场景：

1. 保护运行在远程主机的程序不因为连接终端而关闭。
2. 允许运行在远程主机的程序被多个不同的本地电脑访问。
3. 在一个终端中运行多个程序和解释器。

## 基本概念

- tmux 服务端和客户端

tmux 将所有状态保存在一个单独的主进程，称为 tmux 服务端。服务端在后台运行，管理运行在 tmux 中的所有程序并跟踪它们的输出。

用户通过启动一个客户端来附着（attach）到服务端。客户端将会控制终端，并使用 `/tmp` 中的 socket 文件与服务端通信。

- 会话、窗口和窗格（sessions, windows and panes）

    - Programs run in terminals in panes, which each belong to one window.
    - Each window has a name and one active pane.
    - Windows are linked to one or more sessions.
    - Each session has a list of windows, each with an index.
    - One of the windows in a session is the current window.
    - Sessions are attached to one or more clients, or are detached (attached to no clients).
    - Each client is attached to one session.

注意：会话没有序号，但必须有一个唯一的名字。窗口有序号，也可以有不唯一的名字。

## 命令

- 创建会话：`tmux new`
  - `-s` 指定会话名称
  - `-n` 指定窗口名称
  - `-d` 创建会话而不附着
  - `-A` 如果会话存在则附着
  - `command` 最后可以附带需要在窗口中运行的命令
  - Example: `tmux new -n mytopwindow top`
- 附着：`tmux attach`
  - `-t` 指定会话的名称
  - `-d` 使其他附着到该会话的客户端脱离
- 列出会话：`tmux ls`


### 内置命令行

`C-b :` 打开内置命令行。

- `:kill-server` 关闭服务端，结束所有会话。
- `:neww` 新的窗口
  - `-d` 创建但不设为当前窗口
  - `-n` 设置名字
  - `-t` 设定序号
  - `command` 最后跟执行的命令
- `:split-window` 分割窗格
  - `-h`, `-v` 水平、垂直分割
  - `-d` 不改变活动窗格
  - `-f` 让新窗格占据整个横、纵向位置
  - `-b` 将新窗格置于左、上方
  - 

## 状态栏

![status bar](https://github.com/tmux/tmux/wiki/images/tmux_status_line_diagram.png)

## 操作

使用 `C-b ?` 查看按键列表。

-   `d`：detach
-   `c`：create
-   `p`：previous
-   `c`：create
-   `<num>`：switch to the tab
-   `,`：rename

分割窗格

-   `"`：split horizontally
-   `%`：split vertically
-   `↑↓←→`：navigate through panes

改变当前窗口

- `0-9` 跳转到指定窗口
- `'` 调出窗口提示符，输入窗口编号后跳转
- `n` 下一个窗口
- `p` 前一个窗口
- `l` 上一个窗口

改变活动窗格

- `q` 显示窗格序号和它们的大小。在数字消失前按下数字可以跳转到指定窗格。
- `o` 跳转到下一个窗格



-   ` `：switch through different layouts
-   `z`：zoom in/out



