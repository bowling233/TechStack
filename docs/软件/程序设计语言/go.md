# Go

## The Little Go Book

### 第一章：基础

Go 语言的特点：

- 编译型语言
- 静态类型
- 类 C 语法
    - C、C++、Java、JavaScript、C# 都算类 C 语法
- 垃圾回收（GC）
    - 具有 GC 的语言还有：Ruby、Python、Java、C#、JavaScript

GO 的入点是 package `main` 中的 main 函数。

```go
package main
func main() {}
```

变量的声明和赋值：

```go
var power int = 900
power := 900
power := getPower()
name, power := "Goku", 9001
```

- 默认给变量赋初值。整数为 0，字符串为空字符串，布尔值为 false。
- `:=` 结合了声明和赋值的功能。
- 不允许未使用的变量。

函数声明：

```go
func power (name string) (int, bool) {}
```

- 函数可以返回多个值
- `_` 是空白标识符（blank identifier），对它赋值表示忽略某个值。
- 参数拷贝传递。

本章出现的包：

```go
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

## 个人笔记

### Go 代码组织和编译运行

!!! quote

    - [How to Write Go Code - The Go Programming Language](https://go.dev/doc/code#Organization)
    - [Managing Go installations - The Go Programming Language](https://go.dev/doc/manage-install#installing-multiple)

- Package：Go 中的包的概念很简单，与 Java、Python 中类似。
- Module：
    - Packages 的集合，目的是管理依赖。项目中的 `go.mod` 文件会描述：用到了哪些 package，它们由哪些 module 提供。
    - 在 [Tutorial: Get started with Go - The Go Programming Language](https://go.dev/doc/tutorial/getting-started) 的一开始，我们就使用了 `go mod init` 这条命令。
- Repository：Modules 的集合。然而一般情况下一个仓库包含一个 module。

!!! example

    Google 发布的 module `go-cmp` 有一个包 `cmp`，那么它的 `import` 路径是

    ```text
    github.com/google/go-cmp/cmp
    ```

Go 语言本身更新也比较频繁，需要像 Python 那样做版本管理。非常方便的事情是：Go 可以管理自身的版本。因此系统的 Go 版本陈旧并不是问题（比如 Debian 对 Go 的更新是比较不及时的）。

```shell
go install golang.org/dl/go1.23.3@latest
go1.23.3 download
```

- `go install` 命令将软件包安装到 `$GOPATH/bin` 或 `$HOME/go/bin`。然后就可以通过把版本号加到命令行来使用这个版本的 Go。
- `go download` 将该版本的 Go 下载到 `$HOME/sdk/go<version>`。
