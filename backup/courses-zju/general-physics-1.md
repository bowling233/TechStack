# 普通物理学 I （H）

!!! abstract "课程简介"

    -   开课时间：2022-2023 春夏
    -   授课教师：Michael Smidman、路欣
    -   分数构成：
        -   作业 30%
        -   期中考试和课后 Quiz 30%
        -   期末考试 40%
    -   授课方式：双语教学

!!! note "个人评价"

    在外教班上学普通物理学，首先遇到的障碍就是语言问题。大多数同学在听完第一节课后，要么换到了其他班上，要么开启自学。
    
    外教班的普通物理学授课内容以《Physics》为主，试图**让你深刻理解物理学的一些基本思想**。从每次课后的 Quiz 和作业内容来看，并不会有复杂的计算和分析（其他班的内容则就像是高中物理竞赛），但是考察得会细节的知识，需要对各种基本定理的思想和推导过程了如于心。

## 考前补天

### 相对论

- 解决相对论问题时，明确以下东西：
    - 静止参考系和运动参考系
    - 固有时间和固有长度
    - 事件发生的时间和地点

- 洛伦兹变换：记住下面两个公式，其他公式都能推导出来：
    $$
    \gamma=\frac1{\sqrt{1-u^2/c^2}}\\
    x'=\gamma(x-ut)\\
    t'=\gamma(t-ux/c^2)
    $$

    - 速度变换：
        $$
        v_x'=\frac{\Delta x'}{\Delta t'}\\
        v_y'=\frac{\Delta y'}{\Delta t'}
        $$

    - 钟慢效应：钟表的固有时 $\Delta t_0$ 与你测量得到的时间 $\Delta t$ 之间的关系。

        - 关键条件：对于钟所在静止参考系中，两次测量事件的地点相同。

        - 方法一：你在 $S$ 系中静止，钟在 $S'$ 系中静止。

            - 你在 $S$ 系中发出两个事件：第一次读取钟的时间、第二次读取钟的时间。这两个事件的时间间隔是你要取得的 $\Delta t$，地点也不同（钟移动了）。

            - 这两个事件在 $S'$ 系中是同一地点的（都是钟的位置），而时间间隔为固有时 $\Delta t_0$。

            - 代入洛伦兹变换公式得到：
                $$
                0=\gamma(\Delta x - u\Delta t)\\
                \Delta t_0 = \gamma(\Delta t - u\Delta x / c^2)
                $$
                消去 $\Delta x$ 得到结果 $\Delta t = \gamma \Delta t_0$。

        - 方法二：你在 $S'$ 系中静止，钟在 $S$ 系中静止。

            - 你在 $S'$ 系中发出两个事件。这两个事件的时间间隔是你要取得的 $\Delta t$。

            - 这两个事件在 $S$ 系中是同一地点的，$\Delta x = 0$，时间间隔为 $\Delta t_0$。

            - 代入洛伦兹变换公式得到：
                $$
                \Delta t = \gamma(\Delta t_0 - u\Delta x/c^2) = \gamma\Delta t_0
                $$
                直接得到了结果。

    - 尺缩效应：一根杆的固有长度 $L_0$ 与你测量得到的长度 $L$ 之间的关系。

        - 关键条件：对于测量者所在的静止参考系中，两次测量事件时间相同。

        - 方法一：你在 $S$ 系中静止，杆在 $S'$ 系中静止。

            - 你在 $S$ 系中同时发出两个事件：测量杆头的位置和杆尾的位置。$\Delta t = 0$，$\Delta L$ 是你要的量。

            - 在 $S'$ 系中看这两个事件，它们不同时发生，但已知它们之间的距离为 $\Delta L_0$。

            - 代入洛伦兹变换公式得到：
                $$
                \Delta L_0 = \gamma(\Delta L - u \Delta t) = \gamma\Delta L
                $$
                直接得到了结果。

        - 方法二：你在 $S'$ 系中静止，杆在 $S$ 系中静止。

            - 你在 $S'$ 系中同时发出两个事件：测量杆头的位置和杆尾的位置。$\Delta t' = 0$，$\Delta L$ 是你要的量。

            - 在 $S$ 系中看这两个事件，它们不同时发生，但已知它们之间的距离为 $\Delta L_0$。

            - 代入洛伦兹变换公式得到：
                $$
                \Delta L = \gamma(\Delta L_0 - u\Delta t)\\
                \Delta t' = 0 = \gamma(\Delta t - u\Delta L_0/c^2)
                $$
                消去 $\Delta t$ 得到结果 $\Delta L = \frac{\Delta L_0}{\gamma}$

- 光的多普勒效应：

    - 光的传播方向与运动方向相同时：

    $$
    f=f_0\sqrt{\frac{1-u/c}{1+u/c}}
    $$

    - 若相对靠近，则用 $-u$ 代替。

- 狭义相对论动力学

    - 动量
        $$
        \mathbf{p}=\frac{m_0}{\sqrt{1-(v/c)^2}}\mathbf{v}
        $$

    - 质量
        $$
        m=\frac{m_0}{\sqrt{1-(v/c)^2}}
        $$

        - 光子的质量是
            $$
            m_\phi=\frac{hv}{c^2}
            $$

    - 相对论动量和能量关关系式
        $$
        E^2=c^2p^2+E_0^2=c^2p^2+m_0^2c^4
        $$

    -

### 分子动理论和理想气体

$$
T_{tr}=273.16\mathrm{K}\\
T_C=T-273.15\\
$$

Ideal gas law:
$$
pV=NkT=nRT
$$

- Boltzmann constant $k=1.38\times10^{-23}\mathrm{J/K}$
- Molar gas constant $R=8.31\mathrm{J/mol\cdot K}$

Thermal Expansion:

$$
\Delta L = \alpha L \Delta T
$$

- $\alpha$ is the coefficient of linear expansion.

- For many solids, called *isotropic,* the percent change in length for a given temperature change is the same for all lines in the solid. So we have volume expansion:

$$
\Delta V = \beta V \Delta T = 3 \alpha V \Delta T\\
\Rightarrow \beta = 3 \alpha
$$

### Pressure

Molecular View of Pressure:

- Average impulsive force exerted by on molecule: $F_x=\frac{mv_x^2}{L}$
    - Change in momentum: $2mv_x$
    - Time required to cross the cube: $\frac{L}{v_x}$
- ==Total force on face of cube==:
    - $\rho=Nm/L^3$ is density.

$$
p = \frac1{L^2}\frac{\sum mv^2_{ix}}{L} = \rho(\frac{\sum^2_{ix}}{N})=\rho(v^2_x)_{av}=\frac13\rho(v^2)_{av}
$$

> `rms` is root-mean-square

$$
\Rightarrow v_{\mathrm{rms}}=\sqrt{(v^2)_{av}}=\sqrt{\frac{3p}{\rho}}
$$

- **Root-mean-square speed** of the molecules is useful measure of average molecualr speed.

### Mean Free Path

Mean free path $\lambda$ is the average value of **straight-line distance** our chosen molecule travels between collisions. All molecules of the gas have **the same** mean free path.
$$
\lambda=\frac{kT}{\sqrt2\pi d^2 p}
$$

### Distribution of molecular speeds

**Maxwell speed distribution:**
$$
N(v)=4\pi N(\frac{m}{2\pi kT})^{3/2}v^2e^{-mv^2/2kT}
$$
Consequences:

- Most probable speed $v_p =\sqrt\frac{2kT}{m}$
- Average speed $v_{av} =\sqrt{\frac{8kT}{\pi m}}$
- Root-mean-square speed $v_{rms} = \sqrt\frac{3kT}{m}$
- ==Average translational kinetic energy== $K_{trans}=\frac32 kT$

### Real Gases

$$
(p+\frac{a}{V_m^2})(V_m-b)=RT
$$

### 热力学

- 四大准静态过程

    - 等体过程（isochoric）
    - 等压过程（isobaric）
    - 等温过程（isothermal），等温线（isotherm）
    - 绝热过程（adiabatic），条件是为绝热（in thermal isolation）

- 循环过程

    - $$
        \Delta E = 0, Q = A
        $$

    - 热机（heat engine）

        - 顺时针方向

        - $$
            \eta = \frac{A}{Q_1}
            $$

    - 制冷机（refrigerator）

        - 逆时针方向

        - $$
            \omega=\frac{Q_2}{A}
            $$

- 卡诺循环（Carnot Cycle）

    - 两恒温热源之间工作。

    - 两个准静态的绝热过程和两个准静态的等温过程。

    - 有正、逆循环

    - $$
        \eta_C=1-\frac{Q_2}{Q_1}=1-\frac{T_2}{T_1}\\
        \omega = \frac{T_2}{T_1-T_2}
        $$

    - 卡诺定理：可逆机效率最高，为：
        $$
        \eta = 1 - \frac{T_2}{T_1}
        $$

- 热力学第二定律

    - 不可能从单一热源吸热使之完全转化为功而不产生其他影响。
    - 热量不可能自发从低温物体传向高温物体。

- 可逆过程

    - 准静态过程+无耗散作用=可逆过程。
    - 不可逆过程实例：
        - 摩擦：功转化为热。由热力学第二定律，热不可能再完全转化为功。
        - 热量从高温物体直接传向低温物体：同上。
        - 气体自由膨胀：用活塞将气体压回去时，必须对气体做功，功转化为气体向外界放出的热，不可能再转化回功。
        - 气体迅速膨胀：活塞附近气体压强小于气体内部压强。如果要用活塞推回去，活塞附近压强不能小于气体内部压强，必定要多做功。这将增加气体内能，以热量形式放出，不可能再转化回功。
    - 过程的可逆与否，与中间状态是否为平衡态密切相关。

- 熵

    - 熵是一个状态函数，只与初末状态有关，与过程无关。

    - 熵的表达式为：
        $$
        \Delta S = \int^2_1(\frac{\delta Q}{T})_{可逆}
        $$

    - 在可逆过程中，$\frac{\delta Q}{T}$ 就是系统的熵变。对于不可逆过程，应当假想一个与其初末状态相同的可逆过程，用可逆过程的公式来计算。

    - 在一个可逆循环中，熵变等于 $0$。

    - 不可逆过程中的熵

        - 自由膨胀
            - 此时不能将 $\frac{\delta Q}{T}=0$ 看作熵变，因为过程不可逆。
            - 设想一个同样初末状态的可逆等温膨胀过程，积分后得 $\Delta S = \frac{m}{M}R\ln{\frac{V_2}{V_1}}>0$。
        - 热传导
            - 将两个物体一起看作一个系统。设 $T_1>T_2$。
            - 系统总熵变为 $\frac{\delta Q}{T_2}-\frac{\delta Q}{T_1} > 0$。

    - 熵增加原理：

        - 封闭系统中，任何不可逆过程，导致系统熵增加。熵只在可逆过程中不变。

    - 玻尔兹曼关系：$S=k\ln W$。其中 $W$ 是热力学概率，即宏观状态所包含的微观状态数。

    -
