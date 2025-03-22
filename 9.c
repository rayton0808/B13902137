#include "9.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
typedef struct Node Node;

// 實際定義全域變數（由 main.c 可 extern 使用）
Node* head = NULL;
Node* tail = NULL;
int next_node_id = 1;

// 工具函式：Next-Node(node, prev) 與 New-XOR-Node(neighbors) 已由 9.h 提供

//----------------------------------------
// 1. O(1) 插入函式：Insert-After
//----------------------------------------
void Insert_After(Node* node, Node* prev) 
{
    Node* next = Next_Node(node, prev);
    Node* newNode = New_XOR_Node((Node*)((uintptr_t)next ^ (uintptr_t)node));

    if (next) 
    {
        next->neighbors = (Node*)((uintptr_t)next->neighbors ^ (uintptr_t)node ^ (uintptr_t)newNode);
    } 
    else 
    {
        tail = newNode;
    }

    node->neighbors = (Node*)((uintptr_t)node->neighbors ^ (uintptr_t)prev ^ (uintptr_t)newNode);
}

//----------------------------------------
// 2. O(1) 移除函式：Remove-Here
//----------------------------------------
void Remove_Here(Node* node, Node* prev) 
{
    Node* next = Next_Node(node, prev);

    if (prev) 
    {
        prev->neighbors = (Node*)((uintptr_t)prev->neighbors ^ (uintptr_t)node ^ (uintptr_t)next);
    } 
    else 
    {
        head = next;
    }

    if (next) 
    {
        next->neighbors = (Node*)((uintptr_t)next->neighbors ^ (uintptr_t)node ^ (uintptr_t)prev);
    } 
    else 
    {
        tail = prev;
    }

    free(node);
}

//----------------------------------------
// 3. O(1) 區段反轉函式：Reverse
//----------------------------------------
void Reverse(Node* prev, Node* begin, Node* end, Node* next) 
{
    if (prev)  prev->neighbors  = (Node*)((uintptr_t)prev->neighbors  ^ (uintptr_t)begin ^ (uintptr_t)end);
    if (begin) begin->neighbors = (Node*)((uintptr_t)begin->neighbors ^ (uintptr_t)prev  ^ (uintptr_t)next);
    if (end)   end->neighbors   = (Node*)((uintptr_t)end->neighbors   ^ (uintptr_t)next  ^ (uintptr_t)prev);
    if (next)  next->neighbors  = (Node*)((uintptr_t)next->neighbors  ^ (uintptr_t)end   ^ (uintptr_t)begin);
}

