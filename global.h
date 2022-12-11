#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include <string.h>

/// @brief 员工
typedef struct{
	int id; // 编号
	int role; // 0 管理员 1 服务员 2 经理
	char name[13]; // 员工姓名
    char passwd[17]; // 登录密码
}Staff;

/// @brief 台桌
typedef struct{
	int id; // 编号
	int flag; // 0 空闲 1 占用 2 预定 3 维护
	char desc[25]; // 描述
}Table;

/// @brief 菜谱
typedef struct{
	int id;    // 编号
	int price; // 价格
	int num;       // 份数
	char name[17];   // 名字
}Menu;

/// @brief 订单
typedef struct{
	int menuId; // 菜的编号
	int num; // 菜的份数
	int price; // 菜的价格 
	int total; // 总额
	char name[17]; // 菜的名字
	char serialNum[26]; // 流水号
}Order;

/// @brief 账单
typedef struct{
	int waiterId; // 服务员的编号
	int  tableId; // 台桌号
	int total; // 金额
	int flag; // 0 未付款 1 付款
	char time[9]; // 订单时间
	char serialNum[26]; // 流水号
}Bill;


void printStaff(void *data);

void printTable(void *data);

void printMenu(void *data);

void printMenu1(void *data);

void printBill(void *data);

void printOrder(void *data);


#endif
