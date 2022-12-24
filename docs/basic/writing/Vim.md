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

## Advanced

要想深入掌握 Vim 的使用，还要学习并练习很久。目前掌握基础章节的内容即可，有时间再继续阅读。

> From: Practical Vim 2th (Avalible on JD read)

!!! tip
    1. use repeat operator ++period++
    2. reduce unnecessary movement
    3. 
     

### 重复操作

* ++period++: 重复上次的操作。
    * NOTICE: 移动并不会被重复。

### 多文件多窗口

* 缓冲区：我们并不是在编辑文件，而是编辑文件在内存中的映像



### 其他操作符

#### 正常模式

* `>` indent 缩进
    * `>G` indent to the end
* `f` jump to character
    * `F` jump left
    * `;` repeat latest `f`, `t`
* `t` 跳至右侧第 n 个指定字符前

#### 选择模式

* ++ctrl+v++ 进入列选择模式

## Configuration

`~/.vimrc`

