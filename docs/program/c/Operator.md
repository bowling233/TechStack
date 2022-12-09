## C's operator precedence

酱紫记忆：（后缀、调用、访问）>（前 缀、一元、强制转换）>二元数学>**移位**>顺序关系（小、大）>等价关系>二元位运算(与、异或、或)>二元逻辑（与、或）>三元逻辑>赋值>**逗号**

|     Precedence     | Operator           | Description                                       | Associativity     |
| :----------------: | :----------------- | :------------------------------------------------ | :---------------- |
|         1          | `++` `--`          | Suffix/postfix increment and decrement            | Left-to-right     |
|        后缀        | `()`               | Function call                                     |                   |
|        调用        | `[]`               | Array subscripting                                |                   |
| 访问（数组、结构） | `.`                | Structure and union member access                 |                   |
|     复合字面量     | `->`               | Structure and union member access through pointer |                   |
|                    | `(*type*){*list*}` | Compound literal(C99)                             |                   |
|         2          | `++` `--`          | Prefix increment and decrement                    | **Right-to-left** |
|        前缀        | `+` `-`            | **Unary plus and minus**                          | **Right-to-left** |
|      一元算符      | `!` `~`            | Logical NOT and bitwise NOT                       | **Right-to-left** |
|      强制转换      | `(*type*)`         | Cast                                              | **Right-to-left** |
|                    | `*`                | Indirection (dereference)                         | **Right-to-left** |
|                    | `&`                | Address-of                                        | **Right-to-left** |
|                    | `sizeof`           | Size-of                                           | **Right-to-left** |
|                    | `_Alignof`         | Alignment requirement(C11)                        | **Right-to-left** |
|   3二元数学运算    | `*` `/` `%`        | Multiplication, division, and remainder           | Left-to-right     |
|   4二元数学运算    | `+` `-`            | Addition and subtraction                          |                   |
|       5移位        | `<<` `>>`          | Bitwise left shift and right shift                |                   |
|     6顺序关系      | `<` `<=`           | For relational operators < and ≤ respectively     |                   |
|                    | `>` `>=`           | For relational operators > and ≥ respectively     |                   |
|     7等价关系      | `==` `!=`          | For relational = and ≠ respectively               |                   |
|    8二元位运算     | `&`                | Bitwise AND                                       |                   |
|         9          | `^`                | Bitwise XOR (exclusive or)                        |                   |
|         10         | `|`                | Bitwise OR (inclusive or)                         |                   |
|   11二元逻辑运算   | `&&`               | Logical AND                                       |                   |
|         12         | `||`               | Logical OR                                        |                   |
|   13三元逻辑运算   | `?:`               | Ternary conditional                               | **Right-to-left** |
|       14赋值       | `=`                | Simple assignment                                 | **Right-to-left** |
|                    | `+=` `-=`          | Assignment by sum and difference                  | **Right-to-left** |
|                    | `*=` `/=` `%=`     | Assignment by product, quotient, and remainder    | **Right-to-left** |
|                    | `<<=` `>>=`        | Assignment by bitwise left shift and right shift  | **Right-to-left** |
|                    | `&=` `^=` `|=`     | Assignment by bitwise AND, XOR, and OR            | **Right-to-left** |
|       15逗号       | `,`                | Comma                                             | Left-to-right     |

* The expression in the middle of the conditional operator (between `？` and `:`) is parsed **as if parenthesized**: its precedence relative to `?:` is ignored.
* unary prefix operators always associate right-to-left, unary postfix operators always associate left-to-right