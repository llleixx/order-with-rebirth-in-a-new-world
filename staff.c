#include "staff.h"
#include "list.h"
#include "file.h"
#include "common.h"

extern int staffLen;
extern LinkList *staffHead;

/// @brief ������Ա
void addStaff()
{
    system("cls");

    // �����û�����Ϣ
    char passwd1[17], passwd2[17];
    Staff *staff;
    char name[10];
    int role; 

    // ����
    printf("--------------------------------------------------\n");
    printf("                     �����Ա\n");
    printf("--------------------------------------------------\n");
    gotoXY(0, 15);
    printf("-------------------------------------------------\n");


    gotoXY(18, 6);

    // �����û���
    printf("������������");

    if(!getString(name, 8, 2, 1)) return;

    putchar('\n');

    // ��������
    while(1)
    {
        gotoXY(18, 7);
		printf("���������룺");
		if(!getString(passwd1, 16, 3, 0)) return;

		gotoXY(18, 8);
		printf("��ȷ�����룺");
		if(!getString(passwd2, 16, 3, 0)) return;
		if (strcmp(passwd1, passwd2) != 0)
		{
			gotoXY(55, 6);
			printf("�������벻��ͬ������������");
            getch();
            clear(18, 7, 24);
            clear(18, 8, 24);
            clear(55, 6, 26);
			continue;
		}
		else
		{
            break;
        }
    }
    gotoXY(18, 9);
	printf("������ְλ��");
	gotoXY(55, 6);
	printf("0: ����Ա 1: ����Ա 2: ����");
	gotoXY(30, 9);
	role = getChar('0', '2');
    if(!role) return;
	
    clear(55, 6, 30);

	gotoXY(55, 6);
	printf("�Ƿ񱣴棿");
	gotoXY(55, 7);
	printf("0��ȡ�� 1������");
	gotoXY(55, 8);
	char ch = getChar('0', '1');
    if(!ch) return;
    if (ch == '1')
	{
        staff = (Staff*)malloc(sizeof(Staff));
        memset(staff, 0, sizeof(Staff));
        if(staffHead->nxt != NULL)
        {
            Staff *firstStaff = (Staff*)staffHead->nxt->data;
            staff->id = firstStaff->id + 1;
        }
        else staff->id = 1000;

        MD5Get(passwd1);
        strcpy(staff->passwd, passwd1);
        strcpy(staff->name, name);
        staff->role = role - 48;
		addNode(staffHead, staff);
		writeFile("staff.txt", staffHead, sizeof(Staff));
		gotoXY(55, 9);
		printf("��ϲ�㱣��ɹ�\n");
        gotoXY(55, 10);
        printf("��Ա���ı��Ϊ��%d", staff->id);
		getchar();  // ��ͣ����ʾ��Ϣ
	}
	else
	{
		gotoXY(55, 9);
		printf("����ʧ��\n");
        getchar(); //��ͣ����ʾ��Ϣ
		return;
	}
}

/// @brief �޸���Ա
void modifyStaff()
{
    while(true)
    {
        system("cls");
        char ID[5]; // ���� ID
        char name[13]; // Ҫ�޸ĵ��û���
        char passwd[17];
        char role;

        printf("--------------------------------------------------\n");
        printf("                     �޸���Ա\n");
        printf("--------------------------------------------------\n");
        gotoXY(0, 15);
        printf("-------------------------------------------------\n");

        gotoXY(18, 6);
        printf("�޸�Ա����ţ�");

        if(!getString(ID, 4, 3, 1)) return;
        int id = atoi(ID);

        LinkList *staffNode = staffHead->nxt;
        Staff *staff;
        while (staffNode != NULL)
        {
            staff = (Staff*)staffNode->data;
            if(staff->id == id)
            {
                // ������Ϣ
                gotoXY(18, 7);
                printf("������");
                if(!getString(name, 8, 2, 1)) return;
                gotoXY(18, 8);
                printf("���룺");
                if(!getString(passwd, 6, 3, 0)) return;
                gotoXY(18, 9);
                printf("ְλ��");
                gotoXY(55, 6);
                printf("0: ����Ա 1: ����Ա 2: ����");
                gotoXY(24, 9);
                role = getChar('0', '2');
                if(!role) return;
                
                clear(55, 6, 30);

                gotoXY(55, 6);
                printf("�Ƿ񱣴棿");
                gotoXY(55, 7);
                printf("0��ȡ�� 1������");
                gotoXY(55, 8);
                char ch = getChar('0', '1');    
                if(!ch) return;
                if(ch == '1')
                {
                    // ��������Ϣ�ŵ� staff �ڣ�������
                    gotoXY(55, 9);
                    printf("��ϲ�㱣��ɹ�\n");
                    staff->id = id;
                    strcpy(staff->name, name);
                    MD5Get(passwd);
                    strcpy(staff->passwd, passwd);
                    staff->role = role - '0';
                    writeFile("staff.txt", staffHead, sizeof(Staff));
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
            staffNode = staffNode->nxt;
        }
        // û��ƥ����Ϣ
        gotoXY(55, 6);
        printf("��Ա�������ڣ�");
        getchar();
    }
}

/// @brief ɾ����Ա
void deleteStaff()
{
    while(true)
    {
        system("cls");

        printf("--------------------------------------------------\n");
        printf("                     ɾ����Ա\n");
        printf("--------------------------------------------------\n");
        printf("���    ����            ְλ  \n");
        putchar('\n');
        printList(staffHead, printStaff);
        putchar('\n');
        printf("--------------------------------------------------");

        gotoXY(55, 6);

        printf("ɾ��Ա����ţ�");

        char ID[5];
        if(!getString(ID, 4, 3, 1)) return;
        int id = atoi(ID);

        LinkList *staffNode = staffHead->nxt;
        Staff *staff;
        while(staffNode != NULL)
        {
            staff = (Staff*)staffNode->data;
            if(staff->id == id)
            {
                gotoXY(55, 7);
                printf("�Ƿ񱣴�?");
                gotoXY(55, 8);
                printf("0��ȡ�� 1������");
                gotoXY(55, 9);
                char ch = getChar('0', '1');
                if(!ch) return;
                if(ch == '1')
                {
                    deleteNode(staffHead, staffNode);
                    gotoXY(55, 10);
                    writeFile("staff.txt", staffHead, sizeof(Staff));
                    printf("��ϲ�㱣��ɹ�");
                    getchar();
                    return;
                }
                else
                {
                    gotoXY(55, 10);
                    printf("����ʧ��");
                    getchar();
                    return;
                }
            }
            staffNode = staffNode->nxt;
        }
        // û���ҵ�
        gotoXY(55, 7);
		printf("��Ա�������ڣ�");
		getchar();
    }
}


/// @brief ��ѯ��Ա
void findStaff()
{
    while(true)
    {
        system("cls");
        char ID[5];  // ������ַ��� id

        // ����
        printf("--------------------------------------------------\n");
        printf("                     ��ѯ��Ա\n");
        printf("--------------------------------------------------\n");
        printf("���    ����            ְλ  \n");
        putchar('\n');
        printList(staffHead, printStaff);
        putchar('\n');
        printf("--------------------------------------------------");

        gotoXY(55, 6);
        printf("��ѯԱ����ţ�");
        if(!getString(ID, 4, 3, 1)) return;

        int id = atoi(ID);

        // ��������
        LinkList *staffNode = staffHead->nxt; 
        Staff *staff;

        while(staffNode != NULL)
        {
            staff = (Staff*)staffNode->data;
            if(staff->id == id)
            {
                system("cls");
                // ��ӡ
                printf("--------------------------------------------------\n");
                printf("                     ��ѯ���\n");
                printf("--------------------------------------------------\n");
                printf("���    ����            ְλ  \n");
                putchar('\n');
                (*printStaff)(staff);
                putchar('\n');
                printf("--------------------------------------------------");
                getchar();
                return;
            }
            staffNode = staffNode->nxt;
        }
        // û�ҵ�
        gotoXY(55, 7);
		printf("��Ա�������ڣ�");
		getchar();
    }
}

/// @brief ��Ա����
void staffView()
{
    while(true)
    {
        system("cls");
        printf("--------------------------------------------------\n");
        printf("                     ��Ա����\n");
        printf("--------------------------------------------------\n");
        gotoXY(0, 15);
        printf("-------------------------------------------------\n");
        gotoXY(0,6);
        printf("                  1: �����Ա\n");
        printf("                  2: �޸���Ա\n");
        printf("                  3: ɾ����Ա\n");
        printf("                  4: ��ѯ��Ա\n");
        printf("                  0: ����\n");

        gotoXY(55, 6);
        printf("���������ѡ��");
        char ch = getChar('0','4');
        if (!ch) return;
        switch(ch)
        {
            case '1':
            {	
                addStaff();
                break;
            }
            case '2':
            {
                modifyStaff();
                break;
            }
            case '3':
            {
                deleteStaff();
                break;
            }
            case '4':
            {
                findStaff();
                break;
            }	
            case '0':
            {
                return;
            }
        }
    }
}


