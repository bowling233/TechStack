---
tags:
    - Ongoin
---

# C 语言基础

因为复习时交叉阅读中英文版《C Primer Plus》，因此笔记中英混杂，请见谅。

## Data and C

### 1. Remember some basic ranges of data

These are common practice today:

-   long long: 64bits =
-   long: 32bits $\in [-2 147 483 648, 2 147 483 647]$
-   short: 16bits $\in [-32 768, 32767]$
-   int 32bits or 16bits

Which `int` type to choose?

-   First consider `unsigned` types for **counting**: reach higher positive numbers
-   Save storage

### 2. `char` type

| Char | Dec | Hex  |
| ---- | --- | ---- |
| 0    | 48  | 0x30 |
| A    | 65  | 0x41 |
| a    | 97  | 0x61 |

### 3. Escape Sequences

| Sequence | Meaning     |
| -------- | ----------- |
| \a       |             |
| \b       |             |
| \\r      |             |
| \t       |             |
| \\       |             |
| \\\'     |             |
| \\"      |             |
| \\?      |             |
| \0oo     | octal       |
| \xhh     | hexadecimal |

### 4.Other Types

-   `_Bool`: C99
-   Portable types: `stdint.h`, `inttypes.h`
    -   exact-width integer: `int32_t`
    -   minimum width types: `int_least8_t`
    -   fastest minimum width types: `int_fast8_t`
    -   `intmax_t`
-   Complex and imaginary Floating Point:
    -   `float _Complex`
    -   `double _Imaginary`

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
