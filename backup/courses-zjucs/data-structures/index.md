# 数据结构基础

<!-- prettier-ignore-start -->
!!! abstract "课程信息"

    - 学年：2023-2024 秋冬学期
    - 授课教师：干红华
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
!!! info "其他学长的笔记"

    - [鹤翔万里：数据结构基础](https://note.tonycrane.cc/cs/algorithm/ds/)
    - [Hobbitqia：数据结构基础](https://note.hobbitqia.cc/ds/)
    - [MinJoker：数据结构基础](https://minjoker.github.io/cs/algorithm/fds/)
<!-- prettier-ignore-end -->

## PPT 上出现过的所有算法、数据结构

### Ch02 算法分析

-   矩阵加法（复杂度分析）
-   斐波那契（递推求和）
-   最大子序列和（枚举、分治、动态规划）

Homework：

-   欧几里得算法
-   快速幂（迭代、递归）、霍纳规则（多项式的快速计算）

### Ch03 线性表

-   数组实现、单向链表实现、双向循环链表实现
-   多项式 ADT
-   游标实现的链表

Homework：

-   稀疏矩阵表示（交叉链表）

### Ch04 栈和队列

-   括号匹配检查算法
-   后缀表达式计算
-   中缀表达式解析
-   队列的循环数组实现

Homework：

-   栈和队列相互实现

### Ch05/06 二叉树、二叉搜索树

- 树型结构的表示：链表式、数组式、左孩子右兄弟式
- 二叉树与左孩子右兄弟树的转换
- 表达式树
- 三种遍历方式
- 线索树（将空的指针指向前驱或后继，根据遍历的顺序决定。需要额外的标志位表示是否存在子树）
- 二叉树的性质：
    - 第 i 层上的结点数目最多为 $2^{i-1}$
    - 深度为 k 的二叉树最多有 $2^k-1$ 个结点（等比数列求和）
    - 任何一棵二叉树，如果其叶结点数为 $n_0$，度为 2 的结点数为 $n_2$，则 $n_0=n_2+1$

Homework：

- 红黑树

### Ch07 优先队列

### Ch08 并查集

### Ch09 图

### Ch10-12 图算法

-   最大流问题：了解基础的 Ford-Fulkerson 算法，知道它的一种改进措施：剩余网络和增广路径。
-   最小生成树：Prim 和 Kruskal 算法
-   DFS 的应用：了解双连通性问题和解决办法、

### Ch13-14 排序算法

插入排序、希尔排序、堆排序、归并排序

-   实现、理论性能下界
-   希尔增量序列和 Hibbard 增量序列，前者的最坏情况（为什么？）
-   堆排序，时间复杂度、空间复杂度

### Ch15 哈希与再哈希

-   哈希的基本概念、哈希函数
-   拉链法：初始化、插入、查找
-   开放定址法：线性探查、平方探查、双散列；查找、插入
-   双散列：合适的选择
-   再散列：适用情况、基本步骤

## 基础数据结构的实现：链表、栈、队列

### 队列

<!-- prettier-ignore-start -->
!!! note "队列的循环数组实现"

    一般实现的要点：

    - 若队列大小为 `size`，则数组大小为 `size + 1`。
    - 两个索引 `front` 和 `end` 分别指向队列头部元素和**尾部元素的后一位**。
        - 注意 `end` 上没有元素，这样可以区分队列为空和队列已满的情况。
    - 空队列时，`front == end`；满队列时，`front == (end + 1) % size`。总是有一个位置空余。
    - 实现时，注意对索引取模，模数为数组的大小（想想为什么）。

    留出的一个空位使得空队列和其他情况可以统一处理。如果要利用数组中的所有元素，则需要额外记录队列中元素的个数或设置标记位。
<!-- prettier-ignore-end -->

## 二叉树、二叉搜索树（Ch05）

BST 是需要重点掌握的内容。

### 树的基础

-   树的高度：根节点到叶节点的最长路径长度。根节点高度为 $0$，空树为 $-1$。

<!-- prettier-ignore-start -->
!!! warning "注意区分树的层数和高度"
<!-- prettier-ignore-end -->

一些树的计算公式：

-   树的度定义和图有所不同。树中节点的度为其子女的数目。树的度为树中节点的最大度。
-   树的节点数 $n=\sum \mathrm{deg} + 1$。理解：把每个节点的直接子女数加起来，再加上根节点。
-   以下计算按照树的层数从 1 开始记（极特别情况下有从 0 开始记的）：
    -   第 $i$ 层上的节点数最多为 $n_i=2^{i-1}$。
    -   高为 $k$ 的树最多有 $n_k=2^{k} - 1$ 个节点。
    -   一个节点数为 $n$ 的 $m$ 叉树的高度最少为 $\lceil \log_m (n(m-1)+1)\rceil$。
    -   假设度为 $i$ 的节点数有 $n_i$ 个，有以下性质：
        -   总分支数 $b=\sum i n_i$。
        -   总节点数 $n=\sum n_i$。
        -   $b=n-1$。

<!-- prettier-ignore-start -->
!!! warning "保险起见，还是自己带入算一下对不对"
<!-- prettier-ignore-end -->

-   二叉树：
    -   一个 $\lambda$ 高的二叉树最多有 $2^{\lambda+1}-1$ 个节点。

### 二叉搜索树

二叉搜索树中序遍历的结果是有序的。

<!-- prettier-ignore-start -->
!!! note "删除树上的元素"

    -   有一个子树是空的：用另一棵子树填补。
    -   两个子树均不空：在**右子树**上寻找**中序**（即最左的）第一个子女填补。因为该子女在右子树上，所以它一定大于左子树上的所有元素。右因为它是中序第一个，所以它一定小于右子树上的所有元素。
<!-- prettier-ignore-end -->

## 堆、优先队列（Ch06）

<!-- prettier-ignore-start -->
??? note "堆"

    -   描述：
        -   定义：堆是完全二叉树，只有底层可能不满，且底层从左到右填充。堆的高度为 $\lfloor \log_2 n\rfloor$。
        -   下标计算：下标为 $i$ 的节点的父节点下标为 $\lfloor i/2\rfloor$，左右孩子节点下标分别为 $2i$ 和 $2i+1$。数组中下标为 0 的位置不存储元素（或存储堆的大小）。
        -   堆的性质：父节点大为最大堆（大顶堆），父节点小为最小堆（小顶堆）。一般来说，堆排序使用最大堆，优先队列使用最小堆。
<!-- prettier-ignore-end -->

## 图算法（Ch10-Ch12）

### ☑️最短路径

在有向图中给定两个顶点，找到一条从起点到终点的路径，使得路径上的边的权重之和最小。

-   无权图：BFS。
-   有权图：Dijkstra 算法（不适用于负值的边）。

<!-- prettier-ignore-start -->
!!! note "BFS 算法"

    -   描述：
        -   使用三个数组：
            -   `dist` 保存起点到每个顶点的距离，初始化为无穷大。
            -   `known` 标记节点是否已经被访问过。
            -   `path` 保存路径（从起点到它的最短路径中的上一个节点，在更新它的最短路径时确定）。
        -   对于一个节点：
            -   如果它未被访问过，且距离等于当前搜索的距离，将它标记为已知，并更新它的邻接节点的距离。

    性能分析：简单的实现会选择在每次 BFS 时扫描所有节点，是 $O(V^2)$ 的。可以使用队列将其优化到 $O(|V|+|E|)$，即将相邻节点加入队列，每次从队列中取出节点扫描。

!!! note "Dijkstra 算法"

    描述：像 BFS 算法一样维护三个数组 `dist`、`known` 和 `path`。不同的是，每次从中找到距离最小的未探索的顶点，探索它（即更新它的相邻节点的距离）。

    Dijkstra 算法与 BFS 算法在行为上的一大区别是，在遇到一个节点时，它不会直接将其标记为已知；当它将节点标记为已知时，它已经找到了到达该节点的最短路径。当然，后者对于 BFS 算法也是成立的。

    ```c title="Dijkstra(G, s)"
    void Dijkstra(Graph G, Vertex s)
    {
        for each Vertex v
        {
            dist[v] = INFINITY;
            known[v] = false;
        }
        dist[s] = 0;
        while(1)
        {
            Vertex v = smallest unknown distance vertex;
            if(v == NOT_A_VERTEX)
                break;
            known[v] = true;
            for each Vertex w adjacent to v
                if(!known[w])
                // update the distance
                    if(dist[v] + dist(v, w) < dist[w])
                    {
                        dist[w] = dist[v] + dist(v, w);
                        path[w] = v;
                    }
        }
    }
    ```

    优化：采用一个优先队列来维护未探索的节点，每次从中取出距离最小的节点，而不是扫描数组寻找。这样可以将时间复杂度降低到 $O(|E|\log |V|)$。
<!-- prettier-ignore-end -->

对于具有负值边的图，书上只介绍了一种朴素的方法，设定一个出队次数阈值防止死循环。

对于无圈图，Dijkstra 算法可以将优先队列更改为普通队列。因为对于无圈图，如果一个顶点被标记为已知，它就不可能再次被更新了。

### 拓扑排序

拓扑排序问题用选课很好理解：课程之间的依赖关系可以用有向图表示，拓扑排序就是找到一种修读顺序。

如果图中存在环，那么不存在拓扑排序。使用 DFS 可以轻易地检测环。

只需要对 DFS 算法稍作修改即可实现拓扑排序。在 DFS 的过程中，在每个节点完成时将其加入栈中，最后将栈中的元素依次弹出即可。这样做的原理是：如果节点 A 在节点 B 之前完成，说明存在一条从 B 到 A 的路径，因此 A 应当排在 B 之后。

### 连通性

无向图的连通性采用 DFS 染色法。

有向图中需要区分强连通性和弱连通性。

-   强连通性：如果两个顶点是互相可达的，那么它们是强连通的。显然，强连通性是一种等价关系。
-   弱连通性：如果两个顶点之间存在一条路径，那么它们是弱连通的。

<!-- prettier-ignore-start -->
!!! note "Kosaraju 算法"

    描述：使用 DFS 求图的**反向图的逆后序**，然后在原始图中按逆后序的顶点顺序进行 DFS。每次 DFS 都会得到一个强连通分量。

    正确性：证明的核心在于，逆后序的步骤相当于在反向图中进行 DFS。

    -   按逆后序进行 DFS 时，如果 `dfs(s)` 到达了顶点 `v`，说明存在路径 `s->v`，并且说明在反向图中，`v` 先完成。
    -   既然在反向图中 `v` 先完成，那么说明在反向图中存在路径 `s->v`，也即在原始图中存在路径 `v->s`。

    等价的实现方式：在图上进行深度优先搜索，标记序号；把图反向，按序号从大到小进行深度优先搜索。
<!-- prettier-ignore-end -->

### 最小生成树

问题：给定一幅**加权**无向图，找到一棵包含所有顶点的树，使得树的所有边的权重之和最小。

需要用到树的两个性质：加上边会产生环、删去边会得到独立的树。

<!-- prettier-ignore-start -->
??? warning "值得考虑的问题"

    -   边的权重可以是非正值：如果都是正值，只需要找到总权最小的树即可，算法会简单很多。
    -   边的权重有可能相同：下面的算法都能解决该问题，但这一条件会使证明困难一些。

??? note "切分定理"

    最小生成树算法都依赖于切分定理：加权图中，给定任意切分，横切边种权重最小者必定属于最小生成树。

!!! note "Prim算法"

    描述：使用一个优先队列保存所有边。当顶点（边）被加入树中后，将连接该顶点和所有不在树中顶点的边加入优先队列。失效的边可以立即从队列中删除，也可以延时删除。

    性能分析：$T=O(E\log V), S=O(V)$

!!! note "Kruskal算法"

    描述：将权重最小的，且不会与已加入的边构成环的边加入树中。使用一个优先队列和一个并查集。

    性能分析：$T=O(E\log E), S=O(E)$

!!! note "欧拉回路"

    欧拉回路不要求实现，因此知道它的方法即可。

    描述：欧拉回路是指一条路径，它经过图中每条边恰好一次，且最终回到起点。

    定理：

    -   无向图存在欧拉路径的充要条件是：奇顶点的数目等于 0 或 2。存在欧拉回路的充要条件是：所有顶点的度数均为偶数。
    -   有向图可以表示为 u 到 v 的欧拉路径的充要条件为：u 的出度比入度大 1，v 的入度比出度大 1，其他顶点的入度和出度相等。
    -   有向图存在欧拉回路的充要条件是：所有顶点的入度和出度相等，或存在一系列环，使得图中每个边都恰好属于某个环。

    使用 DFS 拼接法找欧拉回路的方法：

    -   执行一次深度优先搜索。找到这样的一条路径，它从出发点出发，回到出发点，并使得出发点没有剩余的边。搜索过程中，删去经过的边。
    -   图中有边剩余，从第一个具有剩余边的顶点开始，执行上一步，直到该节点被封死。将得到的路径拼接到上一步的路径上。
    -   重复上一步骤，直到所有边都被删除。
<!-- prettier-ignore-end -->

### 网络流

### DFS

DFS 使用一个布尔数组辅助。

<!-- prettier-ignore-start -->
!!! note "双连通性 Biconnected"

    问题：如果一个无向图不存在删除之后使得剩下图不再连通的顶点，那么它是双连通的。这样的店叫割点（articulation point）。

    描述：用 DFS 给顶点编号。每个顶点记录两个值：自己的编号 `num` 和自己可以到达的最小顶点 `low`。
        -   对于根节点，如果它有两个及以上孩子，它是割点。
        -   对于其他节点，如果它的孩子的 `low` 比自己大，它是割点（这个孩子要回到上面的点，必须经过它）。

    求 `low` 的值：从树的叶子节点开始，它能到达的最小值，它的父亲也能到达。采用递归解决。
<!-- prettier-ignore-end -->

## 排序算法（Ch11-13）

### 插入、冒泡、选择排序

<!-- prettier-ignore-start -->
??? note "插入排序"

    描述：维持一个有序子序列，每次将一个元素插入到有序子序列中的合适位置。

    ```c hl_lines="7-11" title="insertionSort(A, N)"
    void insertionSort(int A[], int N)
    {
        for(int i = 1; i < N; i++)
        {
            // the key to insert
            int key = A[i];
            int j = i - 1;
            // find and prepare the position to insert
            while(j >= 0 && A[j] > key)
            {
                // move
                A[j + 1] = A[j];
                j--;
            }
            // insert
            A[j + 1] = key;
        }
    }
    ```

    性能分析：取决于 `while` 循环比较的次数。最坏情况（逆序）下 $O(n^2)$，最好情况（顺序）下 $O(n)$。 
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
??? note "冒泡排序"

    描述：将最小的元素逐步冒泡到序列的前端。

    ```c hl_lines="5-12" title="bubbleSort(A, N)"
    void bubbleSort(int A[], int N)
    {
        for(int i = 0; i < N - 1; i++)
        {
            for(int j = N - 1; j > i; j--)
            {
                if(A[j] < A[j - 1])
                {
                    int temp = A[j];
                    A[j] = A[j - 1];
                    A[j - 1] = temp;
                }
                // the min element is bubbled
            }
        }
    }
    ```

    性能分析：取决于内层 `for` 循环的比较次数。**比较次数**是固定的，为 $n(n-1)/2$；**交换次数**不定，最坏情况下为 $n(n-1)/2$，最好情况下为 0。

    优化：如果某一趟冒泡过程中没有发生交换，则说明序列已经有序，可以提前结束。通过在内层 `for` 循环中设置一个标志位来实现。

    ```c hl_lines="13" title="bubbleSort(A, N)"
    void bubbleSort(int A[], int N)
    {
        for(int i = 0; i < N - 1; i++)
        {
            bool flag = false;
            for(int j = N - 1; j > i; j--)
            {
                if(A[j] < A[j - 1])
                {
                    int temp = A[j];
                    A[j] = A[j - 1];
                    A[j - 1] = temp;
                    flag = true;
                }
            }
            if(!flag)
                break;
        }
    }
    ```

    性能分析：此时比较次数也不固定了，最好情况下为 $O(n)$，最坏情况下为 $O(n^2)$。
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
??? note "选择排序"

    描述：每次从未排序的序列中选择最小的元素，放到已排序序列的末尾。

    ```c hl_lines="5-12" title="selectionSort(A, N)"
    void selectionSort(int A[], int N)
    {
        for(int i = 0; i < N - 1; i++)
        {
            //find min
            int min = i;
            for(int j = i + 1; j < N; j++)
            {
                if(A[j] < A[min])
                    min = j;
            }
            //swap
            int temp = A[i];
            A[i] = A[min];
            A[min] = temp;
        }
    }
    ```
<!-- prettier-ignore-end -->

### 归并排序

<!-- prettier-ignore-start -->
??? note "归并排序"

    描述：需要两个 function：
        -   `mergeSort` 排序指定范围的子序列。本质上它只负责序列拆分，排序由 `merge` 完成。
        -   `merge` 将两个有序序列合并成一个有序序列。每次从两个序列的头部取出较小的元素，放到新序列的尾部，直到两个序列都为空。

    ```c title="mergeSort(A, p, r)
    void mergeSort(int A[], int p, int r)
    {
        if(p < r)
        {
            int q = (p + r) / 2;
            mergeSort(A, p, q);
            mergeSort(A, q + 1, r);
            merge(A, p, q, r);
        }
    }
    ```

    ```c title="merge(A, p, q, r)
    void merge(int A[], int p, int q, int r)
    {
        int n1 = q - p + 1;
        int n2 = r - q;
        // copy old array
        int L[n1 + 1], R[n2 + 1];
        for(int i = 0; i < n1; i++)
            L[i] = A[p + i];
        for(int i = 0; i < n2; i++)
            R[i] = A[q + i + 1];
        L[n1] = INT_MAX;
        R[n2] = INT_MAX;
        int i = 0, j = 0;
        // select the smaller one
        for(int k = p; k <= r; k++)
        {
            if(L[i] <= R[j])
            {
                A[k] = L[i];
                i++;
            }
            else
            {
                A[k] = R[j];
                j++;
            }
        }
    }
    ```

    性能分析：这是分治算法，有递归式 $T(n)=2T(n/2)+O(n)$，根据主定理可知其时间复杂度为 $O(n\log n)$。这种简单情况也可以用递归树直接理解：树高为 $\log n$，每**层**的复杂度为 $O(n)$。

    特点：时间稳定，但需要额外的空间。

??? note "迭代版本"

    描述：归并排序的迭代版本和下面的希尔排序有点像，不过不是间隔 $h$之间有序，而是每 $2^k$ 个元素有序。

    ```c title="mergeSort(A, N)"
    void mergeSort(int A[], int N)
    {
        for(int h = 1; h < N; h *= 2)
        {
            for(int i = 0; i < N; i += 2 * h)
            {
                int p = i;
                int q = i + h;
                int r = i + 2 * h;
                if(r > N)
                    r = N;
                merge(A, p, q, r);
            }
        }
    }
    ```
<!-- prettier-ignore-end -->

### 希尔排序

>   希尔排序是对插入排序的改进。插入排序只会交换相邻的数组元素，对于大数组，元素的**移动速度很慢**。

描述：希尔排序使数组中任意间隔 $h$ 的元素之间有序，不断减小 $h$ 的值直到 $h=1$ 完成排序。所选取的 $h$ 序列称为**增量序列**。

```c title="shellSort(A, N)" hl_lines="3 17"
void shellSort(int A[], int N)
{
    for(int h = /*...*/; h > 0; h = /*...*/)
        for(int i = h; i < N; i++)
        {
            int key = A[i];
            int j = i - h;
            while(j >= h && A[j] > key)
            {
                A[j + h] = A[j];
                j -= h;
            }
            A[j + h] = key;
        }
}
```

性能分析：希尔排序的时间复杂度取决于增量序列的选择，已证明广泛的增量序列满足 $O(n^{3/2})$。有三种典型的增量序列：
    -   $h=3h+1$
    -   Hibbard's Increments $h=2^k-1$：该序列相邻的增量之间互质。

        ```c
        int h = 1;
        while(h < N)
            h = 2 * h + 1;
        h = (h - 1) / 2;
        ```
    -   Shell's Increments $h_i=\lfloor N/2\rfloor^i, h_k=\lfloor h_{k+1}/2\rfloor$：最坏情况 $\Theta(n^2)$。因为该序列增量之间不一定互质，若 $h=2$ 时有序，那么 $h=4, 8, 16, \cdots$ 时也有序，这些时候都没有排序发生，直到最后 $h=1$ 时发生插入排序。

        ```c
        int h = N / 2;
        h = h / 2;
        ```

### 堆排序

>   请回忆堆、建堆的方法。

<!-- prettier-ignore-start -->
??? note "线性时间建堆"

    描述：从最后一个非叶子节点开始，依次向上调整（将该节点下沉到合适为止），直到根节点。需要两个 function：
        -   `maxHeapify` 负责该节点的调整。对于它和它的两个孩子节点，找到最大的那个，置换到该节点的位置。如果发生了置换，置换的位置对递归调用 `maxHeapify`。
        -   `buildMaxHeap` 负责从最后一个非叶子节点开始调用 `maxHeapify`。

    ```c title="maxHeapify(A, i, N)"
    void maxHeapify(int A[], int i, int N)
    {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        // find the largest one
        int largest = i;
        if(l < N && A[l] > A[largest])
            largest = l;
        if(r < N && A[r] > A[largest])
            largest = r;
        if(largest != i)
        {
            int temp = A[i];
            A[i] = A[largest];
            A[largest] = temp;
            // recursive call
            maxHeapify(A, largest, N);
        }
    }
    ```

    ```c title="buildMaxHeap(A, N)"
    void buildMaxHeap(int A[], int N)
    {
        // start from the last non-leaf node
        for(int i = N / 2 - 1; i > 0; i--)
            maxHeapify(A, i, N);
    }
    ```
<!-- prettier-ignore-end -->

堆排序的步骤如下：

-   建堆 $O(n)$
-   将堆顶元素依次移动到临时的数组，每次 $O(\log n)$，共 $n$ 次
-   将数组拷贝回来 $O(n)$

性能分析：堆排序非常稳定，时间复杂度为 $O(n\log n)$，空间复杂度为 $O(n)$。

优化：堆缩小后末尾的空间可以用来存储临时的数组，这样就不需要额外的空间了。实际操作是交换堆顶和堆尾元素，然后将堆的大小减一，再将堆顶元素下沉到合适位置。

### 快速排序

快速排序是已知实践中最快的排序算法。

描述：上面的归并排序在合并部分进行排序，而快排在分解问题的步骤进行排序。分解时，它使左侧子数组小于等于主元，右侧子数组大于等于主元。需要两个 function：
    -   `partition` 负责分解数组。
    -   `quickSort` 负责递归调用 `partition`。

```c title="quickSort(A, p, r)"
void quickSort(int A[], int p, int r)
{
    if(p < r)
    {
        int q = partition(A, p, r);
        quickSort(A, p, q - 1);
        quickSort(A, q + 1, r);
    }
}
```

分解时计算主元的位置。最直接的实现选取最右侧的主元：使用两个指针 `i` 和 `j`，从左向右扫描。前者标记小于的区域，后者标记大于的区域。每次扫描时，右侧指标都会移动。如果扫描到的元素大于主元，左指标不动；如果小于主元，将其交换到小于主元的区域，左指标右移。当右指标扫描到结尾时，将主元交换到左指标的位置。

```c title="partition(A, p, r)"
int partition(int A[], int p, int r)
{
    int x = A[r];
    int i = p - 1;
    for(int j = p; j < r; j++)
    {
        if(A[j] <= x)
        {
            i++;
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
    // swap
    int temp = A[i + 1];
    A[i + 1] = A[r];
    A[r] = temp;
    return i + 1;
}
```

性能分析：容易看出快排性能由分解的效率决定。如果每次都分解为 $n-1$ 和 $1$，那么递推式为 $T(n)=T(n-1)+O(n)$，时间复杂度为 $O(n^2)$。最好情况为 $T(n)=2T(n/2)+O(n)$，时间复杂度为 $O(n\log n)$。

从概率的角度来看，如果输入数据的所有排列都是等概率的，那么快排的期望时间复杂度为。为了保证这样的情况，我们在快排过程中加入随机化算法：

```c title="randomizedPartition(A, p, r)"
int randomizedPartition(int A[], int p, int r)
{
    // generate a random number in [p, r]
    int i = rand() % (r - p + 1) + p;
    // swap
    int temp = A[i];
    A[i] = A[r];
    A[r] = temp;
    return partition(A, p, r);
}
```

还有一种经典的双向切分方法：从左向右找到大于主元的元素，从右向左找到小于主元的元素，交换它们。重复这个过程，直到左右指针相遇。最后将主元交换到相遇的位置。

```c title="partition(A, p, r)"
int partition(int A[], int p, int r)
{
    int x = A[r];
    int i = p - 1;
    int j = r;
    while(true)
    {
        while(A[++i] < x)
            ;
        while(A[--j] > x)
            if(j == p)
                break;
        if(i >= j)
            break;
        // swap
        int temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }
    // swap
    int temp = A[i];
    A[i] = A[r];
    A[r] = temp;
    return i;
}
```

<!-- prettier-ignore-start -->
!!! warning "快排实现的常见错误"

    1. 终止条件：数组中可能有重复元素。
    2. 终止递归：将主元放入正确的位置，否则将导致无限递归。

??? note "进一步优化"

    1. 切换到插入排序
    2. 三向切分
<!-- prettier-ignore-end -->

### 间接排序（表排序）

间接排序是为了解决大型数据的排序问题。如果直接对数据进行排序，那么需要移动大量的数据。间接排序的思想是，将数据的下标存储在数组中，对下标进行排序，然后根据下标访问数据。

### 线性时间排序

上面我们介绍的所有排序都基于比较的思想，即通过比较两个元素的大小来确定它们的顺序。通过决策树模型很容易知道这类算法的时间复杂度下界为 $O(n\log n)$。接下来的线性时间排序算法一般需要用较大的空间来换取时间。

对于这些算法，课内只要求知道其步骤，不需要掌握实现。

<!-- prettier-ignore-start -->
!!! note "计数排序"

!!! note "基数排序"

    描述：先按最低位进行排序，再按次低位进行排序，直到最高位。每次排序都是稳定的。

    性能分析：取决于三个量：$n$ 个 $d$ 位数，每个数位有 $k$ 个可能取值，那么时间复杂度为 $\Theta(d(n+k))$。


!!! note "桶排序"

    描述：将数据分到有限数量的桶中，对每个桶进行排序，然后依次输出。

    性能分析：桶排序希望输入数据服从均匀分布，它的期望时间为 $\Theta(n)$。
<!-- prettier-ignore-end -->



## 哈希与散列（Ch14-15）

我们的目标是研究以下内容：

-   选择一个哈希函数 $H$
-   处理冲突
-   决定哈希表的大小

一个数据存储在哈希表中的位置是 $H(x)$。

### 哈希函数

哈希函数应当尽量使定义域内的元素均匀分布在值域中，且方便计算。一般哈希函数有两个参数，即元素和哈希表大小。常见的哈希函数有：

-   直接定址法：$H(x)=a\cdot x+b$，其中 $a, b$ 为常数。
-   除留余数法：$H(x)=x\mod m$，其中 $m$ 为素数。
-   平方取中法：$H(x)=\lfloor x^2\rfloor$，取中间的几位作为哈希值。

对于字符串，书上介绍的哈希函数是：

```c
int hash(char *key, int tableSize)
{
    unsigned int hashVal = 0;
    while(*key != '\0')
        hashVal = (hashVal << 5) + *key++;
    return hashVal % tableSize;
}
```

### 处理冲突

引入 load factor $\lambda$，表示哈希表中元素的个数与哈希表大小的比值。

<!-- prettier-ignore-start -->
??? note "拉链法"

    描述：将哈希表的每个位置都设置为一个链表，将哈希值相同的元素放到同一个链表中。

    具体代码就不作展示了，主要难点在于结构体和指针的使用。哈希表结构体中包含一个指针数组，每个指针指向一个链表的头节点。

    性能分析：对拉链法哈希表的查找主要耗时在链表搜索上，因此尽量保持链表短小是提高性能的关键。期望的 $\lambda$ 值为 $1$。

??? note "开放定址法"

    描述：将哈希值相同的元素放到其他空闲的位置上，即 $h_i(x) = (H(x) + f(i))\mod m$，其中 $f(i)$ 是要研究的探查函数。

    有三种探查函数：
        -   线性探查：$f(i)=i$
        -   平方探查：$f(i)=i^2$。平方探查的问题在于只能覆盖到哈希表的一部分位置。以下是一些结论，有兴趣可以查看书上的证明：
            -   如果表大小是**质数**，且至少有**一半的位置是空**的，那么总**可以**插入**一个**新的元素。
            -   如果表大小为 $4k+3$ 的质数，则平方探查可以覆盖到整个表。
        -   双散列：$f(i)=i\cdot H'(x)$，其中 $H'(x)$ 是另一个哈希函数。

    性能分析：显然，开放寻址法需要更多的空间以容纳冲突的元素。期望的 $\lambda$ 值为 $0.5$。

    删除操作：开放寻址法无法直接执行删除操作，因为删除一个元素会导致后面的元素无法被 Find 查找到（Find 寻找到空的位置时停止）。一般使用懒惰删除，哈希表项添加一个标记字段。
<!-- prettier-ignore-end -->

### 再散列

再散列是为了解决哈希表装填因子过大的问题。当装填因子过大时，哈希表的性能会急剧下降。当装填因子过大时，再散列将重新构造一个更大的哈希表，然后将原来的元素重新插入。

一般会选择的散列表大小为 $2n$ 或 $nextPrime(2n)$。