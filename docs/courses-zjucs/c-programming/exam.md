# C 大程历年卷简单整理

> 感谢和我一起做历年卷分析和整理的 uu 们：
>
> Anston Sun、45gfg9、sanaka、TH 讠 NK、cxy

## 常见问题

### 怎么读声明？

-   详见：[Reading C type declarations (unixwiz.net)](http://unixwiz.net/techtips/reading-cdecl.html)

### 函数与函数指针

> Author：45gfg9、Anston Sun

首先，让我介绍一下两个惹人喜爱的小家伙。

```c
int function(int arg)
{
    return 2 * arg;
}
```

一般通过函数，**类型是 `int (int)`**。

```c
int (*func_ptr)(int);
```

芝士什么？芝士函数指针，**类型是 `int (*)(int)`**。

那么，这两个小家伙能干什么呢？

```c
func_ptr = &function;
func_ptr = function;
```

前者是什么？指针。没错，平平无奇的取地址操作，洒洒水啦。
后者是什么？我们知道指针的值实际上是某块内存地址，不考虑奇技淫巧的话，将所指对象的值赋值给指针是没有意义的。但是，将函数指代器 `function` 赋值给函数指针 `func_ptr`，却没有产生任何问题。

坏了，自动播放妈妈生的，大脑要打高端局了。不过你先别急，这个看起来不知所云的赋值语句，其实与前者完全等效。C 标准是仁慈的，它不忍心看到被函数绕晕的初学者面对错误的解引用不知所措，于是规定了函数到指针的*隐式转换*。

> #### 函数到指针转换
>
> 任何函数指代器表达式，在用于**异于下列语境**时
>
> -   作为取址运算符的操作数
> -   作为 `sizeof` 的操作数
>
> 会经历到指向<u>表达式所指代函数</u>的指针的转换。

这里 `function` 经过一次隐式转换变成 `&function`。这一步转换并不改变值，而**类型从 `int (int)` 变成 `int (*)(int) `** 了。也就是实际上在编译器看来，第二行就是第一行。

现在你已经对函数和函数指针有了一定了解，就让我们看一看下面这个简单的例子，把我们已经学到的知识运用到实践中吧。

请解释以下代码的作用：

```c
// 试试看！
(*(void(*)())0)();
```

好吧，这样的表达式或许对你来说为时尚早。我们换一个简单点的例子。

```c
function(20);
(function)(20);
(*&function)(20);
(&function)(20);
(*function)(20);
(***********function)(20); // 不用数了，11 个
```

先不管第六个是什么东西。我们看看前五个。

第一个不能再熟悉了，一个人畜无害的函数调用。

第二个看着和第一个差不多……没错，相信自己，它们完全一样。

第三个呢？没错，取地址再解引用，除了出题没有用。连编译器都会毫不犹豫地优化掉。

第四个开始奇怪了起来。缺失的解引用并非粗心大意，它象征着我们玩转指针的自信与惬意，以及捍卫指针地位的决心。鉴于 **C 标准允许通过函数指针调用函数**，编译器对此也没什么意见。

第五个换了种折磨方式。聪明如你早已料到最后的结果。但是为什么？引言定真，鉴定为隐式转换惯的。回忆一下**函数到指针的隐式转换**，`*function` 等效于 `*&function`，这下看懂了。

现在第六个你应该也能理解了。每次尝试对 `function` 解引用，都会迫使编译器将它转换为函数指针，以满足你对代码风格的奇怪癖好。

还是看看远处的 `func_ptr` 吧家人们。

```c
(*func_ptr)(20);
func_ptr(20);
(****func_ptr)(20);
(&func_ptr)(20);
```

第一个，简单易懂的指针解引用，相当于上面的第二个。

第二个，人畜无害的函数指针调用函数，相当于上面的第四个。

第三个，函数到指针的隐式转换发生了整整三回啊三回，类似上面的第六个。

**第四个，编译器跟你爆了**。怎么会是呢？我们不妨拆开看看：

```c
int (*func_ptr)(int) = &function;    // 这是之前的
int (**second_ptr)(int) = &func_ptr; // 这是我们正在做的
second_ptr(20);                      // 我们想这样
```

在这里，`second_ptr` 已经是个二级指针了。**函数到函数指针（它是个一级指针）的变化，地址值是不会改变的，就是这个函数的可执行代码所在的位置**。问题在于，二级指针的值不是 `function` 的地址，而是 `func_ptr` 这个变量的地址。这还得了，骗自己可以，骗兄弟也就算了，编译器可不吃你这套。

接下来，我们再看点不太一样的：

```c
int func_two(int a, int f(int arg))
{
    return 3 * f();
}
```

这是什么？函数，调用一下：

```c
// function 如上文定义
int function(int arg);

int a = 1;
int b = func_two(a, function);
```

相信聪明的你已经猜到了，`b` 的值就是 6。桥豆麻袋，好像有哪里不太对劲。`func_two` 的两个参数类型分别是 `int` 和 `int (int)`，但是调用时却传入了一个函数指针（还记得隐式转换吗？），这却没有产生任何问题。这又是什么操作？

又是隐式转换？Bingo！不过需要注意发生隐式转换的位置。`func_two` 的第二个形参实际上是 `#!c int (*)(int)` ，而非字面上的 `int (int)`。这就和 `void f(int a[])` 实际上就是 `void f(int *a)` 一样，同样是出于节约资源的考虑。也就是说，编译器眼中的 `func_two` 是 `int func_two(int a, int (*f)(int)`。搞清楚这一点，其余部分也就顺理成章了。

经过练习，你应该已经可以看出，从**函数到指针的隐式转换**规定出发，理解上述情景并非难事。对函数指针的畏惧，往往是因为不熟悉转换规则，或受复杂的声明语法干扰。因此，提高识别类型的熟练度，足以让你自信运用函数指针。

### 图形库

简要整理一下 `libgraphics` 用法：

#### 必备函数

图形与文字

> 值得注意的一点是：`libgraphics` 的坐标系统与 `ACLLib` 不同。前者以左下角为原点，符合我们常用的数学表达；后者以左上角为顶点，使用窗口坐标系统。
>
>   <img src="https://cdn.bowling233.top/images/2023/06/202306232338094.png" style="zoom:50%;" />

-   `void InitGraphics(void)`：使用图形库中的函数前调用
-   `void MovePen(double x, double y)`：将笔移动到某点（注意不是相对移动）
-   `void DrawLine(double dx, double dy)`：从当前点 $(x,y)$ 画到 $(x+dx, y+dy)$ 的线，画笔随之移动
-   `void DrawArc(double r, double start, double sweep)`：以当前点为圆心，从 $\phi=start$ 角开始，画半径为 $r$，圆心角为 $\Delta\phi=sweep$ 的圆弧。<img src="https://cdn.bowling233.top/images/2023/06/202306232336927.png" style="zoom: 50%;float:right" />
-   `double GetWindowWidth(void)`：获取窗口宽度
-   `double GetWindowHeight(void)`
-   `double GetCurrentX(void)`：获取当前画笔的位置
-   `double GetCurrentY(void)`
-   `void DrawTextString(string text)`：在当前位置打印字符串
-   `double TextStringWidth(string text)`：获取该字符串打印时的宽度

关于 `SetEraseMode()` 和 `GetEraseMode()` 我直接把注释贴在这了，直接读吧：

```c
/*
 * Function: SetEraseMode
 * Usage: SetEraseMode(TRUE);
 *        SetEraseMode(FALSE);
 * ---------------------------
 * The SetEraseMode function sets the value of the internal
 * erasing flag.  Setting this flag is similar to setting the
 * color to "White" in its effect but does not affect the
 * current color setting.  When erase mode is set to FALSE,
 * normal drawing is restored, using the current color.
 */

void SetEraseMode(bool mode);

/*
 * Function: GetEraseMode
 * Usage: mode = GetEraseMode();
 * -----------------------------
 * This function returns the current state of the erase mode flag.
 */

bool GetEraseMode(void);
```

控制台交互：这些源代码在 `simpio.h` 中

-   `void InitConsole(void)`：打开一个新的控制台，要使用 `stdio.h` 中的标准输入输出函数前记得写上这个。

-   `int GetInteger(void)`：从标准输入中读入一行，并尝试读取一个整数。如果遇到意外情况，会要求用户重新输入。源码如下：

    ```c
    int GetInteger(void)
    {
        string line;
        int value;
        char termch;

        while (TRUE) {
            line = GetLine();
            if (line == NULL) Error("GetInteger: unexpected end of file");
            switch (sscanf(line, " %d %c", &value, &termch)) {
              case 1:
                FreeBlock(line);
                return (value);
              case 2:
                printf("Unexpected character: '%c'\n", termch);
                break;
              default:
                printf("Please enter an integer\n");
                break;
            }
            FreeBlock(line);
            printf("Retry: ");
        }
    }
    ```

-   `double GetReal(void)`：读取一个实数，具体同上。

-   `string GetLine(void)`

-   `string ReadLine(FILE *infile)`：从指定的文件中读入一行。

#### 定时启动——计时器回调

> Author: Anston Sun

计时器用于延时或重复执行同类任务。相比钟表等纯粹的计时工具，计时器更接近于日程安排。计时器的核心功能如下：每经过*预先设定的时长*，计时器便会*通过某种机制*，执行*特定的指令*。

`libgraphics` 库通过*事件回调机制*实现定时触发的功能。回调机制此处不再赘述。

##### 计时器

与计时器相关的函数如下：

-   `void startTimer(int timerID, int interval)`
-   `void cancelTimer(int timerID)`

顾名思义，两个函数分别用于启动与终止定时器。`interval` 是*预先设定的时长*，即每两次触发的时间间隔。`timerID` 为计时器的标识符，可理解为计时器的专用名称。

为了完成多项定时任务，往往需要分别启动多个间隔不同的定时器。由于所有计时器均会触发 `TimerEvent`，在回调函数内需要使用 `timerID` 区分不同的定时器。

##### 回调注册函数

-   `void registerTimerEvent(TimerEventCallback)`：注册计时器事件。 `TimerEventCallback` 类型见下。

##### 回调函数

-   `typedef void (*TimerEventCallback)(int timerID)`

`TimerEventCallback` 是一个函数指针类型，该类型变量指向函数（假设名称为 `func`）的类型为 `void func(int timerID)`。通过回调机制，每当任一计时器到达设定时间时，均会通过该类型函数指针调用 `func` 函数。通过传入的 `timerID`，回调函数内可以区分不同计时器的触发事件，并执行特定操作。

##### 补充思考

以上介绍均集中于重复执行，但是前面提到计时器也可用于延时执行，即在*预先设定的时长*后执行*特定次数*的*特定操作*。结合 `cancelTimer` 函数，想想怎样实现这一目标。

#### 回调函数

```c
typedef void (*KeyboardEventCallback) (int key,int event);
typedef void (*CharEventCallback) (char c);
typedef void (*MouseEventCallback) (int x, int y, int button, int event);
typedef void (*TimerEventCallback) (int timerID);

void registerKeyboardEvent(KeyboardEventCallback callback);
void registerCharEvent(CharEventCallback callback);
void registerMouseEvent(MouseEventCallback callback);
void registerTimerEvent(TimerEventCallback callback);
void startTimer(int id,int timeinterval);
```

因为这些回调函数在 `graphics` 库中都没有注释，我就不作解释了，课上都讲过回调函数怎么用。

-   计时器：以 20 年程序填空第 3 题为例：

    ```c
    void Main()
    {
        InitGraphics();
        registerTimerEvent(TimerEventProcess);
        //...
        startTimer(TIMER_CURSOR, 500);/*start 500ms cursor blinking timer*/
    }
    void TimerEventProcess(int timerID)
    {
        bool erasemode;
        if(TIMER_CURSOR == timerID)
        {
            //...
        }
    }
    ```

    从这段例程中可以了解到几个重要的点：

    -   使用 `void registerTimerEvent(TimerEventCallback callback)` 注册回调函数 `callback` 后，还需要用 `void startTimer(int id,int timeinterval)` 设定并启动一个计时器，设定这个计时器的 `id` 和 `timeinterval`。
    -   每当计时器到达指定时间后，计时器就会调用所有的回调函数，回调函数会接收这个计时器的 `id` 并检查是不是自己需要进行动作的那个计时器。这就是 `TimerEventProcess` 函数中 `if` 语句的作用。

#### 使用方法

-   主函数是 `void Main()` 别写错了
-   下面是一个最简单的例程：

```c
#include <stdio.h>
#include "graphics.h"

void Main(void)
{
    InitGraphics();
    MovePen(1.5, 1.0);
    DrawArc(0.5, 0, 360);
}
```

#### `New()` 函数

向下翻，找到 2019 年程序填空第 3 题，使用方法在那里。

### 算法复杂度分析

-   记住：排序算法的时间复杂度与两项操作的次数有关：**比较**和**交换**。

    -   你可以这样想：创建一个全局变量作为计数器，在所有涉及比较和交换的地方让它 `++`，运行完的结果就是其时间复杂度。比如：

        ```c
        int count = 0;
        for (int i = 0; i < n; ++i) {
          for (int j = 0; j < n; ++j) {
            for (int k = 0; k < m; ++k) {
                count++;
            }
          }
        }
        ```

        运行完这段代码，`count = n*n*m`，则其时间复杂度为 $O(n^2m)$。

-   记住并理解一些常见的算法的平均时间复杂度、最优、最差情况复杂度：![image-20230623223659304](https://cdn.bowling233.top/images/2023/06/202306232248681.png)

    来源：[常用排序算法总结对比 | 数据结构与算法 系列教程（笔记） (zq99299.github.io)](https://zq99299.github.io/dsalg-tutorial/dsalg-java-hsp/07/10.html)

### 后缀表达式

这东西前两三年都考了，需要了解一下。关于表达式树的相关内容请参见：

-   [表达式求值 - OI Wiki (oi-wiki.org)](https://oi-wiki.org/misc/expression/)
-   [树基础 - OI Wiki (oi-wiki.org)](https://oi-wiki.org/graph/tree-basic/#树的遍历)

在前缀、中缀、后缀表达式之间进行转换的最好方法是将其想象成一个树状结构。

![](https://cdn.bowling233.top/images/2023/06/202306232250141.png)

-   中缀表达式：对这棵树进行中序遍历，即**左、根、右**
    -   a+b\*(c-d)-(e/f)
-   前缀表达式：对这棵树进行先序遍历，即**根、左、右**
    -   -+a\*b-cd/ef
-   后缀表达式：对这棵树进行后序遍历，即**左、右、根**。注意到左右子节点都比根先遍历，所以可以一路往下找到最深的子节点，然后向上解析。
    -   abcd-*+ef/-

值得一提的是后缀表达式具有几个方便的性质：

-   计算后缀表达式，只需要维护一个数字栈，每次遇到一个运算符，就取出两个栈顶元素，将运算结果重新压入栈中。
-   后缀表达式与表达式树一一对应。后缀表达式不需要括号表示，它的运算顺序是唯一确定的。

## 2020-2021 年卷

-   选择题 1 `typedef`

> 注意这里的 `typedef struct{char * name;} *T;` 把 `T` 定义为 `struct{char * name;}*;` 的别名。下一个语句即声明变量 `t` 为该类型。
>
> -   A：`char *`
> -   B：该表达式实际为 `&(t->name[0])`，即 `char *` 类型。
> -   C：`char *`
> -   D：`*(t.name)` 是一个错误的用法，不能直接对结构的指针使用 `.` 运算符访问其成员。

-   选择题 3 指针类型

> 函数名、数组名都不是指针哦，虽然它们常常退化成指针。
>
> -   A：`p` 是函数名
> -   B：`p` 是函数名
> -   C：`p` 是指向 `int[5]` 的指针
> -   D：`p` 是一个数组

-   选择题 4 存储类别限定符

> C 语言中一共有 5 个存储类别限定符，请回忆它们的作用：
>
> -   `auto`：默认的存储类别限定符，用于局部变量，表示变量的生命周期与函数调用相同。
> -   `register`：用于局部变量，表示变量可能存储在 CPU 寄存器中，以加快访问速度。
> -   `extern`：用于全局变量，表示变量在其他文件中定义。
> -   `static`：
>
>     -   用于局部变量，表示变量的生命周期与程序运行相同。
>     -   用于全局变量，表示变量的作用域仅限于当前文件。
>
> -   `_Thread_local`：不作要求。
>
> 其实 `typedef` 按语法功能也被分在这一类，我们不管它。
>
> 在任何声明中，只能同时存在最多一个**存储类别限定符**。这与 `const`、`volatile`、`restrict` 等**类型限定符**不同，它们可以同时存在。

-   选择题 5 函数指针

> 见 2019 年选择题 6

-   选择题 8 数据结构的使用

> 这种题通用的方法就是每个选项尝试一遍。只要对栈、队列操作熟悉的话，一个个试很快就出来了。

-   简答题 1.1 后缀表达式

> 如果你的答案和参考答案不一样，也是有对的可能的，就像中缀表达式那样，二元运算符的操作数是可以换序的（
>
> 注意这道题中的 `^` 运算符的右结合问题，加上括号后变成 `d^(e^f)` 而不是 `(d^e)^f`，转换成后缀表达式只能是 `def^^`，而 `fed^^` 之类的全是错的。

-   简答题 5 排序算法最优情况

> 见常见问题-算法复杂度
>
> 引用一下 ztgg 的解释：
>
> -   平均情况下，插入元素导致的移动依旧是 $O(n)$ 的，并没有优化，所以总复杂度还是 $O(n^2)$。（批注：交换的复杂度为 $O(n^2)$，比较的复杂度为 $O(n\log n)$，前者较大，占据主导地位）。
> -   最佳情况应该是插入元素时，不需要移动原来的元素，也就是数组已经排好序了。这个情况下，每次插入只有二分查找的代价，即为 $O(n\log n)$。

-   简答题 6 队列操作

> 如果第一个 `while` 循环读不懂一定要找同学/老师问清楚捏，队列的使用是很基本的。请思考这个 `while` 循环为什么需要逐个 `malloc()` 呢？
>
> 中间那个 `while` 循环有点迷惑。它其实只是在将 `eQueue` 中的每个元素放到 `dQueue` 时同时把后面一个元素换到队尾去。理解到这里就能做对啦。

-   程序填空 3

> 这几个空都需要花一会儿时间来推断的：
>
> -   `InitGraphics()` 一定要记得
> -   记住几种回调函数的使用方法，`void registerTimerEvent(TimerEventCallback callback)` 与 `void startTimer(int id,int timeinterval)` 配对使用，它们各自的参数意义。
> -   **计时器回调函数怎么写？**参数 `timerID` 是用来做什么的？
> -   第 14 空可能不容易想到，反正记住在每次画点什么东西之前，都要检查**画笔位置**是否正确，这在绘制分形图形时也很重要。

-   算法设计 1 链表循环检测

> 想象一个解谜场景：如果你和你的朋友走在一条路上，你们要怎么做才能判断有没有遇到鬼打墙（即在原路绕圈） ？
>
> 答案很简单：一个人走快点，一个人走慢点。如果这条路有尽头，先走的人一定会先到达尽头；如果没有到达尽头，那么他一定会重新看见你。
>
> `LoopDetect()` 函数的思路也类似：使用两个指针 `fast` 和 `late`，`fast` 每次步进两个节点，`late` 每次步进一个节点。最后终止时只有两种条件：`fast` 无法继续步进或 `fast` 在前进的路上看见 `late`。前者表明没有循环，后者表明有循环。

-   算法设计 2 有序数组原地去重

> 看到这道题你有没有想起字符串去空格的一个例程？
>
> ```c
> char *a;
> for(int i = 0, j = 0; i < length; i++){
>     if(a[i] != ' ')
>         a[j++] = a[i];
> }
> ```
>
> 有序数组去重与这个算法也有些类似，只是比较条件换成 `a[i]!=a[j]` 了而已。

## 2019-2020 年卷

-   选择题 1 递归函数

> -   D 项 调用栈位于**堆栈段（Stack Segment）**，在运行时创建，也有自己的大小，不能越界访问。越界造成**段错误（Segmentation Fault）**。每次递归调用添加栈帧，造成的越界称为**栈溢出（Stack Overflow）**。堆栈段中保存着**函数调用关系和局部变量**。局部变量过大也可能造成栈溢出。

-   选择题 2 时间复杂度分析
-   选择题 6 函数指针

>   一句话总结：作为函数作为形参，会自动退化成函数指针，就像数组名作为形参自动退化成指针那样。这句话在下面的英文部分提到了。
>
>   >   The type of a function is determined using the following rules. [...] After determining the type of each parameter, **any parameter** of type “array of T” or **of function type T is adjusted to be “pointer to T”**. [...]

> -   函数指针：指向函数的指针中储存着函数代码的起始处地址。要指明函数的类型，要指明函数的返回类型和形参类型。把函数名替换成 `#!c (*pf)` 的形式是最简单的方法，如 `#!c void ToUpper(char *)` 改为函数指针 `#!c void (*pf)(char *)`。
> -   声明函数指针后，可以将函数的地址赋给它，**这种语境下函数名可以表示函数的地址**。因此我们可以写：`#!c pf = ToUpper`，注意不是 `#!c pf = ToUpper()`。
>
> -   使用函数指针访问函数有两种方法：`#!c (*pf)(mis)` 和 `#!c pf(mis)`。事实上，K&R C 不允许第二种形式，我也推荐大家始终将函数调用理解为第一种形式，理解 `#!c (*pf)` 与 `pf` 的等价之处（分别从声明和赋值角度）。
> -   还有一个点：`f` 与 `#!c &f` 的值也一样，都是函数的地址。

> -   C 项 或许通过上面的讲解，你能理解 `#!c (*cmd)` 与 `cmd` 的等价之处。下面是 StackOverflow 中的讨论：[c++ - What does `#!c void f(void())` mean? - Stack Overflow](https://stackoverflow.com/questions/39440970/what-does-void-fvoid-mean)。
>
> > As mentioned in [_dcl.fct_](http://eel.is/c++draft/dcl.fct#5) of the working draft (emphasis mine):
> >
> > > The type of a function is determined using the following rules. [...] After determining the type of each parameter, **any parameter** of type “array of T” or **of function type T is adjusted to be “pointer to T”**. [...]
> >
> > Because of that, the following function:
> >
> > ```cpp
> > void f(void());
> > ```
> >
> > Has the same type of:
> >
> > ```cpp
> > void f(void(*)());
> > ```
> >
> > Thus the definitions below are identical:
> >
> > ```cpp
> > void f(void(g)());
> > void f(void(*g)());
> > ```
>
> > Correct me if I'm wrong, AFAIK function names are pointers just like array names so **in the first example you are passing function object and compiler does implicit conversion**, in the second example you are directly passing function pointer which is explicit conversion.

-   选择题 7 函数指针

> 同样依据上面的讲解能够选出正确答案

-   选择题 8 函数参数

> 我觉得 D 项的表述本来就很混乱。函数参数如果为 `void` 就表示函数不接收参数，这就是 `void` 关键字的作用，而不是选项中说的什么“函数有一个 `void` 类型的参数”。

-   选择题 9 图形库

> 请 WK 班同学一定要去看辅学群里其他老师的图形库课件

-   选择题 10 还是函数指针

> -   第一行：`F` 定义为 `int (int)` 类型的函数。
> -   第二行：声明两个类型为 `F` 的函数 `g` 和 `h`。其实就是 `int g(int a)` 和 `int h(int a)`。
> -   第三行：声明一个数组 `p`，其中每个元素都是 `int (*)(int)` 类型（与 `F` 等价）。并用 `g` 和 `h` 来初始化这个数组。
>     -   让我们从内往外读这个声明：`p` 是标识符的名称，向右 `[]` 表明这是一个数组，向左 `*` 表示其元素是指针，再向右 `(int)` 表示其所指类型是函数，这种函数接受 `int` 类型参数，再向左 `int` 说明这种函数返回 `int` 类型。
>     -   用 `g` 和 `h` 初始化这个数组时，`g` 和 `h` 被转换为函数指针（回顾上面的讨论）。
> -   第四行：声明一个函数 `q` 这个函数返回 `int`，接受一种数组，这种数组的每个元素都是 `F*` 类型，即 `int (*)(int)`。故函数 `q` 的参数类型为 `int (**)(int)`。

> -   A 项：数组名就是首元素指针，为 `int (**)(int)`，匹配。
> -   C 项：显然类型匹配。
> -   D 项：对函数取地址，得到 `int (*)(int)`，与 `int (**)(int)` 类型不匹配。

-   简答题 1

> 如果程序代码有错，就勇敢地写“该段程序可能运行失败”。

-   简答题 3

> 注意，合并数组的时候部分去重了。如果离开了第一个 `while` 循环，则不会去重。

-   简答题 4

> 让我们看 `main()` 函数的第一行的表达式：
>
> -   外层：`((H)内层表达式 )(100);`，它会将内层表达式强制类型转换为 `H` 类型的函数，然后对该函数执行函数调用。
> -   内层：`h(0)`。调用后返回了 `h`，即函数自己，也就是函数自己的指针。作为 `void *` 类型返回，表明它是一个指针，但不知道所指向的类型。
> -   内层调用后，外层就相当于 `h(100)`了，因为 `h` 本来就是 `H` 类型的函数。

-   程序填空 3 `geblib.h`

> WK 班同学应当补充阅读 `libgraphics` 库中的一些内容，我们直接读源码吧：
>
> -   `New()` 宏函数：
>
>     -   Usage: `p = New(pointer-type);`
>
>     -   The New pseudofunction allocates enough space to hold an object of the type to which pointer-type points and returns a pointer to the newly allocated pointer. Note that "New" is different from the "new" operator used in C++; the former takes a **pointer type** and the latter takes the target type.
>
>     -   源码：
>
>         ```C
>         void *GetBlock(size_t nbytes);
>         #define New(type) ((type) GetBlock(sizeof *((type) NULL)))
>         ```
>
>     -   举个例子：调用 `New(char*)`
>
>         -   宏展开为 `((char*) GetBlock(sizeof *((char*) NULL)))`
>         -   `GetBlock()` 函数接收需要分配的字节数，返回分配成功的指针。对于上面的宏展开后的调用参数，`NULL` 被转换为 `char*` 随后解引用仍为 `char` 类型的大小。
>         -   这个调用就返回了一个 `char*` 的指针。
>
> -   `FreeBlock()` 函数：
>
>     -   原型：`void FreeBlock(void *ptr)`
>     -   与 `free()` 功能类似，不加解释。

> 第 15 空有意思，`FreeBlock(PopStack(stack))` 的嵌套写法。

-   算法设计 1 分形

> 这类算法设计题目，怎么简洁怎么来，以 OI 码风去写是最合适的。不要试图弄完善的交互，那是浪费时间。

> 以下是我自己做的时候写的，作为一个不好的参考（
>
> 理解错题意了，原来 `order` 不是方向而是分形次序。
>
> -   基准情形：长度缩小到某值。
> -   递归情形：画一根，随后两次递归调用，绘制下一支的 `length` 和 `order`。每次递归调用后，都应当**返回原位**。
>
>     ```c
>     #include <stdio.h>
>     #include <math.h>
>     #include <stdlib.h>
>     #include "graphics.h"
>     #define MIN_LEN .1
>    
>     double toRadius(double deg)
>     {
>         return deg * 3.1415926 / 180;
>     }
>    
>     void DrawBranch(double len, double deg)
>     {
>         DrawLine(len * cos(toRadius(deg)), len * sin(toRadius(deg)));
>         if (len * 0.75 < MIN_LEN)
>             return;
>         DrawBranch(len * 0.75, deg - 15);
>         MovePen(GetCurrentX() - len * 0.75 * cos(toRadius(deg - 15)),
>                 GetCurrentY() - len * 0.75 * sin(toRadius(deg - 15)));
>         //也可以用 DrawLine 实现
>         DrawBranch(len * 0.75, deg + 15);
>         MovePen(GetCurrentX() - len * 0.75 * cos(toRadius(deg + 15)),
>                 GetCurrentY() - len * 0.75 * sin(toRadius(deg + 15)));
>     }
>    
>     int main(void)
>     {
>     	double length;
>         char order;
>         printf("Please enter initial length: ");
>         scanf("%lf", &length);
>         getchar();
>         printf("Please enter order (u)pper, (d)own, (r)ight, (l)eft: ");
>         scanf("%c", &order);
>         double deg;
>         switch(order)
>         {
>             case 'u': deg = 90; break;
>             case 'd': deg = -90; break;
>             case 'r': deg = 0; break;
>             case 'l': deg = 180; break;
>             default: printf("error.\n"); return 1;
>         }
>         InitGraphics();
>         MovePen(GetWindowWidth()/2, GetWindowHeight()/2);
>     	DrawBranch(length, deg);
>         return 0;
>     }
>     ```

-   算法设计 2 列表变序

> 就用标答的方法，将偶数节点移动到另一个链表，再合并两个链表。

## 2018-2019 年卷

-   选择题 4 递归计算

> 像这种递归计算，就老老实实把函数递归展开吧。展开过程中记得依次记下已经计算完的 `f(0)`、`f(1)` 等值，方便后续计算。

-   选择题 6 算法复杂度分析

> 这道题我的想法挺奇葩的，我是想只要全部排序一遍 $O(N\log N)$，然后用 $O(1)$ 的时间检查一下头、中间、尾部的元素不就好了吗（doge

-   选择题 9 递增运算符

> 前缀递增运算符先递增再使用。

-   简答题 1.2

> 本题英文有点烫嘴，我翻译一下：
>
> > 为了用类似 `T p` 的方式声明一个指针 `p`，请写出复合类型 `T` 的定义。`p` 是一个函数的指针，该函数接收 `(char *, double)` 参数，并返回一个 `int *`。
>
> 读懂题目剩下的就不用说啦。

-   简答题 2 数据与字节

> 注意：**xx-bit system（n 位系统）**指的是这个系统的指针长度有 $n$ 比特，$8$ 比特为一个字节。故本题的所有指针都是 $4$ 字节。
>
> 以下是各类型的大小：
>
> -   `StudentInfo`：两个 `char` 数组 + 一个指针 = $12 + 20 + 4 = 36$
> -   `PtrStudentInfo`：$4$
> -   `pStudent->name`：一个 `char` 数组 $=20$
> -   `pStudent->photo`：一个 `void*` 指针 $=4$
>
> 从上面再次看到，数组名并不能简单被看作指针，它还包含数组的类型信息。

-   简答题 3 链表操作

> 这道题答案感觉有点问题啊。反正只要知道返回的时候 `p` 指向 $2$ 这个节点就算对了，题目说 `node` 那应该不用吧后面的节点都写出来吧。

-   简答题 4 链表操作

> 这个函数合并了两个链表，按升序合并。
>
> `HEAD` 是一个临时使用的哑节点。
>
> 调用后，原来的两个指针指的位置不变，`l1` 仍然指向 $1$ 这个节点。但节点之间的连接变了，这时 `l1` 后面链上了从 `l2` 合并进来的其他节点。所以可以看作“链表” `l1` 发生了改变。

-   简答题 5 双向栈

> 这是一个双向的栈。每次入/出栈时，需要用 `Tag` 参数指定是哪一头。从数组的角度来看，`Top1` 是左边（头部）那头，`Top2` 是右边（尾部）那头。
>
> 读这种题时，我推荐先读 `main()` 中的内容，即观察题目给的数据结构是**怎么被使用的**。然后不明白的地方再去看具体实现的代码，其他部分就一点都不用看。比如这道题：
>
> -   先看 `main()` 中的 `Push()` ，这怎么比平常的 `Push()` 多一个参数呢？
> -   再看类型定义，怎么有两个 `Top`？回想 `main()` 中一个令为 `-1` 一个令为 `MaxSize` 便知道这是一个双向栈了。
> -   `Push()` 和 `Pop()` 的代码就不用看了，想象得到是怎么操作的。最多再多看一眼 `if(Tag == 1)` 知道哪个值对应哪一头，就可以完成这道题了。

-   简答题 6 不知道是什么

> 这个东西，保险起见推荐手工模拟，而且手工模拟几次后你就知道这个函数在干嘛了。
>
> 其实这个函数的作用是：调用后保证数组 `a[k]` 左侧的元素都比 `a[k]` 小，右侧都比 `a[k]` 大。最后返回 `a[k]` 上的元素。**但不会保证其他元素之间的相对顺序**。
>
> 具体的操作就是：每轮循环把第 `a[k]` 位置上的元素提出来作为 `x`，然后用 `i` 和 `j` 分别从左右遍历并交换两侧不符合要求的数。交换完成后，数组中比 `x` 小的数都在相对左边的位置，比 `x` 大的数都在相对右边的位置。
>
> 如果你对快排比较熟悉，那么这就是“如果目标位置不在的一边直接舍弃”的快排。相当于本来快排区间形成一颗树，但是现在就只走一条路，只排 `a[k]` 所在的那些区间套。

-   程序填空 1 分型

> 画个坐标轴，一切都清晰起来了。然后 `Main()` 里最开始对大三角形三个顶点的求值可能会引起困惑，其实可以不用管它，它不影响你分析递归调用过程。它只是在用三角函数计算位置使这个大三角形的中心在屏幕中央罢了。给个很草的草稿示意图：
>
> 画这个分形的步骤就是：先画大三角，然后各边取中点。大三角的每个顶点和相邻两边中点构成两个小三角。
>
> ![](https://cdn.bowling233.top/images/2023/06/202306241632120.png)

-   程序填空 2 循环队列实现

> 本质上还是用数组实现循环队列，只不过本题进行了比较完善的封装。
>
> 如果还不知道循环队列是什么东西，去网上搜一搜。循环队列的要点就是：所有加法操作全部要套上一次取模操作。本题注意一下间接成员运算符 `->` 的使用。
>
> 此外循环队列的 `rear` 也有不同实现方法，在本题中，它标志队列尾部的后一个元素，也就是下一个元素应该插入的地方；在另一些实现中，它直接标志队列尾部的元素。比如如果本题在创建数组的时候 `Q->rear = maxsize - 1`，这些空应该作怎样的改变呢？

-   程序填空 3 图形库

> 参见常见问题-图形库-计时器

-   算法设计 1 寻找第一个公共节点

> 想象这样一个情境：还是想象你和你的朋友站在题目所示的两个链表的起始处。这两个链表有可能相交，你们想要尽快找到会合点，怎么办呢？而且一个有用的信息是，你们都知道自己离终点还有多远。
>
> 如果相交，你们肯定有公共子链表。剩下不同的部分就是你们各自子链表的长度。因此，你们应当先相对终点对齐彼此的位置，使自己剩余的子链表的的长度相等。接下来以相同的速度前进，如果你们在某处会合了，那么这一定是公共子链表的起始处。
>
> 参答中，`lPtr` 指向较长的链表，`sPtr` 指向较短的链表，`numLeftNodes` 就是两链表节点数的差值，`lPtr=lPtr->next` 的 `for` 循环就是在对齐两人的位置。
>
> 循环终止的条件是：其中某人走到了尽头 `NULL`，或两人相遇 `lPtr==sPtr`。返回最终位置即可。

-   算法设计 2 二分插入排序

> 这题简单，不作解析。参答中漏了检查 `minPos == rh` 的情况，想想这样会造成什么后果？

## 2017-2018 年卷

-   选择题 1 数据类型与指针操作

> -   C 项：`strcpy()` 只能用于字符串。进一步说，它依据字符串末尾的 `\0` 来决定是否停止复制，因此不宜用于此情境。
> -   D 项：每次 `*pc2++ = *pc1++`，都会将 `pc1` 的一个字节拷贝到 `pc2` 指向的位置，并让这两个指针向后移动一个 `char` 的位置。由于 `p1` 和 `p2` 两个结构变量大小都是 $8+8=16$ 字节，因此该选项正确地执行了拷贝。

-   选择题 7 冒泡排序

> 这道题时，我选的是 D 项。因为我记忆中的冒泡排序是这样的：
>
> ```c
> void bubble_sort(int *arr, int len) {
>  int i, j, tmp;
>  for (i = 0; i < len - 1; i++) {
>      for (j = len - 1; j > i; j--) {//Bubble
>          if (arr[j] < arr[j - 1]) {
>              tmp = arr[j];
>              arr[j] = arr[j - 1];
>              arr[j - 1] = tmp;
>          }
>      }
>  }
> }
> ```
>
> 上面这样的写法对于任何情况的复杂度都是 $O(n^2)$。但是冒泡排序普遍会作这样的优化：
>
> -   如果在上一轮的 Bubble 中，没有发生任何交换，则说明这个序列也是有序的，不再需要后续操作了。
>
> 因此可以在外循环开头添加 `bool flag = 0;`，结尾添加 `if(!flag)break;`，交换操作中添加 `flag=true` 即可将最优情况优化至 $O(n)$。

-   选择题 9 存储类别限定符

>   -   D 项：`static` 此处修饰的是指针 `p`。事实上，也不存在指针指向 `static int` 这种说法。`static` 作为存储类别限定符，在变量的声明中表示该变量具有静态存储期。一个指针，只需要管它指向的是什么类型，不需要知道这个对象的存储期。

-   简答题 1.(2) 写函数声明

>   先想想自己会怎么调用这个 `fun` 函数才能得到 `void` 类型：
>
>   -   第一步，调用函数获取返回值：`fun(int)`。
>   -   第二步，解引用返回值，获得函数，调用该函数：`(*fun(int))(int)`。注意，函数指针应当使用 `(*fp)()` 形式调用。
>
>   得到了答案：`void (*fun(int))(int)`。

-   简答题 5 最大子列和

>   其实这是一个经典的算法：**所有连续子列元素的和中最大者**。在网上可以搜到很多该算法的原理介绍，请去看一看，看完就能立刻明白这段代码了。
>
>   `thisp` 被放置在最大子列的开头，`maxp` 被放置在最大子列的末尾。

-   简答题 6 侏儒排序

>   基于比较的排序算法，大概都能优化到**最优情况**复杂度为 $O(n)$ 吧？

-   程序填空 2 多项式计算

>   这题蛮坑的，我看了好一会儿才明白第 (7)(8) 空在干嘛。它其实就是先把前面的高次项提公因式，然后在逐步向后求和的过程给它整体乘上 $x$。比如 $3x^4+2x^2+1$ 可以这样计算：
>
>   -   $(((3x)x^2)+2x)x + 1$
>
>   这样做一定程度上减少了计算乘积的次数。
>
>   同样注意 `->` 运算符的使用。

## 2016-2017 年卷

-   选择题 1 倒序栈

>   注意题目中说明了**栈顶指针位于 `N`**，这个栈是从数组的尾部开始累积的。

-   简答题 1.(2) 写函数指针

>   简单函数指针，直接这样记：`typedef 返回类型 (*新名字)(参数列表)`

-   简答题 3 奇偶排序

>   和前一年的侏儒排序有点像，有序情况也是一遍过，最优时间复杂度也是 $O(n)$。

-   简答题 4 链表操作

>   过程中，该链表顺序被重新排列。比 `x` 小的节点依次移动到 `root` 为首的带哨兵链表中，大的依次移动到 `pivot` 为首的哨兵链表中，最后将两个链表合并，返回合并后的链表。

-   简答题 5 因数分解

>   本题其实就是在从小到达求因数、约去这个因数、求下一个更大的因数...。模拟一遍即可。

-   程序填空 1 计数排序

>   排序原理题目已经讲清楚了，这里讲一下循环中几个变量的作用：
>
>   -   `count` 数组：先用于统计出现次数，后用来标记开始位置。
>   -   `output_array[count[input_array[i]]] = input_array[i]` 我们来拆解一下：
>       -   `intput_array[i]` 就是第 `i` 个元素
>       -   把它放到 `count[]` 就能查到这个数应该放置的起始位置。
>       -   所以第 4 空当然要递增啦。

-   程序填空 3 差集

>   值得一提的是，这两个链表都是集合，这意味着其中的元素都是唯一的，所以不需要考虑重复元素的情况，不需要完整遍历 $A$。

## 2015-2016 年卷

-   选择题 5 宏的展开

>   宏展开只是简单的文本替换。
>
>   -   先展开 `DD` 得到 `SQ(2*3) - SQ(2+3)`，得到 `2 * 3 * 2 * 3 - 2 + 3 * 2 + 3`
>   -   先展开 `SQ` 得到 `DD(x, y) = x * x - y * y`，得到 `2 * 3 * 2 * 3 - 2 + 3 * 2 + 3`
>
>   从上面的展开中我们看到，宏函数的展开顺序并不重要。最终结果应当一致。