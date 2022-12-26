## Chapter 17 Advanced Data Representation

the knowledge you should know:

-   `malloc()`
-   structure
-   union
-

Finding the right data representation is important in program design. You should think of these aspects:

-   What **operation** will be necessary

### 17.1 Exploring Data Representation

### 17.2 Beyond the Array to the Linked List

-   Linked List: a list in which each item contains information **describing where to find the next item**
-   Head Pointer: the head pointer points to the first item in a linked list of items

Next step: Separating the user interface from the details will make the program easier to understand and to update.

### 17.3 Abstract Data Types

Way to define new data types:

1. Provide an abstract description of the type’s properties and of the operations you can perform on the type. This description shouldn’t be tied to any particular implementation. It shouldn’t even be tied to a particular programming language. Such a formal abstract description is called an abstract data type (ADT).
2. Develop a **programming interface** that implements the ADT. That is, indicate how to store the data and describe a set of functions that perform the desired operations. In C, for example, you might supply **a structure definition along with prototypes for functions to manipulate the structures**. These functions play the same role for the user-defined type that C’s built-in operators play for the fundamental C types. Someone who wants to use the new type will use this interface for her or his programming.
3. Write code to implement the interface. This step is essential, of course, but the programmer using the new type need not be aware of the details of the implementation.

List:

-   Type Name: Simple List
-   Type Properties: Can hold a sequence of items.
-   Type Operations:
    -   Initialize list to empty.
    -   Determine whether list is empty.
    -   Determine whether list is full.
    -   Determine number of items in the list.
    -   Add item to end of list.
    -   Traverse list, processing each item in list.
    -   Empty the list.

Build an Interface: interface design should parallel the ADT description as closely as possible

1. describes how the **data will be represented**

    should be expressed in terms of some **general `Item` type** instead of in terms of some specific type

    ```C
      struct specificType { ... };
      typedef struct specificType Item;//to generalize its concept
    ```

2. how to **store items** of that type

    belongs to the implementation stage

    ```C
    typedef struct node { ... } Node;
    typedef struct list { ... } List;
    ```

3. operations

    ```C
    // operation: initialize a list
    // preconditions: plist points to a list
    // postconditions: the list is initialized to empty
    void InitializeList(List * plist);
    ```

4. put these things into an **header file**

    1. capitalizes each function name as a way of marking it as part of an interface package
    2. uses the `#ifndef` technique

5. put functions implementations into an `.c` file

    1. there are functions that is part of the implementation but not part of the interface, called **local function**. We **hide these functions usging the `static` storage class qualifier**
    2. local functions are often type related

> The Limitations of `const`:
>
> ```C
> (*plist)->item.rating = 3; // allowed even if *plist is const
> ```
>
> That’s because this code doesn’t change *plist ; it changes data that *plist points to.
>
> You can’t necessarily rely on const to catch programming errors that accidentally modify data.

### 17.4 Getting Queued with an ADT

Queue:

-   Type Name: Queue
-   Type Properties: Can hold an ordered sequence of items.
-   Type Operations:
    -   Initialize queue to empty.
    -   Determine whether queue is empty.
    -   Determine whether queue is full.
    -   Determine number of items in the queue.
    -   Add item to rear of queue.
    -   Remove and recover item from front of queue.
    -   Empty the queue.

Implementation thoughts:

-   adding an item to the end of **arrays** is easy,but ... **removing the front items waste a lot of time to move the array left**
-   **changing the indicator to the first item**,but waste a lot of space
-   **make the queue circular**
-   Best choice: **list**

Implementation:

```C
typedef struct queue {
	Node * front;
	Node * rear;
	int items;
} Queue;
```

### 17.5 Simulating with a Queue

### 17.6 The Linked List Versus the Array

### 17.7 Binary Search Trees

-   Ordering: the item in a left node precedes the item in the parent node, and the item in the right node follows the item in the parent node.
-   Relationship: all items that can trace their ancestry back to a left node of a parent contain items that precede the parent item in order, and every item descended from the right node contains items that follow the parent item in order.
-   **Hierarchical** organization: the data is organized in **ranks**, or levels, with each rank, in general, having ranks above and below it

Binary Tree ADT:

-   Type Name: Binary Search Tree
-   Type Properties: A binary tree is either an empty set of nodes (an empty tree) or a set of nodes with one node designated the root. Each node has exactly two trees, called the left subtree and the right subtree , descending from it.
    Each subtree is itself a binary tree, which includes the possibility of being an empty tree.
    A binary search tree is an ordered binary tree in which each node contains an item, in which all items in the left subtree precede the root item, and in which the root item precedes all items in the right subtree.
-   Type Operations:
    -   Initializing tree to empty.
    -   Determining whether tree is empty.
    -   Determining whether tree is full.
    -   Determining the number of items in the tree.
    -   Adding an item to the tree.
    -   Removing an item from the tree.
    -   Searching the tree for an item.
    -   Visiting each item in the tree.
    -   Emptying the tree.

### 17.8 Other Directions
