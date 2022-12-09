# LinuxTools

## 帮助

### tldr

* 安装 `tldr` 后，首先需要运行 `tldr -r` 获取最新数据库

## 系统管理



## 常用工具

* [tmux](tools/tmux.md)

## Deprecated

* `ifupdown` 网络管理器： Debian 的默认管理器

### NetworkManager

Debian 最小安装不会携带 NetworkManager，GUI 安装则会

* `apt install network-manager`
* `nmcli`
* `nmtui`
* `systemctl status network-manager`

## Shell

* `$` tells you that you are **not the root user**
* You can quote the argument with `'` or `"`, or escape just the relevant characters with `\`
* `exit`
* `history`: print your shell history to the standard output
* `CTRL + R`: type a substring you want to match for commands in your history

### Variables

* `$PATH`
* `$SHELL$`

### Pipes

* `> <`: file input/output
* `|`: chain programs
* `>>`: append to a file
* **NOTICE:** pipe operations are done by the **shell**, so `sudo echo 3 > brightness` only give echo the root permission. We can address this using `echo 3 | sudo tee brightness`
* 
* 

### Syntax

* `!` has special meaning even within `"`, so use `'` instead

> More on bash `quoting` manual page

### Bash Script

* shebang

* **variables:**

  * `foo=bar`: assign variable. **DO NOT USE `foo = bar`**, it'll be interpreted as calling the `foo` program
  * `$foo`: access the value

* **string**

  * `'`: **literal** strings, do not substitute variable values
  * `"`: substitute variables

* **function**

  * ``` 
    mcd(){
    	mkdir -p "$1"
    	cd "$1"
    }
    ```

  * `$0`: Name of the script

  * `$1-9`: Arguments 

  * `$@`: All arguments

  * `$#`: Number of arguments 

  * `$?`: Return code of previous command

  * `$$`: PID for current script 

  * `!!`: Entire last command 

* **Logic**

  * `|| &&` are **short-circuiting** operators
  * command can be separated within the same line using `;`
  
* **Substitution**

  * `$(CMD)`: Command substitution as variable
  * `<(CMD)`: Process substitution as file

* `#`: Explanation

* **Control**

  * ```
    for file in "$@"; do
    	if [[]]; then
    	fi
    done
    ```
    
  * **NOTICE:** When preforming comparisons in bash, try to use double brackets `[[]]`

  * 

* `/dev/null`: redirect output to this location

  * `>`: STDOUT
  * `2>`: STDERR
  
* **Shell Globbing**

  * Wildcards: `?` one character, `*` any amount of character
  
  * `{}`: bash will expand this list automatically
  
  * ```
    convert image.{png,jpg}
    touch {foo,bar}/{a..h}
    ```
  
* **Tools for bash scripts**

  * [ShellCheck](https://github.com/koalaman/shellcheck)

* **Shebang**

  * use `env` command to increasing the portability of your scripts

  * ```
    #! /usr/bin/env python
    ```

  * **NOTICE:** 

    * **Functions** have to be in the same language as the shell, while script can be written in any language (using **shebang**)
    * **Functions** are loaded once when their definition is read, while scripts are loaded every time they are executed.
    * **Functions** are executed in the current shell while scripts execute in their own process. So **functions** can modify environment variables while **scripts** can only use variables that have been **exported**
    * 






## Navigating

* Path on Linux and macOS is separated by `/` and `\` on Windows
* `pwd`: print working directory
* `cd`: change directory
* `.`: current working directory
* `..`: father directory
* `mv`: 
* `mkdir`: 
* `tree`
* 

### ls

* `-l`: **l**ong listing format
* `-a`
* `-h`: **h**uman readable sizes
  * `--block-size=SIZE`: with `-l`
    * 1024: K, M, G, T, P, E, Z ,Y
    * 1000: KB, MB, GB, TB, ...

  * `--si`: use powers of 1000

* `-r`: **r**everse order
* `-S`: sort by **S**ize, largest first
* `--sort=WORD`
  * `size`: S
  * time: t
  * version: v
  * extension: X


> More about information:
>
> `drwxr-xr-x`
>
> * owner, owning group, everyone else
> * `d`: is a directory
>   * `w`: modify (add/remove files in it)
>   * `x`: execute (enter/search a directory)
>   * `r`: read (list contents)
> * `rwx`
> * **nearly all the files in `/bin` have the `x` permission for everyone**

### ln: make links between files

### fasd/autojump: find frequent and/or recent files

 ```
 z cool #jump to your most frequent directory that contains "cool"
 ```



## System Path

* `/sys`: exposes a number of **kernel parameters** as files

> More on `man sysfs`





## Help

* man
* tldr
* which

### More about `man`

* Contents

* 

*     1   Executable programs or shell commands
         2   System calls (functions provided by the kernel)
         3   Library calls (functions within program libraries)
         4   Special files (usually found in /dev)
         5   File formats and conventions, e.g. /etc/passwd
         6   Games
         7   Miscellaneous (including macro packages and conventions), e.g. man(7), groff(7)
         8   System administration commands (usually only for root)
         9   Kernel routines [Non standard]

## Others

* date
* 

## File Related

* `touch`: change file timestamps (often used to create file)
* tee

### find

* `-name`: 
  * `-iname`: case insensitive
* `-type`: d(directory),f(file)
* `-path`: + '\*/xxx'
* `-mtime`: modified time (-1=last day)
* `-size`: +500k -10M
* `-exec + [command] {} \;` : `{}` represent the find result

Examples:

```
find . -name '*.tmp' -exec rm {} \;
find . -name '*.png' -exec convert {} {}.jpg \;
```

> A better way: using `fd` and `locate` command



### chmod: change file mode bits

```
chmod u+x {{path/to/file}}
```

* `u`: user, `a`: all users, `o`: others
* `+ - =`: give remove copy
* `-R`: recursively

### grep: print lines that match patterns

* `-C + [num]` : getting **C**ontext around the matching line
* `-v`: in**v**erting the match
* `-R`: **R**ecursively search

> More better replacement:
>
> * ack
> * ag
> * **rg**: ripgrep
>
> ```
> rg -t py 'import requests'
> rg -u --files-without-match "^#!"
> rg foo -A 5
> ```
>
> 