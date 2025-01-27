# JavaScript

## 概述

> 来自[MDN](https://developer.mozilla.org/en-US/docs/Web/JavaScript/A_re-introduction_to_JavaScript)

### 让我们首先建立一些基础概念

-   JavaScript 是一种具有[函数优先](https://developer.mozilla.org/zh-CN/docs/Glossary/First-class_Function)特性的轻量级、解释型或者说[即时编译型](https://zh.wikipedia.org/wiki/即時編譯)的编程语言。

    <details><summary>什么是函数优先（first-class function）？</summary>指的是函数和变量没有区别</details>

-   与大多数编程语言不同，JavaScript 没有输入或输出的概念。它是**一个在宿主环境（host environment）下运行的脚本语言，任何与外界沟通的机制都是由宿主环境提供的**。浏览器是最常见的宿主环境，但在非常多的其他程序中也包含 JavaScript 解释器，如 Adobe Acrobat、Adobe Photoshop、SVG 图像、Yahoo！的 Widget 引擎，Node.js 之类的服务器端环境，NoSQL 数据库（如开源的 Apache CouchDB）、嵌入式计算机，以及包括 GNOME（注：GNU/Linux 上最流行的 GUI 之一）在内的桌面环境等等。

### 数据类型

-   <details><summary>JavaScript 的 7 种基本数据类型是什么？</summary><ul><li>Number</li><li>BigInt</li><li>String</li><li>Boolean</li><li>Symbol</li><li>Undefined</li><li>Null</li></ul></details>

-   **所有其他东西都是** **_对象_** 。

    -   常见的对象有：Function, Array, Date, RegExp, Error。

    -   函数并不是什么特殊的数据结构。

介绍基本数据类型：

-   Number：所有数都以 IEEE 754 浮点数标准存储，**看起来是整数的**也是浮点数。

    -   如果运算符需要整数（比如位运算），数字会被转换为**32 位**整数。

    -   <details><summary>把字符串转换成数字的三种方式？</summary>
        <ul>
            <li>parseInt()</li>
            <li>parseFloat()</li>
            <li>Number()</li>
        </ul>
        </details>

    -   一元运算符 `+` 尝试把后面的东西转换成数字。

    -   `NaN` 和 `Infinity` 有什么特别之处吗？

-   BigInt：以 `n` 作为后缀，无限大。不要将 BigInt 和 Number 混用。

-   String：以 **UTF-16** 编码存储

    -   字符和字符串没有区别，所以 `''` 和 `""` 的作用相同。

    -   字符串具有一些功能函数，参阅 [MDN] 了解它们的使用方法。

    -   因为**字符串是基本数据类型**，基本数据类型**不可更改**。所以功能函数返回一个新的字符串。

    -   `` ` `` 反点号用于**模板字符串**：

        ```javascript
        `string test ${expression} string text`;
        ```

-   Undefined：表明**缺少值**可以在以下情况下获得

    -   空的 return
    -   访问不存在的属性
    -   未初始化的声明

-   Null：表明**故意的没有值**

-   Boolean：

    -   任何值都能使用 `Boolean()` 被转换为 Boolean，只有这些值转换成 false：`0`, `""`, `NaN`, `null`, `undefined`。
    -   当 JS 期望一个布尔值时，它会自动执行该转换（比如 if 语句）。

### 变量

-   `let` 块作用域
-   `const` 块作用域，不可**重新赋值**，但**不保证变量的值被改变**。
    -   注意：对象和基本类型不同：声明对象时，标识符是它的**引用**。使用 `const` 意味着引用不可更改，而非对象的值不可更改
-   `var` 在现代 JS 中不推荐使用

> 什么是 TDZ（Temporal Dead Zone）？
>
> 以下内容对 `let` 和 `const` 适用：
>
> -   指的是从块的起始位置到该变量被声明和初始化的位置。
> -   在 TDZ 内，变量未被初始化，对变量的访问讲返回 `ReferenceError`。
> -   当程序执行到声明/初始化语句时，变量才具有值。如果没有初始化，会是 `undefined`
>
> TDZ 会引起一些有趣的覆盖情况，总之记住：块内定义的变量，总是在**整个块中可见**。

### 运算符

有些新的东西：

-   `**`：指数运算
-   `==`：比较前尝试类型转换，**不推荐使用**
-   `===`：比较前不尝试类型转换
    -   它们都有不等形式：`!==`, `!=`

### 语法

和 C 类似，也有些新的东西：

-   标识符可以是 Unicode 字符。
-   分号是**可选的**：JS 会在需要的时候自动插入它们。

### 控制结构

也有新的东西：

-   `for...of`：遍历迭代量
-   `for...in`：访问一个对象所有*可列*的属性
    -   它们的使用：`for (const property in object)`，记得用**const**。
-   `switch`
    -   JS 中，任何表达式都可以是标签。
    -   与 C 的**跳转表**实现不同：JS 中，标签被逐个使用 `===` 测试是否相等。

控制结构是语句，不能被分配给变量（与 Rust 不同）

错误处理 #暂不学习

### 对象

-   JS 中的对象是一对对键和值的集合，你可以把它看作哈希表。

-   与静态语言不同，JS 中的对象不固定：属性可以被添加、删除、重排、更改、动态质询。

-   Key：总是字符串或 Symbol

    -   甚至数组下标也是**字符串**

-   创建对象：

    ```javascript
    const obj = {
        name: "Carrot",
        for: "Max",
        details: {
            color: "orange",
            size: 12,
        },
    };
    ```

-   访问对象属性：

    -   `.` 键必须是一个合法的标识符
    -   `[expression]` 表达式应当估值为一个字符串或 Symbol
    -   两种访问方式都能嵌套

-   对象总是**引用**

    -   两个分别创建的对象永远不可能相等
    -   赋值时拷贝的是引用而非对象

### 数组

-   下标、长度与一般语言定义相同。
-   `{}` 换成了 `[]`
    -   例：`const a = ["dog", "cat", "hen"];`
-   sparse array（稀疏数组）：多数情况下表现得像是填充了 `undefined`，某些情况下（尤其是迭代方法）会被略过。
    -   sparse array 会阻止引擎将它优化成**哈希表**，所以最好保证数组密度。
-   **下标越界**不会抛出异常，而是会得到 `undefined`。
-   `array` 是**类型松散的**，可以任意增长、缩小。
-   `array` 使用 `for...of` 语句遍历。
    -   例：`for(const currentValue of a)`
-   数组也有一些方法：
    -   `map()`：接受一个函数。对每个元素调用回调函数，返回一个新数组。

### 函数

-   基本函数声明：

    ```javascript
    function add(x, y) {
        const total = x + y;
        return total;
    }
    ```

-   不 return 会得到 `undefined`

-   参数

    -   缺少的参数设置为 `undefined`，多的参数被忽略

    -   [rest parameters](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Functions/rest_parameters)允许函数收集多余的参数，成为一个数组。例：`function (a, b, ...theArgs)`。rest parameters 只能有一个，只能是最后一个参数

    -   > Python `**kwargs` （键值对参数列表）可以通过对象析构实现：
        >
        > ```javascript
        > // Note the { } braces: this is destructuring an object
        > function area({ width, height }) {
        >     return width * height;
        > }
        >
        > // The { } braces here create a new object
        > console.log(area({ width: 2, height: 3 }));
        > ```

    -   默认参数语法：`function avg(firstValue, secondValue, thirdValue = 0) `

-   匿名函数

    -   匿名函数才能使用 `=>` 符号。

    -   这个函数可以被赋给某个变量，但注意它和普通的函数有些不同。

    -   在声明的同时调用（单表达式）：

        ```javascript
        (function () {
            // …
        })();
        ```

-   递归

    -   用于处理文档树等结构
    -   函数表达式也能被命名，进而递归

        ```javascript
        const charsInBody = (function counter(elm) {
            if (elm.nodeType === 3) {
                // TEXT_NODE
                return elm.nodeValue.length;
            }
            let count = 0;
            for (let i = 0, child; (child = elm.childNodes[i]); i++) {
                count += counter(child);
            }
            return count;
        })(document.body);
        ```

    -   **为了避免内存溢出，尽量不要使用递归**

-   函数优先：

    -   `const add = (x) => (y) => x + y;`，返回函数的示例。
    -   函数的属性同样能被随时添加删除。

-   **闭包（Closures）**：A **closure** is the combination of a function bundled together (enclosed) with references to its surrounding state (the **lexical environment**). In other words, a closure gives you access to an outer function's scope from an inner function. In JavaScript, closures are created every time a function is created, at function creation time.

    > 闭包是函数式编程的一个重要概念：**函数和其周围的状态(词法环境)的引用捆绑在一起形成闭包。**
    >
    > ```javascript
    > function makeFn() {
    >     let msg = "Hello function";
    >     return function () {
    >         console.log(msg);
    >     };
    > }
    >
    > const fn = makeFn();
    > fn();
    > ```
    >
    > makeFn 函数中又返回了一个内部函数并且赋值给 fn，fn 对这个内部函数就有了引用，内部里面访问了 msg 变量，当 makeFn 函数执行完毕时，因为**外部 fn 引用着内部函数，且内部函数访问了 msg**，所以**msg 变量并不会被释放**。这就形成了一个闭包。由此可见闭包的核心作用就是**把 makeFn 函数中的 msg 成员的作用范围延长。**
    >
    > **闭包可以在另一个作用域中调用一个函数的内部函数并访问到该函数的作用域中的成员。**

-   嵌套函数：常常被用于把工具函数隐藏于一个函数内，减少全局函数的数量。内层函数能访问父函数的变量，这也能减少全局命名空间的污染。

### 类

语法和 Java 类似。

```javascript
class Person {
    constructor(name) {
        this.name = name;
    }
    sayHello() {
        return `Hello, I'm ${this.name}!`;
    }
}

const p = new Person("Maria");
console.log(p.sayHello());
```

-   JS 的类不过是必须使用 `new` 实例化的函数罢了

-   mixin 模式：类的创建可以根据需求很随意地变化

    ```javascript
    const withAuthentication = (cls) =>
        class extends cls {
            authenticate() {
                // …
            }
        };

    class Admin extends withAuthentication(Person) {
        // …
    }
    ```

-   属性

    -   静态属性：`static`
    -   私有属性：`#`，并且这个 `#` 是属性名称的一部分（把它当作 Python 中的 `_`）。绝对没有任何办法在类之外的地方访问私有属性，即使是派生类型。

### 异步编程

-   JS 天生是单**线程**的，没有并行（paralleling）的概念，只有并发（concurrency）。

    > -   并行：两个任务在**同一时刻互不干扰**的同时执行。
    > -   并发：同时安排若干个任务，这些任务可以彼此穿插着进行；有些任务可能是并行的，比如买菜、发邮件和去幼儿园的某些路途是重叠的，这时你的确同时在做三件事；但进菜市场和发邮件和接娃三者是互斥的，每个时刻只能完成其中一件。换句话说，并发允许两个任务彼此干扰。
    > -   串行还是并发，这都是**任务安排者**视角看到的东西。
    > -   相比之下，“并行”是**任务执行者**视角的东西。
    >
    > 《深入理解计算机系统》对两个术语作了清晰明了的定义：
    >
    > -   并发（concurrency）：一个同时具有多个活动的系统
    > -   并行（parallelism）：用并发使一个系统运行得更快

-   JS 异步编程由**事件循环**驱动，允许一堆任务组织成队列等待完成。JS 有三种惯用的异步编程方法：

    -   回调函数
    -   `Promise`
    -   `async/await` ，只是 `Promise` 的语法糖

    例子：

    ```javascript
    // Callback-based
    fs.readFile(filename, (err, content) => {
        // This callback is invoked when the file is read, which could be after a while
        if (err) {
            throw err;
        }
        console.log(content);
    });
    // Code here will be executed while the file is waiting to be read

    // Promise-based
    fs.readFile(filename)
        .then((content) => {
            // What to do when the file is read
            console.log(content);
        })
        .catch((err) => {
            throw err;
        });
    // Code here will be executed while the file is waiting to be read

    // Async/await
    async function readFile(filename) {
        const content = await fs.readFile(filename);
        console.log(content);
    }
    ```

-   异步编程需要注意与外界的交互。让那些可能长时间运行的操作保持异步，这样其他步骤可以在操作等待时保持运行。

-   不可能同步地读取异步的值，只可能读取最终值。

    #暂缓学习

### 模块

-   模块通常是：a file, identified by it's file path or URL
-   可以 use the [`import`](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Statements/import) and [`export`](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Statements/export) statements to exchange data between modules

> Different runtimes may use different module systems. For example, [Node.js](https://nodejs.org/en/) uses the package manager [npm](https://www.npmjs.com/) and is mostly file-system based, while [Deno](https://deno.land/) and browsers are fully URL-based and modules can be resolved from HTTP URLs.

### 运行时

A runtime, or a host, is something that feeds data to the JavaScript engine (the interpreter), provides extra global properties, and provides hooks for the engine to interact with the outside world.

Module resolution, reading data, printing messages, sending network requests, etc. are all runtime-level operations.

While you learn about JavaScript core features, it's also important to understand host-provided features in order to put the knowledge to use.

## 词汇语法

-   Identifiers
    -   标识符用于把值和名字联系起来。
    -   标识符由数组、字符、下划线、`$` 组成。
        -   由于 Unicode，你甚至可以使用中文作为标识符。
-   Arrow function `=>`

    -   没有 `this`, `argument` 等的绑定，因此不应当被作为对象属性的方法使用

    -   不能当作构造器

    -   语法：

        ```javascript
        param => expression
        (param) => expression
        (param1, paramN) => expression
        param => {
          statements
        }
        (param1, paramN) => {
          statements
        }
        ```

### 运算符

-   `...` Spread syntax

    -   有三种应用情况：

        ```javascript
        myFunction(a, ...iterableObj, b)
        [1, ...iterableObj, '4', 'five', 6]
        { ...obj, key: 'value' }
        ```

-   Destructuring assignement

    -   只是把数组、对象标志放在了赋值表达式的左边，表示怎么从右侧的量中提取值

    -   常用例：

        ```javascript
        const x = [1, 2, 3, 4, 5];
        const [y, z] = x; //y = 1, z = 2
        const obj = { a: 1, b: 2 };
        const { a, b } = obj; //a = obj.a, b = obj.b;
        ```

        嵌套情况：

        ```javascript
        const obj = { a: 1, b: { c: 2 } };
        const {
            a,
            b: { c: d },
        } = obj;
        ```

        上面这些是“绑定模式”

    -   赋值模式：外面用括号括起来，属性被赋予指定的变量，这样所有东西都能出现在赋值表达式的左侧。

        ```javascript
        const numbers = [];
        const obj = { a: 1, b: 2 };
        ({ a: numbers[0], b: numbers[1] } = obj);
        ```
