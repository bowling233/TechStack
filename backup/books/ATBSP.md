# Python 编程快速上手：让繁琐工作自动化

|     出版社     |    作者     | 年份 | 阅读时间 ｜ |
| :------------: | :---------: | :--: | :---------: |
| 人民邮电出版社 | Al Sweigart | 2015 |   2023.07   |

<!-- prettier-ignore-start -->
!!! abstract "本书摘要"

    本书的目的性很强：让你快速上手 Python 在实际应用中最常见的用法，只需要写用完就扔掉的代码。因此它并不会向你介绍很多编程方面的细节，甚至根本不提面向对象等知识。

    在我看来，这本书适合希望快速将 Python 应用到学习工作中的读者。如果你选择 SOP 和 PCC 等书，那么大部分的时间都将花在编程和语言的学习上，并不能立刻将它应用到工作上。

    本篇笔记仅选读以下章节：

    - Ch6. 字符串操作
    - Ch7. 正则表达式
    - Ch8-9. 文件
    - Ch11. Web
    - Ch17. 图像
<!-- prettier-ignore-end -->

## 零散 tips

-   `None` 值：这是 `NoneType` 数据类型的唯一值。如果你希望变量中的值不会和其他东西混淆，你可以使用它。
    -   使用没有返回值的函数进行赋值也会得到 `None`，你可以认为 Python 在这些函数末尾都加上了 `return None`。
-   引用到底是怎么回事？
    -   你可以将变量看作一个包含值的盒子
    -   对于**不可变数据类型**的值，比如**字符串、整型或元组**，盒子里装的就是值本身。
    -   对于**可变数据类型**的值，比如**列表、字典**，盒子里装的是值的引用。
    -   技巧：`copy` 模块：
        -   `copy.copy()`：复制列表或字典这样的可变值。但是，如果列表的里面有列表呢？
        -   `copy.deepcopy()`：同时复制列表、字典或列表中的列表这样的可变值。
-   技巧：`pprint` 模块 漂亮打印：
    -   `pprint.pprint()`：将列表、字典等数据类型打印成漂亮的格式。
    -   如果希望得到字符串，使用 `pprint.pformat()`。

## Ch6. 字符串操作

-   `r` 前缀：原始字符串，不转义。常用于路径、正则表达式。
-   **_三重引号_**：其间的所有引号、制表符或换行都被认为是字符串的一部分。**_Python 的代码缩进规则不适用于三重引号_**，你的缩进也会被打印出来。三重引号推荐这样写，保证输出与代码看起来一致。其中第一行的 `\` 防止文段开头多一个换行符。

```python
print('''\
Dear Alice,
    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.
Sincerely,
Bob''')
```

-   多行字符串还经常用作多行注释。

### 字符串方法集锦

-   `isX()` 系列：`isalpha()`、`isalnum()`、`isdecimal()`、`isspace()`、`istitle()`。
-   转换：`upper()`、`lower()`、`title()`、`capitalize()`、`swapcase()`。
-   查找：`startswith()`、`endswith()`。
-   多字符串：`join()`、`split()`
-   裁剪：`strip()`、`lstrip()`、`rstrip()`。
-   对齐：`ljust()`、`rjust()`、`center()`。

### 剪贴板

使用 `pyperclip` 包（需要安装）可以与系统剪贴板交互。

-   `pyperclip.copy()`：将字符串复制到剪贴板。
-   `pyperclip.paste()`：将剪贴板中的内容粘贴到字符串。

<!-- prettier-ignore-start -->
!!! example "练习"

    从剪贴板上获取多行字符串，将它们转换成 Markdown 格式的列表。

    ```python
    import pyperclip
    text = pyperclip.paste()
    lines = text.split('\n')
    for i in range(len(lines)):
        lines[i] = '* ' + lines[i]
    text = '\n'.join(lines)
    pyperclip.copy(text)
    ```

    关注代码中如何处理换行符。

<!-- prettier-ignore-end -->

## Ch7. 模式匹配与正则表达式

### 使用正则表达式模块

`re` 模块处理正则表达式。

-   `re.compile()`：创建一个正则表达式对象（Regex 模式对象）。
    -   用例：`phoneNumRegex = re.compile(r'\d\d\d-\d\d\d-\d\d\d\d')`
    -   记得用原始字符串。
-   Regex 对象有如下方法：
    -   `search()`：找第一次匹配
        -   输入：一个字符串。
        -   返回：一个 **Match 对象**，包含匹配文本的**第一个**出现的位置。
        -   Match 对象有如下方法：
            -   `group()`：返回匹配的字符串。
                -   输入：一个整数（表示分组），0 或留空表示整个匹配。
                -   返回：对应的字符串。
    -   `findall()`：找所有匹配
        -   输入：一个字符串。
        -   返回：一个**字符串列表**，包含匹配的所有字符串。
        -   如果有分组，返回的是元组的列表。每个元组是一个**匹配**，每个元组中的项是改匹配中的各个分组。
    -   `sub()`：替换操作
        -   输入：两个参数，第一个是用于取代匹配的字符串，第二个是要被替换的字符串。
            -   在第一个参数中，可以使用 `\1`、`\2` 等来引用匹配的分组。
        -   返回：替换后的字符串。

### 正则表达式语法

-   `()` 分组：
    -   分组就是将多个字符当作一个单元。
-   `|` 管道：匹配多个表达式中的一个。
-   `?` 可选匹配：前面的分组出现 0 次或 1 次。
-   `*` 零次或多次匹配：前面的分组出现 0 次或多次。
-   `+` 一次或多次匹配：前面的分组出现 1 次或多次。
-   `{n}` 匹配 n 次：前面的分组出现 n 次。
    -   可以指定一个范围，比如 `{1,3}`。第一或第二个数字可以不写。
-   `?` 非贪心匹配：限制前面的分组匹配尽可能少的文本。
    -   默认情况下，正则表达式是贪心的，即匹配尽可能长的字符串。

字符分类：

-   `\d` 任何数字
-   `\D` 除数字外的任何字符
-   `\w` 任何字母、数字或下划线字符（可以认为是匹配“单词”字符）
-   `\W` 除字母、数字和下划线以外的任何字符
-   `\s` 空格、制表符或换行符（可以认为是匹配“空白”字符）
-   `\S`

使用中括号创建自己的字符分类。

-   `^`：匹配必须发生在字符串开始处。
-   `$`：匹配必须发生在字符串结尾处。
-   `.`：通配符，匹配除换行符外任何字符。
    -   如果要匹配换行符，使用 `re.DOTALL` 作为 `re.compile()` 的第二个参数。
-   大小写无关匹配：使用 `re.IGNORECASE` 或 `re.I` 作为 `re.compile()` 的第二个参数。

### 管理复杂的正则表达式

-   使用 `re.VERBOSE` 或 `re.X` 作为 `re.compile()` 的第二个参数，可以在正则表达式中添加注释。

用例：

```python   
phoneRegex = re.compile(r'''(
    (\d{3}|\(\d{3}\))?              # area code
    (\s|-|\.)?                      # separator
    \d{3}                           # first 3 digits
    (\s|-|\.)                       # separator
    \d{4}                           # last 4 digits
    (\s*(ext|x|ext.)\s*\d{2,5})?    # extension
)''', re.VERBOSE)
```

加了注释，正则表达式就清晰多啦！

使用管道符号可以将多个 `re.compile()` 的第二个参数结合起来使用，比如 `re.compile(r'pattern', re.IGNORECASE | re.DOTALL)`。

