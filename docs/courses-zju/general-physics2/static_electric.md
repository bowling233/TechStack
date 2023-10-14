# 电学

## 静止电荷的电场

### 电荷 库仑定律

-   电荷是相对论不变量，与运动无关。
-   $e=1.6\times10^{-19}\mathrm{C}$
-   库仑定律
-    $\varepsilon_0$ 真空电容率（permittivity of free space）或真空介电常数（dieletric constant of vacuum）。
-    库仑定律只适用于点电荷。与叠加原理结合能够求解静电学中所有问题。

$$
\begin{array}{l} 
\vec{F}=\frac{1}{4\pi\varepsilon_0}\frac{q_1q_2}{r^2}\hat{r} \\
k = \frac{1}{4\pi\varepsilon_0}=9\times10^9\mathrm{N\cdot m^2/C^2} \\
\varepsilon_0=8.85\times10^{-12}\mathrm{C^2/N\cdot m^2}
\end{array} 
$$


### 静电场 电场强度

-   没有物质作传递介质的超距作用是不存在的。
-   电磁场是物质存在的一种形态，分布在一定范围的空间里，具有能量、动量等属性，并通过交换场量子来实现相互作用的传递。电磁场的媒介子是光子，电荷间相互作用的传递速度也是电磁场的运动速度，光速。
-   静电场是**相对于观察者静止的电荷**在其周围激发的电场。
-   电场强度：$\vec{E}=\frac{\vec{F}}{q}$
    -   电场强度形成矢量场 $\vec{E}(\vec{r})$。
    -   电场强度叠加原理。
    -   连续分布电荷电场强度：$\vec{E}=\int \mathrm{d}\vec{E}=k\int \frac{\mathrm{d}q}{r^2}\hat{r}$

<!-- prettier-ignore-start -->
!!! example "电偶极子"

    两个大小相等符号相反的电荷，间距为 $l$，比所考虑的场点到它们的距离小得多时，称为电偶极子（electric dipole）。电偶极子的电偶极矩（electric dipole moment）为 $\vec{p}=q\vec{l}$，方向由负电荷指向正电荷。

    -   在轴线延长线上计算电场强度：$\vec{E_A}=\frac{1}{4\pi\varepsilon_0}\frac{2\vec{p}}{x^3}$
    -   在中垂线上计算电场强度：$\vec{E_B}=-\frac{1}{4\pi\varepsilon_0}\frac{\vec{p}}{y^3}$

    远离电偶极子处场强与距离三次方成反比，与电偶极矩成正比。
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
!!! example "均匀带电直棒"

    无限长带点直棒附近某点电场强度 $E = \frac{1}{4\pi\varepsilon_0}\frac{2\lambda}{r}$，其中 $\lambda$ 为电荷线密度。以上结论对靠近有限长直棒中部区域也近似成立。
<!-- prettier-ignore-end -->
