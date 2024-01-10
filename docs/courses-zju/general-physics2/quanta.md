# 量子理论

<!-- prettier-ignore-start -->
!!! note "总体脉络"

    -   普朗克：解释黑体辐射，提出能量子假设。
    -   爱因斯坦：光电效应实验与经典理论的矛盾，光量子假说。
    -   玻尔：氢原子光谱，玻尔理论。
    -   德布罗意：物质波假说。
    -   薛定谔：薛定谔方程。
    -   海森堡：矩阵力学。
<!-- prettier-ignore-end -->



## 热辐射与能量子假设

黑体在任何温度下，对任何波长辐射能的吸收比都等于 $1$。任何空腔小孔相当于一个黑体的模型。物体的辐射本领越大，吸收本领也越大。黑体是完全的吸收体，也是理想的辐射体。

辐出度 $M(T)$ 表示单位时间内物体单位面积的辐射能量，单位为 $\mathrm{W/m^2}$。单色辐出度 $M(\lambda,T)$ 表示在 $\lambda$ 波长范围内的辐射能量，单位为 $\mathrm{W/m^3}$。吸收比 $a(\lambda,T)$ 是一个比值。

【图片：黑体辐出度按波长分布曲线】

-   Stefan-Boltzmann 定律
    -   黑体**总**辐出度与温度的四次方成正比 $M_0(T)=\sigma T^4$
    -   $\sigma=5.67\times 10^{-8}\mathrm{W/m^2\cdot K^4}$ 称为 Stefan-Boltzmann 常数。
    -   题型：计算黑体辐出度、温度。
-   Wien 位移定律：
    -   温度增高，单色辐出度峰值向短波方向移动 $T\lambda_{max}=b$。
    -   $b=2.898\times 10^{-3}\mathrm{m\cdot K}$ 称为 Wien 常数。
    -   题型：计算单色辐出度峰值波长、**温度**。
-   Plank 辐射定律：
    -   黑体辐射能量密度与波长的关系
    -   波长形式：$M_0(\lambda,T)=\frac{2\pi hc^2}{\lambda^5}\frac{1}{e^{\frac{hc}{\lambda kT}}-1}$
        -   试试用这个积分，可以得到 Stefan-Boltzmann 定律。
        -   对它求导可以得到 Wien 位移定律。
        -   $\lambda$ 很大时，得到 Rayleigh-Jeans 公式。
        -   $\lambda$ 很小时，得到 Wien 近似公式。
    -   频率形式：$M_0(\nu,T)=\frac{2\pi h\nu^3}{c^2}\frac{1}{e^{\frac{h\nu}{kT}}-1}$
    -   $h=6.626\times 10^{-34}\mathrm{J\cdot s}$ 称为 Plank 常数。
    -   题型：计算单色辐出度、**温度**。
    -   Plank 分布函数：$u(\nu)\mathrm{d}\nu = \frac{8\pi h\nu^3}{c^3}\frac{1}{e^{\frac{h\nu}{kT}}-1}\mathrm{d}\nu$

普朗克能量子假设：辐射黑体由大量带电的谐振子组成，它们可以发射和吸收辐射能，它们的能量是最小能量子 $\varepsilon=h\nu$ 的整数倍。$n$ 称为量子数。

## 光电效应 爱因斯坦的光子理论

## 生词表