#include "mm/buddy.h"

buddy_node buddy_root;

void init_buddy()
{
    buddy_root.left = NULL;
    buddy_root.right = NULL;
    buddy_root.order = MAX_ORDER;
    buddy_root.state = FREE;
    buddy_root.start = (void *)USER_START_ADDR;
}

int split_buddy(buddy_node *node)
{
    if (node->order == 0)
        return -1;
    node->left = (buddy_node *)kmalloc(sizeof(buddy_node));
    node->right = (buddy_node *)kmalloc(sizeof(buddy_node));
    node->left->order = node->order - 1;
    node->left->start = node->start;
    node->left->state = FREE;
    node->left->left = NULL;
    node->left->right = NULL;
    node->right->order = node->order - 1;
    node->right->start = node->start + (1 << (node->order - 1));
    node->right->state = FREE;
    node->right->left = NULL;
    node->right->right = NULL;
    return 0;
}

void merge_buddy(buddy_node *node)
{
    if (node->left == NULL) // 无子节点（左右子节点状态相同，判断其中之一即可）
        return;
    if (node->left->state == ALLOCATED || node->right->state == ALLOCATED)
        return;
    // 有子节点，在此不做递归调用，因为在分配内存时，只会分配到最底层的节点
    // 合并节点时，只需判断左右子节点是否为空，若为空，则合并
    kfree(node->left, sizeof(buddy_node));
    kfree(node->right, sizeof(buddy_node));
    node->left = NULL;
    node->right = NULL;
}

buddy_node *alloc_buddy(buddy_node *root, int order)
{
    if (order > root->order)
        return NULL;
    if (order == root->order)
    {
        root->state = ALLOCATED;
        return root;
    }
    else
    {
        if (root->left == NULL)
        {
            if (split_buddy(root) == -1)
                return NULL;
        }
        void *ret = alloc_buddy(root->left, order);
        if (ret == NULL)
            ret = alloc_buddy(root->right, order);
        return ret;
    }
    return NULL;
}

void free_buddy(void *start, int order)
{
    buddy_node *root = &buddy_root;
    buddy_node *node = root;
    while (node->order != order)
    {
        if (node->left == NULL)
        {
            mm_error("free_buddy: invalid operation. (start: %p, order: %d)", start, order);
            return;
        }
        root = node;
        if (start < node->right->start)
            node = node->left;
        else
            node = node->right;
    }
    node->state = FREE;
    if (root->left->state == FREE && root->right->state == FREE)
        merge_buddy(root);
}

void *buddy_alloc(int size)
{
    int order = 0;
    while ((1 << order) < size)
        order++;
    buddy_node *node = alloc_buddy(&buddy_root, order);
    if (node == NULL)
        return NULL;
    set_dead_beef(node->start + (1 << order) - 1);
    return (void *)node->start;
}

void buddy_free(void *addr, int size)
{
    int order = 0;
    while ((1 << order) < size)
        order++;
    if (!check_dead_beef(addr + (1 << order) - 1))
    {
        mm_error("buddy_free: Dead beef check failure. (addr: %p, size: %d)", addr, size);
    }
    free_buddy(addr, order);
}

void *buddy_realloc(void *addr, int old_size, int new_size)
{
    void *new_addr = buddy_alloc(new_size);
    if (new_addr == NULL)
        return NULL;
    memcpy(new_addr, addr, old_size);
    buddy_free(addr, old_size);
    return new_addr;
}

void *buddy_calloc(int size)
{
    void *addr = buddy_alloc(size);
    if (addr == NULL)
        return NULL;
    memset(addr, 0, size);
    return addr;
}