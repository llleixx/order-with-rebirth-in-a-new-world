#include "list.h"

/// @brief ��������ڵ�
/// @param head ����ͷ��
/// @param data ����
void addNode(LinkList *head, void *data)
{
    LinkList *p = (LinkList*)malloc(sizeof(LinkList));
    p->nxt = head->nxt;
    p->data = data;
    head->nxt = p;
}

/// @brief ���ϲ�ͬ��ֻ���ڶ�ȡ�ļ�ʱ��β��
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

/// @brief ɾ������ڵ�
/// @param head ����ͷ��
/// @param node �豻ɾ���ڵ�
void deleteNode(LinkList *head, LinkList *node)
{
    LinkList *preNode = head;
    while(preNode->nxt != node) preNode = preNode->nxt;
    preNode->nxt = node->nxt;
    free(node->data);
    free(node);
}

/// @brief ��ӡ����
/// @param p ��ǰ�ڵ�
/// @param model ��ӡ��ʽ
void printList(LinkList *p, PrintModel model)
{
    p = p->nxt;
    while(p != NULL)
    {
        (*model)(p->data);
        p = p->nxt;
    }
}

