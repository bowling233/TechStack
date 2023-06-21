---
tags:
    - todo
---


# 数据结构与算法

<!-- prettier-ignore-start -->
!!! abstract

    本节讲解几种基本的抽象数据类型（ADT，Abstract Data Type）和算法：
    
    -   链表
    -   栈、队列
    -   递归思想
    -   查找算法
    -   排序算法
        -   三大基础排序：选择排序、冒泡排序、插入排序
        -   快速排序
        -   归并排序
<!-- prettier-ignore-end -->

## 抽象数据类型

用一句话概括抽象数据类型（ADT，Abstract Data Type），就是它将**使用**和**实现**分离。使用 ADT 的人不需要知道这种数据类型是如何实现的，只需要知道它能做哪些操作。

<!-- prettier-ignore-start -->
!!! example "举个例子"

    字符串 `string` 就是一种 ADT。我们知道它的一些操作如 `length()`、`substr()`、`find()` 等，但是我们不需要知道它是如何实现的。`string` 可以用数组、链表等实现。
<!-- prettier-ignore-end -->

为了描述 ADT，我们使用 API（Application Programming Interface）进行表示。简单来说，API 是一组函数，它们定义了 ADT 的操作。

<!-- prettier-ignore-start -->
!!! example "举个例子"

    字符串 `string` 的 API：
    
    | 返回值 | 方法名 | 参数 | 功能 |
    | --- | --- | --- | --- |
    | `int` | `length()` | 无 | 返回字符串的长度 |
    | `string` | `substr(string str, int start, int len)` | `start`：子串的起始位置<br>`len`：子串的长度 | 返回子串 |
    | `int` | `find(string substr)` | `substr`：待查找的子串 | 返回子串在字符串中的位置 |
    
    这样的一张表就是字符串的 API。它完整地描述了字符串的使用方法，使用者只需要这张表就够了。
<!-- prettier-ignore-end -->

接下来我们使用 API 对链表、栈、队列等 ADT 进行描述，并重点关注其背后的实现细节。

### 链表

发明链表的一大目的是弥补数组插入元素的麻烦。

你可以将数组想象成一排房子，每个房子都有地址，你可以通过地址找到房子。但是如果你想在这排房子中间插入一栋新房子，你就需要将后面的房子都往后挪一位，这样的操作是很麻烦的。而链表像是一串相连的钥匙扣，**你可以通过解开两个钥匙扣之间的连接在任意位置插入一个新的钥匙扣**，而不需要挪动后面的钥匙扣。

链表的每个节点 `Node` 都包含两个字段：自己的数据 `Data` 和指向下一个节点的指针 `Next`。

![Types of Linked List - GeeksforGeeks](https://cdn.bowling233.top/images/2023/06/202306220001784.png)

#### 链表 API

| 返回值 | 方法名 | 参数 | 功能 |
| --- | --- | --- | --- |
| `LinkedList` | `create()` | 无 | 创建一个空链表 |
| `void` | `destroy(LinkedList list)` | `list`：链表 | 销毁链表 |
| `void` | `insert(LinkedList list, int index, int data)` | `list`：链表<br>`index`：节点的索引<br>`data`：待插入的数据 | 在链表中指定索引的节点后插入一个新节点 |
| `void` | `append(LinkedList list, int data)` | `list`：链表<br>`data`：待插入的数据 | 在链表的末尾插入一个新节点 |
| `void` | `delete(LinkedList list, int index)` | `list`：链表<br>`index`：节点的索引 | 删除链表中指定索引的节点 |
| `void` | `deleteValue(LinkedList list, int data)` | `list`：链表<br>`data`：待删除的数据 | 删除链表中第一个值为 `data` 的节点 |
| `int` | `length(LinkedList list)` | `list`：链表 | 返回链表的长度 |
| `Node` | `get(LinkedList list, int index)` | `list`：链表<br>`index`：节点的索引 | 返回链表中指定索引的节点 |
| `Node` | `search(LinkedList list, int data)` | `list`：链表<br>`data`：待查找的数据 | 返回链表中第一个值为 `data` 的节点 |
| `void` | `print(LinkedList list)` | `list`：链表 | 打印链表 |


#### 链表的实现

基本代码不再作解析，列出如下：

<!-- prettier-ignore-start -->
??? note "基础链表的实现"

    ```c title="linked_list.c"
    typedef struct Node {
        int data;
        struct Node *next;
    } Node;
    typedef struct LinkedList {
        Node *head;
        int length;
    } LinkedList;
    LinkedList *create() {
        LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
        list->head = NULL;
        list->length = 0;
        return list;
    }
    int length(LinkedList *list) {
        return list->length;
    }
    Node *get(LinkedList *list, int index) {
        if (index < 0 || index >= list->length) {
            printf("Index out of range\n");
            return NULL;
        }
        Node *p = list->head;
        for (int i = 0; i < index; i++) {
            p = p->next;
        }
        return p;
    }
    void insert(LinkedList *list, int index, int data) {
        if (index < 0 || index > list->length) {
            printf("Index out of range\n");
            return;
        }
        Node *new_node = (Node *)malloc(sizeof(Node));
        new_node->data = data;
        new_node->next = NULL;
        if (index == 0) {
            new_node->next = list->head;
            list->head = new_node;
        } else {
            Node *p = get(list, index - 1);
            new_node->next = p->next;
            p->next = new_node;
        }
        list->length++;
    }
    ```

<!-- prettier-ignore-end -->

在学习链表时，同学们遇到的最大的问题是处理空指针等边界情况。观察上面的代码，我们会发现**大部分操作都需要判断链表是否为空**。

<!-- prettier-ignore-start -->
!!! tip "空指针"

    使用链表时特别注意空指针的情况。
<!-- prettier-ignore-end -->

![](https://cdn.bowling233.top/images/2023/06/202306220004326.png)

为了简化处理空指针的情况，我们可以在链表的头部添加一个虚拟节点（哑节点） `dummy`，这样链表的头部就不会为空了。虚拟节点的数据域可以存储链表的长度，这样我们就不需要再维护 `length` 字段了。



此外，我们还会遇到双向链表和循环链表等实现，其 API 也会略有不同。这里给出其示意图，请自行考虑其 API 和实现方法：

![Doubly Circular Linked List | Omkar Nath Singh](https://cdn.bowling233.top/images/2023/06/202306220003165.gif)

### 栈

你可以将栈想象成一堆书本，你只能从最上面取走一本书，也只能将书放在最上面。这种数据结构被称为**后进先出**（Last In First Out，LIFO）。

#### 栈 API

| 返回值 | 方法名 | 参数 | 功能 |
| --- | --- | --- | --- |
| `Stack` | `create()` | 无 | 创建一个空栈 |
| `void` | `destroy(Stack stack)` | `stack`：栈 | 销毁栈 |
| `void` | `push(Stack stack, int data)` | `stack`：栈<br>`data`：待入栈的数据 | 将数据入栈 |
| `int` | `pop(Stack stack)` | `stack`：栈 | 将栈顶数据出栈并返回 |
| `int` | `peek(Stack stack)` | `stack`：栈 | 返回栈顶数据 |
| `int` | `isEmpty(Stack stack)` | `stack`：栈 | 判断栈是否为空 |

#### 栈的实现

基本实现代码如下：

<!-- prettier-ignore-start -->
??? note "栈的实现"

    ```c title="stack.c"
    typedef struct Stack {
        int *data;
        int top;
        int capacity;
    } Stack;
    Stack *create() {
        Stack *stack = (Stack *)malloc(sizeof(Stack));
        stack->data = (int *)malloc(sizeof(int) * 10);
        stack->top = -1;
        stack->capacity = 10;
        return stack;
    }
    void destroy(Stack *stack) {
        free(stack->data);
        free(stack);
    }
    void push(Stack *stack, int data) {
        if (stack->top == stack->capacity - 1) {
            printf("Stack overflow\n");
            return;
        }
        stack->data[++stack->top] = data;
    }
    int pop(Stack *stack) {
        if (stack->top == -1) {
            printf("Stack underflow\n");
            return -1;
        }
        return stack->data[stack->top--];
    }
    int peek(Stack *stack) {
        if (stack->top == -1) {
            printf("Stack underflow\n");
            return -1;
        }
        return stack->data[stack->top];
    }
    int isEmpty(Stack *stack) {
        return stack->top == -1;
    }
    ```
<!-- prettier-ignore-end -->

栈的实现较为简单，这里不再进一步解释。

### 队列

队列是一种**先进先出**（First In First Out，FIFO）的数据结构，你可以将其想象成排队买票。队列有两个端点，一个是队头，一个是队尾。新元素从队尾入队，从队头出队。

#### 队列 API

| 返回值 | 方法名 | 参数 | 功能 |
| --- | --- | --- | --- |
| `Queue` | `create()` | 无 | 创建一个空队列 |
| `void` | `destroy(Queue queue)` | `queue`：队列 | 销毁队列 |
| `void` | `enqueue(Queue queue, int data)` | `queue`：队列<br>`data`：待入队的数据 | 将数据入队 |
| `int` | `dequeue(Queue queue)` | `queue`：队列 | 将队头数据出队并返回 |
| `int` | `peek(Queue queue)` | `queue`：队列 | 返回队头数据 |
| `int` | `isEmpty(Queue queue)` | `queue`：队列 | 判断队列是否为空 |

#### 队列的实现

队列通常使用链表实现，因为需要频繁地在队尾插入元素和在队头删除元素。基本实现代码如下：

<!-- prettier-ignore-start -->
??? note "队列的基础实现"

    ```c title="queue.c"
    typedef struct Queue {
        int data;
        struct Queue *next;
    } Queue;
    Queue *create() {
        Queue *queue = (Queue *)malloc(sizeof(Queue));
        queue->next = NULL;
        return queue;
    }
    void destroy(Queue *queue) {
        Queue *tmp;
        while (queue) {
            tmp = queue;
            queue = queue->next;
            free(tmp);
        }
    }
    void enqueue(Queue *queue, int data) {
        Queue *tmp = queue;
        while (tmp->next) {
            tmp = tmp->next;
        }
        tmp->next = (Queue *)malloc(sizeof(Queue));
        tmp->next->data = data;
        tmp->next->next = NULL;
    }
    int dequeue(Queue *queue) {
        if (!queue->next) {
            printf("Queue underflow\n");
            return -1;
        }
        Queue *tmp = queue->next;
        int data = tmp->data;
        queue->next = tmp->next;
        free(tmp);
        return data;
    }
    int peek(Queue *queue) {
        if (!queue->next) {
            printf("Queue underflow\n");
            return -1;
        }
        return queue->next->data;
    }
    int isEmpty(Queue *queue) {
        return !queue->next;
    }
    ```
<!-- prettier-ignore-end -->



---

分割线下的部分暂未整理

## 排序算法

假设我们要让数组以升序排列

## Selection sort

数组被划分为两个子数组：排序的和未排序的。每次迭代，从未排序的子数组中选出最小的元素，将其放到未排序的子数组的开头。

选择排序需要两个循环，因为其中嵌套了查找最值的算法。

对于长度为 $N$ 的数组，选择排序需要约 $N^2/2$ 次比较和 $N$ 次交换。


```c
void selection_sort(int *arr, int len) {
    int i, j, min, tmp;
    for (i = 0; i < len - 1; i++) {//The wall begins at 0 and ends at len-1
        min = i;
        for (j = i + 1; j < len; j++) {//Find the minimum element in the unsorted array
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        if (min != i) {//Swap
            tmp = arr[i];
            arr[i] = arr[min];
            arr[min] = tmp;
        }
    }
}
```

## Bubble sort

数组被划分为两个子数组：排序的和未排序的。每次迭代，未排序的子数组中的最小元素从未排序的子数组上浮到排序的子数组的末尾。

所谓的冒泡是这样的：从未排序数组的末尾开始，逐个元素向前比较。如果当前元素比前一个元素小，则交换两个元素的位置，即小元素“上浮”。当然，我们也可以让大元素“下沉”，此时未排序的数组在左侧，排序的数组在右侧。

对于长度为 n 的数组，冒泡排序需要 n-1 次操作。

```c
void bubble_sort(int *arr, int len) {
    int i, j, tmp;
    for (i = 0; i < len - 1; i++) {
        for (j = len - 1; j > i; j--) {//Bubble
            if (arr[j] < arr[j - 1]) {
                tmp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = tmp;
            }
        }
    }
}
```

## Insertion sort

数组被划分为两个子数组：排序的和未排序的。每次迭代，未排序的子数组中的第一个元素被插入到排序的子数组的正确位置。

插入排序嵌入了寻找正确位置的算法。

对于随机排列的长度为 $N$ 且主键不重复的数组，平均情况下插入排序需要 $N^2/4$ 次比较和 $N^2/4$ 次交换。最坏情况下需要 $N^2/2$ 次比较和 $N^2/2$ 次交换，最好情况下需要 $N-1$ 次比较和 $0$ 次交换。

```c
void insertion_sort(int *arr, int len) {
    int i, j, tmp;
    for (i = 1; i < len; i++) {
        tmp = arr[i];
        for (j = i; j > 0 && arr[j - 1] > tmp; j--) {//Find the correct position
            arr[j] = arr[j - 1];
        }
        arr[j] = tmp;
    }
}
```

## 归并排序

```c
void merge(int *arr, int *tmp, int left, int mid, int right) {
    int i, j, k;
    for (i = left, j = mid + 1, k = left; i <= mid && j <= right; k++) {
        if (arr[i] <= arr[j]) {
            tmp[k] = arr[i++];
        } else {
            tmp[k] = arr[j++];
        }
    }
    while (i <= mid) {
        tmp[k++] = arr[i++];
    }
    while (j <= right) {
        tmp[k++] = arr[j++];
    }
    for (i = left; i <= right; i++) {
        arr[i] = tmp[i];
    }
}

void merge_sort(int *arr, int *tmp, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        merge_sort(arr, tmp, left, mid);
        merge_sort(arr, tmp, mid + 1, right);
        merge(arr, tmp, left, mid, right);
    }
}

```

## 快速排序

```c
int partition(int *arr, int left, int right) {
    int pivot = arr[left];
    while (left < right) {
        while (left < right && arr[right] >= pivot) {
            right--;
        }
        arr[left] = arr[right];
        while (left < right && arr[left] <= pivot) {
            left++;
        }
        arr[right] = arr[left];
    }
    arr[left] = pivot;
    return left;
}

void quick_sort(int *arr, int left, int right) {
    if (left < right) {
        int pivot = partition(arr, left, right);
        quick_sort(arr, left, pivot - 1);
        quick_sort(arr, pivot + 1, right);
    }
}
```

## 希尔排序

```c
void shell_sort(int *arr, int len) {
    int i, j, tmp, gap;
    for (gap = len / 2; gap > 0; gap /= 2) {
        for (i = gap; i < len; i++) {
            tmp = arr[i];
            for (j = i; j >= gap && arr[j - gap] > tmp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = tmp;
        }
    }
}
```

