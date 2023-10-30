# C++ Primer

<!-- prettier-ignore-start -->
!!! abstract

    This note is written in English. 
<!-- prettier-ignore-end -->

## Chapter 1. Getting Started

Somethings different from C:

-   `iostream` library: - `istream`, `ostream` - `cin`, `cout`, `cerr` (stderr, not buffered), `clog` (stderr, buffered) - built-in (primitive) type, class type - `::` scope operator

<!-- prettier-ignore-start -->

??? note "随手记点单词"

    - curly brace, open curly, close curly
    - parentheses
    - underscore
    - directive 指令

<!-- prettier-ignore-end -->

## Part 1 The Basics

### Chapter 2. Variables and Basic Types

<!-- prettier-ignore-start -->
!!! abstract "Key"

    - `const` Qualifier
    - reference
<!-- prettier-ignore-end -->

#### Type Conversions

-   If we assign an out-of-range value to an object of **unsigned** type, the result is the remainder of the value modulo the number of values the target type can hold (wrap around).
-   If we assign an out-of-range value to an object of **signed** type, the result is undefined.

<!-- prettier-ignore-start -->
!!! example "unsigned type"
    
    Assigning –1 to an 8-bit unsigned char gives that object the value 255.

!!! danger "Don't mix signed and unsigned types"

??? note "Specifying the Type of a Literal"

    Character and character string literals **prefix**:

    - `u`: `char16_t` (Unicode 16)
    - `U`: `char32_t` (Unicode 32)
    - `L`: `wchar_t`
    - `u8`: `char` (utf-8, string literal only)

    Integer literals **suffixes**:

    - `u`: `unsigned`
    - `l`: `long`
    - `ll`: `long long`

    Floating-point literals **suffix**:

    - `f`: `float`
    - `l`: `long double`
<!-- prettier-ignore-end -->

#### List Initialization (C++ 11)

Braced lists of initializers can now be used whenever we initialize an object and in some cases when we assign a new value to an object.

```c
int units_sold = 0;
int units_sold = {0};
int units_sold{0};
int units_sold(0);
```

List initialization prevents narrowing conversions.

<!-- prettier-ignore-start -->
!!! note "Variables must be defined exactly once but can be declared many times."
<!-- prettier-ignore-end -->

#### Compound Types

More generally, a declaration is a base type followed by a list of **declarators**. Each declarator names a variable and gives the variable a type that is related to the **base type**.

<!-- prettier-ignore-start -->
!!! tip "A reference or pointer is part of a particular declarator and not part of the base type for the declaration."
<!-- prettier-ignore-end -->

-   A reference defines an alternative name (alias) for an object.

    ```c
    int &refVal = ival; // refVal refers to (is another name for) ival
    ```

    -   There is no way to **rebind** a reference to refer to a different object. References must be initialized.
    -   The type of a reference and the object to which the reference refers must match exactly.
    -   A reference may be bound only to an object, **not to a literal or to the result of a more general expression**.

        ```c title="reference to pointer"
        int *p;
        int *&r = p;
        ```

        !!! tip "read from right to left"

    -   A reference is not an object. Hence, we may **not have a pointer to a reference**.

`nullptr` (C++ 11) is a literal that has a special type that can be converted to any other pointer type. Use it to initialize pointers. `NULL` is now defined in `<cstdlib>`.

We cannot use a `void*` to operate on the object it addresses—we don’t know that object’s type, and the **type determines what operations we can perform** on the object. Use a `void*` pointer to deal with memory as memory, rather than using the pointer to access the object stored in that memory.

#### `const` Qualifier

<!-- prettier-ignore-start -->
!!! note "To share a const object among multiple files, you must define the variable as extern."

??? note "By Default, `const` Objects Are Local to a File"

    When a const object is initialized from a **compile-time** constant, the compiler will usually replace uses of the variable with its corresponding value during compilation.

    To substitute the value for the variable, the compiler has to see the variable’s initializer. To support this usage, yet avoid multiple definitions of the same variable, `const` variables are defined as local to the file.

    Sometimes we have a `const` variable that we want to share across multiple files but whose initializer is not a constant expression. We use the keyword extern on both its definition and declaration(s).

!!! note "Initialize a **reference to `const`** from any expression that can be **converted** to the type of the reference."

    We can bind a reference to const to a nonconst object, a literal, or a more general expression:

    ```c
    const int &r2 = 42; // ok: r1 is a reference to const
    const int &r3 = r1 * 2; // ok: r3 is a reference to const
    ```

!!! tip "A Reference to `const` May Refer to an Object That Is Not `const`."
<!-- prettier-ignore-end -->

-   `Top-level` `const`: an object itself is a `const`.
-   `Low-level` `const`: the pointer points to a `const` object. appears in the base type of compound types such as pointers or references.

When we copy an object, top-level `const`s are ignored. Low-level `const` is never ignored.

```c
int *const p1 = &i; // we can’t change the value of p1; const is top-level
const int ci = 42; // we cannot change ci; const is top-level
const int *p2 = &ci; // we can change p2; const is low-level
```

<!-- prettier-ignore-start -->
!!! note "`constexpr` Variables"

    There are several contexts in the language that require constant expressions.

    We can ask the compiler to verify that a variable is a constant expression by declaring the variable in a constexpr declaration. Variables declared as constexpr are implicitly const andmust be initialized by constant expressions.

    ```c
    constexpr int mf = 20; // 20 is a constant expression
    ```

    !!! note "The address of an object defined outside of any function is a constant expression (stored in fixed address), and so may be used to initialize a constexpr pointer."

    `constexpr` imposes a **top-level** const on the objects it defines. A constexpr pointer may point to a const or a nonconst type.
<!-- prettier-ignore-end -->

#### Dealing with Types

-   new way to define a type alias: `using SI = Sales_item`. (C++ 11)

<!-- prettier-ignore-start -->
!!! danger "Declarations that use type aliases that represent compound types and const can yield surprising results."
<!-- prettier-ignore-end -->

-   `auto` (C++ 11): the type of the variable that we are defining will be deduced from the initializer we provide.
    -   `auto` ordinarily ignores **top-level** consts.
    -   If you want so, use `const auto`.
-   `decltype` (C++ 11): analyzes the expression to determine its type but **does not evaluate** the expression.
    ```c
    decltype(f()) sum = x; // sum has whatever type f returns
    ```

<!-- prettier-ignore-start -->
!!! danger "`decltype` will include top-level `const`s and references in its deduced type."

    `decltype` is the **only** context in which a variable defined as a reference is not treated as a synonym for the object to which it refers.

!!! danger "`decltype` returns a reference type for expressions that yield objects that can stand on the left-hand side of the assignment"

    If `p` is a pointer to `int`, then `decltype(*p)` is **`int&`**, not int.

!!! danger "enclosing the name of a variable in parentheses affects the type
returned by `decltype`"

    - `decltype((variable))` (note, double parentheses) is always a reference type
    - `decltype(variable)` is a reference type only if variable is a reference.
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
??? note "随手记点单词"

    - variable-langth
    - undefined behavior, implementation-defined behavior
<!-- prettier-ignore-end -->

### Chapter 3. Strings, Vectors, and Arrays

<!-- prettier-ignore-start -->
!!! abstract "Key"

    - `using`
    - `string`
    - `vector`
    - Iterators
<!-- prettier-ignore-end -->

#### `using` Declaration

-   A Separate using Declaration Is Required for Each Name
    ```c
    using std::cout; using std::endl;
    ```
-   Headers Should Not Contain `using` Declarations

#### String

Ways to Initialize a `string`:

```cpp
string s1; // default initialization; s1 is the empty string
string s2(s1); // s2 is a copy of s1
string s3("value"); // s3 is a copy of the string literal
string s3 = "value"; // equivalent to s3("value")
...
```

Some operation:

```cpp
is >> s; // Reads whitespace-separated string into s. Returns is.
getline(is, s); // Reads a line of input from is into s. Return is.
s.empty(); // Returns true if s is empty; otherwise returns false.
...
```

<!-- prettier-ignore-start -->
!!! tip "Stream is valid until it has hit end-of-file or an error."

    Used as condition.

!!! tip "`getline()` don't save the newline character."
!!! tip "`string::size_type` Type"

    It is an unsigned type.

    For example, if `n` is an int that holds a negative value, then `s.size() < n` will almost surely evaluate as true. It yields true because the negative value in n will convert to a large unsigned value.
<!-- prettier-ignore-end -->

`string` library lets us convert both **character literals and character string literals** to `strings`.

#### Range-Based `for`

```cpp
for (declaration : expression)
    statement
```

-   `expression` is an object of a type that represents a sequence
-   `declaration` defines the variable that we’ll use to access the underlying elements in the sequence.

On each iteration, the variable in declaration is initialized from the value of the next element in expression.

```cpp
decltype(s.size()) punct_cnt = 0;
// count the number of punctuation characters in s
for (auto c : s) // for every char in s
    if (ispunct(c)) // if the character is punctuation
        ++punct_cnt; // increment the punctuation counter
cout << punct_cnt
     << " punctuation characters in " << s << endl;
```

<!-- prettier-ignore-start -->
!!! tip "If we want to change the value of the characters in a string, wemust define the loop variable as a reference type"
<!-- prettier-ignore-end -->

#### `vector`-container and class template

<!-- prettier-ignore-start -->
!!! tip "`vector` is a template, not a type. Types generated from vector must
include the element type."
<!-- prettier-ignore-end -->

Ways to Initialize a `vector`:

```cpp
vector<T> v1; // v1 is empty
vector<T> v2(v1); // v2 is a copy of v1
vector<T> v2 = v1; // equivalent to v2(v1)
vector<T> v3(n, val); // v3 has n elements with value val
vector<T> v4(n); // v4 has n copies of the value-initialized value of T
vector<T> v5{a, b, c...}; // v5 has as many elements as there are initializers
vector<T> v5 = {a, b, c...}; // equivalent to v5{a, b, c...}
```

<!-- prettier-ignore-start -->
!!! tip "Parentheses construct the object, curly braces **list initialize** the object."
<!-- prettier-ignore-end -->

Some operation:

```cpp
v.push_back(t); // Adds a copy of t to the end of v. Returns void.
```

<!-- prettier-ignore-start -->
!!! danger "The body of a range for must not change the size of the sequence over which it is iterating."
!!! tip "`vector<int>::size_type` instead of `vector::size_type`"
<!-- prettier-ignore-end -->

#### Iterators

All of the **library containers** have iterators, but only a few of them support the subscript operator.

A **valid** iterator either denotes an element or denotes a position **one past the last element** in a container.

Obtain an iterator:

```cpp
auto b = v.begin(); // denotes the first element
auto b = v.cbegin(); // const iterator
auto c = cv.begin(); // also const iterator (vector is const)
auto e = v.end(); // denotes one past the last element
```

<!-- prettier-ignore-start -->
!!! tip "**of-the-end** iterator"

    If container is empty, begin and end iterator are equal.
<!-- prettier-ignore-end -->

Dereference an iterator to obtain the element denoted
by an iterator.

```cpp
*iter;
iter->mem;
++iter;
--iter;
iter1 == iter2;
```

<!-- prettier-ignore-start -->
!!! tip "C++ prefers `!=` to `>` and `<`. Use it."
!!! info "Iterator Types: `vector<int>::iterator`, `vector<int>::const_iterator`"
!!! danger "Changes the size of a `vector` potentially invalidates all iterators into that `vector`."
<!-- prettier-ignore-end -->

**Some** iterator support all relational operators (such as `vector` and `string`):

```cpp
+ - += -= > >= < <=
```

<!-- prettier-ignore-start -->
!!! note "Subtraction of two iterators result in `difference_type`, which is **signed**."

!!! example "iterator arithmetic"

    ```cpp
    // text must be sorted
    // beg and end will denote the range we’re searching
    auto beg = text.begin(), end = text.end();
    auto mid = text.begin() + (end - beg)/2; // original midpoint
    // while there are still elements to look at and we haven’t yet found sought
    while (mid != end && *mid != sought) {
        if (sought < *mid) // is the element we want in the first half?
            end = mid; // if so, adjust the range to ignore the second half
        else // the element we want is in the second half
            beg = mid + 1; // start looking with the element just after mid
    mid = beg + (end - beg)/2; // new midpoint
    }
    ```

!!! tip "Complicated Array Declarations"

    No array of references. No vector of references.

    Reference is not a type.

    ```cpp
    int *ptrs[10]; // ptrs is an array of ten pointers to int
    int &refs[10] = /* ? */; // error: no arrays of references
    int (*Parray)[10] = &arr; // Parray points to an array of ten ints
    int (&arrRef)[10] = arr; // arrRef refers to an array of ten ints
    int *(&arry)[10] = ptrs; // arry is a reference to an array of ten pointers
    ```
<!-- prettier-ignore-end -->



<!-- prettier-ignore-start -->
!!! note "随手记点单词"

    - instantiation
<!-- prettier-ignore-end -->

### Chapter 4. Expressions

### Chapter 5. Statements

### Chapter 6. Functions

### Chapter 7. Classes
