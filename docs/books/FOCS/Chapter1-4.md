---
tags:
  - Ongoing
---

# Ch. 1-4 Intro, Number, Data and Operation

These contents are closely related, so I put them together in one note.

<!-- prettier-ignore-start -->
!!! abstract
    
    Main Topic are these:

    - Model of computer
    - Outline for this book
    - Storing Data
    - Data Operation
<!-- prettier-ignore-end -->

## Ch1. Introduction

### Turing Model

**Turing model** is a mathematical and philosophical definition of computation. We only care about the philosophical definition here.

He defined these things: 

- Data processor: accepts input data, process the data, and creates output data.
- Program: a set of instructions that tells the computer what to do with data.

<!-- prettier-ignore-start -->
!!! info

    Turing's thesis can be found here: [On Computable Numbers，with an Application to the Entscheidungsproblem](https://www.cs.virginia.edu/~robins/Turing_Paper_1936.pdf)

    In the thesis, he presented a mathematical description of the **universal Turing machine** than can perform all computation.

    A Chinese explanation can be found here: [《论可计算数及其在判定上的应用》简单理解](https://cloud.tencent.com/developer/article/1762927)
<!-- prettier-ignore-end -->

### Von Neumann Model

Today's computers are based on the **von Neumann model**. The main difference bewtween Turing model and von Neumann model is that while Turing model stores data in its memory, von Neumann model also stores programs in its memory.

The von Neumann model consists of four subsystem:

- Input/Output
- Arithmetic logic unit (ALU): calculation and **logical operations** take place
- Memory
- Control Unit: controls all other subsystem

Main concepts:

- Programs and data are stored in memory as **binary patterns**.
- Sequential execution of instructions.

### Computer Componenets

This section briefly describes the three parts of computer: **hardware, software and data**. Please refer to the book.

### History

Ignored.

### Outline of the course

As described in the [index note](index.md).

## Ch2. Number Systems

In this chapter your main task is to understand the binary, hexadecimal and octal systems, and know how to convert number from one system to another.

### Any base to decimal conversion

Simply multiply each digit with its place value in the source system and add the results to get the number.

### Decimal to any base

Integral part and fractional part are handled differently.

- Integral part
    - Repetitively divide the source to get the quotient and the remainder.
    - **The remainder** is inserted to the **left** of the destination.
    - Until quotient is zero.
- Fractional part
    - Repetitively multiply the source to get the result.
    - **The intergral part** is inserted to the **right** of the destination.
    - Until fractional part is zero or destination digits are enough.

<!-- prettier-ignore-start -->
!!! question "Number of digits"
    
    Given a positional number system with base $b$, find the number of digits of an integer N.

    ??? note
        
        The answer is $\left \lceil \log_b{N} \right \rceil$.

    If we are using $K$ digits in base $b_1$, we need to know the minimum number of digits $x$ we need in the destination system with base $b_2$.

    ??? note
        
        The answer is $\left \lceil K \times (\log_{b_2}b_1) \right \rceil$.

<!-- prettier-ignore-end -->

### Nonpositional number systems

Ignored.

## Ch3. Data Storage

### Storing Numbers

#### Integers

For representations below, you need to know: how to store, retrieve numbers, overflow situation, application.

- Unsigned representation
- Sign-and-magnitude representation
- Two's complement representation

#### Reals

We use **floating-point representation** to represent reals. It consists of three parts:

- Sign
- Shifter
- Fixed-point number

<!-- prettier-ignore-start -->
!!! tip
    
    You can compare **scientific method** with floating-point method.
<!-- prettier-ignore-end -->

Normalization: 

- Decimal: `d.xxxxx`, d is 1-9 while x is 0-9.
- Binary: `1.yyyyy`, y is 0 or 1.

Then extract three pieces of information:

- Sign
- Exponent
- Mantissa (尾数): the point and bit 1 to the left of the fixed-point section are not stored.

The exponent can be positive and negative. We use **Excess system** to represent:

- Add a **bias** to shift positive or negative numbers uniformly to the nonnegative side.
- The value of this bias is $2^{m-1}-1$, $m$ is the size of the memory location to store the exponent.









