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

/// @brief 登录
void login()
{
    curStaff = (Staff*)malloc(sizeof(Staff));
    system("cls");
    while(true)
    {
        system("cls");
        // 界面
        printf("--------------------------------------------------\n");
        printf("             异世界重生之我要点菜系统\n");
        printf("--------------------------------------------------\n");
        gotoXY(0, 15);
        printf("-------------------------------------------------\n");

        // 登录
        char ID[5], passwd[17];
        while(1)
        {
            gotoXY(20,7);
            printf("用户名：");
            if(!getString(ID, 4, 3, 1)) return;
            int id = atoi(ID);

            gotoXY(21,8);
            printf(" 密码: ");
            if(!getString(passwd, 16, 1, 0)) return;
            LinkList *staffNode = staffHead->nxt;
            Staff *staff;
            bool flag = false; // 用于记录是否找到

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
            // 清空 用户名和密码显示
            clear(20, 7, 12);
            clear(21, 8, 23);
            // 没找到
            if (flag) break;
        }

        // 跳转界面
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