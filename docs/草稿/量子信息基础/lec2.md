# 光子和它们在复向量空间中的量子态

本节课可能被各种记号搞的糊里糊涂的，我们来梳理一下。

## 琼斯运算

本节课前半部分其实是在介绍怎么使用[琼斯运算](https://en.wikipedia.org/wiki/Jones_calculus)的各种符号来表示光的偏振并引出量子态的概念。就我个人感觉来说，从两能级系统进行引入或许会更容易理解一些🫠。

偏振光的状态用琼斯向量表示，光学元件用琼斯矩阵表示。偏振光通过光学元件就能运算出新的偏振态。该运算只适用于完全极化的光，不能用于部分极化等其他光。

先说结论：

| 偏振态 | 琼斯向量 | 狄拉克记号 |
| --- | --- | --- |
| x 轴线偏振 | $\begin{bmatrix} 1 \\ 0 \end{bmatrix}$ | $\ket{H}$ |
| y 轴线偏振 | $\begin{bmatrix} 0 \\ 1 \end{bmatrix}$ | $\ket{V}$ |
| 与 x 轴夹角为 $\theta$ 的线偏振 | $\begin{bmatrix} \cos\theta \\ \sin\theta \end{bmatrix}$ | |
| 左旋圆偏振 | $\frac{1}{\sqrt{2}}\begin{bmatrix} 1 \\ -i \end{bmatrix}$ | $\ket{L}$ |
| 右旋圆偏振 | $\frac{1}{\sqrt{2}}\begin{bmatrix} 1 \\ i \end{bmatrix}$ | $\ket{R}$ |

实数的都好理解，让我们看看复数是怎么表示旋转偏振光的。

在电磁学中，平面电磁波表示为下面的形式：

$$
\displaystyle {\begin{pmatrix}E_{x}(t)\\E_{y}(t)\\0\end{pmatrix}}={\begin{pmatrix}E_{0x}e^{i(kz-\omega t+\phi _{x})}\\E_{0y}e^{i(kz-\omega t+\phi _{y})}\\0\end{pmatrix}}={\begin{pmatrix}E_{0x}e^{i\phi _{x}}\\E_{0y}e^{i\phi _{y}}\\0\end{pmatrix}}e^{i(kz-\omega t)}
$$

$E$ 是上式的实部，复数乘子用于表示相位信息。琼斯矢量即为：

$$
\displaystyle {\begin{pmatrix}E_{0x}e^{i\phi _{x}}\\E_{0y}e^{i\phi_{y}}\end{pmatrix}}
$$

表示了振幅和相位信息。在这里，我们把 $z$、$t$ 的信息都去掉了。

为了便于计算，通常把它归一化为单位长度，这就得到了上面的琼斯向量。到这里，$\ket{H}$ 这样的线偏振光的表示就应该理解清楚了。

接下来我们看相位，这里会引入复数。根据欧拉公式，$i = e^{i\frac{\pi}{2}}$，与 $1 = e^{i0}$ 相比是一个 $90^\circ$ 的相位差（延迟相位差）。观察左旋圆偏振的琼斯向量，它的 $y$ 分量为 $-i$，说明比 $x$ 方向的要延迟 $\frac{\pi}{2}$。考察 $t=0$ 时刻开始，$x$ 方向振幅从 $1$ 开始减小，$y$ 方向振幅从 $0$ 开始增大，这就是左旋圆偏振光矢量的轨迹。

接下来，不妨用几个光学器件来做点计算，进一步体会琼斯运算的意义。

| 器件 | 琼斯矩阵 |
| --- | --- |
| 穿透方向平行x轴的线偏振片 | $\displaystyle {\begin{pmatrix}1&0\\0&0\end{pmatrix}}$ |
| 穿透方向与x轴夹45°的线偏振片 | $\displaystyle {\frac {1}{2}}{\begin{pmatrix}1&1\\1&1\end{pmatrix}}$ |
| 右旋偏振片 | $\displaystyle {\frac {1}{2}}{\begin{pmatrix}1&i\\-i&1\end{pmatrix}}$ |
| 穿透方向与x轴夹 $\displaystyle \Psi$ 的线偏振片 | $\displaystyle {\begin{pmatrix}\cos ^{2}\Psi &\cos \Psi \sin \Psi \\\cos \Psi \sin \Psi &\sin ^{2}\Psi \end{pmatrix}}$ |

## 量子态

本节课剩余部分对这个线性空间作了一些解释。重点在于理解共轭和投影算子。
