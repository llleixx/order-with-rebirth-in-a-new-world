#include "list.h"
#include "file.h"
#include "global.h"
#include "login.h"

// �ֱ�Ϊ��Ա��̨�����˵����������˵��������ͷ
LinkList *staffHead, *tableHead, *billHead, *orderHead, *menuHead;

int main()
{
    // system("chcp 65001");
    // ��ʼ������
    staffHead = (LinkList*)malloc(sizeof(LinkList));
    tableHead = (LinkList*)malloc(sizeof(LinkList));
    billHead = (LinkList*)malloc(sizeof(LinkList));
    orderHead = (LinkList*)malloc(sizeof(LinkList));
    menuHead = (LinkList*)malloc(sizeof(LinkList));
    readFile("staff.txt", staffHead, sizeof(Staff));
    readFile("table.txt", tableHead, sizeof(Table));
    readFile("bill.txt", billHead, sizeof(Bill));
    readFile("order.txt", orderHead, sizeof(Order));
    readFile("menu.txt", menuHead, sizeof(Menu));
    //��¼
    login();
    return 0;
}