# QLDPC

在课程中，我们选择的课题是 *Decoding Quantum LDPC*。本文档记录过程中学习到的相关知识。

## 编码理论与经典 LDPC

## QECC 基础

[https://www.youtube.com/watch?v=MqGBwQjS4CI](Introduction to qLDPC Codes)

### 量子纠错的基本操作

- 我们有 $k$ 个量子比特的信息要传递，这是逻辑量子比特。
- 用 $n$ 个物理量子比特编码它。
- 传输过程中，其中至多 $d$ 个物理量子比特发生了错误。
- 测量其中的 stabilizer，得到 syndromes。
- 根据特定的编码方式，可以根据 syndromes 进行纠错，解码还原得到 $k$ 个原始的逻辑量子比特。

注意上面过程中的三个关键参数：$[k, n, d]$，它们衡量了一个 QECC 的性能。

> 此外还有其他考量。比如 Locality，指的是 stabelizer 之间的距离。如果要在硬件上实现解码器，应当尽量减小需要测量的量子比特之间的距离，这样电路设计更简单。在我们不关心这些。

### Repetition Code

[Lecture 16: Quantum error correction](https://cs.uwaterloo.ca/~watrous/QC-notes/QC-notes.16.pdf)

### Stabilizer Codes

[A Short Introduction to Stabilizer Codes](https://people.engr.tamu.edu/andreas-klappenecker/689/stabilizer.pdf)

其中的一些关键知识：

- 错误的权重（weight）：发生错误的量子比特的个数。如果一种编码能够纠正权重为 $t$ 的错误，那么它就能纠正影响 $t$ 个以内量子比特的任意错误。
- Stabilizer：如果将它作用在编码空间中的态上，不会改变态的性质。也就是说，如果发生了错误，码跳出了编码空间，那么测量 stabilizer 就会得到非平凡的结果。
- 对易：错误 $E$ 与 stabilizer $S$ 要么对易 $ES = SE$，要么不对易 $EF = -FE$。
    - 如果错误 $E$ 与 stabilizer $S$ 对易，那么 $S$ 的测量结果不会改变。
    - 如果错误 $E$ 与 stabilizer $S$ 不对易，那么 $S$ 的测量结果会改变。错误 $E$ 可以被改编码检测到。$P_QEP_Q =P_QEMP_Q= P_QMEP_Q= P_QEP_Q$，因此 $P_QEP_Q = 0$。
- 错误的分类：不影响信息（Good），可被检测（Detectable），不可检测（Ugly）。

### CSS Codes

### Toric/Surface Code

### Hypergraph Product Codes

通过 Hypergraph Product，我们可以用渐近良好的经典码构造出渐近良好的量子码。

## Expander LP Codes
