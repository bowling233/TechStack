---
tags:
  Ongoing

---

# make: GNU Make

<!-- prettier-ignore-start -->
!!!  ""
	
<!-- prettier-ignore-end -->

`make` 实用工具用于自动化从源代码构建程序的过程，`makefile` 文件描述了构建可执行文件的规则。

## Makefile

```makefile
all: hello.exe

hello.exe: hello.o
	gcc -o hello.exe hello.o

hello.o: hello.c
	gcc -c hello.c

clean:
	rm hello.o hello.exe
```

- 使用 ++tab++ 缩进命令。

<!-- prettier-ignore-start -->
!!! failure "必须使用制表符缩进"
	
	如果没有使用制表符缩进，会得到 `makefile:4: *** missing separator. Stop`
<!-- prettier-ignore-end -->

每个规则都有三个部分：一个目标、一个必需品列表和一个命令

```makefile
target: pre-req-1 pre-req-2 ...
	command
```

- 运行 `make` 时默认启动 `all` 的生成。

`make` 检查一个规则时，先查找必须品列表中的文件。如果文件不存在，则寻找生成文件的规则；如果所有文件都比目标旧，则不会执行生成命令（提示 `Nothing to be done`）。

## Makefile 语法

- 注释：`#` 直到行尾

- 规则语法：

  ```makefile
  target1 [target2 ...]: [pre-req-1 pre-req-2 ...]
  	[command1
  	command2
  	....]
  ```

- 伪目标（人工目标）：只执行命令，不生成文件。标准伪目标有：`all`、 `clean`、 `install`。

- 变量：`$` 开头，用圆括号或花括号包裹。如 `$(CC)`。

- 自动变量：

  - `$@`：目标文件名
  - `$*`：目标文件名（不带扩展名）
  - `$<`：第一个必需品的文件名
  - `$^`：所有必须品的文件名（用空格分隔，去除重复）
  - `$+`：所有必须品的文件名（用空格分隔，不去除重复）
  - `$?`：所有比目标新的必须品的文件名

- 虚拟路径：

  - `VPATH`：设定寻找依赖项和目标文件的路径，如 `VPATH = src include`
  - `vpath`：设定某类文件的寻找路径，如 `vpath %.c src`

- 模式：

  ```makefile
  %.o: %.c
  	$(COMPILE.c) $(OUTPUT_OPTION) $<
  ```

  - `%` 匹配文件名
  - 





