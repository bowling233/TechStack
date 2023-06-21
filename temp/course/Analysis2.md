# 数学分析 II
## 数项级数
### 9.1 数项级数的收敛性 基本性质
* 定义：部分和数列的敛散性就是无穷级数的敛散性
* p 级数和几何级数是两种基本的级数
* 收敛**必要条件**：通项是无穷小量
	- 容易说明发散
- 线性性、括号随便添加
- 
### 9.2 上极限与下极限
### 9.3 正项级数 比较、Cauchy、d'Alembert、Raabe、积分判别法

<!-- prettier-ignore-start -->
!!! note "不要混肴项和部分和"
	
	在本章收敛定理证明和使用时，容易混肴对部分和还是数列项进行操作。做题时仔细。
<!-- prettier-ignore-end -->

- 正项级数收敛的充要条件可由**数列的单调收敛定理**直接得到。
- 比较判别法
	- 普通形式
	- 极限形式：$0$ 和 $+\infty$ 是特殊情况

<!-- prettier-ignore-start -->
!!! note "选择已知的数列进行比较"
	
	一般选择** p 级数**。

	- $p>1$ 收敛
	- $p\leq1$ 发散

	对于几种不同的函数作和差，可以使用麦克劳林公式（或泰勒公式）展开到指定幂次，再与** p 级数**进行比较。
<!-- prettier-ignore-end -->

- Cauchy 判别法
	- **平均公比**：$\sqrt[n]{x_n}$。
	- 通过平均公比的上极限与 $1$ 的大小关系进行判断，等于 $1$ 时无法使用。
	- 证明：转化为与** p 级数**的比较。
- d'Alembert 判别法
	- 看公比的上/下极限判断。
	- 上极限只能判断收敛，下极限只能判断发散，其他情况均失效。
	- 证明方法是将公比与平均公比上下极限进行比较。**适用范围更窄**。
- Raabe 判别法
	- 适用条件：前两个判别法失效时（$\lim_{n\to \infty}\frac{x_{n}}{x_{n+1}}=1$）。
	- 判据：$r=\lim_{n\to \infty}n(\frac{x_n}{x_{n+1}}-1)$，大于 $1$ 收敛，小于 $1$ 发散。
	- 然而这个判别法也会失效，还可以进一步建立 Bertrand 判别法，建立下去的过程是无限的，证明也更加复杂。
	- 

<!-- prettier-ignore-start -->
!!! note "双阶乘"
	
	$$
	k!!=\left\{\begin{matrix} 
    &k(k-2)(k-4)\cdots6\cdot4\cdot2,& k=&2n \\  
    &k(k-2)(k-4)\cdots5\cdot3\cdot1,& k=&2n+1 
    \end{matrix}\right. 
    $$

    记忆：隔项相乘，奇偶自定。
<!-- prettier-ignore-end -->


### 9.4 任意项级数 

<!-- prettier-ignore-start -->
!!! abstract "任意项级数的敛散性判别"
	
	- 最基础的是柯西收敛原理，但比较难用。
	1. 考虑是否绝对收敛，即加上绝对值后转化为正项级数的判别。
	2. 如果加绝对值发散，那么考虑级数本身是否收敛（条件收敛）。【与反常积分判别法相似】
	3. 有时考虑正/负部级数。
<!-- prettier-ignore-end -->

任意项级数研究其中每一项正负随意的无穷级数。最基本的还是 Cauchy 收敛定理：

<!-- prettier-ignore-start -->
??? note "级数的 Cauchy 收敛定理"
	
	无穷级数收敛的充分必要条件是：

	$$
	\forall \epsilon > 0, \exists N > 0, s.t. \forall m > n > N, |\sum^m_{k=n+1}x_k| < \epsilon
	$$

	另一种叙述是：

	$$
	\forall \epsilon > 0, \exists N > 0, s.t. \forall n > N, p > 0, |\sum^p_{k=1}x_{n+k}| < \epsilon
	$$
<!-- prettier-ignore-end -->

- Leibniz 级数

交错级数可以这样表述：$\sum^\infty_{n=1}x_n = \sum^\infty_{n=1}(-1)^{n+1}u_n$。

当 $\{u_n\}$ 单调减少收敛于 $0$ 时，该交错级数称为 Leibniz 级数，它一定收敛。

<!-- prettier-ignore-start -->
??? note "Leibniz 判别法的证明"
	
	可以使用柯西收敛定理，这里我们用定义证明，考虑部分和数列：

	- 部分和数列的偶数项，容易证明单调递增，接下来需要证明有界。有界同样容易证明，小于数列第一项。
	- 奇数项在偶数项的基础上证明，也容易。
<!-- prettier-ignore-end -->

接下来看一般级数。这里的判别方法和反常积分原理相似。

<!-- prettier-ignore-start -->
??? note "Dirichlet 判别法"
	
	$\sum^\infty_{n=1}a_n$ 的部分和数列有界，$\{b_n\}$ 单调趋于 $0$，则级数 $\sum^\infty_{n=1}a_nb_n$ 收敛。
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
??? note "Abel 判别法"
	
	$\sum^\infty_{n=1}a_n$ 收敛，$\{b_n\}$ 单调有界，则级数 $\sum^\infty_{n=1}a_nb_n$ 收敛。
<!-- prettier-ignore-end -->

事实上，Leibniz 判别法是 Dirichlet 判别法的特例，Dirichlet 判别法又是 Abel 判别法的特殊情况。你能分析一下它们之间的关系吗？



<!-- prettier-ignore-start -->
??? info "正/副部级数"
	
	正部级数：
	
	$$
	a_n^+=\left\{\begin{matrix} 
  	a_n, a_n > 0 \\  
  	0, a_n \leq 0
	\end{matrix}\right.
	$$

	负部级数：
	
	$$
	a_n^+=\left\{\begin{matrix} 
  	-a_n, a_n < 0 \\  
  	0, a_n \geq 0
	\end{matrix}\right.
	$$

	在第一节中我们知道，收敛的无穷级数可以进行加减法。我们可以尝试把 $\sum^\infty_{n=1}x_n$ 和 $\sum^\infty_{n=1}|x_n|$ 表达成正负部级数的和/差。当无穷级数绝对收敛时，正负部级数一定收敛。尝试用比较判别法说明。

	??? note "定理 4.1"
		
		设级数 $\sum^\infty_{n=1}x_n$ 绝对收敛，则

		- $\sum^\infty_{n=1}x_n^+, \sum^\infty_{n=1}x_n^-$ 收敛
		- $|\sum^\infty_{n=1}x_n|\leq|\sum^\infty_{n=1}|x_n|$

	如果级数条件收敛，你能讨论其正、副部级数的敛散性吗？
<!-- prettier-ignore-end -->

