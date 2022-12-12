#include "file.h"
#include "list.h"

/// @brief 写入文件数据
/// @param str 文件路径
/// @param head 链表头
/// @param size data 数据大小
void writeFile(char *str, LinkList* head, int size)
{
    FILE *fp = fopen(str,"wb");
    if(!fp)
    {
        perror("writeFile error");
        return;
    }
    LinkList *p = head->nxt;
    while(p != NULL)
    {
        fwrite(p->data, size, 1, fp);
        p = p->nxt;
    }
    fclose(fp);
}

/// @brief 读取文件数据，并存储到链表中
/// @param str 文件路径
/// @param head 链表头
/// @param size data 数据大小
/// @param len 链表长度存储到，应传地址
void readFile(char *str, LinkList* head, int size)
{
    FILE *fp = fopen(str, "rb");
    if(!fp)
    {
        perror("readFile error");
        return;
    }
    head->nxt = NULL;
    void *data = NULL;
    LinkList *tail = head;
    while (true)
    {
        data = malloc(size);
        int n = fread(data, size, 1, fp);
        if(!n) return;  // 如果没有读取到一个 size 大小的数据
        tail = addNode2(tail, data);
    }
    fclose(fp);
}