# 并行程序设计导论

An Introduction to Parallel Programming

## Ch1. Why Parallel Programming?

This chapter mainly describes the reasons for parallel programming, the development of parallel programming, and the basic concepts of parallel programming.

- Rather than building ever-faster, more complex, monolithic processors, the industry has decided to put **multiple, relatively simple, complete processors on a single chip**. Such integrated circuits are called **multicore processors**, and core has become synonymous with central processing unit, or CPU.

<!-- prettier-ignore-start -->
!!! example "Compute n values and add them together"
    
    Method 1:

    - I have $p$ cores, so I will divide the work into $p$ pieces. Each core can form a partial sum of approximately $n/p$ values.
    - They send their partial sums to a single core, which adds them together.

    Method 2:

    - Instead of making the master core do all the work of computing the final sum, we can pair the cores so that while core 0 adds in the result of core 1, core 2 can add in the result of core 3, core 4 can add in the result of core 5 and so on.
    
    Compare:

    - When $n$ is large, method 2 is better. The first method require 999 receives and adds, while the second method requires only 10.

<!-- prettier-ignore-end -->

- Two approaches to parallel programming: 
    - Task-parallelism
    - Data-parallelism
    - Explanaition: The first part of global sum example is task-parallelism, each core carries out roughtly the same oprations on its assigned elements. And the second part is data-parallelism, receiving and adding the cores' partial sums.

**Writing actual code for parallel programs is relatively complex.**

- **Communication**: cores communicate with each other.
- **Load balancing**: the work is divided evenly among the cores.
- **Synchronization**: cores must **wait** for each other at certain points in the program.

Things we will learn:

- Three different extensions to C:
    - OpenMP
    - MPI
    - Pthreads
- Two main types of parallel systems:
    - Shared-memory systems
        - cores can share access to the computer’s memory
    - Distributed-memory systems
        - each core has its own, private memory, and the cores must communicate explicitly by doing something like sending messages across a network
    - Pthreads and OpenMP were designed for programming shared-memory systems. They provide mechanisms for accessing shared-memory locations. MPI, on the other hand, was designed for programming distributed-memory systems. It provides mechanisms for sending messages.

And we distinguish between three terms:

- **Concurrent**: a program is one in which multiple tasks can be in progress
at any instant.
- **Parallel**: a program is one in which multiple tasks cooperate closely
to solve a problem.
- **Distributed**: a program may need to cooperate with other programs
to solve a problem.

<!-- prettier-ignore-start -->
!!! tip "A Word of Warning"
    
    It may be tempting to write parallel programs “by the seat of your pants,” without taking the trouble to carefully design and incrementally develop your program. This will almost certainly be a mistake.

    Every parallel program contains at least one serial program. Since we almost always need to coordinate the actions of multiple cores, writing parallel programs is almost always more complex than writing a serial program that solves the same problem. In fact, it is often far more complex. All the rules about careful design and development are usually far more important for the writing of parallel programs than they are for serial programs.
<!-- prettier-ignore-end -->



