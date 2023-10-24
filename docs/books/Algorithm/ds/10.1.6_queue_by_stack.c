// 本程序演示双栈实现队列
#include <stdio.h>
#include <stdlib.h>

struct stack
{
    int *stack;
    int size;
    int top;
};
typedef struct stack Stack;

struct queue
{
    Stack *input, *output;
    int size;
};
typedef struct queue Queue;

Stack *createStack(int size)
{
    Stack *ret = (Stack *)malloc(sizeof(Stack));
    ret->size = size;
    ret->top = 0;
    ret->stack = (int *)malloc(sizeof(int) * (size + 1));
    return ret;
}

int isEmptyStack(Stack *s)
{
    return !s->top;
}

int isFullStack(Stack *s)
{
    return s->top == s->size;
}

void pushStack(Stack *s, int data)
{
    if (s->top == s->size)
    {
        printf("push stack failed\n");
        exit(1);
    }
    s->stack[++s->top] = data;
}

int popStack(Stack *s)
{
    if (!s->top)
    {
        printf("pop stack failed\n");
        exit(1);
    }
    return s->stack[s->top--];
}

void printStack(Stack *s)
{
    if(isEmptyStack(s))
    {
        printf("Empty Stack\n");
        return;
    }
    for(int i = s->top; i > 0; i--)
    {
        printf("%d ", s->stack[i]);
    }
    putchar('\n');
}

void printStackReverse(Stack *s)
{
    if(isEmptyStack(s))
    {
        printf("Empty Stack\n");
        return;
    }
    for(int i = 1; i <= s->top; i++)
    {
        printf("%d ", s->stack[i]);
    }
    putchar('\n');
}

Queue *createQueue(int size)
{
    Queue *ret = (Queue *)malloc(sizeof(Queue));
    ret->input = createStack(size);
    ret->output = createStack(size);
    ret->size = size;
    return ret;
}

// all data will only be in one place, input stack or output stack
// enQueue to input stack, deQueue from output stack

int isFullQueue(Queue *queue)
{
    return isFullStack(queue->input) || isFullStack(queue->output);
}

int isEmptyQueue(Queue *queue)
{
    return isEmptyStack(queue->input) && isEmptyStack(queue->output);
}

void enQueue(Queue *queue, int data)
{
    if(isFullQueue(queue))
    {
        printf("enQueue failed\n");
        exit(1);
    }
    while(!isEmptyStack(queue->output))
    {
        pushStack(queue->input, popStack(queue->output));
    }
    pushStack(queue->input, data);
    // lazy data movement left to dequeue operation
}

int deQueue(Queue *queue)
{
    if(isEmptyQueue(queue))
    {
        printf("deQueue failed\n");
        exit(1);
    }
    while(!isEmptyStack(queue->input))
    {
        pushStack(queue->output, popStack(queue->input));
    }
    return popStack(queue->output);
}

void printQueue(Queue *queue)
{
    if(!isEmptyStack(queue->input))
    {
        printStackReverse(queue->input);
    }
    else if(!isEmptyStack(queue->output))
    {
        printStack(queue->output);
    }
    else{
        printf("print Queue error\n");
        exit(1);
    }
}

int main(void)
{
    int size;
    scanf("%d", &size);
    Queue *queue = createQueue(size);
    for(int i = 0; i < size; i++)
    {
        int data;
        scanf("%d", &data);
        enQueue(queue, data);
    }
    deQueue(queue);
    printQueue(queue);
    for(int i = 0; i < size; i++)
    {
        deQueue(queue);
    }
    return 0;
}
