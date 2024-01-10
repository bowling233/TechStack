# 离散数学

<!-- prettier-ignore-start -->
!!! abstract "课程信息"

    - 时间：2023-2024 学年 秋冬学期
    - 授课教师：金小刚
<!-- prettier-ignore-end -->

## 单词表

| 英文          | 中文 |
| ------------- | ---- |
| propositional | 命题 |
| predicate     | 谓词 |
| quantifier    | 量词 |
| cardinality   | 基数 |
| hypothesis    | 假设 |
| antecedent    | 前件 |
| premise       | 前提 |
| conclusion    | 结论 |
| consequence   | 结果 |

## 命题逻辑

### 简单逻辑运算符

| 算符     | 名称              | 有关的运算性质 |
| -------- | ----------------- | -------------- |
| $\neg$   | 非 negation       | 无             |
| $\wedge$ | 合取 conjunction  |                |
| $\vee$   | 析取 disjunction  |                |
| $\oplus$ | 异或 exclusive or |                |

-   从两个及以上命题构造新命题的逻辑运算符称为**联结词（connectives）**。

### 条件语句

| 算符              | 名称                                                   | 有关的运算性质 |
| ----------------- | ------------------------------------------------------ | -------------- |
| $\rightarrow$     | 条件语句 condition statement<br>蕴含 implication       |                |
| $\leftrightarrow$ | 双条件语句 biconditional statement<br>等价 equivalence |                |

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
-   基数 $|A|$，有限集、无限集
-   幂集 $\mathcal{P}(A)$
-   笛卡儿积 $A \times B = \{(a, b) \mid a \in A, b \in B\}$
    -   笛卡儿积的子集称为从 $A$ 到 $B$ 的**关系**。
-   运算：交、并、补、差

<!-- prettier-ignore-start -->
!!! warning "注意：$\emptyset$ 的幂集不是 $\{\emptyset\}$，而是 $\{\emptyset, \{\emptyset\}\}$。"
<!-- prettier-ignore-end -->

带量词的集合符号：

$$
\forall x \in S(P(x)) \equiv \forall x (x \in S \rightarrow P(x))
\forall x \in \mathbf{R}(x^2 \geq 0)
\exists x \in S(P(x)) \equiv \exists x (x \in S \wedge P(x))
\exists x \in \mathbf{Z}(x^2=1)
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
