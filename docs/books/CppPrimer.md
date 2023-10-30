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

<!-- prettier-ignore-start -->
!!! note "Variables must be defined exactly once but can be declared many times."
<!-- prettier-ignore-end -->

#### Compound Types

More generally, a declaration is a base type followed by a list of **declarators**. Each declarator names a variable and gives the variable a type that is related to the **base type**.

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

- `Top-level` `const`: an object itself is a `const`.
- `Low-level` `const`: the pointer points to a `const` object. appears in the base type of compound types such as pointers or references.

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
<!-- prettier-ignore-end -->



<!-- prettier-ignore-start -->
??? note "随手记点单词"

    - variable-langth
    - undefined behavior, implementation-defined behavior
    - 
<!-- prettier-ignore-end -->

### Chapter 3. Strings, Vectors, and Arrays

### Chapter 4. Expressions

### Chapter 5. Statements

### Chapter 6. Functions

### Chapter 7. Classes
