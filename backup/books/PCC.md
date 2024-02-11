---
tags:
    - Todo
---

# Python 编程：从入门到实践

Python Crash Course: A Hands-On, Project-Based Introduction to Programming

| 出版社         | 作者         | 年份 |
| -------------- | ------------ | ---- |
| 人民邮电出版社 | Eric Matthes | 2016 |

!!! abstract

    本书仅作项目部分笔记。

## 前置知识

!!! abstract

    这里介绍一些创建 Python 项目的基本知识，比如虚拟环境、`pip` 包管理器等。

### 命令相关

Python 的命令容易引起困惑，我现在也依旧没有搞懂。如果你安装了 Python 后执行 `python3` 显示找不到，可以尝试替换为 `python` 或 `py`。如果还找不到，请检查 `$PATH` 环境变量。一般来说，Windows 系统中默认命令为 `py`，而 Unix 系统中默认命令为 `python3`。`pip` 包管理器也会默认安装，如果找不到可以尝试替换为 `pip3`。

### 虚拟环境

创建虚拟环境的理由有很多：不同项目的依赖不同、版本不同，或者是为了保持系统的干净整洁。

从 Python 3.3 开始，一般使用 Python 自带的模块 `venv` 来创建虚拟环境：

```bash
python3 -m venv <DIR>
source <DIR>/bin/activate
```

第一行的命令创建了虚拟环境，第二行命令（限 Unix 系统）将虚拟环境的环境变量载入终端。

创建虚拟环境并加载环境变量后，就能使用 `pip` 命令来安装依赖包了。

需要注意的是，Windows 和 Linux 下的虚拟环境并不能通用，因为其配置文件使用绝对路径。因此应当为不同的系统配置不同的虚拟环境，最好的方式是使用 `requirements.txt` 文件来记录依赖包，这样可以保证不同系统下的依赖包一致。

## 基础知识补全

> 复习以及补充 SOP4 中没有涉及的知识。

### 关键字和内置函数

- 定义：`def`、`class` 等
- 布尔等表达式运算：`False`、`True`、`None`、`and`、`or`、`not` 等
- 控制结构：`while`、`for`、`if`、`else`、`elif` 等
- 其他

### 字符串

- 修改大小写 `.title()`、`.upper()`、`.lower()`
- 拼接
- 删除空白 `.rstrip()`、`.lstrip()`、`.strip()`

!!! tip "空白"

    空白指任何非打印字符。

- 将其他数据转换为字符串 `str(value)`

### 列表

```python
list = [1, 2, 3]
```

基础：

- 添加元素：`.append(value)`、`.insert(index, value)`
- 删除语句：`del list[index]`、`.pop(index)`（尾部删除）、`.remove(value)`
- 排序：`.sort()`、`.sort(reverse=True)`
- 反转：`.reverse()`
- 长度：`len(list)`

更多操作：

- 遍历

!!! warning "循环结束后"

    `for` 循环结束后，迭代使用的变量仍然存在。

- `range(start, end, step)`：生成一个整数序列，不包含 `end`，默认 `start=0`，`step=1`。
- 切片 `list[start:end:step]`：不包含 `end`，默认 `start=0`，`step=1`。
    - 利用切片复制列表 `list[:]`。

!!! note "列表解析"

    这是一种比较高阶但常用的技巧，使用一行代码生成特定的列表：

    ```python
    squares = [value**2 for value in range(1, 11)]
    ```

    -   首先指定列表名
    -   再定义一个表达式 `value**2` 生成你要存储到列表中的值
    -   接下来写一个 `for` 循环给表达式提供值

    请练习生成一个 3 的倍数的列表。

### `if` 语句

- 比较方法：

    - `in` 检查特定值是否在列表中
    - 使用 `.lower()` 检查字符串是否为小写（注意个这个函数并不能直接检测，怎么用呢？）

- `if-elif-else` 结构
- 一些布尔表达式：
    - Python 中支持连续的比较，如 `age >= 18 and age <= 65` 可以简写为 `18 <= age <= 65`。

### 字典

```python
dict = {'key': 'value'}
```

基础：

- 访问：`dict['key']`
- 添加：`dict['key'] = 'value'`
- 创建空字典：`dict = {}`
- 修改值：`dict['key'] = 'new value'`
- 删除键值对：`del dict['key']`

较长字典的缩进方法：

```python
dict = {
    'key1': 'value1',
    'key2': 'value2',
    'key3': 'value3',
    }
```

- 遍历：
    - `for key, value in dict.items():`
    - `for key in dict.keys():`
    - `for value in dict.values():`
    - 按顺序遍历 `for key in sorted(dict.keys()):`

更多操作：

- 字典的列表
- 字典中嵌套列表
- 字典嵌套字典

### 循环

- 使用 `break` 和 `continue`
- 设置标志
- 用循环处理列表和字典
    - 删除指定值
    - 移动元素
    - 学习下面这种用法，以列表作为循环条件：

        ```python
        users = ['user1', 'user2', 'user3']
        while users:
            user = users.pop()
            print(user)
        ```

### 函数

```python
def function_name(parameters):
    """docstring"""
    function body
```

#### 参数

- 关键字实参：`function_name(parameter=value)`'
- 默认值：`def function_name(parameter=value)`
    - 在函数定义中，应当将没有默认值的参数放在前面，有默认值的参数放在后面，以便 Python 依然能够正确解读位置实参。
- 禁止函数修改列表：`function_name(list_name[:])` （创建副本）
- 任意数量实参：`def function_name(*parameters)`，`*` 会创建一个空元组，将所有值都封装到这个元组中。
- 任意数量的关键字实参：`def function_name(**parameters)`，`**` 会创建一个空字典，将所有值都封装到这个字典中。

!!! note "参数的顺序"

    -   在定义和调用中，都应当按普通形参、带默认值的形参、任意数量形参的顺序排列。

#### 将函数存储在模块中

- 导入整个模块：`import module_name`
- 导入特定函数：`from module_name import function_name`
- 函数别名：`from module_name import function_name as fn`
- 模块别名：`import module_name as mn`
- 导入所有函数：`from module_name import *`

!!! tip "函数代码规范"

    - 形参指定默认值时等号两边不要有空格
    - 函数调用时，关键字实参等号两边不要有空格
    - 对齐参数列表行

    ```python
    def function_name(
            parameter_0, parameter_1, parameter_2,
            parameter_3, parameter_4, parameter_5):
        function body...
    ```

### 类

#### 编写类的基础

- 与类有关的每个方法都需要 `self` 参数，且必须位于参数列表的第一个位置。
- 类的每个属性都必须有初始值。

#### 继承

```python
class ChildClass(ParentClass):
    """docstring"""
    def __init__(self, parameters):
        super().__init__(parameters)
        self.attribute = value
```

- 子类的方法 `__init__()` 需要父类的方法 `__init__()` 来初始化父类的属性。
- `super()` 是一个特殊函数，帮助 Python 将父类和子类关联起来。
- `super().__init__(parameters)`：调用父类的方法 `__init__()`。
- 重写父类的方法
- 将实例用作属性（其实就是类的嵌套）：一些类的细节越来越多，应当拆分成多个协同工作的小类。

#### Python 标准库

- `collections` 模块：包含很多有用的类
    - `OrderedDict` 类：记录键值对的添加顺序

### 文件和异常

- `with` 语句：在不再需要访问文件后将其关闭。

```python
with open(filename) as file_object:
    contents = file_object.read() # 读取整个文件
    for line in file_object: # 逐行读取
        print(line.rstrip())
```

- `open()`：默认以只读模式打开文件。

!!! question "考考你"

    以下问题如何解决？

    -  读取文件时，空行会出现两次换行
    -  将文件内容全部合并成一行
    -  从文件中读取数字等其他类型的值

文件对象操作：

- `.read()`：读取整个文件
- `.write()`：写入文件。注意不会在末尾添加换行符。

异常：

- `try-except-else` 代码块
- `pass` 语句：什么都不做，只是占位符，使代码结构正确。

### 测试代码

`unittest` 模块：用于核实函数的行为是否符合预期。

- 导入 `unittest` 模块和要测试的函数
- 创建一个继承 `unittest.TestCase` 的类

```python
import unittest
from name_function import get_formatted_name

class NamesTestCase(unittest.TestCase):
    """测试name_function.py"""
    def test_first_last_name(self):
        """能够正确地处理像Janis Joplin这样的姓名吗？ """
        formatted_name = get_formatted_name('janis', 'joplin')
        self.assertEqual(formatted_name, 'Janis Joplin')

unittest.main()
```

- `NamesTestCase` 中所有以 `test_` 开头的方法都将自动运行。
- 常用的断言方法：
    - `assertEqual(a, b)`：核实 a == b
    - `assertNotEqual(a, b)`：核实 a != b
    - `assertTrue(x)`：核实 x 为 True
    - `assertFalse(x)`：核实 x 为 False
    - `assertIn(item, list)`：核实 item 在 list 中
    - `assertNotIn(item, list)`：核实 item 不在 list 中
- `setUp()` 方法：只需创建一次对象，然后在每个测试方法中使用它。
- 测试结果：
    - `.`：测试通过
    - `E`：测试引发错误
    - `F`：测试断言失败

### 最后一点马蜂小建议

- 类名使用驼峰命名法
- 实例名和模块名使用小写字母和下划线
- 每个类定义后都应当包含一个文档字符串
- 每个模块都应包含一个文档字符串

## Projects

### Project 2 数据可视化

#### json 模块

在第 10 章我们学习了 json 模块，现在简单回顾复习文件操作和模块使用：

- `json.dump(data, file_object)`：将 Python 数据结构转换为 JSON 格式并写入文件。
- `json.load(file_object)`：从文件中读取 JSON 格式的数据并转换为 Python 数据结构。

示例：

```python title="remember_me.py"
import json
filename = 'username.json'
try:
    with open(filename) as file_object:
        username = json.load(file_object)
except FileNotFoundError:
    username = input("What's your name? ")
    with open(filename, 'w') as file_object:
        json.dump(username, file_object)
        print("We'll remember you when you come back, " + username + "!")
else:
    print("Welcome back, " + username + "!")
```

#### matplotlib

!!! tip "查阅手册"

    需要时请翻阅手册查找用法

以下功能应该如何实现？

- 绘制：折线图、散点图
- 设置样式：
    - 文字：标题、坐标轴标题
    - 刻度（`tick_params`）：标记、大小、颜色
    - 线条：粗细、颜色
    - 点：大小、颜色
    - 各部分的字体大小

#### 生成数据

完成以下任务：

- 绘制从 1 到 100 的平方图像（列表解析）。
- 用随机漫步方法绘制图像，可以使用散点图和折线图（`random.choice()`）。
- 为图表使用颜色映射。
- 使用 Pygal 生成矢量图形文件。
- 写一个掷骰子实验，一个和多个骰子。

#### CSV 文件

- `csv` 模块：用于读取和写入 CSV 文件。
- `csv.reader(file_object)`：读取文件并返回一个读取器对象，其中包含以逗号分隔的值。
- `next(reader)`：返回文件中的下一行。

其他函数：

- `enumerate()`：返回一个包含索引和值的元组列表。
- `datetime` 模块：
    - `strptime()`：将字符串转换为日期对象。
    -
