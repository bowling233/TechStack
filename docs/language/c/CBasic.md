---
tags:
    - Ongoin
---

# C 语言基础

因为复习时交叉阅读中英文版《C Primer Plus》，因此笔记中英混杂，请见谅。

## 总体结构

结合 C Primer Plus 和自己的见解，对 C 语言的基础知识作如下分类：

-   基本概念：C 语言是什么？编程机制等。
-   基础知识
    -   数据
    -   运算符和表达式
    -   字符串及其操作
    -   关键字
-   控制语句
-   函数
-   指针
-   内存管理
-   文件
-   高级数据表示
-   位操作
-   预处理器
-   C 库

## 基本概念

-   使用 C 语言的 7 个步骤：
    -   定义程序目标
    -   设计程序
    -   编写代码
    -   编译
    -   运行程序
    -   测试和调试程序
    -   维护和修改程序

<!-- prettier-ignore-start -->
!!! tip 
    
    平常写题时我们很可能并不关注这一流程，但我觉得这一流程代表一个良好的习惯：先好好思考再行动。我们总是喜欢遇到问题直接着手写代码，但如果能先进行分析，用自然语言/伪代码表述出程序的框架，就能让写代码的过程更加流畅。
<!-- prettier-ignore-end -->

-   C 语言的标准和发展：

    -   _K&R C_ 指的是书本 _The C Programming Language_，被认为是第一版的 C 标准。
    -   第一个 _ANSI/ISO C_ 定义了 C 语言和 C 标准库，是更全面、严格的标准。
        -   它的最终版本是 _C89_。
    -   _C99_ 主要做了 3 件事：国际化、弥补缺陷和提高计算实用性。
    -   _C11_ 尚未得到广泛应用。

-   编程机制：为什么要经过这些特殊的步骤才能得到 C 程序？
    -   过程中涉及的文件有：源代码文件、目标代码文件和可执行文件。
    -   过程中涉及的工具有：编译器和链接器。
    -   这样做是为了模块化：更改某个模块时，不用重新编译其他模块。

<!-- prettier-ignore-start -->
!!! info
    
    关于编译的详细信息可以参考 [gcc](../../basic/linux/tools/gcc.md)。通常使用的编译器相关套件有 GUN（`gcc`） 和 LLVM（`clang`）。
<!-- prettier-ignore-end -->

-   关键字：[CPP reference](https://en.cppreference.com/w/c/keyword) 提供了 C 语言关键字的表单。

## 数据

### 基本数据类型

以下是 C 语言中的数据类型关键字：

| Keyword  | Keyword     |
| -------- | ----------- |
| int      | double      |
| long     | signed      |
| short    | void        |
| unsigned | \_Bool      |
| char     | \_Complex   |
| float    | \_Imaginary |

<!-- prettier-ignore-start -->
!!! note "考考你"
    
    * 什么是位、字节和字？
    * 你知道这些数据类型的位模式是什么吗？常见的语言教材都不作具体介绍，[计算机科学导论](../../books/计算机科学导论.md) 和 [深入理解计算机系统](../../books/深入理解计算机系统.md) 做出了详细的解释。
<!-- prettier-ignore-end -->

布尔类型：

-   `_Bool`: C99

<!-- prettier-ignore-start -->
!!! tip "true 和 false"
    
    在 C23 中，它们终于成为了关键字。
<!-- prettier-ignore-end -->

#### 整型

<!-- prettier-ignore-start -->
??? tip "关于七七八八的整数类型"
    
    在三个修饰符 `short`、`long` 和 `unsigned` 的加持下，C 能表示各种各样的整数。
    
    * `short` 是有符号类型，占用空间**可能**比 `int` 少。
    * `long` 同样是有符号类型，占用空间**可能**比 `int` 多。
    * `long long` 至少占 64 位，**可能**比 `long` 多。
    
    为什么要搞出这么奇怪的东西？因为 C 标准**只规定了基本数据的最小大小**😓。
<!-- prettier-ignore-end -->

以下是整型数据常见的实现：

-   long long: 64 bits
-   long: 32 bits $\in [-2 147 483 648, 2 147 483 647]$
-   short: 16 bits $\in [-32 768, 32767]$
-   int 32 bits or 16 bits (depend on size of word)

Which `int` type to choose?

-   First consider `unsigned` types for **counting**: reach higher positive numbers
-   Save storage

整型字面量数据有一些前后缀：

-   `0` 八进制
-   `0x` 或 `0X` 十六进制
-   `L` long 常量
-   `U` unsigned 常量

<!-- prettier-ignore-start -->
!!! bug "整数溢出"
    
    在 C 语言中，整数溢出是未定义的行为。
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
??? info "可移植的整数类型"
    
    蛮复杂的，不想关心这块内容，随手记一下。
    
    -   Portable types: `stdint.h`, `inttypes.h`
        -   exact-width integer: `int32_t`
        -   minimum width types: `int_least8_t`
        -   fastest minimum width types: `int_fast8_t`
        -   `intmax_t`
    -   Complex and imaginary Floating Point:
        -   `float _Complex`
        -   `double _Imaginary`
<!-- prettier-ignore-end -->



### 字符

字符常量是以数值形式存储的，编译器会将字符常量转换为数值，并且视为 `int` 类型。

<!-- prettier-ignore-start -->
??? tip "米奇妙妙屋"
    
    上文提到，字符常量被视为 `int` 类型。那么，在 `int` 为 32 位的系统上，我们可以定义字符常量 `FATE`，把 4 个独立的 8 位字符储存在一个 32 位存储单元中。但如果将该值赋给 `char` 类型，只有最后 8 位（低 8 位）有效。编译器会为该操作抛出警告。
<!-- prettier-ignore-end -->

以下是值得记忆的字符的 ASCII 码。值得注意的是，大小写字母之间的间距只有 7。

| Char | Dec | Hex  |
| ---- | --- | ---- |
| 0    | 48  | 0x30 |
| A    | 65  | 0x41 |
| Z    | 90  | 0x5A |
| a    | 97  | 0x61 |

以下是一些常用的转义序列（Escape Sequences）

| Sequence | Meaning     |
| -------- | ----------- |
| \\a       |             |
| \\b       |             |
| \\r      |             |
| \\t       |             |
| \\\\       | backslash |
| \\\'     |             |
| \\"      |             |
| \\?      |             |
| \\0ooo     | octal       |
| \\xhh     | hexadecimal |

<!-- prettier-ignore-start -->
!!! note "八进制的表示容易引起困惑"
    
    遇到一些字符串考题，如 `"abc\087"` 打印的结果是 `abc`。八进制转义序列以 `\0` 开头容易与空字符混肴，要牢记这一点。八进制 ASCII 最大到达了 0177（127，0x7F）。
<!-- prettier-ignore-end -->

## Format Strings and Formatted IO

-   `strlen()`
-   `const`
-   symbolic constants

### 4.1 Introductory Program

### 4.2 Character Strings: An Introduction

-   `scanf()` stops reading at the first _whitespace(blank, tab, or newline)_
-   `strlen()` gives the length of a string in characters, **NOT includes the `'\0'` (but `sizeof()` includes)**
-   two methods to **handle long `printf()` statements**: **spreads over two lines** or printf one line twice
-   `%zd` for return value of `sizeof` and `strlen()`

### 4.3 Constants and the C Processor

-   symbolic constants:
    -   name tells you more than number
    -   easily change the value in several places
-   `#define`: compile-time substitution, done by **preprocessor** (before compiler)
-   manifest constants (字面量)
-   capitalize constants is a good behaviour, or use prefix `c_` or `k_`
-   round (四舍五入)
-   `const` : allows you to declare a type
    > see Chapter 12 Storage Classes, Linkage, and Memory Management
    > `enum` in Chapter 14 is also constants
-   `limits.h`
    -   `INT_MAX`
    -   `INT_MIN`
    -   `CHAR_BIT`
    -   `SHRT_MAX`
    -   `UINT_MAX`
    -   `ULLONG_MAX`
    -   ...
-   `float.h`
    -   `FLT_DIG` : minimum number of significant decimal digits for a float
    -   `DBL_DIG`
    -   `FLT_MIN` : minimum value for a positive float retaining full precision
    -   `FLT_EPSILON` : difference between 1.00 and the least float value greater than 1.00

### 4.4 Exploring and Exploiting printf() and scanf()

#### `printf()`

-   **conversion specifications:** specify how the data is to be converted into displayable form
    -   `%%`
    -   `%g`
    -   `%i` = `%d`
-   control-string
-   **conversion specification modifiers**
    -   `digit`: minimum filed width
    -   `.digit`: precision (specially for `%g`, the maximum number of significant digits; `%s`, the maximum number of characters to be printed; `integer`, minimum number to appear)
    -   `h` and `hh`: short, char
    -   `j`: `intmax_t` type...
    -   `l` and `ll`: for long, long long integer
    -   `L`: for long double
    -   `t`: for `ptrdiff_t` value `%td`
    -   `z`: for `size_t` value `%zd` (`sizeof, strlen`)
        -   reason for `z` and `t` is portability: the underlying type for `size_t` vary between machines
-   flags
    -   `-`: left-justified
    -   `+`: signed values displayed with sign
    -   `space` : signed values are displayed with a leading space, negative with a minus
    -   `#`:
        -   for `o` and `x`: print `0x`
        -   for `float` : guarantees a decimal-point is printed
    -   `0` : pad the field width with **leading zero** (ignored with - or precision\[int\])

> How does printf() handle mismatched conversion specifiers?
>
> -   **Passing Arguments:** When the computer puts these values on the **stack**, it is guided by the **types of the variables**, not by the conversion specifiers
> -   But printf() **reads them from the stack** according to the conversion specifiers: the conversion specifiers indicates how many bytes `printf()` should read
> -   usually reads **the first n bytes** in the stack

-   return value of `printf()`: the number of characters it printed; negative value if output error

#### `scanf()`

Simple rules for arguments:

-   basic variable types: precede with `&`, (**include array item `&a[n]`**)
-   string: don't use `&`

About blank skipping:

-   Consecutive conversion specifications: `%d%f%s`, skip over the whitespace **in between, except for `%c`**

-   **conversion specifications:**
    -   float and double are the same
-   **conversion specifications modifiers:**
    -   `*`: suppress assignment

## Arrays and Pointers

### 10.1 Arrays

-   Initialization
    -   _Note:_ Using `const` with Arrays
    -   _Note:_ Storage Class Caveat
    -   Partially initialize an array: the remaining elements are set to 0
    -   **sizeof:** `sizeof array` is the size of the whole array in bytes, `sizeof array[0]` is the size of one element in bytes
-   **Designated Initializers (C99):**

    -   pick and choose which elements are initialized
    -   **subscript**

-   Assigning Array Values
-   **Array Bounds:**

    -   It's your responsibility. **_The compiler isn't required to check for you!_**
    -   One simple habit to develop is to use a symbolic constant in the array declaration and in other places the array size is used.

-   **Specifying an Array Size**: use a _constant integer expression_, **a const value isn't**, and the value must be greater than 0

### 10.2 Multidimensional Arrays

-   Initializing a Two-Dimensional Array
-   More Dimensions

### 10.3 Pointers and Arrays

-   array notation is simply a disguised use of pointers: **the C standard describes array notation in terms of pointers** :`ar[n]` means `*(ar + n)`
-   an array name is also the address of the first element of the array
-   `%p` specifier
-   when you say "add 1 to the pointer," C adds one **storage unit**, and the pointer is increased to the **next element**
-   **_Precedence:_** indirection operator `*` is higher than `+`
-   The compiler produces the same code for either pointer method or array method.

### 10.4 Functions, Arrays, and Pointers

-   Question: array as parameter [stackflow](https://stackoverflow.com/questions/25680014/find-the-size-of-integer-array-received-as-an-argument-to-a-function-in-c)

    -   Explanation: `arr` is identified as an array only in its scope. When you pass `arr` to a function, `arr` is regarded as `int *`
    -   Remember: you can only pass a point but not an array

-   Escape Sequence related to pointers

| Escape Sequence | Meaning                     |
| --------------- | --------------------------- |
| %zd             | sizeof                      |
| %td             | difference between pointers |

-   **NOTICE:** one-past-the-end pointer is not guaranteed to be derefenced
-   **Precedence:** unary operators `*` and `++` have the same precedence but associate **from right to left**

### 10.5 Pointer Operations

-   assignment
-   value finding (dereferencing)
-   taking a pointer address
-   adding an integer to a pointer
-   incrementing a pointer
-   subtracting an integer from a pointer
-   decrementing a pointer
-   differencing
-   comparisons

### 10.6 Protecting Array Contents

-   Using `const` with Formal Parameters
-   More about `const`
    -   When you try to modify an `const` variable, you'll receive a **compile-time** error.
    -   **Pointers to constants** can't be used to change values: `const type * ptc`
        -   but `ptc` itself can be changed
        -   valid to assign the address of either **constant or non-constant** data to `ptc`
    -   **const pointers:** `type * const cp` can be used to change values

### 10.7 Pointers and Multidimensional Arrays

Example:

```
int zippo[4][2];
```

-   In value: `zippo` = `zippo[0]`
    -   **NOTICE:** `zippo[0][0] = *(zippo[0]) = **zippo` is not a pointer. It's a int value.
-   The **size of the referred-to object** differ.
-   `zippo = &zippo[0]`: actually `zippo` is an address of an address
-   `*zippo = zippo[0] = &zippo[0][0]`
-   So: `*(*(zippo + 1) + 2) = zippo[1][2]`
-   **Pointers to Multidimensional Arrays**
    -   `[]` has a higher precedence than `*`
    -   `int (* pz)[2]`: points to **an array of 2 ints**
    -   `int * pax[2]`: **an array** of two pointers-to-int
    -   You can use `pz` as `zippo`: `pz[1][2]`
-   **Pointer Compatibility**
    -   **DONOT** assign non-const to const
    -   **DONOT** assign nested pointer types: const qualifier disregarded, behavior undefined

> #### _C_ const and _C++_ const:
>
> Not identically.
>
> -   C++ allows using a const integer value to _declare an array size_
> -   C++ has _stricter rules_ about _pointer assignments_: you're **NOT** allowed to assign a const pointer to a non-const pointer.

-   **Functions and Multidimensional Arrays**

    -   How to make proper declaration for function arguments in functions that process multidimensional array

-

### 10.9 Compound Literals (C99) 复合字面量

-   **Question:** What's the difference between **symbolic constant** and **literals**
-   Example: `(int []){10, 20}`, `(int [2][3]){{1, 2, 3}, {4, 5, 6}}`
-   identified as an array, translates to the **address of the first element**
-   Typical use: pass information to a function **without having to create an array first**
-   **NOTICE:** providing values that are needed only temporarily, has **block scope**

## Character Strings and String functions

-   functions
    -   gets, gets_s, fgets, puts, fputs
    -   strcat, strncat, strcmp, strncmp, strncpy, strncpy, sprintf, strchr
-   command-line arguments

### 11.1 Representing Strings and String I/O

-   `puts()`: only displays strings, _automatically appends a newline_

Ways to _define strings_:

-   Character String Literals (String Constants)
    -   string literals that are separated by nothing or by whitespace will be _concatenated_
    -   placed in the **static storage class**, stored just once and lasts for **the duration of the program**
    -   the entire quoted phrase acts as a **pointer** to where the string is stored
-   Character String Arrays and Initialization
-   **Nodus: Array vs Pointer**
    -   Array:
        -   the memory for the array is allocated only **after the program begins running**, and the quoted string is **copied into the array**
        -   there are two copies of the string: one is the string literal in static memory, one is the string stored in the array (in dynamic memory)
        -   the array name is an **address constant**
    -   Pointer:
        -   just set aside one more storage location for the pointer
        -   **you should declare is as pointing to `const` data**
        -   The compiler has **the freedom** to store a literal that’s used more than once in one or more locations.
        -   the part of **memory** used for static data is different from that used for dynamic memory, the memory used for array (compiler even uses a different number of bits to represent the two kinds of memory)
        -   **NOTICE:** In short, don’t use a pointer to a string literal if you plan to alter the string.
    -   Arrays of Character Strings
        -   array of pointers
            -   don’t necessarily have to be stored consecutively in memory
        -   array of arrays
            -   each array has the same length

### 11.2 String Input

1. Creating Space
    1. Don’t expect the computer to count the string length as it is read and then allot space for it.
2. Read Strings: `scanf()`, `gets()`, and `fgets()`

3. `gets()`: read an entire line, discards the newline character
    1. C11 has dropped `gets()` from the standard
4. `char *fgets(char *str, int count, FILE *stream)`
    1. reads the newline
    2. reads up to **n-1** characters or newline
    3. return the same address as the first argument or NULL pointer if _encounters EOF_
    4. **NULL** pointer is guaranteed not to point to valid data, can be represented by **0 and the marco `NULL`**
    5. the presence or absence of a newline character in the stored string can be used to tell **whether the whole line was read**
5. `int fputs(const char *str, FILE *stream)`
    1. doesn't automatically append a newline
    2. **NOTICE: The system uses buffered I/O.** This means the input is stored in temporary memory (the buffer) until the **Return key** is pressed. On output, when a **newline is sent**, the buffer contents are sent on to the display.
6. `gets_s()`: C11's optional function, DO NOT use

7. `scanf()`: starts at the first non-whitespace character, runs up to (_but not including_) the next whitespace character (blank, tab, or newline)

    but you can specify a field width

8.

### 11.3 String Output

### 11.4The Do-It-Yourself Option

### 11.5 String Functions

### 11.6 A String Example: Sorting Strings

### 11.7 The `ctype.h` Character Functions and Strings

### 11.8 Command-Line Arguments

### 11.9 String-to-Number Conversions

## 高级主题

这里提供了高级主题的笔记索引：

-   [运算符汇总](Operator.md)
-   [内存管理](StorageClasses.md)
-   [文件 IO](FileIO.md)
-   [结构和数据类型](Structures.md)
-   [位运算](BitFiddling.md)
-   [预处理器与宏](Macro.md)
-   [高级数据表示](ADT.md)
