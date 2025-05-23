# 量子纠错

## 量子错误是什么？

对传统信息而言，错误可以用随机过程比如马尔可夫链来描述。可以写出一个概率转移矩阵表示从一个状态到另一个状态的概率。

在量子信息中，错误是与环境相互作用的结果。设环境为 $\ket{e_0}$，量子比特发生了如下错误：

$$
\ket{e_0}\ket{0} \rightarrow \ket{e_1}\ket{0} + \ket{e_2}\ket{1}\\
\ket{e_0}\ket{1} \rightarrow \ket{e_3}\ket{0} + \ket{e_4}\ket{1}
$$

通过一番换元拆解，可以把上面的变换拆成几个基本的变换：

$$
\ket{e_0}\ket{\psi} \rightarrow (\ket{d}I + \ket{a}X + \ket{b}Y + \ket{c}Z)\ket{\psi}
$$

于是我们就可以给错误分类：

| 矩阵 | 错误类型 |
| --- | --- |
| $I$ | 无错误 |
| $X$ | 位翻转 |
| $Y$ | 位翻转 + 相位偏移 |
| $Z$ | 相位偏移 |

对于 $n$ 比特的量子信息，可能发生的错误为：

$$
\ket{e_0}\ket{\psi_n} \rightarrow (\ket{d}I+ \sum^n_{i=1}(\ket{a_i}X_i + \ket{b_i}Y_i + \ket{c_i}Z_i))\ket{\psi_n}
$$

就是各种可能性变多了，上式有 $3n+1$ 项。

## 约化密度矩阵

用约化密度矩阵可以描述上面这种混合经典概率和量子叠加的情况。
