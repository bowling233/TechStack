// 本程序演示二叉树和左儿子右兄弟树的实现

#include <stdio.h>
#include <stdlib.h>

typedef struct bNodes* BinaryTree;
struct bNodes
{
    int key;
    BinaryTree left, right;
};

typedef BinaryTree BSearchTree;

BinaryTree createBinaryTree(int key)
{
    BinaryTree ret = (BinaryTree)malloc(sizeof(struct bNodes));
    ret->key = key;
    ret->left = ret->right = NULL;
    return ret;
}

/**
 * @brief 
 * 
 * 如果该树有任意节点，那么打印括号
 *  如果其中有一个是空节点，那么打印 n
 * 如果该树没有孩子，那么它是叶子，不打印括号
 * @param n 
 */
void printBinaryTree(BinaryTree n)
{
    if(n->left || n->right)
    {
        printf("(");
    }
    if(n->left)
    {
        putchar('(');
        printBinaryTree(n->left);
        putchar(')');
    }
    printf(" %d ", n->key);
    if(n->right)
    {
        putchar('(');
        printBinaryTree(n->right);
        putchar(')');
    }
    if(n->left || n->right)
    {
        printf(")");
    }
}

struct stack
{
    BinaryTree *n;
    int size, top;
};
typedef struct stack Stack;

Stack* createStack(int size)
{
    Stack *ret = (Stack *)malloc(sizeof(Stack));
    ret->size = size;
    ret->top = -1;
}

int isEmpty(Stack *s)
{
    return s->top == -1;
}

int isFull(Stack *s)
{
    return s->top == s->size - 1;
}

void stackInsert(Stack *s, BinaryTree n)
{
    if(isFull(s))
        return;
    s->n[++s->top] = n;
}

BinaryTree stackPop(Stack *s)
{
    if(isEmpty(s))
        return NULL;
    return s->n[s->top--];
}

BinaryTree stackPeep(Stack *s)
{
    if(!isEmpty(s))
        return s->n[s->top];
    exit(EXIT_FAILURE);
}

/**
 * @brief 
 * 
 * 先将一个节点推入栈。
 * 一个循环条件：栈非空。
 * 如果栈的每个元素只能是纯净的 tree，那么应当维护一个 lastOpIsPop，报告上一次对栈的操作。这样就能够知道当前究竟打印到什么情况了。
 *  对栈顶的节点，分以下情况：
 * 1. 如果该节点是叶子，那么打印该节点，然后弹出
 * 2. 上一次结果是弹出，检查该节点是否是左节点。如果是的话，它的底下是右兄弟节点，接下来处理右兄弟节点（将pop置0）。
 * 3. 上一次结果是弹出，检查该节点是否是右节点。如果是的话，弹出该节点，pop为1。
 * 4. 上一次结果不是弹出，但该节点是内部节点。这是什么情况？
 * @param n 
 */
void printBinaryTreeStack(Stack *s, BinaryTree n)
{
    stackInsert(s, n);
    while(!isEmpty(s))
    {
        BinaryTree thisNode = stackPeep(s);
        if(thisNode->left)
        {
            stackInsert(s, thisNode->left);
            continue;
        }

        printf(" %d ", thisNode->key);

        if(thisNode->right)
        {
            stackInsert(s, thisNode->right);
            continue;
        }

        stackPop(s);
    }

}

typedef struct lrNodes lrTree;
struct lrNodes
{
    int key;
    lrTree *child, *sibling;
};

int main(void)
{
    BinaryTree n = createBinaryTree(1);
    n->left = createBinaryTree(2);
    n->right = createBinaryTree(3);
    n->left->left = createBinaryTree(4);
    printBinaryTree(n);
    return 0;
}