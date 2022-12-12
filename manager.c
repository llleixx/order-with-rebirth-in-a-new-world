#include "manager.h"
#include "waiter.h"
#include "bill.h"
#include "list.h"
#include "common.h"
#include "file.h"


extern LinkList *billHead;

/// @brief �������
void managerView()
{
    while(true)
    {
        system("cls");

        printf("--------------------------------------------------\n");
        printf("             ����������֮��Ҫ���ϵͳ\n");
        printf("--------------------------------------------------\n");
        gotoXY(0, 15);
        printf("-------------------------------------------------\n");
        gotoXY(0,6);
        printf("                  1: �˵���ѯ\n");
        printf("                  2: Ӫҵ���ѯ\n");
        printf("                  0: ����\n");

        gotoXY(55, 6);
        printf("���������ѡ��");
        char ch = getChar('0','2');
        if(!ch) return;
        switch(ch)
        {
            case '1':
            {
                billView();
                break;
            }
            case '2':
            {
                queryTurnover();
                break;
            }
            case '0':
            {
                return;
            }
        }        
    }
}

/// @brief ��ѯӪҵ��
void queryTurnover()
{
    system("cls");
    // �洢��ʼ����
    char startTime[9] = {0};
    char startYear[5];
    char startMonth[3];
    char startDay[3];
    // �洢��������
    char endTime[9] = {0};
    char endYear[5];
    char endMonth[3];
    char endDay[3];


    printf("--------------------------------------------------\n");
    printf("                   Ӫҵ���ѯ��ѯ\n");
    printf("--------------------------------------------------\n");
    gotoXY(0, 15);
    printf("-------------------------------------------------\n");

	gotoXY(12, 6);
	printf("��ѯ���ڣ�");
	gotoXY(12, 8);
	printf("�������ڣ�");
	
	gotoXY(30,6);
	printf(" ��");
	gotoXY(37,6);
	printf("��");
	gotoXY(42,6);
	printf("��");
	gotoXY(30,8);
	printf(" ��");
	gotoXY(37,8);
	printf("��");
	gotoXY(42,8);
	printf("��");   
    
    gotoXY(27, 6);
    if(!getString(startYear, 4, 3, 1)) return;

    gotoXY(35, 6);
    if(!getString(startMonth, 2, 3, 1)) return;

    gotoXY(40, 6);
    if(!getString(startDay, 2, 3, 1)) return;

    gotoXY(27, 8);
    if(!getString(endYear, 4, 3, 1)) return;

    gotoXY(35, 8);
    if(!getString(endMonth, 2, 3, 1)) return;

    gotoXY(40, 8);
    if(!getString(endDay, 2, 3, 1)) return;
    // ��ʽ���� startTime, endTime
    sprintf(startTime, "%04s%02s%02s", startYear, startMonth, startDay);
    sprintf(endTime, "%04s%02s%02s", endYear, endMonth, endDay);

    LinkList *billNode = billHead->nxt;
    Bill *bill;

    system("cls");
    printf("------------------------------------------------------------------\n");
    printf("                             ��ѯ���\n");
    printf("------------------------------------------------------------------\n");
    printf("��ˮ��                      ����Ա���  ̨�����  ʱ��      ���\n");
    putchar('\n');

    // ����
    int total = 0;
    while(billNode != NULL)
    {
        bill = (Bill*)billNode->data;
        if(strcmp(startTime, bill->time) <= 0 && strcmp(endTime, bill->time) >= 0) 
        {
            printBill(bill);
            total += bill->total; //ͳ���ܽ��
        }
        billNode = billNode->nxt;
    }
    putchar('\n');
    printf("------------------------------------------------------------------");

    gotoXY(71, 6);
    printf("�ܽ�%d", total);
    getchar();
}
