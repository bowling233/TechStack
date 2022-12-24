# C Operator

## C Operator Precedence

> [cppreference](https://en.cppreference.com/w/c/language/operator_precedence)

??? note "Things you should remember!"
    
    * First: suffix, access
    * Second: unary, dereference, prefix
        * They are naturally right to left.
    * Third: Math
        * Where is remainder?
    * Forth: shift
    * Relation, equality, then inequality
    * Bitwise (AND, XOR, then OR)
    * Logic: AND, then OR
    * Ternary conditional
    * Assignment
    * Comma

* The expression in the middle of the conditional operator (between `？` and `:`) is parsed **as if parenthesized**: its precedence relative to `?:` is ignored.
* unary prefix operators always associate right-to-left, unary postfix operators always associate left-to-right

## Dereference and Increment

!!! note
    Always remember the suffix increment operator first USE the value, THEN increse the value.

Common Puzzle:

```C
*p++;//NOTE HERE
(*p)++;
++*p;
*++p;
```
