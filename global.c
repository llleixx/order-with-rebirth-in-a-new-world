#include "global.h"

/// @brief 打印人员信息
/// @param data 人员节点
void printStaff(void *data)
{
    Staff *staff = (Staff*)data;
    printf("%-8d", staff->id);
	printf("%-16s", staff->name);
	switch(staff->role)
	{
		case 0:
			printf("%-10s", "管理员");
			break;
		case 1:
			printf("%-10s", "服务员");
			break;
		case 2:
			printf("%-8s", "经理");
			break;
	}
	putchar('\n');
}

/// @brief 打印台桌信息
/// @param data 台桌节点
void printTable(void *data)
{
	Table *table = (Table*)data;
	printf("%-8d", table->id);
	switch(table->flag)
	{
		case 0:
			printf("%-8s", "空闲");
			break;
		case 1:
			printf("%-8s", "占用");
			break;
		case 2:
			printf("%-8s", "预定");
			break;
		case 3:
			printf("%-8s", "维护");
			break;
	}
	printf("%-28s", table->desc);
	printf("\n");
}

/// @brief 打印菜谱信息（不显示份数）
/// @param data 菜谱节点
void printMenu(void *data)
{
	Menu *menu = (Menu*)data;
	printf("%-14d", menu->id);
	printf("%-22s", menu->name);
	printf("%d", menu->price);
	printf("\n");
}

/// @brief 打印菜谱信息（显示份数）
/// @param data 菜谱节点
void printMenu1(void *data)
{
	Menu *menu = (Menu*)data;
	printf("%-14d", menu->id);
	printf("%-22s", menu->name);
	printf("%-9d", menu->price);
	printf("%d", menu->num); // 还需优化
	printf("\n");
}

/// @brief 打印账单信息
/// @param data 账单节点
void printBill(void *data)
{
	Bill *bill = (Bill*)data;
	printf("%-28s", bill->serialNum);
	printf("%-12d", bill->waiterId);
	printf("%-10d", bill->tableId);
	printf("%-10s", bill->time);
	printf("%-6d", bill->total);
	printf("\n");
}

/// @brief 打印订单信息
/// @param data 订单节点
void printOrder(void *data)
{
	Order *order = (Order*)data;
	printf("%-28s", order->serialNum);
	printf("%-18s", order->name);
	printf("%-7d", order->price);
	printf("%-7d", order->num);
	printf("%-7d", order->total);
	printf("\n");
}