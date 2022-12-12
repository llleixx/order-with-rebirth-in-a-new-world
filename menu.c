#include "menu.h"
#include "common.h"
#include "file.h"
#include "list.h"



extern LinkList *menuHead;

/// @brief ���Ӳ���
void addMenu()
{
	system("cls");
	char name[17];
	char price[6];
	Menu *menu = NULL;

    printf("--------------------------------------------------\n");
    printf("                     ��Ӳ���\n");
    printf("--------------------------------------------------\n");
    gotoXY(0, 15);
    printf("-------------------------------------------------\n");

	gotoXY(18, 6);
	printf("�����������");
	if (!getString(name, 16, 4, 1)) return;

	gotoXY(18, 7);
	printf("������˵ļ۸�: ");
	if (!getString(price, 5, 3, 1)) return;

	gotoXY(55, 6);
	printf("�Ƿ񱣴棿");
	gotoXY(55, 7);
	printf("0��ȡ�� 1������");
	gotoXY(55, 8);
	char ch = getChar('0', '1');
	if (!ch) return;
	if (ch == '1')
	{
		menu = (Menu *)malloc(sizeof(Menu));
		memset(menu, 0, sizeof(Menu));
		strcpy(menu->name, name); // �����ִ���ȥ
		menu->price = atoi(price);	
		if (menuHead->nxt != NULL) // ����˵���ǰ�в�
		{
			Menu *firstMenu = (Menu*)menuHead->nxt->data;
			menu->id = firstMenu->id + 1; // ��id
		} 
		else menu->id = 1000;  // �����ǰ�˵�û��
		addNode(menuHead, menu); // ������
		writeFile("menu.txt", menuHead, sizeof(Menu)); // д���ļ�
		gotoXY(55, 9);
		printf("��ϲ�㱣��ɹ�\n");
		getchar();
	}
	else
	{
		gotoXY(55, 10);
		printf("����ʧ��\n");
		getchar(); 
	}
}

/// @brief �޸Ĳ���
void modifyMenu()
{
	while (1)
	{
		system("cls");
		char name[17];
		char price[6];
		char ID[5];


        printf("--------------------------------------------------\n");
        printf("                     �޸Ĳ���\n");
        printf("--------------------------------------------------\n");
        gotoXY(0, 15);
        printf("-------------------------------------------------\n");

        gotoXY(18, 6);
        printf("���ױ�ţ�");

        if(!getString(ID, 4, 3, 1)) return;
        int id = atoi(ID);

		// ��������
		LinkList *menuNode = menuHead->nxt;
		Menu *menu;
		while (menuNode != NULL)
		{
			menu = (Menu*)menuNode->data;
			menuNode = menuNode->nxt;
			if (menu->id == id)
			{
				gotoXY(18, 7);
				printf("������");
				if (!getString(name, 16, 4, 1))
					return;
				gotoXY(18, 8);
				printf("�۸�: ");
				if (!getString(price, 5, 3, 1))
					return;
				gotoXY(18, 9);

				gotoXY(55, 6);
				printf("�Ƿ񱣴棿");
				gotoXY(55, 7);
				printf("0��ȡ�� 1������");
				gotoXY(55, 8);
				char ch = getChar('0', '1');
				if (!ch)
					return;
				if (ch == '1')
				{
					strcpy(menu->name, name);
					menu->price = atoi(price);
					writeFile("menu.txt", menuHead, sizeof(Menu)); // д���ļ�
					gotoXY(55, 9);
					printf("��ϲ�㱣��ɹ�\n");
					getchar();
					return;
				}
				else
				{
					gotoXY(55, 9);
					printf("����ʧ��\n");
					getchar(); 
					return;
				}
				break;
			}
		}
		gotoXY(55, 6);
		printf("�˲��ײ����ڣ�");
		getchar();
	}
}

/// @brief ɾ������
void deleteMenu()
{
	while (1) // ��������յĲ���ID��ֱ���˳�
	{
		system("cls");

		char ID[5];

		printf("--------------------------------------------------\n");
        printf("                     ɾ������\n");
        printf("--------------------------------------------------\n");
        printf("���          ����                  �۸�       \n");
        putchar('\n');
        printList(menuHead, printMenu);
        putchar('\n');
        printf("--------------------------------------------------");

        // ��ʾ bug
        gotoXY(55, 6);

        printf("���ױ�ţ�");

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
				printf("�Ƿ񱣴棿");
				gotoXY(55, 8);
				printf("0��ȡ�� 1������");
				gotoXY(55, 9);
				char ch = getChar('0', '1');
				if (!ch) return;
				if (ch == '1')
				{
					deleteNode(menuHead, menuNode); // ɾ���ڵ�
					writeFile("menu.txt", menuHead, sizeof(Menu));
					gotoXY(55, 10);
					printf("��ϲ��ɾ���ɹ�\n");
					getchar();
					return;
				}
				else
				{
					gotoXY(55, 10);
					printf("����ʧ��\n");
					getchar();
					return;
				}
			}
			menuNode = menuNode->nxt;
		}
		gotoXY(55, 7);
		printf("�˲��ײ����ڣ�");
		getchar();
		// ����whileѭ��
	}
}

/// @brief ��ѯ����
void findMenu()
{
	while(1)
	{
		system("cls");

		char ID[5];

		printf("--------------------------------------------------\n");
        printf("                     ��ѯ����\n");
        printf("--------------------------------------------------\n");
        printf("���          ����                  �۸�       \n");
        putchar('\n');
        printList(menuHead, printMenu);
        putchar('\n');
        printf("--------------------------------------------------");

        // ��ʾ bug
        gotoXY(55, 6);

        printf("���ױ�ţ�");

		if (!getString(ID, 4, 3, 1)) return;
		int id = atoi(ID);

		// ��������
		LinkList *menuNode = menuHead->nxt;
		Menu *menu;
		while (menuNode != NULL)
		{
			menu = (Menu*)menuNode->data;
			menuNode = menuNode->nxt;
			if (menu->id == id)
			{
				printf("--------------------------------------------------\n");
				printf("                     ��ѯ���\n");
				printf("--------------------------------------------------\n");
				printf("���          ����                  �۸�       \n");
				putchar('\n');
				(*printMenu)(menu);
				putchar('\n');
				printf("--------------------------------------------------");
				getchar();
				return;
			}
		}
		gotoXY(55, 7);
		printf("�˲��ײ����ڣ�");
		getchar();
	}
}

/// @brief ���׽���
void menuView()
{
	while(true)
	{
        system("cls");
        printf("--------------------------------------------------\n");
        printf("                     ���׹���\n");
        printf("--------------------------------------------------\n");
        gotoXY(0, 15);
        printf("-------------------------------------------------\n");
        gotoXY(0,6);
        printf("                  1: ��Ӳ���\n");
        printf("                  2: �޸Ĳ���\n");
        printf("                  3: ɾ������\n");
        printf("                  4: ��ѯ����\n");
        printf("                  0: ����\n");

        gotoXY(55, 6);
        printf("���������ѡ��");
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