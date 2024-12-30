# C++ Concurrency in Action

## 第二章 线程管控

### 2.1 线程的基本管控

!!! note "RAII (Resource Acquisition Is Initialization)"

    - 一种资源管理技术，通过在构造函数中获取资源，析构函数中释放资源，来保证资源的正确释放。
    - 适用于任何资源，包括内存、文件描述符、互斥量、线程等。

- 在 `thread` 对象被销毁前，应当决定线程汇合或分离，否则析构函数调用 `terminate()` 终止程序，引发异常。
    - 一旦调用 `join()`，属于线程的存储空间被清空，`thread` 也不再关联到线程。
    - 如果线程启动后抛出异常，可能导致 `join()` 未被调用。最优的方案是在析构函数中调用 `join()`。
- 生存期问题。一般让线程函数 self-contain，将所需数据复制到线程内部。

### 2.2 向线程函数传递参数

- `thread` 的构造函数只是简单地拷贝实参到新线程的空间，将其当作右值传给新线程上的可调用对象。
    - **`thread` 的构造函数对可调用对象的参数类型并不知情**，参数转换发生在进入新线程上下文后。
    - 如果传递指针作为实参，可能导致转换发生时指针所指的对象已被销毁，需要提前完成转换。

        ```cpp
        thread t(string(buffer));
        ```

    - 如果可调用对象的参数是引用，通过上面的方式它将得到以右值形式传递的参数的副本，导致编译失败。应当使用 `ref()` 包装引用。
    - 如果需要移动对象（比如 `unique_ptr`），可以使用 `move()`。

!!! note "move-only 类型"

    [Rvalue Reference Quick Look](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2027.html#Move_Semantics)

    `thread` 也是一种 move-only 类型，只能移动，不可拷贝。

