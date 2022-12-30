#include "staff.h"
#include "list.h"
#include "file.h"
#include "common.h"

extern int staffLen;
extern LinkList *staffHead;

/// @brief 增加人员
void addStaff()
{
    system("cls");

    // 新增用户的信息
    char passwd1[17], passwd2[17];
    Staff *staff;
    char name[10];
    int role; 

    // 界面
    printf("--------------------------------------------------\n");
    printf("                     添加人员\n");
    printf("--------------------------------------------------\n");
    gotoXY(0, 15);
    printf("-------------------------------------------------\n");


    gotoXY(18, 6);

    // 输入用户名
    printf("请输入姓名：");

    if(!getString(name, 8, 2, 1)) return;

    putchar('\n');

    // 输入密码
    while(1)
    {
        gotoXY(18, 7);
		printf("请输入密码：");
		if(!getString(passwd1, 16, 3, 0)) return;

		gotoXY(18, 8);
		printf("请确认密码：");
		if(!getString(passwd2, 16, 3, 0)) return;
		if (strcmp(passwd1, passwd2) != 0)
		{
			gotoXY(55, 6);
			printf("两次密码不相同，请重新输入");
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
	printf("请输入职位：");
	gotoXY(55, 6);
	printf("0: 管理员 1: 服务员 2: 经理");
	gotoXY(30, 9);
	role = getChar('0', '2');
    if(!role) return;
	
    clear(55, 6, 30);

	gotoXY(55, 6);
	printf("是否保存？");
	gotoXY(55, 7);
	printf("0：取消 1：保存");
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
		printf("恭喜你保存成功\n");
        gotoXY(55, 10);
        printf("新员工的编号为：%d", staff->id);
		getchar();  // 暂停以显示信息
	}
	else
	{
		gotoXY(55, 9);
		printf("保存失败\n");
        getchar(); //暂停以显示信息
		return;
	}
}

/// @brief 修改人员
void modifyStaff()
{
    while(true)
    {
        system("cls");
        char ID[5]; // 输入 ID
        char name[13]; // 要修改的用户名
        char passwd[17];
        char role;

        printf("--------------------------------------------------\n");
        printf("                     修改人员\n");
        printf("--------------------------------------------------\n");
        gotoXY(0, 15);
        printf("-------------------------------------------------\n");

        gotoXY(18, 6);
        printf("修改员工编号：");

        if(!getString(ID, 4, 3, 1)) return;
        int id = atoi(ID);

        LinkList *staffNode = staffHead->nxt;
        Staff *staff;
        while (staffNode != NULL)
        {
            staff = (Staff*)staffNode->data;
            if(staff->id == id)
            {
                // 读入信息
                gotoXY(18, 7);
                printf("姓名：");
                if(!getString(name, 8, 2, 1)) return;
                gotoXY(18, 8);
                printf("密码：");
                if(!getString(passwd, 6, 3, 0)) return;
                gotoXY(18, 9);
                printf("职位：");
                gotoXY(55, 6);
                printf("0: 管理员 1: 服务员 2: 经理");
                gotoXY(24, 9);
                role = getChar('0', '2');
                if(!role) return;
                
                clear(55, 6, 30);

                gotoXY(55, 6);
                printf("是否保存？");
                gotoXY(55, 7);
                printf("0：取消 1：保存");
                gotoXY(55, 8);
                char ch = getChar('0', '1');    
                if(!ch) return;
                if(ch == '1')
                {
                    // 将输入信息放到 staff 内，并保存
                    gotoXY(55, 9);
                    printf("恭喜你保存成功\n");
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
                    printf("保存失败\n");
                    getchar();
                    return;
                }
            }
            staffNode = staffNode->nxt;
        }
        // 没有匹配信息
        gotoXY(55, 6);
        printf("此员工不存在！");
        getchar();
    }
}

/// @brief 删除人员
void deleteStaff()
{
    while(true)
    {
        system("cls");

        printf("--------------------------------------------------\n");
        printf("                     删除人员\n");
        printf("--------------------------------------------------\n");
        printf("编号    姓名            职位  \n");
        putchar('\n');
        printList(staffHead, printStaff);
        putchar('\n');
        printf("--------------------------------------------------");

        gotoXY(55, 6);

        printf("删除员工编号：");

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
                printf("是否保存?");
                gotoXY(55, 8);
                printf("0：取消 1：保存");
                gotoXY(55, 9);
                char ch = getChar('0', '1');
                if(!ch) return;
                if(ch == '1')
                {
                    deleteNode(staffHead, staffNode);
                    gotoXY(55, 10);
                    writeFile("staff.txt", staffHead, sizeof(Staff));
                    printf("恭喜你保存成功");
                    getchar();
                    return;
                }
                else
                {
                    gotoXY(55, 10);
                    printf("保存失败");
                    getchar();
                    return;
                }
            }
            staffNode = staffNode->nxt;
        }
        // 没有找到
        gotoXY(55, 7);
		printf("此员工不存在！");
		getchar();
    }
}


/// @brief 查询人员
void findStaff()
{
    while(true)
    {
        system("cls");
        char ID[5];  // 输入的字符串 id

        // 界面
        printf("--------------------------------------------------\n");
        printf("                     查询人员\n");
        printf("--------------------------------------------------\n");
        printf("编号    姓名            职位  \n");
        putchar('\n');
        printList(staffHead, printStaff);
        putchar('\n');
        printf("--------------------------------------------------");

        gotoXY(55, 6);
        printf("查询员工编号：");
        if(!getString(ID, 4, 3, 1)) return;

        int id = atoi(ID);

        // 遍历链表
        LinkList *staffNode = staffHead->nxt; 
        Staff *staff;

        while(staffNode != NULL)
        {
            staff = (Staff*)staffNode->data;
            if(staff->id == id)
            {
                system("cls");
                // 打印
                printf("--------------------------------------------------\n");
                printf("                     查询结果\n");
                printf("--------------------------------------------------\n");
                printf("编号    姓名            职位  \n");
                putchar('\n');
                (*printStaff)(staff);
                putchar('\n');
                printf("--------------------------------------------------");
                getchar();
                return;
            }
            staffNode = staffNode->nxt;
        }
        // 没找到
        gotoXY(55, 7);
		printf("此员工不存在！");
		getchar();
    }
}

/// @brief 人员界面
void staffView()
{
    while(true)
    {
        system("cls");
        printf("--------------------------------------------------\n");
        printf("                     人员管理\n");
        printf("--------------------------------------------------\n");
        gotoXY(0, 15);
        printf("-------------------------------------------------\n");
        gotoXY(0,6);
        printf("                  1: 添加人员\n");
        printf("                  2: 修改人员\n");
        printf("                  3: 删除人员\n");
        printf("                  4: 查询人员\n");
        printf("                  0: 返回\n");

        gotoXY(55, 6);
        printf("请输入你的选择：");
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


