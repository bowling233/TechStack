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

## 算法分析基础

### 算法正确性的证明

<!-- prettier-ignore-start -->
!!! note "循环不变式"

    《算法导论》中提出了“循环不变式”这一概念，类似于数学中的归纳法，用于证明迭代和递归算法的**正确性**。
<!-- prettier-ignore-end -->

### 算法复杂度的分析

在算法分析中，我们往往只关注**最坏情况运行时间**。“平均情况”往往较难定义，对于特定问题，“平均输入”的构成也不一定明显。我们会学习到“随机化算法”，使得算法可以使用概率论分析，产生期望运行时间。

<!-- prettier-ignore-start -->
!!! note "记号"

    - $O$：大 $O$ 记号，表示上界。
    - $\Omega$：大 $\Omega$ 记号，表示下界。
    - $\Theta$：大 $\Theta$ 记号，表示紧界。
    - $o$：小 $o$ 记号，表示严格上界。
    - $\omega$：小 $\omega$ 记号，表示严格下界。

!!! note "主方法：求解分治算法"

    《算法导论》中介绍了三种求解递归式（分治策略）的方法：代入法（猜测）、递归树法（简单的递推式）和主方法。主方法最为通用。

    主方法求解递归式 $T(n)=a(T(n/b))+f(n)$。其中，$a\geq 1$ 表示子问题的个数，$b>1$ 表示子问题的规模，$f(n)>0$ 表示除去子问题的代价。

    1. 若对某个常数 $\epsilon>0$，有 $f(n)=O(n^{\log_b a-\epsilon})$，则 $T(n)=\Theta(n^{\log_b a})$。
    2. 若 $f(n)=\Theta(n^{\log_b a})$，则 $T(n)=\Theta(n^{\log_b a}\lg n)$。
    3. 若对某个常数 $\epsilon>0$，有 $f(n)=\Omega(n^{\log_b a+\epsilon})$，且对某个常数 $c<1$ 和所有足够大的 $n$，有 $af(n/b)\leq cf(n)$，则 $T(n)=\Theta(f(n))$。

    上面的分析定义很严谨，但是看起来很难理解。其实只需要求解 $\frac{f(n)}{n^{\log_b a}}$ 的极限即可。如果该极限是 $\lg n$ 等小于 $n^\epsilon$ 的低阶量，则无法应用主方法。

<!-- prettier-ignore-end -->


### 复杂度分析的例子

这里罗列了一些无法归类到某一类算法的小问题。

<!-- prettier-ignore-start -->
!!! note "3-sum"

    问题：从 $N$ 个数中找出 3 个和为 $0$ 的整数元组的数量。

    解法：

    - 首先对数组进行归并排序（$O(N\lg N)$）。
    - 对每对元素 $a_i$ 和 $a_j$（$N(N-1)/2$ 次），使用二分查找（$O(\lg N)$）在数组中查找 $-(a_i+a_j)$。

    该解法的复杂度为 $N^2\lg N$。3-sum 问题的最优解可能是平方级别的，目前还没有发现。
<!-- prettier-ignore-end -->


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
    - 两个索引 `front` 和 `end` 分别指向队列头部元素和**尾部元素的后一位**。
        - 注意 `end` 上没有元素，这样可以区分队列为空和队列已满的情况。
    - 空队列时，`front == end`；满队列时，`front == (end + 1) % size`。总是有一个位置空余。
    - 实现时，注意对索引取模，模数为数组的大小（想想为什么）。

    留出的一个空位使得空队列和其他情况可以统一处理。如果要利用数组中的所有元素，则需要额外记录队列中元素的个数或设置标记位。

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

#### （二叉）堆

（二叉）堆是一个近似完全的二叉树。除了最底层外，该树是完全充满的，且从左向右填充。

堆采用数组实现。堆包含两个属性：该数组的大小 `length` 和堆中元素的数量 `heap_size`。

堆的父子节点

## 算法

### 排序 Sort

#### 比较排序

这一类排序算法都通过**比较元素间的大小**确定它们的次序。任何比较排序算法的最坏情况都需要 $\Omega(N\lg N)$ 的时间，我们来证明一下：

<!-- prettier-ignore-start -->
!!! note "归并排序"

    典型的归并排序实现由两个子程序组成：

    - `MERGE(A, p, q, r)`：将两个有序数组 `A[p..q]` 和 `A[q+1..r]` 合并为一个有序数组 `A[p..r]`。
    - `MERGE-SORT(A, p, r)`：将数组 `A[p..r]` 排序。

    `MERGE-SORT` 负责递归地将数组分成两半，直到只剩下一个元素，然后调用 `MERGE` 合并两个有序数组。

    ```title="MERGE-SORT(A, p, r)"
    if p<r
        q = (p+r)/2
        MERGE-SORT(A, p, q)
        MERGE-SORT(A, q+1, r)
        MERGE(A, p, q, r)
    ```

    `MERGE` 有多种实现方式：

    - 《算法导论》将两个子数组拷贝出去，然后在两个数组上进行比较，将较小的元素放入原数组中。两个拷贝后的新子数组尾部设置了哨兵，避免在比较时检查数组是否为空。

    !!! note "复杂度"

        归并排序的递推式为：$T(n)=2T(n/2)+cn$，画出递归树很容易知道总代价为 $cn\lg n+cn=O(n\lg n)$。

    !!! note "优化"

        - 小数组插入排序：当子数组长度较小时，可以使用插入排序代替归并排序，这样可以减少递归的深度。
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

### 动态规划

<!-- prettier-ignore-start -->
!!! note "最大子数组问题"

    最大子数组问题的最优解法是动态规划。

    !!! note "分治解法"

        最大子数组要么在左半边，要么在右半边，要么跨越中点。前两种情况可以递归求解，第三种情况可以在 $O(n)$ 时间内求解，即分别寻找形如 $A[i..mid]$ 和 $A[mid+1..j]$ 的最大子数组，然后合并。
    
        从上面的分析可知：最大子数组问题的分治解法的时间复杂度为 $T(n)=2T(n/2)+O(n)$，即 $O(n\lg n)$。
<!-- prettier-ignore-end -->

## 图

几个概念：

-   顶点的**度数**、路径、简单路径（无重复顶点）、环、简单环（无重复顶点和边）、长度
-   连通、子图、连通分量
-   密度、稀疏图、稠密图
-   二分图

### 无向图

无向图有两种特殊情况，我们不做考虑：自环和平行边。

我们仅考虑简单的路径和环。

<!-- prettier-ignore-start -->
!!! note "生成树"

    树是无环连通图。互不相连的树成为森林。

    连通图的生成树是它的一幅子图，它含有图中所有顶点，且是一棵树。图的生成树森林是它的所有连通子图的生成树的集合。

!!! note "树的数学性质"

    一幅含有 $V$ 个节点的图满足下面的任意条件时，它是一棵树：

    - 有 $V-1$ 条边，且不含有环。
    - 有 $V-1$ 条边，且是连通的。
    - 连通，但删除任意一条边都会使它不连通。
    - 无环，但添加任意一条边都会产生环。
    - 任意两个顶点之间都有且仅有一条简单路径。
<!-- prettier-ignore-end -->

#### 无向图的表示

API：添加边、查询相邻顶点、字符串表示。

通过上面的 API 可以进行下列操作：

- 计算度数
- 计算图的度数
- **计算自环的个数**
- 邻接表表示

有三种数据结构可选：

- 邻接矩阵（太大）
- 边的数组（存储边的信息）
- 邻接表数组

如果需要进行添加、删除节点、删除边、检查是否含有边等操作，可以进一步使用**邻接集**的表示方法。会造成一定性能损失。

#### 连通性

连通性可以用并查集算法处理。对每条边执行 `union()` 操作。

深度优先搜索更常用于图的处理。

## 案例

### union-find 动态连通性

输入：一列整数对，表示整数对之间的连通性。

目标：去除能被前面的整数对连通的整数对。

#### 定义问题

- `union(p, q)`：将 `p` 和 `q` 连通。
- `find(p)`：返回 `p` 所在的连通分量的标识符。
- `connected(p, q)`：判断 `p` 和 `q` 是否在同一个连通分量中。
- `count()`：返回连通分量的数量。

#### 实现

##### quick-find

简单想法：使用数组 `id[]` 存储每个整数对所在的连通分量的标识符。这样，`connected(p, q)` 只需要判断 `id[p] == id[q]` 即可。

缺点：`union(p, q)` 的实现需要遍历数组 `id[]`，将所有与 `id[p]` 相同的元素都改为 `id[q]`。这样，`union(p, q)` 的时间复杂度为 $O(N)$。

评估：如果最后只得到了一个连通分量，那么 `union(p, q)` 至少调用 $N-1$ 次，即 $O(N^2)$。

##### quick-union

想法：优化 `union(p, q)` 的实现。`id[]` 数组中存储相同分量中的另一个触点，这样就能持续跳转到达根触点。此时 `union(p, q)` 的实现只需要将 `p` 的根触点指向 `q` 的根触点即可。

评估：该算法有最坏情况，即所有触点之间的连通构成了一条链，极大地影响了 `find(p)` 的性能。此时，`find(p)` 的时间复杂度为 $O(N)$，处理整个数组所需的时间复杂度为 $O(N^2)$。

##### 加权 quick-union

想法：优化 `quick-union` 的实现。在 `union(p, q)` 时，总是将小树的根触点连接到大树的根触点上。这样，`find(p)` 的性能就能得到保证。

