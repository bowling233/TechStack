# Storage Classes, Liknage and Memory Management

-   Keywords:
    -   `auto, extern, static, register, const, volatile, restricted`
    -   `_Thread_local, _Atomic`
-   Functions
    -   `rand, srand, time`
    -   `malloc, calloc, free`
-   scope, life time

### 12.1 Storage Classes

Here are some basic concepts:

-   All data is stored in memory. **Object** is the term used to describe such _chunk of memory_
-   **Identifier:** a name used to designate the contents of a object
-   **lvalue:** an expression that designates and object

We can describe an object in terms of its storage duration, identifier by its **scope and linkage**

**Scope:** the region of a program that can access an identifier

-   block scope

    -   the code controlled by a **for, while, do while** loop or **if** statement

        -   Two parts: **control section, loop body**. They are nested.

    -   ```C
        for(int i = 1;i < 0;i++)//outside i in efect, so the judgement is based on outside i
        {
            int i = 0;//inside i in effect
        }//inside i disappear
        ```

-   function scope
    -   **labels** used with `goto` statements
    -   **NOTICE:** even if a label appears inside an **inner** block in a function, its scope extends to the **whole** function
-   function prototype scope
    -   variable **names** used in function prototypes
    -   only runs from the definition to the end of the prototype
    -   is all the compiler cares about when handling a function
    -   **needn't** match the name used in function definition (except for variable-length array parameters `int n, int m, ar[n][m]`)
-   file scope
    -   variable with its definition placed **outside of any function**

> Translation Units:
>
> -   What **you view as several files** may appear to the compiler as a **single file**
> -   e.g.`#include` inform **C preprocessing** to insert the header file, this single file is called a **translation unit**
> -   file scope actually means visible the **translation unit**

**Linkage:** only variable with file scope can have linkage

-   internal linkage: can be used anywhere in a single translation unit
    -   Keyword: `static`
-   external linkage: anywhere in a multifile program

> Formal Terms:
>
> -   file scope with external/internal linkage

**Storage Duration:**

-   static storage duration
    -   exits **throughout program execution**
    -   for **file scope** variables
    -   for **block scope** with `static`
-   thread storage duration
    -   exits **from declaration until the thread terminates**
    -   Keyword: `_Thread_local` modified variable that defined outside any function, each thread gets its own **private copy of the variable**
-   automatic storage duration
    -   for **block scope** normally
    -   have memory allocated for them when **entering the block** (except for VLA, from its **definition**) and space freed when **exiting the block**
    -   these memory can be **reused**
-   allocated storage duration

Five **Storage Classes**

-   **automatic:** in a block
    -   automatic, block, none
    -   can use **storage-class specifier** `auto`, buy not compatible with C++, so **DO NOT USE**
-   **register:** in a block with `register`
    -   automatic, block, none
    -   **NOTICE:** CANNOT take the address of a register variable
    -   types that can be declared register may be restricted
-   **static with external linkage:** outside of all functions
    -   static, file, external
    -   declaring the variable in the second file with extern is **mandatory**
-   **static with internal linkage:** outside of all functions with `static`
    -   static, file, internal
-   **static with no linkage:** in a block with `static`
    -   static, block, none
    -   **initialized** only once
    -   the declaration **actually isn't part of the function**
    -   can't use formal parameter as static
    -

### 12.2 A Random-Number Function and a Static Varibale

### 12.3 Roll 'Em

### 12.4 Allocated Memory: `malloc()` and `free()`

`void *malloc( size_t size )`

-   size: the number of **bytes** of memory you want
-   the return value is **typecast** to the proper value
-   returns the null pointer if fails to find the required memory
-   e.g.`double * ptd = (double *) malloc(30 * sizeof(double))`

`void free( void *ptr )`

`void *calloc( size_t num, size_t size )`

-   sets all the bits in the block to **zero**
-

### 12.5 ANSI C Type Qualifiers
