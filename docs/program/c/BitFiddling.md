## Chapter 15 Bit Fiddling

-   Operators: `~ & | ^ << >> &= |= ^= >>= <<=`
-   Two C facilities for handling the individual bits: bitwise operators and bit fields
-   Keywords: `_Alignas, _Alignof`

### 15.1 Binary Numbers, Bits, and Bytes

#### Binary Integers

-   a **byte** contains 8 bits
-   C uses **byte** to denote the size used to hold a system's character set, it could be 8 bits, 9 bits ...
-   8-bit byte is called **octet**: **describe memory chips and data transfer rates**
-   bits are numbered from **7 ~ 0, left to right** ,**bit 7** is called the **high-order bit**
-   **magnitude**: 绝对值

#### Signed Integers

-   two's-completement

#### Binary Floating Point

-   **fraction**: 小数

### 15.2 Other Number Bases

#### Octal

-   each octal digit corresponds to **three binary digits**
-   Note: the internal 0s are not dropped
-   `0876`

#### Hexadecimal

-   In C you can use **either lowercase or uppercase letters for the additional hex digits**
-   `0x3F`
-   hexadecimal is a natural choice for **representing byte values**
-   remember: **A = `1010` = 10, C = `1100` = 12, F = `1111` = 15, **

### 15.3 C's Bitwise Operators

#### Bitwise Logical Operators

-   work on **integer-type data**
-   `~`: one's complement or **Bitwise Negation**
-   **NOTICE**: there is no `~=` operator
-   `&`: **Bitwise AND**
-   `&=`
-   `|`: **Bitwise OR**
-   `|=`
-   `^`: **Bitwise EXCLUSIVE OR**: but not both
-   `^=`

#### Usage: Masks

Bitwise AND

#### Usage: Turning Bits On (Setting Bits)

#### Usage: Turning Bits Off (Clearing Bits)

`flags = flags & ~MASK`: the `mask` indicates the bits needed to be toggled

#### Usage: Toggling Bits

#### Usage: Checking the Value of a Bit

-   first mask the other bits in flags: `(flags & MASK) == MASK`
-   **NOTICE:** `bitwise` operators have lower precedence than `==`
-   **NOTICE:** a mask should be at least as wide as the value it's masking

#### Bitwise Shift Operators

-   `A << B`: shifts A to the left by B and fill 0s
-   `<<=`
-   `A >> B`: for _unsigned_ integers, fill 0s. for _signed_ integers, the result is machine dependent
-   `>>=`
-   **NOTICE:** shift operators do not change the value of the variables
-   Usage
    -   multiplication and division by powers of 2 (if number is not negative)
    -   **extract groups of bits** from larger units (e.p. use unsigned long value to represent color)
    -

#### Programming Example

-   `CHAR_BIT * sizeof(int)`: remember `sizeof` operator return the size **in bytes**

#### Another Example

-   Summary: **try to think on the basis of directly operating the bits of data**

### 15.4 Bit Fields (位字段)

-   **NOTICE:** bit fields tend **not to be very portable**, but are used for nonportable purposes such as **putting data in the exact form used by a particular hardware device**
-

#### Bit-field Example

#### Bit Fields and Bitwise Operators

### Alignment Features (C11)
