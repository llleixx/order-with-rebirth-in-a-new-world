#include "table.h"
#include "list.h"
#include "common.h"
#include "file.h"

extern LinkList *tableHead; // ̨��ͷ���

/// @brief ̨������
void tableView()
{
    while(true)
    {
        system("cls");

        printf("--------------------------------------------------\n");
        printf("                     ̨������\n");
        printf("--------------------------------------------------\n");
        gotoXY(0, 15);
        printf("-------------------------------------------------\n");
        gotoXY(0,6);
        printf("                  1: ���̨��\n");
        printf("                  2: �޸�̨��\n");
        printf("                  3: ɾ��̨��\n");
        printf("                  4: ��ѯ̨��\n");
        printf("                  0: ����\n");

        gotoXY(55, 6);
        printf("���������ѡ��");
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


/// @brief ���̨��
void addTable()
{
    system("cls");

	char ch;
	char ID[5];
	char flag;
	char desc[25];

	Table *table; // ָ���µ���

    printf("--------------------------------------------------\n");
    printf("                     ���̨��\n");
    printf("--------------------------------------------------\n");
    gotoXY(0, 15);
    printf("-------------------------------------------------\n");
	
	gotoXY(55, 6);
	printf("0 ���� 1 ռ�� 2 Ԥ�� 3 ά��");

	gotoXY(18, 6);
	printf("������̨��״̬: ");

	flag = getChar('0', '3');
	if (!flag) return;

    clear(55, 6, 30);

	gotoXY(18, 7);
	printf("���������(����)�� ");
	if(!getString(desc, 24, 4, 1)) return;

	gotoXY(55, 6);
	printf("�Ƿ񱣴棿");
	gotoXY(55, 7);
	printf("0��ȡ�� 1������");
	gotoXY(55, 8);

	ch = getChar('0', '1');
	if (!ch) return;

	if (ch == '1')
	{
        table = (Table*)malloc(sizeof(Table));
        if (tableHead->nxt != NULL) // �����ǰ����̨��
        {
            Table *firstTable = (Table*)tableHead->nxt->data;
            table->id = firstTable->id + 1;
        }
        else table->id = 1000;  // �����ǰ������̨��
        table->flag = flag - 48;
        strcpy(table->desc, desc);
		addNode(tableHead, table);
		writeFile("table.txt", tableHead, sizeof(Table));
		gotoXY(55, 9);
		printf("��ϲ�㱣��ɹ�\n");
        gotoXY(55, 10);
        printf("��̨���ı��Ϊ��%d", table->id);
		getchar(); // ��ͣ����ʾ��Ϣ
        return;
	}
	else
	{
		gotoXY(55, 9);
		printf("����ʧ��\n");
		getchar(); // ��ͣ����ʾ��Ϣ
		return;
	}
}

/// @brief �޸�̨��
void modifyTable()
{
    while(true)
    {
        system("cls");
        char flag;
        char desc[25];
        char ID[5];

        printf("--------------------------------------------------\n");
        printf("                     �޸�̨��\n");
        printf("--------------------------------------------------\n");
        gotoXY(0, 15);
        printf("-------------------------------------------------\n");

        gotoXY(18, 6);
        printf("̨�����: ");
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
                printf("������״̬��");
                gotoXY(55, 6);
                printf("0 ���� 1 ռ�� 2 Ԥ�� 3 ά��");
                gotoXY(30, 7);
                flag = getChar('0', '3');
                if (!flag) return;

                clear(55, 6, 30);

                gotoXY(18, 8);
                printf("�����������");
                if (!getString(desc, 24, 4, 1)) return;

                gotoXY(55, 6);
                printf("�Ƿ񱣴棿");
                gotoXY(55, 7);
                printf("0��ȡ�� 1������");
                gotoXY(55, 8);
                char chr = getChar('0', '1');
                if(!chr) return;

                if (chr == '1')
                {
                    table->flag = flag - 48;
                    strcpy(table->desc, desc);
                    gotoXY(55, 9);
                    writeFile("table.txt", tableHead, sizeof(Table));
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
            }
            tableNode = tableNode->nxt;
        }

        gotoXY(55, 6);
        printf("��̨�������ڣ�");
        getchar();
    }
}

/// @brief ɾ��̨��
void deleteTable()
{
    while(true)
    {
        system("cls");
        char chr;
        char ID[5];

        printf("--------------------------------------------------\n");
        printf("                     ɾ��̨��\n");
        printf("--------------------------------------------------\n");
        printf("���    ״̬    ����\n");
        putchar('\n');
        printList(tableHead, printTable);
        putchar('\n');
        printf("--------------------------------------------------");

        gotoXY(55, 6);
        printf("̨����ţ�");

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
                printf("�Ƿ񱣴棿");
                gotoXY(55, 8);
                printf("0��ȡ�� 1������");
                gotoXY(55, 9);
                chr = getChar('0', '1');
                if (!chr) return;

                if (chr == '1')
                {
                    deleteNode(tableHead, tableNode);
                    gotoXY(55, 10);
                    writeFile("table.txt", tableHead, sizeof(Table));
                    printf("��ϲ�㱣��ɹ�\n");
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
            tableNode = tableNode->nxt;
        }
        gotoXY(55, 7);
        printf("��̨�������ڣ�");
        getchar();
    }
}

/// @brief ��ѯ̨��
void findTable()
{
    while(true)
    {
        system("cls");

        char ID[5];
        Table *table;
        printf("--------------------------------------------------\n");
        printf("                     ��ѯ̨��\n");
        printf("--------------------------------------------------\n");
        printf("���    ״̬    ����\n");
        putchar('\n');
        printList(tableHead, printTable);
        putchar('\n');
        printf("--------------------------------------------------");

        gotoXY(55, 6);
        printf("̨����ţ�");
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
                printf("                     ��ѯ���\n");
                printf("--------------------------------------------------\n");
                printf("���    ״̬    ����\n");
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
        printf("��̨�������ڣ�");
        getchar();
    }
}
