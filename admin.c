#include "admin.h"
#include "file.h"
#include "list.h"
#include "common.h"

/// @brief 管理员的主界面
void adminView()
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
        printf("                  1: 人员管理\n");
        printf("                  2: 台桌管理\n");
        printf("                  3: 菜谱管理\n");
        printf("                  0: 返回\n");

        gotoXY(55, 6);
        printf("请输入你的选择：");
        char ch = getChar('0', '3');
        if(!ch) return;
        switch (ch)
        {
            case '1':
            {
                staffView();
                break;
            }
            case '2':
            {
                tableView();
                break;
            }
            case '3':
            {
                menuView();
                break;
            }
            case '0':
            {
                return;
            }
        }
    }
}