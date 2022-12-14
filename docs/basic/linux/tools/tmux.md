---
tags:
    - Done
---

# tmux: terminal multiplexer

窗口层级：

-   session
    -   window
        -   pane

输入 `tmux` 时发生了什么？

## Keybindings

-   `Ctrl+B`：脱离输入
    -   `d`：detach
    -   `c`：create
    -   `p`：previous
    -   `c`：create
    -   `<num>`：switch to the tab
    -   `,`：rename
    -   `"`：split horizontally
    -   `%`：split vertically
    -   `↑↓←→`：navigate through panes
    -   ` `：switch through different layouts
    -   `z`：zoom in/out

## Commands

-   `new -t <name>`
-   `a -t <name>`：attach
-   `ls`
