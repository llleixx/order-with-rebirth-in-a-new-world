#include "file.h"
#include "list.h"

/// @brief д���ļ�����
/// @param str �ļ�·��
/// @param head ����ͷ
/// @param size data ���ݴ�С
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

/// @brief ��ȡ�ļ����ݣ����洢��������
/// @param str �ļ�·��
/// @param head ����ͷ
/// @param size data ���ݴ�С
/// @param len �����ȴ洢����Ӧ����ַ
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
        if(!n) return;  // ���û�ж�ȡ��һ�� size ��С������
        tail = addNode2(tail, data);
    }
    fclose(fp);
}