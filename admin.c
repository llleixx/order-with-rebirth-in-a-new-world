#include "admin.h"
#include "file.h"
#include "list.h"
#include "common.h"

/// @brief ����Ա��������
void adminView()
{
    while(true)
    {
        system("cls");
        printf("--------------------------------------------------\n");
        printf("             ����������֮��Ҫ���ϵͳ\n");
        printf("--------------------------------------------------\n");
        gotoXY(0, 15);
        printf("-------------------------------------------------\n");
        gotoXY(0, 6);
        printf("                  1: ��Ա����\n");
        printf("                  2: ̨������\n");
        printf("                  3: ���׹���\n");
        printf("                  0: ����\n");

        gotoXY(55, 6);
        printf("���������ѡ��");
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