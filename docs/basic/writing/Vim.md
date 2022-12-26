---
tags:
  - Ongoing
---

# Vim

## VSCode 中的 Vim

有一些方便的快捷键：

* `gd` - jump to definition.
    * 可以跨文件跳转。
* `gq` - on a visual selection reflow and wordwrap blocks of text, preserving commenting style. Great for formatting documentation comments.
    * 没搞懂。
* `af` - visual mode command which selects increasingly large blocks of text. For example, if you had "blah (foo [bar 'ba|z'])" then it would select 'baz' first. If you pressed `af` again, it'd then select [bar 'baz'], and if you did it a third time it would select "(foo [bar 'baz'])".
    * 选择代码块时非常之好用。
* `gh` - equivalent to hovering your mouse over wherever the cursor is. Handy for seeing types and error messages without reaching for the mouse!
    * 不错，可以得到函数提示。

## Basic

### Move Around

* Move the cursor
    * `e` move to the end of the word
    * `0` the head of the line
* ++ctrl+g++: show your location in the file
* `G` to the bottom of the file, `gg` to the start of the file
    * `[number] G` move to the line
* ++ctrl+w++ jump between windows

!!! note
    ++ctrl+w++x2 don't take effect in VSCode

### Edit

!!! note "Command Pattern"
    operator [number] motion
    all motion:

    * `w` word
    * `$` end of line
    * `c` character

* `x` delete character
* append
    * `a` insert after the cursor 
    * `A` insert at the end of the line
* undo
    * `u` undo previous actions
    * `U` undo all changes on a line, ++ctrl+r++ undo undo's
        * if you edit in another line, `U` will switch to the current line
* `p` paste
    * if you operate on a line (using `dd`, `yy` etc), the line will be pasted under current line
    * `gp` paste and move to the end
* replace
    * `r` replace charcter
    * `[number] r` replace the following n charater with the same character
    * `R` enter replace mode
* change
    * `c` change
    * `ce` change to the end of a word
* open
    * `o` open one line under the cursor and switch to insert mode
    * `O` open above
* copy
    * `y` copy selected content
    * `yy` or `Y` copy whole line
    * `yw` one word
    *  
* select
    * `v` enter visual mode
    * `V` select whole line
    * ++ctrl+v++ select a rectangle
    * `d` to cut

### Search

* `/` search forward
    * `n`, `N`
* `?` search backward
* ++ctrl+o++ go back to where you come from
* ++ctrl+i++ go forward

When the search reaches the end of the file it will continue at the start, unless the 'wrapscan' option has been reset.

* `%` matching parentheses
    * place the cursor on `(`, then type `%`

### Replace

* `:s/old/new` substitute the first occurence in the line
* `:s/old/new/g` substitute globally in the line
* `#,#s/old/new/g` #,# are the line numbers of the range
* `%s/old/new/g` change in the whole file
* `%s/old/new/gc` change in the whole file with prompt to check

### Commands

* `:wq` save a file and quit
* `:q!` quit without save
* `:!command` to execute external command
* `:w FILENAME` write current content to file
    * **VSCode current not support**
    * in visual mode, selected content will be saved
    * you will remain working in the origin file but not the saved file
* `r FILENAME` insert the contents of a file
* `r !COMMAND` insert the output of the command
    * insert operation behave like the paste opeartion

### Option 

Prepend `no` to switch an option off

* `:set KEY`
    * ic = ignorecase
        * to ignore for one search, use `\c`, that is `/search\c`
    * is = incserch: partial matche
    * hls = hlsearch: high light search results
        * to remove current hightlight, enter `:nohlsearch`
* ++f1++ or `:help` to open `help.txt`
    * `:help [something]` to find help on something
        * e.g. `:help insert-index`
* auto completion
    * ++ctrl+d++ to show possible commands
    * ++tab++ to complete (can complete command and path)
    * 

## 进阶操作

要想深入掌握 Vim 的使用，还要学习并练习很久。目前掌握基础章节的内容即可，有时间再继续阅读。

<!-- prettier-ignore-start -->
!!! info "参考文献"
    
    大部分内容来自《Vim 实用指南》（Vim Practical）
<!-- prettier-ignore-end -->

- 映射快捷键

为一些快捷键提供映射能大大提高效率，比如把 `jj` 映射为 ++esc++ 能让输入更高效。

!!! tip
    1. use repeat operator ++period++
    2. reduce unnecessary movement

### 模式

Vim 中，不同模式下各种按键产生不同的动作。接下来学习每种模式的工作方式。

#### Normal 普通模式

Vim 的语法是**操作符+动作=操作**。额外的规则是：当操作符重复执行时，它将作用于当前行。这时有一些简化，比如 `gUgU` 简化为 `gUU`。

<!-- prettier-ignore-start -->
??? note "操作符"
    
    `:h operator` 可以查阅完整的操作符列表。这里也记录一些常用的操作符：

    | Operator | Usage |
    | - | - |
    | c | change |
    | d | delete |
    | y | copy to register |
    | g~ | reverse case |
    | gu | to lower |
    | gU | to upper |
    | > | increase indent |
    | < | decrease indent |
    | = | automatic indent |
    | ! | 不知道怎么用，使用外部程序过滤{motion}跨越的行 | 

    ??? info "自定义操作符"
        
        [commentary.vim](github.com/tpope/vim-commentary) 插件为 Vim 支持的编程语言增加了注释命令。用 `gc{motion}` 触发。`gcap` 切换当前段落注释状态，`gcG` 注释当前行到文件尾，`gcc` 注释当前行。
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
??? note "动作命令"
    
    `:h motion` 可以查阅完整的动作列表。这里记录一些常用的动作：

    | Motion | Usage |
    | - | - |
    | l | letter |
    | w | next word |
    | e | end of next word |
    | b | begin of next word |
    | aw | a word |
    | ap | a paragraph |
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
!!! tip "普通模式的哲学"
    
    普通模式是 Vim 的默认模式，你可能会觉得这很奇怪。Vim 这样做的原因是：程序员应该**只花一小部分时间编写代码，绝大多数时间用来思考、阅读**，以及在代码中穿梭浏览。
<!-- prettier-ignore-end -->

- 控制撤销的粒度

`u` 撤销最新的修改。**一次修改**可以是改变文档内文本的任意操作，从进入插入模式开始，直到返回普通模式为止，在此期间的所有操作作为**一次修改**。因此，控制对 ++esc++ 键的使用是很关键的。让每个**可撤销块**对应一次思考过程，你可以在每次停顿输入时按下 ++esc++，把每次换行替换成 ++esc++ + `o`。

但是，如果在插入模式期间使用**光标键**移动光标位置，将产生新的撤销块，这很符合逻辑。这同样对 ++period++ 操作产生影响。

- 构造可重复的修改

如果需要在多个地方执行操作，需要仔细考虑一下。

<!-- prettier-ignore-start -->
!!! note "考考你"
    
    你的光标在行尾，你如何删除最后一个词？
<!-- prettier-ignore-end -->

有三种方式：`db,x`, `b,dw`, `daw`。想一想，这三种操作按下 ++period++ 后会发生什么？应该选择谁？

- 对数字作简单运算

`<C-a>` `<C-x>` 分别对数字执行加减。如果**不带数字**那么它们会递增递减，如果**提供数字前缀**则可以加减任意整数。

如果光标在数字上，这个数字会被加减。比如在 5 上执行 `10<C-a>` 会变成 15。

如果不在数字上，会在当前行正向查找一个数字，跳到那里，对数字进行运算。

<!-- prettier-ignore-start -->
!!! info "数字的格式"
    
    如 `007` 这样的数字会被解释为八进制，对其加减也会按对应的进制进行。你可以在 `vimrc` 中设置 `set nrformats=` 将所有数字都作为特定进制处理。
<!-- prettier-ignore-end -->

- 次数和重复

删除两个连续单词有 3 种方法：`d2w`, `2dw`, `dw.`。你可以说出它们的区别吗？

<!-- prettier-ignore-start -->
!!! tip "用重复代替次数计算"
    
    计算次数真是一件挺麻烦的事，对吧？你真的确信自己能每次都算对次数吗？或许，我们宁肯用多几次 ++period++ 来代替错误计算次数带来的撤销麻烦。这也能让你有更好的**细粒度**控制。
<!-- prettier-ignore-end -->

在必要的时候使用次数。比如，你要替换 3 个单词为另外 2 个单词。此时，你可以使用 `c3w` 删除并进入插入模式。此后按一次 `u` 就可以撤销整个更改。这又是一种对细粒度的把控。



* `>` indent 缩进
    * `>G` indent to the end
* `f` jump to character
    * `F` jump left
    * `;` repeat latest `f`, `t`
* `t` 跳至右侧第 n 个指定字符前

#### 块选择模式

* ++ctrl+v++ 进入列选择模式
     

### 重复操作

* ++period++: 重复上次的操作。
    * NOTICE: 移动并不会被重复。

### 多文件多窗口

* 缓冲区：我们并不是在编辑文件，而是编辑文件在内存中的映像





## Configuration

`~/.vimrc`

