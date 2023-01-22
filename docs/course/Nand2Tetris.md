# Nand2Tetris

现代计算机系统就像是一座巨大的冰山，大多数人只看到了最顶端的一角。

本书的阐述顺序：

-   逻辑门构建
-   构建组合芯片和时序芯片
-   典型计算机体系架构
-   软件层级
-   基于对象的语言
-   编译器
-   简单的操作系统

## 第一章 布尔逻辑

本章讲解布尔门（gate）的构建。

-   布尔门是布尔函数的物理实现
-   将简单的布尔门相互连接实现复杂芯片的功能
-   使用软件仿真来设计硬件

### 布尔代数

布尔函数有几种表示方法：

-   用**真值表**表示
-   用**布尔表达式**表示
-   **规范表示**：其实就是《离散数学及其应用》中的**和之积**与**积之和**表示法。这种表示法告诉我们：任何一个布尔函数都能使用和、或、非三种布尔算子表示。

<!-- prettier-ignore-start -->
!!! question "考考你"

    - n 个输入变量的布尔函数的真值表有几行？
    - n 个输入变量的布尔函数有几个？
    	- 你能简单地讲解以下布尔表达式为什么实现了它的功能吗？
    		- Equivalence: $x\cdot y + \bar{x}\cdot\bar{y}$
    	- 构造 If x then y
<!-- prettier-ignore-end -->

与非门和或非门具有重要的性质：与、或、非算子都能用与非门和或非门来建构。

<!-- prettier-ignore-start -->
!!! question "考考你"

    试试用与非门和或非门建构与、或、非算子。
<!-- prettier-ignore-end -->

### 门

门（gate）是用于实现布尔函数的物理设备。门通过管脚（pins）进行输入输出。

任何具有转换（switching）和传导（conductiong）能力的技术都能用来构造门，比如磁、光等。今天，大多数门采用晶体管实现，这些晶体管在硅上蚀刻并封装为芯片。

<!-- prettier-ignore-start -->
!!! question "考考你"

    - 画出与、或、非门的电路符号表示。
    	- 画一个三通道与门的实现。
    	- 画一个异或门的实现。
<!-- prettier-ignore-end -->

逻辑电路设计就是**连接门电路的艺术**，设计的基本原则是使用尽可能少的门。

### 硬件描述语言（Hardware Description Language）

今天，硬件设计者使用 HDL 描述芯片的结构。硬件仿真器可以接受 HDL 程序，并输入变量的不同组合来产生仿真芯片的输出。

一个芯片的 HDL 定义包括 header 和 parts。Header 描述芯片的接口（芯片名称、输入输出管脚的名称），parts 描述底层电路的名称和拓扑结构，每个部分用一个语句描述该部分名称和与其他部分的连接方式。

<!-- prettier-ignore-start -->
!!! question "尝试读懂 HDL"

    这是内部模块的接口文档。
    
    | Name | Input pins | Output pins |
    | - | - | - |
    | Not | in | out |
    | And | a, b | out |
    
    接下来是 HDL 程序片段，猜一猜它在干什么？
    
    ```HDL
    CHIP Xor
    {
    	IN a, b;
    	OUT out;
    	PARTS:
    	Not(in=a, out=nota);
    	Not(in=b, out=notb);
    	And(a=a, b=notb, out=w1);
    	And(a=nota, b=b, out=w2);
    	Or(a=w1, b=w2, out=out);
    }
    ```
    
    接下来是 HDL 测试脚本，猜猜它在干什么？
    
    ```HDL
    load Xor.hdl,
    output-list a, b, out;
    set a 0, set b 0,
    eval, output;
    ```
<!-- prettier-ignore-end -->

### 实验：设计门电路

<!-- prettier-ignore-start -->
!!! tip "请先阅读"
	
	- Appendix A
	- [HDL Survival Guide](://drive.google.com/file/d/1dPj4XNby9iuAs-47U9k3xtYy9hJ-ET0T/view)
<!-- prettier-ignore-end -->

运行课程材料中的 `tools/HardwareSimulator.sh` 即可启动硬件模拟器。

#### 材料

-   Nand 门
-   书本提供的硬件仿真器

#### 目标

基本逻辑门：以下逻辑门可以**仅由 Nand 门**建构。试着做一下。

-   Not 门（又称为反相器 converter）
-   And 门
-   Or 门
-   Xor 门
-   Mux 门（选择器 multiplexor）
    -   输入：a, b, sel
    -   功能：If sel = 0 then out=a else out=b
-   DMux 门
    -   输入：in, sel
    -   输出：a, b
    -   功能：If sel=0 then {a=in, b=0} else {a=0, b=in}

通用计算机需要在多位数据线（总线 bus）上运行。比如一个 32 位计算机能够在 2 个给定 32 位总线上按位进行 And 函数计算。这需要**多位逻辑门**。

-   Not16
    -   Input: in[16]
    -   Out: out[16]
    -   Function: For i=0..15 out[i]=Not(in[i])
-   And16
-   Or16
-   Mux16
    -   Input: a[16], b[16], sel
    -   Output: out[16]
    -   Function: If sel=0 then for i=0..15 out[i]=a[i] else for i=0..15 out[i]=b[i]

多通道逻辑门

-   Or8Way
    -   Input: in[8]
    -   Output: out
    -   Function: out=Or(in[0],in[1],...,in[7])

多通道多位逻辑门

-   Mux4Way16 四通道 16 位选择器
    -   Input: a[16], b[16], c[16], d[16], sel[2]
    -   Output: out[16]
    -   Function: If sel=00 then out=a else if sel = 01 then out=b else if ...

<!-- prettier-ignore-start -->
!!! question "考考你"

    - n 通道选择器需要多少个控制位？
    - 描述 Mux8Way16
    - 描述 DMux4Way
<!-- prettier-ignore-end -->

## 第二章 布尔运算
