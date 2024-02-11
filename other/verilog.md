# Verilog 简明教程

!!! note 本篇教程主要依据《Verilog 数字系统设计（第三版）》。"

要熟练掌握 Verilog，硬件知识必不可少，《数字逻辑设计》课程已经覆盖了大部分内容，这里不再赘述。本篇笔记侧重于 Verilog 的语法和使用，帮助同学们解决实验、大作业中的代码问题。

## 〇、目标

在实际使用中，我们需要掌握两种 Verilog 文件的编写。一种是模块（Module），一种是测试（Testbench）。

## 一、数据类型、变量、运算符号、基本语法规则

和学习 C 语言的过程一样，我们简单看一眼 Verilog 具有的数据类型、变量和运算符号。

### 数据类型

或许你会想，硬件描述语言为什么要有数据类型。人们只是出于编程语言的惯例，把硬件（如触发器等）抽象成了数据类型。我们可以从数字逻辑电路中抽象出的数据类型有：

- `wire`：抽象自模块内部的连线，不能存储数据。
- `reg`：抽象自寄存器，可以存储数据。

它们都有位宽的概念，如 `wire [7:0] a;` 表示 `a` 是一个 8 位的连线。方括号里的上下限由你自己决定，比如也可以写成 `wire [8:1] a;`。习惯上从 `0` 开始。

此外还有很多数据类型，用得较少，暂不介绍。

### 常量

Verilog 中的常量都是整型（integer），表示方式为：

```text
<位宽>'<进制><值>
```

可以使用的进制有：

- 二进制：`b` 或 `B`
- 八进制：`o` 或 `O`
- 十进制：`d` 或 `D`
- 十六进制：`h` 或 `H`

值除了各进制对应的数字外，还可以是 `x`（未知值）和 `z`（高阻值，也可以表示为 `?`）。此外，还可以用下划线 `_` 分隔，便于阅读。

举几个例子：

```verilog
8'b1010_1100 // 8 位二进制数 10101100
4'b10x0 // 4 位二进制数，第三位为不定值
12'dz // 12 位十进制数，全为高阻值
8'h4x // 8 位十六进制数，前 4 位为 4，后 4 位为不定值
```

## 二、初识模块和测试

接下来我们将认识 Verilog 的基本组件——模块，并理解 Verilog 的三种编程模型：逻辑功能描述、内部连线描述、原语描述。

??? info "Verilog 设计层次"

    除了这三种编程模型，Verilog 还可以在 5 种层次上进行设计：系统级、算法级、寄存器传输级、门级、原语级。这些内容比较综合，暂时不进行介绍。

### 定义一个模块

一个 Verilog 模块就像 C 语言中的函数，我们需要定义它的名称、接口和逻辑功能。Verilog 模块被 `module` 和 `endmodule` 包围，`module` 紧跟着模块名和接口，如下所示：

```verilog
module block_name(a, b, c, d);
    output a, b;
    input c, d;
    // logic
endmodule
```

`input` 和 `output` 关键字的部分是 I/O 说明，它也可以写在端口声明语句，如：

```verilog
module block_name(output a, output b, input c, input d);
```

!!! tip "习惯上，输出引脚被放在前面。"

!!! note "二选一选择器的三种 Verilog 描述"

    === "逻辑功能描述"

        ```verilog
        module muxtwo(out, a, b, sl);
            input a, b, sl;
            output out;
            reg out;
            always @ (a or b or sl)
                if (sl)
                    out = b;
                else
                    out = a;
        endmodule
        ```

        这是逻辑功能描述，用类似 C 语言的语法（`if-else` 语句等）描述了模块的功能。从这段代码中，我们能立刻读懂模块的功能，但无法直接看出模块内部的连线方式。

    === "内部连线描述"

        ```verilog
        module muxtwo(out, a, b, sl);
            input a, b, sl;
            output out;
            wire out
            assign out = sl ? b : a;
        endmodule
        ```

        这是内部连线描述，使用 `wire` 声明了模块内部的连线，使用 `assign` 连接连线和逻辑。这种描述方式更加接近硬件的实现。

    === "原语描述"

        ```verilog
        module muxtwo(out, a, b, sl);
            input a, b, sl;
            output out;
            and #2 u1(out, a, ~sl);
            and #2 u2(out, b, sl);
            or #2 u3(out, u1, u2);
        endmodule
        ```

        计算机科学中所谓原语（primitive）的概念，就是别人提供给你的最底层能调用的功能，不能再分割得更小了。
        
        在 Verilog 中，原语就是一些基本的逻辑门，如 `and`、`or`、`not` 等。我们自然可以用这些基本逻辑门实现各种各样的逻辑电路。

接下来，我们要编写一个测试来验证我们写的选择器是否正确，验证的思路很简单，就是把所有可能的输入都输入一遍，然后检查输出是否正确。

```verilog
include "muxtwo.v"
module t;
    reg a, b, sl;
    wire out;
    muxtwo m1(out, a, b, sl);
    initial begin
        a = 0; b = 0; sl = 0;
    end
    #10;
    a = 0; b = 0; sl = 1;
    #10;
    a = 0; b = 1; sl = 0;
    #10;
    a = 0; b = 1; sl = 1;
    #10;
    a = 1; b = 0; sl = 0;
    #10;
    a = 1; b = 0; sl = 1;
    #10;
    a = 1; b = 1; sl = 0;
    #10;
    a = 1; b = 1; sl = 1;
endmodule
```

## 编程模型

在书中展示了几种 Verilog 编程方式：

- 逻辑功能描述：使用 `if` 等逻辑语句描述该模块的功能
- 内部连线描述：使用 `wire` 定义模块内部的连线，使用 `assign` 连接连线和逻辑
- 原语描述：使用 `and`、`or` 等原语描述模块的功能

数逻教材中的大部分 Verilog 都采用后两种编程方式结合。

## 模块的结构、数据类型、变量和基本运算符号

### 模块

两个部分，I/O 接口和逻辑功能。

基本模块结构如下：

接下来就是内部信号说明（`wire` 和 `reg` 等的声明）和功能定义（逻辑部分）

### 功能定义

有 3 种方式能够产生逻辑：

- `assign` 声明语句
- 实例元件 `and #2 ul(a, b, c);`
- `always` 块

```verilog
always @ (a or b)
    c = a & b;
```

`assign` 最常用，`always` 既可描述组合逻辑，也可描述时序逻辑，手段较多。

!!! warning "并行性"

    如果把上面三个部分放到一个模块中，它们之间是并行的。它们之间的顺序不会影响实现的功能。

    `always` 模块内，语句是顺序执行的。

### 使用模块

有两种方式：

- 严格按照定义的端口顺序来连接。

```verilog
block MyBlock(a, b, c, d);
```

- 用 `.portname(signal)` 来连接：

```verilog
block MyBlock(.a(a), .b(b), .c(c), .d(d));
```

第二种方式不必按端口顺序对应，提高可读性和可移植性。

#### 常量-`parameter` 类型

描述方式：`parameter <name1> = <expression1>, <name2> = <expression2>, ...;`

表达式必须是常量表达式。

示例：

```verilog
parameter r = 10, f = 20;
parameter average_delay = (r + f) / 2;
```

常见用法：

- 实例化时传参指定

    ```verilog
    module Decode(A,F);
        parameter Width=1, Polarity=1;
    endmodule
    module Top;
        Decode #(Width=4, Polarity=0) D1(A,F);
        Decode #(4, 0) D2(A,F); // 也可以省去关键字赋值
    endmodule
    ```

- 使用 `defparam` 语句改变任意模块的参数值

    ```verilog
    module Decode(A,F);
        parameter Width=1, Polarity=1;
    endmodule
    module Top;
        Decode D1(A,F);
        Decode D2(A,F);
        defparam D1.Width = 4, D1.Polarity = 0;
        defparam D2.Width = 4, D2.Polarity = 0;
    endmodule
    ```

#### 变量

- 网络数据类型：表示结构实体之间的连接
    - `wire`：单驱动

        ```verilog
        wire a;
        wire [7:0] b;
        ```

    - `tri`：多驱动
- 寄存器 `reg`：数据存储单元的抽象

    ```verilog
    reg [n-1:0] a;
    ```

- `memory` 型：对 `reg` 建立数组

    ```verilog
    reg[7:0] mem[0:255]; // 256 个 8 位寄存器组 mem
    reg[n-1:0] rega; // n 位寄存器 rega
    reg mema[n-1:0]; // n 个 1 位寄存器组 mema
    mema[3]=0; // 必须使用下标访问其中的单个寄存器进行读写
    rega=0;
    ```

#### 运算符和表达式

四则、位移、逻辑运算不再介绍。

- 位运算

    ```verilog
    ~ & | ^ ^~
    ```

- 三目运算
- 拼接运算

    ```verilog
    {a, b, c}
    ```

## 进阶：使用更加基础的工具

提前准备、学习以下工具，它们用于 Verilog 的编译、仿真、综合等。

- `verilator`：Verilog 编译器

看看系统贯通课的一个 `Makefile`：

```makefile
DIR_SRC				:=	src
DIR_BUILD			:=	build

VERILATOR_TOP		:=	Adder_1
VERILATOR_SRCS		:= $(shell find $(DIR_SRC) -name "*.v" -o -name "*.cpp")
VERILATOR_TFLAGS	:=	-Wno-WIDTH
VERILATOR_FLAGS		:=	--trace --cc --exe --Mdir $(DIR_BUILD) --top-module $(VERILATOR_TOP) -o $(VERILATOR_TOP) -I$(DIR_SRC)

.PHONY: all wave clean

all: clean
	verilator $(VERILATOR_TFLAGS) $(VERILATOR_FLAGS) $(VERILATOR_SRCS)
	make -C $(DIR_BUILD) -f V$(VERILATOR_TOP).mk $(VERILATOR_TOP)
	cd $(DIR_BUILD); ./$(VERILATOR_TOP)

wave:
	gtkwave $(DIR_BUILD)/V$(VERILATOR_TOP).vcd

clean:
	rm -rf build
```

编译时抄抄就好。注意到其中几个关键的参数：

- `--top-module`：编译出的模块名

`verilator` 将在 `DIR_BUILD` 编译出一大堆文件，还有一个 `.mk`，这是一个 `Makefile`。所以上面又 `make -C` 进入该目录使用该 `Makefile` 编译得到可执行文件，名称就是 `VERILATOR_TOP` 指定的。运行即可。此时 Testbench 也在里面。也可以看到 `gtkwave` 使用了其中的 `.vcd` 文件。

接下来再看看 Testbench 是怎么写的。

```cpp
#include "VAdder_1.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

#include <stdio.h>
#include <memory>

#define MAX_SIM_TIME 300
vluint64_t main_time = 0;

void poke(VAdder_1 *topp)
{
    topp->A = rand() % 2;
    topp->B = rand() % 2;
    topp->CI = rand() % 2;
    printf("[poke] S(?) CO(?) A(%x) B(%x) CI(%x)\n", topp->A, topp->B, topp->CI);
}

bool peek_and_check(VAdder_1 *topp)
{
    printf("[peek] S(%x) CO(%x) A(%x) B(%x) CI(%x)\n", topp->S, topp->CO, topp->A, topp->B, topp->CI);
    return (topp->S == topp->A ^ topp->B ^ topp->CI) && (topp->CO == (topp->A & topp->B) | (topp->A & topp->CI) | (topp->B & topp->CI));
}

int main(int argc, char **argv, char **env)
{
    Verilated::commandArgs(argc, argv);
    VAdder_1 *topp = new VAdder_1;

    Verilated::traceEverOn(true);
    VerilatedVcdC *tfp = new VerilatedVcdC;
    topp->trace(tfp, 99);
    tfp->open("VAdder_1.vcd");

    while (main_time < MAX_SIM_TIME && !Verilated::gotFinish())
    {
        printf("[time] %ld\n", main_time);
        poke(topp);
        topp->eval();
        tfp->dump(main_time);
        if (!peek_and_check(topp))
        {
            printf("Verification failed!\n");
            break;
        }
        main_time++;
    }

    tfp->close();
    delete topp;
    exit(0);
}
```

可以看到，我们编写的 Verilog Module 被转换为 C++ 中的一个类。我们将在 `main` 中实例化该 Module，并使用自己编写的 `poke` 和 `peek_and_check` 函数对其进行测试。其中 `poke` 用于随机生成输入，`peek_and_check` 用于检查输出是否正确。可以看到，类内的成员均是我们定义的 Label。`peek_and_ckeck` 函数手写了正确的逻辑表达式，并返回与 Module 输出的比较结果。Testbench 的编写还是比较容易理解的。
