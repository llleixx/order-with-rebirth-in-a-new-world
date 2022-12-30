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

            // MD5 加密，passwd 转化为本身的 md5 值
            MD5Get(passwd);

            // 查找用户
            LinkList *staffNode = staffHead->nxt;
            Staff *staff;
            bool flag = false; // 用于记录是否找到

            while (staffNode != NULL)
            {
                staff = (Staff*)staffNode->data;
                // 匹配用户名与 MD5 加密
                if(staff->id == id && strcmp(staff->passwd, passwd) == 0)
                {
                    memcpy(curStaff, staff, sizeof(Staff));
                    flag = true;
                    break;
                }
                staffNode = staffNode->nxt;
            }
            // 清空 用户名和密码显示

            // 找到了
            if (flag) break;
            else
            {
                gotoXY(55, 6);
			    printf("用户名不存在或密码错误");
                getch();
                // 清空错误信息和用户名及密码显示
                clear(55, 6, 22);
                clear(20, 7, 20);
                clear(21, 8, 23);
            }
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