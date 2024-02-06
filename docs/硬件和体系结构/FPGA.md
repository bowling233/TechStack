---
tags:
    -   草稿
---

# FPGA

<!-- prettier-ignore-start -->
!!! info "参考资料"

    -   [Reconfigurable Embedded Systems with Xilinx Zynq APSoC
 | Youtube](https://www.youtube.com/playlist?list=PLXHMvqUANAFOviU0J8HSp0E91lLJInzX1)
<!-- prettier-ignore-end -->

## 前置概念

这些概念经过数字逻辑设计课程的学习，应该有一定了解，列出在这里作为复习：

-   门 Gate
-   触发器 Flip-Flop：内存的基本单位
    -   D 触发器
    -   JK 触发器
    -   T 触发器
    -   SR 触发器
-   锁存器 Latch
-   寄存器 Register

### LUT、CLB 和 SB 实现了 FPGA

-   LUT：Look Up Table，查找表，是 FPGA 的基本单元，用于实现逻辑功能。
-   CLB：Configurable Logic Block，可配置逻辑块，是 FPGA 的基本单元，由 LUT、寄存器和其他逻辑组成。
-   SB：Switch Box，开关盒，是 FPGA 的基本单元，用于连接 CLB 和其他 CLB。

<!-- prettier-ignore-start -->
??? info "其他概念"

    -   BGA：Ball Grid Array，球栅阵列，是一种封装形式。
    -   IC：Integrated Circuit，集成电路。
    -   AIC：Application-Specific Integrated Circuit，专用集成电路。
    -   FPGA：Field-Programmable Gate Array，现场可编程门阵列。
<!-- prettier-ignore-end -->

### FPGA 开发流程

-   IP 核：一种可重用的设计单元。知道在 Vivado 中如何使用即可。Vivado 也有创建、封装 IP 核的工具。

## VGA

-   驱动方式：
    -   像素直接驱动
    -   标准制式驱动（VRAM 扫描输出），将显示内容事先存储在显存 VRAM 中，信息在屏幕上显示的位置和 VRAM 单元地址一一对应，像素定位和同步时间固定。
-   显示原理：光栅扫描
    -   从左到右从上到下
    -   前后过冲 porch。
    -   回扫时不显示，也称为消影线。过冲往往不消隐。
-   VGA 各类标准：
    -   VGA 本身是 640x480 的。具体计算如下：
        -   同步脉冲 96 像素、返回过冲 45 像素、前过冲 13 像素、6 个富余像素，每行共 800 像素。
        -   帧同步脉冲 2 行、返回过冲 30 行、前过冲 9 行、4 行富余，每帧共 525 行。
        -   采用 60 HZ 刷新率，帧周期 $\frac{1s}{60}$，行周期 $\frac{1}{60*525}$，像素周期 $\frac{1}{60*525*800}\approx 40ns$，因此采用 25MHZ 的时钟频率。
-   水平同步计数器：可以用纯粹计数器和组合电路构成，这里用状态机描述：

```verilog
always @(posedge clk or posedge rst) begin
    if (rst) begin
        hsync <= 1'b0;
        hcount <= 10'd0;
    end else begin
        hcount <= hcount + 10'd1;
        case(hcount)
            HSC: hsync <= 1'b0;
            HBP: hsync <= 1'b1;
            HACT: hcount <= 10'd0;
            default: ;
    end
end
```

-   垂直同步计数器：同样用主时钟触发，用行结束信号作为垂直计数使能，从而实现帧计数器。

```verilog
always ...
    if(hcount == 10'd799)
        vcount <= vcount + 10'd1;
```

-   像素地址合成：用扫描同步状态生成：

```verilog
wire[9:0] col = hcount - 10'd144;
...
```

-   综合封装以后的 VGA 模块：

```verilog
module VGA(
    input clk,
    input rst,
    input [11:0] Din,
    output [8:0] row,
    output [9:0] col,
    output rdn, // 视频显示使能
    output reg [3:0] R, G, B,
    output reg HS, VS
)
```



