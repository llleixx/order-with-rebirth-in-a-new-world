#include <time.h>
#include "common.h"

/// @brief ����ƶ���
/// @param x ������
/// @param y ������
void gotoXY(short x, short y)
{
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/// @brief ��ȡ������ַ���
/// @param str �洢���ַ���
/// @param maxLen ���������
/// @param putType ��������. 1 ��ĸ������ 2 ��ĸ 3 ���� 4 ����
/// @param isPlaintext �Ƿ�������ʾ 
/// @retval true ȷ������
/// @retval false ����
bool getString(char str[], int maxLen, int putType, bool isPlaintext)
{
    int len = 0; //��ǰ����
    char ch;
    while(1)
    {
        ch = getch();
        if(len < maxLen)
        {
            if((isalnum(ch) && putType == 1) || \
            (isalpha(ch) && putType == 2) || \
            (isdigit(ch) && putType == 3) || \
            (ch < 0 && putType == 4))
            {
                str[len] = ch;
                isPlaintext ? putchar(ch) : putchar('*');
                ++len;
            }
        }
        if(ch == '\b' && len) // �˸�����г���
        {
            printf("\b \b");
            --len;
        }
        else if(ch == 0x1b) return false; // esc��������ʧ��
        else if(ch == 0x0d && len)
        {
            str[len] = '\0'; // �ַ�����β��־
            break; // �س���������ɹ�
        } 
    }
    return true;
}

/// @brief ��ȡʱ��
/// @param returnTime ʱ��洢�� 
void getTime(char returnTime[])
{
    time_t time1;
    time(&time1);  // ���� CUT ʱ�䵽��ǰ����
    struct tm *p = localtime(&time1); // 
    sprintf(returnTime, "%04d%02d%02d%02d%02d%02d", p->tm_year + 1900, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
}

/// @brief �õ�������ַ�
/// @param num1 ����
/// @param num2 ����
/// @return ������ַ� 
char getChar(char num1, char num2)
{
    char ch, returnCh;
    int len = 0;
    while(1)
    {
        ch = getch();
        if(ch >= num1 && ch <= num2) //�ڷ�Χ֮��
        {
            if(len == 0)
            {
                returnCh = ch;
                putchar(ch);
                ++len;
            }
        }
        if(ch == '\b') // �˸��
        {
            if(len)
            {
                printf("\b \b");
                --len;
            }
        }
        else if(ch == 0x0d && len) return returnCh; // �س���
        else if(ch == 0x1b) return 0;  // ������һ������
    }
}

/// @brief ���������Ļ
/// @param x ��ʼ������
/// @param y ��ʼ������
/// @param z ��ӡ���ٿո�
void clear(short x, short y, int z)
{
    gotoXY(x, y);
    for(int i = 0; i < z; ++i) putchar(' ');
}