---
tags:
    -   不完善
---
# ISA

## RISC-V 32

-   32 个 64 位寄存器 `x0-x31`，其中 `x0` 恒为 0。
-   $2^{61}$ 字节虚拟地址空间，`Memory[0]-Memory[2^61-1]`。
-   32 位称为 word，64 位称为 doubleword。
-   回忆 R、I、S、U 指令的格式。
-   以下是一些常用指令：

    ```text
    add, sub, 
    ld, lb, lbu
    sd
    slli, srli, srai
    sll, srl, sra
    and, or, xor
    beq, bne, blt, bge, bltu, bgeu
    lr.d, sc.d
    mul
    mulh, mulhsu, mulhu
    ```
-   如何实现锁（原子化操作）？

<!-- prettier-ignore-start -->
??? note "RISC-V 指令集助记卡"

    <embed src="./attachment/riscv指令集助记卡.pdf" style="width:100%; height:80vh;" type="application/pdf">

    <embed src="./attachment/riscv编程助记卡.pdf" style="width:100%; height:80vh;" type="application/pdf">

??? note "RISC-V 指令集标准"

    <embed src="./attachment/riscv指令集标准.pdf" style="width:100%; height:80vh;" type="application/pdf">
<!-- prettier-ignore-end -->



