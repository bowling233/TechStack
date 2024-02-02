# 算法竞赛入门经典

## Ch4. 递归

### 段错误与栈溢出

可执行文件的格式

| 系统    | 格式 |
| ------- | ---- |
| Unix    | ELF  |
| DOS     | COFF |
| Windows | PE   |

**“段”**是二进制文件内的区域，某种特定的信息被保存在里面。用 `size` 工具可以得到可执行文件中各个段的大小：

```
$ size test
   text    data     bss     dec     hex filename
   1934     616       8    2558     9fe test
```

其中：

- Text Segment：正文段，存储指令
- Data Segment：数据段，已初始化的全局变量
- BSS Segment：BSS 段，未赋值的全局变量的空间

调用栈位于**堆栈段（Stack Segment）**，在运行时创建，也有自己的大小，不能越界访问。越界造成**段错误（Segmentation Fault）**。每次递归调用添加栈帧，造成的越界称为**栈溢出（Stack Overflow）**。

堆栈段中保存着**函数调用关系和局部变量**。局部变量过大也可能造成栈溢出。

栈的大小与操作系统相关：

- Linux 中，使用 `ulimit` 命令指定。`ulimit -a` 显示栈大小。
- Windows 中，栈大小储存在可执行文件中。`gcc -W1,--stack=16777216` 将栈大小设置为 16 MB。
    > 栈大小由 `ld` 指定，`-W1` 将其后的参数传递给 `ld`。

