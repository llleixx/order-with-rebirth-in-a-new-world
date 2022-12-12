#include "table.h"
#include "list.h"
#include "common.h"
#include "file.h"

extern LinkList *tableHead; // 台桌头结点

/// @brief 台桌界面
void tableView()
{
    while(true)
    {
        system("cls");

        printf("--------------------------------------------------\n");
        printf("                     台桌管理\n");
        printf("--------------------------------------------------\n");
        gotoXY(0, 15);
        printf("-------------------------------------------------\n");
        gotoXY(0,6);
        printf("                  1: 添加台桌\n");
        printf("                  2: 修改台桌\n");
        printf("                  3: 删除台桌\n");
        printf("                  4: 查询台桌\n");
        printf("                  0: 返回\n");

        gotoXY(55, 6);
        printf("请输入你的选择：");
        char ch = getChar('0','4');
        if(!ch) return;
        switch (ch)
        {
            case '1':
                addTable();
                break;
            case '2':
                modifyTable();
                break;
            case '3':
                deleteTable();
                break;
            case '4':
                findTable();
                break;
            case '0':
                return;
        }
    }
}


/// @brief 添加台桌
void addTable()
{
    system("cls");

	char ch;
	char ID[5];
	char flag;
	char desc[25];

	Table *table; // 指向新的桌

    printf("--------------------------------------------------\n");
    printf("                     添加台桌\n");
    printf("--------------------------------------------------\n");
    gotoXY(0, 15);
    printf("-------------------------------------------------\n");
	
	gotoXY(55, 6);
	printf("0 空闲 1 占用 2 预定 3 维护");

	gotoXY(18, 6);
	printf("请输入台桌状态: ");

	flag = getChar('0', '3');
	if (!flag) return;

    clear(55, 6, 30);

	gotoXY(18, 7);
	printf("请进行描述(中文)： ");
	if(!getString(desc, 24, 4, 1)) return;

	gotoXY(55, 6);
	printf("是否保存？");
	gotoXY(55, 7);
	printf("0：取消 1：保存");
	gotoXY(55, 8);

	ch = getChar('0', '1');
	if (!ch) return;

	if (ch == '1')
	{
        table = (Table*)malloc(sizeof(Table));
        if (tableHead->nxt != NULL) // 如果当前存在台桌
        {
            Table *firstTable = (Table*)tableHead->nxt->data;
            table->id = firstTable->id + 1;
        }
        else table->id = 1000;  // 如果当前不存在台桌
        table->flag = flag - 48;
        strcpy(table->desc, desc);
		addNode(tableHead, table);
		writeFile("table.txt", tableHead, sizeof(Table));
		gotoXY(55, 9);
		printf("恭喜你保存成功\n");
        gotoXY(55, 10);
        printf("新台桌的编号为：%d", table->id);
		getchar(); // 暂停以显示信息
        return;
	}
	else
	{
		gotoXY(55, 9);
		printf("保存失败\n");
		getchar(); // 暂停以显示信息
		return;
	}
}

/// @brief 修改台桌
void modifyTable()
{
    while(true)
    {
        system("cls");
        char flag;
        char desc[25];
        char ID[5];

        printf("--------------------------------------------------\n");
        printf("                     修改台桌\n");
        printf("--------------------------------------------------\n");
        gotoXY(0, 15);
        printf("-------------------------------------------------\n");

        gotoXY(18, 6);
        printf("台桌编号: ");
        if (!getString(ID, 4, 3, 1)) return;
        int id = atoi(ID);

        LinkList *tableNode = tableHead->nxt;
        Table *table;

        while (tableNode != NULL)
        {
            table = (Table*)tableNode->data;
            if (table->id == id)
            {
                gotoXY(18, 7);
                printf("请输入状态：");
                gotoXY(55, 6);
                printf("0 空闲 1 占用 2 预定 3 维护");
                gotoXY(30, 7);
                flag = getChar('0', '3');
                if (!flag) return;

                clear(55, 6, 30);

                gotoXY(18, 8);
                printf("请进行描述：");
                if (!getString(desc, 24, 4, 1)) return;

                gotoXY(55, 6);
                printf("是否保存？");
                gotoXY(55, 7);
                printf("0：取消 1：保存");
                gotoXY(55, 8);
                char chr = getChar('0', '1');
                if(!chr) return;

                if (chr == '1')
                {
                    table->flag = flag - 48;
                    strcpy(table->desc, desc);
                    gotoXY(55, 9);
                    writeFile("table.txt", tableHead, sizeof(Table));
                    printf("恭喜你保存成功\n");
                    getchar();
                    return;
                }
                else
                {
                    gotoXY(55, 9);
                    printf("保存失败\n");
                    getchar();
                    return;
                }
            }
            tableNode = tableNode->nxt;
        }

        gotoXY(55, 6);
        printf("此台桌不存在！");
        getchar();
    }
}

/// @brief 删除台桌
void deleteTable()
{
    while(true)
    {
        system("cls");
        char chr;
        char ID[5];

        printf("--------------------------------------------------\n");
        printf("                     删除台桌\n");
        printf("--------------------------------------------------\n");
        printf("编号    状态    描述\n");
        putchar('\n');
        printList(tableHead, printTable);
        putchar('\n');
        printf("--------------------------------------------------");

        gotoXY(55, 6);
        printf("台桌编号：");

        if(!getString(ID, 4, 3, 1)) return;
        int id = atoi(ID);

        LinkList *tableNode = tableHead->nxt;
        Table *table;

        while(tableNode != NULL)
        {
            table = (Table*)tableNode->data;
            if(table->id == id)
            {
                gotoXY(55, 7);
                printf("是否保存？");
                gotoXY(55, 8);
                printf("0：取消 1：保存");
                gotoXY(55, 9);
                chr = getChar('0', '1');
                if (!chr) return;

                if (chr == '1')
                {
                    deleteNode(tableHead, tableNode);
                    gotoXY(55, 10);
                    writeFile("table.txt", tableHead, sizeof(Table));
                    printf("恭喜你保存成功\n");
                    getchar();
                    return;
                }
                else
                {
                    gotoXY(55, 10);
                    printf("保存失败\n");
                    getchar();
                    return;
                }
            }
            tableNode = tableNode->nxt;
        }
        gotoXY(55, 7);
        printf("此台桌不存在！");
        getchar();
    }
}

/// @brief 查询台桌
void findTable()
{
    while(true)
    {
        system("cls");

        char ID[5];
        Table *table;
        printf("--------------------------------------------------\n");
        printf("                     查询台桌\n");
        printf("--------------------------------------------------\n");
        printf("编号    状态    描述\n");
        putchar('\n');
        printList(tableHead, printTable);
        putchar('\n');
        printf("--------------------------------------------------");

        gotoXY(55, 6);
        printf("台桌编号：");
        if(!getString(ID, 4, 3, 1)) return;

        int id = atoi(ID);

        LinkList *tableNode = tableHead->nxt;
        while(tableNode != NULL)
        {
            table = (Table*)tableNode->data;
            if(table->id == id)
            {
                system("cls");
                printf("--------------------------------------------------\n");
                printf("                     查询结果\n");
                printf("--------------------------------------------------\n");
                printf("编号    状态    描述\n");
                putchar('\n');
                printTable(table);
                putchar('\n');
                printf("--------------------------------------------------");
                getchar();
                return;
            }
            tableNode = tableNode->nxt;
        }
        gotoXY(55, 7);
        printf("此台桌不存在！");
        getchar();
    }
}
