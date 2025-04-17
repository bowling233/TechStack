# Go

!!! abstract

    本篇笔记以 [:simple-github: go101](https://github.com/go101/go101) 和 [Let's Go!](https://lets-go.alexedwards.net/) 为基础。

## 语言

Go 语言的特点：

- 编译型语言
- 静态类型
- 类 C 语法
    - C、C++、Java、JavaScript、C# 都算类 C 语法
- 垃圾回收（GC）
    - 具有 GC 的语言还有：Ruby、Python、Java、C#、JavaScript

### 工具链与项目管理

!!! tip "使用代理"

    国内最好用的 Go 代理是 [七牛云 - Goproxy.cn](https://goproxy.cn/)，先按教程配置好代理。

Go 语言本身更新比较频繁，需要像 Python 那样做版本管理。非常方便的事情是：Go 可以管理自身的版本。因此系统的 Go 版本陈旧并不是问题（比如 Debian 官方源的 Go 更新十分缓慢）。

```shell
go install golang.org/dl/go1.23.3@latest
go1.23.3 download
```

使用 Go 工具链时需要注意几个环境变量：

- `GOPATH`：默认是 `$HOME/go`。
    - `pkg` 目录缓存 modules。
    - `bin` 存放 `go install` 的可执行文件。
- `GOROOT`：Go 的安装目录，由 `go` 命令自动识别。

常用命令：

```shell
go run
go build
go install
go vet # 语法检查
go fmt # format
go test
go doc
```

!!! quote

    - [Understanding Go Modules for Beginners](https://www.pingcap.com/article/understanding-go-modules-for-beginners/)
    - [How to Write Go Code - The Go Programming Language](https://go.dev/doc/code#Organization)

Go Module 在我初学时给我带来了极大的困惑，特别是配置环境时。

- **包（Package）** 是代码封装的基本单位。包可以暴露公有接口给其他包使用，其他包必须导入（import）才能使用。
    - 一个目录（不包括子目录）下的源文件**必须属于同一个包**，因此一个文件夹就是一个包。
    - 文件夹名称为 `internal` 的包只能在其父目录下使用。
    - 名称为 `main` 的包称为程序包（program package），其他包称为库包（library package）。
- **模块（Module）** 是包的集合，根目录的 `go.mod` 描述用到了该模块的路径、版本和依赖项。

```shell
# automatically
go mod tidy
# add/upgrade/downgrade/remove
go get github.com/some/package@version
# list upgradeable modules
go list -u -m all
```

- **仓库（Repository）**：模块的集合。然而一般情况下一个仓库包含一个 module。

!!! example

    Google 发布的 module `go-cmp` 有一个包 `cmp`，那么它的 `import` 路径是

    ```text
    github.com/google/go-cmp/cmp
    ```

### 基础知识

`main` 函数必须定义在 `main` 包中，作为程序入口（entrypoint）：

```go
package main
func main() {}
```

!!! tip "换行"

    Go 不允许某些 `{` 被放置在下一行，比如 `if`、`for` 等语句：

    ```go
    if a > b {
        // ...
    }
    ```

标识符：

- 以**大写字符**开头的标识符是可导出的（exported），可以被其他包访问。可以理解为 C++ 的 `public`。
- 支持 Unicode。
- `_` 是空白标识符（blank identifier）。

类型与字面量：

```go
bool
int8 uint8 int16 uint16 int32 uint32 int64 uint64 int uint uintptr
float32 float64 complex64 complex128
string
// 内置类型别名
type byte = uint8
type rune = int32 // Unicode 码点
// 类型声明
type MyInt int // 两个类型不同
// 字面量
0o17 0b1111 0_33_77_22
// rune
'众' '\u4f17'
```

- `string` 存储为 UTF-8。
- 所有类型具有**零值（zero value）**，即默认值。
- 没有**布尔字面量**，`true` 和 `false` 是预定义的常量（named constant）。
- **数值字面量**支持 `_` 提供更好可读性。
- **数值字面量（常量）的转换**：目标类型必须能够表示源类型的值，**不允许溢出**。

    ```go
    TODO
    ```

- `"` 引起**可转义字符串（interpreted string）**，`\`` 引起**原始字符串（raw string）**，能够跨行。

常量与变量：

```go
// 类型转换
T(v) (T)(v)
// 有名常量
const (
    pi = 3.14
    e = 2.718
)
const pi = 3.14, e = 2.718
// 有名有类型常量
const (
    pi float64 = 3.14
    e float32 = 2.718
)
// 常量声明组的自动补全、常量生成器 iota
const (
    Failed = iota - 1 // == -1
    Unknown           // == 0
    Succeeded         // == 1
)
// 变量声明（标准形式）
var power int = 900
var (
    lang, dynamic = "Go", false
)
// 变量声明（简短形式，仅本地变量）
name, power := "Goku", 9001
```

- **类型后置**
- **常量**分为**有名/无名**、**有类型/无类型**。

!!! tip "可以将常量理解为 C 中 `#define` 的增强版"

    常量在编译时被替换为字面量，常量表达式在编译时计算出值。

- 结合常量数值的转换规则，理解下面的常量声明：

    ```go
    // error: -1 overflows uint
    const MaxUint_a = uint(^0)
    // error: -1 overflows uint
    const MaxUint_b uint = ^0
    // correct
    const MaxUint = ^uint(0)
    ```

- **变量**都是有类型的。
- 不支持**链式赋值**。
- `:=` 结合了声明和赋值的功能。
- 不允许未使用的**本地变量**。
- **全局变量**的依赖关系决定初始化顺序，不允许循环依赖 `var a, b = b, a`。
- 所有变量**可寻址（addressable）**，常量不可寻址。
- 数值**变量**的**显式转换**允许溢出（overflow）和截断（round）。

    ```go
    const a = -1.23
    // The type of b is deduced as float64.
    var b = a
    // error: constant 1.23 truncated to integer.
    var x = int32(a)
    // error: cannot assign float64 to int32.
    var y int32 = b
    ```

运算符：

- `&^` 是按位清除（bit clear）运算符。
- `>>` 是算术右移。
- 一元运算符 `^` 计算按位取反（bitwise complement），相当于 C 中的 `~`。

函数声明：

```go
func power (name string) (a int, b bool) {
    return
}
func power (a, b bool) string {
}
// 匿名函数及其调用
x, y := func(a, b int) (int, int) {
}(c, d)
```

- **返回类型后置，允许返回多个值**。返回值的名称可以省略。
- 如果返回值列表未省略名称，则 `return` 语句可以省略返回值名称。
- 不支持默认参数值。默认返回值初始值为零值。
- 参数拷贝传递。

包：

```go
import (
    importname "path/to/package"
    . "path/to/package" // 直接使用包导出的标识符
    _ "net/http/pprof" // 仅导入包，执行初始化，但无法使用包导出的标识符
)
// 内置
println()
len()
// 标准库：fmt
fmt.Println()
// 标准库：os
os.Args
os.Exit()

```

- 不允许未使用的包。
- 标准库 [pkg.go.dev/std](https://pkg.go.dev/std)。
- 在一个包甚至一个源文件中，可以重复定义 `init()` 函数。它们将被在 `main()` 之前顺序调用。`init()` 不接受参数，不返回值。

### 第二章：结构

Go 不是面向对象语言，没有对象和继承，更没有多态和重载。C++、Java、Ruby 和 C# 是面向对象语言。

Go 具有结构，可以和方法关联，支持简单且高效的组合。

```go
type Saiyan struct {
    Name string
    Power int
}
goku := Saiyan{}
goku := Saiyan{"Goku", 9000}
goku := Saiyan{Name: "Goku"}
goku.Power = 900
```

指针：

```go
goku := &Saiyan{"Goku", 9000}
func Super(s *Saiyan) {
    s.Power += 10000
}
```

- 熟悉的 `&` 和 `*`。

!!! tip

    If you aren't sure, use a pointer.

上面的声明将 `Super()` 和 `type Saiyan` 关联起来，`*Saiyan` 称为 `Super()` 的接收者（receiver）。

```go
goku.Super()
```

结构没有构造函数，可以创建一个返回对应类型的函数（不一定要是指针），称为工厂函数（factory function）。

```go
func NewSaiyan(name string, power int) *Saiyan {
    return &Saiyan{
        Name: name,
        Power: power,
    }
}
```

也可以使用内置 `new` 函数。`new(X)` 结果与 `&X{}` 相同。

在 Go 中广泛使用组合。Go 编程者认为这是比继承更具有鲁棒性的共享代码的方式。结构中使用结构作为匿名域，可以可以直接访问其中的域和函数：

```go
type Person struct {
    Name string
}
func (p *Person) Introduce() {
    fmt.Println("Hi, I'm " + p.Name)
}
type Saiyan struct {
    *Person
    Power int
}
goku := &Saiyan{
    Person: &Person{"Goku"},
    Power: 9000,
}
goku.Introduce()
```

### 第三章：映射、数组和切片

数组：

```go
scores := [4]int{9001, 9333, 212, 33}
for index, value := range scores {}
```

- 固定长度，数组越界访问是编译或运行时错误。
- `range`

在 Go 中很少直接使用数组。切片（slice）是轻量级的结构，表示数组的一部分：

```go
scores := []int{1, 2, 3, 4, 5}
scores := make([]int, 0, 10)
scores := make([]*Saiyan, 0)
var names []string
scores = append(scores, 5)
scores = scores[1:4]
c := cap(scores)
```

- 切片声明不带长度。
- `make` 为切片底层的数组分配空间，并初始化切片。
    - length 指切片的大小。
    - capacity 指底层数组的大小。
    - 只有一个参数时，length 和 capacity 相同。
- `cap` 返回切片的容量。
- `append` 为切片添加元素。
    - 如果底层数组满了，它会创建更大的新数组并拷贝原数组的元素。所以上面要使用赋值，因为 `append` 可能会返回新的。
- 切片可以重新切片。
- `[:]`
    - 不支持负值。使用 `len` 和 `cap` 计算。
- 在 Ruby 和 Python 中，切片是新的数组。而在 Go 中，切片是对数组的引用。
- `copy(dst, src)` 函数可以复制切片。函数从两个切片的开头开始，将 src 中的元素复制到 dst 中，直到其中一个切片耗尽。

```go
func removeAtIndex(source []int, index int) []int {
    last := len(source) - 1
    // swap the last element and the element to remove
    source[index], source[last] = source[last], source[index]
    return source[:last]
}
```

映射

```go
lookup := make(map[string]int)
lookup := make(map[string]int, 100)
lookup["goku"] = 9001
power, exists := lookup["vegeta"]
delete(lookup, "goku")
type Saiyan struct {
    Friends map[string]*Saiyan
}
```

- `range` 顺序随机。

指针与值的选择：

```go
a := make([]Saiyan, 10)
b := make([]*Saiyan, 10)
```

一个是值切片，一个是指针切片。有些程序员认为 `b` 在传递和返回时更好，但事实并不如此。传递和返回的是切片，而**切片自己就是引用**。

### 第四章：代码组织和接口

!!! note

    本节讲述的称为 GOPATH 开发模式，已经过时。自 Go 1.16（2021 年），GOPATH 模式被默认关闭，总是使用 module 模式。可以参考 [Go Wiki: GOPATH](https://go.dev/wiki/GOPATH)，使用 Go Modules。

    ```shell
    $ cd mymod
    $ go mod init mymod
    go: creating new go.mod: module mymod
    ```

    下文中过时的内容使用引用格式标注。

> 包的名称遵循 Go 工作区的目录结构，如 `shopping` 包位于 `$GOPATH/src/shopping`。

使用 `package` 命名包时可以不含路径，但是用 `import` 从其他地方导入时需要使用路径。

Go 不允许循环导入（cyclical imports）。

Go 的可见性由名称决定。大写字母开头的名称是可导出的，小写字母开头的是私有的。

使用 `go get` 拉取远程包。

本节最后介绍的 Dependency Management 最终 2020 年被 Go Modules 取代。

接口定义契约而没有实现。

```go
type Logger interface {
    Log(message string)
}
```

在 Java 中，需要显式实现该接口：

```java
public class ColorLogger implements Logger {
    public void Log(String message) {
        System.out.println("Red: " + message)
    }
}
```

在 Go 中，只需要名称和参数对应，就能当作接口的实现：

```go
type ConsoleLogger struct {}
func (l ConsoleLogger) Log(message string) {
    fmt.Println(message)
}
```

### 第五章：杂项

#### 错误处理

```go
n, err := strconv.Atoi(os.Args[1])
if err != nil {
    fmt.Println("not a valid number")
}
```

可以创建自己的错误类型，只要满足内置 `error` 接口的契约：

```go
type error interface {
    Error() string
}
```

标准库中有一些错误变量，应该使用它们：

```go
var EOF = errors.New("EOF")

_, err := fmt.Scan(&input)
if err == io.EOF {
    fmt.Println("No more input")
}
```

#### 垃圾回收

虽然 Go 有垃圾回收，但文件等资源还是要手动释放。`defer` 语句可以在函数返回时执行。

```go
defer file.Close()
```

#### 格式化

`go fmt ./..`

#### 初始化 if

```go
if err := file.Chmod(0664); err != nil {
    fmt.Println(err)
}
```

只在 if 语句中可见。

#### 空接口和惯例

空接口 `interface{}` 没有任何方法，因此所有类型都实现了它。使用 `.(TYPE)` 将空接口转换为具体类型。

```go
func add (a interface{}, b interface{}) interface{} {
    switch a.(type) {
        case int:
            return a.(int) + b.(int)
        default:
        //...
    }
}
```

#### 字符串和字符数组

容易转换。

```go
stra := "test"
byts := []byte(stra)
string := string(byts)
```

字符串由 Unicode 码点称为 rune（如尼文字）组成。对 `string` 取长度可能与预期有别。使用 `range` 遍历 string 是以 rune 为单位的。

#### 函数类型

函数是第一类类型（first-class type），可以在任何地方使用：作为类型、参数、返回值。

### 第六章：并发

## 模块

### `net/http`

```go
import (
    "net/http"
)

func handler(w http.ResponseWriter, r *http.Request) {
    if r.Method != http.MethodGet {
        w.Header().Set("Allow", http.MethodGet)
        // Add, Get, Set, Del
        http.Error(w, "Method Not Allowed", http.StatusMethodNotAllowed)
        return
    }
    // Query
    id, err := strconv.Atoi(r.URL.Query().Get("id"))
    if err != nil || id < 1> {
        http.NotFound(w, r)
        return
    }
    w.Write([]byte("Hello, world!"))
    fmt.Fprintf(w, "Hello, %s!", r.URL.Path[1:])
}

func main() {
    mux := http.NewServeMux()
    // fixed path 不以 `/` 结尾，使用最长前缀匹配
    // subtree path 以 `/` 结尾，使用任意前缀匹配
    // 路由可以使用主机名，如 `foo.example.com/`
    mux.HandleFunc("/", handler) // 匹配所有
    err := http.ListenAndServe(":8080", mux)
    log.Fatal(err)
}
```
