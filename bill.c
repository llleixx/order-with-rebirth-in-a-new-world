#include "bill.h"
#include "common.h"
#include "list.h"

extern LinkList *billHead;

/// @brief 账单查询界面
void billView()
{
    while(true)
    {
        system("cls");
        // 界面
        printf("--------------------------------------------------\n");
        printf("                      账单查询\n");
        printf("--------------------------------------------------\n");
        gotoXY(0, 15);
        printf("-------------------------------------------------\n");
        gotoXY(0,6);
        printf("                  1: 未付款查询\n");
        printf("                  2: 已付款查询\n");
        printf("                  0: 返回\n");

        gotoXY(55, 6);
        printf("请输入你的选择：");
        char ch = getChar('0', '2');

        if (!ch) return;
        switch (ch)
        {
            case '1':
            {
                queryUnpaidBill();
                break;
            }
            case '2':
            {
                queryPaidBill();
                break;
            }
            case '0':
            {
                return;
            }
        }
    }
}

/// @brief 查询未付款账单
void queryUnpaidBill()
{
    system("cls");

    // 存储输入的起始时间
    char startTime[9] = {0};
    char startYear[5];
    char startMonth[3];
    char startDay[3];
    // 存储输入的结束时间
    char endTime[9] = {0};
    char endYear[5];
    char endMonth[3];
    char endDay[3];


    printf("--------------------------------------------------\n");
    printf("                   未买单查询\n");
    printf("--------------------------------------------------\n");
    gotoXY(0, 15);
    printf("-------------------------------------------------\n");

	gotoXY(12, 6);
	printf("查询日期：");
	gotoXY(12, 8);
	printf("结束日期：");
	
	gotoXY(30,6);
	printf(" 年");
	gotoXY(37,6);
	printf("月");
	gotoXY(42,6);
	printf("日");
	gotoXY(30,8);
	printf(" 年");
	gotoXY(37,8);
	printf("月");
	gotoXY(42,8);
	printf("日");   
    
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

    // 格式化到 startTime，endTime
    sprintf(startTime, "%04s%02s%02s", startYear, startMonth, startDay);
    sprintf(endTime, "%04s%02s%02s", endYear, endMonth, endDay);

    LinkList *billNode = billHead->nxt;
    Bill *bill;

    system("cls");
    printf("------------------------------------------------------------------\n");
    printf("                             查询结果\n");
    printf("------------------------------------------------------------------\n");
    printf("流水号                      服务员编号  台桌编号  时间      金额\n");
    putchar('\n');
    // 遍历账单
    while(billNode != NULL)
    {
        bill = (Bill*)billNode->data;
        if(bill->flag == 0 && strcmp(startTime, bill->time) <= 0 && strcmp(endTime, bill->time) >= 0) 
        {
            printBill(bill);
        }
        billNode = billNode->nxt;
    }
    putchar('\n');
    printf("------------------------------------------------------------------");
    getchar();
}

/// @brief 查询付款账单
void queryPaidBill()
{
    system("cls");
    // 存储输入的起始时间
    char startTime[9] = {0};
    char startYear[5];
    char startMonth[3];
    char startDay[3];
    // 存储输入的结束日期
    char endTime[9] = {0};
    char endYear[5];
    char endMonth[3];
    char endDay[3];


    printf("--------------------------------------------------\n");
    printf("                   已买单查询\n");
    printf("--------------------------------------------------\n");
    gotoXY(0, 15);
    printf("-------------------------------------------------\n");

	gotoXY(12, 6);
	printf("查询日期：");
	gotoXY(12, 8);
	printf("结束日期：");
	
	gotoXY(30,6);
	printf(" 年");
	gotoXY(37,6);
	printf("月");
	gotoXY(42,6);
	printf("日");
	gotoXY(30,8);
	printf(" 年");
	gotoXY(37,8);
	printf("月");
	gotoXY(42,8);
	printf("日");   
    
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

    sprintf(startTime, "%04s%02s%02s", startYear, startMonth, startDay);
    sprintf(endTime, "%04s%02s%02s", endYear, endMonth, endDay);

    LinkList *billNode = billHead->nxt;
    Bill *bill;

    system("cls");
    printf("------------------------------------------------------------------\n");
    printf("                             查询结果\n");
    printf("------------------------------------------------------------------\n");
    printf("流水号                      服务员编号  台桌编号  时间      金额\n");
    putchar('\n');
    // 遍历账单
    while(billNode != NULL)
    {
        bill = (Bill*)billNode->data;
        if(bill->flag == 1 && strcmp(startTime, bill->time) <= 0 && strcmp(endTime, bill->time) >= 0) 
        {
            printBill(bill);
        }
        billNode = billNode->nxt;
    }
    putchar('\n');
    printf("------------------------------------------------------------------");
    getchar();
}
