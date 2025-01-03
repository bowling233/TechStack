---
tags:
    - 不完善
---

# C

## 标准库

- 合格程序员：ctype.h、stdio.h、stdlib.h、string.h
- 熟练程序员：assert.h、limits.h、stddef.h、time.h
- 优秀程序员：float.h、math.h、error.h、locale.h、setjmp.h、signal.h、stdarg.h

## 语法

### 零碎

- 三目（ternary）运算符的嵌套结构与 `if-else-if` 类似。

```c
char *colorStr = (value == RED) ? "Red" : (value == BLUE) ? "Blue" : "Unknown";
```

### 词法分析：贪心法

- 术语 **token** （符号）是语言的基本表意单元。字符组成符号。例子: `->`、`file` 都是符号。
    - 同一组字符序列在**不同上下文**中可能属于不同符号。

C 的词法分析遵循**贪心法**：如果该字符可能组成符号，那么再读入下一个字符，直到读入的字符串已经不可能再组成一个有意义的符号。我们举几个可能不恰当的例子来说明贪心法：

```c
a---b
a -- - b
a - -- b

y = x/*p /* p point to the dividen */
y = x / *p

n-->0
n-- >0
n- -> 0

a+++++b
```

### 函数声明

!!! question

    请设计一个 C 语句，调用首地址为 0 的函数。

对于上面这个问题，标准答案是 `(*(void(*)())0)()`。

接下来我们一步步解释这一函数调用。

#### 声明的组成

本书将声明看做由：**类型**和一组**类似表达式的声明符**组成。简单的逻辑就是：对声明符求值时应当返回指定类型的结果。

- `float f, g` 对 `f` 和 `g` 求值应返回 `float`
- `float ff()` 对 `ff()` 求值应返回 `float`
- `float *pf` 对 `*pf` 求值应返回 `float`
- `float *g(), (*h)()` 对 `*(g())` 和 `h()` 求值应返回 `float` （本例中，注意运算符优先级和函数指针的意义）

!!! note "函数指针"

    应当始终理解：函数指针实际表达的意义是 `(*fp)()`。`fp()` 只是简写。在声明中，必须使用前一种形式。这是因为 `()` 的优先级比 `*` 高，所以必须用圆括号将指针 `(*fp)` 括起来。事实上，K&R C 不允许第二种形式的使用。

    再回忆一些相关的知识：

    - 函数名可以代表函数的地址
    - 函数指针类型名最好这样声明：`V_FP_CHARP`，即说明返回值、名称、参数列表。

#### 类型转换符

把声明中的变量名去掉，再用括号封装，就变成了类型转换符，比如对上面的每一例：

- `(float)`
- `(float (*)())`
- `(float *)`
- `(float *())`, `(float (*)())`

我们要想调用地址为 0 的函数，可能会这样想：

```c
(*0)()
```

但是，`0` 应当使用强制类型转换为我们需要的类型，类型转换符是：`(void(*)())`

使用 `typedef` 可以更清晰地解决该问题：

```c
typedef void (*funcptr)();
(*(funcptr)0)();
```

#### 理解 `typedef`

本书给出的理解声明的方式也能让我们更好地理解 `typedef`：直接在声明语句前面加上 `typedef` 就将该声明符作为该声明符的类型的替代。

- `typedef float *pf` 中 `pf` 代表 `float *`
- `typedef float *g()` 中 `g` 代表 `float *()`

#### 例子：`signal()`

!!! note "`signal()` 函数"

    声明在 `<signal.h>` 中，它接受一个代表需要被捕获的特定 signal 的整数值，和一个用户提供的用于处理 signal 函数的指针。

我们先从用户定义的函数开始设计。用户可能会定义这样的处理函数：

```c
void sigfunc(int);
```

因此，我们将 `signal` 函数声明为：

```c
void (*signal(int, void(*)(int)))(int);
```

解释：传递 `(int, void(*)(int))` 参数以调用 `signal` 函数，对 `signal` 的返回值（是一个函数指针类型）解引用得到一个函数，然后传递一个整数给这个函数，最后返回值是 `void`。

### 指针与数组

本节重点理解数组名与指针的概念、数组与指针的转化。

- 除了被用作 `sizeof` 的参数这一情形，其他情况下数组名都代表指向数组首元素地址的指针。

    - 注意，这个首元素可能还是数组，让我们来看一个多维数组的情况：

        ```c
        int calendar[12][31];
        p = calendar;
        ```

        这里的 `calendar` 是一个指向数组的指针。

- 还有 `&array_name` 的情况，得到一个指向数组的指针。
- 因为 `*(a+i)` 与 `*(i+a)` 含义相同，因此 `a[i]` 与 `i[a]` 相同。

对于上面的日历多维数组，我们写一个你可能从来不会这样写的循环：

```c
int (*montp)[31];
for (monthp = calendar; monthp < &calendar[12]; monthp++){
    int *dayp;
    for (dayp = *monthp; dayp < &(*monthp)[31]; dayp++)
        *dayp = 0;
}
```

这个例子仅用于揭示数组与指针的关系，在实际写代码时，千万不要这样做。

### 作为参数的数组声明

将数组作为参数毫无意义，将被自动转换为指向首元素的指针。

但是，请不要假设在其他情况下也有这样的转换。以下两个语句有着天壤之别：

```c
extern char *hello;
extern char hello[];
```

!!! note "编写函数声明时，选择能最清晰表达自己意图的方式"
