# Lab0: C Programming Lab

<!-- prettier-ignore-start -->
!!! note "第一次实验的提醒"
    
    请仔细阅读实验手册。
<!-- prettier-ignore-end -->

本实验要求用链表实现一个字符串队列。该 Lab 对代码鲁棒性要求较高，需要尽可能多地**考虑各种情况**。此外，对**内存泄漏**的检查也十分严格。在所有进行了节点增删操作的函数中都应当注意。

以下浅记录自己踩过的各种坑：

## 原地反转链表

```c
void queue_reverse(queue_t *q) {
    if(!q) return;
    /* You need to write the code for this function */
    if(!q->head) return;
    if(q->n == 1) return;

    list_ele_t * prev, * next;
    prev = q->tail = q->head;
    next = prev->next;

    while(next)
    {
        q->head = next;
        next = next->next; 
        q->head->next = prev;
        prev = prev->next; //Wrong Code
    }
    q->tail->next = NULL;
}
```

这段代码在链表长度为 3 以内时都能正确运行，若链表长度超过 3，则反转后链表竟只剩下反转后的头尾两个元素。原因在于标注 `Wrong Code` 的那一行：反转第一个节点时，上面的操作导致节点指向自身（这个问题在函数末尾处理 `tail` 时才得到解决），因此改行并不会使 `prev` 节点向后移动，而是一直固定在 `tail`。循环过后，链表中剩下的节点全都指向 `tail`，结果就是只剩两个了。

解决办法是改为 `prev = q->head`。

## 小心内存泄漏

容易踩坑的情况：

### 分配内存失败时的处理

本题调用 `malloc()` 的函数主要是插入节点函数。但是如果为节点的字符串调用 `malloc()` 失败时，不能直接退出函数，需要释放预先创建的节点 `newh`。**总之：函数首先要保证自己的完善。**

- 如果函数失败，函数要保证自己退出时内存安全。
- 如果函数成功返回，调用者必须保证内存安全。

### 删除节点时的处理

```c
bool queue_remove_head(queue_t *q, char *buf, size_t bufsize){
    if(!q) return false;
    if(!q->head) return false;

    if(buf)
    {
        strncpy(buf, q->head->value, bufsize - 1);
        buf[bufsize - 1] = 0;
    }
    free(q->head->value);
    q->head = q->head->next;
    q->n--;
    return true;
}
```

上面的这个函数没有释放删去的节点的内存，是典型的内存泄露。


<!-- prettier-ignore-start -->
!!! info "实验解析和答案"
    
    - [知乎：CSAPP:Lab0-C Programming Lab](https://zhuanlan.zhihu.com/p/127317503)
<!-- prettier-ignore-end -->
