# 并行程序设计导论

An Introduction to Parallel Programming

## Ch1. Why Parallel Programming?

This chapter mainly describes the reasons for parallel programming, the development of parallel programming, and the basic concepts of parallel programming.

-   Rather than building ever-faster, more complex, monolithic processors, the industry has decided to put **multiple, relatively simple, complete processors on a single chip**. Such integrated circuits are called **multicore processors**, and core has become synonymous with central processing unit, or CPU.

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

-   Two approaches to parallel programming:
    -   Task-parallelism
    -   Data-parallelism
    -   Explanaition: The first part of global sum example is task-parallelism, each core carries out roughtly the same oprations on its assigned elements. And the second part is data-parallelism, receiving and adding the cores' partial sums.

**Writing actual code for parallel programs is relatively complex.**

-   **Communication**: cores communicate with each other.
-   **Load balancing**: the work is divided evenly among the cores.
-   **Synchronization**: cores must **wait** for each other at certain points in the program.

Things we will learn:

-   Three different extensions to C:
    -   OpenMP
    -   MPI
    -   Pthreads
-   Two main types of parallel systems:
    -   Shared-memory systems
        -   cores can share access to the computer’s memory
    -   Distributed-memory systems
        -   each core has its own, private memory, and the cores must communicate explicitly by doing something like sending messages across a network
    -   Pthreads and OpenMP were designed for programming shared-memory systems. They provide mechanisms for accessing shared-memory locations. MPI, on the other hand, was designed for programming distributed-memory systems. It provides mechanisms for sending messages.

And we distinguish between three terms:

-   **Concurrent**: a program is one in which multiple tasks can be in progress
    at any instant.
-   **Parallel**: a program is one in which multiple tasks cooperate closely
    to solve a problem.
-   **Distributed**: a program may need to cooperate with other programs
    to solve a problem.

<!-- prettier-ignore-start -->
!!! tip "A Word of Warning"
    
    It may be tempting to write parallel programs “by the seat of your pants,” without taking the trouble to carefully design and incrementally develop your program. This will almost certainly be a mistake.

    Every parallel program contains at least one serial program. Since we almost always need to coordinate the actions of multiple cores, writing parallel programs is almost always more complex than writing a serial program that solves the same problem. In fact, it is often far more complex. All the rules about careful design and development are usually far more important for the writing of parallel programs than they are for serial programs.
<!-- prettier-ignore-end -->

### Exercise Answers

<!-- prettier-ignore-start -->
??? question "1.3 Global sum"

    variables:

    - `core_nums`: number of cores
    - `core_index`: index of core
    - `divisor`: determine whether to send or receive data
    - `core_difference`: determine which core to cooperate with

    | round | send core | receive core | divisor | core_difference |
    | - | - | - | - | - |
    | 1 | 1 = 0 + 1 | 0 = 0 * 2 | 2 | 1 |
    | 2 | 2 = 0 + 2 | 0 = 0 * 4 | 4 | 2 |
    | 3 | 4 = 0 + 4 | 0 = 0 * 8 | 8 | 4 |

    ```title="pseduocode"
    while divisor != core_num
    {
        if(!core_index % divisor)
            receive data from core_index + core_difference
            sum together
        else
            send data to core_index - core_difference
        divisor *= 2
        core_difference *= 2
    }
    ```
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
??? question "1.4 Bitmask implementation"

    ```title="pseduocode"
    while bitmask != core_num
    {
        if(!core_index % bitmask)
            receive data from core_index ^ bitmask
            sum together
        else
            send data to core_index ^ bitmask
        bitmask << 1
    }
    ```
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
??? question "1.5 Odd cores"

    Only need to modify condition of `while` loop and check number before receive data.

    === "divisor version"
        ```title="pseduocode"
        while true
        {
            if(!core_index % divisor)
                receive data from core_index + core_difference
                sum together
            else
                send data to core_index - core_difference


            if(divisor >= core_num) break;
            divisor *= 2
            core_difference *= 2
        }
        ```
    === "bitmask version"
        ```title="pseduocode"
        while true
        {
            if(!core_index % bitmask)
                receive data from core_index ^ bitmask
                sum together
            else
                send data to core_index ^ bitmask
            if(bitmask >= core_num)
            bitmask << 1
        }
        ```
<!-- prettier-ignore-end -->

## Ch2. Parallel Hardware and Parallel Software

<!-- prettier-ignore-start -->
!!! tip "First time read"

    I skipped these contents when I read this chapter for the first time:

    - Modifications to the von Neumann Model
    - SIMD Systems
    - Interconnection Networks

    Notes for these contents can be seen in CSAPP.
<!-- prettier-ignore-end -->

### 2.1 Background

-   von Neumann architecture
    -   What's the **von Neumann bottleneck**?
-   Concepts of processes, multitasking, and threads
    -   From the perspective of the operating system, a process contains of what?
        -   Executable code, block of memory (what's in it?), descriptor, security information, state.
    -   Some terminology: block, fork, join

### 2.2 Modifications to the von Neumann Model

-   Caching (CPU Cache)
    -   Terminology:
        -   spatial locality, temporal locality
        -   cache miss
        -   write-through, write-back
    -   In which way will data be cached?
    -   When CPU needs access to some data, how will it work?
    -   What causes the **inconsistency** between cache and main memory?

### 2.3 Parallel Hardware

-   MIMD system

    -   They are **asynchronous**.
    -   Shared-memory system:
        -   communicate by accessing shared data structure
        -   **interconnect** connect all the processors to main memory or a block of memory
        -   Uniform Memory Access, Nonuniform Memory Access
    -   Distributed-memory system:
        -   communicate by sending messages or special functions that provide access to the memory of another processor

-   Interconnection

(Skipped, but remember to read back again.)

-   Cache coherence
    -   Why cache inconsistency happens both in write-through and write-back policy?

## Ch3. Distributed-Memory Programming with MPI

-   What is MPI? What do we use it for?

### 3.1 Getting Started

<!-- prettier-ignore-start -->
!!! tip "Configuring Environment"

    Refer to HPC-101 Lab 1. Notes are [here](../courses-zjucs/hpc101/lab1.md).
<!-- prettier-ignore-end -->

-   Some concepts:

    -   **communicator**: a group of processes that can communicate with each other. All MPI function that involve communication have a communicator argument.
    -   **collective communication**: a communication that involves all processes in a communicator
    -   **butterfly**: a communication pattern, reverse the branches to distribute data
    -   **broadcast**: data belonging to a single process is sent to all of the processes in the communicator

-   Basic Structure of MPI program:

```c title="Basic Structure of MPI program"
#include <mpi.h>
int main(int argc, char *argv[])
{
    int my_rank, p;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    /* do some work */
    MPI_Finalize();
    return 0;
}
```

-   Basic Commands for MPI Programs:
    -   `mpicc`: compile MPI programs
        -   a wrapper for `gcc`
    -   `mpiexec` and `mpirun`: run MPI programs (they are synonyms to each other)
        -   `-n <num>`: specify the number of processes
        -   `--hostfile <filename>`: specify the hostfile
        -   More on [Open MPI documentation](https://docs.open-mpi.org/en/v5.0.x/man-openmpi/man1/mpirun.1.html)

<!-- prettier-ignore-start -->
??? tip "Tools for clusters"

    -   `scp`: tools for transferring files
        -   `-r`: recursive (copy directory with multiple files)
        -   `-P`: port

    Example:

    ```bash
    scp [other options] [source username@IP]:/[directory and file name] [destination username@IP]:/[destination directory]
    scp /users/Hostinger/desktop/scp.zip root@191.162.0.2:/writing/article
    scp -r /users/Hostinger/desktop root@191.162.0.2:/writing/article
    ```

    I also wrote a Python script to send files to clusters:

    ```python title="send_file.sh"
    #!/usr/bin/env python3
    import sys
    import os

    for i in range(3, len(sys.argv)):
        os.system("scp " + sys.argv[1] + " " + sys.argv[i] + ":" + sys.argv[2])
    ```

    Usage:

    ```bach
    ./send_file.sh file /path/to/dest vm1 vm2 ...
    ```

<!-- prettier-ignore-end -->

-   Ref to functions:

```c title="must include"
int MPI_Init(
    int *argc_p /* in/out */,
    char ***argv /* in/out */);
int MPI_Finalize(void);
```

`MPI_Init` defines a communicator called `MPI_COMM_WORLD` that contains all the processes started by the user.

```c title="about communicator"
int MPI_Comm_size(
    MPI_Comm comm /* in */,
    int *comm_sz_p /* out */);
int MPI_Comm_rank(
    MPI_Comm comm /* in */,
    int *my_rank_p /* out */);
```

The two function is getting information about `MPI_COMM_WORLD`.

```c title="send and receive"
int MPI_Send(
    void *buf /* in，points to the data to be sent */,
    int count /* in, number of objects */,
    MPI_Datatype datatype /* in, type of objects, correspond to C basic data type */,
    int dest /* in, the rank of the process that receive the message */,
    int tag /* in, distinguish messages that are otherwise identical */,
    MPI_Comm comm /* in */);
int MPI_Recv(
    void *buf /* out */,
    int count /* in */,
    MPI_Datatype datatype /* in */,
    int source /* in, MPI_ANY_SOURCE can be used */,
    int tag /* in, MPI_ANY_TAG can be used */,
    MPI_Comm comm /* in */,
    MPI_Status *status /* out, usually won't use, just pass MPI_STATUS_IGNORE */);
int MPI_Get_count(
    MPI_Status* status_p /* in */,
    MPI_Datatype type /* in */,
    int * count_p /* out */);
```

<!-- prettier-ignore-start -->
!!! warning "About wildcard arguments"

    - ONLY ONE RECIVER can use a wildcard argument.
<!-- prettier-ignore-end -->

-   `status_p` argument
    -   `MPI_Status` is a struct with at least three members: `MPI_SOURCE`, `MPI_TAG`, `MPI_ERROR`.
    -   We can determine the sender by `MPI_SOURCE` and `MPI_TAG`.
-   `MPI_Get_count()` is used to get the amount of data that's been received.

<!-- prettier-ignore-start -->
!!! warning "HANG"

    If a process tries to receive a message and there's no matching send, then the process will block forever. If send don't match, it will block too.
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
!!! note "What happens when you send message?"

    - Sending process assemble the message with information about the destination process, tag, size and etc.
    - Two ways to send messages: **buffer** and **block**.
    - Buffer: place the message into its own internal storage, and **the call will return**.
    - Block: wait until it can begin transmitting the message.
    - So, **when function returns, we don't know whether the message has been transmitted, only know that the storage for the message (buffer) is available for reuse**.
    - Typical implementations have default "cutoff" message size. If less, it will buffer, or it will block.
    - Messages from one process are **nonovertaking**.
<!-- prettier-ignore-end -->

### 3.4 Collective Communication

```c title="collective communication"
int MPI_Reduce( // reduce data from all processes to one process
    void *input_data_p /* in */,
    void *output_data_p /* out */,
    int count /* in */,
    MPI_Datatype datatype /* in */,
    MPI_Op operator /* in */,
    int dest_process /* in */,
    MPI_Comm comm /* in */);
int MPI_Allreduce( // reduce data from all processes to all processes
    void *input_data_p /* in */,
    void *output_data_p /* out */,
    int count /* in */,
    MPI_Datatype datatype /* in */,
    MPI_Op operator /* in */,
    MPI_Comm comm /* in */);
int MPI_Bcast( // broadcast data from one process to all processes
    void *data_p /* in/out */,
    int count /* in */,
    MPI_Datatype datatype /* in */,
    int source_proc /* in */,
    MPI_Comm comm /* in */);

int MPI_Scatter( // scatter data from one process to all processes
    void *send_buf_p /* in */,
    int send_count /* in, NOTICE HERE counts for the amount of data going to each process */,
    MPI_Datatype send_type /* in */,
    void *recv_buf_p /* out */,
    int recv_count /* in */,
    MPI_Datatype recv_type /* in */,
    int src_proc /* in */,
    MPI_Comm comm /* in */);
int MPI_Gather( // gather data from all processes to one process
    void *send_buf_p /* in */,
    int send_count /* in */,
    MPI_Datatype send_type /* in */,
    void *recv_buf_p /* out */,
    int recv_count /* in, NOTICE HERE counts for the number of data items received from each process */,
    MPI_Datatype recv_type /* in */,
    int dest_proc /* in */,
    MPI_Comm comm /* in */);
int MPI_Allgather( // gather data from all processes to all processes
    void *send_buf_p /* in */,
    int send_count /* in */,
    MPI_Datatype send_type /* in */,
    void *recv_buf_p /* out */,
    int recv_count /* in */,
    MPI_Datatype recv_type /* in */,
    MPI_Comm comm /* in */);
```

-   Key is the fifth argument `operator`.
    -   Find: `MPI_MAX`, `MPI_MIN`, `MPI_MAXLOC`, `MPI_MINLOC`
    -   Compute: `MPI_SUM`, `MPI_PROD`
    -   Bitwise: `MPI_BAND`, `MPI_BOR`, `MPI_BXOR`
    -   Logical: `MPI_LAND`, `MPI_LOR`, `MPI_LXOR`
    -   You can define yourself.
-   Difference between `MPI_Reduce` and `MPI_Allreduce`: `MPI_Reduce` have `dest_process` argument, and `MPI_Allreduce` doesn't.

<!-- prettier-ignore-start -->
!!! tip "Read the example"

    Please read the example `vector.c` and make sure you understand each line of code.
<!-- prettier-ignore-end -->

### 3.5 MPI Derived Datatypes

-   To improve the performance of our program, we can reduce the total number of messages sent.
-   A derived datatype consists of a sequence of basic MPI datatypes together with a displacement for each of the datatypes.

```
{(MPI_DOUBLE, 0), (MPI_DOUBLE, 16), (MPI_INT, 24)}
```

-   To create a derived datatype, we need to use `MPI_Type_create_struct()`.

```c title="create derived datatype"
int MPI_Type_create_struct(
    int count /* in, number of elements */,
    int array_of_blocklengths[] /* in, individual data items might be arrays or subarrays */,
    MPI_Aint array_of_displacements[] /* in, displacement of each elements */,
    MPI_Datatype array_of_types[] /* in, type of each block */,
    MPI_Datatype *new_type_p /* out */);
int MPI_Type_commit(
    MPI_Datatype *new_mpi_t_p /* in/out */);
int MPI_Type_free(
    MPI_Datatype *old_mpi_t_p /* in/out */);
```

-   `MPI_Aint` is big enough to store any address on the system.
-   In our example, the call is:

```c
MPI_Type_create_struct(3, {1, 1, 1}, {0, 16, 24}, {MPI_DOUBLE, MPI_DOUBLE, MPI_INT}, &new_type);
```

-   To find displacement of a variable, we can use `MPI_Get_address()`.

```c title="get address of a variable"
int MPI_Get_address(
    void *location_p /* in */,
    MPI_Aint *address_p /* out */);

MPI_Aint, a_addr, b_addr, n_addr;
MPI_Get_address(&a, &a_addr);
array_of_displacements[0] = 0;
MPI_Get_address(&b, &b_addr);
array_of_displacements[1] = b_addr - a_addr;
MPI_Get_address(&n, &n_addr);
array_of_displacements[2] = n_addr - a_addr;
```


Other MPI Routines:

```c
MPI_Barrier(MPI_Comm comm);
MPI_Isend();//non-blocking
MPI_Irecv();//non-blocking
MPI_Wait();//block until message is completed
```
