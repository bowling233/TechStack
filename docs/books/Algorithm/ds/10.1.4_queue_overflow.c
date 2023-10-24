// 本程序演示基本的队列 ADT 和溢出的处理。
// 值得注意的是，tail 一般指向队列末位元素的后一位。
// 长度为 n 的数组可容纳 n-1 的队列
#include <stdio.h>
#include <stdlib.h>

struct queue
{
    int * queue;
    int size;
    int head, tail;
};
typedef struct queue Queue;

int isEmptyQueue(Queue* queue)
{
    return queue->head == queue->tail;
}

Queue* createQueue(int size)
{
    Queue* ret = (Queue*)malloc(sizeof(Queue));
    ret->queue = (int*)malloc(sizeof(int) * (size + 1));
    ret->size = size;
    ret->head = ret->tail = 0;
    return ret;
}

void enQueue(Queue* queue, int data)
{
    int tail_next = (queue->tail + 1) % (queue->size + 1);

    if(tail_next == queue->head)
    {
        printf("Up Overflow\n");
        exit(1);
    }
    queue->queue[queue->tail] = data;
    queue->tail = tail_next;
}

int deQueue(Queue* queue)
{
    if(queue->head == queue->tail)
    {
        printf("Bottom Overflow\n");
        exit(1);
    }
    int ret = queue->queue[queue->head];
    queue->head = (queue->head + 1) % (queue->size + 1);
    return ret;
}

void printQueue(Queue* queue)
{
    if(isEmptyQueue(queue))
    {
        printf("Empty Queue\n");
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
    Queue* queue = createQueue(size);
    for(int i = 0; i < size; i++)
    {
        int temp;
        scanf("%d", &temp);
        enQueue(queue, temp);
        deQueue(queue);
    }
    printQueue(queue);
    enQueue(queue, 6);
    deQueue(queue);
    deQueue(queue);
    return 0;
}
