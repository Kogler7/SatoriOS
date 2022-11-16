#include "mm/sys_heap.h"

//int队列

//队列节点
typedef struct queue_node
{
    struct queue_node *prev;
    struct queue_node *next;
    int value;
} queue_node_t;

//队列头
typedef struct queue_head
{
    queue_node_t *first;
    queue_node_t *last;
} queue_head_t;

//初始化队列头
void queue_init(queue_head_t *head)
{
    head->first = NULL;
    head->last = NULL;
}

//初始化队列节点
void queue_node_init(queue_node_t *node)
{
    node->prev = NULL;
    node->next = NULL;
}

//在队列头插入节点
void queue_insert_first(queue_head_t *head, queue_node_t *node)
{
    if (head->first == NULL)
    {
        head->first = node;
        head->last = node;
        node->prev = node;
        node->next = node;
    }
    else
    {
        node->prev = head->last;
        node->next = head->first;
        head->first->prev = node;
        head->last->next = node;
        head->first = node;
    }
}