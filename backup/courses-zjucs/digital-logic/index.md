# 数字逻辑设计

<!-- prettier-ignore-start -->
!!! abstract "课程信息"

    - 时间：2023-2024 学年 秋冬学期
    - 授课教师：马德
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
!!! info "其他学长的笔记"

    - [Isshiki修：数字逻辑设计](https://note.isshikih.top/cour_note/D2QD_DigitalDesign/)
    - [Hobbitqia：计算机逻辑设计基础](https://note.hobbitqia.cc/Logic/)
    - [鹤翔万里：计算机系统I](https://note.tonycrane.cc/cs/system/cs1/)
<!-- prettier-ignore-end -->

## 课堂简录

### 2023.09.18 第一讲

第一讲老师特意放慢上课节奏，有很多闲聊，讲的新东西不多。

第一节课串讲了整个计算机系统课的概论，总之就是说明数逻是计算机组成、计算机体系结构等课程的基础，这些课程的关系和大概内容。说明了我们课程的目标：掌握基本逻辑电路的设计。

第二、三节课，讲一些计算机结构的基本概念和数字信号、数字系统。要全部记下来，量还是比较大的。但其实这些只要做了解就好。

> 一些新东西：
>
> - BCD 码：我的理解，就是仅仅把十进制系统中的符号集合换掉了而已。它的优点是直观，易于与人类交互。它的运算也很有趣。

额外提一句，如果上过《控制论》这门课程，那么对数字逻辑设计的背景会有更多的了解。个人觉得《控制论》作为一门通识核心课程，非常适合作为这些硬件课的前置。

要回顾 PPT 记一下陌生的单词。

#### 实验课：基本仪器使用

万用表、示波器的使用。

### 2023.09.25 第二讲

继续讲编码：

> 10 个数字的八千种编码方法：课上列出了 Excess3、Gray、84-2-1 等编码方式。其中，Excess3、84-2-1 等编码方式的特点是 0 1 出现的概率相等，难以破译。Gray 码的特点是相邻数只有一位不同，在远距离传输时可以保证稳定性。它们的优越性不止这些。

ASCII 码中，大小写只需要反转第 5 位。

#### 奇偶校验（Parity Check）

奇偶校验是一种简单的错误检测方法。奇偶校验的原理是：在传输的数据中加入一个校验位，使得传输的数据中 1 的个数为奇数或者偶数。这样，接收方就可以根据接收到的数据中 1 的个数来判断数据是否出错。

#### 布尔代数

基本内容，各种定理。表达式的化简和证明。

#### 实验课：门电路

本次实验课就和课堂有一点脱节了。课堂还在讲布尔表达式，实验课就直接搭门电路了。就是课上硬件基本不讲，实验直接开始做。

使用二极管制作了多通道与门、或门，用三极管制作或门。三极管是相对陌生的，需要知道怎么用万用表的 HFE 档。