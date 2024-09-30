# Computer Architecture: A Quantitative Approach

## 第一章：量化设计与分析基础

### 1.5 集成电路中功率和能量的趋势

系统设计者考虑三个问题：

- 处理器需要的**最大功率**是多少？如果供电系统不能满足峰值功率需求，往往会导致电压下降，设备无法正常工作。
- **持续的功率**是多少？一般称为 **TDP（Thermal Design Power）**，通常比峰值功耗低，比平均功耗高。一般系统的供电和散热系统都和 TDP 相匹配。
- 能耗和能耗效率。通常**以能耗而不是功率作为指标**，不论是 PC 还是云服务场景。

    !!! exmaple

        处理器 A 比 B 功率高 $20%$，但只需要 $70%$ 的时间来完成任务。**对于一个相同的任务**，A 的能耗为 $1.2 \times 0.7 = 0.84$，比 B 少。

处理器内的能耗分为两种：

- 动态能耗（dynamic energy）：切换晶体管开关消耗的能量 $E_{\text{dynamic}} \propto C \times V^2$，与电容负载和电压有关。20 年来，处理器的电压从 5V 降到 1V，正是为了降低动态能耗。
- 静态能耗（static energy）：晶体管漏电流消耗的能量 $E_{\text{static}} \propto I \times V$，随着晶体管数量的增加而增加。比如一些高性能芯片中使用大量的 SRAM 缓存，将显著增加静态能耗。

### 1.7 可靠性

基础设施服务商提供 SLA（Service Level Agreement）或者 SLO（Service Level Objective）来保证服务的可靠性。在 SLA 中，系统在 Service Accomplishment 和 Service Interruption 两个状态间切换，切换的原因分别为 failure 和 restoration。相应地定义了一下可靠性指标：

- 可靠性指标：
    - MTTF（Mean Time To Failure）：正常运行的平均时间
    - FIT（Failure In Time）：每 $10^9$ 小时的故障次数

    上面两个指标互为倒数。比如，MTTF 为 $10^6$ 小时，则 FIT 为 $\frac{10^9}{10^6} = 10^3$。

    - MTTR（Mean Time To Repair）
    - MTBF（Mean Time Between Failure）= MTTF + MTTR
- 可用性指标：

    $$
    \text{Availability} = \frac{\text{MTTF}}{\text{MTTF} + \text{MTTR}}
    $$

要计算多个子系统组成的系统的可靠性（MTTF），一般先计算每个子系统的 FIT，相加得到整个系统的 FIT，取倒数即为 MTTF。

