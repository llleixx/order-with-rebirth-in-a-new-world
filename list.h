#ifndef _LIST_H_
#define _LIST_H_

#include "global.h"

/// @brief 链表
typedef struct Node{
    void *data;
    struct Node *nxt;
}LinkList;

/// @brief 打印方式
typedef void (*PrintModel)(void *);

void addNode(LinkList *head, void *data);
void deleteNode(LinkList *head, LinkList *node);
void deleteList(LinkList *head);
void printList(LinkList *head, PrintModel model);
LinkList* addNode2(LinkList *tail, void *data);

#endif