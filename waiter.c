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
        printf("             异世界重生之我要点菜系统\n");
        printf("--------------------------------------------------\n");
        gotoXY(0, 15);
        printf("-------------------------------------------------\n");
        gotoXY(0, 6);
        printf("                  1: 开桌\n");
        printf("                  2: 点菜\n");
        printf("                  3: 账单查询\n");
        printf("                  4：结账\n");
        printf("                  0: 返回\n");

        gotoXY(55, 6);
        printf("请输入你的选择：");
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

void openDesk()//开桌
{
    while(true)
    {
        system("cls");
        char ID[5];  // 输入的开桌号
        Bill *bill;  // 生成的账单号
        char curTime[15] = {0};

        LinkList *tableNode = tableHead->nxt;
        Table *table;
        
        // 打印界面
        printf("--------------------------------------------------\n");
        printf("                     开桌\n");
        printf("--------------------------------------------------\n");
        printf("编号    状态    描述\n");
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
        printf("台桌编号：");
        if(!getString(ID, 4, 3, 1)) return;

        int id = atoi(ID);

        tableNode = tableHead->nxt;

        bool flag = false;
        
        while (tableNode != NULL)
        {
            table = (Table*)tableNode->data;
            if(table->id == id)
            {
                // 桌子未处于空闲状态
                if(table->flag != 0)
                {
                    flag = true;
                    break;
                }

                gotoXY(55, 7);
                printf("占用或预定:");
                gotoXY(55, 8);
                printf("1:占用 2:预定");
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
                printf("%s", "操作成功");
                getchar();
                return;
            }
            tableNode = tableNode->nxt;
        }

        gotoXY(55, 7);
        flag ? printf("该台桌未处于空闲状态") : printf("此桌号不存在");
        getchar();
    }
}

void orderDish()
{
    while (true)
    {
        system("cls");

        // 遍历链表
        LinkList *billNode;
        Bill *bill;
        LinkList *menuNode;
        Menu *menu;
        LinkList *orderNode;
        Order *order;
        LinkList *tableNode;
        Table *table;

        // 打印界面
        printf("--------------------------------------------------\n");
        printf("                     点菜\n");
        printf("--------------------------------------------------\n");
        printf("编号    状态    描述\n");
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

        // menu 清空
        menuNode = menuHead->nxt;
        while(menuNode != NULL)
        {
            menu = (Menu*)menuNode->data;
            menu->num = 0;
            menuNode = menuNode->nxt;
        }        

        char ID[5];

        gotoXY(55, 6);
        printf("台桌编号：");
        if(!getString(ID, 4, 3, 1)) return;
        int id = atoi(ID);


        // 读取当前台桌已点菜单
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
                break;  // 找到即退出
            }
            billNode = billNode->nxt;
        }

        // 遍历到了结尾，即没找到
        if (billNode == NULL)
        {
            gotoXY(55, 7);
            printf("该台桌不存在或未开桌");
            getchar();
            continue;
        }

        // 点菜
        while(true)
        {
            // 打印菜单
            system("cls");
            printf("--------------------------------------------------\n");
            printf("                       菜单\n");
            printf("--------------------------------------------------\n");
            printf("编号          菜名                  价格     已点份数\n");
            putchar('\n');
            printList(menuHead, printMenu1);
            putchar('\n');
            printf("--------------------------------------------------");

            gotoXY(55, 4);
            printf("目前总金额：%d", bill->total);

            gotoXY(55, 6);
            printf("菜谱编号：");
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
                    printf("1：加菜 2：减菜");
                    printf("   ");
                    char ch = getChar('1', '2');
                    if(!ch) return;

                    gotoXY(55, 8);
                    printf("份数：");
                    char numStr[6];
                    if(!getString(numStr, 5, 3, 1)) return;

                    int num = atoi(numStr);

                    if(ch == '2' && menu->num < num)
                    {
                        gotoXY(55, 9);
                        printf("菜数不能为负数！");
                        getchar();
                        break;
                    }

                    // 生成新的 order
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
                    printf("点菜成功！");
                    getchar();
                    break;
                }
                menuNode = menuNode->nxt;
            }

            // 遍历到了结尾，即没找到
            if(menuNode == NULL)
            {
                gotoXY(55, 7);
                printf("此菜谱不存在！");
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

        // 打印界面
        printf("------------------------------------------------------------------\n");
        printf("                             结账\n");
        printf("------------------------------------------------------------------\n");
        printf("流水号                      服务员编号  台桌编号  时间      金额\n");
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
        printf("台桌编号：");

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
                printf("                       订单\n");
                printf("-------------------------------------------------------------------\n");
                printf("流水号                      菜名              价格   份数   总价\n");
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
                printf("应付金额：%d", bill->total);
                gotoXY(72, 7);
                printf("确定结账？");
                gotoXY(72, 8);
                printf("0：取消 1：确定");
                gotoXY(72, 9);
                char ch = getChar('0', '1');
                if (!ch) return;
                if(ch == '1')
                {
                    bill->flag = 1;
                    writeFile("bill.txt", billHead, sizeof(Bill));

                    // 改变桌子状态
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
                    printf("结账成功！\n");
                    getchar();
                    return;
                }
                else
                {
                    gotoXY(72, 10);
                    printf("结账失败！\n");
                    getchar();
                    return;
                }
                break;
            }
            billNode = billNode->nxt;
        }
        gotoXY(71, 7);
        printf("此桌并不需要结账！");
        getchar();
    }
}