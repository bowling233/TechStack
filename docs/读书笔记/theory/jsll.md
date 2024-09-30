# 计算理论

## 1.7 字母表与语言

| 中文 | 英文 | 符号 | 说明 |
| --- | --- | --- | --- |
| 字母表 | alphabet | $\Sigma$ | 有穷符号集合 |
| 字符串 | string | $w$ | 字母表中符号的有穷序列 |
| 空串 | empty string | $e$ | |
| 长度 | length | $|w|$ | |
| | | $\Sigma*$ | 字母表上所有字符串集合 |
| | exponentiation | $w^i$ | $w$ 的 $i$ 次幂 |
| 反转 | reversal | $w^R$ | |
| 字符串连接 | concatenation | $x \circ y$ 简写为 $xy$ | |
| 语言 | language | $L$ | 字符串的集合 |
| Kleene 星号 | Kleene star | $L^*$ | 连接 $L$ 中 0 或多个字符串得到的所有字符串的集合 |
| 语言连接 | concatenation | $L_1 \circ L_2$ 简写为 $L_1L_2$ | |
| | | $L^+$ | $LL^*$ |

## 1.8 语言的有穷表示

- 正则表达式的字母表：$\Sigma\cup\{ (, ), \cup, *, \emptyset \}$

## Finite Automata

- Deterministic Finite Automaton (DFA): $M = (K, \Sigma, \delta, s, F)$