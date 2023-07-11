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

