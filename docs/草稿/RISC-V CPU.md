# RISC-V CPU 设计

!!! info "推荐资源"

    -   视频：
        -   Rong晔：[RISC-V设计入门指北](https://www.bilibili.com/video/BV1Qr4y1H7v8)
    -   项目：
        -   [tinyriscv](https://github.com/liangkangnan/tinyriscv)

## ALU

### Quick Review: Two's Complement

==todo==

减法到加法的转换关键在于：对一个补码表示的二进制数取补码，得到的结果是原数的相反数。要把减法转换为加法，只需要把减数取补码，然后做加法即可。

补码操作一般表示为取反加一。

### 加减法

`add` `sub`

只支持全字长的加减法。如果需要半字长、单字节的加减法，可以通过==todo==

溢出由编译器使用条件分支检测。溢出只在加法同号、减法异号时发生。==todo==

### 减法单元

书本和课件上以两种描述给出了相同的减法单元：

- 书本：`b` 取反，`CarryIn` 置 `1`
- 课件：`b` 与**扩展的** `sub` 异或，同时 `CarryIn` 置 `sub`

上面两种描述本质思想完全一样：取反加一。

### 乘法单元

`mul` `mulh` `mulhu` `mulhsu`

RISC-V 软件可以检查乘法结果的高位判断是否发生溢出：

==todo==

#### 简单版本

简单版本模仿竖式计算二进制乘法。对于 $m\times n$，结果可能为 $m+n$ 位。这个最简单的乘法器设计如下：

- 一个 64 位寄存器，存储乘数。每次取其最低位，决定是否要进行加法操作。
- 一个 128 位寄存器，存储被乘数。每次将其左移，输出到 ALU 进行运算。
- 一个 128 位寄存器，存储结果。输出到 ALU 进行运算。
- 一个 128 位 ALU，将位移的被乘数不断累加到结果寄存器上。

```verilog
module simple_multipler(
    input clk,
    input [63:0] A,
    input [63:0] B,
    output reg [127:0] O
);
    reg [63:0] multiplier;
    reg [127:0] multiplicand;
    reg [63:0] shitf_count; // count for 64 = 2^6 times shift

    always @ (posedge clk) begin
        if(rst) begin
            multiplier <= B;
            multiplicand <= {64'b0, A};
            shift_count <= 64'b0;
            O <= 128'b0;
        end
        else begin
            shift_count <= shift_count + 1;
            multiplier >> 1;
            multiplicand << 1;
            if(multiplier[0])
            begin
                O = O + multiplicand;
            end
        end
    end
endmodule
```

#### 优化版本

其实，每次运算只有 64 个位发生变化，我们可以将 ALU 和被乘数的位数均缩减到 64 位，并删去乘数寄存器，转而将其放置在结果寄存器的低位：

- 64 位 ALU、被乘数寄存器
- 129 位结果/乘数寄存器

!!! question "为什么不是 128 位？"

    这是为 ALU 的进位预留的 1 位。

```verilog
module refined_multiplier(
    input clk,
    input [63:0] A,
    input [63:0] B,
    input en,
    output reg [128:0] O
    output fi
);
    reg [63:0] multiplicand;
    reg [63:0] multiplier;
    reg [7:0] shift_count;
    reg running;

    always @ (posedge clk) begin
        if(rst) begin
            multiplicand <= A;
            multiplier <= B;
            reg <= 1'b0;
            O <= 1'b0;
            running <= 0;
        end
        else if(shift_count == 8'd64)
            running <= 0;
        else if(running) begin

        end
    end
endmodule
```

#### 带符号乘法

上面我们只考虑了无符号的情况。符号的处理很简单：直接从输入的最高位得到两个数的符号，并直接决定结果的符号，然后将两个数转换为正整数，进行无符号乘法。这样会减少一次迭代，为 carry-out 腾出了空间，可以将寄存器改回 128 位。

#### Booth's: multiplies two signed binary numbers in two's complement notation

该算法依次检查乘数的每一位，将被乘数加或减到结果上：

- 如果当前检查的位和前一位相同，则不改变结果
- 如果遇到 0，把被乘数加到结果上
- 如果遇到 1，把被乘数减到结果上

要理解这个算法为什么起作用，可以参考维基百科的解释。大概就是把每个 2 的幂都拆成一加一减。非常聪明的一个算法。

### 除法单元

`div` `divu` `rem` `remu`

长除法的本质就是不停地从被除数中减去除数。它的结构和乘法器类似，只是位移方向有所调整。

### 浮点运算单元
