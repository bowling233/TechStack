// 本程序演示后缀表达式建树

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node Node;
struct node
{
    char key;
    Node* left, *right;
};

typedef struct stack Stack;
struct stack
{
    int size;
    Node** stack;
    int top;
};

Node* createNode(char key)
{
    Node* ret = (Node*)malloc(sizeof(Node));
    if(!ret)
    {
        printf("Malloc Failed\n");
        exit(1);
    }
    ret->key = key;
    ret->left = ret->right = NULL;
    return ret;
}

Stack* createStack(int size)
{
    Stack* ret = (Stack*)malloc(sizeof(Stack));
    if(!ret)
    {
        exit(1);
    }
    ret->stack = (Node**)malloc(sizeof(Node) * (size + 1));
    ret->size = size;
    ret->top = 0;
    if(!ret->stack)
    {
        exit(1);
    }
    return ret;
}

void pushStack(Stack *s, Node* n)
{
    if(s->top == s->size)
    {
        exit(1);
    }
    s->stack[++s->top] = n;
}

Node* popStack(Stack *s)
{
    return s->stack[s->top--];
}

void printTree(Node *n)
{
    if(n->left)
    {
        printf("[Node %c] left leaf: %c\n", n->key, n->left->key);
        printTree(n->left);
    }
    if(n->right)
    {
        printf("[Node %c] right leaf: %c\n", n->key, n->right->key);
        printTree(n->right);
    }
}

int main(void)
{
    int size;
    scanf("%d", &size);

    Stack* s = createStack(size);

    for(int i = 0; i < size; i++)
    {
        char temp;
        if(scanf(" %c", &temp) == EOF) break;
        Node *new = createNode(temp);
        printf("input %c\n", temp);
        switch(temp)
        {
            case '+': case '-': case '*': case '/':
                new->left = popStack(s);
                new->right = popStack(s);
                pushStack(s, new);
                break;
            default:
                if(!isalpha(temp))
                {
                    printf("switch error: %c\n", temp);
                    exit(1);
                }
                pushStack(s, createNode(temp));
        }
    }
    if(s->top != 1) 
    {
        printf("s->top %d\n", s->top);
        exit(1);
    }
    printTree(s->stack[s->top]);
    return 0;
}
