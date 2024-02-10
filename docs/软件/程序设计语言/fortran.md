---
tags:
    - 较完善
---

# Fortran

!!! abstract "大部分内容来自《Modern Fotran Explained》2018 版。"

## 第二章 语言元素

### 2.2 Fortran 字符集

- 字符串以外的地方**大小写无关**。
- Fortran 特殊字符：

![fortran_character](graph/fortran_character.png)

### 2.3 Token

- 标签、关键字、名字、常量、运算符、分隔符。
- 部分关键字对之间的空格是可以省略的，比如：`else if`、`end do`、`in out` 等。**一般将其连写，不适用空格形式**。

### 2.4 源文件格式

- 每行最多包含 132 个字符。

!!! tip "更改长度限制"

    在编译某些 Fortran 项目时可能遇到长度超过 132 的代码。如果使用 `gfortran` 编译，可以添加 `-ffree-line-length-512` 将长度限制更改为 512。Fortran 编译选项一般可以在 `./configure` 中使用 `FCFLAG=` 进行设置。

    参见 [StackOverflow: Line truncated, Syntax error in argument list](https://stackoverflow.com/questions/34194589/line-truncated-syntax-error-in-argument-list)

- 使用 `!` 进行单行注释。
- 使用 `&` 标记将语句分布到多行。语句接到下一行开头。
    - 如果下一行开头的第一个非空字符是 `&`，则接到它后面。这样可以切断 Token。
    - `&` 不能为注释跨行。注释可以夹杂在断行之间。

    ```fortran
    type, public :: t_ma& !a line break
        &trix(rows, cols, k)
    ```

- 可以使用 `;` 分隔一行中的多个语句。
- 语句标签：每个语句（不是复合语句的一部分）都可以打标签。标签可以由 1 - 5 个数字组成。不允许全零，允许前导零。

    ```fortran
    100 continue
    ```

    前导 0 并不重要，比如 `10` 和 `010` 是同一个标签。

### 2.5 类型的概念

- 5 种内置类型
    - 每种内置类型（type）都有一个默认的种类（kind）和编译器决定的其他种类。种类由一个非负整数表示。

!!! tip "区分类型（type）及其种类（kind)"

    这或许是初学时非常难以理解的一点：**每个内置类型都有一个默认种类和由编译器决定的其他变种**。每个种类都和一个称为**种类参数（kind type parameter）**的非负整数相关联。比如在 QuickStart 中曾经见过：

    ```fortran
    integer, parameter :: dp = kind(0d0)
    real(kind=dp), parameter :: x = 9.3
    ```

    初学者很可能看不懂 `kind()` 的参数是什么东西。`0d0` 其实是一个双精度浮点数常量，`kind()` 函数返回的参数的 `kind` 值，比如这边就是内置类型 `real` 中的双精度对应的 `kind` 值。使用它作为 `real` 的 `kind` 参数，就可以声明一个双精度浮点数了。

    `kind` 值也可以接在常量后跟一个下划线。比如：

    ```fortran
    integer, parameter :: k6 = selected_int_kind(6)
    -123456_k6 
    +1_k6
     2_k6
    ```

    如果某个编译器上，`k6` 的值就是 `3`，那也可以直接用：`2_3`。

### 2.6 内置类型的字面量

- 数值类型：整数、实数、复数
- 非数值类型：字符、逻辑

#### 整数字面量

- 标准没有规定范围。如果计算机字长为 $n$，范围一般为 $-2^{n-1}\sim 2^{n-1}-1$。
- 定宽整形 `selected_int_kind()`：

    ```fortran
    interger, parameter :: k6 = selected_int_kind(6)
    -999999_k6
    +1_k6
    ```

- 获得种类和范围信息 `range()`、`kind()`

    ```fortran
    kind(1)
    range(2_k6)
    ```

#### 实数字面量

- 标准也没有规定范围和有效位数。一般编译器遵守 IEEE 浮点规范，范围为 $10^{-37}\sim 10^{37}$。
- 指定精度和范围（$10^{-n}\sim 10^n$） `selected_real_kind()`

    ```fortran
    integer, parameter :: long = selected_real_kind(9, 99)
    12.3456789e30_long
    ```

- 除了种类、范围外，还可以获得精度信息 `precision()`。

#### 复数字面量

```fortran
(1., 3.2)
(1.0, 3.7_8)
```

- 复数的类型有以下情况：
    - 如果其中一个分量是整数：类型为另一个分量
    - 如果两个分量均为整数：类型为默认实数类型
    - 如果两个分量均为实数且种类不同：种类为精度最高的一个分量

!!! tip "总结一下：至少是实数，精度取最高"

- 可以查询种类、范围、精度。

#### 字符串字面量

- 可以使用单或双引号引起。在字符串内使用引号有以下两种方式：
    - 重复两次：`"He said, ""Hello!"""`
    - 使用异种引号：`'He said, "Hello!"'`
- 字符串的长度可以是 0：`""`
- 长字符串的写法：

    ```fortran
    long_string =               &
        "This is a long string  &
        & that is continued on  &
        & the next line."
    ```

    - 不允许附加注释。

- 字典序规则
    - 空格小于所有字母和数字。
    - 数字和字母间的顺序并不固定。
    - 其余特殊字符间的顺序也不固定。

!!! tip "记住字典序规则"

!!! info "岁月史书"

    之所以会产生这么奇葩的字典序规则，是因为 Fortran 不仅要支持 ASCII，还要支持如 EBCDIC 等编码。

存储 Fortran 字符集外的字符将在后文介绍。

#### 逻辑字面量

```fortran
.true._1
.false._long
```

非默认种类的逻辑字面量一般用于紧凑地存储逻辑数列。

#### 二进制值常量（boz 常量）

```fortran
b'1001'
z'a2f'
```

- 使用 `b`、`o` 和 `z` 开头，单/双引号引起。
- 长度不允许超过最大整数、实数。
- 使用场景十分有限。

### 2.8 内置类型的标量变量

- 声明语句可以接受参数
    - 只有字符接收两个参数（多了一个 `len`），其他都只接受一个参数即 `kind`
        - 无名参数默认为长度参数

```fortran
! 这两个等价
integer(kind=4) ::i
integer(4) :: i
! 这两个不等价
character(kind=4) :: c
character(4) :: c
```

### 2.9 派生类型

```fortran
type point
    real :: x, y
end type point
type triangle
    type(point) :: a, b, c
end type triangle
```

- 成员选择器 `%`：`triangle%a`。
- 派生类型字面量：`person('Smith', 'John', 42)`
- 复数类型有伪成员 `re` 和 `im`，也可以通过内置函数 `real()` 和 `aimag()` 获得。

### 2.10 内置类型的数组

!!! note "一些术语"

    - rank：数组的维数。
    - extent：每个维度的大小。
    - shape：每个维度的大小组成的元组。

!!! tip "Fortran 数组下标默认从 $1$ 开始。"

- 定长数组
    - 使用 `dimension` **属性**声明
    - 可以指定头尾元素的下标
    - 支持最多 15 维
    - 如果名字后面跟了自己的维度信息，那么 `dimension` 属性将不会作用于该数组。

    ```fortran
    real, dimension(10):: a
    real, dimension(-10:5)::vector
    real, dimension(-10:5, -20:-1)::grid
    integer, dimension(10) :: c, d, e(8, 7)
    ```

- 有些语句数组序迭代数组中的元素：先迭代外层的维度

    ```text
    grid(-10, -20, 0, -15, 1, 1, 1)
    grid( -9, -20, 0, -15, 1, 1, 1)
    ...
    ```

    - 但标准并不要求数组按这样的顺序存放
- 切片
    - 数组的切片是一个数组，但不能使用下标访问其中的单个元素

    ```fortran
    c(1:i, 1:j, k) !Rank-two array with extents i and j
    a(ipoint) ! ipoint is a rank-one integer array
    ```

    - designator 不能连用：

    ```fortran
    b(k, 1:n)(l) ! false
    b(k, l) ! correct
    ```

- 数组常量使用 `(/ /)` 或 `[]` 引起，其中可以使用构造器

    ```fortran
    (/ 1, 2, 3, 5, 10 /)
    [1, 2, 3, 4, 5]
    (/ (i, i = 2,8,2) /)
    (/ (i*0.1, i=11,15) /)
    ```

- `allocatable` 属性和 `allocate` 语句：数组的维数在声明时确定，大小在 `allocate` 后确定。

    ```fortran
    real, dimension(:, :), allocatable :: a
    allocate (a(n, 0:n+1)) 
    deallocate (a)
    ```

### 2.11 字符串的子串

- 可以创建字符串的数组。

    ```fortran
    character(len=80), dimension(60) :: page
    ```

!!! tip "注意 `len` 和 `dimension` 的区别"

这种情况下，可以连用数组下标和子串两个 designator：

```fortran
page(j)(i:i)
```

!!! warning "一定要区分字符串和数组"

    作为从 C 转过来的人，很容易以为字符串和数组的处理方式是一样的。在 Fortran 中它们的处理方式完全不一样，典型的就是下面的例子：

    ```fortran
    character(len = 10) :: c = 'hello'
    character :: d
    d = c(1) ! Error: Unclassifiable statement at (1)
    d = c(1:1) ! Correct
    ```

    字符串不能像数组一样使用下标，而是必须使用子串，即使只访问一个字符。

### 指针

`pointer` 属性：

```fortran
real, pointer, dimension(:,:) :: a
```

上面是一个数组指针，而不是指针数组。它可以用于指向一个二维的数组。

!!! note "`nullify()` 函数显式说明指针不指向任何东西。"
!!! note "`allocate` 能够为指针分配空间。"

上面两个函数都能接收多个参数：

```fortran
allocate (son, x(10), y(-10:10), a(n, n))
```

!!! tip "声明指针时总是初始化。"

    ```fortran
    real, pointer :: son => null()
    ```

!!! example "链表结构"

    ```fortran
    type entry 
        real :: value 
        integer :: index 
        type(entry), pointer :: next 
    end type entry
    ```

!!! question "章末练习"

    ??? note "1"

        1. Yes
        2. No
        3. Not Determined
        4. Not Determined
        5. No
        6. Yes
    
    ??? note "2"

        1. Correct
        2. Correct, with commentary
        3. Correct
        4. Correct
        5. Not Correct, with commentary
        6. Initial line
        7. continuation line
        8. Not correct
        9. not correct
        10, not correct

    ??? note "3"

        - `43`: integer
        - `'word'`: string
        - `4.39`: real
        - **`1.9-4`: not legal**
        - `0.0001e+20`: real
        - `'stuff & nonsence`: string
        - `4 9`: not legal
        - `(0.,1.)`: complex
        - `(1.e3,2)`: complex
        - `'I can''t'`: string
        - `'(4.3e9, 6.2)'`: string
        - `.true._1`: logical
        - `e5`: not legal
        - `'shouldn' 't'`: not legal
        - `1_2`: integer
        - `"O.K."`: string
        - `z10`: not legal
        - `z'10'`: integer, hex
    
    ??? note "4"

        Legal names:

        ```fortran
        name
        name32
        quotient
        a183c3
        burn_
        no_go
        lone__name
        ```

    ??? note "5"

        （看错题目了）

        First, Seventh, Last:

        ```fortran
        a(1), a(7), a(11)
        b(0), b(6), b(11)
        c(-11), c(-4), c(0)
        d(10), not exist, d(10) ! 错了，要认清逗号和分号
        e(5), not exits, e(9) ! 同样的错误
        f(1, 0, 1), f(2, 1, 1), f(5, 1, 4)
        [i, i=1, 7]
        ```

    ??? note "6"

        Legal designators:

        ```fortran
        c(2,3)
        c(0,3)
        c(4,3)(:)
        c(5,3)(9) ! 不合法，必须使用字串 `(9:9)` 而非数组下标 `(9)`
        c(5,3)(9:9)
        c(2,1)(4:8)
        c(3,2)(0:9) ! 不合法，这里的不合法是因为从子串的选择应当从 1 开始。
        ```

        这道题强调了书本中的一句话：

        > we could combine the array subscript and character substring notations into
        > 
        > ```fortran
        > page(j)(i:i)
        > ```

        注意：只有数组下标和子字符串两个 designator 可以连用。

    ??? note "7"

        Vehicle registration:

        ```fortran
        type vehicle_reg
            character(len=10) :: make
            character(len=10) :: model
            integer :: year
            character(len=10) :: color
            character(len=10) :: owner
        end type vehicle_reg

        vehicle_reg('Ford', 'Focus', 2010, 'red', 'John Doe')
        ```

        Circle:
        ```fortran
        type circle
            real :: x, y, radius
        end type circle

        circle(0., 0., 1.)
        ```

        将坐标作为向量存储会更好。

        Book:
        ```fortran
        type book
            character(len=10):: title, author
            integer :: pages
        end type book

        book('Modern Fortran Explained', 'Michael Metcalf', 496)
        ```

    ??? note "8"

        ```fortran
        type triplet 
            real, dimension(3) :: vertex
        end type triplet
        type(triplet), dimension(10) :: t
        ```

        Is array:

        ```fortran
        t
        t(1)%vertex
        t(5:6)
        t(5:5) ! 注意：这也是数组！单元素切片是 size = 1 的数组
        ```

    ??? note "9"

        ```fortran
        integer, parameter :: range = selected_int_kind(20)
        integer(kind = rang):: i
        integer, parameter :: range2 = selected_real_kind(12, 100)
        real(kind = range2):: j
        integer, parameter :: range3 = kind(2_"汉字")
        character(kind = range3):: k
        ```

## 表达式和赋值

### 一些表达式规则

- 一元运算符不能紧跟在运算符后面。比如要表达 $x^{-y}$ 必须使用括号 `x**(-y)`。
- 整数的除法将趋零截断。在指数运算时需要特别注意这一点
    !!! danger "`2**(-3)` is `1/(2**3)` is `0`!"
- 混合类型表达式将会统一使用最高级的类型形式的值。
    比如，如果 `a+b` 中 `a` 是整数，`b` 是复数，那么 `a` 将被替换为：

    ```fortran
    complex(a, 0, kind(b))
    ```

    !!! warning "混合类型表达式中的常数并不会自动提升，它会以默认的方式存储。记得为这些常数指定 `kind` 值。"

        如果 `a` 的 `kind` 是 `long`：

        ```fortran
        a/1.7
        a/1.7_long
        ```

        上面的式子不一定比下面的式子更精确。
    !!! info "有关复分析的内容：任意实数都能被写为复数的幂，关于 raising a complex value to a complex power 的数值方面的问题，请参阅书本。"

### 已定义和未定义的变量

变量必须在定义的状态才能使用：

- 数组：其中的每个元素都被定义
- 派生类型：其中每个非指针元素都被定义
- 字符串：每个字符都被定义

可能出现数组中一个元素失去定义，而导致整个数组被视为未定义的情况。

对于指针，它是否定义取决于它关联的对象是否定义。因此**指针还有另一层状态：关联和未关联**。即使它已经关联了某个对象，它仍有可能未定义。

### 比较

大部分都和 C 一样。除了字符串可以直接比较（按字典序）。

### 逻辑运算

```fortran
logical :: i,j,k,l
( .not.k .and. j .neqv. .not.l) .or. i
```

支持短路运算。

### 字符串运算

`//` 连接两个字符串：

```fortran
word1(4:4)//word2(2:4)//’S’
```

值得注意，未定义的字符在比较中总是会使比较错误：

```fortran
character(len=5) :: fill 
fill(1:4) = 'AB'
fill == 'AB'
```

事实上，`fill` 现在的状态是 `AB  x`，即 AB 后跟两个空格，再是一个未定义的元素。如果将 `fill(1:5)` 上面的片段就会正确。

赋值的两侧可以重叠，比如 `result(3:5)=result(1:3)`。

关于 ASCII、EBCDIC 和 ISO 10646 编码的使用问题，请参阅书本。

### 自定义运算符

将涉及到模块、函数等知识，这里仅浅提一下：

- 需要在模块中设置函数、特定 intent 的参数、接口块

```fortran
type interval
    real :: lower, upper
end type interval

function add_interval(a,b)
    type(interval) :: add_interval
    type(interval), intent(in) :: a, b
    add_interval%lower = a%lower + b%lower
    add_interval%upper = a%upper + b%upper
end function add_interval

interface operator(+)
    module procedure add_interval
end interface 
```

运算符可以是任意内置运算符，或者使用小数点包裹的不超过 63 个字符的序列。比如 `.sum.`。只需要设置好接口即可：`interface operator(.sum.)`。不能覆盖内置类型已经定义好的运算符。

### 自定义赋值

派生类型的赋值行为可以自定义。可以为不同类型间定义赋值。

与自定义运算符不同的，就在于使用 `subroutine` 和 `assignment` 接口：

```fortran
subroutine real_from_interval(a,b) 
    real, intent(out) :: a
    type(interval), intent(in) :: b 
    a = (b%lower + b%upper)/2
end subroutine real_from_interval

interface assignment(=) 
    module procedure real_from_interval
end interface
```

内置的赋值会为派生类型的所有非指针成员赋值，包括已经重定义了赋值的成员。

!!! tip "和 C++ 的类型体系行为有些相似。"

### 数组表达式

!!! tip "有点像 NumPy。"

一元、二元运算符都可以用于数组。二元运算符要求两个操作数的形状相同，或其中一个是标量（可以广播）。

```fortran
real, dimension(10,20) ::a,b
real, dimension(5)::v
a + b
a == b ! 注意这里会产生一个布尔数组，而不是只有一个布尔值
a(2:9,5:10) + b(1:8,15:20) ! 注意对应关系只用于形状，而与下标无关
```

第 7 章将介绍，我们可以对特定维度的数组定义不同的数组运算。

### 数组赋值

按元素赋值、广播赋值。

和一维的情况一样，赋值右侧的操作数在赋值发生前会被求值。如下：

```fortran
v(2:5) = v(1:4)
```

赋值的顺序、上面数组表达式的求值顺序都没有固定，预留了优化空间。

### 表达式中指针

!!! note "不需要显式解引用指针就能使用关联的对象。"

    这意味着，如果赋值语句的两端都是指针，相应的对象将被赋值，而不是指针被赋值。
!!! note "术语 target"

    target 指的是指针所关联的对象。书本上的原话如下：

    > -   A pointer may appear as a variable in the expressions and assignments that we have considered so far in this chapter, provided it has a valid association with a target.
    > -   The target is accessed without any need for an explicit dereferencing symbol.
    > -   In particular, if both sides of an assignment statement are pointers, data are copied from one target to the other target.

如果需要对指针本身进行赋值，应当使用 `=>` 运算符。

```fortran
pointer => target
```

当然指针不能指向指针，target 为指针时，发生指针的拷贝，指针的 `state` 也会被拷贝。

target 甚至可以是返回指针值的 `function`。

派生类型赋值时，指针也会被赋值：

```fortran
allocate (current)
current = entry(new_value, new_index, first)
! 上面执行了 current%next => first
```

这里还有个属性 `target`。如果变量要作为指针的 target，那么它必须带上 `target` 属性。
