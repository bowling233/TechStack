# 离散数学

<!-- prettier-ignore-start -->
!!! abstract "课程信息"

    - 时间：2023-2024 学年 秋冬学期
    - 授课教师：金小刚
<!-- prettier-ignore-end -->

## 单词表

| 英文 | 中文 |
| ---- | ---- |
| propositional | 命题 |
| predicate | 谓词 |
| quantifier | 量词 |
| cardinality | 基数 |
| hypothesis | 假设 |
| antecedent | 前件 |
| premise | 前提 |
| conclusion | 结论 |
| consequence | 结果 |

## 命题逻辑

### 简单逻辑运算符

| 算符 | 名称 | 有关的运算性质 |
| ---- | ---- | -------------- |
| $\neg$ | 非 negation | 无 |
| $\wedge$ | 合取 conjunction | |
| $\vee$ | 析取 disjunction | |
| $\oplus$ | 异或 exclusive or | |

- 从两个及以上命题构造新命题的逻辑运算符称为**联结词（connectives）**。

### 条件语句

| 算符 | 名称 | 有关的运算性质 |
| ---- | ---- | -------------- |
| $\rightarrow$ | 条件语句 condition statement<br>蕴含 implication | |
| $\leftrightarrow$ | 双条件语句 biconditional statement<br>等价 equivalence | |

- 逆命题、逆否命题、反命题
- 两个复合命题，不论变量的取值如何，真值总是相同，则称这两个复合命题**等价**。


### 优先级

$\neg$ > $\wedge$ > $\vee$ > $\rightarrow$ > $\leftrightarrow$

### 命题的等价与化简

| 公式 | 名称 | 化简 |
| ---- | ---- | ---- |
| $p \wedge \neg p$ | 矛盾式 contradiction | F |
| $p \vee \neg p$ | 永真式 tautology | T |
| $p \rightarrow q$ | 蕴含式 implication | $\neg p \vee q$ |
| $p \leftrightarrow q$ | 等价式 equivalence | $(p\wedge q) \vee (\neg p \wedge \neg q)$ |
| $\neg (p \wedge q)$ | 德摩根定律 De Morgan's law | $\neg p \vee \neg q$ |
| $\neg (p \vee q)$ | 德摩根定律 De Morgan's law | $\neg p \wedge \neg q$ |



- $p \leftrightarrow q$ 永真，则称 $p$ 与 $q$ 等价，记 $p \equiv q$。注意：$\equiv$ 和 $\Leftrightarrow$ 不是逻辑联结词，而是代表这一语句。







