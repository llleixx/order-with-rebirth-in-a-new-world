#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include <string.h>

/// @brief Ա��
typedef struct{
	int id; // ���
	int role; // 0 ����Ա 1 ����Ա 2 ����
	char name[13]; // Ա������
    char passwd[17]; // ��¼����
}Staff;

/// @brief ̨��
typedef struct{
	int id; // ���
	int flag; // 0 ���� 1 ռ�� 2 Ԥ�� 3 ά��
	char desc[25]; // ����
}Table;

/// @brief ����
typedef struct{
	int id;    // ���
	int price; // �۸�
	int num;       // ����
	char name[17];   // ����
}Menu;

/// @brief ����
typedef struct{
	int menuId; // �˵ı��
	int num; // �˵ķ���
	int price; // �˵ļ۸� 
	int total; // �ܶ�
	char name[17]; // �˵�����
	char serialNum[26]; // ��ˮ��
}Order;

/// @brief �˵�
typedef struct{
	int waiterId; // ����Ա�ı��
	int  tableId; // ̨����
	int total; // ���
	int flag; // 0 δ���� 1 ����
	char time[9]; // ����ʱ��
	char serialNum[26]; // ��ˮ��
}Bill;


void printStaff(void *data);

void printTable(void *data);

void printMenu(void *data);

void printMenu1(void *data);

void printBill(void *data);

void printOrder(void *data);


#endif
