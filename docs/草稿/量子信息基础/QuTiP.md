# QuTiP

## Python

- 常用库：

```python
import matplotlib.pyplot as plt
import numpy as np
from scipy.special import factorial
```

- 常用语句示例：

```python
n = 10
fib = [0, 1]
for i in range(2, n):
    fib.append(fib[i - 1] + fib[i - 2])
print(fib)

def sine_series(x, N):
    ans = 0.0
    for k in range(N + 1):
        ans = ans + (-1) ** k * x ** (1 + 2 * k) / factorial(1 + 2 * k)
    return ans
result = sine_series(x, N)
print("Series approximation:", result)
print("Error:", np.sin(x) - result)

xc, yc = random_coordinates(N)
max_dist, pnt1, pnt2 = max_dist(xc, yc)
plt.plot(xc, yc, "ro", markersize=8)
plt.plot(pnt1, pnt2, "b-", lw=2)
plt.show()
```

- NumPy:

```python
a = np.array([2.0, 4.0, 8.0, 16.0])
b = np.array([0, 1 + 0j, 1 + 1j, 2 - 2j])
c = np.array(["a", "b", "c", "d"])
output = [n for n in range(10)]
np.array(output)
np.linspace(-5, 5, 15)
np.array([1.0, 1 + 1j, "hello"])  # array data is upcast to strings

a = np.linspace(-10, 10, 20)
print(a[a <= -5]) # conditional statements return another array of boolean values
```

- Matplotlib:

```python
plt.plot(x, np.sin(x), "^", ms=8, color="0.8")
plt.xlim([-1, 1])  # change bounds on x-axis to [-1,1]
plt.ylim([-0.75, 0.75])  # change bounds on y-axis to [-0.75,0.75]
plt.show()

plt.figure(figsize=(12, 3))
plt.subplot(1, 3, 1)
plt.plot(x, np.sin(x), lw=2)
plt.subplot(1, 3, 2)
plt.plot(x, np.sin(x), lw=2, color="#740007")
plt.xlim([-np.pi, np.pi])
plt.subplot(1, 3, 3)

plt.savefig(
    "axes_example.png"
)  # Save the figure in PNG format in same directory as script
```

## Lecture 0 - Introduction to QuTiP

```python
from qutip import (Qobj, about, basis, coherent, coherent_dm, create, destroy,
                   expect, fock, fock_dm, mesolve, qeye, sigmax, sigmay,
                   sigmaz, tensor, thermal_dm)
```

## Appendix 术语表和数学知识

| Eng | 中文 |
| - | - |
| Bra-ket(Dirac) notation | 狄拉克符号 |

- 狄拉克符号：
    - $\ket{v}$ 表示向量（量子系统的状态）
    - $\bra{f}$ 表示线性泛函
    - 任何一个态都可以写为基在复数空间上的线性组合 $\ket{\phi} = \alpha\ket0 + \beta e^{i\theta}\ket1$
    - 内积：$\braket{a|b} = \braket{b|a}^*$

> 在量子力学中使用狄拉克符号因为这些向量与一般的向量所在的空间有很大不同。一般的向量在普通的三维空间，而量子力学中的向量在更加抽象、复杂的希尔伯特空间，比如所有可能的波函数组成的无限维空间。

!!! note "回顾知识：线性映射"

    - 线性泛函：从向量空间到标量域的映射
    - 对偶空间 $V'=L(V, F)$：向量空间上所有线性泛函构成
    - 对偶基：一组线性泛函，将向量空间中的每个基分别映射到 $1$
    - 对偶映射：对 $T\in L(V,W)$，对偶映射是7. $T'\in L(W', V')$

- 复数

- 欧拉公式：$e^{ix} = \cos x + i\sin x$
    - 其实平常使用复指数我们都只关心展开后的实部，这可以看作简单表示三角函数。把指数上面除 $i$ 以外的部分套进 $\cos$ 函数即可。
    - 更进一步的理解是：$\cos$ 和 $\sin$ 是线性独立的，它们一起构成一个二维向量空间。

- 张量积 $\otime$ 两个向量空间形成一个更大的向量空间，用于生成复合系统。
    - 从线性代数角度来看，张量积是一种双线性运算。在线性代数中，外积就是张量积。
    - 张量积的秩是所需指标数，维数是两个空间维数相乘
    - 对于矩阵，通常称为克罗内科积
