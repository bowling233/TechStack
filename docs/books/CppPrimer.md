# C++ Primer

<!-- prettier-ignore-start -->
!!! abstract

    This note is written in English. 
<!-- prettier-ignore-end -->

## Chapter 1 Getting Started

Somethings different from C:

-   `iostream` library:
    -   `istream`, `ostream`
    -   `cin`, `cout`, `cerr` (stderr, not buffered), `clog` (stderr, buffered)
    -   built-in (primitive) type, class type
    -   `::` scope operator

<!-- prettier-ignore-start -->

??? note "随手记点单词"

    - curly brace, open curly, close curly
    - parentheses
    - underscore
    - directive
<!-- prettier-ignore-end -->

## Part I: The Basics

### Chapter 2 Variables and Basic Types

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

```cpp
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

    ```cpp
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

    ```cpp
    const int &r2 = 42; // ok: r1 is a reference to const
    const int &r3 = r1 * 2; // ok: r3 is a reference to const
    ```

!!! tip "A Reference to `const` May Refer to an Object That Is Not `const`."
<!-- prettier-ignore-end -->

-   `Top-level` `const`: an object itself is a `const`.
-   `Low-level` `const`: the pointer points to a `const` object. appears in the base type of compound types such as pointers or references.

When we copy an object, top-level `const`s are ignored. Low-level `const` is never ignored.

```cpp
int *const p1 = &i; // we can’t change the value of p1; const is top-level
const int ci = 42; // we cannot change ci; const is top-level
const int *p2 = &ci; // we can change p2; const is low-level
```

<!-- prettier-ignore-start -->
!!! note "`constexpr` Variables"

    There are several contexts in the language that require constant expressions.

    We can ask the compiler to verify that a variable is a constant expression by declaring the variable in a constexpr declaration. Variables declared as constexpr are implicitly const andmust be initialized by constant expressions.

    ```cpp
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
    ```cpp
    decltype(f()) sum = x; // sum has whatever type f returns
    ```

<!-- prettier-ignore-start -->
!!! danger "`decltype` will include top-level `const`s and references in its deduced type."

    `decltype` is the **only** context in which a variable defined as a reference is not treated as a synonym for the object to which it refers.

!!! danger "`decltype` returns a reference type for expressions that yield objects that can stand on the left-hand side of the assignment"

    If `p` is a pointer to `int`, then `decltype(*p)` is **`int&`**, not int.

!!! danger "enclosing the name of a variable in parentheses affects the type returned by `decltype`"

    - `decltype((variable))` (note, double parentheses) is always a reference type
    - `decltype(variable)` is a reference type only if variable is a reference.
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
??? note "随手记点单词"

    - variable-langth
    - undefined behavior, implementation-defined behavior
<!-- prettier-ignore-end -->

### Chapter 3 Strings, Vectors, and Arrays

<!-- prettier-ignore-start -->
!!! abstract "Key"

    - `using`
    - `string`
    - `vector`
    - Iterators
<!-- prettier-ignore-end -->

#### `using` Declaration

-   A Separate using Declaration Is Required for Each Name
    ```cpp
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
!!! tip "`vector` is a template, not a type. Types generated from vector must include the element type."
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

### Chapter 4 Expressions

Skipped.

#### Named Casts

A named cast has the following form:

```cpp
cast-name<type>(expression);
```

-   `static_cast`:
    -   Any well-defined type conversion, **other than those involving low-level const**, can be requested using a `static_cast`.
    -   useful to perform a conversion that the compiler will not generate automatically.
-   `dynamic_cast`
-   `const_cast`:
    ```cpp
    const char *pc;
    char *p = const_cast<char*>(pc); // ok: but writing through p is undefined
    ```
    -   A `const_cast` changes only a low-level const in its operand.
    -   the compiler will no longer prevent us from writing to that object.
-   `reinterpret_cast`:
    ```cpp
    int *ip;
    char *pc = reinterpret_cast<char*>(ip);
    ```
    -   performs a low-level reinterpretation of the bit pattern of its operands.

<!-- prettier-ignore-start -->
!!! danger "Avoid casts, especially `reinterpret_cast` and old-style casts `(type) expr` and `type (expr)`."
<!-- prettier-ignore-end -->

### Chapter 5 Statements

Skipped.

### Chapter 6 Functions

<!-- prettier-ignore-start -->
!!! abstract "Key"

    - Overloaded Functions
<!-- prettier-ignore-end -->

-   `void f1();` **implicit** `void` parameter list.

<!-- prettier-ignore-start -->
!!! warning "In C, `void no_args()` declares a function that takes an **unspecified (but not variable) number of parameters**."
<!-- prettier-ignore-end -->

#### Arguments

-   Pass by reference:

```cpp
void reset(int &i) {
    i = 0;
}
```

Reference parameters that are not changed inside a function should be references to const.

<!-- prettier-ignore-start -->
!!! tip "Reference parameters let us **effectively** return multiple results. "
<!-- prettier-ignore-end -->

-   `const` arguments:

Just as in any other **initialization**, when we copy an argument to initialize a parameter, **top-level** `consts` are ignored. The following two declarations are equivalent:

```cpp
void fcn(const int i) { /* fcn can read but not write to i */}
void fcn(int i) { /* .. . */} // error: redefines fcn(int)
```

<!-- prettier-ignore-start -->
!!! tip "The above rule is evident because arguments is passed by value except reference arguments which is **low-level** `const`."
<!-- prettier-ignore-end -->

-   Array arguments:

Cannot copy an array. Arrays is (usually) converted to pointer.

```cpp
// despite appearances, these three declarations ofprintare equivalent
// each function has a single parameter of type constint*
void print(const int*);
void print(const int[]); // shows the intent that the function takes an array
void print(const int[10]); // dimension for documentation purposes (at best)
```

<!-- prettier-ignore-start -->
!!! note "three common techniques used to manage pointer parameters"

    - Using a Marker to Specify the Extent of an Array
    - Using the Standard Library Conventions: pass `begin` and `end` pointers.
    - Explicitly Passing a Size Parameter

!!! danger "Array Reference Parameters"

    ```cpp
    f(int (&arr)[10]);
    ```

    - The parentheses around `&arr` are necessary.
    - Because **the size of an array is part of its type**, it is safe to rely on the dimension in the body of the function.

!!! tip "Passing a Multidimensional Array"

    - The **size of the second (and any subsequent) dimension is part of the element type** and must be specified.
<!-- prettier-ignore-end -->

#### `initializer_list` Parameters (C++ 11)

an unknown number of arguments of a **single
type**.

`initializer_list` header.

```cpp
void error_msg(initializer_list<string> il) {
    for (auto beg = il.begin(); beg != il.end(); ++beg)
        cout << *beg << " ";
    cout << endl;
}
```

-   the elements in an `initializer_list` are always `const` values.
-   When we pass a sequence of values to an initializer_list parameter, we must enclose the sequence in **curly brace**.

#### Ellipsis Parameters

A C library facility named `varargs`.

-   **Only** for types that are common to both C and C++. Objects of most class types are not copied properly when passed to an ellipsis parameter.
-   Appear only as the last element in a parameter list.
-   No type checking is done for the arguments that correspond to the ellipsis parameter.

#### Return Value

Values are returned in exactly the same way as variables and parameters are initialized: The return value is used to initialize a temporary at the call site, and that temporary is the result of the function call.

<!-- prettier-ignore-start -->
!!! danger "Never Return a Reference or Pointer to a Local Object"

    Here is a local temporary string.

    ```cpp
    return "Empty"; // WRONG: "Empty"is a local temporary string
    ```

!!! note "Calls to functions that return references are lvalues; other return types yield rvalues."

    ```cpp
    char &get_val(string &str, string::size_type ix) {
        return str[ix]; // get_valassumes the given index is valid 
    }
    int main() {
        string s("a value"); 
        cout << s << endl; // prints a value 
        get_val(s, 0) = ’A’; // changes s[0]to A 
        cout << s << endl; // prints A value return 0;
    }
    ```
<!-- prettier-ignore-end -->

-   List Initializing the Return Value
-   The main function may not call itself.

The form of a function that returns a pointer to an array is:

```cpp
Type (*function(parameter_list))[dimension]
```

<!-- prettier-ignore-start -->
!!! example "Think about follows"

    ```cpp
    func(int);
    (*func(int));
    (*func(int))[10];
    int (*func(int))[10];
    ```
<!-- prettier-ignore-end -->

-   Trailing Return Type (C++ 11)

Useful for functions with complicated return types

A trailing return type follows the parameter list and is preceded by `->`.

```cpp
auto func(int i) -> int(*)[10];
```

#### Overloaded Functions

Functions that have the same name but different parameter lists and that appear in the **same scope** are overloaded.

-   The main function may not be overloaded.
-   A type alias does not create a new type. So not overloadable.
-   **top-level** `const` is ignored. Can overload based on whether the parameter is a **reference (or pointer) to** the `const` or non`const` version of a given type.

`const_cast` is usually useful in overloaded functions:

```cpp
string &shorterString(string &s1, string &s2)
{
    auto &r = shorterString(const_cast<const string&>(s1),
                            const_cast<const string&>(s2));
    return const_cast<string&>(r);
}
```

Inner scope name hides uses of that name declared in an outer scope:

```cpp
string read();
void print(const string &);
void print(double); // overloads the printfunction v
oid fooBar(int ival)
{
    bool read = false; // new scope: hides the outer declaration of read
    string s = read(); // error: readis a boolvariable, not a function
    // bad practice: usually it’s a bad idea to declare functions at local scope
    void print(int); // new scope: hides previous instances of print
    print("Value: "); // error: print(const string &)is hidden
    print(ival); // ok: print(int)is visible
    print(3.14);
}
```

<!-- prettier-ignore-start -->
!!! note "In C++, name lookup happens **before** type checking."
!!! danger "Notice above **all** instances in outer scope is hidden."
<!-- prettier-ignore-end -->

#### Specialized Uses

-   Default Arguments: - The default arguments are used for the trailing (right-most) arguments of a call.
    <!-- prettier-ignore-start -->
    !!! danger "can omit only trailing arguments"
    <!-- prettier-ignore-end -->
-   Default Argument Declarations
    ```cpp
    string screen(sz, sz, char = ’*’);
    string screen(sz = 24, sz = 80, char); // ok: adds default arguments
    ```
    -   it is legal to redeclare a function multiple times.
    -   each parameter can have its default specified only once in a given scope.
    -   any subsequent declaration can add a default only for a parameter that has **not previously** had a default specified.
    -   defaults can be specified only if all parameters to the right already have defaults
-   Default Argument Initializers
    -   a default argument can be any **expression** that has a type that is convertible to the type of the parameter
-   -   `inline` Functions Avoid Function Call Overhead
    -   optimize small, straight-line functions that are called frequently
    -   putting the keyword `inline` before the function’s **return type**
    -   The compiler may choose to ignore this request.
-   `constexpr` function is a function that can be used in a constant expression
    ```cpp
    // scale(arg)is a constant expression ifarg is a constant expression
    constexpr size_t scale(size_t cnt) { return new_sz() * cnt; }
    ```
    -   The return type and the type of each parameter in a must be a literal type, and the function body must contain exactly one return statement.
    -   A constexpr function is not required to return a constant expression.
    -   A constexpr function is permitted to return a value that is not a constant.

<!-- prettier-ignore-start -->
!!! note "Put `inline` and `constexpr` Functions in Header Files"

    All of the definitions of a given `inline` or `constexpr` must match exactly. As a result, `inline` and `constexpr` functions normally are defined in headers.
<!-- prettier-ignore-end -->

#### `assert` and `NDEBUG`

-   `_ _func_ _`: compiler defines, the name of the function in which the call appears.
-   `_ _FILE_ _`: preprocessor defines, string literal containing the name of the file
-   `_ _LINE_ _`: preprocessor defines, integer literal containing the line number of the file
-   `_ _TIME_ _`: preprocessor defines, string literal containing the time of translation
-   `_ _DATE_ _`: preprocessor defines, string literal containing the date of translation

#### Function Matching

- candidate functions: same name, can be seen.
- viable functions: same number of parameters, each argument can be converted to the type of its corresponding parameter.

<!-- prettier-ignore-start -->
!!! tip "When a function has default arguments, a call may appear to have fewer arguments than it actually does."
<!-- prettier-ignore-end -->

Select the best match:

- The match for each argument is no worse than the match required by any other viable function.
- There is at least one argument for which the match is better than the match provided by any other viable function.

If after looking at each argument there is no single function that is preferable, then the call is in error. The compiler will complain that the call is **ambiguous**.

Casts should not be needed to call an overloaded function. The need for a cast suggests that the parameter sets are designed poorly.

Conversion ranks:

- exact match:
    - identical type
    - array to pointer
    - top-level const
- const conversion
- promotion: integral promotion, floating-point promotion
- arithmetic or pointer conversion
- class-type conversion

#### Pointers to Functions

Pointers to Overloaded Functions must match one of the overloaded functions **exactly**.

Returning a Pointer to Function better use type alias. Try to read this:

```cpp
int (*f1(int))(int*, int);
auto f1(int) -> int (*)(int*, int);
```

Using auto or decltype for Function Pointer Types:

```cpp
string::size_type sumLength(const string&, const string&); 
string::size_type largerLength(const string&, const string&); // depending on the value of its stringparameter, 
// getFcn returns a pointer to sumLengthor to largerLength 
decltype(sumLength) *getFcn(const string &);
```

<!-- prettier-ignore-start -->
!!! danger "The only tricky part in declaring `getFcn` is to remember that when we apply `decltype `to a function, it returns a function type, not a pointer to function type. We must add a `*` to indicate that we are **returning a pointer, not a function**."
<!-- prettier-ignore-end -->

### Chapter 7 Classes

## Part II: The C++ Library

### Chapter 8 The IO Library

### Chapter 9 Sequential Containers

### Chapter 10 Generic Algorithms

### Chapter 11 Associative Containers

### Chapter 12 Dynamic Memory

## Part III: Tools for Class Authors

### Chapter 13 Copy Control

### Chapter 14 Overloaded Operations and Conversions

### Chapter 15 Object-Oriented Programming

### Chapter 16 Templates and Generic Programming

## Part IV:  Advanced Topics

### Chapter 17 Specialized Library Facilities

### Chapter 18 Tools for Large Programs

### Chapter 19 Specialized Tools and Techniques
