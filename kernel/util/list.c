#include "mm/sys_heap.h"

//双向循环链表

//链表节点
typedef struct list_node
{
    struct list_node *prev;
    struct list_node *next;
} list_node_t;

//链表头
typedef struct list_head
{
    list_node_t *first;
    list_node_t *last;
} list_head_t;

//初始化链表头
void list_init(list_head_t *head)
{
    head->first = NULL;
    head->last = NULL;
}

//初始化链表节点
void list_node_init(list_node_t *node)
{
    node->prev = NULL;
    node->next = NULL;
}

//在链表头插入节点
void list_insert_first(list_head_t *head, list_node_t *node)
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

//在链表尾插入节点
void list_insert_last(list_head_t *head, list_node_t *node)
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
        head->last = node;
    }
}

//在链表中插入节点
void list_insert(list_head_t *head, list_node_t *node, list_node_t *prev)
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
        node->prev = prev;
        node->next = prev->next;
        prev->next->prev = node;
        prev->next = node;
    }
}

//删除链表中的节点
void list_remove(list_head_t *head, list_node_t *node)
{
    if (head->first == node)
    {
        if (head->first == head->last)
        {
            head->first = NULL;
            head->last = NULL;
        }
        else
        {
            head->first = node->next;
            head->last->next = head->first;
            head->first->prev = head->last;
        }
    }
    else
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
}

//获取链表中的第一个节点
list_node_t* list_first(list_head_t *head)
{
    return head->first;
}

//获取链表中的最后一个节点
list_node_t* list_last(list_head_t *head)
{
    return head->last;
}