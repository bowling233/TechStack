# C 大程历年卷简单整理

-   常见问题：
    -   这个声明究竟是什么类型？[Reading C type declarations (unixwiz.net)](http://unixwiz.net/techtips/reading-cdecl.html)

## For wk 班同学

一下简要整理一下 `libgraphics` 用法：

### 必备函数

图形与文字

-   `void InitGraphics(void)`
-   `void MovePen(double x, double y)`
-   `void DrawLine(double dx, double dy)`
-   `void DrawArc(double r, double start, double sweep)`
-   `double GetWindowWidth(void)`
-   `double GetWindowHeight(void)`
-   `double GetCurrentX(void)`
-   `double GetCurrentY(void)`
-   `void DrawTextString(string text)`
-   `double TextStringWidth(string text)`

控制台交互：

-   `OpenConsole()`
-   `int GetInteger(void)`
-   `double GetReal(void)`
-   `string GetLine(void)`
-   `string ReadLine(FILE *infile)`
-   `CloseConsole()`

### 使用方法

-   值得注意的一点是：`libgraphics` 的坐标系统与 `ACLLib` 不同。前者以左下角为原点，符合我们常用的数学表达；后者以左上角为顶点，使用窗口坐标系统。
-   `void Main()` 别写错了
-   `InitGraphics()`

```c
#include <stdio.h>
#include "genlib.h"
#include "graphics.h"

void Main(void)
{
    InitGraphics();
    MovePen(1.5, 1.0);
    DrawArc(0.5, 0, 360);
}
```

## 2020 年

6.16 更新

- 选择题 1 递归函数

> - D 项 调用栈位于**堆栈段（Stack Segment）**，在运行时创建，也有自己的大小，不能越界访问。越界造成**段错误（Segmentation Fault）**。每次递归调用添加栈帧，造成的越界称为**栈溢出（Stack Overflow）**。堆栈段中保存着**函数调用关系和局部变量**。局部变量过大也可能造成栈溢出。
>

-   选择题 2 时间复杂度分析
-   选择题 6 函数指针

>   -   函数指针：指向函数的指针中储存着函数代码的起始处地址。要指明函数的类型，要指明函数的返回类型和形参类型。把函数名替换成 `(*pf)` 的形式是最简单的方法，如 `void ToUpper(char *)` 改为函数指针 `void (*pf)(char *)`。
>   -   声明函数指针后，可以将函数的地址赋给它，**这种语境下函数名可以表示函数的地址**。因此我们可以写：`pf = ToUpper`，注意不是 `pf = ToUpper()`。
>
>   -   使用函数指针访问函数有两种方法：`(*pf)(mis)` 和 `pf(mis)`。事实上，K&R C 不允许第二种形式，我也推荐大家始终将函数调用理解为第一种形式，理解 `(*pf)` 与 `pf` 的等价之处（分别从声明和赋值角度）。
>   -   还有一个点：`f` 与 `&f` 的值也一样，都是函数的地址。

>   -   C 项 或许通过上面的讲解，你能理解 `(*cmd)` 与 `cmd` 的等价之处。下面是 StackOverflow 中的讨论：[c++ - What does `void f(void())` mean? - Stack Overflow](https://stackoverflow.com/questions/39440970/what-does-void-fvoid-mean)。
>
>   >   As mentioned in [*dcl.fct*](http://eel.is/c++draft/dcl.fct#5) of the working draft (emphasis mine):
>   >
>   >   >   The type of a function is determined using the following rules. [...] After determining the type of each parameter, **any parameter** of type “array of T” or **of function type T is adjusted to be “pointer to T”**. [...]
>   >
>   >   Because of that, the following function:
>   >
>   >   ```cpp
>   >   void f(void());
>   >   ```
>   >
>   >   Has the same type of:
>   >
>   >   ```cpp
>   >   void f(void(*)());
>   >   ```
>   >
>   >   Thus the definitions below are identical:
>   >
>   >   ```cpp
>   >   void f(void(g)());
>   >   void f(void(*g)());
>   >   ```
>
>   >   Correct me if I'm wrong, AFAIK function names are pointers just like array names so **in the first example you are passing function object and compiler does implicit conversion**, in the second example you are directly passing function pointer which is explicit conversion.

-   选择题 7 函数指针

>   同样依据上面的讲解能够选出正确答案

-   选择题 8 函数参数

>   `void` 参数不需要标识符，它表示函数不接收参数，而不是说 `void` 类型。

-   选择题 9 图形库

>   请 WK 班同学一定要去看辅学群里其他老师的图形库课件

-   选择题 10 还是函数指针

>   -   第一行：`F` 定义为 `int (int)` 类型的函数。
>   -   第二行：声明两个类型为 `F` 的函数 `g` 和 `h`。其实就是 `int g(int a)` 和 `int h(int a)`。
>   -   第三行：声明一个数组 `p`，其中每个元素都是 `int (*)(int)` 类型（与 `F` 等价）。并用 `g` 和 `h` 来初始化这个数组。
>       -   让我们从内往外读这个声明：`p` 是标识符的名称，向右 `[]` 表明这是一个数组，向左 `*` 表示其元素是指针，再向右 `(int)` 表示其所指类型是函数，这种函数接受 `int` 类型参数，再向左 `int` 说明这种函数返回 `int` 类型。
>       -   用 `g` 和 `h` 初始化这个数组时，`g` 和 `h` 被转换为函数指针（回顾上面的讨论）。
>   -   第四行：声明一个函数 `q` 这个函数返回 `int`，接受一种数组，这种数组的每个元素都是 `F*` 类型，即 `int (*)(int)`。故函数 `q` 的参数类型为 `int (**)(int)`。

>   -   A 项：数组名就是首元素指针，为 `int (**)(int)`，匹配。
>   -   C 项：显然类型匹配。
>   -   D 项：对函数取地址，得到 `int (*)(int)`，与 `int (**)(int)` 类型不匹配。

-   简答题 1 
    -   如果程序代码有错，就勇敢地写“该段程序可能运行失败”。
    
-   简答题 3
    -   注意，合并数组的时候部分去重了。如果离开了第一个 `while` 循环，则不会去重。
-   简答题 4

>   让我们看 `main()` 函数的第一行的表达式：
>
>   -   外层：`((H)内层表达式 )(100);`，它会将内层表达式强制类型转换为 `H` 类型的函数，然后对该函数执行函数调用。
>   -   内层：`h(0)`。调用后返回了 `h`，即函数自己，也就是函数自己的指针。作为 `void *` 类型返回，表明它是一个指针，但不知道所指向的类型。
>   -   内层调用后，外层就相当于 `h(100)`了，因为 `h` 本来就是 `H` 类型的函数。

-   程序填空 3 `geblib.h`

>   WK 班同学应当补充阅读 `libgraphics` 库中的一些内容，我们直接读源码吧：
>
>   -   `New()` 宏函数：
>
>       -    Usage: `p = New(pointer-type);`
>       
>       -   The New pseudofunction allocates enough space to hold an object of the type to which pointer-type points and returns a pointer to the newly allocated pointer.  Note that "New" is different from the "new" operator used in C++; the former takes a **pointer type** and the latter takes the target type.
>       
>       -   源码：
>       
>           ```C
>           void *GetBlock(size_t nbytes);
>           #define New(type) ((type) GetBlock(sizeof *((type) NULL)))
>           ```
>       
>       -   举个例子：调用 `New(char*)`
>       
>           -	宏展开为 `((char*) GetBlock(sizeof *((char*) NULL)))`
>           -	`GetBlock()` 函数接收需要分配的字节数，返回分配成功的指针。对于上面的宏展开后的调用参数，`NULL` 被转换为 `char*` 随后解引用仍为 `char` 类型的大小。
>           -	这个调用就返回了一个 `char*` 的指针。
>       
>   -   `FreeBlock()` 函数：
>
>       -   原型：`void FreeBlock(void *ptr)`
>       -   与 `free()` 功能类似，不加解释。

>   第 15 空有意思，`FreeBlock(PopStack(stack))` 的嵌套写法。

-   算法设计 1 分形

>   这类算法设计题目，怎么简洁怎么来，以 OI 码风去写是最合适的。不要试图弄完善的交互，那是浪费时间。

>   以下是我自己做的时候写的，作为一个不好的参考（
>
>   理解错题意了，原来 `order` 不是方向而是分形次序。
>
>   -   基准情形：长度缩小到某值。
>   -   递归情形：画一根，随后两次递归调用，绘制下一支的 `length` 和 `order`。每次递归调用后，都应当**返回原位**。
>
>       ```c
>       #include <stdio.h>
>       #include <math.h>
>       #include <stdlib.h>
>       #include "graphics.h"
>       #define MIN_LEN .1
>           
>       double toRadius(double deg)
>       {
>           return deg * 3.1415926 / 180;
>       }
>           
>       void DrawBranch(double len, double deg)
>       {
>           DrawLine(len * cos(toRadius(deg)), len * sin(toRadius(deg)));
>           if (len * 0.75 < MIN_LEN)
>               return;
>           DrawBranch(len * 0.75, deg - 15);
>           MovePen(GetCurrentX() - len * 0.75 * cos(toRadius(deg - 15)),
>                   GetCurrentY() - len * 0.75 * sin(toRadius(deg - 15)));
>           //也可以用 DrawLine 实现
>           DrawBranch(len * 0.75, deg + 15);
>           MovePen(GetCurrentX() - len * 0.75 * cos(toRadius(deg + 15)),
>                   GetCurrentY() - len * 0.75 * sin(toRadius(deg + 15)));
>       }
>           
>       int main(void)
>       {
>       	double length;
>           char order;
>           printf("Please enter initial length: ");
>           scanf("%lf", &length);
>           getchar();
>           printf("Please enter order (u)pper, (d)own, (r)ight, (l)eft: ");
>           scanf("%c", &order);
>           double deg;
>           switch(order)
>           {
>               case 'u': deg = 90; break;
>               case 'd': deg = -90; break;
>               case 'r': deg = 0; break;
>               case 'l': deg = 180; break;
>               default: printf("error.\n"); return 1;
>           }
>           InitGraphics();
>           MovePen(GetWindowWidth()/2, GetWindowHeight()/2);
>       	DrawBranch(length, deg);
>           return 0;
>       }
>       ```

-   算法设计 2 列表变序

>   就用标答的方法，将偶数节点移动到另一个链表，再合并两个链表。