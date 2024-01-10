# Verilog 笔记

<!-- prettier-ignore-start -->
!!! note "参考资料"

    本篇笔记主要参考《Verilog 数字系统设计》。
<!-- prettier-ignore-end -->

## 工具

提前准备、学习以下工具，它们用于 Verilog 的编译、仿真、综合等。

-   `verilator`：Verilog 编译器

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

-   `--top-module`：编译出的模块名

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

## 编程模型

在书中展示了几种 Verilog 编程方式：

-   逻辑功能描述：使用 `if` 等逻辑语句描述该模块的功能
-   内部连线描述：使用 `wire` 定义模块内部的连线，使用 `assign` 连接连线和逻辑
-   原语描述：使用 `and`、`or` 等原语描述模块的功能

数逻教材中的大部分 Verilog 都采用后两种编程方式结合。

## 模块的结构、数据类型、变量和基本运算符号

### 模块

两个部分，I/O 接口和逻辑功能。

基本模块结构如下：

```verilog
module block(a, b, c, d)
    input a, b;
    output c, d;

    wire e, f;
    assign e = a & b;
    assign f = a | b;
    assign c = e ^ f;
    assign d = e & f;
endmodule
```

-   `block` 是模块名，后面是输入输出端口
-   `input` 和 `output` 关键字的部分是 I/O 说明，它也可以写在端口声明语句，如：

```verilog
module block(input a, input b, output c, output d)
```

接下来就是内部信号说明（`wire` 和 `reg` 等的声明）和功能定义（逻辑部分）

### 功能定义

有 3 种方式能够产生逻辑：

-   `assign` 声明语句
-   实例元件 `and #2 ul(a, b, c);`
-   `always` 块

```verilog
always @ (a or b)
    c = a & b;
```

`assign` 最常用，`always` 既可描述组合逻辑，也可描述时序逻辑，手段较多。

<!-- prettier-ignore-start -->
!!! warning "并行性"

    如果把上面三个部分放到一个模块中，它们之间是并行的。它们之间的顺序不会影响实现的功能。

    `always` 模块内，语句是顺序执行的。
<!-- prettier-ignore-end -->

### 使用模块

有两种方式：

-   严格按照定义的端口顺序来连接。

```verilog
block MyBlock(a, b, c, d);
```

-   用 `.portname(signal)` 来连接：

```verilog
block MyBlock(.a(a), .b(b), .c(c), .d(d));
```

第二种方式不必按端口顺序对应，提高可读性和可移植性。

### 数据类型

共 19 种，这里介绍 4 种。

#### 常量-数字

描述方式：`<size>'<base><value>`，其中 `<size>` 是位宽，`<base>` 是进制，`<value>` 是值。

-   二进制：`b` 或 `B`
-   八进制：`o` 或 `O`
-   十进制：`d` 或 `D`
-   十六进制：`h` 或 `H`

特殊值：

-   `x`：未知值
-   `z` 或 `?`：高阻值

其他：

-   `_`：分隔符，用于提高可读性

示例：

```verilog
8'b10101100
4'b10x0
12'dz
8'h4x // 低四位为不定值
16'b1010_1100_0011_0101
```

#### 常量-`parameter` 类型

描述方式：`parameter <name1> = <expression1>, <name2> = <expression2>, ...;`

表达式必须是常量表达式。

示例：

```verilog
parameter r = 10, f = 20;
parameter average_delay = (r + f) / 2;
```

常见用法：

-   实例化时传参指定
    ```verilog
    module Decode(A,F);
        parameter Width=1, Polarity=1;
    endmodule
    module Top;
        Decode #(Width=4, Polarity=0) D1(A,F);
        Decode #(4, 0) D2(A,F); // 也可以省去关键字赋值
    endmodule
    ```
-   使用 `defparam` 语句改变任意模块的参数值
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

-   网络数据类型：表示结构实体之间的连接
    -   `wire`：单驱动
        ```verilog
        wire a;
        wire [7:0] b;
        ```
    -   `tri`：多驱动
-   寄存器 `reg`：数据存储单元的抽象
    ```verilog
    reg [n-1:0] a;
    ```
-   `memory` 型：对 `reg` 建立数组
    ```verilog
    reg[7:0] mem[0:255]; // 256 个 8 位寄存器组 mem
    reg[n-1:0] rega; // n 位寄存器 rega
    reg mema[n-1:0]; // n 个 1 位寄存器组 mema
    mema[3]=0; // 必须使用下标访问其中的单个寄存器进行读写
    rega=0;
    ```

#### 运算符和表达式

四则、位移、逻辑运算不再介绍。

-   位运算
    ```verilog
    ~ & | ^ ^~
    ```
-   三目运算
-   拼接运算
    ```verilog
    {a, b, c}
    ```

    ./configure PATH=/home/regcm/RegCM-ISC24/bin:$PATH CC="scorep mpicc" FC="scorep gfortran" MPIFC="scorep /home/regcm/RegCM-ISC24/bin/mpif90" CPPFLAGS=-I/home/regcm/RegCM-ISC24-scorep/include LDFLAGS=-L/home/regcm/RegCM-ISC24-scorep/lib LIBS="-lnetcdff -lnetcdf -lhdf5_hl -lhdf5 -lz" FCFLAGS=-ffree-line-length-512
