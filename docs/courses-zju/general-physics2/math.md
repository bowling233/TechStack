# 数学基础

## 几种坐标系

二维平面上的：

- 极坐标变换：$x=r\cos\theta,y=r\sin\theta$
    - 雅可比行列式为 $r$。

三维空间中的：

- 球坐标变换：$x=r\sin\theta\cos\phi,y=r\sin\theta\sin\phi,z=r\cos\theta$
    - 两个角分别是与 $x$ 轴和 $z$ 轴的夹角。
    - 雅可比行列式为 $r^2\sin\theta$，与 $z$ 轴夹角。
- 柱坐标变换：$x=r\cos\theta,y=r\sin\theta,z=z$
    - 雅可比行列式为 $r$。

一些概念

- 立体角：以观测点为球心，构造一个单位球面；任意物体投影到该单位球面上的投影面积，即为该物体相对于该观测点的立体角。$\Omega = \frac{S}{r^2}$，其中 $S$ 为球面上的面积，$r$ 为球心到球面的距离。
    - 球面坐标系中，任意球面的极小面积为：$\mathrm{d}A = (r\sin\theta\,\mathrm{d}\varphi)(r \mathrm{d}\theta)=r^2(\sin\theta\,\mathrm{d}\theta\,\mathrm{d}\varphi)$，极小立体角为 $\mathrm{d}\Omega = \frac{\mathrm{d}A}{r^2} = \sin\theta\,\mathrm{d}\theta\,\mathrm{d}\varphi$
    -  对极小立体角做曲面积分即可得立体角：$\Omega= \iint_S \mathrm{d}\Omega = \iint_S \sin\theta\,\mathrm{d}\theta\,\mathrm{d}\varphi$
    -  定向曲面：$\Omega= \iint_S \frac{dA}{r^{2}} =\iint_S \frac { \vec{r} \cdot \textrm{d}\vec{S}}{\left| \vec{r} \right|\, r^2}= \iint_S \frac { \vec{r} \cdot \textrm{d}\vec{S}}{ r^3}$。
    -  计算例：顶角为 $2\theta$ 的圆锥的立体角为 $\int_0^{2\pi} \int_0^{\theta}  \sin \theta' \ d \theta' \ d \phi = 2\pi\int_0^{\theta} \sin \theta' \ d \theta' = 2\pi\left[ -\cos \theta' \right]_0^{\theta} \ = 2\pi\left(1 -\cos \theta \right)$.


## 其他

### 幂次前缀

| Prefix | Symbol | Factor |
| ------ | ------ | ------ |
| yotta  | Y      | $10^{24}$ |
| zetta  | Z      | $10^{21}$ |
| exa    | E      | $10^{18}$ |
| peta   | P      | $10^{15}$ |
| tera   | T      | $10^{12}$ |
| giga   | G      | $10^{9}$ |
| mega   | M      | $10^{6}$ |
| kilo   | k      | $10^{3}$ |
| hecto  | h      | $10^{2}$ |
| deca   | da     | $10^{1}$ |
| deci   | d      | $10^{-1}$ |
| centi  | c      | $10^{-2}$ |
| milli  | m      | $10^{-3}$ |
| micro  | μ      | $10^{-6}$ |
| nano   | n      | $10^{-9}$ |
| pico   | p      | $10^{-12}$ |
| femto  | f      | $10^{-15}$ |
| atto   | a      | $10^{-18}$ |
| zepto  | z      | $10^{-21}$ |
| yocto  | y      | $10^{-24}$ |