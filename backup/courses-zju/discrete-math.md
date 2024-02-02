# 离散数学

<!-- prettier-ignore-start -->
!!! abstract "课程信息"

    - 时间：2023-2024 学年 秋冬学期
    - 授课教师：金小刚
<!-- prettier-ignore-end -->

## 逻辑与证明

| 英文        | 中文 |
| ----------- | ---- |
| proposition | 命题 |
| predicate   | 谓词 |
| quantifier  | 量词 |
| cardinality | 基数 |
| hypothesis  | 假设 |
| antecedent  | 前件 |
| premise     | 前提 |
| conclusion  | 结论 |
| consequence | 结果 |

### 逻辑

从上到下，优先级递减。

| 算符     | 名称              | 有关的运算性质 |
| -------- | ----------------- | -------------- |
| $\neg$   | 非 negation       | 无             |
| $\wedge$ | 合取 conjunction  |                |
| $\vee$   | 析取 disjunction  |                |
| $\oplus$ | 异或 exclusive or |                |
| $\rightarrow$     | 条件语句 condition statement<br>蕴含 implication       |                |
| $\leftrightarrow$ | 双条件语句 biconditional statement<br>等价 equivalence |     

-   从两个及以上命题构造新命题的逻辑运算符称为**联结词（connectives）**。
-   逻辑中的蕴含与因果没有关系。
-   逆命题、逆否命题、反命题
-   两个复合命题，不论变量的取值如何，真值总是相同，则称这两个复合命题**等价**。

### 优先级

$\neg$ > $\wedge$ > $\vee$ > $\rightarrow$ > $\leftrightarrow$

### 命题的等价与化简

| 公式                  | 名称                       | 化简                                      |
| --------------------- | -------------------------- | ----------------------------------------- |
| $p \wedge \neg p$     | 矛盾式 contradiction       | F                                         |
| $p \vee \neg p$       | 永真式 tautology           | T                                         |
| $p \rightarrow q$     | 蕴含式 implication         | $\neg p \vee q$                           |
| $p \leftrightarrow q$ | 等价式 equivalence         | $(p\wedge q) \vee (\neg p \wedge \neg q)$ |
| $\neg (p \wedge q)$   | 德摩根定律 De Morgan's law | $\neg p \vee \neg q$                      |
| $\neg (p \vee q)$     | 德摩根定律 De Morgan's law | $\neg p \wedge \neg q$                    |

-   $p \leftrightarrow q$ 永真，则称 $p$ 与 $q$ 等价，记 $p \equiv q$。注意：$\equiv$ 和 $\Leftrightarrow$ 不是逻辑联结词，而是代表这一语句。

## 基本结构：集合、函数、序列、求和与矩阵

|         Eng          |      中文       |
| :------------------: | :-------------: |
|    universal set     |      全集       |
| open/closed interval |    开/闭区间    |
|    singleton set     |    单元素集     |
|     Venn diagram     |     维恩图      |
|  **proper** subset   |   **真**子集    |
|     cardinality      |      基数       |
|      power set       |      幂集       |
|  Cartesian product   |    笛卡尔积     |
| ordered n-**tuple**  | 有序 n **元组** |
|      truth set       |     真值集      |

### 集合

简单内容一笔带过：

-   子集、韦恩图
-   运算：交、并、补、差

新内容：

-   对称差 symmetric difference：$A \oplus B = (A - B) \cup (B - A)$
    -   $A \oplus B = B \oplus A$
    -   $A \oplus A = \emptyset$
    -   $(A \oplus B) \oplus C = A \oplus (B \oplus C)$
-   幂集 power set：$\mathcal{P}(A)$ 或 $2^A$。
-   笛卡儿积 cartesian product：$A \times B = \{(a, b) \mid a \in A, b \in B\}$
    -   笛卡儿积的子集称为从 $A$ 到 $B$ 的**关系**。
-   基数 cardinality：$|A|$，有限集、无限集
    -   容斥原理 inclusion-exclusion principle：$|A \cup B| = |A| + |B| - |A \cap B|, |\cup^n_{i=1} A_i| = \sum^n_{i=1} |A_i| - \sum_{1 \leq i < j \leq n} |A_i \cap A_j| + \sum_{1 \leq i < j < k \leq n} |A_i \cap A_j \cap A_k| + \dots + (-1)^{n+1} |A_1 \cap A_2 \cap \dots \cap A_n|$
    -   集合基数相同称 equinumerous：如果两个集合之间存在双射，两个集合的基数相同。
        -   等价关系
        -   双射
        -   无限集的真子集与自身基数相同（充要条件）
-   无限集：
    -   可数无限集：和正整数集有相同基数 $\aleph_0$ 的集合。
        -   $Z$、$Q$、$N\times N$ 都是可数集。
    -   不可数 denumerable 无限集：不是可数集的集合。
    -   可数个可数集的并是可数集。

<!-- prettier-ignore-start -->
!!! note "集合基数有关的定理"

    -   幂集的基数大于原集合的基数：$|2^A| > |A|$
    -   实数集是不可数的：$|\mathbf{R}| = \aleph > \aleph_0$

    ??? example "尝试证明"

        -   $(0, 1)$ 不可数
        -   

!!! warning "注意：$\emptyset$ 的幂集不是 $\{\emptyset\}$，而是 $\{\emptyset, \{\emptyset\}\}$。"
<!-- prettier-ignore-end -->

带量词的集合符号：

$$
\begin{align}
\forall x \in S(P(x)) \equiv \forall x (x \in S \rightarrow P(x))\\
\forall x \in \mathbf{R}(x^2 \geq 0)\\
\exists x \in S(P(x)) \equiv \exists x (x \in S \wedge P(x))\\
\exists x \in \mathbf{Z}(x^2=1)\\
\end{align}
$$

真值集和量词：给定谓词 $P$ 和论域 $D$，真值集 $\{x \in D \mid P(x)\}$。

集合运算，其实可以转化为命题逻辑的运算：

$$
\begin{aligned}
\overline{A\cap B} &= \{x \mid x \notin A \cap B\} \\
&= \{x \mid \neg (x \in A \cap B)\} \\
&= \{x \mid \neg (x \in A \wedge x \in B)\} \\
&= \{x \mid \neg x \in A \vee \neg x \in B\} \\
&= \{x \mid x \notin A \vee x \notin B\} \\
&= \{x \mid x \notin A\} \cup \{x \mid x \notin B\} \\
&= \overline{A} \cup \overline{B}
\end{aligned}
$$

上面的方法可用于证明基础的集合恒等式。化简集合等式时，直接应用已知的恒等式即可。

### 集合的基数

-   衡量无限集的相对大小

<!-- prettier-ignore-start -->
!!! note "基数"

    当且仅当集合 $A$ 和 $B$ 之间存在双射时，称 $A$ 和 $B$ 的基数相同，记作 $|A|=|B|$。
!!! note "可数集与不可数集"

    - 可数集：和正整数集有相同基数 $\aleph_0$ 的集合

    如果能将集合中的元素排成序列，那么这个集合就是可数集。正有理数集是可数集，就是通过排列的方式证明的。

    - 不可数集：不是可数集的集合

    通常使用反证法证明不可数集。假定实数集是可数的，那么可以将实数集排成一个序列，然后构造一个不在这个序列中的实数（通过取数字的方法），从而得到矛盾。
<!-- prettier-ignore-end -->

-   两个可数集合的并集是可数集

根据集合是否有限，分三种情况证明即可。

-   Schroder-Bernstein 定理：如果 $|A| \leq |B|$ 且 $|B| \leq |A|$，则 $|A|=|B|$
    > 该证明较难：构造双射 $f:A \rightarrow B$ 和 $g:B \rightarrow A$，然后证明 $f \circ g$ 和 $g \circ f$ 都是恒等映射。

<!-- prettier-ignore-start -->
!!! example "证明 $|(0, 1)|=|(0, 1]|$"
<!-- prettier-ignore-end -->

-   不可计算性

    1. 任何编程语言编写的计算机程序的集合是**可数的**。
    2. 从一个特定的可数无限集到自身的函数有**不可数无限多个**。
    3. 结合上面两个结论，可得到：存在不可计算的函数。

-   连续统假设
    1. $|\mathbf{P}(\mathbf{Z^+})|=|\mathbf{R}|=c$

## 关系

-   关系：$n$ 元集合上有 $2^n^2$ 个二元关系。
    -   怎么数的？数笛卡尔积的幂集即可。笛卡尔积的基数为 $n^2$，幂集的基数为 $2^{n^2}$。
    -   关系也有定义域和值域。关系也可以像函数那样复合，可以有幂。关系也有逆。
    -   $n$ 元关系是 $n$ 元笛卡尔积的子集。
    -   Identity relation：$I_A = \{(a, a) \mid a \in A\}$，是 $A$ 上的恒等关系。
-   自反性：$\forall a \in A(aRa)$；非自反性：$\forall a \in A(\neg aRa)$
    -   例子：$\leq$
    -   $n$ 元集合上有 $2^{n(n-1)}$ 个自反关系：共计 $n^2$ 个关系中，有 $n$ 个关系确定，接下来的 $n^2-n$ 个可以属于该关系或不属于该关系。
    -   显然，$R_= \subseteq R$。
-   对称性：$\forall a, b \in A(aRb \rightarrow bRa)$；反对称性：$\forall a, b \in A(aRb \wedge bRa \rightarrow a=b)$
    -   例子：$=$
    -   反对称性有：$R\cap R^{-1} \subseteq R_=$
-   传递性：$\forall a, b, c \in A(aRb \wedge bRc \rightarrow aRc)$；非传递性：$\forall a, b, c \in A(aRb \wedge bRc \rightarrow \neg aRc)$
    -   例子：$\leq$
    -   充要条件：$R^n \subseteq R$。
    -   


## 图

| Eng            | 中文                      |
| -------------- | ------------------------- |
| pseuodgraph    | 伪图                      |
| pendant vertex | 悬挂顶点 $\mathrm{deg}=1$ |
| incident with  | 关联                      |
| bipatite graph | 二分图                    |

-   分类：simple、multi、pseudo、directed、directed multi。考虑边、平行边、环。
-   基本概念：
    -   度
        -   无向图-握手定理：$\sum_{v \in V} \mathrm{deg}(v) = 2|E|$，因为每条边都会贡献两个顶点的度。
        -   有向图：$\sum_{v \in V} \mathrm{deg^+}(v) = \sum_{v \in V} \mathrm{deg^-}(v) = |E|$
-   特别的图：
    -   完全图 $K_n$：$n$ 个顶点的无向图，每两个顶点之间都有边。$|E|=C_n^2=\frac{n(n-1)}{2}$
    -   环 $C_n$
    -   轮 $W_n$：在环的基础上添加一个顶点。
    -   $n$ 立方体图 $Q_n$
    -   二分图：$V=V_1 \cup V_2$，$E$ 中的每条边都连接 $V_1$ 和 $V_2$ 中的两个顶点。
        -   举例：$C_6$ 是二分图，$K_3$ 不是二分图。
    -   完全二分图 $K_{m,n}$：$V=V_1 \cup V_2$，$E$ 中的每条边都连接 $V_1$ 和 $V_2$ 中的两个顶点。每个 $V_i$ 中的顶点都与另一个 $V_j$ 中的顶点相连。
        -   举例：$K_{3,3}$ 是完全二分图，$K_3$ 不是完全二分图。
-   图的变化：
    -   子图
    -   span 子图
    -   并
-   图的表示：
    -   邻接矩阵（adjacency matrix）：可表示简单图。若元素定义为关联的边数时，可以表示伪图。若非对称，可以表示有向图。
    -   关联矩阵（incidentce matrix）：行为顶点，列为边。每列有两个 $1$，表示该边关联的两个顶点。

<!-- prettier-ignore-start -->
!!! note "连通性 connectivity"

    $$
    \begin{align}
    A^r
    \end{align}
    $$
<!-- prettier-ignore-end -->

-   连通性：
    -   路径：一系列边 $e_1, e_2, \dots$。
    -   无向图的连通性、连通分量。
    -   割点（cut vertex）：删除该顶点后，图不再连通。割边（cut edge）类似。
    -   有向图的强连通性、强连通分量。
    -   邻接矩阵的幂：$A^k$ 中的元素 $a_{ij}$ 表示从 $v_i$ 到 $v_j$ 的长度为 $k$ 的路径数。

<!-- prettier-ignore-start -->
!!! note "图同构 isomorphic"
<!-- prettier-ignore-end -->

-   图同构（isomorphic）：通俗的理解就是，两个图的顶点和边可以一一对应。
    -   简单图：存在双射 $f:V_1 \rightarrow V_2$，使得 $u$ 和 $v$ 相邻当且仅当 $f(u)$ 和 $f(v)$ 相邻。
    -   图形不变量：这些量在图同构时保持不变。因此可以用图形不变量来证明两个图不同构（但不能证明同构）。
    -   证明图同构：找到指定的双射即可。但这样的双射有 $n!$ 个（顶点之间的映射关系）。
    -   证明图不同构：常用以下图形不变量：
        -   具有某长度的环。如果另一个图中找不到这么长的环，那么两个图不同构。

<!-- prettier-ignore-start -->
!!! note "欧拉回路和哈密顿路径 Eulerian and Hamiltonian"

    $$
    \begin{align}
    \mathrm{deg}(v_k) \text{is even}\\
    n\geq 3, \mathrm{deg}(u) + \mathrm{deg}(v) \geq n \text{ for all } u, v \in V\\
    \end{align}
    $$
<!-- prettier-ignore-end -->

-   欧拉回路和哈密顿路径：
    -   欧拉路径：经过每条边一次且仅一次的路径。
    -   欧拉回路：经过每条边一次且仅一次的回路。
    -   欧拉回路充要条件：图连通且所有顶点的度都是偶数（even）。
    -   哈密顿路径：经过每个顶点一次且仅一次的路径。
    -   哈密顿回路：经过每个顶点一次且仅一次的回路。
    -   哈密顿回路存在性：
        -   Dirac 定理：如果 $n \geq 3$ 且每个顶点的度都大于等于 $n/2$，则图存在哈密顿回路。
        -   Ore 定理：如果 $n \geq 3$ 且对于所有不相邻的顶点 $u$ 和 $v$，$\mathrm{deg}(u) + \mathrm{deg}(v) \geq n$，则图存在哈密顿回路。

<!-- prettier-ignore-start -->
!!! note "Dijkstra 算法"
<!-- prettier-ignore-end -->

-   最短路径问题：
    -   Dijkstra 算法

<!-- prettier-ignore-start -->
!!! note "平面图 planar graph"

    $$
    \begin{align}
    v-e+r=2\\
    e \leq 3v-6\\
    e \leq 2v-4\\
    K_5, K_{3,3}
    \end{align}
    $$
<!-- prettier-ignore-end -->

-   Planar 图：可以画在平面上的图。
    -   Euler 公式：$v-e+r=2$，其中 $v$ 为顶点数，$e$ 为边数，$r$ 为面数。
    -   如果 $G$ 是一个简单连通平面图，且 $v \geq 3$，则 $e \leq 3v-6$。
        -   区域的度：区域的边数。一个平面图把平面分成 $r$ 个区域。
        -   每个区域的度至少为 $3$，无限区域的度至少是$3$，因为一个图至少有 $3$ 个顶点。
        -   综上，$2e \geq 3r$。利用 Euler 公式，可得 $e \leq 3v-6$。
        -   用这个结论证明：$K_5$ 不是平面图。
    -   如果 $G$ 是一个简单连通平面图且不含有三角形，则 $e \leq 2v-4$。
        -   用这个结论证明：$K_{3,3}$ 不是平面图。
    -   检验 $G$ 是否是平面图：
        -   初等细分：将边分成两条边。
        -   同胚（homeomorphic）：可以从相同的图通过初等细分得到的图。
        -   Kuratowski 定理：$G$ 是非平面图当且仅当 $G$ 含有 $K_5$ 或 $K_{3,3}$ 的同胚子图。

<!-- prettier-ignore-start -->
!!! note "图着色 coloring"

    $$
    \begin{align}
    \chi(K_n) = n\\
    \chi(K_{m,n}) = 2\\
    \chi(C_n) = 2 \text{ if } n \text{ is even}\\
    \chi(C_n) = 3 \text{ if } n \text{ is odd}
    \end{align}
    $$
<!-- prettier-ignore-end -->

-   图着色：
    -   对偶图 dual：将平面图的每个区域看作顶点，如果两个区域有公共边，则在对偶图中连接这两个顶点。
    -   问题：给对偶图着色，使得相邻的顶点着不同的颜色。最少色数为 $\chi(G)$。
    -   四色定理：平面图着色数最多为 $4$。

## 树
