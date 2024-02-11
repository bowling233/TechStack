# Chapter 5 Digital Hardware Implementation

## Vocabulary

!!! info "Vocabulary"

    | English | Chinese |
    | :-----: | :-----: |
    | CMOS (Complementary Metal Oxide Semiconductor) | 互补金属氧化物半导体 |
    | PLD (Programmable Logic Device) | 可编程逻辑器件 |
    | ROM (Read Only Memory) | 只读存储器 |
    | PLA (Programmable Logic Array) | 可编程逻辑阵列 |
    | PAL (Programmable Array Logic) | 可编程阵列逻辑 |
    | FPGA (Field Programmable Gate Array) | 现场可编程门阵列 |
    | BIOS (Basic Input Output System) | 基本输入输出系统 |
    | IC (Integrated Circuit) | 集成电路 |
    | **package** | 封装 |
    | **die** | 芯片 |
    | wafer | 晶圆 |
    | transistor | 晶体管 |
    | gate | 栅极 |
    | drain | 漏极 |
    | source | 源极 |
    | channel | 沟道 |
    | terminal | 端口 |
    | contact | 触点 |
    | fuse | 熔丝 |

## Implementation Technology

### CMOS Transistor

- nMOS: drain at a higher voltage than source
    - gate voltage > threshold voltage: on (closed)
    - gate voltage < threshold voltage: off (open)

Input variable on the gate terminal represent the control voltage. nMOS: $X:X$, pMOS: $X:\overline{X}$.

In general, switches in series give an AND function and switches in parallel an
OR function.

### Fully Complementary CMOS Circuits

Except during transitions, there is a path to the output of the circuit $F$ either from the power supply +V (logic $1$) or from ground (logic $0$). Such a circuit is called static CMOS.

!!! info "[Quora: Why is PMOS good to pass logic 1 and NMOS is good to pass logic 0?](https://www.quora.com/Why-is-PMOS-good-to-pass-logic-1-and-NMOS-is-good-to-pass-logic-0)"

$F$ is implemented using pMOS and connects the circuit output to logic 1 (VDD), while $\overline{F}$ is implemented using nMOS and connects the circuit output to logic 0 (GND).

### Technology Parameters

- Fan-in: the number of inputs to a gate
- Fan-out: the number of gates that can be driven by a gate
- Propagation delay: the time required for a signal to propagate from input to output of a gate
- Power dissipation (dissipation): the amount of power consumed by a gate

## Programmable Implementation Technology

Four types of basic programmable logic devices (PLDs): ROM, PLA, PAL, and FPGA.

### ROM
