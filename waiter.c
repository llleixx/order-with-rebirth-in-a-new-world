#include "waiter.h"
#include "common.h"
#include "list.h"
#include "file.h"
#include "bill.h"

extern LinkList *billHead, *tableHead, *orderHead, *menuHead;
extern Staff *curStaff;

void waiterView()
{
    while(true)
    {
        system("cls");


        printf("--------------------------------------------------\n");
        printf("             ����������֮��Ҫ���ϵͳ\n");
        printf("--------------------------------------------------\n");
        gotoXY(0, 15);
        printf("-------------------------------------------------\n");
        gotoXY(0, 6);
        printf("                  1: ����\n");
        printf("                  2: ���\n");
        printf("                  3: �˵���ѯ\n");
        printf("                  4������\n");
        printf("                  0: ����\n");

        gotoXY(55, 6);
        printf("���������ѡ��");
        char ch = getChar('0', '4');

        if(!ch) return;
        switch(ch)
        {
            case '1':
            {
                openDesk();
                break;
            }
            case '2':
            {
                orderDish();
                break;
            }
            case '3':
            {
                billView();
                break;
            }
            case '4':
            {
                payBill();
                break;
            }
            case '0':
            {
                return;
            }
        }           
    }
}

void openDesk()//����
{
    while(true)
    {
        system("cls");
        char ID[5];  // ����Ŀ�����
        Bill *bill;  // ���ɵ��˵���
        char curTime[15] = {0};

        LinkList *tableNode = tableHead->nxt;
        Table *table;
        
        // ��ӡ����
        printf("--------------------------------------------------\n");
        printf("                     ����\n");
        printf("--------------------------------------------------\n");
        printf("���    ״̬    ����\n");
        putchar('\n');
        

        while(tableNode != NULL)
        {
            table = (Table*)tableNode->data;
            if(table->flag == 0) printTable(table);
            tableNode = tableNode->nxt;
        }

        putchar('\n');
        printf("--------------------------------------------------");

        gotoXY(55, 6);
        printf("̨����ţ�");
        if(!getString(ID, 4, 3, 1)) return;

        int id = atoi(ID);

        tableNode = tableHead->nxt;

        bool flag = false;
        
        while (tableNode != NULL)
        {
            table = (Table*)tableNode->data;
            if(table->id == id)
            {
                // ����δ���ڿ���״̬
                if(table->flag != 0)
                {
                    flag = true;
                    break;
                }

                gotoXY(55, 7);
                printf("ռ�û�Ԥ��:");
                gotoXY(55, 8);
                printf("1:ռ�� 2:Ԥ��");
                gotoXY(55, 9);
                char ch = getChar('1', '2');
                if(!ch) return;

                table->flag = ch - '0';
                writeFile("table.txt", tableHead, sizeof(Table));

                bill = (Bill*)malloc(sizeof(Bill));
                memset(bill, 0, sizeof(Bill));
                bill->waiterId = curStaff->id;
                bill->tableId = id;
                bill->flag = 0;

                getTime(curTime);

                for(int i = 0; i < 8; ++i) bill->time[i] = curTime[i];
                sprintf(bill->serialNum, "YSJ%04d%04d%s", id, curStaff->id, curTime);

                addNode(billHead, bill);
                writeFile("bill.txt", billHead, sizeof(Bill));
                gotoXY(55, 10);
                printf("%s", "�����ɹ�");
                getchar();
                return;
            }
            tableNode = tableNode->nxt;
        }

        gotoXY(55, 7);
        flag ? printf("��̨��δ���ڿ���״̬") : printf("�����Ų�����");
        getchar();
    }
}

void orderDish()
{
    while (true)
    {
        system("cls");

        // ��������
        LinkList *billNode;
        Bill *bill;
        LinkList *menuNode;
        Menu *menu;
        LinkList *orderNode;
        Order *order;
        LinkList *tableNode;
        Table *table;

        // ��ӡ����
        printf("--------------------------------------------------\n");
        printf("                     ���\n");
        printf("--------------------------------------------------\n");
        printf("���    ״̬    ����\n");
        putchar('\n');
        
        tableNode = tableHead->nxt;
        while(tableNode != NULL)
        {
            table = (Table*)tableNode->data;
            if(table->flag == 1 || table->flag == 2) printTable(table);
            tableNode = tableNode->nxt;
        }

        putchar('\n');
        printf("--------------------------------------------------");

        // menu ���
        menuNode = menuHead->nxt;
        while(menuNode != NULL)
        {
            menu = (Menu*)menuNode->data;
            menu->num = 0;
            menuNode = menuNode->nxt;
        }        

        char ID[5];

        gotoXY(55, 6);
        printf("̨����ţ�");
        if(!getString(ID, 4, 3, 1)) return;
        int id = atoi(ID);


        // ��ȡ��ǰ̨���ѵ�˵�
        billNode = billHead->nxt;
        while (billNode != NULL)
        {
            bill = (Bill*)billNode->data;
            if (bill->tableId == id)
            {
                orderNode = orderHead->nxt;
                while (orderNode != NULL)
                {
                    order = (Order*)orderNode->data;
                    if (strcmp(order->serialNum, bill->serialNum) == 0)
                    {
                        menuNode = menuHead->nxt;
                        while(menuNode != NULL)
                        {
                            menu = (Menu*)menuNode->data;
                            if(menu->id == order->menuId)
                            {
                                menu->num += order->num;
                            }
                            menuNode = menuNode->nxt;
                        }
                    }
                    orderNode = orderNode->nxt;
                }
                break;  // �ҵ����˳�
            }
            billNode = billNode->nxt;
        }

        // �������˽�β����û�ҵ�
        if (billNode == NULL)
        {
            gotoXY(55, 7);
            printf("��̨�������ڻ�δ����");
            getchar();
            continue;
        }

        // ���
        while(true)
        {
            // ��ӡ�˵�
            system("cls");
            printf("--------------------------------------------------\n");
            printf("                       �˵�\n");
            printf("--------------------------------------------------\n");
            printf("���          ����                  �۸�     �ѵ����\n");
            putchar('\n');
            printList(menuHead, printMenu1);
            putchar('\n');
            printf("--------------------------------------------------");

            gotoXY(55, 4);
            printf("Ŀǰ�ܽ�%d", bill->total);

            gotoXY(55, 6);
            printf("���ױ�ţ�");
            if(!getString(ID, 4, 3, 1)) return;
            int id = atoi(ID);
            int total = 0;
            menuNode = menuHead->nxt;
            while(menuNode != NULL)
            {
                menu = (Menu*)menuNode->data;
                if(menu->id == id)
                {
                    gotoXY(55, 7);
                    printf("1���Ӳ� 2������");
                    printf("   ");
                    char ch = getChar('1', '2');
                    if(!ch) return;

                    gotoXY(55, 8);
                    printf("������");
                    char numStr[6];
                    if(!getString(numStr, 5, 3, 1)) return;

                    int num = atoi(numStr);

                    if(ch == '2' && menu->num < num)
                    {
                        gotoXY(55, 9);
                        printf("��������Ϊ������");
                        getchar();
                        break;
                    }

                    // �����µ� order
                    order = (Order*)malloc(sizeof(Order));
                    memset(order, 0, sizeof(Order));
                    if(ch == '1')
                    {
                        menu->num += num;
                        order->num = num;
                        order->total = num * (menu->price);
                    }
                    else
                    {
                        menu->num -= num;
                        order->num = -num;
                        order->total = -num * (menu->price);
                    }

                    bill->total += order->total;
                    writeFile("bill.txt", billHead, sizeof(Bill));

                    strcpy(order->serialNum, bill->serialNum);
                    strcpy(order->name, menu->name);
                    order->menuId = menu->id;
                    order->price = menu->price;

                    addNode(orderHead, order);
                    writeFile("order.txt", orderHead, sizeof(Order));

                    gotoXY(55, 9);
                    printf("��˳ɹ���");
                    getchar();
                    break;
                }
                menuNode = menuNode->nxt;
            }

            // �������˽�β����û�ҵ�
            if(menuNode == NULL)
            {
                gotoXY(55, 7);
                printf("�˲��ײ����ڣ�");
                getchar();
            }
        }
    }
}

void payBill()
{
    while(true)
    {
        system("cls");

        LinkList *orderNode = orderHead->nxt;
        Order *order;
        LinkList *billNode = billHead->nxt;
        Bill *bill;
        LinkList *tableNode = tableHead->nxt;
        Table *table;

        // ��ӡ����
        printf("------------------------------------------------------------------\n");
        printf("                             ����\n");
        printf("------------------------------------------------------------------\n");
        printf("��ˮ��                      ����Ա���  ̨�����  ʱ��      ���\n");
        putchar('\n');
        

        while(billNode != NULL)
        {
            bill = (Bill*)billNode->data;
            if(bill->flag == 0)
            {
                printBill(bill);
            }
            billNode = billNode->nxt;
        }

        putchar('\n');
        printf("------------------------------------------------------------------");

        gotoXY(71, 6);
        printf("̨����ţ�");

        char ID[5];
        if(!getString(ID, 4, 3, 1)) return;

        int id = atoi(ID);

        billNode = billHead->nxt;
        while(billNode != NULL)
        {
            bill = (Bill*)billNode->data;

            if(id == bill->tableId && bill->flag == 0)
            {
                system("cls");


                printf("-------------------------------------------------------------------\n");
                printf("                       ����\n");
                printf("-------------------------------------------------------------------\n");
                printf("��ˮ��                      ����              �۸�   ����   �ܼ�\n");
                putchar('\n');


                orderNode = orderHead->nxt;
                while(orderNode != NULL)
                {
                    order = (Order*)orderNode->data;
                    if(strcmp(bill->serialNum, order->serialNum) == 0)
                    {
                        printOrder(order);
                    }
                    orderNode = orderNode->nxt;
                }

                putchar('\n');
                printf("-------------------------------------------------------------------");


                gotoXY(72, 6);
                printf("Ӧ����%d", bill->total);
                gotoXY(72, 7);
                printf("ȷ�����ˣ�");
                gotoXY(72, 8);
                printf("0��ȡ�� 1��ȷ��");
                gotoXY(72, 9);
                char ch = getChar('0', '1');
                if (!ch) return;
                if(ch == '1')
                {
                    bill->flag = 1;
                    writeFile("bill.txt", billHead, sizeof(Bill));

                    // �ı�����״̬
                    while(tableNode != NULL)
                    {
                        table = (Table*)tableNode->data;
                        if(table->id == id)
                        {
                            table->flag = 0;
                            break;
                        }
                        tableNode = tableNode->nxt;
                    }
                    writeFile("table.txt", tableHead, sizeof(Table));

                    gotoXY(72, 10);
                    printf("���˳ɹ���\n");
                    getchar();
                    return;
                }
                else
                {
                    gotoXY(72, 10);
                    printf("����ʧ�ܣ�\n");
                    getchar();
                    return;
                }
                break;
            }
            billNode = billNode->nxt;
        }
        gotoXY(71, 7);
        printf("����������Ҫ���ˣ�");
        getchar();
    }
}