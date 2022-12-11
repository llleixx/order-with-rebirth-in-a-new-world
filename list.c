#include "list.h"

/// @brief 增加链表节点
/// @param head 链表头部
/// @param data 数据
void addNode(LinkList *head, void *data)
{
    LinkList *p = (LinkList*)malloc(sizeof(LinkList));
    p->nxt = head->nxt;
    p->data = data;
    head->nxt = p;
}

/// @brief 与上不同，只用于读取文件时的尾插
/// @param tail 
/// @param data 
LinkList* addNode2(LinkList *tail, void *data)
{
    LinkList *p = (LinkList*)malloc(sizeof(LinkList));
    tail->nxt = p;
    p->data = data;
    p->nxt = NULL;
    return p;
}

/// @brief 删除链表节点
/// @param head 链表头部
/// @param node 需被删除节点
void deleteNode(LinkList *head, LinkList *node)
{
    LinkList *preNode = head;
    while(preNode->nxt != node) preNode = preNode->nxt;
    preNode->nxt = node->nxt;
    free(node->data);
    free(node);
}

/// @brief 打印链表
/// @param p 当前节点
/// @param model 打印方式
void printList(LinkList *p, PrintModel model)
{
    p = p->nxt;
    while(p != NULL)
    {
        (*model)(p->data);
        p = p->nxt;
    }
}

