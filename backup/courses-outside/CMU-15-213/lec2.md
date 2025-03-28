---
tags:
  - Ongoing
---

# Lecture 02: Bits, Bytes, and Ints; Floating Point

把讲计算机算数的三节课合在一个笔记了。

## 第一节课

- 位、信息、进制
- 简单布尔代数
- **C 中的位运算、位移运算**
    - 仅用于整数类型
    - 位移量 <0 或 > 字长时行为是未定义的

### 整数编码

- 无符号数和补码数值的计算
- 表示范围
- `<limits.h>` 的简单使用
- **类型转换 cast**
    - cast 时保持位模式不变，重新解释。
    - 写出 T2U 与 U2T 的函数表达式。
    - 常量默认有符号，`U` 后缀无符号。
    - **表达式求值时，若有/无符号数混杂，有符号数隐式转换为无符号数。**
- **位扩展 extension**
    - 有符号数扩展
    - 无符号数扩展