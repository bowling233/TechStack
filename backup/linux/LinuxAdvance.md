# Linux Advance

<!-- prettier-ignore-start -->
!!! abstract
    
    此处记录 Linux 新手期后可以学习的一些**使用技巧**。内容更加深入的笔记请参见各专题。
<!-- prettier-ignore-end -->

## CSAPP Bootcamp 1

### 目录操作

- `~<username>` 快速移动到某用户的家目录
- `cd -` 回到移动前的目录

### 传输文件 `scp`

简单记法：`scp <from> <to>`，`-r` 递归，

例子：

```bash
scp local_file remote_host:path
scp remote_host:path local_file
```

**当然，也可以在 remote 之间拷贝啦。**

### 【重要】文件管理

- `rmdir`

<!-- prettier-ignore-start -->
!!! tip "删除的习惯"
    
    以下几个命令是非常坏的习惯，永远不要使用！！！

    ```bash
    rm -rf /
    rm -rf *
    rm -rf .
    mv /home/user/* /dev/null
    ```

    关于其他千万不要做的事，可以参考以下文章：

    > - [](https://www.tecmint.com/10-most-dangerous-commands-you-should-never-execute-on-linux/)
    > - [](https://www.howtogeek.com/125157/8-deadly-commands-you-should-never-run-on-linux/)
<!-- prettier-ignore-end -->

- Vim swap files

<!-- prettier-ignore-start -->
!!! tip "E325: ATTENTION"
    
    你可能在保存文件时遇到 `Swap file "xxxx" already exists!` 报错。这种情况通常在多个 Vim 会话同时编辑一个文件时发生。
<!-- prettier-ignore-end -->

文件没有被正确保存时 Vim 会产生一个如 `.<file_name>.swp` 的文件。Vim 会给出提示和选择，请参照提示选择你需要的操作。

- 使用 `tar`

<!-- prettier-ignore-start -->
!!! tip "归档"
    
    在 Linux 中，最通用的归档文件格式是 `.tar`，并衍生如 `.tar.gz` 和 `.tar.bz` 等。
<!-- prettier-ignore-end -->

`-c` Create, `-x` Open(untie) tar file in current directory, `-z` gzip, `-v` verbose, `-f` specify file name.

### 文本处理

- `sort`

`-d` Dictionary order, `-f` ignore case, `-n` numeric sort, `-r` reverse.

<!-- prettier-ignore-start -->
!!! tip "你知道吗"
    
    `cat` 其实是 `conCATenate`，意为**按顺序连接**。
<!-- prettier-ignore-end -->

- `head` 与 `tail`

`-cx` = `--bytes=x`, `-nx` = `--lines=x`.

- `grep` Global Regular Expression Print

Searches for patterns **in a file** (if not provided, all files are recursively searched).

Syntax:

```bash
grep [OPTION] PATTERNS [FILE]
```

`-c` count, `-h`