// 本程序演示双端队列的实现
// 双端队列的接口应当简洁明了，在哪一段的操作就用哪一段表示。不应当认为在 head 的 dequeue 操作是从 tail 出队。
#include <stdio.h>
#include <stdlib.h>

struct deque
{
    int * queue;
    int size;
    int head, tail;
};
typedef struct deque Deque;

int isEmptyQueue(Deque* queue)
{
    return queue->head == queue->tail;
}

Deque* createQueue(int size)
{
    Deque* ret = (Deque*)malloc(sizeof(Deque));
    ret->queue = (int*)malloc(sizeof(int) * (size + 1));
    ret->size = size;
    ret->head = ret->tail = 0;
    return ret;
}

void enQueueFront(Deque* queue, int data)
{
    int head_next = queue->head - 1;
    head_next = head_next < 0 ? head_next + queue->size + 1 : head_next;
    if(head_next == queue->tail)
    {
        printf("enqueue front failed\n");
        exit(1);
    }
    queue->queue[head_next] = data;
    queue->head = head_next;
}

void enQueueBack(Deque* queue, int data)
{
    int tail_next = (queue->tail + 1) % (queue->size + 1);

    if(tail_next == queue->head)
    {
        printf("enqueue back failed\n");
        exit(1);
    }
    queue->queue[queue->tail] = data;
    queue->tail = tail_next;
}

int deQueueFront(Deque* queue)
{
    if(queue->head == queue->tail)
    {
        printf("dequeue front failed\n");
        exit(1);
    }
    int ret = queue->queue[queue->head];
    queue->head = (queue->head + 1) % (queue->size + 1);
    return ret;
}

int deQueueBack(Deque* queue)
{
    if(queue->head == queue->tail)
    {
        printf("dequeue back failed\n");
        exit(1);
    }
    int tail_next = queue->tail - 1;
    tail_next = tail_next < 0 ? tail_next + queue->size + 1 : tail_next;
    queue->tail = tail_next;
    return queue->queue[queue->tail];
}

void printQueue(Deque* queue)
{
    if(isEmptyQueue(queue))
    {
        printf("Empty Deque\n");
        return;
    }

    for(int index = queue->head; index != queue->tail;)
    {
        printf("%d ", queue->queue[index]);
        index = (index + 1) % (queue->size + 1);
    }
    putchar('\n');
}

int main(void)
{
    int size;
    scanf("%d", &size);
    Deque* queue = createQueue(size);
    for(int i = 0; i < size; i++)
    {
        int temp;
        scanf("%d", &temp);
        if(temp % 2 == 0) enQueueBack(queue, temp);
        else enQueueFront(queue, temp);
    }
    deQueueBack(queue);
    deQueueFront(queue);
    printQueue(queue);
    for(int i = 0; i < 4; i++)
    {
        deQueueBack(queue);
    }
    return 0;
}
