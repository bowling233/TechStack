# Lecture 5 Vectorization

Date: 2023/07/08

## Before you begin

工欲善其事，必先利其器。在学习 HPC 中的 Python 相关内容时，我们会遇到各种的包和环境问题，如果配置不善会产生各种奇奇怪怪的错误。我强烈推荐你在学习 NumPy 等内容前，先掌握 Conda、IPython 等工具的使用。

### Conda

- [Conda Doc](https://docs.conda.io/en/latest/)
- [Installation](https://docs.conda.io/projects/conda/en/stable/user-guide/install/index.html)

Most used conda commands:

- `conda create -n myenv`: create a new environment
- `conda activate myenv`: activate an environment
- `conda deactivate`: deactivate current environment
- `conda install numpy`: install a package
- `conda list`: list all packages installed in current environment
- `conda remove numpy`: remove a package
- `conda update numpy`: update a package
- `conda search numpy`: search a package
- `conda env export > environment.yml`: export an environment
- `conda env create -f environment.yml`: create an environment from a file
- `conda env remove -n myenv`: remove an environment
- `conda env list`: list all environments

Use `--help` argument to get help information for a specific action: `conda env --help`.

### IPython

IPython 是一个 Python 的增强交互式解释器，它提供了很多有用的功能，例如语法高亮、代码补全、自动缩进等等。当你在命令行中打开 IPython 并按下 ++tab++ 时，你就会感受到它的强大。

- 在 conda 环境中安装 IPython。

```bash
conda install -c anaconda ipython
```

- 输入 `ipython` 即可启动 IPython 解释器。

#### 📄 获取帮助

- `?` 帮助：你应该还记得在先前学习 Python 时，我们被建议为每个对象创建一个文档字符串（docstring），包含该对象的简要介绍和使用方法。在 Python 中我们可以通过 `help(fun)` 来获取某个对象的文档，在 IPython 中我们可以通过 `fun?` 来获取帮助。
- `??` 源代码：如果你想查看某个对象的源代码，可以使用 `fun??`。
- 通配符 超越 ++tab++ 自动补全：如果你只记得所寻找对象的中间几个字符，一般的补全工具可能无法为你提供帮助。在 IPython 中，你可以使用 `*` 通配符来匹配任意字符串，例如 `np.*load*?` 可以匹配 `np.load`、`np.loadtxt`、`np.chararray.astype` 等等。

#### 🪄 魔法命令

魔法命令具有两种形式：行魔法和单元魔法。行魔法以 `%` 开头，作用于单行；单元魔法以 `%%` 开头，作用于整个单元。

- `%paste` 和 `%cpaste`：处理粘贴代码时额外的提示符号和缩进问题。
- `%run`：运行外部脚本。`%run test.py`。
- `%timeit`：测试代码运行时间。`%timeit np.random.normal(size=100)`。

魔法命令同样可以使用 `?` 获取帮助。使用 `%magic` 和 `%lsmagic` 可以获得魔法函数的通用描述和列表。

#### 🕒 输入和输出历史

或许你已经注意到 IPython 的提示符不再是 `>>>` 和 `...`，而是 `In[n]` 和 `Out[n]`。事实上 IPython 创建了 `In` 和 `Out` 变量，它们自动更新以反映历史。输入 `print(In)` 看看吧～

变量 `_` 和 `__` 分别表示上一个和上上一个输出结果，`_N` 表示 `Out[N]`。

在行的末尾添加分号 `;` 可以禁止一个命令的输出。

相关的魔法命令还有 `%history`、`%rerun`、`%save` 等等。

#### 🐚 Shell 命令  

在 IPython 中通过 `!` 前缀执行 shell 命令。

```bash
!ls
```

可以将 shell 命令的输出赋值给一个变量，这种变量将拥有 IPython 定义的一个特殊 shell 返回类型。用 `type()` 试试看吧～

```bash
contensts = !ls
type(contents)
```

这里有一些好用的与 shell 相关的魔法命令：

- `%cd`：改变当前工作目录。
- `%cp`：复制文件。
- `%env`：设置环境变量。
- ...

如果打开 `automagic`，你可以省略 `!` 前缀。这时的 IPython 就像是一个普通的 shell ❗️

#### ⚙️ 错误和调试

- `%xmode`：控制异常报告的详细程度。`%xmode Plain`、`%xmode Verbose`、`%xmode Context`。
- `%debug`：进入交互式调试器。
    - 回忆一下 Python 的调试器是 `pdb`。IPython 的增强版本是 `ipdb`。
    - 在捕获异常后调用该调试器，将在异常点自动打开交互式调试提示符。你可以探索**栈空间的状态、可用变量**，甚至运行 Python 命令。

<!-- prettier-ignore-start -->
??? note "ipdb 的基本使用"

    - `up`, `down`：单步出/入栈。可以方便地查看各变量的值。
    - `quit`：退出调试器
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
??? note "交互式调试脚本"

    使用 `%run -d` 运行脚本，利用 `next` 命令单步交互执行。
<!-- prettier-ignore-end -->

#### 📉 代码统计信息

- `%time`：单语句计时
- `%timeit`：单语句重复执行计时，获取更高准确度
    - 注意，对列表排序的算法不适用。因为排序算法会在列表上重复执行，有序情况下的时间将显著减少，产生误导。
- `%prun`：分析器运行代码，用于整个脚本
- `%lprun`：逐行分析器
- `%memit`：单语句内存使用
- `%mprun`：逐行内存分析器

通过 `%%` 前缀，上面的命令都可以用于调试多行代码块。

其中的一些魔法命令需要安装 `line_profiler` 和 `memory_profiler` 扩展。

## NumPy

- `np.info()` 获取帮助。
- `np.show_config()` 查看配置信息（如 CPU 支持的 SIMD 指令集）。

### Python 中的数据类型

学习 NumPy 前，如果能重新审视 Python 的数据类型，将会对 NumPy 所做的优化有更好的理解。

- Python 的标准实现使用 C 语言编写。**每一个 Python 对象都是一个伪 C 语言结构体**，其中包含了：
    - 引用计数：帮助 Python 处理内存分配和回收。
    - 类型编码
    - 数据成员的大小
    - 变量的值
- C 语言变量的本质是某个内存位置的标签，Python 变量的本质是一个指针，指向包含 Python 对象所有信息的内存位置。
- Python 列表中的每一项都是一个完整的 Python 对象，Python 列表**是一个指向指针块的指针**。

### 数组操作

<!-- prettier-ignore-start -->
::cards:: cols=2

[
  {
    "title": "创建",
    "content": "
                `np.array([1, 2, 3])` 类型不匹配时向上转换<br>
                `np.zeros(10, dtype=int)`<br>
                `np.ones((3, 5), dtype=float)`<br>
                `np.full((3, 5), 3.14)`<br>
                `np.arange(0, 20, 2)` 注意浮点型可能出现误差<br>
                `np.linspace(0, 1, 5)` 避免了上面的问题<br>
                `np.random.random((3, 3))` 0~1 随机分配<br>
                `np.random.normal(0, 1, (3, 3))` 均值为 0 方差为 1 的正态分布<br>
                `np.random.randint(0, 10, (3, 3))` 左闭右开区间<br>
                `np.eye(3)` 3x3 单位矩阵<br>
                `np.empty(3)` 未初始化
                ",
  },
  {
    "title": "标准数据类型",
    "content": "
                `bool_` `int_` `intc` `intp` `int8` `int16` `int32` `int64` `uint8` `uint16` `uint32` `uint64` `float_` `float16` `float32` `float64` `complex_` `complex64` `complex128`
                ",
  },
  {
    "title": "属性",
    "content": "
                `ndim` 维度<br>
                `shape` 各维度大小<br>
                `size` 元素总数<br>
                `dtype` 数据类型<br>
                `itemsize` 每个元素占用字节数<br>
                `nbytes` 数组总字节数<br>
                ",
  },
  {
    "title": "索引：获取单个元素",
    "content": "
                `x[0]`<br>
                `x[-1]`<br>
                `x[0, 0]` 多维数组使用逗号分隔的索引元组<br>
                使用索引修改元素值时，值会被自动转换为数组的类型，不会产生提示或警告<br>
                ",
  },
  {
    "title": "切片：获取子数组",
    "content": "
                **数组切片均返回原数组的视图**，不会生成副本。<br>
                好处：处理数据集中片段时不用复制数据缓存。<br>
                一维：<br>
                `x[start:stop:step]`<br>
                `x[::-1]` 逆序<br>
                `x[5::-2]`<br>
                多维：使用逗号分隔<br>
                `x2[:2, :3]`<br>
                `x2[::-1, ::-1]` 子数组维度逆序<br>
                `x3[..., 1] == x3[:, :, 1]` 更简易的写法<br>
                获取行和列：单个冒号表示空切片，可以省略
                `x2[0] == x[0, :]`<br>
                创建副本：使用 `copy()` 方法<br>
                `x2_sub_copy = x2[:2, :2].copy()`<br>
                ",
  },
  {
    "title": "变形：改变数组维度",
    "content": "
                `x.reshape(3, 2)` 要求原始数组大小与变形后一致，返回**视图**。<br>
                可以使用 `newaxis` 简化操作：<br>
                `x[:, np.newaxis] == x.reshape((3, 1))`<br>
                `x[np.newaxis, :] == x.reshape((1, 3))`<br>
                ",
  },
  {
    "title": "拼接：将多个数组合并",
    "content": "
                `np.concatenate([x, y])` 接受数组元组或列表<br>
                `np.concatenate([grid, grid], axis = 1)` <br>
                `np.vstack([x, grid])` 垂直堆叠<br>
                `np.hstack([grid, y])` 水平堆叠<br>
                `np.dstack([grid, grid])` 深度堆叠<br>
                ",
  },
  {
    "title": "分裂",
    "content": "
                传递一个索引列表记录分裂点位置，分割位置是分裂点元素前<br>
                分裂时可以用到多重赋值的技巧<br>
                `np.split(x, [3, 5])`<br>
                `np.vsplit(grid, [2])` 垂直分裂<br>
                `np.hsplit(grid, [2])` 水平分裂<br>
                `np.dsplit(grid, [2])` 深度分裂<br>
                ",
  },
]

::/cards::
<!-- prettier-ignore-end -->

还有一些常用的函数：

`np.pad()` ``

### 通用函数

NumPy 的很多类型操作提供了非常方便的、静态的、可编程的接口，称为**向量操作**，它们**将循环推送到编译层**。向量操作是通过**通用函数（ufunc）**实现的，目的是对数组中的值执行快速的重复操作。

通用函数具有很多特性，在数据量较大时充分利用可以提高性能、节省资源：

- 指定输出：`out` 参数指定计算结果的存放位置。不使用 `out` 参数则会创建一个临时数组，浪费内存。
    - `np.multiply(x, 2, out=y)`
- 聚合：二元通用函数可以通过 `reduce` 方法对给定的元素和操作反复执行，`accumulate` 方法保存每次计算的中间结果。
    - `np.add.reduce(x)`
    - `np.ad.accumulate(x)`
- 外积：`outer` 方法计算两个输入数组所有**元素**的函数运算结果。
    - `np.multiply.outer(x, y)`
- 广播：通用函数能够使用广播规则操作不同大小和形状的数组。详见下文。

### 聚合

NumPy 提供一些快速内置函数对数组进行聚合操作：

`np.sum` `np.prod` `np.mean` `np.std` `np.var` `np.min` `np.max` `np.argmin` `np.argmax` `np.median` `np.percentile` `np.any` `np.all`

语法：

- 调用函数：`np.sum(x)`
- 对数组对象调用方法：`x.sum()`
- 指定轴：`np.sum(x, axis=0)`
    - `axis` 关键字指定将要被折叠的维度，即沿着该维度进行聚合操作。
    - 思考：`arr1.sum(-1)` 会执行什么操作呢？
- 大多数聚合函数同样有**对 `NaN` 安全**的版本，计算时忽略缺失值。添加前缀 `nan` 即可
    - `np.nanmean(x)`

### 广播

广播是一组规则，用于描述**不同大小和形状**的数组之间的**二进制通用函数**的行为。

- 二进制通用函数：如加、减、乘、除等

<!-- prettier-ignore-start -->
!!! note "广播的三条规则"

    1. 如果两个数组的维度数不相同，则小维度数组的形状将会在**最左边**补 1。
    2. 如果两个数组的形状在任何一个维度上都不匹配，那么数组的形状会沿着**维度为 1 的维度扩展**以匹配另外一个数组的形状。
    3. 如果两个数组的形状在任何一个维度上都不匹配，并且没有任何一个维度等于 1，则会引发异常。
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
??? question "考考你"

    请应用上面的规则，思考下面的一系列广播操作是否合法？结果是什么？

    ```python
    M = np.ones((2, 3))
    a = np.arange(3)
    M + a
    ```

    ```python
    a = np.arange(3).reshape((3, 1))
    b = np.arange(3)
    a + b
    ```

    ```python
    M = np.ones((3, 2))
    a = np.arange(3)
    M + a
    M + a[:, np.newaxis]
    np.logaddexp(M, a[:, np.newaxis])
    ```
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
??? info "广播的应用"

    1. 数组的**缩放**：将数据标准化到均值为 0、方差为 1
    2. 数组的**中心化**：将数据标准化到均值为 0
    3. 数组的**归一化**：将数据标准化到 0 到 1 之间
<!-- prettier-ignore-end -->

### 比较、掩码和布尔逻辑

比较和布尔运算符同样使用通用函数进行了重载，在这里就不一一列出了~

这些运算同样有广播机制。比如一个数与数组进行比较，将得到一个布尔数组，包含逐元素比较的结果。

复合表达式也是同样：`(2 * x) == (x ** 2)`，其中 `x` 是一个数组。

重载后的 `<` 运算符不能连续使用，比如不能写 `np.sum(0.5 < x < 1)` 而应写为 `np.sum((0.5 < x) & (x < 1))`。

一些常用的函数：

`np.count_nonzero()`、`np.any()`、`np.all()`，它们用于操纵布尔数组。

`np.nonzero()`：返回数组中非零元素的索引。索引作为数组的元组返回，每个维度一个数组。

### Fancy Indexing

与索引不同，fancy indexing 传递的是索引数组，**结果的形状与索引数组的形状一致**。

思考下面的代码：

```python
x = rand.randint(100, size=10)
[x[3], x[7], x[2]]
ind = [3, 7, 4]
x[ind]
ind = np.array([[3, 7], [4, 5]])
x[ind]
```

对于多维数组，第一个索引指的是行，第二个索引指的是列，以此类推：

```python
X = np.arange(12).reshape((3, 4))
row = np.array([0, 1, 2])
col = np.array([2, 1, 3])
X[row, col]
```

将一个行向量与一个列向量组合在索引中，利用广播规则，我们可以得到二维结果：

```python
X[row[:, np.newaxis], col]
```

Fancy indexing 有时令人难以理解，可以查阅官方文档 [Indexing on ndarrays — NumPy v1.25 Manual](https://numpy.org/doc/stable/user/basics.indexing.html)，这里做一些摘录：

### Fancy Index 的各种使用方式

首先，在 Python 中 `[(exp1, ...)]` 的索引方式等价于 `[exp1, ...]`。**后者只是前者的语法糖**。

#### 关于普通索引和切片的提醒

- 在性能上，`x[0][2]` 比 `x[0, 2]` 低，因为前者需要创建一个中间数组。
- `a[i]` 与 `a[i:i+1]` 的区别是：前者比后者少一个维度。

#### Advanced Indexing 的条件

当索引对象是 `ndarray` 或非元组的序列对象时时触发。例如：`x[(1, 2, 3), ]` 可以触发，而 `x[1, 2, 3]` 不能。

基于整数的 Advanced Indexing 会返回一个与索引数组形状相同的数组，而基于布尔的 Advanced Indexing 则会返回一个一维数组。

#### 基于整数的 Advanced Indexing

首先，每个索引数组的形状必须相同或符合广播规则。如果索引有重复，那么使用广播规则是最为方便的。

比如，要取出 `(4, 3)` 数组的边角元素，我们可以这样做：

```python
row = np.array([[0, 0], [3, 3]])
col = np.array([[0, 2], [0, 2]])
x[row, col]
```

利用广播可以写作：

```python
row = np.array([0, 3])
col = np.array([0, 2])
x[row[:, np.newaxis], col]
```

#### 与布尔运算结合

布尔数组常常被当作“掩码”使用，从数组中抽取符合条件的元素。用布尔数组进行 Fancy Indexing 得到的结果都是一维的。以下举几例：

- `a[a.nonzero()]` 取出 `a` 中的非零元素（一维）
  - 还记得 `np.nonzero()` 返回的是索引吗？
- `a[a != 0]` 同样是取出 `a` 中的非零元素
  - 但是这里的 `a != 0` 是一个布尔数组，而不是索引数组。

通过上面的两个例子，我们可以将布尔数组的 Fancy Indexing 解释为 `a[np.nonzero(condition)]`。比如：`a[a > 7]` 等价于 `a[np.nonzero(a > 7)]`。

常见的用法有：`x[~np.isnan(x)]`



### 线性代数

NumPy 的 `linalg` 子模块提供了线性代数的标准功能。此处主要介绍乘法运算。

<!-- prettier-ignore-start -->
::cards:: cols=2 

[
  {
    "title": "`np.dot(a, b[, out])`",
    "content": "计算两个数组的点积。<br>
                两个均为标量，等价于 `numpy.multiply(a, b)` 或 `a*b`。<br>
                两个数组都为一维，则执行普通的内积运算。<br>
                两个数组都为二维，则执行矩阵乘法，等价于 `a@b`。<br>
                $N$ 维乘 $1$ 维，相当于用 $N$ 维数组的最后一个维度与 $1$ 维数组进行内积。例如：`(4,3,2)` 与 `(2,)` 相乘的结果是 `(4, 3)`，每个元素是二维向量的内积。<br>
                $N$ 维乘 $M$ 维，相当于用 $N$ 维数组的最后一个维度与 $M$ 维数组的倒数第二个维度进行内积。例如 `(3, 4, 5, 6)` 与 `(5, 4, 6, 3)` 相乘的结果是 `(3, 4, 5, 5, 4, 3)`。这个结果可能有些难以理解，我的解释是：对 $A$ 最后一个维度的每个矩阵 `(, 6)`，将其与 $B$ 最后两维度的每个 `(6, 3)` 矩阵相乘得到的矩阵塞回 $B$ 中 `(6, 3)` 对应的位置，将 $B$ 形状变为 `(5, 4, 3)` 再塞回 $A$ 中 `(, 6)` 的位置，从而将 `(3, 4, 5, 6)` 的最后一维替换成了 `(5, 4, 3)` 形状，得到 `(3, 4, 5, 5, 4, 3)` 的形状。<br>
                表达式为：`dot(a, b)[i,j,k,m] = sum(a[i,j,:] * b[k,:,m])`
                ",
    "image": "https://cdn.bowling233.top/images/2023/07/202307121147578.png",
  },
  {
    "title": "`np.matmul(x1, x2, /[, out, casting, order, …])`",
    "content": "
                简单来说，`matmul` 将高维数组视为最后两个维度的矩阵的堆叠。此时，`matmul` 要求高维数组除最后两个维度的其他维度相同（或为 1 维以应用广播规则），然后对每一对矩阵进行乘法。`(9, 5, 7, 4)` 与 `(9, 5, 4, 3)` 相乘就变为 `(9, 5, 7, 3)`。<br>
                If both arguments are 2-D they are multiplied like conventional matrices.<br>
                If either argument is N-D, N > 2, it is treated as a **stack** of matrices residing in the last two indexes and broadcast accordingly.<br>
                If the first argument is 1-D, it is promoted to a matrix by prepending a 1 to its dimensions. After matrix multiplication the prepended 1 is removed.<br>
                If the second argument is 1-D, it is promoted to a matrix by appending a 1 to its dimensions. After matrix multiplication the appended 1 is removed.
                ",
    "image": "https://cdn.bowling233.top/images/2023/07/202307121239096.png"
  },
  {
    "title": "`np.inner(a, b, /)`",
    "content": "
                普通的内积。高维情况可以看作将 `np.dot` 改为两矩阵最后一维直接做点乘，表达式如下：<br>
                `ndim(a) = r > 0` 且 `ndim(b) = s > 0`<br>
                `np.inner(a, b) = np.tensordot(a, b, axes=(-1,-1))`<br>
                `np.inner(a, b)[i0,...,ir-2,j0,...,js-2]= sum(a[i0,...,ir-2,:]*b[j0,...,js-2,:])`<br>
                ",
    "image": "https://cdn.bowling233.top/images/2023/07/202307121206515.png"
  },
  {
    "title": "`np.outer(a, b, out=None)`",
    "content": "
                外积，仅用于向量。<br>",
    "image": "https://cdn.bowling233.top/images/2023/07/202307121236806.png"
  },
  {
    "title": "`linalg.multi_dot(arrays, *[, out])`",
    "content": "计算两个或者更多的数组的乘积。",
  },
  {
    "title": "`np.vdot(a, b, /)`",
    "content": "
                对于高维数组，`vdot` 会将其展平成一维数组，然后再计算点积。<br>
                如果 `a` 是一个复数，那么取它的复共轭计算点积。
                ",
  },
]

::/cards::
<!-- prettier-ignore-end -->



