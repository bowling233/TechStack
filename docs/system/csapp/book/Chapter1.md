# Ch1. 计算机系统漫游

<!-- prettier-ignore-start -->
!!! abstract
    
    本章快速过了一遍本书将要学习的内容，建立了几个基本概念。

    **初次阅读时不理解没关系，也不需要死记硬背，本章内容都会在书中一一展开**。
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
!!! note "Amdahl 定律"
    
    当我们对系统的某个部分加速时，其对系统整体性能的影响取决于该部分的重要性和加速程度：

    $$
    S=\frac1{(1-\alpha)+\alpha/k}
    $$

    其中 $S$ 是加速前后的时间比，$\alpha$ 是所加速部分占系统时间比，$k$ 是该部分性能提升比例。
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
!!! note "并发和并行"
    
    书本定义：

    - 并发（concurrency）指同时具有多个活动。
    - 并行（parallelism）指使用并发使系统运行得更快。

    更易懂的解释：
    > -   并行：两个任务在**同一时刻互不干扰**的同时执行。
    > -   并发：同时安排若干个任务，这些任务可以彼此穿插着进行；有些任务可能是并行的，比如买菜、发邮件和去幼儿园的某些路途是重叠的，这时你的确同时在做三件事；但进菜市场和发邮件和接娃三者是互斥的，每个时刻只能完成其中一件。换句话说，并发允许两个任务彼此干扰。
    > 串行还是并发，这都是**任务安排者**视角看到的东西。相比之下，“并行”是**任务执行者**视角的东西。
<!-- prettier-ignore-end -->

简单了解三个层次的并发：

- 线程级并发

<!-- prettier-ignore-start -->
!!! note "线程、进程"
    
    - 进程：一个在操作系统上运行的程序
        - 一个操作系统运行多个进程。
        - 每个进程看上去是独占地使用处理器、主存和 I/O 设备。
        - 使用*并发*运行，不同进程的指令可以交错进行。这是通过**上下文切换**实现的。
    - 线程：现代操作系统中，进程由多个线程组成。
        - 每个线程都运行在进程的上下文中，**共享代码和全局数据**。
        - 在网络服务中，线程能高效满足并行处理要求。
        - 在**多处理器**可用时，线程能极大提升程序的效率。
    - 超线程：又称同时多线程，指 CPU 执行多个控制流。
        - 实现原理是 CPU 的某些硬件有多个备份，比如程序计数器和寄存器。

<!-- prettier-ignore-end -->