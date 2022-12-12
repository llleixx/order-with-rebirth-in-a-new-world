#include "menu.h"
#include "common.h"
#include "file.h"
#include "list.h"



extern LinkList *menuHead;

/// @brief 增加菜谱
void addMenu()
{
	system("cls");
	char name[17];
	char price[6];
	Menu *menu = NULL;

    printf("--------------------------------------------------\n");
    printf("                     添加菜谱\n");
    printf("--------------------------------------------------\n");
    gotoXY(0, 15);
    printf("-------------------------------------------------\n");

	gotoXY(18, 6);
	printf("请输入菜名：");
	if (!getString(name, 16, 4, 1)) return;

	gotoXY(18, 7);
	printf("请输入菜的价格: ");
	if (!getString(price, 5, 3, 1)) return;

	gotoXY(55, 6);
	printf("是否保存？");
	gotoXY(55, 7);
	printf("0：取消 1：保存");
	gotoXY(55, 8);
	char ch = getChar('0', '1');
	if (!ch) return;
	if (ch == '1')
	{
		menu = (Menu *)malloc(sizeof(Menu));
		memset(menu, 0, sizeof(Menu));
		strcpy(menu->name, name); // 把名字传进去
		menu->price = atoi(price);	
		if (menuHead->nxt != NULL) // 如果菜单当前有菜
		{
			Menu *firstMenu = (Menu*)menuHead->nxt->data;
			menu->id = firstMenu->id + 1; // 传id
		} 
		else menu->id = 1000;  // 如果当前菜单没菜
		addNode(menuHead, menu); // 存链表
		writeFile("menu.txt", menuHead, sizeof(Menu)); // 写入文件
		gotoXY(55, 9);
		printf("恭喜你保存成功\n");
		getchar();
	}
	else
	{
		gotoXY(55, 10);
		printf("保存失败\n");
		getchar(); 
	}
}

/// @brief 修改菜谱
void modifyMenu()
{
	while (1)
	{
		system("cls");
		char name[17];
		char price[6];
		char ID[5];


        printf("--------------------------------------------------\n");
        printf("                     修改菜谱\n");
        printf("--------------------------------------------------\n");
        gotoXY(0, 15);
        printf("-------------------------------------------------\n");

        gotoXY(18, 6);
        printf("菜谱编号：");

        if(!getString(ID, 4, 3, 1)) return;
        int id = atoi(ID);

		// 遍历菜谱
		LinkList *menuNode = menuHead->nxt;
		Menu *menu;
		while (menuNode != NULL)
		{
			menu = (Menu*)menuNode->data;
			menuNode = menuNode->nxt;
			if (menu->id == id)
			{
				gotoXY(18, 7);
				printf("菜名：");
				if (!getString(name, 16, 4, 1))
					return;
				gotoXY(18, 8);
				printf("价格: ");
				if (!getString(price, 5, 3, 1))
					return;
				gotoXY(18, 9);

				gotoXY(55, 6);
				printf("是否保存？");
				gotoXY(55, 7);
				printf("0：取消 1：保存");
				gotoXY(55, 8);
				char ch = getChar('0', '1');
				if (!ch)
					return;
				if (ch == '1')
				{
					strcpy(menu->name, name);
					menu->price = atoi(price);
					writeFile("menu.txt", menuHead, sizeof(Menu)); // 写入文件
					gotoXY(55, 9);
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
				break;
			}
		}
		gotoXY(55, 6);
		printf("此菜谱不存在！");
		getchar();
	}
}

/// @brief 删除菜谱
void deleteMenu()
{
	while (1) // 避免输入空的菜谱ID而直接退出
	{
		system("cls");

		char ID[5];

		printf("--------------------------------------------------\n");
        printf("                     删除菜谱\n");
        printf("--------------------------------------------------\n");
        printf("编号          菜名                  价格       \n");
        putchar('\n');
        printList(menuHead, printMenu);
        putchar('\n');
        printf("--------------------------------------------------");

        // 显示 bug
        gotoXY(55, 6);

        printf("菜谱编号：");

		if (!getString(ID, 4, 3, 1)) return;
		int id = atoi(ID);

		LinkList *menuNode = menuHead->nxt;
		Menu *menu;
		
		while(menuNode != NULL)
		{
			menu = (Menu*)menuNode->data;
			if (menu->id == id)
			{
				gotoXY(55, 7);
				printf("是否保存？");
				gotoXY(55, 8);
				printf("0：取消 1：保存");
				gotoXY(55, 9);
				char ch = getChar('0', '1');
				if (!ch) return;
				if (ch == '1')
				{
					deleteNode(menuHead, menuNode); // 删除节点
					writeFile("menu.txt", menuHead, sizeof(Menu));
					gotoXY(55, 10);
					printf("恭喜你删除成功\n");
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
			menuNode = menuNode->nxt;
		}
		gotoXY(55, 7);
		printf("此菜谱不存在！");
		getchar();
		// 继续while循环
	}
}

/// @brief 查询菜谱
void findMenu()
{
	while(1)
	{
		system("cls");

		char ID[5];

		printf("--------------------------------------------------\n");
        printf("                     查询菜谱\n");
        printf("--------------------------------------------------\n");
        printf("编号          菜名                  价格       \n");
        putchar('\n');
        printList(menuHead, printMenu);
        putchar('\n');
        printf("--------------------------------------------------");

        // 显示 bug
        gotoXY(55, 6);

        printf("菜谱编号：");

		if (!getString(ID, 4, 3, 1)) return;
		int id = atoi(ID);

		// 遍历菜谱
		LinkList *menuNode = menuHead->nxt;
		Menu *menu;
		while (menuNode != NULL)
		{
			menu = (Menu*)menuNode->data;
			menuNode = menuNode->nxt;
			if (menu->id == id)
			{
				printf("--------------------------------------------------\n");
				printf("                     查询结果\n");
				printf("--------------------------------------------------\n");
				printf("编号          菜名                  价格       \n");
				putchar('\n');
				(*printMenu)(menu);
				putchar('\n');
				printf("--------------------------------------------------");
				getchar();
				return;
			}
		}
		gotoXY(55, 7);
		printf("此菜谱不存在！");
		getchar();
	}
}

/// @brief 菜谱界面
void menuView()
{
	while(true)
	{
        system("cls");
        printf("--------------------------------------------------\n");
        printf("                     菜谱管理\n");
        printf("--------------------------------------------------\n");
        gotoXY(0, 15);
        printf("-------------------------------------------------\n");
        gotoXY(0,6);
        printf("                  1: 添加菜谱\n");
        printf("                  2: 修改菜谱\n");
        printf("                  3: 删除菜谱\n");
        printf("                  4: 查询菜谱\n");
        printf("                  0: 返回\n");

        gotoXY(55, 6);
        printf("请输入你的选择：");
        char ch = getChar('0','4');

		switch(ch)
		{
			case '1':
			{
				addMenu();
				break;
			}
			case '2':
			{
				modifyMenu();
				break;
			}
			case '3':
			{
				deleteMenu();
				break;
			}
			case '4':
			{
				findMenu();
				break;
			}
			case '0':
			{
				return;
			}
		}
	}
}