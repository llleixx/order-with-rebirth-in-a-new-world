#include "login.h"
#include "file.h"
#include "list.h"
#include "common.h"
#include "admin.h"
#include "waiter.h"
#include "manager.h"


extern LinkList *staffHead, *tabelHead, *billHead;
extern int staffLen, tabelLen, billLen;
Staff *curStaff;

/// @brief ��¼
void login()
{
    curStaff = (Staff*)malloc(sizeof(Staff));
    system("cls");
    while(true)
    {
        system("cls");
        // ����
        printf("--------------------------------------------------\n");
        printf("             ����������֮��Ҫ���ϵͳ\n");
        printf("--------------------------------------------------\n");
        gotoXY(0, 15);
        printf("-------------------------------------------------\n");

        // ��¼
        char ID[5], passwd[17];
        while(1)
        {
            gotoXY(20,7);
            printf("�û�����");
            if(!getString(ID, 4, 3, 1)) return;
            int id = atoi(ID);

            gotoXY(21,8);
            printf(" ����: ");
            if(!getString(passwd, 16, 1, 0)) return;
            LinkList *staffNode = staffHead->nxt;
            Staff *staff;
            bool flag = false; // ���ڼ�¼�Ƿ��ҵ�

            while (staffNode != NULL)
            {
                staff = (Staff*)staffNode->data;
                if(staff->id == id && strcmp(staff->passwd, passwd) == 0)
                {
                    memcpy(curStaff, staff, sizeof(Staff));
                    flag = true;
                    break;
                }
                staffNode = staffNode->nxt;
            }
            // ��� �û�����������ʾ
            clear(20, 7, 12);
            clear(21, 8, 23);
            // û�ҵ�
            if (flag) break;
        }

        // ��ת����
        switch(curStaff->role)
        {
            case 0:
                adminView();
                break;
            case 1:
                waiterView();
                break;
            case 2:
                managerView();
                break;
            default:
                perror("login");
        }
    }
}