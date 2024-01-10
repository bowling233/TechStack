# FPGA 学习笔记

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






