# 算法与数据结构

<!-- prettier-ignore-start -->
!!! abstract "摘要"

    该篇笔记是多本算法分析教材的笔记合集，包括：

    - 《算法》第四版
    - 《算法导论》第三版
    - 《数据结构与算法分析 C 语言描述》第二版
<!-- prettier-ignore-end -->

因为算法和数据结构有着千丝万缕的联系，我把他们放在一篇笔记，不断向其中整合我所学到的内容。

这篇笔记很长，大致分为以下版块：

1. 相关数学知识
2. 算法分析例
3. 数据结构
4. 算法

## 数学知识

每本算法书都会在开头介绍一些数学知识，这里我也罗列一下方便查找。

### 求和（级数）

算法分析中的求和一般都是对无穷级数求和，这里顺便复习一下数学分析的知识。

- 无穷级数 $\sum_{n=1}^{\infty} x_n$ 是通项 $x_n$ 的和，还定义了部分和数列 $\{S_n\}$。
- 无穷级数收敛的定义是部分和数列收敛。
- 级数的敛散性：
    - 收敛必要条件：通项是无穷小量。（复习：无穷小量指的是极限为 0 的量）
    - 正项级数：
        - 充要条件：部分和数列有上界。
        - 比较判别法。
            - 常用于比较判别法的级数：
                - $p$ 级数：$\sum_{n=1}^{\infty} \frac{1}{n^p}$，$p>1$ 收敛，$p\leq 1$ 发散。
                - 几何级数：$\sum_{n=1}^{\infty} q^n$，$|q|<1$ 收敛，$|q|\geq 1$ 发散。
                - 调和级数：$\sum_{n=1}^{\infty} \frac{1}{n}$ 发散。
- 求和：
    - 等差数列：$S_n = \frac{a_1 + a_n}{2}n$
    - 几何级数：$S_n = \frac{a_1(1-q^n)}{1-q}$，当 $|q|<1$ 时极限为 $\frac{a_1}{1-q}$。
    - 平方和：$S_n = \frac{n(n+1)(2n+1)}{6}$
    - 立方和：$S_n = \frac{n^2(n+1)^2}{4}$

对于函数项级数，目前看到大多数为幂级数，记录如下：

- 幂级数：$\sum_{n=0}^{\infty} a_n x^n$
    - 敛散性判别：
        - 求 $A=\limsup_{n \to \infty} \sqrt[n]{|a_n|}$，收敛半径 $R=\frac{1}{A}$。
        - 当 $|x|<R$ 时，绝对收敛；当 $|x|>R$ 时，发散；当 $|x|=R$ 时，不确定。
    - 和函数求法：
        - 求导：$f'(x)=\sum_{n=1}^{\infty} n a_n x^{n-1}$
        - 积分：$\int f(x) \mathrm{d}x = \sum_{n=0}^{\infty} \frac{a_n}{n+1} x^{n+1} + C$
        - 上面两种方法常常用于产生其他新的级数求和公式，试一试 $\sum_{n=1}^{\infty} kx^{k}$。

无穷乘积基本不会涉及，仅提一个 简单方法：

$$
\lg(\prod_{n=1}^{n} a_k) = \sum_{n=1}^{n} \lg a_n
$$

在近似计算中，我们会用到一些经典结论：

- Stirling 公式，用于估计无穷大量 $\{n!\}$ 的增长阶：$n! \sim \sqrt{2\pi n}(\frac{n}{e})^n (n \to \infty)$
- 调和级数的渐近展开（欧拉常数）：$\sum_{n=1}^{N}\frac{1}{n} = \log N + \gamma + O(\frac{1}{N})$

<!-- prettier-ignore-start -->
!!! tip "调和级数渐近展开的简单推导"

    学习一下调和级数渐近展开的简单推导，我们就能轻松应对如 $\sum_{n=1}^{N}\frac{1}{2n-1}$ 这样的级数求和。

    $$
    \begin{align}
    \sum_{i=1}^{n} \frac{1}{i} &= \sum_{i=1}^{n}\int_{i-1}^{i} \frac{1}{\lfloor x \rfloor} \mathrm{d}x \\
    &= \int_{1}^{n+1} (\frac{1}{x} + \frac{1}{\lfloor x \rfloor} - \frac{1}{x+1}) \mathrm{d}x \\
    &= \int_{1}^{n+1} \frac{1}{x} \mathrm{d}x + \int_{1}^{n+1} (\frac{1}{\lfloor x \rfloor} - \frac{1}{x+1}) \mathrm{d}x \\
    &= \ln(n+1) + \gamma + O(\frac{1}{n})
    \end{align}
    $$
<!-- prettier-ignore-end -->

## 算法分析及例子

## 数据结构

### 线性数据结构

#### 表 List

表常定义下面的方法：

<!-- prettier-ignore-start -->
!!! note "表的常用方法"

    | 方法名 | 作用 |   
    | --- | --- |
    | `Find` | 查找表中是否存在某个元素 |
    | `FindKth` | 查找表中第 $k$ 个元素 |
    | `Insert` | 插入元素 |
    | `Delete` | 删除元素 |
    | `FindPrevious` | 查找某个元素的前驱 |
    | `DeleteKth` | 删除第 $k$ 个元素 |
<!-- prettier-ignore-end -->

表可以使用数组或链表实现：

<!-- prettier-ignore-start -->
!!! note "表的数组实现"

    如果创建的表读取频率远高于插入和删除操作，那么使用数组实现是较好的选择。数组实现的表有以下特点：

    - 需要对表的最大值进行估计。
    - `PrintList` 和 `Find` 以线性时间执行，`FindKth` 常数时间，插入和删除最坏情况为 $O(N)$。
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
!!! note "表的链表实现"

    表一般采用链表实现，这使得插入和删除操作更加灵活。链表实现也有多种变式，我们逐一考虑。

    !!! note "最简单的链表实现中的问题"
    
        问题主要集中在首元素：

        - 删除首元素、向空链表中插入元素、查找首元素的前驱都是特殊情况，需要特殊处理。

    一般会在链表前留出一个节点，称为表头（Header）或哑节点（dummy node）或哨兵。这时，空链表也至少有一个 Node，各种操作都能够与非空链表统一处理。

    为了简化 `FindPrevious` 的实现，我们又引入双向链表（Doubly Linked List）的实现，它在每个节点中都存储了前驱和后继的指针。

    我暂时没有看到循环链表的实际应用。

    在编写表的链表实现时，有一些常见的错误：

    !!! note "链表的常见错误"
    
        - 解引用指针前，没有检验指针所指位置是否有效。

        使用 `ptr != NULL && ptr->Element != x` 这样的检测条件是好习惯。

        - `malloc` 和 `free` 的内存管理
<!-- prettier-ignore-end -->

以下是链表的典型应用：

<!-- prettier-ignore-start -->
??? example "多项式"

    链表常常用于存储多项式。存储时，我们总会使多项式的项按照一定顺序排列，以便进行合并同类项等操作。
    
    编程中，多项式的难点主要在于合并同类项。
<!-- prettier-ignore-end -->

#### 栈 Stack

栈的特点是后进先出（LIFO）。在使用中，我们主要关注栈顶元素。

栈的实现十分灵活，可以使用数组或链表实现。

#### 队列 Queue

队列的特点是先进先出（FIFO）。

队列的实现也十分灵活，可以使用数组或链表实现。

<!-- prettier-ignore-start -->
!!! note "队列的循环数组实现"

    一般实现的要点：

    - 若队列大小为 `size`，则数组大小为 `size + 1`。
    - 两个索引 `front` 和 `end` 分别指向队列头部元素和**尾部元素的一位**。
        - 注意 `end` 上没有元素，这样可以区分队列为空和队列已满的情况。
    - 空队列时，`front == end`；满队列时，`front == (end + 1) % size`。总是有一个位置空余。
    - 实现时，注意对索引取模，模数为数组的大小（想想为什么）。

    留出的一个空位使得空队列和其他情况可以统一处理。如果要利用数组中的所有元素，则需要额外记录队列中元素的个数或设置标记位。

<!-- prettier-ignore-start -->
??? success "队列练习"

    - [处理上溢和下溢](Algorithm/ds/10.1.4_queue_overflow.c)
    - [双向队列](Algorithm/ds/10.1.5_dequeue.c)
<!-- prettier-ignore-end -->

!!! tip "栈和队列的关系"

    有趣的一点：栈和队列可以相互实现。

    ??? note "用双栈实现队列"
    
        假设两个栈分别为 `s1` 和 `s2`。

        有两种经典思路：

        - 常数时间出队：
            - 将所有数据保存在 `s1` 中，其中，队列尾部的元素在栈顶，这样能够立刻出队。
            - 入队时，将 `s1` 中的元素全部出栈并入栈 `s2`，然后将新元素入栈（入队）`s2`，最后将 `s2` 中的元素全部出栈并入栈 `s1`。
        - 常数时间入队：
            - 将所有数据保存在 `s1` 中，其中，队列头部的元素在栈顶，这样能够立刻入队。
            - 出队时，将 `s1` 中的元素全部出栈并入栈 `s2`，然后将 `s2` 顶部的元素出栈（出队），最后将 `s2` 中的元素全部出栈并入栈 `s1`。

        我采用 lazy move 的方式，即只有在需要时才将元素从一个栈移动到另一个栈。假设用于入队的栈为 `input`、出队的栈为 `output`：
        
        - 入队时，检测 `output` 是否为空，如果不为空，将 `output` 中的元素全部出栈并入栈 `input`，然后将新元素入栈 `input`。
            - 这样，如果持续入队，就不需要移动元素。
        - 出队时，检测 `input` 是否为空，如果不为空，将 `input` 中的元素全部出栈并入栈 `output`，然后将 `output` 顶部的元素出栈。
            - 这样，如果持续出队，也不需要移动元素。
        
        此外，还可以使用数据栈和函数调用栈这两个栈来实现队列，该方法摘自 [GeeksForGeeks](https://www.geeksforgeeks.org/queue-using-stacks/)，因其性能受限故不赘述。

        > ```c
        > enQueue(x)
        >   1) Push x to stack1.
        > deQueue:
        >   1) If stack1 is empty then error.
        >   2) If stack1 has only one element then return it.
        >   3) Recursively pop everything from the stack1, store the popped item 
        >     in a variable res,  push the res back to stack1 and return res
        > ```
        > 
        > The step 3 makes sure that the last popped item is always returned and since the recursion stops when there is only one item in stack1 (step 2), we get the last element of stack1 in deQueue() and all other items are pushed back in step 

??? success "队列与栈练习"

    - [双栈实现队列](Algorithm/ds/10.1.6_queue_by_stack.c)
<!-- prettier-ignore-end -->

### 树形数据结构

#### 二叉树 Binary Tree

#### 分支无限制的有根树 

#### 二叉查找树 Binary Search Tree

#### 红黑树 Red-Black Tree

### 高级数据结构

## 算法

### 排序 Sort

#### 比较排序

这一类排序算法都通过**比较元素间的大小**确定它们的次序。任何比较排序算法的最坏情况都需要 $\Omega(N\lg N)$ 的时间，我们来证明一下：

<!-- prettier-ignore-start -->
!!! note "title"

    text
<!-- prettier-ignore-end -->

#### 线性时间排序

<!-- prettier-ignore-start -->
!!! note "桶式排序 Bucket Sort"

    
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
!!! note "基数排序 Radix Sort | 卡式排序 Card Sort"

    
<!-- prettier-ignore-end -->

### 树上的算法

#### 遍历

<!-- prettier-ignore-start -->
!!! note "先序遍历 Preorder Traversal"

    - 先处理节点，再处理儿子。

!!! note "后序遍历 Postorder Traversal"

    - 先处理儿子，再处理节点。
<!-- prettier-ignore-end -->

在二叉树上，可以定义中序遍历：

<!-- prettier-ignore-start -->
!!! note "中序遍历 Inorder Traversal"

    - 先处理左儿子，再处理节点，最后处理右儿子。
<!-- prettier-ignore-end -->