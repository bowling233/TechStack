# Practical Foundations for Programming Languages, Second Edition

本篇笔记大部分都是原书的翻译。仅引用块和 abstract 块是我自己的笔记内容。

## 第一部分：判断和规则

### 第一章：抽象语法

> 抽象语法（abstract syntax）也称为结构语法（structural syntax），考虑词组（phrase）的结构，它们如何有别的词组组成。在这一层次，词组是一棵树，节点是将多个词组组合在一起的操作符（operator）。
>
> 语法的绑定（binding）结构引入了标识符（identifier），考虑它们如何声明和使用。在这一层次，词组视为抽象绑定树（abstract binding tree）。
>
> 本节分两部分：
>
> - 定义抽象语法树
> - 介绍标识符绑定和作用域（scope）的规则
>
> 接下来将会在 ABT 上精确定义一些函数和关系，来阐明绑定和作用域的精确含义。这两个概念难以正确定义，通常是语言实现者产生错误的地方。

#### 抽象语法树

!!! abstract "本节概览"

    - 定义：
        - 类型 $s$、类型集合 $S$、运算符 $o$、运算符集族 $O$、变量 $x$、变量集 $X$、变量集族 $X_s$
        - 抽象语法树 $a$、抽象语法树家族 $A[X]$
        - 添加类型 $X, x$
        - 替换 $[b/x]a$
    - 应用：
        - 结构归纳法
    - 定理：
        - 替换的良定义

!!! note "定义：抽象语法树、变量、操作符、类型、元数"

    抽象语法树（简称 AST）是一种有序树，其叶节点为**变量（variables）**，内部节点为**操作符（operators）**，操作符的**参数（arguments)**为其子节点。AST 可以分为不同的**类型（sort）**，每种类型对应不同的语法形式。变量表示指定类型中未确定或通用的语法片段。AST 可以通过操作符组合起来，操作符的**元数（arity）**指定了操作符的类型以及其参数的**数量和类型**。一个类型为 \( s \) 且元数为 \( s_1, \dots, s_n \) 的操作符可以将 \( n \geq 0 \) 个分别属于 \( s_1, \dots, s_n \) 类型的 AST 组合成一个属于 \( s \) 类型的复合 AST。

变量的概念至关重要，因此值得特别强调。变量是从某一定义域（domain）中抽象出的**未知**对象。通过将特定对象**替换（substitution）**变量在公式中出现的所有位置，这个未知对象可以被具体化，从而将通用公式特化为具体实例。例如，在代数中，变量代表实数，我们可以形成多项式，比如 \( x^2 + 2x + 1 \)，并通过用 $7$ 替换 \( x \) 来将其特化为 \( 7^2 + (2 \times 7) + 1 \)，根据算术法则化简得到 \( 64 \)，即 \( (7 + 1)^2 \)。

抽象语法树按**类型（sort）**分类，以便将 AST 划分为语法类别。例如，常见的编程语言在表达式和命令之间具有语法上的区分，这就是抽象语法树的两种**类型（sort）**。在抽象语法树中，变量的取值范围在类型之中，即仅具有该变量指定类型的 AST 才可以替换该变量。因此，用命令替换表达式变量或用表达式替换命令变量是没有意义的，因为它们属于不同的类型。但这一核心思想与数学代数的概念类似，即**变量是未知数或占位符，其含义通过替换来赋予**。

!!! example

    例如，考虑一个由数字、加法和乘法组成的算术表达式语言。该语言的抽象语法仅由一个类型 $\mathsf{Exp}$ 组成，并由以下操作符生成：

    1. 类型为 $\mathsf{Exp}$ 的操作符 $\mathtt{num}[n]$，其中 \( n \in \mathbb{N} \)。
    2. 两个类型为 $\mathsf{Exp}$ 的操作符 $\mathtt{plus}$ 和 $\mathtt{times}$，每个操作符有两个类型为 $\mathsf{Exp}$ 的参数。

    表达式 \( 2 + (3 \times x) \)，其中包含变量 \( x \)，可以表示为 AST

    $$
    \mathtt{plus}(\mathtt{num}[2]; \mathtt{times}(\mathtt{num}[3]; x))
    $$

    类型为 $\mathsf{Exp}$（假设 \( x \) 也为该类型）。因为 $\mathtt{num}[4]$ 是一个 $\mathsf{Exp}$ 类型的 AST，我们可以将它替换到上述 AST 中的 $x$ 位置，从而得到

    $$
    \mathtt{plus}(\mathtt{num}[2]; \mathtt{times}(\mathtt{num}[3]; \mathtt{num}[4]))
    $$

    非正式地记作 $2 + (3 \times 4)$。当然，我们还可以将更复杂的 $\mathsf{Exp}$ 类型 AST 插入到 $x$ 中，从而生成新的 AST。

AST 的树形结构提供了一种非常有用的推理方法，称为**结构归纳（structural induction）**。假设我们希望证明某个性质 \( \mathcal{P}(a) \) 对所有指定类型的 AST \( a \) 都成立，只需考虑生成 \( a \) 的所有方式，并在假设其组成 AST（若有）满足该性质的前提下证明该性质对每种情况都成立。

!!! example

    对于前述的 Exp 类型，我们需要证明以下几点：

    1. 该性质对任何 $\mathsf{Exp}$ 类型的变量 \( x \) 都成立：证明 \( \mathcal{P}(x) \)。
    2. 该性质对任何数字 $\mathtt{num}[n]$ 都成立：对每个 \( n \in \mathbb{N} \)，证明 \( \mathcal{P}(\mathtt{num}[n]) \)。
    3. 在假设该性质对 \( a_1 \) 和 \( a_2 \) 成立的前提下，证明其对 $\mathtt{plus}(a_1; a_2)$ 和 $\mathtt{times}(a_1; a_2)$ 成立：若 $\mathcal{P}(a_1)$ 和 $\mathcal{P}(a_2)$ 成立，则 $\mathcal{P}(\mathtt{plus}(a_1; a_2))$ 和 $\mathcal{P}(\mathtt{times}(a_1; a_2))$ 也成立。

    因为这些情况穷尽了 \( a \) 的所有可能构造方式，因此可以确保 \( \mathcal{P}(a) \) 对任何 $\mathsf{Exp}$ 类型的 AST \( a \) 都成立。

通常情况下，应用结构归纳原理时，会考虑将变量解释为合适类型的抽象语法树 (AST) 的占位符。非正式地讲，在证明涉及变量的 AST 性质时，通常有用的是以变量满足某种性质为前提，来证明 AST 的某个性质。这样做的目的是预期这些变量将被具有该性质的 AST 替换，从而替换后的结果也会保持该性质。这相当于将结构归纳原理应用于某种形式的性质 $\mathcal{P}(a)$，即“如果 $a$ 包含变量 $x_1, \dots, x_k$，并且每个 $x_i$ 都满足 $\mathcal{Q}$，那么 $a$ 也满足 $\mathcal{Q}$”。因此，通过结构归纳证明所有 AST $a$ 的 $\mathcal{P}(a)$，实际上就是在假设 $\mathcal{Q}$ 对这些变量成立的情况下，证明 $\mathcal{Q}(a)$ 对所有 AST $a$ 都成立。当没有变量时，不存在任何假设，证明 $\mathcal{P}$ 就是证明 $\mathcal{Q}$ 对所有封闭的 AST 都成立。另一方面，如果 $a$ 中的变量 $x$ 被满足性质 $\mathcal{Q}$ 的 AST $b$ 替换，那么在 $a$ 中将 $x$ 替换为 $b$ 的结果也将满足性质 $\mathcal{Q}$。

!!! note "定义：元数"

    为了精确起见，我们现在给出这些概念的准确定义。设 $\mathcal{S}$ 为一个有限的类型集合。对于给定的类型集合 $\mathcal{S}$，一个算子的**元数（arity）**形式为 $(s_1, \dots, s_n)s$，表示该算子取 $n \geq 0$ 个参数，每个参数的类型为 $s_i \in \mathcal{S}$，且算子的类型为 $s \in \mathcal{S}$。令 $\mathcal{O} = \{ \mathcal{O}_\alpha \}$ 为一组按元数 $\alpha$ 索引的不交算子集 $\mathcal{O}_\alpha$，其中每个算子具有元数 $\alpha$。如果 $o$ 是元数为 $(s_1, \dots, s_n)s$ 的算子，我们称 $o$ 的类型为 $s$，且它有 $n$ 个参数，其类型分别为 $s_1, \dots, s_n$。

固定一个类型集合 $\mathcal{S}$ 和一个按元数索引的运算符集族 $\mathcal{O}$，每个运算符集对应不同的元数。令 $\mathcal{X} = \{ \mathcal{X}_s \}_{s \in \mathcal{S}}$ 为按类型索引的变量集族，每个变量集 $\mathcal{X}_s$ 是一个属于类型 $s$ 的不相交有限变量集。当上下文清楚时，如果 $x \in \mathcal{X}_s$，我们称变量 $x$ 属于类型 $s$。如果 $\forall s, x \notin \mathcal{X}_s$（对任何类型 $s$ 都不在其变量集中），我们就说 $x$ 对于 $\mathcal{X}$ 是“新鲜”的，或者直接称 $x$ 为“新鲜”的。如果 $x$ 对于 $\mathcal{X}$ 是新鲜的且 $s$ 是一个类型，那么 $\mathcal{X}, x$ 表示通过将 $x$ 添加到 $\mathcal{X}_s$ 中得到的变量集族。该符号具有一定的歧义性，因为类型 $s$ 没有明确给出，而是从上下文中确定的。

!!! note "定义：抽象语法树"

    抽象语法树（AST）家族 $\mathcal{A}[\mathcal{X}] = \{ \mathcal{A}[\mathcal{X}]_s \}_{s \in S}$ 是满足以下条件的最小集合：

    1. 属于类型 $s$ 的变量是类型 $s$ 的抽象语法树：如果 $x \in \mathcal{X}_s$，则 $x \in \mathcal{A}[\mathcal{X}]_s$。
    2. 运算符将抽象语法树组合起来：如果 $o$ 是一个元数为 $(s_1, \dots, s_n)s$ 的运算符，并且 $a_1 \in \mathcal{A}[\mathcal{X}]_{s_1}, \dots, a_n \in \mathcal{A}[\mathcal{X}]_{s_n}$，则 $o(a_1; \dots; a_n) \in \mathcal{A}[\mathcal{X}]_s$。

根据这个定义，可以应用结构归纳原理来证明某个性质 $\mathcal{P}$ 对每个抽象语法树都成立。要证明 $\mathcal{P}(a)$ 对所有 $a \in \mathcal{A}[\mathcal{X}]$ 成立，只需证明：

!!! note "方法：结构归纳法"

    1. 如果 $x \in \mathcal{X}_s$，则 $\mathcal{P}_s(x)$ 成立。
    2. 如果 $o$ 的元数为 $(s_1, \dots, s_n)s$，且 $\mathcal{P}_{s_1}(a_1)$、$\dots$、$\mathcal{P}_{s_n}(a_n)$ 成立，则 $\mathcal{P}_s(o(a_1; \dots; a_n))$ 成立。

!!! example "例如，通过结构归纳法很容易证明，当 $\mathcal{X} \subseteq \mathcal{Y}$ 时，$\mathcal{A}[\mathcal{X}] \subseteq \mathcal{A}[\mathcal{Y}]$。"

> 让我们尝试证明：
>
> 1. $\forall a \in \mathcal{A}[\mathcal{X}]_s$，有 $a \in \mathcal{A}[\mathcal{Y}]_s$。
> 2. 如果 $o$ 的元数为 $(s_1, \dots, s_n)s$，且 $a_1 \in \mathcal{A}[\mathcal{X}]_{s_1}, \dots, a_n \in \mathcal{A}[\mathcal{X}]_{s_n}$，则 $o(a_1; \dots; a_n) \in \mathcal{A}[\mathcal{X}]_s$，因此 $o(a_1; \dots; a_n) \in \mathcal{A}[\mathcal{Y}]_s$。

!!! note "定义：抽象语法树中的替换"

    变量的意义通过替换来赋予。如果 $a \in \mathcal{A}[\mathcal{X}, x]_{s'}$，且 $b \in \mathcal{A}[\mathcal{X}]_s$，则 $[b/x]a \in \mathcal{A}[\mathcal{X}]_{s'}$ 表示将 $b$ 替换 $a$ 中每个出现的 $x$ 的结果。此时，抽象语法树 $a$ 被称为替换的目标，$x$ 被称为替换的对象。替换由以下方程定义：

    1. $[b/x]x = b$ 且 $[b/x]y = y$（如果 $x \neq y$）。
    2. $[b/x]o(a_1; \dots; a_n) = o([b/x]a_1; \dots; [b/x]a_n)$。

> 注意，根据这一定义，$b$ 中不能有 $x$，因为 $x$ 对 $\mathcal{X}$ 是新鲜的。

!!! example "例如，我们可以验证：$[\mathtt{num}[2]/x]\mathtt{plus}(x; \mathtt{num}[3]) = \mathtt{plus}(\mathtt{num}[2]; \mathtt{num}[3])$"

我们可以通过结构归纳法证明抽象语法树上的替换是良定义的。

!!! note "定理 1.1：抽象语法树中的定义是好的"

    **定理**：如果 $a \in \mathcal{A}[\mathcal{X}, x]$，那么对于每个 $b \in \mathcal{A}[\mathcal{X}]$，存在唯一的 $c \in \mathcal{A}[\mathcal{X}]$，使得 $[b/x]a = c$。

    ---

    **证明**：通过对 $a$ 进行结构归纳。如果 $a = x$，则根据定义 $c = b$；如果 $a = y \neq x$，则根据定义 $c = y$。否则，$a = o(a_1, \dots, a_n)$，根据归纳假设，存在唯一的 $c_1, \dots, c_n$，使得 $[b/x]a_1 = c_1$ 以及 $[b/x]a_n = c_n$。因此，根据替换的定义，$c$ 为 $c = o(c_1; \dots; c_n)$。

> 什么是良定义（well-defined）？在数学中，一个定义是良定义的，意味着它是**唯一的、明确的、无歧义的**。在这个定理中，我们证明了对于每个抽象语法树 $a$ 和每个替换对象 $b$，替换 $[b/x]a$ 是唯一的。

#### 抽象绑定树

!!! abstract

    - 定义：
        - 绑定 $\mathtt{let}(a_1; x.a_2)$

抽象绑定树（ABT）是在抽象语法树（AST）的基础上进行扩展的，用来引入新的变量和符号，这种引入称为**绑定（binding）**，并具有一个特定的作用范围，称为其**作用域（scope）**。绑定的作用域是一个 ABT，在该范围内被绑定的标识符可以被使用，要么作为占位符（在变量声明的情况下），要么作为某个运算符的索引（在符号声明的情况下）。因此，在 ABT 的某个子树中，活动标识符的集合可能比其外部树中的更大。此外，不同的子树可能引入具有不相交作用域的标识符。关键原则是，标识符的任何使用都应被理解为对其绑定的引用或抽象指针。由此产生的一个结果是，标识符的选择并不重要，只要我们始终可以将每次标识符的使用唯一地关联到其绑定即可。

!!! example "作为一个激励性的例子，考虑表达式 $\texttt{ let } x \texttt{ be } 7 \texttt{ in } x + x$。这个表达式引入了一个变量 $x$，该变量在表达式 $x + x$ 中表示 $7$。变量 $x$ 由 $\texttt{ let }$ 表达式绑定，仅在 $x + x$ 内部使用；任何在 $7$ 中对 $x$ 的使用都指代一个不同的变量，即使它恰好具有相同的名称。另一方面，表达式 $\texttt{ let } x \texttt{ be } x \times x \texttt{ in } x + x$ 中，乘法中的 $x$ 指代的是 $\texttt{ let }$ 引入的绑定，而加法中的 $x$ 指代的是某个外部绑定（这里未展示）。"

> 通过上面这个例子，我们能够清晰地理解前文的抽象概念。例中绑定的作用域是 $x + x$，它是一个 ABT。作用于中被绑定的标识符是 $x$。对 $x$ 的任何使用，都应当理解为对 $7$ 的引用或抽象指针。标识符用 $x$ 还是 $y$ 并不重要，只要我们能够唯一地将其引用与其绑定关联起来。

**（被）绑定变量（bound variable）**的名称并不重要，只要它们指向相同的绑定。

!!! example "例如，表达式 $\texttt{ let } x \texttt{ be } x \times x \texttt{ in } x + x$ 也可以写作 $\texttt{ let } y \texttt{ be } x \times x \texttt{ in } y + y$，而不会改变其含义。在前一种情况下，加法中的变量 $x$ 被绑定，而在后一种情况下，被绑定的是变量 $y$，但“指针结构”保持不变。另一方面，表达式 $\texttt{ let } x \texttt{ be } y \times y \texttt{ in } x + x$ 与前两者的含义不同，因为乘法中的变量 $y$ 此时指向的是一个不同的外部变量。"

**重命名（renaming）**被绑定变量的限制在于，它不能改变表达式的引用结构。

!!! example "例如，表达式 $\texttt{ let } x \texttt{ be } 2 \texttt{ in } \texttt{ let } y \texttt{ be } 3 \texttt{ in } x + x$ 与表达式 $\texttt{ let } y \texttt{ be } 2 \texttt{ in } \texttt{ let } y \texttt{ be } 3 \texttt{ in } y + y$ 含义不同，因为在第二个表达式中，加法中的 $y + y$ 引用了内部的声明，而不像第一个表达式那样引用外部的声明。"

抽象语法树（AST）的概念可以通过引入变量的绑定和作用域来进行扩展。这些扩展后的 AST 称为抽象绑定树（ABT）。ABT 允许一个运算符在每个参数中绑定任意数量（可能为零）的变量，从而扩展了 AST 的概念。

!!! note "定义：抽象器"

    运算符的一个参数称为**抽象器**，其形式为 $x_1, \dots, x_k .a$。其中，变量序列 $x_1, \dots, x_k$ 在 ABT $a$ 中被绑定。（当 $k$ 为零时，我们省略抽象器中的点，直接写作 $a$）。

以 ABT 的形式书写，表达式 $\texttt{ let } x \texttt{ be } a_1 \texttt{ in } a_2$ 的形式是 $\texttt{ let }(a_1; x.a_2)$，这更清楚地指定了变量 $x$ 是在 $a_2$ 中绑定的，而不是在 $a_1$ 中。我们常用 $\vec{x}$ 来表示一个有限的、不同的变量序列 $x_1, \dots, x_n$，并用 $\vec{x}.a$ 表示 $x_1, \dots, x_n .a$。

!!! note "定义：广义元数、价位"

    为了处理绑定，运算符被赋予形式为 $(\nu_1, \dots, \nu_n)s$ 的**广义元数（generalized arities）**，这表示类型为 $s$ 的运算符具有 $n$ 个参数，每个参数的**价位（valence）**分别为 $\nu_1, \dots, \nu_n$。通常，价位 $\nu$ 具有形式 $s_1, \dots, s_k .s$，这指定了一个参数的类型以及在该参数中绑定的变量的数量和类型。

> 广义元数描述 ABT 中的运算符，价位描述它的参数，即抽象器。
>
> 对比 AST 中的元数：$(s_1, \dots, s_n)s$，描述了运算符的类型以及参数的数量和类型。因为 AST 中的参数简单，不需要多一层价位的描述。

我们说变量序列 $\vec{x}$ 的类型为 $\vec{s}$，意味着这两个序列的长度 $k$ 相同，并且对于每个 $1 \leq i \leq k$，变量 $x_i$ 的类型为 $s_i$。

!!! example

    因此，指定运算符 $\texttt{let}$ 的元数为 $(\mathsf{Exp}, \mathsf{Exp}.\mathsf{Exp})\mathsf{Exp}$ 表示它是一个类型为 $\mathsf{Exp}$ 的运算符，其第一个参数的类型为 $\mathsf{Exp}$，并且不绑定任何变量；第二个参数也是 $\mathsf{Exp}$ 的类型，并在其中绑定一个 $\mathsf{Exp}$ 类型的变量。非正式表达式 $\texttt{let } x \texttt{ be } 2 \texttt{ in } x + x$ 可以写作 ABT 形式 $\texttt{let}(\texttt{num}[2]; x.\texttt{plus}(x; x))$。其中运算符 $\texttt{let}$ 具有两个参数，第一个是表达式，第二个是一个抽象器，它绑定了一个表达式变量。

固定一个类型集合 $\mathcal{S}$ 和一个按广义元数索引的互不相交的运算符集族 $\mathcal{O}$。对于给定的互不相交的变量集族 $\mathcal{X}$，抽象绑定树（ABT）家族 $\mathcal{B}[\mathcal{X}]$ 的定义类似于 $\mathcal{A}[\mathcal{X}]$，但不同的是，$\mathcal{X}$ 在定义过程中不是固定不变的，而是随着进入抽象器的作用域而变化。

这个简单的概念在精确定义上意外地困难。对其定义的初步尝试是作为满足以下条件的最小集合族：

!!! note "定义：抽象绑定树（初步尝试）"

    1. 如果 $x \in \mathcal{X}_s$，则 $x \in \mathcal{B}[\mathcal{X}]_s$。
    2. 对于每个元数为 $(\vec{s_1}.s_1, \dots, \vec{s_n}.s_n)s$ 的运算符 $o$，如果 $a_1 \in \mathcal{B}[\mathcal{X}, \vec{x_1}]_{s_1}, \dots, a_n \in \mathcal{B}[\mathcal{X}, \vec{x_n}]_{s_n}$，则 $o(\vec{x_1}.a_1; \dots; \vec{x_n}.a_n) \in \mathcal{B}[\mathcal{X}]_s$。

绑定变量被附加到每个参数的活动变量集合中，每个变量的类型由运算符的价位决定。

这个定义几乎是正确的，但未能正确处理绑定变量的重命名。按照这个定义，形如 $\texttt{let } x \texttt{ be } 2 \texttt{ in } \texttt{let } x \texttt{ be } 3 \texttt{ in } x + x$ 的 ABT 是合法的，因为第一个 $\texttt{let}$ 绑定的 $x$ 与第二个 $\texttt{let}$ 绑定的 $x$ 是不同的。但是，这个 ABT 的意义是不明确的，因为两个绑定变量具有相同的名称，这可能会导致混淆。为了避免这种混淆，我们需要确保每个参数都是合法的，无论绑定变量名称的选择如何。这通过使用新的重命名来实现，新的重命名是变量序列之间的双射。

!!! note "定义：新重命名（fresh renaming）"

    具体来说，相对于 $\mathcal{X}$ 的一个有限变量序列 $\vec{x}$ 的新的**重命名**是一个双射 $\rho : \vec{x} \leftrightarrow \vec{x'}$，其中 $\vec{x'}$ 对 $\mathcal{X}$ 是新的。我们用 $\hat{\rho}(a)$ 表示将 $a$ 中每个 $x_i$ 替换为其新的对应变量 $\rho(x_i)$ 的结果。

> 让我们举一个具体的例子：
>
> $\rho: x \leftrightarrow y$，$\hat{\rho}(x + x) = y + y$。

这通过使用新的重命名来修改 ABT 定义的第二条规则实现，如下所示：

!!! note "定义：抽象绑定树"

    对于每个元数为 $(\vec{s_1}.s_1, \dots, \vec{s_n}.s_n)s$ 的运算符 $o$，如果对于每个 $1 \leq i \leq n$ 和每个新的重命名 $\rho_i : \vec{x_i} \leftrightarrow \vec{x'_i}$，我们有 $\hat{\rho_i}(a_i) \in \mathcal{B}[X, \vec{x'_i}]$，则 $o(\vec{x_1}.a_1; \dots; \vec{x_n}.a_n) \in \mathcal{B}[X]_s$。

重命名 $\hat{\rho_i}(a_i)$ 确保了不会发生冲突，并且 ABT 对几乎所有的绑定变量的重命名都是有效的。

> 这个定义确保了 ABT 的定义良好，不会出现歧义。再次总结 ABT 的定义：
>
> 1. 变量是 ABT。
> 2. 对运算符的抽象器中的被绑定变量进行**新重命名**，仍然是 ABT。即无歧义。

结构归纳原理可以扩展到抽象绑定树（ABT），这种扩展称为“结构归纳**模**新重命名”。它表明，为了证明 $\mathcal{P}[\mathcal{X}](a)$ 对于每个 $a \in \mathcal{B}[\mathcal{X}]$ 都成立，只需证明以下条件即可：

1. 如果 $x \in \mathcal{X}_s$，则 $\mathcal{P}[\mathcal{X}]_s(x)$ 成立。
2. 对于每个元数为 $(\vec{s_1}.s_1, \dots, \vec{s_n}.s_n)s$ 的运算符 $o$，如果对于每个 $1 \leq i \leq n$，对于每个新重命名 $\rho_i : \vec{x_i} \leftrightarrow \vec{x'_i}$（其中 $\vec{x'_i} \notin \mathcal{X}$），有 $\mathcal{P}[\mathcal{X}, \vec{x'_i}]_{s_i}(\hat{\rho_i}(a_i))$ 成立，则 $\mathcal{P}[\mathcal{X}]_s(o(\vec{x_1}.a_1; \dots; \vec{x_n}.a_n))$ 也成立。

第二个条件确保归纳假设对所有新选择的绑定变量名称都成立，而不仅仅是 ABT 中实际给出的那些名称。

!!! example

    作为一个例子，我们定义判断 $x \in a$，其中 $a \in \mathcal{B}[\mathcal{X}, x]$，表示 $x$ 在 $a$ 中自由出现。非正式地，这意味着 $x$ 在 $a$ 外部某处被绑定，而不是在 $a$ 本身内部。如果 $x$ 在 $a$ 内部被绑定，则这些 $x$ 的出现与绑定外部的那些出现不同。以下定义确保了这一点：

    !!! note "定义：判断 $x \in a$"

        1. $x \in x$。
        2. $x \in o(\vec{x_1}.a_1; \dots; \vec{x_n}.a_n)$：如果存在 $1 \leq i \leq n$，对于每个新的重命名 $\rho : \vec{x_i} \leftrightarrow \vec{z_i}$，我们有 $x \in \hat{\rho}(a_i)$。

    第一个条件声明 $x$ 在 $x$ 中是自由的，但在任何变量 $y$（除了 $x$ 之外）中不是自由的。第二个条件声明，如果 $x$ 在某个参数中是自由的，无论该参数中的绑定变量名称如何选择，那么它在整个 ABT 中也是自由的。

> 上面这个例子使用结构归纳模新重命名完成了 $x \in a$ 的良定义。
>
> 我们可以尝试证明 $x \in \mathtt{let}(x; y.x + y)$：
>
> - 对于 $i = 1$，我们有 $x \in x$。
> - 对于 $i = 2$，不论对 $y$ 做什么样的重命名，$x$ 都在 $x + y$ 中。
>
> 证毕。

!!! note "定义：$\alpha$ 等价"

    关系 $a =_\alpha b$（称为 $\alpha$-等价，因历史原因）表示 $a$ 和 $b$ 在绑定变量名称选择上是相同的。$\alpha$-等价关系是包含以下两个条件的最强同余关系：

    1. $x =_\alpha x$。
    2. $o(\vec{x_1}.a_1; \dots; \vec{x_n}.a_n) =_\alpha o(\vec{x'_1}.a'_1; \dots; \vec{x'_n}.a'_n)$ 如果对于每个 $1 \leq i \leq n$，$\hat{\rho_i}(a_i) =_\alpha \hat{\rho'_i}(a'_i)$ 对于所有新的重命名 $\rho_i : \vec{x_i} \leftrightarrow \vec{z_i}$ 和 $\rho'_i : \vec{x'_i} \leftrightarrow \vec{z_i}$。

这个想法是我们一致地重命名 $\vec{x_i}$ 和 $\vec{x'_i}$，以避免混淆，并检查 $a_i$ 和 $a'_i$ 是否是 $\alpha$-等价的。如果 $a =_\alpha b$，则 $a$ 和 $b$ 是对方的 $\alpha$-变体。

> 简单来说，上面的定义将所有绑定变量的名称统一，然后检查等价。这种等价条件很强，意思是要求两个 ABT 的结构一致，仅仅是绑定变量的名称不同。

在定义将一个 ABT $b$（其类型为 $s$）替换到另一个 ABT $a$ 的某个变量 $x$（其类型为 $s$）的自由出现位置时（记作 \([b/x]a\)），需要小心。替换的部分定义如下：

!!! note "定义：ABT 中的替换"

    1. \([b/x]x = b\)，而 \([b/x]y = y\)（如果 $x \neq y$）。
    2. \([b/x]o(\vec{x_1}.a_1; \dots; \vec{x_n}.a_n) = o(\vec{x_1}.a'_1; \dots; \vec{x_n}.a'_n)\)，其中，对于每个 $1 \leq i \leq n$，我们要求 \(\vec{x_i} \notin b\)，并且设置 $a'_i = [b/x]a_i$ 如果 $x \notin \vec{x_i}$，否则 $a'_i = a_i$。

定义 \([b/x]a\) 是相当精细的，需要仔细考虑。

替换的一个问题是，如果 $x$ 在 $a$ 内部由抽象器绑定，则 $x$ 在抽象器内部不会出现为自由变量，因此不会被替换。

!!! example "例如，\([b/x] \text{let}(a_1; x.a_2) = \texttt{let}([b/x]a_1; x.a_2)\)，因为在 $x.a_2$ 中没有 $x$ 的自由出现。"

> 替换只会替换自由变量，不会替换绑定变量。

另一个问题是替换过程中可能会捕获到 $b$ 中的自由变量。

!!! example "例如，如果 $y \in b$ 且 $x \neq y$，则 \([b/x] \texttt{let}(a_1; y.a_2)\) 是未定义的，而不是 \(\texttt{let}([b/x]a_1; y.[b/x]a_2)\)，这可能在初看时会有所误解。"

> 在替换时，不应当使绑定变量 $\vec{x}$ 与替换变量 $b$ 中的自由变量出现重名，这会让替换变量中的自由变量被绑定，导致结构发生变化。

!!! example "例如，给定 $x \neq y$，\([y/x] \texttt{let}(\text{num}[0]; y.\text{plus}(x; y))\) 是未定义的，而不是 \(\texttt{let}(\text{num}[0]; y.\text{plus}(y; y))\)，因为这混淆了两个不同的变量 $y$。"

尽管避免捕获（capture avoidance）是替换的一个基本特征，但在某种意义上，它仅仅是一个技术上的麻烦。如果绑定变量的名称没有实际意义，那么可以通过首先重命名 $a$ 中的绑定变量来避免 $b$ 中的任何自由变量，从而总是能够避免捕获。在前面的例子中，如果我们将绑定变量 $y$ 重命名为 $y'$，得到 $a' = \texttt{let}(\text{num}[0]; y'.\text{plus}(x; y'))$，那么 \([b/x]a'\) 是定义好的，且等于 \(\texttt{let}(\text{num}[0]; y'.\text{plus}(b; y'))\)。以这种方式避免捕获的代价是，替换仅在 $\alpha$-等价下确定，因此我们可能不再将替换视为一个函数，而只能视为一个适当的关系。

> 替换前可以对绑定变量进行重命名，避免捕获。

为了恢复替换的函数特性，采用以下识别约定是足够的：

!!! note "识别约定"

    抽象绑定树（ABTs）总是按 $\alpha$-等价（$\alpha$-equivalence）来识别。

也就是说，$\alpha$-等价的 ABT 被视为相同。替换可以扩展到 ABT 的 $\alpha$-等价类，以避免捕获，通过选择 ABT 的等价类的代表，从而使得替换是定义良好的，然后形成结果的等价类。任何两个替换定义良好的代表选择都将给出 $\alpha$-等价的结果，因此替换变成一个定义明确的全函数。在本书中，我们将采用 ABT 的识别约定。

我们经常需要考虑一些语言，它们的抽象语法不能通过固定的操作符集合来指定，而是需要操作符对其出现的上下文敏感。

!!! note "定义：符号参数"

    为了我们的目的，我们将考虑一组**符号参数（symbolic parameters），或称为符号（symbols）**，这些符号索引一族操作符，从而在符号集变化时，操作符集也会变化。一个索引操作符 $o$ 是一个由符号 $u$ 索引的操作符家族，当 $u$ 是一个可用符号时，$o[u]$ 是一个操作符。

如果 $\mathcal{U}$ 是一个有限的符号集，那么 $\mathcal{B}[\mathcal{U}; \mathcal{X}]$ 是按照之前的方式生成的按类型索引的 ABTs 家族，接受所有符号 $u \in \mathcal{U}$ 的索引操作符实例。虽然变量是一个占位符，代表其类型的未知 ABT，但符号本身并不代表任何东西，也不是一个 ABT。符号的唯一意义在于它是否与另一个符号相同或不同；操作符实例 $o[u]$ 和 $o[u']$ 只有在 $u$ 和 $u'$ 相同时才相同，即当 $u$ 和 $u'$ 是相同的符号时，操作符实例才相同。

符号集通过在作用域内引入新的（new）或“新鲜的”（fresh）符号来扩展，这使用抽象器 $u.a$，该抽象器在 ABT $a$ 中绑定了符号 $u$。抽象符号在某种意义上是“新”的，就像抽象变量一样：绑定符号的名称可以随意变化，只要不产生冲突。这种重命名属性确保了抽象符号在作用域内是唯一的。

!!! note "符号与变量的区别"

    符号和变量之间的唯一区别在于：对符号的唯一操作是重命名；对于符号，没有替换的概念。

> 符号不能被替换。

最后，关于符号表示法的一点说明：为了提高可读性，我们通常会对操作符的参数进行“分组”和“分阶段”处理，使用圆括号和花括号来显示分组，并且一般认为阶段从右到左进行。所有在一个组中的参数被认为是在相同的阶段出现的，尽管它们的顺序是有意义的，而连续的组被认为是在顺序的阶段中出现的。分阶段和分组通常是一个有用的记忆工具，但没有根本意义。例如，ABT $o\{a1; a2\}(a3; x.a4)$ 与 $o(a1; a2; a3; x.a4)$ 是相同的，任何其他保持顺序的分组或分阶段方法也会得到相同的结果。

### 第二章：归纳定义 Inductive Definitions

归纳定义是编程语言研究中不可或缺的工具。在本章中，我们将建立归纳定义的基本框架，并给出其一些应用实例。归纳定义由一组用于推导各种形式的**判断（judgments）**（或称为**断言（assertions）**）的**规则（rules）**组成。判断是关于某种抽象绑定树的一个或多个的陈述。这些规则规定了判断有效的必要和充分条件，从而完全确定了其含义。

#### 判断 Judgments

我们首先介绍关于抽象绑定树的判断（或断言）的概念。我们将使用多种形式的判断，其中包括以下示例：

- \(n\ \mathsf{nat}\) 表示 \(n\) 是一个自然数
- \(n_1 + n_2 = n\) 表示 \(n\) 是 \(n_1\) 和 \(n_2\) 的和
- \(\tau\ \mathsf{ type}\) 表示 \(\tau\) **是一种类型**
- \(e : \tau\) 表示表达式 \(e\) 的**类型是** \(\tau\)
- \(e \Downarrow v\) 表示表达式 \(e\) 的**值**为 \(v\)

!!! note "定义：判断、判断形式、实例、谓词、主体"

    一个判断声明一个或多个抽象绑定树具有某种属性或彼此之间存在某种关系。属性或关系本身被称为**判断形式（judgment form）**，而对象具有该属性或存在该关系的判断则称为该判断形式的一个**实例（instance）**。判断形式也称为**谓词（predicate）**，而构成实例的对象称为其**主体（subject）**。

我们用 \(a \ \mathsf{J}\) 或 \(\mathsf{J} \ a\) 来表示断言判断 \(\mathsf{J}\) 对抽象绑定树 \(a\) 成立。相应地，有时我们用 \(- \mathsf{J}\) 或 \(\mathsf{J} -\) 来表示判断形式 \(\mathsf{J}\)，其中破折号表示 \(\mathsf{J}\) 没有具体的参数。当判断的主体不重要时，我们用 \(\mathsf{J}\) 来代表未指定的判断，即某个判断形式的实例。对于特定的判断形式，我们可以自由地使用前缀、后缀或混合表示法，如上例所示，以增强可读性。

> $-$ 表示没有具体参数。

#### 推理规则 Inference Rules

!!! note "定义：判断形式"

    判断形式的**归纳定义（inductive definition）**由一组形式为：

    \[
    \frac{J_1 \dots J_k}{J} \tag{2.1}
    \]

    的规则组成，其中 \(J\) 和 \(J_1, \dots, J_k\) 都是所定义的判断形式。水平线以上的判断称为规则的**前提（premises）**，水平线以下的判断称为其**结论（conclusion）**。如果一个规则没有前提（即 \(k\) 为零），该规则称为**公理（axiom）**；否则，称为**适当的规则（proper rule）**。

推理规则可以理解为前提对于得出结论是**充分（sufficient）**的：要证明 \(J\)，只需要证明 \(J_1, \dots, J_k\)。当 \(k\) 为零时，规则表示其结论无条件成立。请记住，通常可能存在多个具有相同结论的规则，每个规则都为结论提供充分条件。因此，如果某个规则的结论成立，并不意味着该规则的前提必须成立，因为它可能是由另一条规则推导出来的。

!!! example

    例如，以下规则构成了判断形式 \(- \mathsf{nat}\) 的归纳定义：

    \[
    \frac{}{\mathtt{zero}\ \mathsf{nat}} \tag{2.2a}
    \]

    \[
    \frac{a\ \mathsf{nat}}{\mathtt{succ}(a)\ \mathsf{nat}} \tag{2.2b}
    \]

    这些规则指定了当 \(a\) 为零，或 \(a\) 为 \(\mathtt{succ}(b)\) 且 \(b\) 对于某个 \(b\) 满足 \(\mathsf{nat}\) 时，\(a \ \mathsf{nat}\) 成立。将这些规则视为完整的，可以得出 \(a\ \mathsf{nat}\) 当且仅当 \(a\) 是一个自然数。

!!! example

    类似地，以下规则构成了判断形式 \(- \mathsf{tree}\) 的归纳定义：

    \[
    \frac{}{\mathtt{empty}\ \mathsf{tree}} \tag{2.3a}
    \]

    \[
    \frac{a_1\ \mathsf{tree} \quad a_2\ \mathsf{tree}}{\mathtt{node}(a_1 ; a_2)\ \mathsf{tree}} \tag{2.3b}
    \]

    这些规则表明，当 \(a\) 是 \(\mathtt{empty}\)，或 \(a\) 是 \(\mathtt{node}(a_1 ; a_2)\) 且 \(a_1\ \mathsf{tree}\) 和 \(a_2\ \mathsf{tree}\) 时，\(a\ \mathsf{tree}\) 成立。将这些规则视为完整的，它们表示 \(a\) 是一棵二叉树，即它要么是空树，要么是由两个子节点组成的节点，而每个子节点也是二叉树。

!!! example

    判断形式 \(a\ \mathsf{is}\ b\) 表示两个抽象绑定树 \(a\) 和 \(b\) 的相等性，其中 \(a\ \mathsf{nat}\) 且 \(b\ \mathsf{nat}\)，其归纳定义由以下规则给出：

    \[
    \frac{}{\mathtt{zero}\ \mathsf{is}\ \mathtt{zero}} \tag{2.4a}
    \]

    \[
    \frac{a\ \mathsf{is}\ b}{\mathtt{succ}(a)\ \mathsf{is}\ \mathtt{succ}(b)} \tag{2.4b}
    \]

在前面的例子中，我们使用了一种符号惯例，通过有限数量的模式或**规则方案（rule scheme）**指定无限多的规则。例如，规则 $(2.2b)$ 是一个规则方案，它为规则中的每个对象 \(a\) 确定了一条规则，称为规则方案的实例。我们将依赖上下文来判断一条规则是针对**特定**对象 \(a\) 还是作为一个规则方案，进而为规则中的**每个**对象提供相应的规则。

一组规则被认为定义了在这些规则下**闭合（closed under）**或**遵守（respect）**这些规则的**最强（strongest）**判断形式。对规则闭合意味着这些规则**足以（sufficient）**证明判断的有效性：如果有办法通过给定的规则得到 \(J\)，则 \(J\) 成立。作为**最强**判断形式，规则是必要的：\(J\) **仅当**通过应用规则能够得到时才成立。规则的充分性意味着我们可以通过组合规则来**推导（derive）**出 \(J\) 的成立。而规则的必要性则意味着我们可以使用**规则归纳（rule induction）**对其进行推理。

> 最强=仅当（必要）；闭合=充分。
>
> 充分性说明可以推导结论，必要性说明要用前提来推导。
>
> 这一段 B 话说的就是这么个事情。

#### 推导 Derivations

要证明一个归纳定义的判断成立，展示其**推导过程（derivation）**就足够了。判断的推导是规则的有限组合，开始于公理，结束于该判断。可以将其看作一个树结构，其中每个节点代表一个规则，而其子节点是该规则前提的推导过程。我们有时会说，某个判断 \(J\) 的推导是该归纳定义的判断 \(J\) 成立的证据。

!!! note "定义：推导过程"

    通常，我们将推导描绘成一棵树，结论位于底部，而规则的前提作为证据出现在该节点的上方。因此，如果

    \[
    \frac{J_1 \quad \dots \quad J_k}{J}
    \]

    是一个推理规则，并且 \(\bigtriangledown_1, \dots, \bigtriangledown_k\) 是其前提的推导过程，那么

    \[
    \frac{\bigtriangledown_1 \quad \dots \quad \bigtriangledown_k}{J}
    \]

    就是其结论的推导。特别地，当 \(k = 0\) 时，节点没有子节点。

!!! example

    例如，以下是 \(\mathtt{succ}(\mathtt{succ}(\mathtt{succ}(\mathtt{zero})))\ \mathsf{nat}\) 的一个推导过程：

    \[
    \frac{
        \frac{
            \frac{
                \frac{}{\mathtt{zero}\ \mathsf{nat}}
            }
            {\mathtt{succ}(\mathtt{zero})\ \mathsf{nat}}
        }
        {\mathtt{succ}(\mathtt{succ}(\mathtt{zero}))\ \mathsf{nat}}
    }
    {\mathtt{succ}(\mathtt{succ}(\mathtt{succ}(\mathtt{zero})))\ \mathsf{nat}}
    \tag{2.5}
    \]

!!! example

    类似地，下面是 \(\mathtt{node}(\mathtt{node}(\mathtt{empty}; \mathtt{empty}); \mathtt{empty}) \mathsf{ tree}\) 的一个推导过程：

    \[
    \frac{
        \frac{
            \frac{}{\mathtt{empty}\ \mathsf{tree}} \frac{}{\mathtt{empty}\ \mathsf{tree}}
        }{
            \mathtt{node}(\mathtt{empty}; \mathtt{empty}) \mathsf{ tree}
        }
        \frac{}{\mathtt{empty}\ \mathsf{tree}}
    }
    {\mathtt{node}(\mathtt{node}(\mathtt{empty}; \mathtt{empty}); \mathtt{empty}) \mathsf{ tree}} \tag{2.6}
    \]

为了证明一个归纳定义的判断是可推导的，我们只需要找到一个推导过程。寻找推导的主要方法有两种，分别称为**前向推导（forward chaining）**或自下而上的构造（bottom-up construction）和**后向推导（backward chaining）**或自上而下的构造（top-down construction）。**前向推导**从公理开始，朝着所需的结论逐步推进，而**后向推导**则从目标结论出发，向后追溯到公理。

更具体地说，前向推导的搜索方法会维护一组可推导的判断，并通过添加所有前提已在该集合中的推理规则的结论，持续扩展这一集合。最初，该集合为空；当所需的判断出现在集合中时，过程结束。假设在每个阶段都考虑了所有规则，那么前向推导最终会找到任何可推导判断的推导过程，但通常无法通过算法确定何时应该停止扩展集合，并得出所需判断不可推导的结论。我们可能会不断地将更多判断添加到可推导集合中，却始终无法实现预期目标。要判断给定的判断是否不可推导，必须理解规则的全局特性。

> 前向推导会遇到无法判断所需判断不可推导的情况。

前向推导是**无目标指向的（undirected）**，因为在每一步决定如何继续时，它并不考虑最终目标。相比之下，后向推导是**目标导向的（goal-directed）**。后向推导的搜索方法会维护一个当前目标的队列，这些是需要寻找推导过程的判断。最初，该队列仅包含我们希望推导的判断。在每个阶段，我们从队列中移除一个判断，并考虑所有以该判断为结论的推理规则。对于每个这样的规则，我们将该规则的前提添加到队列的末尾，然后继续。如果有多条符合条件的规则，这个过程必须为每个候选规则重复，使用相同的初始队列。该过程在队列为空时终止，所有目标都已实现；此过程中可以丢弃对候选规则的任何未完成的考虑。和前向推导一样，后向推导最终也会找到任何可推导判断的推导过程，但通常没有算法可以确定当前目标是否可推导。如果不可推导，我们可能徒劳地将更多判断添加到目标集合中，永远无法满足所有目标。

> 后向推导同样难以判断当前目标是否可推导。

#### 规则归纳 Rule Induction

由于归纳定义指定了在一组规则下封闭的最强判断形式，我们可以通过**规则归纳**对它们进行推理。规则归纳原理表明，要证明某个性质 \( P \) 在 \( J \) 可导时成立，只需证明 \( P \) 在定义判断形式 \( J \) 的规则下是封闭的或遵守这些规则。

更具体地说，性质 \( P \) 遵守如下规则：

\[
\frac{a_1 J \ \dots \ a_k J}
{a J}
\]

如果当 \( P(a_1), \dots, P(a_k) \) 成立时，\( P(a) \) 也成立。假设 \( P(a_1), \dots, P(a_k) \) 被称为归纳假设，而 \( P(a) \) 被称为推理的归纳结论。

规则归纳原理只是归纳定义的表达形式，它说明通过一组规则定义的判断形式是最强的、在这些规则下封闭的形式。因此，规则归纳定义的判断形式有两个特性：(a) 在这些规则下封闭，即通过规则推导出的结论是有效的；(b) 足以用于推理其他在规则下也封闭的性质。这意味着推导出的判断是判断有效性的证据，同时我们可以通过规则归纳推理关于归纳定义的判断形式。

对于规则 (2.2)，规则归纳原理表明，要证明 \( P(a) \) 在 \( a \) 为自然数时成立，只需证明：

1. \( P(zero) \)。
2. 对任意 \( a \)，如果 \( P(a) \) 成立，则 \( P(succ(a)) \) 也成立。

这些条件的充分性是我们熟悉的数学归纳法原理。同样，对于规则 (2.3)，规则归纳法表明，要证明 \( P(a) \) 在 \( a \) 为树时成立，只需证明：

1. \( P(empty) \)。
2. 对任意 \( a_1 \) 和 \( a_2 \)，如果 \( P(a_1) \) 和 \( P(a_2) \) 成立，则 \( P(node(a_1; a_2)) \) 也成立。

这些条件的充分性被称为**树归纳原理**。

我们还可以通过规则归纳证明，自然数的前驱也是自然数。尽管这看起来显而易见，但这个例子展示了如何从基本原则推导出这一结论。

!!! note "引理 2.1：自然数的后继还是自然数"

    **引理 2.1** 如果 \( succ(a) \) 是自然数，则 \( a \) 也是自然数。

    ---

    **证明** 我们只需证明性质 \( P(a) \)，即如果 \( a \) 是自然数且 \( a = succ(b) \)，则 \( b \) 是自然数，该性质遵守规则 (2.2)。

    - **规则 (2.2a)**：显然 \( zero \) 是自然数，且第二个条件空成立，因为 \( zero \) 不是 \( succ(-) \) 的形式。
    - **规则 (2.2b)**：归纳假设下，我们知道 \( a \) 是自然数，且如果 \( a \) 是 \( succ(b) \) 的形式，则 \( b \) 是自然数。我们要证明 \( succ(a) \) 是自然数，这是显然的；且如果 \( succ(a) \) 是 \( succ(b) \) 的形式，则 \( b \) 是自然数，根据归纳假设，\( b \) 是自然数。

通过规则归纳，我们还可以证明按照规则 (2.4) 定义的等式是自反的。

!!! note "引理 2.2：自然数等于自身"

    **引理 2.2** 如果 \( a \) 是自然数，则 \( a = a \)。

    ---

    **证明** 通过对规则 (2.2) 进行规则归纳：

    - **规则 (2.2a)**：应用规则 (2.4a)，我们得到 \( zero = zero \)。
    - **规则 (2.2b)**：假设 \( a = a \)，那么通过应用规则 (2.4b)，可以推导出 \( succ(a) = succ(a) \)。

类似地，我们可以证明后继运算是单射的。

!!! note "引理 2.3：自然数的后继是单射的"

    **引理 2.3** 如果 \( succ(a_1) = succ(a_2) \)，则 \( a_1 = a_2 \)。

    ---

    **证明** 类似于引理 2.1 的证明。

#### 迭代和同时归纳定义 Iterated and Simultaneous Inductive Definitions

归纳定义通常是迭代进行的，意味着一个归纳定义是在另一个归纳定义的基础上构建的。在迭代归纳定义中，规则的前提：

\[
\frac{J_1 \ \dots \ J_k}
{J}
\]

可以是之前定义的判断形式的实例，也可以是正在定义的判断形式的实例。例如，以下规则定义了判断形式 $- \mathsf{list}$，它表示 \(a\) 是一个自然数列表：
\[
\frac{}{\mathtt{nil}\ \mathsf{list}} \tag{2.7a}
\]

\[
\frac{a\ \mathsf{nat} \quad b\ \mathsf{list}}{\mathtt{cons}(a;b)\ \mathsf{list}} \tag{2.7b}
\]

规则 $(2.7b)$ 的第一个前提是之前定义的判断形式 \(a\ \mathsf{nat}\) 的实例，而前提 \(b\ \mathsf{list}\) 则是正在通过这些规则定义的判断形式的实例。

两个或更多的判断形式通常由**同时归纳定义（simultaneous inductive definition）**定义。一个同时归纳定义包含一组规则，用于推导多个不同判断形式的实例，任何判断形式都可以作为任何规则的前提。由于定义每个判断形式的规则可能涉及其他判断形式，因此这些判断形式没有一个是先于其他形式定义的。相反，我们必须理解，这些判断形式是由整组规则同时定义的。由这些规则定义的判断形式仍然是封闭在这些规则下的最强判断形式。因此，规则归纳的证明原则仍然适用，不过它要求我们同时证明每个定义的判断形式的某个性质。

!!! example

    例如，以下规则构成了 $a\ \mathsf{even}$（表示 \(a\) 是偶数）和 $a\ \mathsf{odd}$（表示 \(a\) 是奇数）判断的同时归纳定义：

    \[
    \frac{}{\mathtt{zero}\ \mathsf{even}} \tag{2.8a}
    \]

    \[
    \frac{b\ \mathsf{odd}}{\mathtt{succ}(b)\ \mathsf{even}} \tag{2.8b}
    \]

    \[
    \frac{a\ \mathsf{even}}{\mathtt{succ}(a)\ \mathsf{odd}} \tag{2.8c}
    \]

这些规则的规则归纳原理表明，要同时证明 \(\mathcal{P}(a)\) 对于 \(a\) 是偶数时成立，且 \(\mathcal{Q}(b)\) 对于 \(b\) 是奇数时成立，只需证明以下几点：

1. \(\mathcal{P}(\mathtt{zero})\)；
2. 如果 \(\mathcal{Q}(b)\) 成立，则 \(\mathcal{P}(\mathsf{succ}(b))\) 成立；
3. 如果 \(\mathcal{P}(a)\) 成立，则 \(\mathcal{Q}(\mathsf{succ}(a))\) 成立。

!!! example "例如，我们可以使用同时规则归纳来证明：（1）如果 \(a\) 是偶数，则 \(a\) 要么是 $0$，要么是 \( \mathtt{succ}(b) \)，其中 \(b\) 是奇数；（2）如果 \(a\) 是奇数，则 \(a\) 是 \( \mathtt{succ}(b) \)，其中 \(b\) 是偶数。"

我们定义 \(\mathcal{P}(a)\) 当且仅当 \(a\) 是 $0$ 或 \(a\) 是 \( \mathtt{succ}(b) \)，其中 \(b\) 是奇数时成立，并定义 \(Q(b)\) 当且仅当 \(b\) 是 \( \mathtt{succ}(a) \)，其中 \(a\) 是偶数时成立。通过规则归纳可以证明：

1. \(\mathcal{P}(\mathtt{zero})\) 成立，因为 \( \mathtt{zero} \) 是 0；
2. 如果 \(Q(b)\) 成立，则 \( \mathtt{succ}(b) \) 是 \( \mathtt{succ}(b') \)，其中 \(b' = b\)，并应用归纳假设；
3. 如果 \(\mathcal{P}(a)\) 成立，则 \( \mathtt{succ}(a) \) 是 \( \mathtt{succ}(a') \)，其中 \(a' = a\)，并应用归纳假设。

#### 通过规则定义函数 Defining Functions by Rules

归纳定义的一个常见用途是通过给定输入和输出之间的**图（graph）**的归纳定义来定义函数，然后证明该关系唯一地确定了给定输入的输出。

!!! example

    例如，我们可以定义自然数上的加法函数为关系 \( \mathsf{sum}(a; b; c) \)，其意图是表示 \(c\) 是 \(a\) 和 \(b\) 的和，定义如下：

    \[
    \frac{b\ \mathsf{nat}}{\mathsf{sum}(\mathtt{zero}; b; b)} \tag{2.9a}
    \]

    \[
    \frac{\mathsf{sum}(a; b; c)}{\mathsf{sum}(\mathtt{succ}(a); b; \mathtt{succ}(c))} \tag{2.9b}
    \]

    这些规则定义了自然数 \(a\)、\(b\) 和 \(c\) 之间的三元关系 \( \mathsf{sum}(a; b; c) \)。我们可以证明，在这个关系中，\(c\) 是由 \(a\) 和 \(b\) 唯一确定的。

!!! note "定理 2.4: 和函数的存在性和唯一性"

    **定理** 对于每个自然数 \(a\ \mathsf{nat}\) 和 \(b\ \mathsf{nat}\)，存在唯一的自然数 \(c\ \mathsf{nat}\)，使得 \( \mathsf{sum}(a; b; c) \) 成立。

    ---

    **证明** 该证明分为两部分：

    1. **存在性**：如果 \(a\) 和 \(b\) 是自然数，则存在自然数 \(c\)，使得 \( \mathsf{sum}(a; b; c) \) 成立。
    2. **唯一性**：如果 \( \mathsf{sum}(a; b; c_1) \) 和 \( \mathsf{sum}(a; b; c_2) \) 都成立，则 \(c_1 = c_2\)。

    ---

    对于存在性，我们令 \(\mathcal{P}(a)\) 表示以下命题：如果 \(b\) 是自然数，则存在自然数 \(c\)，使得 \( \mathsf{sum}(a; b; c) \) 成立。我们通过规则归纳来证明，如果 \(a\) 是自然数，则 \(\mathcal{P}(a)\) 成立。我们有两个情况需要考虑：

    - **规则 $(2.2a)$**：我们要证明 \(\mathcal{P}(\mathsf{zero})\)。假设 \(b\) 是自然数，并令 \(c = b\)，根据规则 $(2.9a)$，我们得出 \( \mathsf{sum(zero; b; c)} \)。
    - **规则 $(2.2b)$**：假设 \(\mathcal{P}(a)\) 成立，我们要证明 \(\mathcal{P}(\mathsf{succ}(a))\)。也就是说，我们假设如果 \(b\) 是自然数，则存在自然数 \(c\)，使得 \( \mathsf{sum}(a; b; c) \) 成立，并且要证明如果 \(b' \) 是自然数，则存在 \(c'\)，使得 \( \mathsf{sum}(\mathtt{succ}(a); b'; c') \) 成立。为此，假设 \(b' \) 是自然数。根据归纳假设，存在 \(c\) 使得 \( \mathsf{sum}(a; b'; c) \) 成立。令 \(c' = \mathtt{succ}(c)\)，并应用规则 $(2.9b)$，我们得出 \( \mathsf{sum}(\mathtt{succ}(a); b'; c') \)，如所需。

    ---

    对于唯一性，我们证明，如果 \( \mathsf{sum}(a; b; c_1) \) 成立，且 \( \mathsf{sum}(a; b; c_2) \) 成立，则 \(c_1 = c_2\)，通过基于规则 (2.9) 的规则归纳来证明。

    - **规则 (2.9a)**：我们有 \(a = 0\) 且 \(c_1 = b\)。通过相同规则的内归纳，我们可以证明如果 \( \mathsf{sum}(\mathtt{zero}; b; c_{2}) \) 成立，则 \(c_2 = b\)。根据引理 2.2，我们得出 \(b = b\)。
    - **规则 (2.9b)**：我们有 \(a = \mathsf{succ}(a')\) 且 \(c_1 = \mathsf{succ}(c'_1)\)，其中 \( \mathsf{sum}(a'; b; c'_1) \) 成立。通过相同规则的内归纳，我们可以证明如果 \( \mathsf{sum}(a; b; c_2) \) 成立，则 \(c_2 = \mathsf{succ}(c'_2)\)，其中 \( \mathsf{sum}(a'; b; c'_2) \) 成立。根据外归纳假设，\(c'_1 = c'_2\)，因此 \(c_1 = c_2\)。

### 第三章：假设判断与一般判断 Hypothetical and General Judgments

**假设判断（Hypothetical judgment）**表达了一个或多个假设与结论之间的**蕴涵关系（entailment）**。我们将考虑两种蕴涵概念，分别是**可推导性（derivability）**和**可接受性（admissibility）**。两者都表示某种形式的蕴涵，但区别在于可导性在扩展新规则时是稳定的，而可接受性则不是。**一般判断**表达了判断的普遍性或泛化性。一般判断有两种形式：**泛型（generic）**和**参数化（parametric）**。泛型判断表示相对于判断中变量的所有替换实例的泛化，而参数化判断表示相对于符号重命名的泛化。

#### 假设判断 Hypothetical Judgments

假设判断编纂了表达一个结论在一个或多个假设成立的条件下有效性的规则。假设判断有两种形式，区别在于结论在何种意义上依赖于假设。其中一种在扩展更多规则时是稳定的，另一种则不是。

##### 可导性 Derivability

对于给定的规则集合 \(\mathcal{R}\)，我们定义**可导性（derivability）判断**，记为 \(J_1, ..., J_k \vdash_\mathcal{R} K\)，其中每个 \(J_i\) 和 \(K\) 是基本判断，意思是我们可以使用下列公理将规则集 \(\mathcal{R}\) 扩展为 \(\mathcal{R} \cup \{J_1, ..., J_k\}\)，并从**扩展（expansion）**中推导出 \(K\)：

\[
\frac{}{J_1} \cdots \frac{}{J_k}
\]

我们将判断的**假设（hypotheses)**或**前提（antecedents）** \(J_1, ..., J_k\) 视为“临时公理”，并通过组合 \(\mathcal{R}\) 中的规则推导出**结论（conclusion）**或**后件（consequent）**。因此，假设判断的证据由使用 \(\mathcal{R}\) 中的规则从假设推导出结论的推导过程组成。

> 假设就是临时的公理。上面的形式定义就是现有条件 + 假设为真 = 结论为真。

我们用大写希腊字母（通常是 \(\Gamma\) 或 \(\Delta\)）表示一组有限的基本判断，并用 \(\mathcal{R} \cup \Gamma\) 表示 \(\mathcal{R}\) 扩展为包含对应 \(\Gamma\) 中每个判断的公理的集合。判断 $\Gamma \vdash_\mathcal{R} K$ 表示 $K$ 能够从 $\mathcal{R} \cup \Gamma$ 推导。判断 \(\vdash_\mathcal{R} \Gamma\) 表示对 $\Gamma$ 中的每个 $J$ 都有 $\vdash_\mathcal{R} J$。一种等价的定义 \(J_1, ..., J_n \vdash_\mathcal{R} J\) 的方式是说规则：

> $\Gamma$ 要转化为公理，再加入 $\mathcal{R}$ 作为假设。

\[
\frac{J_1, \dots, J_n}{J} \tag{3.1}
\]

是从 \(\mathcal{R}\) 中可导出的，这意味着存在一个由 \(\mathcal{R}\) 中的规则组成的 \(J\) 的推导过程，并将 \(J_1, ..., J_n\) 作为公理。

> 第一种定义使用“临时公理”扩展规则集，第二种定义利用**推导过程**，同时把假设作为公理。
>
> 感觉说的完全是同一种事情。

!!! example

    例如，考虑相对于规则 $(2.2)$ 的可导性判断：

    > 规则 $(2.2)$：$\mathtt{zero}\ \mathsf{nat}$ 和 $\frac{a\ \mathsf{nat}}{\mathtt{succ}(a)\ \mathsf{nat}}$

    \[
    a \ \mathsf{nat} \vdash_{(2.2)} \mathtt{succ}(\mathtt{succ}(a))\ \mathsf{nat} \tag{3.2}
    \]

    对于任何对象 \(a\)，这个判断都是有效的，如推导所示：

    \[
    \frac{
        \frac{
            a \ \mathsf{nat}
        }
        {
            \mathsf{succ}(a) \ \mathsf{nat}
        }
    }{
        \mathsf{succ}(\mathsf{succ}(a)) \ \mathsf{nat}
    }
    \tag{3.3}
    \]

    这是通过组合规则 $(2.2)$ 从 \(a \ \mathsf{nat}\) 作为公理出发，最终得到 \( \mathsf{succ}(\mathsf{succ}(a)) \ \mathsf{nat}\)。等价地，$(3.2)$ 的有效性也可以通过说明规则

    \[
    \frac{
    a \ \mathsf{nat}
    }
    {
    \mathtt{succ}(\mathtt{succ}(a)) \ \mathsf{nat}
    }
    \tag{3.4}
    \]

    是从规则 $(2.2)$ 可导出来表达。

可导性在扩展新规则时是稳定的，这直接源于它的定义。

!!! note "定理 3.1：稳定性"

    **定理**：如果 \(\Gamma \vdash_\mathcal{R} J\)，那么 \(\Gamma \vdash_{\mathcal{R} \cup \mathcal{R}'} \vdash J\)。

    ---

    **证明**：从 \(\mathcal{R} \cup \Gamma\) 到 $J$ 的任何推导也可以从 \(\mathcal{R} \cup \mathcal{R}' \cup \Gamma\) 中推导出来，因为 \(\mathcal{R}\) 中的任何规则也是 \(\mathcal{R} \cup \mathcal{R}'\) 中的规则。

可导性具有许多**结构性质（structural properties）**，它们独立于所讨论的规则 \(\mathcal{R}\) 而存在：

!!! note "可导性的结构性质"

    - **自反性（reflexivity）**：每个判断都是自己的后件，即 \(\Gamma, J \vdash_\mathcal{R} J\)。每个假设都可以证明自己为结论。
    - **弱化（weakening）**：如果 \(\Gamma \vdash_\mathcal{R} J\)，那么 \(\Gamma, K \vdash_\mathcal{R} J\)。未使用的选项不会影响蕴涵。
    - **传递性（transitivity）**：如果 \(\Gamma, K \vdash_\mathcal{R} J\) 并且 \(\Gamma \vdash_\mathcal{R} K\)，那么 \(\Gamma \vdash_\mathcal{R} J\)。如果我们用一个推导替换掉一个公理，结果仍然是该后件的推导。

    > 第三条不如称为简并性。

自反性直接源于可导性的定义。弱化直接来自可导性的定义。传递性通过对第一个前提进行规则归纳来证明。

##### 可接受性 Admissibility

!!! todo "暂未修订"

**可接受性**，记为 \(\Gamma \models_\mathcal{R} J\)，是一种较弱的假设判断形式，表示 \(\mathcal{R}\) 推导出 \(\mathcal{R} \vdash J\)。也就是说，当假设可以从 \(\mathcal{R}\) 中推导出时，结论 \(J\) 也可以从 \(\mathcal{R}\) 中推导出。特别地，如果任何假设不能相对于 \(\mathcal{R}\) 推导出来，那么判断是空真值。另一种定义 \(J_1, ..., J_n \models_\mathcal{R} J\) 的等价方式是说规则：

\[
J_1 \dots J_n \\
J
\]
（3.5）

相对于 \(\mathcal{R}\) 的规则是可接受的。也就是说，给定任何使用 \(\mathcal{R}\) 中规则推导出的 \(J_1, ..., J_n\)，我们可以使用 \(\mathcal{R}\) 中的规则推导出 \(J\)。

例如，可接受性判断：

\[
\mathsf{succ}(a) \ \mathsf{even} \models_{(2.8)} a \ \mathsf{odd} \tag{3.6}
\]

是有效的，因为从规则 (2.8) 中推导出 \(\mathsf{succ}(a) \ \mathsf{even}\) 的任何推导都必须包含从相同规则中推导出 \(a \ \mathsf{odd}\) 的子推导，这证明了结论。这个事实可以通过对规则 (2.8) 进行归纳证明。判断 (3.6) 的有效性也可以通过表示规则：

\[
\mathsf{succ}(a) \ \mathsf{even} \\
a \ \mathsf{odd}\tag{3.7}
\]

相对于规则 (2.8) 是可接受的来表达。

与可导性不同，可接受性判断在扩展规则时并不稳定。例如，如果我们用公理：

\[
\mathsf{succ(zero)} \ \mathsf{even} \tag{3.8}
\]

扩展规则 (2.8)，则规则 (3.6) 就变得不可接受了，因为没有规则组合可以推导出 \( \mathsf{zero odd}\)。可接受性对归纳定义中缺失或存在的规则都非常敏感。

**定理 3.2** 如果 \(\mathcal{R} \vdash J\)，那么 \(\Gamma \models_\mathcal{R} J\)。

**证明** 通过多次应用可导性的传递性，可以证明如果 \(\mathcal{R} \vdash J\) 并且 \(\mathcal{R} \vdash \Gamma\)，那么 \(\mathcal{R} \vdash J\)。

反例说明了反过来的情况并不成立。例如，\(\mathsf{succ(zero)} \ \mathsf{even} \vdash_{(2.8)} \ \mathsf{zero odd}\) 并不成立，因为在添加 \(\mathsf{succ(zero)} \ \mathsf{even}\) 作为公理时，无法推导出 \(\mathsf{zero odd}\)。然而，相关的可接受性判断：

\[
\mathsf{succ(zero)} \ \mathsf{even} \models_{(2.8)} \ \mathsf{zero odd}
\]

是有效的，因为假设是假的：根据规则 (2.8)，无法推导出 \(\mathsf{succ(zero)} \ \mathsf{even}\)。即便如此，可导性判断

\[
\mathsf{succ(zero) even} \models_{(2.8)} \quad \mathsf{succ(succ(zero)) odd}
\]

是有效的，因为我们可以通过组合规则 (2.8) 从左边推导出右边。

可接受性的证据可以被视为一个数学函数，将假设的推导 \( \delta_1, \dots, \delta_n \) 转化为结论的推导 \( \delta \)。因此，可接受性判断享有与可导性相同的结构性质，因此也是一种假设判断：

- **自反性** 如果 \( J \) 可以从原始规则中推导出，那么 \( J \) 也可以从原始规则中推导出：\( J \models_\mathcal{R} J \)。
- **弱化** 如果在假设每个判断 \( \Delta \) 都可以从这些规则中推导出的前提下 \( J \) 可导，那么在假设 \( \Delta \) 和 \( K \) 都可以从原始规则中推导出的前提下，\( J \) 也必须是可导的：如果 \( \Delta \models_\mathcal{R} J \)，那么 \( \Delta, K \models_\mathcal{R} J \)。
- **传递性** 如果 \( \Delta, K \models_\mathcal{R} J \) 且 \( \Delta \models_\mathcal{R} K \)，那么 \( \Delta \models_\mathcal{R} J \)。如果 \( \Delta \) 中的判断是可导的，那么 \( K \) 也是可导的，因此 \( \Delta, K \) 中的判断也是可导的，进而 \( J \) 也是可导的。

**定理 3.3** 可接受性判断 \( \Delta \models_\mathcal{R} J \) 享有蕴涵的结构性质。

**证明** 这一结论直接来源于可接受性的定义，即假设相对于规则 \( \mathcal{R} \) 是可导的，那么结论也是可导的。

如果一个规则 \( r \) 对于规则集合 \( \mathcal{R} \) 是可接受的，那么 \( \mathcal{R}, r \vdash J \) 等价于 \( \mathcal{R} \vdash J \)。因为如果 \( \mathcal{R} \vdash J \)，那么显然 \( \mathcal{R}, r \vdash J \)，只需忽略 \( r \) 即可。反之，如果 \( \mathcal{R}, r \vdash J \)，那么我们可以用 \( r \) 在 \( \mathcal{R} \) 规则中的展开替代对 \( r \) 的任何使用。通过对 \( \mathcal{R}, r \) 进行规则归纳，可以得出从扩展后的规则集合 \( \mathcal{R}, r \) 推导出的任何推导都可以转化为仅从 \( \mathcal{R} \) 中推导出的推导。因此，如果我们想要证明从 \( \mathcal{R}, r \) 推导出的判断的某一性质，而 \( r \) 对 \( \mathcal{R} \) 是可接受的，只需证明该性质在 \( \mathcal{R} \) 规则下是闭合的即可，因为 \( r \) 的可接受性表明 \( r \) 的结果隐含于 \( \mathcal{R} \) 的结果之中。

#### 假设性归纳定义

!!! todo "暂未修订"

将归纳定义的概念拓展为允许包含推导性判断作为前提和结论的规则是非常有用的。这样做可以让我们引入仅适用于某个特定前提推导过程的局部假设，同时也允许我们在规则应用的点约束基于有效全局假设的推理。

一个假设性归纳定义由以下形式的一组假设性规则组成：

\[
\frac{\Gamma_1 \vdash J_1 \quad \dots \quad \Gamma_n \vdash J_n}{\Gamma \vdash J} \tag{3.9}
\]

其中，\( \Gamma \) 是规则的全局假设，而 \( \Gamma_i \) 是第 \( i \) 个前提的局部假设。非正式地，这条规则表明，当每个 \( J_i \) 都是 \( \Gamma \)，并扩展了对应的局部假设 \( \Gamma_i \) 时，可以从 \( \Gamma \) 推导出 \( J \)。因此，证明 \( J \) 可以从 \( \Gamma \) 推导的方式之一是依次证明每个 \( J_i \) 都可以从 \( \Gamma_i \) 推导出。每个前提的推导涉及一种“上下文切换”，我们在该前提的推导中，将全局假设扩展为包括局部假设。

我们要求假设性归纳定义中的所有规则都是**一致的**，即这些规则在所有全局上下文中都适用。**一致性**确保规则可以以隐含或局部形式呈现：

\[
\frac{J_1 \quad \dots \quad J_n}{J} \tag{3.10}
\]

在这里，全局上下文被隐含忽略，并默认规则适用于任意全局假设的选择。

假设性归纳定义应被视为形式推导判断 \( \Gamma \vdash J \) 的普通归纳定义，推导过程由一组有限的基本判断 \( \Gamma \) 和一个基本判断 \( J \) 构成。一组假设性规则 \( \mathcal{R} \) 定义了最强的形式推导判断，该判断具有结构性并在一致规则 \( \mathcal{R} \) 下封闭。**结构性**意味着形式推导判断必须在以下规则下封闭：

1. \( \Gamma, J \vdash J \) \tag{3.11a}
2. \( \Gamma, K \vdash J \Rightarrow \Gamma \vdash J \) \tag{3.11b}
3. \( \Gamma \vdash K \quad \Gamma, K \vdash J \Rightarrow \Gamma \vdash J \) \tag{3.11c}

这些规则确保形式推导行为像假设性判断一样。我们写作 \( \Gamma \vdash_\mathcal{R} J \) 来表示 \( J \) 是从规则 \( \mathcal{R} \) 中推导出来的。

假设性规则归纳的原则仅是形式假设性推导判断上的规则归纳原则。因此，若要证明 \( \mathcal{P}(\Gamma \vdash J) \)，只需证明 \( \mathcal{P} \) 在规则 \( \mathcal{R} \) 和结构规则下封闭。因此，对于每条形式如 (3.9) 的规则（无论是结构性的还是 \( \mathcal{R} \) 中的），我们必须证明：

如果 \( \mathcal{P}(\Gamma_1 \vdash J_1) \)、……以及 \( \mathcal{P}(\Gamma_n \vdash J_n) \) 成立，那么 \( \mathcal{P}(\Gamma \vdash J) \) 也成立。

但这只是第二章中规则归纳原则的重新表述，专门针对形式推导判断 \( \Gamma \vdash J \)。

在实践中，我们通常通过 3.1.2 节中描述的方法省略结构规则。通过证明结构规则是可接受的，任何基于规则归纳的证明都可以将注意力限制在 \( \mathcal{R} \) 中的规则上。如果假设性归纳定义的所有规则都是一致的，那么结构规则 (3.11b) 和 (3.11c) 显然是可接受的。通常，规则 (3.11a) 必须显式地作为一条规则提出，而不是基于其他规则来证明其可接受性。

#### 一般判断 General Judgments

!!! note "定义：泛化判断、参数化判断"

一般判断编纂了处理判断中的变量的规则。与数学中类似，变量被视为一个**未知量（unknown）**，范围在指定的对象集内。一个**泛化判断（generic judgment）**表明，对于替换判断中指定变量的任何对象，判断都成立。另一种形式的泛化判断编纂了符号参数的处理。一个**参数化判断（parametric judgment）**表示对于指定符号的任何新的重命名，判断都成立。为了跟踪推导中的活动变量和符号，我们写作 \( \Gamma \vdash^\mathcal{U;X}_\mathcal{R} J \)，表示在符号 \( \mathcal{U} \) 和变量 \( \mathcal{X} \) 构成的 abt（抽象绑定树）对象上，\( J \) 可以根据规则 \( \mathcal{R} \) 从 \( \Gamma \) 推导出来。

**规则的一致性（uniformity of a rule）**概念必须扩展，要求规则在变量的重命名和替换下封闭，并且在参数的重命名下封闭。更精确地说，如果 \( \mathcal{R} \) 是包含类型为 \( s \) 的自由变量 \( x \) 的规则集，那么它必须包含所有可能的替换实例，将类型为 \( s \) 的 abt \( a \) 替换为 \( x \)，包括那些包含其他自由变量的 abt。同样，如果 \( \mathcal{R} \) 包含带有参数 \( u \) 的规则，那么它必须包含通过将类型为 \( u \) 的参数重命名为*同类型*的其他 \( u' \) 而获得的所有规则实例。一致性排除了只为某个变量声明规则而不为该变量的所有实例声明规则的情况，也排除了只为某个参数声明规则而不为该参数的所有可能重命名声明规则的情况。

> 规则的一致性表明对于**变量的所有实例、参数的所有可能重命名**都成立。

**泛化可导性（Generic derivability）判断**定义如下：

\[
\mathcal{Y} | \Gamma \vdash^\mathcal{X} _\mathcal{R} J \quad \text{iff} \quad \Gamma \vdash^\mathcal{XY}_\mathcal{R} J
\]

其中，\( \mathcal{Y\cap X} = \emptyset \)。泛化推导的证据由涉及变量 \( \mathcal{XY} \) 的泛化推导 \( \bigtriangledown  \) 构成。只要规则是一致的，选择 \( \mathcal{Y} \) 并无区别，原因将在后面解释。

!!! example

    例如，以下泛化推导：

    \[
    \frac{
        \frac{
            \frac{}{
                x \mathsf{nat}
            }
        }{
            \mathsf{succ}(x) \mathsf{nat}
        }
    }{
        \mathsf{succ}(\mathsf{succ}(x)) \mathsf{nat}
    }
    \]

    可以作为判断 \( x | x\ \mathsf{nat} \vdash^\mathcal{X}_{(2.2)} \quad \mathsf{succ}(\mathsf{succ}(x)) \mathsf{nat} \) 的证据，只要 \( x \notin \mathcal{X} \)。只要所有规则是一致的，其他任何 \( x \) 的选择都同样有效。

只要 \( \mathcal{R} \) 是一致的，泛化推导判断享有以下**结构性质**，这些性质约束了变量的行为：

!!! note "泛化推导的结构性质"

    - **增生（proliferation）**：如果 \( \mathcal{Y} | \Gamma \vdash^\mathcal{X}_\mathcal{R} J \)，那么 \( \mathcal{Y}, y | \Gamma \vdash^\mathcal{X}_\mathcal{R} J \)。
    - **重命名（ranaming）**：如果 \( \mathcal{Y}, y | \Gamma \vdash^\mathcal{X}_\mathcal{R} J \)，那么 \( \mathcal{Y}, y' | [y \leftrightarrow y'] \Gamma \vdash^\mathcal{X}_\mathcal{R} [y \leftrightarrow y'] J \)，对于任意 \( y' \notin \mathcal{XY} \)。
    - **替换（substitution）**：如果 \( \mathcal{Y}, y | \Gamma \vdash^\mathcal{X}_\mathcal{R} J \) 且 \( a \in \mathcal{B}[\mathcal{X}\mathcal{Y}] \)，那么 \( \mathcal{Y} |[a/y] \Gamma \vdash^\mathcal{X}_\mathcal{R} [a/y] J \)。

增生由规则模式的解释保证，它涵盖了宇宙的所有扩展。重命名内置于泛化判断的意义中。替换原则中隐含的是，替换的 abt 与被替换的变量类型相同。

**参数化可导性（parametric derivability）**类似于泛化可导性，只是其泛化对象是符号而非变量。参数化推导定义如下：

$$
\mathcal{V} || \mathcal{Y} \vdash^\mathcal{U; X} _\mathcal{R} J \quad \text{iff} \quad \mathcal{Y}| \Gamma  \vdash^\mathcal{UV; X} _\mathcal{R} J
$$

其中，\( \mathcal{V\cap U}=\emptyset \)。参数化推导的证据由涉及符号 \( \mathcal{V} \) 的推导 \( \bigtriangledown \) 构成。规则 \(\mathcal{R}\) 的一致性确保了参数名称的任意选择都同样有效；推导在重命名下是稳定的。

#### 泛化归纳定义 Generic Inductive Definitions

## 第二部分：静态与动态

### 第四章：静态语义（Statics）

大多数编程语言表现出静态和动态处理阶段之间的**阶段区分**。

- 静态阶段包括解析和类型检查，以确保程序是形式正确的。
- 动态阶段包括形式正确程序的执行。

当形式正确的程序在执行时表现良好时，一种语言被称为**安全的**。静态阶段通过一组用于推导**类型判断**的规则（称为 statics）来指定，这些规则声明表达式在某种类型上是形式正确的。类型通过“预测”程序的组成部分在运行时的某些执行行为的方式来调节这些部分之间的交互，从而确保它们在运行时正确地配合。如果这些预测是正确的，类型安全得以保证；如果不是，则静态语义被认为定义不当，该语言被视为执行时**不安全**。

在本章中，我们介绍一种简单表达式语言 $E$ 的静态语义，作为贯穿本书的分析方法的一个示例。

#### 语法 Syntax

在定义一种语言时，我们主要关注其抽象语法，该语法由一组操作符及其元数（arity）指定。抽象语法提供了语言的系统化、明确的层级结构和绑定结构的描述，并被视为该语言的官方表示。然而，为了清晰起见，通常还需要指定最小的具体语法约定，而无需建立完全精确的语法。

我们通过以下方式完成这两个目的：使用一个**语法表**，并通过示例说明其含义。以下表格总结了 $E$ 的抽象语法和具体语法：

| **抽象语法（Typ 和 Exp）**  | **具体语法** |
|----------------------------|---------------|
| $\text{Typ} \; \tau ::= \text{num}$       | numbers       |
| $\phantom{\text{Typ} \; \tau ::= }\text{str}$       | strings       |
| $\text{Exp} \; e ::= x$       | variable       |
| $\phantom{\text{Exp} \; e ::= }\text{num}[n]$ | numeral        |
| $\phantom{\text{Exp} \; e ::= }\text{str}[s]$ | literal        |
| $\phantom{\text{Exp} \; e ::= }\text{plus}(e_1, e_2)$ | $e_1 + e_2$   |
| $\phantom{\text{Exp} \; e ::= }\text{times}(e_1, e_2)$ | $e_1 \ast e_2$ |
| $\phantom{\text{Exp} \; e ::= }\text{cat}(e_1, e_2)$ | $e_1 \wedge e_2$ |
| $\phantom{\text{Exp} \; e ::= }\text{len}(e)$ | $\|e\|$          |
| $\phantom{\text{Exp} \; e ::= }\text{let}(e_1; x.e_2)$ | $\text{let } x \text{ be } e_1 \text{ in } e_2$ |

此表定义了两种类别：

1. **类型**（Typ），由 $\tau$ 表示。
2. **表达式**（Exp），由 $e$ 表示。

表格定义了一组操作符及其元数。例如，操作符 $\text{let}$ 的元数为 $(\text{Exp}, \text{Exp.Exp})\text{Exp}$，这意味着该操作符有两个属于 $\text{Exp}$ 类型的参数，并且在第二个参数中绑定一个属于 $\text{Exp}$ 类型的变量。

#### 类型系统 Type System

类型系统的作用是对短语的构成施加约束，这些短语对其出现的上下文敏感。例如，表达式 $\text{plus}(x; \text{num}[n])$ 是否合理，取决于变量 $x$ 是否被限制为表达式上下文中 $\text{num}$ 类型。这一示例实际上说明了一般情况：关于表达式上下文的唯一信息是其所在范围内变量的类型。因此，语言 $E$ 的静态语义包括对通用假设判断形式的归纳定义：

\[
\vec{x} \mid \Gamma \vdash e : \tau
\]

其中 $\vec{x}$ 是变量的有限集合，$\Gamma$ 是一个**类型上下文（typing context）**，包含形如 $x : \tau$ 的假设，每个 $x \in \vec{x}$ 都有一个假设。我们依赖于排版约定来确定变量的集合，使用字母 $x$ 和 $y$ 表示它们。我们写作 $x \notin \text{dom}(\Gamma)$ 来表示 $\Gamma$ 中没有关于 $x : \tau$ 的假设（对于任意类型 $\tau$），此时我们说变量 $x$ 对于 $\Gamma$ 是新的。

定义 $E$ 静态语义的规则如下：

\[
\frac{}{\Gamma, x : \tau \vdash x : \tau} \tag{4.1a}
\]

\[
\frac{}{\Gamma \vdash \text{str}[s] : \text{str}} \tag{4.1b}
\]

\[
\frac{}{\Gamma \vdash \text{num}[n] : \text{num}} \tag{4.1c}
\]

\[
\frac{\Gamma \vdash e_1 : \text{num}, \Gamma \vdash e_2 : \text{num}}{\Gamma \vdash \text{plus}(e_1, e_2) : \text{num}} \tag{4.1d}
\]

\[
\frac{\Gamma \vdash e_1 : \text{num}, \Gamma \vdash e_2 : \text{num}}{\Gamma \vdash \text{times}(e_1, e_2) : \text{num}} \tag{4.1e}
\]

\[
\frac{\Gamma \vdash e_1 : \text{str}, \Gamma \vdash e_2 : \text{str}}{\Gamma \vdash \text{cat}(e_1, e_2) : \text{str}} \tag{4.1f}
\]

\[
\frac{\Gamma \vdash e : \text{str}}{\Gamma \vdash \text{len}(e) : \text{num}} \tag{4.1g}
\]

\[
\frac{\Gamma \vdash e_1 : \tau_1 \quad \Gamma, x : \tau_1 \vdash e_2 : \tau_2}{\Gamma \vdash \text{let}(e_1; x.e_2) : \tau_2} \tag{4.1h}
\]

在规则 (4.1h) 中，我们隐式地假设变量 $x$ 未在 $\Gamma$ 中声明。这一条件可通过为 $\text{let}$ 表达式选择合适的 $\alpha$-等价类的表示来满足。

> - 前三条表明在 $\Gamma$ 上下文中，变量 $x$、操作符 $\text{str}$ 和 $\text{num}$ 的类型。
> - 中间四条表明在 $\Gamma$ 上下文中，四种运算的结果的类型。
> - 最后一条表明在 $\Gamma$ 上下文中，如果变量 $x$ 在 $\Gamma$ 中未声明，$e_1$ 的类型是 $\tau_1$，$e_2$ 的类型是 $\tau_2$，那么将 $e_1$ 绑定到 $x$ 后，$e_2$ 的类型不变。

通过对规则 (4.1) 应用类型归纳，可以很容易地检查每个表达式至多有一种类型。

!!! note "引理 4.1（类型唯一性）"
    **引理** 对于任意类型上下文 $\Gamma$ 和表达式 $e$，至多存在一个 $\tau$ 使得 $\Gamma \vdash e : \tau$。

    ---

    **证明** 通过对规则 (4.1) 进行规则归纳，利用变量在任意类型上下文中至多具有一种类型的事实。

类型规则是**语法导向**的，因为每种表达式形式恰好对应一条规则。因此，可以容易地给出类型判断的必要条件，它们是通过反转对应类型规则的充分条件得到的。

!!! note "引理 4.2（类型反推）"
    **引理** 假设 $\Gamma \vdash e : \tau$。如果 $e = \text{plus}(e_1, e_2)$，则 $\tau = \text{num}$，$\Gamma \vdash e_1 : \text{num}$，并且 $\Gamma \vdash e_2 : \text{num}$。对于语言的其他构造形式也是类似的。

    ---

    **证明** 所有这些都可以通过对类型判断 $\Gamma \vdash e : \tau$ 的推导过程进行归纳来证明。

在更复杂的语言中，这种反转原则更难陈述和证明。

#### 结构性质 Structual Properties

静态语义具有通用假设判断的结构属性。

> 回忆：一般假设判断的结构属性有自反性、弱化、传递性。

!!! note "引理 4.3（弱化）"
    **引理** 如果 $\Gamma \vdash e' : \tau'$，那么 $\Gamma, x : \tau \vdash e' : \tau'$，其中 $x \notin \text{dom}(\Gamma)$ 且 $\tau$ 是任意类型。

    ---

    **证明** 通过对 $\Gamma \vdash e' : \tau'$ 的推导过程进行归纳。以下给出规则 (4.1h) 的情况：
    已知 $e' = \text{let}(e_1; z.e_2)$，根据变量约定，可以假设 $z$ 被选为 $z \notin \text{dom}(\Gamma)$ 且 $z \neq x$。通过归纳假设，我们有：

    1. $\Gamma, x : \tau \vdash e_1 : \tau_1$；
    2. $\Gamma, x : \tau, z : \tau_1 \vdash e_2 : \tau'$。
    由规则 (4.1h) 可得结论。

从编程的角度来看，引理 4.3 表明我们可以在任何绑定其自由变量的上下文中使用一个表达式：如果表达式 $e$ 在某上下文 $\Gamma$ 中是类型正确的，那么我们可以将其“导入”到包含假设 $\Gamma$ 的任何上下文中。换句话说，为表达式 $e$ 引入超出其所需的变量不会使 $e$ 无效；它保持良构，且类型不变。

!!! note "引理 4.4（替换）"
    **引理** 如果 $\Gamma, x : \tau \vdash e' : \tau'$ 且 $\Gamma \vdash e : \tau$，那么 $\Gamma \vdash [e/x]e' : \tau'$。

    ---

    **证明** 通过对 $\Gamma, x : \tau \vdash e' : \tau'$ 的推导过程进行归纳。我们同样仅考虑规则 (4.1h) 的情况：
    如前所述，$e' = \text{let}(e_1; z.e_2)$，其中 $z$ 被选为 $z \neq x$ 且 $z \notin \text{dom}(\Gamma)$。通过归纳假设和引理 4.3，我们有：

    1. $\vdash [e/x]e_1 : \tau_1$；
    2. $\Gamma, z : \tau_1 \vdash [e/x]e_2 : \tau'$。
    由于 $z$ 的选择，我们有：
    \[
    [e/x]\text{let}(e_1; z.e_2) = \text{let}([e/x]e_1; z.[e/x]e_2)。
    \]
    由规则 (4.1h) 可得 $\vdash [e/x]\text{let}(e_1; z.e_2) : \tau'$，即得证。

更重要的是，引理 4.4 表达了模块化和链接的重要概念。我们可以将表达式 $e$ 和 $e'$ 视为更大系统中的两个组件，其中 $e'$ 是实现 $e$ 的客户端。客户端声明了一个变量以指定实现的类型，并在仅了解此信息的情况下进行类型检查。实现必须符合客户端的假设类型。如果符合，则可以将它们链接形成复合系统 $[e/x]e'$。该实现本身可能是另一个组件的客户端，用变量 $y$ 表示，并在链接期间被该组件替换。当所有此类变量都被实现后，结果是一个封闭表达式，准备好进行执行（求值）。

!!! note "引理 4.5（分解）"
    **引理** 如果 $\vdash [e/x]e' : \tau'$，那么对于任何类型 $\tau$，只要 $\vdash e : \tau$，就有 $\Gamma, x : \tau \vdash e' : \tau'$。

    ---

    **证明** 表达式 $[e/x]e'$ 的类型仅依赖于 $e$ 的类型（若有出现）。引理 4.5 表明，任何子表达式都可以作为更大系统的单独模块被隔离出来。当变量 $x$ 在 $e'$ 中多次出现时，这一性质尤为有用，因为一个 $e$ 的副本足以满足 $e'$ 中所有 $x$ 的出现。

规则 (4.1) 给出的 $E$ 的静态语义体现了一个重复出现的模式。语言的构造被分类为两种形式：**引入形式（introduction）**和**消解形式（elimination）**。一种类型的引入形式决定了该类型的值或规范形式（canonical form）；消解形式决定了如何操作该类型的值以形成另一种（可能相同）类型的计算。在语言 $E$ 中，类型 $\text{num}$ 的引入形式是数字，类型 $\text{str}$ 的引入形式是字符串字面量。类型 $\text{num}$ 的消解形式是加法和乘法，类型 $\text{str}$ 的消解形式是字符串拼接和求长度。

这种分类的重要性将在第 5 章定义语言的动态语义时变得清晰。届时，我们将看到消解形式是引入形式的逆操作，因为它们“分解”了引入形式“组合”起来的内容。语言静态语义和动态语义的一致性表达了**类型安全**的概念，这是第 6 章的主题。

### 第五章：动态语义 Dynamics

编程语言的**动态语义（dynamics）**描述程序的执行方式。定义编程语言动态语义的最重要方法是 **结构动态方法（structural dynamics）**，通过一个 **转换系统（transition system）** 逐步归纳地指定程序的执行过程。另一种描述动态语义的方法是 **上下文动态方法（contextual dynamics）**，这是结构动态方法的一种变体，其转换规则以稍微不同的方式进行定义。**等式动态方法（equational dynamics）** 通过一组规则定义程序在什么时候在**意义上等价（definitionally equivalent）**，以此呈现编程语言的动态语义。

#### 转换系统 Transition System

一个**转换系统**通过以下四种判断形式进行定义：

1. **\( s \ \mathsf{state} \)**：断言 \( s \) 是转换系统的一个状态。
2. **\( s \ \mathsf{final} \)**：在 \( s \ \mathsf{state} \) 的前提下，断言 \( s \) 是一个终止状态。
3. **\( s \ \mathsf{initial} \)**：在 \( s \ \mathsf{state} \) 的前提下，断言 \( s \) 是一个初始状态。
4. **\( s \longmapsto s' \)**：在 \( s \ \mathsf{state} \) 和 \( s' \ \mathsf{state} \) 的前提下，断言状态 \( s \) 可以转换为状态 \( s' \)。

!!! note "定义：卡住状态、转换系统的确定性和非确定性"

    > 有点像计算理论中的自动机。

在实际使用中，我们通常设置规则，使得从终止状态无法再发生任何转换：如果 \( s \ \mathsf{final} \)，那么不存在状态 \( s' \ \mathsf{state} \) 使得 \( s \longmapsto s' \)。一种无法进行任何转换的状态称为 **卡住状态（stuck）**。虽然按照约定，所有终止状态都是卡住状态，但一个转换系统中可能存在不是终止状态的卡住状态。一个转换系统是 **确定性的（deterministic）**当且仅当：如果对于每个状态 \( s \)，至多存在一个状态 \( s' \) 使得 \( s \longmapsto s' \)；否则，它是 **非确定性的（non-deterministic）**。

!!! note "定义：转换序列、最大序列、完整序列"

一个 **转换序列（transition sequence）**是由一系列状态组成的序列 \( s_0, \dots, s_n \)，满足 \( s_0 \ \mathsf{initial} \)，且对于所有 \( 0 \leq i < n \)，都有 \( s_i \longmapsto s_{i+1} \)。转换序列是 **最大序列（maximal）**当且仅当不存在状态 \( s \) 使得 \( s_n \longmapsto s \)。序列是 **完整序列（complete）**当且仅当它既是最大序列，又有 \( s_n \ \mathsf{final} \)。因此，所有完整序列都是最大序列，但最大序列不一定是完整的。判断 \( s \downarrow \) 表示从状态 \( s \) 开始存在一个完整的转换序列，即存在一个终止状态 \( s' \ \mathsf{final} \)，使得 \( s \longmapsto^* s' \)。

转换判断\( s \longmapsto^* s' \) 的**迭代（iteration）**由下列规则定义：

\[
s \longmapsto^* s \tag{5.1a}
\]

\[
\frac{
s \longmapsto s'\quad s' \longmapsto^*s''
}{
s \longmapsto^* s''
}
\tag{5.1b}
\]

在迭代转换的定义中，规则归纳原则说明，要证明 \(P(s, s')\) 在 \(s \longmapsto^* s'\) 时成立，只需要证明 \(P\) 满足以下两个性质：

1. \(P(s, s)\)。
2. 如果 \(s \longmapsto s'\) 且 \(P(s', s'')\)，则 \(P(s, s'')\)。

第一个要求表明 \(P\) 是 **自反的（reflexive）**。第二个要求表明 \(P\) 在 **头部扩展（head expansion）** 或 **逆向计算（inverse evaluation）** 下是**封闭的（closed）**。利用这一原则，可以轻松证明 \( \longmapsto^* \) 是自反且传递的。

**n 次迭代转换判断** \(s \longmapsto^n s'\)（其中 \(n \geq 0\)）的归纳定义如下：

\[
s \longmapsto^0 s\tag{5.2a}
\]

\[
\frac{
s \longmapsto s'\quad s' \longmapsto^{n} s''
}{
s \longmapsto^{n+1} s''
}
\tag{5.2b}
\]

!!! note "定理 5.1：迭代转换的等价性"

    对于任意状态 \(s\) 和 \(s'\)，有：

    \[
    s \longmapsto^* s' \iff s \longmapsto^k s' \quad \text{对于某个 } k \geq 0
    \]

    ---
    **证明**：

    - **从左到右**：基于多步转换定义进行归纳。
    - **从右到左**：基于 \(k \geq 0\) 进行数学归纳。

#### 结构动态 Structural Dynamics

语言 \(\mathsf{E}\) 的**结构动态（structural dynamics）**通过一个转换系统定义，其中的状态是封闭表达式（closed expressions）。所有状态都是初始状态。终止状态是**封闭值（closed values）**，它们表示完成的计算。判断 \(e \ \mathsf{val}\) 表示 \(e\) 是一个值，其归纳定义如下：

\[
\frac{}{
\mathtt{num}[n] \ \mathsf{val}
}
\tag{5.3a}
\]

\[
\frac{}{
\mathtt{str}[s] \ \mathsf{val}
}
\tag{5.3b}
\]

状态之间的转换判断 \(e \longmapsto e'\) 归纳定义如下：

\[
\frac{
    n_1 + n_2 = n
}{
    \mathtt{plus}(\mathtt{num}[n_1]; \mathtt{num}[n_2]) \longmapsto \mathtt{num}[n]
}
\tag{5.4a}
\]

\[
\frac{
    e_1 \longmapsto e_1'
}{
    \mathtt{plus}(e_1; e_2) \longmapsto \mathtt{plus}(e_1'; e_2)
}
\tag{5.4b}
\]

\[
\frac{
    e_1 \ \mathsf{val} \quad e_2 \longmapsto e_2'
}{
    \mathtt{plus}(e_1; e_2) \longmapsto \mathtt{plus}(e_1; e_2')
}
\tag{5.4c}
\]

\[
\frac{
    s_1 ^\wedge s_2 = s\ \mathsf{str}
}{
    \mathtt{cat}(\mathtt{str}[s_1]; \mathtt{str}[s_2]) \longmapsto \mathtt{str}[s]
}\tag{5.4d}
\]

\[
\frac{
    e_1 \longmapsto e_1'
}{
    \mathtt{cat}(e_1; e_2) \longmapsto \mathtt{cat}(e_1'; e_2)
}\tag{5.4e}
\]

\[
\frac{
    e_1 \ \mathsf{val} \quad e_2 \longmapsto e_2'
}{
    \mathtt{cat}(e_1; e_2) \longmapsto \mathtt{cat}(e_1; e_2')
}\tag{5.4f}
\]

\[
\left[
    \frac{
        e_1 \longmapsto e_1'
    }{
        \mathtt{let}(e_1; x.e_2) \longmapsto \mathtt{let}(e_1'; x.e_2)
    }
\right]\tag{5.4g}
\]

\[
\frac{
    [e_1\ \mathsf{val}]
}{
    \mathtt{let}(e_1; x.e_2) \longmapsto [e_1 / x]e_2
}\tag{5.4h}
\]

文中省略了关于乘法操作和字符串长度计算的规则，因为它们遵循类似的模式。规则 (5.4a)、(5.4d) 和 (5.4h) 是 **指令转换（instruction transitions）**，对应于计算的基本步骤。其余规则是 **搜索转换（search transitions）**，用于确定指令执行的顺序。

!!! note "概念：按值和按名解释"

带括号的规则（bracketed rule） (5.4g) 和规则 (5.4h) 中的括号前提（bracketed premise on rule）适用于**按值（by-value）**的 \(\mathtt{let}\) 解释，而对于**按名（by-name）**的解释则省略。按值解释在将表达式绑定到定义变量之前会对其进行求值，而按名解释会以未求值的形式进行绑定。按值解释在定义变量多次使用时节省计算，但如果未使用变量则浪费计算。相反，按名解释在未使用变量时节省计算，但在多次使用时会浪费计算。

在结构动态中，推导序列具有二维结构，其中序列中的步骤数表示其“宽度”，而每一步的推导树表示其“高度”。

!!! example

    例如，考虑以下求值序列：

    \[
    \begin{align*}
        &\mathtt{let}(\mathtt{plus}(\mathtt{num}[1]; \mathtt{num}[2]); x.\mathtt{plus}(\mathtt{plus}(x; \mathtt{num}[3]); \mathtt{num}[4])) \\
        &\longmapsto \mathtt{let}(\mathtt{num}[3]; x.\mathtt{plus}(\mathtt{plus}(x; \mathtt{num}[3]); \mathtt{num}[4])) \\
        &\longmapsto \mathtt{plus}(\mathtt{plus}(\mathtt{num}[3]; \mathtt{num}[3]); \mathtt{num}[4]) \\
        &\longmapsto \mathtt{plus}(\mathtt{num}[6]; \mathtt{num}[4]) \\
        &\longmapsto \mathtt{num}[10]
    \end{align*}
    \]

    该序列中的每一步转换都可以根据规则 (5.4) 通过推导进行证明。例如，第三次转换可通过以下推导证明：

    \[
    \frac{
        \frac{}{
            \mathtt{plus}(\mathtt{num}[3]; \mathtt{num}[3]) \rightarrow \mathtt{num}[6]
        }\quad(5.4a)
    }{
        \mathtt{plus}(\mathtt{plus}(\mathtt{num}[3]; \mathtt{num}[3]); \mathtt{num}[4]) \rightarrow \mathtt{plus}(\mathtt{num}[6]; \mathtt{num}[4])
    }\quad(5.4b)
    \]

    其他步骤可类似地通过规则组合证明。

\(\mathsf{E}\) 的结构动态中的规则归纳原则表明，要证明 \(\mathcal{P}(e \rightarrow e')\) 在 \(e \rightarrow e'\) 时成立，只需证明 \(\mathcal{P}\) 在规则 (5.4) 下是封闭的。例如，通过规则归纳，可以证明 \(\mathsf{E}\) 的结构动态是**确定的（determinate）**，这意味着一个表达式最多只能转换为另一个表达式。这一证明需要一个简单的引理来将转换与值联系起来：

!!! note "引理 5.2：值的终止性"

    对于任何表达式 \(e\)，不存在 \(e \, \mathsf{val}\) 且 \(e \rightarrow e'\) 对某个 \(e'\) 成立。

    ---

    **证明**：通过对规则 (5.3) 和 (5.4) 进行规则归纳。

!!! note "引理 5.3：确定性"

    如果 \(e \rightarrow e'\) 且 \(e \rightarrow e''\)，那么 \(e'\) 和 \(e''\) 是 \(\alpha\)-等价的。

    ---

    **证明**：通过对 \(e \rightarrow e'\) 和 \(e \rightarrow e''\) 的前提进行规则归纳，无论是同时进行还是依次进行。假设基本运算符（如加法）在作用于值时具有唯一结果。

规则 (5.4) 体现了编程语言设计中的 **反转原则（inversion principle）**，该原则指出语言的消解形式（elimination forms）是其引入形式（introduction forms）的**逆（inverse）**。搜索规则决定了每种消解形式的**主要参数（principal arguments）**，而指令规则指定当所有主要参数处于引入形式时如何计算消解形式。例如，规则 (5.4) 指定了加法的两个参数都是主要参数，并说明当主要参数被计算为数值后如何执行加法。反转原则是确保编程语言定义正确的核心，第 6 章对此进行了详细说明。

#### 上下文动态 Contextual Dynamics

一种名为**上下文动态（contextual dynamics）**的结构化动态变体，有时是有用的。上下文动态和结构化动态之间没有根本的区别，更多的是风格上的差异。其主要思想是将指令步骤隔离为一种特殊形式的判断，称为**指令转换（instruction transition）**，并通过一个称为**评估上下文（evaluation context）**的工具，形式化地确定下一个要执行的指令的位置。定义表达式是否为值的判断 \( e \ \mathsf{val} \) 不变。

指令转换判断 \( e_1 \longmapsto e_2 \) 定义为以下规则，此外，还有类似的规则用于数值的乘法和字符串的长度。

\[
\frac{
    m + n \ \mathsf{is} \ p \ \mathsf{nat}
}{
    \mathsf{plus}(\mathtt{num}[m]; \mathtt{num}[n]) \longmapsto \mathtt{num}[p]
}
\tag{5.5a}
\]

\[
\frac{
    s \hat{t} = u \ \mathsf{str}
}{
    \mathtt{cat}(\mathtt{str}[s]; \mathtt{str}[t]) \longmapsto \mathtt{str}[u]
}
\tag{5.5b}
\]

\[
\frac{}{
    \mathtt{let}(e_1; x.e_2) \longmapsto [e_1/x]e_2
}
\tag{5.5c}
\]

判断 \( \mathcal{E} \ \mathsf{ectxt} \) 确定下一个要执行的指令在更大表达式中的位置。下一个指令步骤的位置通过一个“空洞”（记作 \( \circ \)）来指定，下一条指令将被放入这个空洞中，具体细节我们将在稍后说明。（由于乘法和长度规则处理方式类似，本文省略这些规则。）

\[
\frac{}{
    \circ \ \mathsf{ectxt}
}
\tag{5.6a}
\]

\[
\frac{
    \mathcal{E}_1 \ \mathsf{ectxt}
}{
    \mathtt{plus}(\mathcal{E}_1; e_2) \ \mathsf{ectxt}
}
\tag{5.6b}
\]

\[
\frac{
    e_1 \ \mathsf{val} \quad \mathcal{E}_2 \ \mathsf{ectxt}
}{
    \mathtt{plus}(e_1; \mathcal{E}_2) \ \mathsf{ectxt}
}
\tag{5.6c}
\]

评估上下文的第一个规则指定，下一个指令可以“在这里”发生，即在空洞的位置。其余规则与结构化动态的搜索规则一一对应。例如，规则（5.6c）说明，在表达式 \( \mathtt{plus}(e_1; e_2) \) 中，如果第一个参数 \( e_1 \) 是一个值，那么下一个指令步骤（如果有的话）将位于或位于第二个参数 \( e_2 \) 内部。

评估上下文是一个模板，通过用要执行的指令替换空洞来实例化。判断 \( e' = \mathcal{E}\{e\} \) 表示表达式 \( e' \) 是通过将表达式 \( e \) 填充到评估上下文 \( \mathcal{E} \) 中的空洞得到的结果。该判断通过以下规则进行归纳定义：

\[
\frac{}{
    e = \circ \{e\}
}
\tag{5.7a}
\]

\[
\frac{
    e_1 = \mathcal{E}_1\{e\}
}{
    \mathsf{plus}(e_1; e_2) = \mathsf{plus}(\mathcal{E}_1; e_2)\{e\}
}
\tag{5.7b}
\]

\[
\frac{
    e_1 \ \mathsf{val} \ e_2 = \mathcal{E}_2\{e\}
}{
    \mathtt{plus}(e_1; e_2) = \mathtt{plus}(e_1; \mathcal{E}_2)\{e\}
}
\tag{5.7c}
\]

每个评估上下文形式都有一条规则。用 \( e \) 填充空洞得到 \( e \)；否则，我们根据评估上下文的结构进行归纳。

最后，\(\mathsf{E}\) 的上下文动态由一条规则定义：

\[
\frac{
    e = \mathcal{E}\{e_0\} \quad e_0 \longmapsto e_0'\quad e' = E\{e_0'\}
}{
    e \longmapsto e'
}
\tag{5.8}
\]

因此，从 \( e \) 到 \( e' \) 的转换包括（1）将 \( e \) 分解为评估上下文和指令，（2）执行该指令，（3）用其执行结果替换 \( e \) 中的指令位置，得到 \( e' \)。

结构化动态和上下文动态定义相同的转换关系。为了证明方便，我们用 \( e \longmapsto_s e' \) 表示由结构化动态（规则（5.4））定义的转换关系，用 \( e \longmapsto_c e' \) 表示由上下文动态（规则（5.8））定义的转换关系。

!!! note "定理 5.4"

    \( e \longmapsto_s e' \) 当且仅当 \( e \longmapsto_c e' \)。

    ---

    **证明**

    - 从左到右，按规则（5.4）对规则进行归纳。在每种情况下，足够展示一个评估上下文 \( \mathcal{E} \)，使得 \( e = \mathcal{E}\{e_0\} \)，\( e' = \mathcal{E}\{e_0'\} \)，且 \( e_0 \longmapsto e_0' \)。例如，对于规则（5.4a），取 \( \mathcal{E} = \circ \)，注意 \( e \longmapsto e' \)。对于规则（5.4b），我们通过归纳可以得到存在一个评估上下文 \( \mathcal{E}_1 \)，使得 \( e_1 = \mathcal{E}_1\{e_0\} \)，\( e_1' = \mathcal{E}_1\{e_0'\} \)，且 \( e_0 \longmapsto e_0' \)。取 \( \mathcal{E} = \mathsf{plus}(\mathcal{E}_1; e_2) \)，并注意 \( e = \mathsf{plus}(\mathcal{E}_1; e_2)\{e_0\} \) 和 \( e' = \mathsf{plus}(\mathcal{E}_1; e_2)\{e_0'\} \)，且 \( e_0 \longmapsto e_0' \)。
    - 从右到左，注意如果 \( e \longmapsto_c e' \)，则存在一个评估上下文 \( \mathcal{E} \)，使得 \( e = \mathcal{E}\{e_0\} \)，\( e' = \mathcal{E}\{e_0'\} \)，且 \( e_0 \longmapsto e_0' \)。我们通过规则（5.7）对 \( e \longmapsto_s e' \) 进行归纳证明。例如，对于规则（5.7a），\( e_0 \) 是 \( e \)，\( e_0' \) 是 \( e' \)，且 \( e \longmapsto e' \)，因此 \( e \longmapsto_s e' \)。对于规则（5.7b），我们有 \( \mathcal{E} = \mathsf{plus}(\mathcal{E}_1; e_2) \)，\( e_1 = \mathcal{E}_1\{e_0\} \)，\( e_1' = \mathcal{E}_1\{e_0'\} \)，且 \( e_1 \longmapsto_s e_1' \)。因此，\( e \) 是 \( \mathsf{plus}(e_1; e_2) \)，\( e' \) 是 \( \mathsf{plus}(e_1'; e_2) \)，因此根据规则（5.4b），\( e \longmapsto_s e' \)。

由于两种转换判断相同，上下文动态可以看作是结构化动态的另一种表述。它相较于结构化动态有两个优点，一个相对肤浅，另一个则不那么肤浅。肤浅的优点来自于将规则（5.8）写成更简单的形式：

\[
e_0 \longmapsto e_0'
\quad
\mathcal{E}\{e_0\} \longmapsto \mathcal{E}\{e_0'\}
\tag{5.9}
\]

这种形式在表面上更简单，因为它没有明确表达一个表达式是如何分解成评估上下文和可化简表达式的。上下文动态的更深层次优点在于，所有的转换都是在完整的程序之间进行的。人们永远不需要考虑非可观察类型的表达式之间的转换，这简化了某些论证，例如引理 47.16 的证明。

#### 等式动态 Equational Dynamics

语言动态的另一种表述是将计算视为一种等式推导，风格类似于初等代数。例如，在代数中，我们可以通过简单的计算和重新组织，利用熟悉的加法和乘法定律，展示多项式 \(x^2 + 2x + 1\) 与 \((x + 1)^2\) 是等价的。同样的定律也足以确定给定变量值的任意多项式的值。例如，将 \(x = 2\) 代入多项式 \(x^2 + 2x + 1\)，可以计算得到 \(2^2 + 2 \cdot 2 + 1 = 9\)，这确实等于 \((2 + 1)^2\)。因此，我们得到了一种计算模型，其中多项式的值通过替换和化简确定。

类似的思想引出了表达式语言 \(E\) 中定义性（或计算性）等价的概念，我们将其记为 \(X \mid \Gamma \vdash e \equiv e' : \tau\)，其中 \(\Gamma\) 包含一个形式为 \(x : \tau\) 的假设，针对每个 \(x \in X\)。我们仅考虑类型正确的表达式的定义性等价，因此在考虑判断 \(\Gamma \vdash e \equiv e' : \tau\) 时，隐含假设 \(\Gamma \vdash e : \tau\) 和 \(\Gamma \vdash e' : \tau\)。如常见的那样，当变量 \(X\) 可以从假设 \(\Gamma\) 的形式中推断出来时，我们会省略显式提及。

在 \(E\) 中，通过按名称解释 \(let\) 语法，可以用归纳的方式定义表达式的定义性等价，具体规则如下：

1. \(\Gamma \vdash e \equiv e : \tau\) (5.10a)
2. 如果 \(\Gamma \vdash e' \equiv e : \tau\)，则 \(\Gamma \vdash e \equiv e' : \tau\) (5.10b)
3. 如果 \(\Gamma \vdash e \equiv e' : \tau\) 且 \(\Gamma \vdash e' \equiv e'' : \tau\)，则 \(\Gamma \vdash e \equiv e'' : \tau\) (5.10c)
4. 如果 \(\Gamma \vdash e_1 \equiv e_1' : \text{num}\) 且 \(\Gamma \vdash e_2 \equiv e_2' : \text{num}\)，则 \(\Gamma \vdash \text{plus}(e_1 ; e_2) \equiv \text{plus}(e_1' ; e_2') : \text{num}\) (5.10d)
5. 如果 \(\Gamma \vdash e_1 \equiv e_1' : \text{str}\) 且 \(\Gamma \vdash e_2 \equiv e_2' : \text{str}\)，则 \(\Gamma \vdash \text{cat}(e_1 ; e_2) \equiv \text{cat}(e_1' ; e_2') : \text{str}\) (5.10e)
6. 如果 \(\Gamma \vdash e_1 \equiv e_1' : \tau_1\) 且 \(\Gamma, x : \tau_1 \vdash e_2 \equiv e_2' : \tau_2\)，则 \(\Gamma \vdash \text{let}(e_1 ; x.e_2) \equiv \text{let}(e_1' ; x.e_2') : \tau_2\) (5.10f)
7. 如果 \(n_1 + n_2 = n \in \text{nat}\)，则 \(\text{plus}(\text{num}[n_1] ; \text{num}[n_2]) \equiv \text{num}[n] : \text{num}\) (5.10g)
8. 如果 \(s_1 \wedge s_2 = s \in \text{str}\)，则 \(\text{cat}(\text{str}[s_1] ; \text{str}[s_2]) \equiv \text{str}[s] : \text{str}\) (5.10h)
9. \(\text{let}(e_1 ; x.e_2) \equiv [e_1 / x]e_2 : \tau\) (5.10i)

规则 (5.10a) 到 (5.10c) 表明定义性等价是一个等价关系。规则 (5.10d) 到 (5.10f) 表明它是一个同余关系，即与语言中所有的表达式构造操作相容。规则 (5.10g) 到 (5.10i) 具体说明了 \(E\) 的基本构造的含义。我们认为规则 (5.10) 定义了在规则 (5.10g)、(5.10h) 和 (5.10i) 下封闭的最强同余关系。

规则 (5.10) 足以通过类似于高中代数的推导方法来计算表达式的值。例如，我们可以通过应用规则 (5.10) 推导出以下等式：

\[
\text{let } x = 1 + 2 \text{ in } x + 3 + 4 \equiv 10 : \text{num}
\]

如一般情况一样，可能有多种方法可以推导出同一个等式，但为了进行求值，我们只需找到一种推导方式即可。

定义性等价是相对较弱的，因为许多我们直觉上认为正确的等式无法从规则 (5.10) 推导。例如，一个典型的例子是加法的交换律：

\[
x_1 : \text{num}, x_2 : \text{num}, \quad x_1 + x_2 \equiv x_2 + x_1 : \text{num} \tag{5.11}
\]

直觉上，这表达了加法的交换性。尽管我们在此不加以证明，该等式无法从规则 (5.10) 中推导。然而，我们可以推导出它的所有闭合实例，例如：

\[
n_1 + n_2 \equiv n_2 + n_1 : \text{num} \tag{5.12}
\]

其中 \(n_1, n_2 \in \text{nat}\) 是具体的数字。

一般法则（如式 (5.11)）与其所有实例（如式 (5.12)）之间的“差距”可以通过扩展等价的概念来弥补，包括一种基于数学归纳法的证明原则。这种等价有时被称为**语义等价**，因为它表达了因表达式动态而成立的关系。（语义等价在第 46 章中针对相关语言进行了严格的发展。）

对于表达式语言 \(E\)，关系 \(e \equiv e' : \tau\) 当且仅当存在 \(e_0 \in \text{val}\)，使得 \(e \rightarrow^*e_0\) 且 \(e' \rightarrow^* e_0\)。

**证明**
从右到左的证明是直接的，因为每一步转化都是一个有效的等式。反之，则基于以下更一般的命题（通过对规则 (5.10) 归纳证明）：如果 \(\Gamma \vdash e \equiv e' : \tau\)，并且对于每个 \(1 \leq i \leq n\)，表达式 \(e_i\) 和 \(e_i'\) 都计算为一个共同的值 \(v_i\)，那么存在 \(e_0 \in \text{val}\)，使得：

\[
[e_1, \ldots, e_n / x_1, \ldots, x_n]e \rightarrow^* e_0
\]

并且

\[
[e_1', \ldots, e_n' / x_1, \ldots, x_n]e' \rightarrow^* e_0.
\]

### 第六章：类型安全

大多数编程语言是安全的（或者称为类型安全、强类型）。非正式地，这意味着某些类型的不匹配不会在执行过程中出现。例如，对于语言 \(E\) 的类型安全而言，以下情况不会发生：将一个数字与一个字符串相加，或将两个数字连接起来，这些操作在语义上都是无意义的。

通常，类型安全表示**静态性质**和**动态性质**之间的一致性。静态性质可以看作预测了表达式的值将具有某种形式，从而保证该表达式的动态行为是定义良好的。因此，计算不会“卡死”在某种无可转换的状态下，这在实现中对应于运行时不会出现“非法指令”错误。通过证明每一步转换都保留可类型性，并证明可类型状态是定义良好的，可以证明类型安全。结果是，计算不会“偏离正轨”，因此永远不会遇到非法指令。

对于语言 \(E\)，类型安全可精确定义如下：

---

#### **定理 6.1 （类型安全）**

1. 如果 \(e : \tau\) 且 \(e \rightarrow e'\)，则 \(e' : \tau\)。
2. 如果 \(e : \tau\)，那么 \(e\) 或是一个值 \(e \text{ val}\)，或者存在 \(e'\)，使得 \(e \rightarrow e'\)。

---

第一部分称为**保型性**（Preservation），表明求值步骤保留类型。第二部分称为**前进性**（Progress），确保良类型的表达式要么是值，要么可以进一步求值。类型安全由保型性和前进性共同保证。

如果一个表达式 \(e\) **卡住**（stuck），当且仅当它不是值且不存在 \(e'\) 使得 \(e \rightarrow e'\)。根据类型安全定理，卡住的状态必然是类型错误的。换句话说，良类型的状态不会卡住。

---

### **6.1 保型性**

第4章和第5章定义的语言 \(E\) 的保型性定理通过对转换系统（规则 (5.4)）的归纳证明。

---

#### **定理 6.2 （保型性）**

如果 \(e : \tau\) 且 \(e \rightarrow e'\)，则 \(e' : \tau\)。

**证明**
我们通过两种情况进行证明，其余部分留给读者。首先考虑规则 (5.4b)：

\[
e_1 \rightarrow e_1' \quad \text{则} \quad \text{plus}(e_1 ; e_2) \rightarrow \text{plus}(e_1' ; e_2)
\]

假设 \(\text{plus}(e_1 ; e_2) : \tau\)。根据类型推导的反演（inversion），我们有 \(\tau = \text{num}\)、\(e_1 : \text{num}\)、\(e_2 : \text{num}\)。根据归纳假设，我们得到 \(e_1' : \text{num}\)，因此 \(\text{plus}(e_1' ; e_2) : \text{num}\)。字符串连接的情况类似处理。

接着考虑规则 (5.4h)：

\[
\text{let}(e_1 ; x.e_2) \rightarrow [e_1 / x]e_2
\]

假设 \(\text{let}(e_1 ; x.e_2) : \tau_2\)。根据反演引理 4.2，有 \(e_1 : \tau_1\)，且存在某个 \(\tau_1\) 使得 \(x : \tau_1 \vdash e_2 : \tau_2\)。根据替换引理 4.4，可得 \([e_1 / x]e_2 : \tau_2\)，这就是所需的结论。

可以很容易验证，所有基本操作都是类型保留的。例如，如果 \(a \in \text{nat}\)、\(b \in \text{nat}\) 且 \(a + b = c \in \text{nat}\)，那么 \(c \in \text{nat}\)。

保型性的证明自然以对转换判断的归纳为结构，因为论证依赖于检查给定表达式的所有可能转换。在某些情况下，我们可以通过对 \(e\) 的结构归纳，或通过对类型推导归纳进行证明，但经验表明这往往会导致笨拙的论证，有时甚至完全行不通。

---

### **6.2 前进性**

前进性定理体现了良类型程序不会“卡住”的思想。证明关键依赖于以下引理，该引理描述了每种类型的值的形式。

---

#### **引理 6.3 （规范形式）**

如果 \(e \text{ val}\) 且 \(e : \tau\)，则：

1. 如果 \(\tau = \text{num}\)，那么 \(e = \text{num}[n]\)，其中 \(n\) 是某个数字。
2. 如果 \(\tau = \text{str}\)，那么 \(e = \text{str}[s]\)，其中 \(s\) 是某个字符串。

**证明**
通过对规则 (4.1) 和 (5.3) 的归纳。

---

前进性通过对规则 (4.1)（定义语言静态性质的规则）进行规则归纳来证明。

---

#### **定理 6.4 （前进性）**

如果 \(e : \tau\)，那么 \(e\) 或是一个值 \(e \text{ val}\)，或者存在 \(e'\) 使得 \(e \rightarrow e'\)。

**证明**
通过对类型推导的归纳证明。我们仅考虑以下一种情况，对于规则 (4.1d)：

\[
e_1 : \text{num} \quad e_2 : \text{num} \quad \text{则} \quad \text{plus}(e_1 ; e_2) : \text{num}
\]

这里上下文为空，因为我们仅考虑封闭项。

通过归纳假设，\(e_1\) 要么是值，要么存在 \(e_1'\) 使得 \(e_1 \rightarrow e_1'\)。在后一种情况下，\(\text{plus}(e_1 ; e_2) \rightarrow \text{plus}(e_1' ; e_2)\)，这满足要求。在前一种情况下，同样通过归纳，\(e_2\) 要么是值，要么存在 \(e_2'\) 使得 \(e_2 \rightarrow e_2'\)。在后一种情况下，\(\text{plus}(e_1 ; e_2) \rightarrow \text{plus}(e_1 ; e_2')\)，这满足要求。在前一种情况下，根据规范形式引理 6.3，\(e_1 = \text{num}[n_1]\)，\(e_2 = \text{num}[n_2]\)，因此：

\[
\text{plus}(\text{num}[n_1] ; \text{num}[n_2]) \rightarrow \text{num}[n_1 + n_2]
\]

由于表达式的类型规则是语法指导的，因此可以通过对 \(e\) 的结构归纳来证明前进性定理，在每一步中使用反演定理来刻画 \(e\) 各部分的类型。然而，当类型规则不是语法指导的（即，某种表达式形式有多个规则）时，这种方法就会失效。这种情况下，通过对类型规则归纳的证明方法没有困难。

总结一下，保型性和前进性共同构成了安全性的证明。前进性定理确保良类型的表达式不会“卡住”在定义不明确的状态，而保型性定理确保每一步的结果保持良类型（并且具有相同的类型）。因此，这两个部分协同工作，确保静态性质和动态性质的一致性，且在计算良类型表达式时永远不会遇到定义不明确的状态。

### 第七章：动态类型推导

课内不涉及，略过。

## 第三部分：全函数

> 该部分从表达式中扩展函数的概念。

### 第八章：函数定义和值

在语言 E 中，我们可以执行诸如给定表达式的加倍计算，但我们无法将加倍作为一个概念本身来表达。为了捕捉加倍一个数字的模式，我们使用变量来表示一个固定但未指定的数字，从而表达任意数字的加倍。然后，通过用一个数值表达式替换该变量，可以获得加倍的特定实例。一般来说，一个表达式可能涉及许多不同的变量，因此我们需要指定在特定上下文中哪个变量在变化，从而产生该变量的**函数（function）**。

在本章中，我们将考虑 E 的两个扩展，分别是函数。第一个也是最明显的扩展是将**函数定义**添加到语言中。函数通过将名称绑定到一个带有绑定变量的 abt（抽象绑定树）来定义，该变量作为该函数的参数。通过将特定表达式（具有适当类型）替换绑定变量来应用函数，从而获得一个表达式。

定义函数的域和范围仅限于类型 nat 和 str，因为这些是唯一的表达式类型。这些函数称为**一阶函数（first-order）**，与之相对的是高阶函数，它们允许函数作为其他函数的参数和结果。由于函数的域和范围是类型，这要求我们引入函数类型，其元素是函数。因此，我们可以形成高阶类型的函数，其域和范围本身可能是函数类型。

#### 一阶函数 First-Order Functions

语言 ED 扩展了 E，增加了函数定义和函数应用，如下所示：

!!! note "定义：函数定义（definition）和应用（application）"

    \[
    \begin{aligned}
    \text{Exp} \ e ::= &\text{apply}\{f \}(e) \quad & f (e) \ \text{应用} \\
    &\text{fun}\{\tau_1; \tau_2\}(x_1.e_2; f.e) \quad & \text{fun} \ f (x_1 : \tau_1) : \tau_2 = e_2 \ \text{in} \ e \ \text{定义}
    \end{aligned}
    \]

    表达式 \(\text{fun}\{\tau_1; \tau_2\}(x_1.e_2; f.e)\) 在 \(e\) 中将函数名 \(f\) 绑定到模式 \(x_1.e_2\)，该模式具有参数 \(x_1\) 和定义 \(e_2\)。函数的域和范围分别是类型 \(\tau_1\) 和 \(\tau_2\)。表达式 \(\text{apply}\{f \}(e)\) 用参数 \(e\) 实例化 \(f\) 的绑定。

ED 的静态语义定义了两种形式的判断：

1. 表达式类型判断，\(e : \tau\)，表示 \(e\) 的类型是 \(\tau\)；
2. 函数类型判断，\(f (\tau_1) : \tau_2\)，表示 \(f\) 是一个参数类型为 \(\tau_1\)，结果类型为 \(\tau_2\) 的函数。

判断 \(f (\tau_1) : \tau_2\) 称为 \(f\) 的函数头，它指定了函数的域类型和范围类型。

ED 的静态语义由以下规则定义：

\[
\frac{\Gamma, x_1 : \tau_1 \vdash e_2 : \tau_2 \quad \Gamma, f (\tau_1) : \tau_2 \vdash e : \tau}{\Gamma \vdash \text{fun}\{\tau_1; \tau_2\}(x_1.e_2; f.e) : \tau} \tag{8.1a}
\]

\[
\frac{\Gamma \vdash f (\tau_1) : \tau_2 \quad \Gamma \vdash e : \tau_1}{\Gamma \vdash \text{apply}\{f \}(e) : \tau_2} \tag{8.1b}
\]

函数替换，记作 \([[ x.e/f ]] e'\)，通过对 \(e'\) 的结构进行归纳定义，类似于普通替换。然而，函数名 \(f\) 不代表一个表达式，只能出现在形式为 \(\text{apply}\{f \}(e)\) 的应用中。函数替换由以下规则定义：

\[
\frac{}{
[[ x.e/f ]] \text{apply}\{f \}(e') = \text{let}([[ x.e/f ]] e'; x.e)
} \tag{8.2}
\]

在应用 \(f\) 的位置，带参数 \(e'\) 的函数替换产生一个 \(\text{let}\) 表达式，将 \(x\) 绑定到扩展 \(e'\) 中任何进一步应用 \(f\) 的结果。

!!! note "引理 8.1"
    如果 \(\Gamma, f (\tau_1) : \tau_2 \vdash e : \tau\) 且 \(\Gamma, x_1 : \tau_1 \vdash e_2 : \tau_2\)，则 \(\Gamma \vdash [[ x_1.e_2/f ]] e : \tau\)。

    **证明** 通过对第一个前提进行规则归纳，类似于引理 4.4 的证明。

ED 的动态语义使用函数替换定义：

\[
\text{fun}\{\tau_1; \tau_2\}(x_1.e_2; f.e) \rightarrow [[ x_1.e_2/f ]] e \tag{8.3}
\]

因为函数替换将所有 \(f\) 的应用替换为适当的 \(\text{let}\) 表达式，所以不需要为应用表达式给出规则（本质上，它们在求值期间表现得像变量，而不是语言的原始操作）。

ED 的安全性可以通过高阶函数的安全性定理推导出来，我们将在下一节讨论。

#### 高阶函数 Higher-Order Functions

ED 中变量定义和函数定义之间的相似性是显而易见的。是否可以将它们结合起来？需要弥合的差距是函数与表达式的隔离。

函数名 \( f \) 绑定到一个抽象器 \( x.e \)，指定了一个模式，当 \( f \) 被应用时实例化。为了将函数定义简化为普通定义，我们将抽象器具体化为一种表达式形式，称为 \(\lambda\)-抽象，记作 \(\lambda\{\tau_1\}(x.e)\)。应用推广为 \(\text{ap}(e_1; e_2)\)，其中 \( e_1 \) 是表示函数的表达式，而不仅仅是函数名。 \(\lambda\)-抽象和应用是函数类型 \(\text{arr}(\tau_1; \tau_2)\) 的引入和消解形式，该类型分类了域为 \(\tau_1\) 且范围为 \(\tau_2\) 的函数。

语言 EF 通过以下语法扩展了 E，增加了函数类型：

\[
\begin{aligned}
\text{Typ} \ \tau &::= \text{arr}(\tau_1; \tau_2) \quad \tau_1 \rightarrow \tau_2 \quad \text{函数} \\
\text{Exp} \ e &::= \lambda\{\tau\}(x.e) \quad \lambda (x : \tau) \ e \quad \text{抽象} \\
&\quad \quad \text{ap}(e_1; e_2) \quad e_1(e_2) \quad \text{应用}
\end{aligned}
\]

在 EF 中，函数是一等公民，因为它们是一种可以像其他表达式一样使用的表达式形式。特别地，函数可以作为参数传递给其他函数，也可以作为结果返回。因此，一等函数被称为高阶函数，而不是一阶函数。

EF 的静态语义通过扩展规则 (4.1) 定义如下规则：

\[
\frac{\Gamma, x : \tau_1 \vdash e : \tau_2}{\Gamma \vdash \lambda\{\tau_1\}(x.e) : \text{arr}(\tau_1; \tau_2)} \tag{8.4a}
\]

\[
\frac{\Gamma \vdash e_1 : \text{arr}(\tau_2; \tau) \quad \Gamma \vdash e_2 : \tau_2}{\Gamma \vdash \text{ap}(e_1; e_2) : \tau} \tag{8.4b}
\]

!!! note "引理 8.2（反演）"
    假设 \(\Gamma \vdash e : \tau\)。

    1. 如果 \(e = \lambda\{\tau_1\}(x.e_2)\)，则 \(\tau = \text{arr}(\tau_1; \tau_2)\) 且 \(\Gamma, x : \tau_1 \vdash e_2 : \tau_2\)。
    2. 如果 \(e = \text{ap}(e_1; e_2)\)，则存在 \(\tau_2\)，使得 \(\Gamma \vdash e_1 : \text{arr}(\tau_2; \tau)\) 且 \(\Gamma \vdash e_2 : \tau_2\)。

    **证明** 证明通过对类型规则的规则归纳进行。观察到对于每条规则，恰好有一个情况适用，并且规则的前提提供了所需的结果。

!!! note "引理 8.3（替换）"
    如果 \(\Gamma, x : \tau \vdash e' : \tau'\)，且 \(\Gamma \vdash e : \tau\)，则 \(\Gamma \vdash [e/x]e' : \tau'\)。

    **证明** 通过对第一个判断的推导进行规则归纳。

EF 的动态语义通过以下规则扩展了 E：

\[
\lambda\{\tau\}(x.e) \ \text{val} \tag{8.5a}
\]

\[
\frac{e_1 \rightarrow e_1'}{\text{ap}(e_1; e_2) \rightarrow \text{ap}(e_1'; e_2)} \tag{8.5b}
\]

\[
\frac{e_1 \ \text{val} \quad e_2 \rightarrow e_2'}{\text{ap}(e_1; e_2) \rightarrow \text{ap}(e_1; e_2')} \tag{8.5c}
\]

\[
\frac{e_2 \ \text{val}}{\text{ap}(\lambda\{\tau_2\}(x.e_1); e_2) \rightarrow [e_2/x]e_1} \tag{8.5d}
\]

带括号的规则和前提适用于按值调用的函数应用解释，而不适用于按名调用的解释。

当函数是一等公民时，不需要函数声明：只需将函数声明 \(\text{fun} \ f (x_1 : \tau_1) : \tau_2 = e_2 \ \text{in} \ e\) 替换为定义 \(\text{let} \ \lambda (x : \tau_1) \ e_2 \ \text{be} \ f \ \text{in} \ e\)，并将二等函数应用 \(f (e)\) 替换为一等函数应用 \(f (e)\)。由于 \(\lambda\)-抽象是值，无论定义是按值还是按名求值，这种替换都是有意义的。

然而，使用普通定义，我们可以给部分应用的函数命名，例如：

\[
\text{let} \ k \ \text{be} \ \lambda (x_1 : \text{num}) \ \lambda (x_2 : \text{num}) \ x_1 \ \text{in} \ \text{let} \ \text{kz} \ \text{be} \ k(0) \ \text{in} \ \text{kz}(3) + \text{kz}(5)
\]

没有一等函数，我们甚至无法形成返回函数作为结果的函数 \(k\)，当应用于其第一个参数时。

!!! theorem "定理 8.4（保型性）"
    如果 \(\Gamma \vdash e : \tau\) 且 \(e \rightarrow e'\)，则 \(\Gamma \vdash e' : \tau\)。

    **证明** 证明通过对定义语言动态的规则 (8.5) 进行归纳。考虑规则 (8.5d)：

    \[
    \text{ap}(\lambda\{\tau_2\}(x.e_1); e_2) \rightarrow [e_2/x]e_1
    \]

    假设 \(\text{ap}(\lambda\{\tau_2\}(x.e_1); e_2) : \tau_1\)。根据引理 8.2，我们有 \(e_2 : \tau_2\) 且 \(\Gamma, x : \tau_2 \vdash e_1 : \tau_1\)，因此根据引理 8.3，\([e_2/x]e_1 : \tau_1\)。

    其他应用规则类似处理。

!!! lemma "引理 8.5（规范形式）"
    如果 \(\Gamma \vdash e : \text{arr}(\tau_1; \tau_2)\) 且 \(e \ \text{val}\)，则 \(e = \lambda (x : \tau_1) \ e_2\)，其中 \(x\) 是某个变量，\(e_2\) 是某个表达式，使得 \(\Gamma, x : \tau_1 \vdash e_2 : \tau_2\)。

    **证明** 通过对类型规则进行归纳，使用假设 \(e \ \text{val}\)。

!!! theorem "定理 8.6（前进性）"
    如果 \(\Gamma \vdash e : \tau\)，则 \(e\) 要么是值 \(e \ \text{val}\)，要么存在 \(e'\)，使得 \(e \rightarrow e'\)。

    **证明** 证明通过对规则 (8.4) 进行归纳。注意，由于我们只考虑封闭项，类型推导没有假设。

考虑规则 (8.4b)（按名解释）。通过归纳，\(e_1\) 要么是值，要么存在 \(e_1'\)，使得 \(e_1 \rightarrow e_1'\)。在后一种情况下，我们有 \(\text{ap}(e_1; e_2) \rightarrow \text{ap}(e_1'; e_2)\)。在前一种情况下，根据引理 8.5，我们有 \(e_1 = \lambda\{\tau_2\}(x.e)\)，其中 \(x\) 和 \(e\) 是某个变量和表达式。但此时 \(\text{ap}(e_1; e_2) \rightarrow [e_2/x]e\)。

#### 估值动态与定义等价 Evaluation Dynamics and Definitional Equality

EF 的估值判断 \( e \Downarrow v \) 的归纳定义如下：

\[
\frac{}{
\lambda\{\tau\}(x.e) \Downarrow \lambda\{\tau\}(x.e)
}
\tag{8.6a}
\]

\[
\frac{
e_1 \Downarrow \lambda\{\tau\}(x.e) \quad [e_2/x]e \Downarrow v
}{
\text{ap}(e_1; e_2) \Downarrow v
}
\tag{8.6b}
\]

很容易验证，如果 \( e \Downarrow v \)，则 \( v \ \text{val} \)，并且如果 \( e \ \text{val} \)，则 \( e \Downarrow e \)。

!!! theorem "定理 8.7"
    \( e \Downarrow v \iff e \rightarrow^* v \) 且 \( v \ \text{val} \)。

    ---


    **证明**：在正向证明中，我们通过对规则 (8.6) 进行规则归纳，类似于定理 7.2 的证明。在反向证明中，我们通过对规则 (5.1) 进行规则归纳。证明依赖于引理 7.4 的类似结论，该引理表明估值在逆向执行下是封闭的，这通过对规则 (8.5) 进行归纳证明。

EF 的按名调用动态的定义等价通过扩展规则 (5.10) 定义：

\[
\frac{}{
\text{ap}(\lambda\{\tau\}(x.e_2); e_1) \equiv [e_1/x]e_2 : \tau_2
}
\tag{8.7a}
\]

\[
\frac{
\Gamma \vdash e_1 \equiv e_1' : \tau_2 \rightarrow \tau \quad \Gamma \vdash e_2 \equiv e_2' : \tau_2
}{
\Gamma \vdash \text{ap}(e_1; e_2) \equiv \text{ap}(e_1'; e_2') : \tau
}
\tag{8.7b}
\]

\[
\frac{
\Gamma, x : \tau_1 \vdash e_2 \equiv e_2' : \tau_2
}{
\Gamma \vdash \lambda\{\tau_1\}(x.e_2) \equiv \lambda\{\tau_1\}(x.e_2') : \tau_1 \rightarrow \tau_2
}
\tag{8.7c}
\]

按值调用的定义等价需要更多的机制。主要思想是限制规则 (8.7a) 要求参数是一个值。此外，值必须扩展以包括变量，因为在按值调用中，函数的参数变量代表其参数的值。按值调用的定义等价判断形式为：

\[
\Gamma \vdash e_1 \equiv e_2 : \tau
\]

其中 \(\Gamma\) 包含成对的假设 \(x : \tau, x \ \text{val}\)，表示每个作用域内的变量 \(x\) 的类型和它是一个值。我们写作 \(\Gamma \vdash e \ \text{val}\) 表示在这些假设下 \(e\) 是一个值，因此 \(x : \tau, x \ \text{val} \vdash x \ \text{val}\)。

#### 动态作用域 Dynamic Scope

规则 (8.5) 定义的函数应用动态仅适用于没有自由变量的表达式。当应用一个函数时，参数被替换为参数变量，确保结果仍然是封闭的。此外，由于封闭表达式的替换不会引起捕获，变量的作用域不会被动态打乱，确保了第 1 章中描述的绑定和作用域原则。这种变量处理方式称为静态作用域或静态绑定，以区别于我们现在描述的另一种方法。

另一种方法称为动态作用域或动态绑定，有时被提倡作为静态绑定的替代方案。关键区别在于动态作用域否认了绑定变量重命名的 abt 的同一性原则。因此，避免捕获的替换不可用。相反，估值是为开放项定义的，自由变量的绑定由一个将变量名映射到（可能是开放的）值的环境提供。变量的绑定尽可能晚地确定，在变量被求值时，而不是在它被绑定时。如果环境没有为变量提供绑定，估值会因运行时错误而中止。

对于一阶函数，动态和静态作用域是一致的，但在高阶情况下，两种方法会有所不同。例如，对于表达式 \((\lambda (x : \text{num}) \ x + 7)(42)\) 的求值，静态和动态作用域没有区别。无论是在求值前将 42 替换为函数体中的 \(x\)，还是在 \(x\) 绑定到 42 的情况下求值函数体，结果都是相同的。

在高阶情况下，静态和动态作用域的等价性被打破。例如，考虑表达式：

\[
e \ (\lambda (x : \text{num}) \ \lambda (y : \text{num}) \ x + y)(42)
\]

在静态作用域下，\(e\) 求值为封闭值 \(v = \lambda (y : \text{num}) \ 42 + y\)，如果应用它，会将 42 加到其参数上。无论如何选择绑定变量 \(x\)，结果总是相同的。在动态作用域下，\(e\) 求值为开放值 \(v' = \lambda (y : \text{num}) \ x + y\)，其中变量 \(x\) 是自由的。当这个表达式被求值时，变量 \(x\) 被绑定到 42，但这无关紧要，因为在求值 \(\lambda\)-抽象时不需要这个绑定。\(x\) 的绑定直到 \(v'\) 被应用到一个参数时才被检索，而不是在 \(e\) 被求值时的绑定。

这就是区别所在。例如，考虑表达式：

\[
e' = (\lambda (f : \text{num} \rightarrow \text{num}) \ (\lambda (x : \text{num}) \ f(0))(7))(e)
\]

在动态作用域下，\(e'\) 的值是 7，而在静态作用域下，它的值是 42。差异可以追溯到在 \(e\) 的值（即 \(v'\)）被应用到 0 之前，将 \(x\) 重新绑定到 7，从而改变了结果。

动态作用域违反了变量通过避免捕获的替换赋予意义的基本原则，如第 1 章所定义。违反这一原则至少有两个不良后果。一个是绑定变量的名称变得重要，这与遵循同一性原则的静态作用域相反。例如，如果 \(e'\) 的最内层 \(\lambda\)-抽象绑定变量 \(y\) 而不是 \(x\)，那么它的值将是 42 而不是 7。因此，程序的一个组件可能对另一个组件中选择的绑定变量名称敏感，这是对模块化分解的明显违反。

另一个问题是动态作用域通常不是类型安全的。例如，考虑表达式：

\[
e' = (\lambda (f : \text{num} \rightarrow \text{num}) \ (\lambda (x : \text{str}) \ f("zero"))(7))(e)
\]

在动态作用域下，这个表达式在尝试求值 \(x + y\) 时卡住，因为 \(x\) 被绑定到字符串“zero”，无法进一步求值。因此，动态作用域只被提倡用于所谓的动态类型语言，这些语言通过动态一致性检查来替代静态一致性检查，以确保一种弱形式的前进性。编译时错误因此被转化为运行时错误。

（有关动态类型的更多信息，请参见第 22 章，关于动态作用域的更多信息，请参见第 32 章。）

### 第九章：高阶递归的 $T$ 系统

系统 T，广为人知的 Gödel 的 T，是函数类型与自然数类型的结合。与 E 不同，E 为自然数配备了一些任意选择的算术运算，而语言 T 提供了一种通用机制，称为**原始递归（primitive recursion）**，从中可以定义这些原语。原始递归捕捉了自然数的基本归纳特性，因此可以看作是语言中每个程序的内在终止证明。因此，我们只能在语言中定义**全函数（total function）**，即对于每个参数总是返回值的函数。本质上，T 中的每个程序都“自带”其终止的证明。尽管这似乎是防止无限循环的保护措施，但它也是一种武器，可以用来证明某些程序不能在 T 中编写。要做到这一点，需要为语言中的每个可能程序提供一个主终止证明，而我们将证明这是不存在的。

> 全函数就是对于每个输入都有一个输出的函数。

#### 静态语义 Static

T 的语法由以下文法给出：

\[
\begin{aligned}
\text{Typ} \ \tau &::= \text{nat} \quad \text{nat} \quad \text{自然数} \\
&\quad \quad \text{arr}(\tau_1; \tau_2) \quad \tau_1 \rightarrow \tau_2 \quad \text{函数} \\
\text{Exp} \ e &::= x \quad x \quad \text{变量} \\
&\quad \quad z \quad z \quad \text{零} \\
&\quad \quad s(e) \quad s(e) \quad \text{后继} \\
&\quad \quad \text{rec}\{e_0; x.y.e_1\}(e) \quad \text{rec} \ e \ \{z \rightarrow e_0 \mid s(x) \ \text{with} \ y \rightarrow e_1\} \quad \text{递归} \\
&\quad \quad \text{lam}\{\tau\}(x.e) \quad \lambda (x : \tau) \ e \quad \text{抽象} \\
&\quad \quad \text{ap}(e_1; e_2) \quad e_1(e_2) \quad \text{应用}
\end{aligned}
\]

我们用 \(n\) 表示表达式 \(s(... s(z))\)，其中后继被应用 \(n \geq 0\) 次到零。表达式 \(\text{rec}\{e_0; x.y.e_1\}(e)\) 被称为递归器。它表示从 \(e_0\) 开始的变换 \(x.y.e_1\) 的 \(e\) 次迭代。绑定变量 \(x\) 表示前驱，绑定变量 \(y\) 表示 \(x\) 次迭代的结果。递归器的具体语法中的“with”子句将变量 \(y\) 绑定到递归调用的结果，这一点稍后会变得清晰。

有时，迭代器 \(\text{iter}\{e_0; y.e_1\}(e)\) 被认为是递归器的替代。它与递归器的含义基本相同，只是递归调用的结果绑定到 \(e_1\) 中的 \(y\)，而没有为前驱进行绑定。显然，迭代器是递归器的特例，因为我们总是可以忽略前驱绑定。反之，只要我们有乘积类型（第 10 章），递归器是可以从迭代器定义的。为了从迭代器定义递归器，我们在迭代指定计算时同时计算前驱。

T 的静态语义由以下类型规则给出：

\[
\frac{\Gamma, x : \tau \vdash x : \tau}{\Gamma \vdash x : \tau} \tag{9.1a}
\]

\[
\frac{}{\Gamma \vdash z : \text{nat}} \tag{9.1b}
\]

\[
\frac{\Gamma \vdash e : \text{nat}}{\Gamma \vdash s(e) : \text{nat}} \tag{9.1c}
\]

\[
\frac{\Gamma \vdash e : \text{nat} \quad \Gamma \vdash e_0 : \tau \quad \Gamma, x : \text{nat}, y : \tau \vdash e_1 : \tau}{\Gamma \vdash \text{rec}\{e_0; x.y.e_1\}(e) : \tau} \tag{9.1d}
\]

\[
\frac{\Gamma, x : \tau_1 \vdash e : \tau_2}{\Gamma \vdash \text{lam}\{\tau_1\}(x.e) : \text{arr}(\tau_1; \tau_2)} \tag{9.1e}
\]

\[
\frac{\Gamma \vdash e_1 : \text{arr}(\tau_2; \tau) \quad \Gamma \vdash e_2 : \tau_2}{\Gamma \vdash \text{ap}(e1; e2) : \tau} \tag{9.1f}
\]

和往常一样，结构规则替换的可接受性至关重要。

!!! theorem "引理 9.1"
    如果 \(\Gamma \vdash e : \tau\) 且 \(\Gamma, x : \tau \vdash e' : \tau'\)，则 \(\Gamma \vdash [e/x]e' : \tau'\)。

#### 动态语义 Dynamics

T 的封闭值由以下规则定义：

\[
\frac{}{\text{z} \ \text{val}} \tag{9.2a}
\]

\[
\frac{e \ \text{val}}{\text{s}(e) \ \text{val}} \tag{9.2b}
\]

\[
\frac{}{\text{lam}\{\tau\}(x.e) \ \text{val}} \tag{9.2c}
\]

规则 (9.2b) 的前提包含在急切解释后继的情况下，排除在惰性解释的情况下。

T 的动态转换规则如下：

\[
\frac{e \rightarrow e'}{\text{s}(e) \rightarrow \text{s}(e')} \tag{9.3a}
\]

\[
\frac{e_1 \rightarrow e_1'}{\text{ap}(e_1; e_2) \rightarrow \text{ap}(e_1'; e_2)} \tag{9.3b}
\]

\[
\frac{e_1 \ \text{val} \quad e_2 \rightarrow e_2'}{\text{ap}(e_1; e_2) \rightarrow \text{ap}(e_1; e_2')} \tag{9.3c}
\]

\[
\frac{e_2 \ \text{val}}{\text{ap}(\text{lam}\{\tau\}(x.e); e_2) \rightarrow [e_2/x]e} \tag{9.3d}
\]

\[
\frac{e \rightarrow e'}{\text{rec}\{e_0; x.y.e_1\}(e) \rightarrow \text{rec}\{e_0; x.y.e_1\}(e')} \tag{9.3e}
\]

\[
\frac{}{\text{rec}\{e_0; x.y.e_1\}(\text{z}) \rightarrow e_0} \tag{9.3f}
\]

\[
\frac{\text{s}(e) \ \text{val}}{\text{rec}\{e_0; x.y.e_1\}(\text{s}(e)) \rightarrow [e, \text{rec}\{e_0; x.y.e_1\}(e)/x,y]e_1} \tag{9.3g}
\]

括号中的规则和前提包含在急切后继和按值调用的情况下，排除在惰性后继和按名调用的情况下。规则 (9.3f) 和 (9.3g) 指定了递归器在 \(\text{z}\) 和 \(\text{s}(e)\) 上的行为。在前一种情况下，递归器简化为 \(e_0\)，在后一种情况下，变量 \(x\) 绑定到前驱 \(e\)，变量 \(y\) 绑定到 \(e\) 上的（未求值的）递归。如果在后续计算中不需要 \(y\) 的值，则不会对递归调用进行求值。

!!! note "引理 9.2（规范形式）"
    如果 \(e : \tau\) 且 \(e \ \text{val}\)，则：

    1. 如果 \(\tau = \text{nat}\)，则 \(e = \text{s}(e')\) 对某个 \(e'\) 成立。
    2. 如果 \(\tau = \tau_1 \rightarrow \tau_2\)，则 \(e = \lambda (x : \tau_1) e_2\) 对某个 \(e_2\) 成立。

!!! note "定理 9.3（安全性）"
    1. 如果 \(e : \tau\) 且 \(e \rightarrow e'\)，则 \(e' : \tau\)。
    2. 如果 \(e : \tau\)，则 \(e\) 要么是值 \(e \ \text{val}\)，要么存在 \(e'\)，使得 \(e \rightarrow e'\)。

#### 可定义性 Definability

一个数学函数 \(f : \mathbb{N} \rightarrow \mathbb{N}\) 在 T 中是可定义的，当且仅当存在一个类型为 \(\text{nat} \rightarrow \text{nat}\) 的表达式 \(e_f\)，使得对于每个 \(n \in \mathbb{N}\)，

\[
e_f(n) \equiv f(n) : \text{nat} \tag{9.4}
\]

即，数值函数 \(f : \mathbb{N} \rightarrow \mathbb{N}\) 是可定义的，当且仅当存在一个类型为 \(\text{nat} \rightarrow \text{nat}\) 的表达式 \(e_f\)，使得当应用于表示参数 \(n \in \mathbb{N}\) 的数字时，该应用在定义上等于对应于 \(f(n) \in \mathbb{N}\) 的数字。

T 的定义性等价，记作 \(\vdash e \equiv e' : \tau\)，是包含以下公理的最强同余关系：

\[
\frac{\vdash e_1 : \tau_1 \quad \vdash e_2 : \tau_2}{\vdash \text{ap}(\text{lam}\{\tau_1\}(x.e_2); e_1) \equiv [e_1/x]e_2 : \tau_2} \tag{9.5a}
\]

\[
\frac{\vdash e_0 : \tau \quad \vdash e_1 : \tau}{\vdash \text{rec}\{e_0; x.y.e_1\}(\text{z}) \equiv e_0 : \tau} \tag{9.5b}
\]

\[
\frac{\vdash e_0 : \tau \quad \vdash e_1 : \tau}{\vdash \text{rec}\{e_0; x.y.e_1\}(\text{s}(e)) \equiv [e, \text{rec}\{e_0; x.y.e_1\}(e)/x,y]e_1 : \tau} \tag{9.5c}
\]

例如，倍增函数 \(d(n) = 2 \times n\) 在 T 中由表达式 \(e_d : \text{nat} \rightarrow \text{nat}\) 定义为：

\[
\lambda (x : \text{nat}) \text{rec} \ x \ \{z \rightarrow z \mid s(u) \ \text{with} \ v \rightarrow s(s(v))\}
\]

为了检查这是否定义了倍增函数，我们对 \(n \in \mathbb{N}\) 进行归纳。对于基础情况，很容易检查到：

\[
e_d(0) \equiv 0 : \text{nat}
\]

对于归纳假设，假设：

\[
e_d(n) \equiv d(n) : \text{nat}
\]

然后使用定义性等价规则计算：

\[
e_d(n + 1) \equiv s(s(e_d(n))) \equiv s(s(2 \times n)) = 2 \times (n + 1) = d(n + 1)
\]

作为另一个例子，考虑以下函数，称为 Ackermann 函数，由以下方程定义：

\[
\begin{aligned}
A(0, n) &= n + 1 \\
A(m + 1, 0) &= A(m, 1) \\
A(m + 1, n + 1) &= A(m, A(m + 1, n))
\end{aligned}
\]

Ackermann 函数增长非常快。例如，\(A(4, 2) \approx 265,536\)，这通常被认为比宇宙中的原子数量还多！然而，我们可以通过对参数对 \((m, n)\) 进行字典序归纳来证明 Ackermann 函数是全函数。在每次递归调用中，要么 \(m\) 减少，要么 \(m\) 保持不变且 \(n\) 减少，因此递归调用是良定义的，因此 \(A(m, n)\) 也是良定义的。

一阶原始递归函数是类型为 \(\text{nat} \rightarrow \text{nat}\) 的函数，它使用递归器定义，但不使用任何高阶函数。Ackermann 函数定义为非一阶原始递归函数，但它是高阶原始递归函数。证明它在 T 中是可定义的关键在于注意到 \(A(m + 1, n)\) 迭代 \(n\) 次函数 \(A(m, -)\)，从 \(A(m, 1)\) 开始。作为辅助函数，我们定义高阶函数：

\[
\text{it} : (\text{nat} \rightarrow \text{nat}) \rightarrow \text{nat} \rightarrow \text{nat} \rightarrow \text{nat}
\]

其 \(\lambda\)-抽象为：

\[
\lambda (f : \text{nat} \rightarrow \text{nat}) \lambda (n : \text{nat}) \text{rec} \ n \ \{z \rightarrow \text{id} \mid s( ) \ \text{with} \ g \rightarrow f \circ g\}
\]

其中 \(\text{id} = \lambda (x : \text{nat}) x\) 是恒等函数，\(f \circ g = \lambda (x : \text{nat}) f(g(x))\) 是 \(f\) 和 \(g\) 的复合。很容易检查到：

\[
\text{it}(f)(n)(m) \equiv f(n)(m) : \text{nat}
\]

其中后者表达式是从 \(m\) 开始的 \(f\) 的 \(n\) 次复合。然后我们可以定义 Ackermann 函数：

\[
e_a : \text{nat} \rightarrow \text{nat} \rightarrow \text{nat}
\]

其表达式为：

\[
\lambda (m : \text{nat}) \text{rec} \ m \ \{z \rightarrow s \mid s( ) \ \text{with} \ f \rightarrow \lambda (n : \text{nat}) \text{it}(f)(n)(f(1))\}
\]

检查以下等价关系是有益的：

\[
e_a(0)(n) \equiv s(n) \tag{9.6}
\]

\[
e_a(m + 1)(0) \equiv e_a(m)(1) \tag{9.7}
\]

\[
e_a(m + 1)(n + 1) \equiv e_a(m)(e_a(s(m))(n)) \tag{9.8}
\]

即，Ackermann 函数在 T 中是可定义的。

#### 不可定义性 Undefinability

不可能在 T 中定义一个无限循环。

!!! theorem "定理 9.4"
    如果 $e : \tau$，那么存在 $v \ \text{val}$ 使得 $e \equiv v : \tau$。

    ---

    **证明** 见推论 46.15。

因此，T 中函数类型的值表现得像数学函数：如果 $e : \tau_1 \rightarrow \tau_2$ 且 $e_1 : \tau_1$，那么 $e(e_1)$ 计算为类型 $\tau_2$ 的值。此外，如果 $e : \text{nat}$，那么存在一个自然数 $n$ 使得 $e \equiv n : \text{nat}$。

利用这一点，我们可以使用一种称为对角化的技术，证明存在一些自然数上的函数在 T 中是不可定义的。我们使用一种称为 G\"odel 编号的技术，为 T 的每个闭合表达式分配一个唯一的自然数。通过为每个表达式分配一个唯一的编号，我们可以将表达式作为 T 中的数据值进行操作，从而使 T 能够处理其自身的程序。

G\"odel 编号的本质通过以下对抽象语法树的简单构造来体现。（推广到抽象绑定树稍微复杂一些，主要的复杂性在于确保所有 $\alpha$-等价的表达式被分配相同的 G\"odel 编号。）回忆一个通用的抽象语法树 $a$ 具有形式 $o(a_1, \ldots, a_k)$，其中 $o$ 是一个 $k$ 元算符。枚举这些算符，使得每个算符都有一个索引 $i \in \mathbb{N}$，并且令 $m$ 是 $o$ 在这个枚举中的索引。定义 $a$ 的 G\"odel 编号为：

\[
2^m 3^{n_1} 5^{n_2} \cdots p_k^{n_k}
\]

其中 $p_k$ 是第 $k$ 个素数（因此 $p_0 = 2, p_1 = 3$，依此类推），$n_1, \ldots, n_k$ 分别是 $a_1, \ldots, a_k$ 的 G\"odel 编号。这个过程为每个抽象语法树分配一个自然数。反过来，给定一个自然数 $n$，我们可以应用素数分解定理，将 $n$ 唯一地解析为一个抽象语法树。（如果分解形式不正确，这只能是因为算符的元数与因子的数量不匹配，那么 $n$ 不编码任何抽象语法树。）

现在，使用这种表示，我们可以定义一个（数学）函数 $\text{funiv} : \mathbb{N} \rightarrow \mathbb{N} \rightarrow \mathbb{N}$，使得对于任何 $e : \text{nat} \rightarrow \text{nat}$，$\text{funiv}(e)(m) = n$ 当且仅当 $e(m) \equiv n : \text{nat}$。动态的确定性以及定理 9.4 确保了 $\text{funiv}$ 是一个定义良好的函数。它被称为 T 的通用函数，因为它指定了任何类型为 $\text{nat} \rightarrow \text{nat}$ 的表达式 $e$ 的行为。使用通用函数，我们定义一个辅助数学函数，称为对角函数 $\delta : \mathbb{N} \rightarrow \mathbb{N}$，通过以下方程：

\[
\delta(m) = \text{funiv}(m)(m)
\]

选择 $\delta$ 函数使得 $\delta(e) = n$ 当且仅当 $e(e) \equiv n : \text{nat}$。（其定义的动机稍后会变得清晰。）

$\text{funiv}$ 在 T 中是不可定义的。假设它可以通过表达式 $e_{\text{univ}}$ 定义，那么对角函数 $\delta$ 将通过表达式

\[
e_{\delta} = \lambda (m : \text{nat}) \ e_{\text{univ}}(m)(m)
\]

定义。但在这种情况下，我们将有以下等式：

\[
e_{\delta}(e) \equiv e_{\text{univ}}(e)(e) \equiv e(e)
\]

现在令 $e$ 为函数表达式

\[
\lambda (x : \text{nat}) \ s(e_{\delta}(x))
\]

因此我们可以推导出

\[
e(e) \equiv s(e_{\delta}(e)) \equiv s(e(e))
\]

但终止定理表明存在 $n$ 使得 $e(e) \equiv n$，因此我们有 $n \equiv s(n)$，这是不可能的。

我们说一个语言 $L$ 是通用的，如果可以在 $L$ 中编写 $L$ 的解释器。直观上，$\text{funiv}$ 是可计算的，因为我们可以在某种足够强大的编程语言中定义它。但前面的论证表明 T 无法完成这项任务；它不是一个通用的编程语言。检查上述证明揭示了一个不可避免的权衡：通过坚持所有表达式终止，我们必然失去了通用性——存在一些可计算的函数在该语言中是不可定义的。

#### 高阶递归旁注 Notes

G\"odel (1958) 在研究算术一致性时引入了系统 T (G\"odel, 1980)。G\"odel 展示了如何将算术中的证明“编译”成系统 T 的良类型项，并将算术的一致性问题简化为 T 中程序的终止问题。这可能是第一个在设计上直接受到其程序终止性验证影响的编程语言。

## 第四部分：有限数据类型

### 第十章：乘积类型

二元乘积类型由两个类型的**有序对**组成，每个类型的值按指定顺序排列。相关的消解形式是**投影**，它选择对的第一个和第二个组件。**零元乘积（nullary product）**类型或**单位（unit）**类型仅由唯一的“空元组”组成，没有相关的消解形式。乘积类型可以采用**惰性（lazy）**和**急切（eager）**两种动态语义。根据惰性动态语义，一个对是一个值，而不考虑其组件是否是值；它们在被访问和用于其他计算之前（如果有的话）不会被求值。根据急切动态语义，一个对只有在其组件是值时才是值；它们在对创建时被求值。

更一般地，我们可以考虑有限乘积 \(\langle \tau_i \rangle_{i \in I}\)，由有限索引集 \(I\) 索引。有限乘积类型的元素是 \(I\) 索引的元组，其中第 \(i\) 个组件是类型 \(\tau_i\) 的元素，对于每个 \(i \in I\)。组件通过 \(I\) 索引的投影操作访问，推广了二元情况。有限乘积的特例包括 \(n\) 元组，由形式为 \(I = \{0, \ldots, n-1\}\) 的集合索引，以及标记元组或记录，由有限符号集索引。类似于二元乘积，有限乘积也可以采用急切和惰性解释。

#### 零元和二元乘积 Nullary and Binary Products

乘积的抽象语法由以下语法定义：

\[
\begin{aligned}
\text{Typ} \ \tau &::= \text{unit} \quad \text{unit} \quad \text{nullary product} \\
&\quad \quad \text{prod}(\tau_1; \tau_2) \quad \quad \tau_1 \times \tau_2 \quad \text{binary product} \\
\text{Exp} \ e &::= \quad \text{triv} \quad \langle \rangle \\
    &\quad \quad \text{pair}(e_1; e_2) \quad \langle e_1, e_2 \rangle\\
    &\quad \quad \text{pr}[l](e) \quad e \cdot l \\
    &\quad \quad \text{pr}[r](e) \quad e \cdot r \quad \text{right projection}
\end{aligned}
\]

单位类型没有消解形式，因为没有什么可以从空元组中提取。

乘积类型的静态语义由以下规则定义：

\[
\frac{}{\Gamma \vdash \langle \rangle : \text{unit}} \tag{10.1a}
\]

\[
\frac{\Gamma \vdash e_1 : \tau_1 \quad \Gamma \vdash e_2 : \tau_2}{\Gamma \vdash \langle e_1, e_2 \rangle : \tau_1 \times \tau_2} \tag{10.1b}
\]

\[
\frac{\Gamma \vdash e : \tau_1 \times \tau_2}{\Gamma \vdash e \cdot l : \tau_1} \tag{10.1c}
\]

\[
\frac{\Gamma \vdash e : \tau_1 \times \tau_2}{\Gamma \vdash e \cdot r : \tau_2} \tag{10.1d}
\]

乘积类型的动态语义由以下规则定义：

\[
\frac{}{\langle \rangle \ \text{val}} \tag{10.2a}
\]

\[
\frac{e_1 \ \text{val} \quad e_2 \ \text{val}}{\langle e_1, e_2 \rangle \ \text{val}} \tag{10.2b}
\]

\[
\frac{e_1 \rightarrow e_1'}{\langle e_1, e_2 \rangle \rightarrow \langle e_1', e_2 \rangle} \tag{10.2c}
\]

\[
\frac{e_1 \ \text{val} \quad e_2 \rightarrow e_2'}{\langle e_1, e_2 \rangle \rightarrow \langle e_1, e_2' \rangle} \tag{10.2d}
\]

\[
\frac{e \rightarrow e'}{e \cdot l \rightarrow e' \cdot l} \tag{10.2e}
\]

\[
\frac{e \rightarrow e'}{e \cdot r \rightarrow e' \cdot r} \tag{10.2f}
\]

\[
\frac{e_1 \ \text{val} \quad e_2 \ \text{val}}{\langle e_1, e_2 \rangle \cdot l \rightarrow e_1} \tag{10.2g}
\]

\[
\frac{e_1 \ \text{val} \quad e_2 \ \text{val}}{\langle e_1, e_2 \rangle \cdot r \rightarrow e_2} \tag{10.2h}
\]

括号中的规则和前提在惰性动态语义中省略，在急切动态语义中包含。

安全性定理适用于急切和惰性动态语义，证明过程在每种情况下类似。

!!! theorem "定理 10.1（安全性）"
    1. 如果 \(e : \tau\) 且 \(e \rightarrow e'\)，则 \(e' : \tau\)。
    2. 如果 \(e : \tau\)，则 \(e\) 要么是值 \(e \ \text{val}\)，要么存在 \(e'\)，使得 \(e \rightarrow e'\)。

    ---

    **证明** 保型性通过对规则 (10.2) 定义的转换进行归纳证明。前进性通过对规则 (10.1) 定义的类型进行归纳证明。

#### 有限乘积 Finite Products

有限乘积类型的语法由以下语法定义：

\[
\begin{aligned}
\text{Typ} \ \tau &::= \text{prod}(\{i \rightarrow \tau_i\}_{i \in I}) \quad \langle \tau_i \rangle_{i \in I} \quad \text{乘积} \\
\text{Exp} \ e &::= \text{tpl}(\{i \rightarrow e_i\}_{i \in I}) \quad \langle e_i \rangle_{i \in I} \quad \text{元组} \\
&\quad \quad \text{pr}[i](e) \quad e \cdot i \quad \text{投影}
\end{aligned}
\]

变量 \(I\) 表示一个有限的索引集，用于形成乘积类型。类型 \(\text{prod}(\{i \rightarrow \tau_i\}_{i \in I})\)，或简写为 \(\langle \tau_i \rangle_{i \in I}\)，表示 \(I\) 元组的类型，其中每个 \(i \in I\) 的表达式 \(e_i\) 的类型为 \(\tau_i\)。一个 \(I\) 元组的形式为 \(\text{tpl}(\{i \rightarrow e_i\}_{i \in I})\)，或简写为 \(\langle e_i \rangle_{i \in I}\)，对于每个 \(i \in I\)，从 \(I\) 元组 \(e\) 中的第 \(i\) 个投影写作 \(\text{pr}[i](e)\)，或简写为 \(e \cdot i\)。

当 \(I = \{i_1, \ldots, i_n\}\) 时，\(I\) 元组类型可以写成如下形式：

\[
\langle i_1 \rightarrow \tau_1, \ldots, i_n \rightarrow \tau_n \rangle
\]

我们明确地将每个索引 \(i \in I\) 关联到一个类型。同样地，我们可以写作：

\[
\langle i_1 \rightarrow e_1, \ldots, i_n \rightarrow e_n \rangle
\]

表示第 \(i\) 个组件为 \(e_i\) 的 \(I\) 元组。

通过选择 \(I\) 为空集或二元集合 \(\{l, r\}\)，有限乘积类型推广了空乘积和二元乘积。在实践中，\(I\) 通常选择为一个有限的符号集，这些符号作为元组组件的标签以增强可读性。

有限乘积类型的静态语义由以下规则定义：

\[
\frac{\vdash e_1 : \tau_1 \quad \ldots \quad \vdash e_n : \tau_n}{\vdash \langle i_1 \rightarrow e_1, \ldots, i_n \rightarrow e_n \rangle : \langle i_1 \rightarrow \tau_1, \ldots, i_n \rightarrow \tau_n \rangle} \tag{10.3a}
\]

\[
\frac{\vdash e : \langle i_1 \rightarrow \tau_1, \ldots, i_n \rightarrow \tau_n \rangle}{\vdash e \cdot i_k : \tau_k} \quad (1 \leq k \leq n) \tag{10.3b}
\]

在规则 (10.3b) 中，索引 \(i_k \in I\) 是索引集 \(I\) 的一个特定元素，而在规则 (10.3a) 中，索引 \(i_1, \ldots, i_n\) 遍历整个索引集 \(I\)。

有限乘积类型的动态语义由以下规则定义：

\[
\frac{e_1 \ \text{val} \quad \ldots \quad e_n \ \text{val}}{\langle i_1 \rightarrow e_1, \ldots, i_n \rightarrow e_n \rangle \ \text{val}} \tag{10.4a}
\]

\[
\frac{e_1 \ \text{val} \quad \ldots \quad e_{j-1} \ \text{val} \quad e_j \rightarrow e_j' \quad e_{j+1} = e_{j+1} \quad \ldots \quad e_n = e_n}{\langle i_1 \rightarrow e_1, \ldots, i_n \rightarrow e_n \rangle \rightarrow \langle i_1 \rightarrow e_1, \ldots, i_j \rightarrow e_j', \ldots, i_n \rightarrow e_n \rangle} \tag{10.4b}
\]

\[
\frac{e \rightarrow e'}{e \cdot i \rightarrow e' \cdot i} \tag{10.4c}
\]

\[
\frac{\langle i_1 \rightarrow e_1, \ldots, i_n \rightarrow e_n \rangle \ \text{val}}{\langle i_1 \rightarrow e_1, \ldots, i_n \rightarrow e_n \rangle \cdot i_k \rightarrow e_k} \tag{10.4d}
\]

如所述，规则 (10.4b) 指定元组的组件按某种顺序求值，但未指定组件的具体求值顺序。通过对索引集施加全序并按此顺序求值组件，可以强制求值顺序，但这在技术上有些复杂。

!!! theorem "定理 10.2（安全性）"
    如果 \(e : \tau\)，则 \(e\) 要么是值 \(e \ \text{val}\)，要么存在 \(e'\)，使得 \(e \rightarrow e'\) 并且 \(e' : \tau\)。

    **证明**
    安全性定理分解为前进性和保型性引理，证明方法如第 10.1 节所述。

#### 原始互递归 Primitive Mutual Recursion

使用乘积类型，我们可以简化 T 的原始递归构造，使得只有前驱上的递归结果，而不是前驱本身，被传递给后继分支。将其写为 \(\text{iter}\{e_0; x.e_1\}(e)\)，我们可以定义 \(\text{rec}\{e_0; x.y.e_1\}(e)\) 为 \(e' \cdot r\)，其中 \(e'\) 是表达式 \(\text{iter}\{\langle z, e_0 \rangle; x'.\langle s(x' \cdot l), [x' \cdot r/x]e_1 \rangle\}(e)\)。

其思想是递归地计算数字 \(n\) 和对 \(n\) 的递归调用的结果，从中我们可以计算 \(n + 1\) 和使用 \(e_1\) 的另一次递归的结果。基本情况直接计算为零和 \(e_0\) 的对。很容易检查递归器的静态和动态性质通过此定义得以保留。

我们还可以使用乘积类型实现互递原始递归，其中我们通过原始递归同时定义两个函数。例如，考虑以下递归方程定义的两个自然数上的数学函数：

\[
\begin{aligned}
e(0) &= 1 \\
o(0) &= 0 \\
e(n + 1) &= o(n) \\
o(n + 1) &= e(n)
\end{aligned}
\]

直观上，当且仅当 \(n\) 是偶数时，\(e(n)\) 非零；当且仅当 \(n\) 是奇数时，\(o(n)\) 非零。

为了在扩展了乘积类型的 T 中定义这些函数，我们首先定义一个辅助函数 \(\text{nat} \rightarrow (\text{nat} \times \text{nat})\)，它通过在递归调用中来回交换来同时计算两个结果：

\[
\lambda (n : \text{nat} \times \text{nat}) \ \text{iter} \ n \{z \rightarrow \langle 1, 0 \rangle \mid s(b) \rightarrow \langle b \cdot r, b \cdot l \rangle\}
\]

然后我们可以如下定义 \(e\) 和 \(o\)：

\[
\begin{aligned}
e &= \lambda (n : \text{nat}) \ \text{eeo}(n) \cdot l \\
o &= \lambda (n : \text{nat}) \ \text{eeo}(n) \cdot r
\end{aligned}
\]

#### 乘积类型旁注 Notes

乘积类型是最基本的结构化数据形式。所有语言都有某种形式的乘积类型，但通常与其他可分离的概念结合在一起。常见的乘积表现形式包括：(1) 具有“多个参数”或“多个结果”的函数；(2) 表示为相互递归函数的元组的“对象”；(3) 具有可变组件的元组“结构”。关于有限乘积类型有许多论文，其中记录类型是一个特例。Pierce (2002) 提供了关于记录类型及其子类型属性的详细说明（见第 24 章）。Allen 等人 (2006) 在依赖类型理论框架中分析了许多关键思想。

### 第十一章：和类型

大多数数据结构涉及替代项，例如树中叶子和内部节点之间的区别，或抽象语法的最外层形式中的选择。重要的是，这种选择决定了值的结构。例如，节点有子节点，而叶子没有，等等。这些概念通过和类型（sum types）来表达，特别是二元和（binary sum），它提供了两者之间的选择，以及零元和（nullary sum），它提供了没有选择的情况。有限和（finite sums）将零元和和二元和推广到允许由有限索引集索引的任意数量的情况。与乘积类型一样，和类型也有急切和惰性两种变体，它们在和类型值的定义方式上有所不同。

#### 空和二元和 Nullary and Binary Sums

和类型的抽象语法由以下语法定义：

\[
\begin{aligned}
\text{Typ} \ \tau &::= \text{void} \quad \text{nullary sum} \\
&\quad \quad \text{sum}(\tau_1; \tau_2) \quad \tau_1 + \tau_2 \quad \text{binary sum} \\
\text{Exp} \ e &::= \text{abort}\{\tau\}(e) \quad \text{abort}(e) \quad \text{abort} \\
&\quad \quad \text{in}[l]\{\tau_1; \tau_2\}(e) \quad l \cdot e \quad \text{left injection} \\
&\quad \quad \text{in}[r]\{\tau_1; \tau_2\}(e) \quad r \cdot e \quad \text{right injection} \\
&\quad \quad \text{case}(e; x_1.e_1; x_2.e_2) \quad \text{case} \ e \ \{l \cdot x_1 \rightarrow e_1 \mid r \cdot x_2 \rightarrow e_2\} \quad \text{case analysis}
\end{aligned}
\]

零元和表示零个选择，因此不允许引入形式。消解形式 \(\text{abort}(e)\) 在 \(e\) 计算为一个值时中止计算，但这不可能发生。二元和类型的元素被标记为左或右的加数，分别为 \(l \cdot e\) 或 \(r \cdot e\)。和类型的值通过 case 分析来消解。

和类型的静态语义由以下规则定义：

\[
\frac{\vdash e : \text{void}}{\vdash \text{abort}(e) : \tau} \tag{11.1a}
\]

\[
\frac{\vdash e : \tau_1}{\vdash l \cdot e : \tau_1 + \tau_2} \tag{11.1b}
\]

\[
\frac{\vdash e : \tau_2}{\vdash r \cdot e : \tau_1 + \tau_2} \tag{11.1c}
\]

\[
\frac{\vdash e : \tau_1 + \tau_2 \quad x_1 : \tau_1 \vdash e_1 : \tau \quad x_2 : \tau_2 \vdash e_2 : \tau}{\vdash \text{case} \ e \ \{l \cdot x_1 \rightarrow e_1 \mid r \cdot x_2 \rightarrow e_2\} : \tau} \tag{11.1d}
\]

为了便于阅读，在规则 (11.1b) 和 (11.1c) 中，我们将 \(l \cdot e\) 和 \(r \cdot e\) 写作 \(\text{in}[l]\{\tau_1; \tau_2\}(e)\) 和 \(\text{in}[r]\{\tau_1; \tau_2\}(e)\)，其中显式包含类型 \(\tau_1\) 和 \(\tau_2\)。在规则 (11.1d) 中，case 分析的两个分支必须具有相同的类型。因为类型表达了对表达式值形式的静态“预测”，而和类型的表达式在运行时可能计算为任一形式，我们必须坚持两个分支产生相同的类型。

和类型的动态语义由以下规则定义：

\[
\frac{e \rightarrow e'}{\text{abort}(e) \rightarrow \text{abort}(e')} \tag{11.2a}
\]

\[
\frac{e \ \text{val}}{l \cdot e \ \text{val}} \tag{11.2b}
\]

\[
\frac{e \ \text{val}}{r \cdot e \ \text{val}} \tag{11.2c}
\]

\[
\frac{e \rightarrow e'}{l \cdot e \rightarrow l \cdot e'} \tag{11.2d}
\]

\[
\frac{e \rightarrow e'}{r \cdot e \rightarrow r \cdot e'} \tag{11.2e}
\]

\[
\frac{e \rightarrow e'}{\text{case} \ e \ \{l \cdot x_1 \rightarrow e_1 \mid r \cdot x_2 \rightarrow e_2\} \rightarrow \text{case} \ e' \ \{l \cdot x_1 \rightarrow e_1 \mid r \cdot x_2 \rightarrow e_2\}} \tag{11.2f}
\]

\[
\frac{e \ \text{val}}{\text{case} \ l \cdot e \ \{l \cdot x_1 \rightarrow e_1 \mid r \cdot x_2 \rightarrow e_2\} \rightarrow [e/x_1]e_1} \tag{11.2g}
\]

\[
\frac{e \ \text{val}}{\text{case} \ r \cdot e \ \{l \cdot x_1 \rightarrow e_1 \mid r \cdot x_2 \rightarrow e_2\} \rightarrow [e/x_2]e_2} \tag{11.2h}
\]

括号中的前提和规则包含在急切动态语义中，排除在惰性动态语义中。

静态和动态的一致性如常规方式陈述和证明。

!!! theorem "定理 11.1（安全性）"
    1. 如果 \(e : \tau\) 且 \(e \rightarrow e'\)，则 \(e' : \tau\)。
    2. 如果 \(e : \tau\)，则 \(e\) 要么是值 \(e \ \text{val}\)，要么存在 \(e'\)，使得 \(e \rightarrow e'\)。

    **证明**
    保型性的证明通过对规则 (11.2) 进行归纳，前进性的证明通过对规则 (11.1) 进行归纳。

#### 有限和 Finite Sums

正如我们可以将零元和二元乘积推广到有限乘积一样，我们也可以将零元和二元和推广到有限和。有限和的语法由以下文法定义：

\[
\begin{aligned}
\text{Typ} \ \tau &::= \text{sum}(\{i \rightarrow \tau_i\}_{i \in I}) \quad [\tau_i]_{i \in I} \quad \text{sum} \\
\text{Exp} \ e &::= \text{in}[i]\{\vec{\tau}\}(e) \quad i \cdot e \quad \text{injection} \\
&\quad \quad \text{case}(e; \{i \rightarrow x_i.e_i\}_{i \in I}) \quad \text{case} \ e \ \{i \cdot x_i \rightarrow e_i\}_{i \in I} \quad \text{case analysis}
\end{aligned}
\]

变量 \(I\) 表示一个有限的索引集，用于形成和类型。记号 \(\vec{\tau}\) 表示一个有限函数 \(\{i \rightarrow \tau_i\}_{i \in I}\) 对于某个索引集 \(I\)。类型 \(\text{sum}(\{i \rightarrow \tau_i\}_{i \in I})\)，或简写为 \(\sum_{i \in I} \tau_i\)，表示 \(I\) 分类值的类型，形式为 \(\text{in}[i]\{I\}(e_i)\)，或简写为 \(i \cdot e_i\)，其中 \(i \in I\) 且 \(e_i\) 是类型 \(\tau_i\) 的表达式。一个 \(I\) 分类值通过形式为 \(\text{case}(e; \{i \rightarrow x_i.e_i\}_{i \in I})\) 的 \(I\) 路 case 分析来解析。

当 \(I = \{i_1, \ldots, i_n\}\) 时，\(I\) 分类值的类型可以写成：

\[
[i_1 \rightarrow \tau_1, \ldots, i_n \rightarrow \tau_n]
\]

指定与每个类 \(i \in I\) 关联的类型。相应地，\(I\) 路 case 分析的形式为：

\[
\text{case} \ e \ \{i_1 \cdot x_1 \rightarrow e_1 \mid \ldots \mid i_n \cdot x_n \rightarrow e_n\}
\]

通过选择 \(I\) 为空集或二元集合 \(\{l, r\}\)，有限和推广了空和和二元和。在实践中，\(I\) 通常选择为一个有限的符号集，这些符号作为类的名称以增强可读性。

有限和的静态语义由以下规则定义：

\[
\frac{\vdash e : \tau_k \quad (1 \leq k \leq n)}{\vdash i_k \cdot e : [i_1 \rightarrow \tau_1, \ldots, i_n \rightarrow \tau_n]} \tag{11.3a}
\]

\[
\frac{\vdash e : [i_1 \rightarrow \tau_1, \ldots, i_n \rightarrow \tau_n] \quad x_1 : \tau_1 \vdash e_1 : \tau \quad \ldots \quad x_n : \tau_n \vdash e_n : \tau}{\vdash \text{case} \ e \ \{i_1 \cdot x_1 \rightarrow e_1 \mid \ldots \mid i_n \cdot x_n \rightarrow e_n\} : \tau} \tag{11.3b}
\]

这些规则推广了第 11.1 节中给出的零元和二元和的静态语义。

有限和的动态语义由以下规则定义：

\[
\frac{e \ \text{val}}{i \cdot e \ \text{val}} \tag{11.4a}
\]

\[
\frac{e \rightarrow e'}{i \cdot e \rightarrow i \cdot e'} \tag{11.4b}
\]

\[
\frac{e \rightarrow e'}{\text{case} \ e \ \{i \cdot x_i \rightarrow e_i\}_{i \in I} \rightarrow \text{case} \ e' \ \{i \cdot x_i \rightarrow e_i\}_{i \in I}} \tag{11.4c}
\]

\[
\frac{i \cdot e \ \text{val}}{\text{case} \ i \cdot e \ \{i \cdot x_i \rightarrow e_i\}_{i \in I} \rightarrow [e/x_i]e_i} \tag{11.4d}
\]

这些规则再次推广了第 11.1 节中给出的二元和的动态语义。

!!! theorem "定理 11.2（安全性）"
    如果 \(e : \tau\)，则 \(e\) 要么是值 \(e \ \text{val}\)，要么存在 \(e'\)，使得 \(e \rightarrow e'\) 并且 \(e' : \tau\)。

    **证明**
    证明类似于二元和的情况，如第 11.1 节所述。

#### 和类型的应用

和类型有很多用途，这里我们概述了其中的几种。一旦我们引入了归纳和递归类型（在第六部分和第八部分中介绍），会出现更有趣的例子。

##### 空类型和单位类型

比较单位类型和空类型是很有启发性的，这两者经常被混淆。单位类型有且仅有一个元素 \(\langle \rangle\)，而空类型根本没有元素。因此，如果 \(e : \text{unit}\)，那么如果 \(e\) 计算为一个值，该值就是 \(\langle \rangle\)——换句话说，\(e\) 没有有趣的值。另一方面，如果 \(e : \text{void}\)，那么 \(e\) 必须不能产生一个值；如果它有一个值，它必须是空类型的值，而空类型没有任何值。因此，许多语言中所谓的空类型实际上是单位类型，因为它表示一个表达式没有有趣的值，而不是没有值！

##### 布尔类型

也许最简单的和类型例子是熟悉的布尔类型，其语法由以下文法给出：

\[
\begin{aligned}
\text{Typ} \ \tau &::= \text{bool} \quad \text{布尔类型} \\
\text{Exp} \ e &::= \text{true} \quad \text{真} \\
&\quad \quad \text{false} \quad \text{假} \\
&\quad \quad \text{if}(e; e_1; e_2) \quad \text{if} \ e \ \text{then} \ e_1 \ \text{else} \ e_2 \quad \text{条件表达式}
\end{aligned}
\]

表达式 \(\text{if}(e; e_1; e_2)\) 根据 \(e : \text{bool}\) 的值进行分支。

布尔类型的静态语义由以下类型规则给出：

\[
\frac{}{\vdash \text{true} : \text{bool}} \tag{11.5a}
\]

\[
\frac{}{\vdash \text{false} : \text{bool}} \tag{11.5b}
\]

\[
\frac{\vdash e : \text{bool} \quad \vdash e_1 : \tau \quad \vdash e_2 : \tau}{\vdash \text{if} \ e \ \text{then} \ e_1 \ \text{else} \ e_2 : \tau} \tag{11.5c}
\]

布尔类型的动态语义由以下值和转换规则给出：

\[
\frac{}{\text{true} \ \text{val}} \tag{11.6a}
\]

\[
\frac{}{\text{false} \ \text{val}} \tag{11.6b}
\]

\[
\frac{}{\text{if} \ \text{true} \ \text{then} \ e_1 \ \text{else} \ e_2 \rightarrow e_1} \tag{11.6c}
\]

\[
\frac{}{\text{if} \ \text{false} \ \text{then} \ e_1 \ \text{else} \ e_2 \rightarrow e_2} \tag{11.6d}
\]

\[
\frac{e \rightarrow e'}{\text{if} \ e \ \text{then} \ e_1 \ \text{else} \ e_2 \rightarrow \text{if} \ e' \ \text{then} \ e_1 \ \text{else} \ e_2} \tag{11.6e}
\]

布尔类型可以用二元和和零元乘积来定义：

\[
\text{bool} = \text{unit} + \text{unit}
\tag{11.7a}
\]

\[
\text{true} = l \cdot \langle \rangle
\tag{11.7b}
\]

\[
\text{false} = r \cdot \langle \rangle
\tag{11.7c}
\]

\[
\text{if} \ e \ \text{then} \ e_1 \ \text{else} \ e_2 = \text{case} \ e \ \{l \cdot x_1 \rightarrow e_1 \mid r \cdot x_2 \rightarrow e_2\}
\tag{11.7d}
\]

在等式 (11.7d) 中，变量 \(x_1\) 和 \(x_2\) 是任意选择的，使得 \(x_1 \notin e_1\) 且 \(x_2 \notin e_2\)。很容易检查到这些定义产生了布尔类型的静态和动态语义。

##### 枚举

更一般地，和类型可以用来定义有限枚举类型，即那些值是一个明确给定的有限集合中的一个，并且其消解形式是对该集合元素的 case 分析。例如，类型 suit，其元素是 ♣、♦、♥ 和 ♠，其消解形式为 case 分析：

\[
\text{case} \ e \ \{\clubsuit \rightarrow e_0 \mid \diamondsuit \rightarrow e_1 \mid \heartsuit \rightarrow e_2 \mid \spadesuit \rightarrow e_3\}
\]

这区分了四种花色。这样的有限枚举可以很容易地表示为和类型。例如，我们可以定义

\[
\text{suit} = [\text{unit}]_{\in I}
\]

其中 \(I = \{\clubsuit, \diamondsuit, \heartsuit, \spadesuit\}\)，并且类型族在这个集合上是常量。标记和的 case 分析形式几乎就是给定枚举的所需 case 分析，唯一的区别是与每个加数相关的不重要值的绑定，我们可以忽略它。其他枚举类型的例子比比皆是。例如，大多数语言都有一个字符类型 char，它是一个包含所有可能的 Unicode（或其他标准分类）字符的大型枚举类型。每个字符都被分配了一个代码（如 UTF-8），用于程序之间的交换。类型 char 配备了诸如 \(\text{chcode}(n)\) 这样的操作，它返回与代码 \(n\) 相关的字符，以及 \(\text{codech}(c)\) 返回字符 \(c\) 的代码。使用代码上的线性排序，我们可以定义字符的总排序，称为由该代码确定的排序序列。

##### 可选类型

和类型的另一个用途是定义可选类型，其语法如下：

\[
\begin{aligned}
\text{Typ} \ \tau &::= \text{opt}(\tau) \\
\text{Exp} \ e &::= \text{null} \ \tau \ \text{opt} \quad \text{null} \quad \text{nothing} \\
&\quad \quad \text{just}(e) \quad \text{just}(e) \quad \text{something} \\
&\quad \quad \text{ifnull}\{\tau\}\{e_1; x.e_2\}(e) \quad \text{which} \ e \ \{\text{null} \rightarrow e_1 \mid \text{just}(x) \rightarrow e_2\} \quad \text{null test}
\end{aligned}
\]

类型 \(\text{opt}(\tau)\) 表示类型 \(\tau\) 的“可选”值的类型。引入形式是 \(\text{null}\)，对应于“无值”，以及 \(\text{just}(e)\)，对应于指定的类型 \(\tau\) 的值。消解形式区分这两种可能性。可选类型可以根据以下等式从和类型和零元乘积定义：

\[
\tau \ \text{opt} = \text{unit} + \tau
\tag{11.8a}
\]

\[
\text{null} = l \cdot \langle \rangle
\tag{11.8b}
\]

\[
\text{just}(e) = r \cdot e
\tag{11.8c}
\]

\[
\text{which} \ e \ \{\text{null} \rightarrow e_1 \mid \text{just}(x_2) \rightarrow e_2\} = \text{case} \ e \ \{l \cdot \rightarrow e_1 \mid r \cdot x_2 \rightarrow e_2\}
\tag{11.8d}
\]

我们留给读者检查这些定义所隐含的静态和动态性质。可选类型是理解一个常见误解，即空指针谬误的关键。这个谬误源于两个相关的错误。第一个错误是将某些类型的值视为神秘的实体，称为指针。这种术语源于对这些值在运行时如何表示的假设，而不是它们在语言中的语义角色。第二个错误加剧了第一个错误。一个特定的指针类型值被区分为空指针，它与该类型的其他元素不同，不代表该类型的值，而是拒绝所有使用它的尝试。

为了帮助避免这种失败，这样的语言通常包括一个函数，例如 \(\text{null} : \tau \rightarrow \text{bool}\)，如果其参数为空，则返回 true，否则返回 false。这样的测试允许程序员采取措施避免将 null 用作其声称所属类型的值。因此，程序充满了如下形式的条件语句：

\[
\text{if} \ \text{null}(e) \ \text{then} \ \ldots \ \text{error} \ \ldots \ \text{else} \ \ldots \ \text{proceed} \ \ldots \tag{11.9}
\]

尽管如此，运行时的“空指针”异常仍然猖獗，部分原因是很容易忽略这种测试的需要，部分原因是检测到空指针后除了中止程序外几乎没有其他办法。根本问题在于未能区分类型 \(\tau\) 和类型 \(\tau \ \text{opt}\)。与其将类型 \(\tau\) 的元素视为指针，并因此不得不担心空指针，不如区分类型 \(\tau\) 的真正值和类型 \(\tau\) 的可选值。类型 \(\tau\) 的可选值可能存在也可能不存在，但如果存在，则基础值确实是类型 \(\tau\) 的值（且不能为 null）。可选类型的消解形式，

\[
\text{which} \ e \ \{\text{null} \rightarrow e_{\text{error}} \mid \text{just}(x) \rightarrow e_{\text{ok}}\} \tag{11.10}
\]

通过将类型 \(\tau\) 的真正值绑定到变量 \(x\)，将 \(e\) 存在的信息传播到非 null 分支中。case 分析实现了从“类型 \(\tau\) 的可选值”到“类型 \(\tau\) 的真正值”的类型转换，因此在非 null 分支中不再需要进一步的 null 检查，无论是显式的还是隐式的。注意，这种类型转换不是通过表达式 (11.9) 所示的简单布尔值测试实现的；可选类型的优势正是它们能够实现这种转换。

#### 注释

异构数据结构无处不在。和类型编码了异构性，但很少有语言以这里给出的形式支持它们。在商业语言中，最好的近似是面向对象编程中的类的概念。类是和类型中的一个注入，调度是对数据对象类的 case 分析。（有关这种对应关系的更多信息，请参见第 26 章。）和类型的缺失是 C.A.R. Hoare 自称的“十亿美元错误”——空指针的起源（Hoare, 2009）。糟糕的语言设计将管理“null”值的负担完全放在运行时，而不是在编译时使“null”的可能性或不可能性显而易见。

## 第五部分：类型和提议

### 第十二章：构造逻辑

### 第十三章：经典逻辑

## 第六部分：无限数据类型

### 第十四章：泛型编程

#### 14.1 简介 Introduction

许多程序是在特定情况下模式的实例。有时类型通过一种称为**（类型）泛型（type generic）**编程的技术来确定模式。例如，在第 9 章中，递归自然数是以一种**特殊（ad hoc）**的方式引入的。正如我们将看到的，归纳类型上的递归模式被表示为一个泛型程序。

为了了解这一概念，考虑一个类型为 $\rho \rightarrow \rho'$ 的函数 $f$，它将类型 $\rho$ 的值转换为类型 $\rho'$ 的值。例如，$f$ 可能是自然数的倍增函数。我们希望通过将 $f$ 应用于输入中的各种位置，将类型 $[\rho/t]\tau$ 转换为类型 $[\rho'/t]\tau$，其中类型 $\rho$ 的值出现以获得类型 $\rho'$ 的值，而数据结构的其余部分保持不变。例如，$\tau$ 可能是 $\text{bool} \times t$，在这种情况下，$f$ 可以扩展为类型 $\text{bool} \times \rho \rightarrow \text{bool} \times \rho'$ 的函数，将对 $\langle a, b\rangle$ 发送到对 $\langle a, f(b) \rangle$。

上述示例略过了由于替换的多对一性质而产生的歧义。根据 $\tau$ 中 $t$ 的出现次数的不同，类型可以以多种不同的方式具有形式 $[\rho/t]\tau$。给定如上的 $f$，尚不清楚如何将其扩展为从 $[\rho/t]\tau$ 到 $[\rho'/t]\tau$ 的函数。为了解决这个歧义，我们必须给出一个模板，该模板标记了 $\tau$ 中应用 $f$ 的 $t$ 的出现位置。这样的模板称为**类型算子（type operator）** $t.\tau$，它是一个在类型 $\tau$ 中绑定类型变量 $t$ 的抽象器。给定这样的抽象器，我们可以明确地将 $f$ 扩展到通过在 $\tau$ 中替换 $t$ 给出的实例。

泛型编程的强大功能取决于允许的类型算子。最简单的情况是多项式类型算子，它是由类型的和与积构造的，包括它们的零元形式。这些扩展到正类型算子，还允许某些形式的函数类型。

#### 14.2 多项式类型算子 Polynomial Type Operators

类型算子是一个类型，配备有一个指定的变量，其出现的位置标记了应用转换的位置。类型算子是一个抽象器 $t.\tau$，其中 $t\ \text{type} \vdash \tau\ \text{type}$。例如，一个类型算子是抽象器

$$t.\text{unit} + (\text{bool} \times t)$$

其中 $t$ 的出现标记了应用转换的位置。类型算子 $t.\tau$ 的一个实例是通过在类型 $\tau$ 中用类型 $\rho$ 替换变量 $t$ 获得的。

多项式类型算子是那些由类型变量 $t$、类型 $\text{void}$ 和 $\text{unit}$ 以及乘积和和类型构造器 $\tau_1 \times \tau_2$ 和 $\tau_1 + \tau_2$ 构造的。更准确地说，判断 $t.\tau$ 是多项式类型算子是通过以下规则归纳定义的：

$$
\frac{}{t.t \ \text{poly}} \tag{14.1a}
$$

$$
\frac{}{t.\text{unit} \ \text{poly}} \tag{14.1b}
$$

$$
\frac{t.\tau_1 \ \text{poly} \quad t.\tau_2 \ \text{poly}}{t.\tau_1 \times \tau_2 \ \text{poly}} \tag{14.1c}
$$

$$
\frac{}{t.\text{void} \ \text{poly}} \tag{14.1d}
$$

$$
\frac{t.\tau_1 \ \text{poly} \quad t.\tau_2 \ \text{poly}}{t.\tau_1 + \tau_2 \ \text{poly}} \tag{14.1e}
$$

练习 14.1 要求证明多项式类型算子在替换下是封闭的。

多项式类型算子是描述具有特定类型值槽的数据结构的模板。例如，类型算子 $t.t \times (\text{nat} + t)$ 指定了所有类型 $\rho \times (\text{nat} + \rho)$，对于任何类型 $\rho$ 的选择。因此，多项式类型算子指定了数据结构中具有共同类型的感兴趣点。正如我们将很快看到的，这使我们能够指定一个程序，该程序将给定函数应用于复合数据结构中感兴趣点的所有值，以获得一个新的数据结构，其中包含在这些点应用的结果。由于替换不是单射的，因此无法从其实例中恢复类型算子。例如，如果 $\rho$ 是 $\text{nat}$，则实例将是 $\text{nat} \times (\text{nat} + \text{nat})$；除非我们通过类型算子给出模式，否则不可能知道哪些 $\text{nat}$ 的出现是在指定的位置。

多项式类型算子的泛型扩展是一种具有以下语法的表达式形式：

$$
\text{Exp} \quad e ::= \text{map}\{t.\tau\}(x.e')(e) \quad \text{map}\{t.\tau\}(x.e')(e) \quad \text{generic extension}
$$

其静态语义如下：

$$
\frac{t.\tau \ \text{poly} \quad \Gamma, x : \rho \vdash e' : \rho' \quad \Gamma \vdash e : [\rho/t]\tau}{\Gamma \vdash \text{map}\{t.\tau\}(x.e')(e) : [\rho'/t]\tau} \tag{14.2}
$$

抽象器 $x.e'$ 指定了一个将 $x : \rho$ 映射到 $e' : \rho'$ 的映射。沿着 $x.e'$ 的 $t.\tau$ 的泛型扩展指定了一个从 $[\rho/t]\tau$ 到 $[\rho'/t]\tau$ 的映射。后者的映射将类型 $\rho$ 的值 $v$ 替换为类型 $\rho'$ 的转换值 $[v/x]e'$，在 $\tau$ 中对应于 $t$ 出现的位置。

以下动态语义精确定义了多项式类型算子的泛型扩展的概念：

$$
\text{map}\{t.t\}(x.e')(e) \rightarrow [e/x]e' \tag{14.3a}
$$

$$
\text{map}\{t.\text{unit}\}(x.e')(e) \rightarrow e \tag{14.3b}
$$

$$
\text{map}\{t.\tau_1 \times \tau_2\}(x.e')(e) \rightarrow \langle \text{map}\{t.\tau_1\}(x.e')(e \cdot l), \text{map}\{t.\tau_2\}(x.e')(e \cdot r) \rangle \tag{14.3c}
$$

$$
\text{map}\{t.\text{void}\}(x.e')(e) \rightarrow \text{abort}(e) \tag{14.3d}
$$

$$
\text{map}\{t.\tau_1 + \tau_2\}(x.e')(e) \rightarrow \text{case} \ e \ \{l \cdot x_1 \rightarrow l \cdot \text{map}\{t.\tau_1\}(x.e')(x_1) \mid r \cdot x_2 \rightarrow r \cdot \text{map}\{t.\tau_2\}(x.e')(x_2)\} \tag{14.3e}
$$

规则 (14.3a) 将转换 $x.e'$ 应用于 $e$ 本身，因为算子 $t.t$ 指定了直接执行转换。规则 (14.3b) 表示空元组转换为自身。规则 (14.3c) 表示根据算子 $t.\tau_1 \times \tau_2$ 转换 $e$，$e$ 的第一个组件根据 $t.\tau_1$ 转换，第二个组件根据 $t.\tau_2$ 转换。规则 (14.3d) 表示类型 $\text{void}$ 的值的转换中止，因为没有这样的值。规则 (14.3e) 表示根据 $t.\tau_1 + \tau_2$ 转换 $e$，对 $e$ 进行 case 分析，并在根据 $t.\tau_1$ 或 $t.\tau_2$ 转换注入值后重构它。

考虑类型算子 $t.\tau$，其定义为 $t.\text{unit} + (\text{bool} \times t)$。令 $x.e$ 为抽象器 $x.s(x)$，它递增一个自然数。使用规则 (14.3)，我们可以推导出

$$
\text{map}\{t.\tau\}(x.e)(r \cdot \langle \text{true}, n \rangle) \rightarrow^* r \cdot \langle \text{true}, n + 1 \rangle
$$

对的第二个组件中的自然数被递增，因为类型变量 $t$ 出现在类型算子 $t.\tau$ 的那个位置。

定理 14.1（保型性）。如果 $\text{map}\{t.\tau\}(x.e')(e) : \tau'$ 且 $\text{map}\{t.\tau\}(x.e')(e) \rightarrow e''$，则 $e'' : \tau'$。

证明：通过规则 (14.2) 的反演，我们有：

1. $t$ 是类型，$\tau$ 是类型；
2. 对于某些 $\rho$ 和 $\rho'$，$x : \rho \vdash e' : \rho'$；
3. $e : [\rho/t]\tau$；
4. $\tau'$ 是 $[\rho'/t]\tau$。

证明通过对规则 (14.3) 进行分类。考虑规则 (14.3c)。通过反演，我们得到 $\text{map}\{t.\tau_1\}(x.e')(e \cdot l) : [\rho'/t]\tau_1$，类似地，$\text{map}\{t.\tau_2\}(x.e')(e \cdot r) : [\rho'/t]\tau_2$。很容易检查到

$$
\langle \text{map}\{t.\tau_1\}(x.e')(e \cdot l), \text{map}\{t.\tau_2\}(x.e')(e \cdot r) \rangle
$$

具有类型 $[\rho'/t](\tau_1 \times \tau_2)$，如所需。

### 第十五章：归纳与协归纳类型

归纳类型和协归纳类型是两种重要的递归类型形式。归纳类型对应于某些类型方程的最小（或初始）解，而协归纳类型对应于它们的最大（或最终）解。直观上，归纳类型的元素是通过其引入形式的有限组合给出的。因此，如果我们指定一个函数在归纳类型的每个引入形式上的行为，那么它在该类型的所有值上的行为就被定义了。这样的函数称为递归器，或称为消态映射（catamorphism）。相对地，协归纳类型的元素是那些在其消解形式的有限组合中表现正确的元素。因此，如果我们指定一个元素在每个消解形式上的行为，那么我们就完全指定了该类型的一个值。这样的元素称为生成器，或称为生态映射（anamorphism）。

#### 15.1 激励性的例子 Motivating Examples

## 第七部分：变量类型

### 第十六章：多态类型的 $F$ 系统

### 第十七章：抽象类型

### 第十八章：更高种类

## 第八部分：部分和递归类型

### 第十九章：递归函数的 $PCF$ 系统

### 第二十章：递归类型的 $FPC$ 系统

## 第九部分：动态类型

### 第二十一章：无类型 $\lambda$ 演算

### 第二十二章：动态类型

### 第二十三章：混合类型

## 第十部分：子类型

### 第二十四章：结构化子类型

### 第二十五章：行为类型

## 第十一部分：动态发射

### 第二十六章：类与方法

### 第二十七章：继承

## 第十二部分：控制流

### 第二十八章：控制栈

### 第二十九章：异常

### 第三十章：继续

## 第十三部分：符号数据

### 第三十一章：符号

### 第三十二章：流体绑定

### 第三十三章：动态分类

## 第十四部分：可变状态

### 第三十四章：现代化变星

### 第三十五章：可分配引用

### 第三十六章：懒惰估值

## 第十五部分：并行

### 第三十七章：嵌套并行

### 第三十八章：未来和推测

## 第十六部分：并发和分布式

### 第三十九章：进程演算

### 第四十章：并发变星

### 第四十一章：分布式变星

## 第十七部分：模块

### 第四十二章：模块和链接

### 第四十三章：单身种类和子种类

### 第四十四章：类型抽象和类型类

### 第四十五章：层次和参数化

## 第十八部分：等价证明

### 第四十六章：系统 $T$ 的等价

### 第四十七章：系统 $PCF$ 的等价

### 第四十八章：参数化

### 第四十九章：进程等价
