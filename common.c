#include <time.h>
#include "common.h"

/// @brief 光标移动到
/// @param x 横坐标
/// @param y 纵坐标
void gotoXY(short x, short y)
{
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/// @brief 获取输入的字符串
/// @param str 存储到字符串
/// @param maxLen 输入最长长度
/// @param putType 输入类型. 1 字母或数字 2 字母 3 数字 4 汉字
/// @param isPlaintext 是否明文显示 
/// @retval true 确定输入
/// @retval false 返回
bool getString(char str[], int maxLen, int putType, bool isPlaintext)
{
    int len = 0; //当前长度
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
        if(ch == '\b' && len) // 退格键且有长度
        {
            printf("\b \b");
            --len;
        }
        else if(ch == 0x1b) return false; // esc键，输入失败
        else if(ch == 0x0d && len)
        {
            str[len] = '\0'; // 字符串结尾标志
            break; // 回车键，输入成功
        } 
    }
    return true;
}

/// @brief 获取时间
/// @param returnTime 时间存储到 
void getTime(char returnTime[])
{
    time_t time1;
    time(&time1);  // 返回 CUT 时间到当前秒数
    struct tm *p = localtime(&time1); // 
    sprintf(returnTime, "%04d%02d%02d%02d%02d%02d", p->tm_year + 1900, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
}

/// @brief 得到输入的字符
/// @param num1 下限
/// @param num2 上限
/// @return 输入的字符 
char getChar(char num1, char num2)
{
    char ch, returnCh;
    int len = 0;
    while(1)
    {
        ch = getch();
        if(ch >= num1 && ch <= num2) //在范围之内
        {
            if(len == 0)
            {
                returnCh = ch;
                putchar(ch);
                ++len;
            }
        }
        if(ch == '\b') // 退格键
        {
            if(len)
            {
                printf("\b \b");
                --len;
            }
        }
        else if(ch == 0x0d && len) return returnCh; // 回车键
        else if(ch == 0x1b) return 0;  // 返回上一个界面
    }
}

/// @brief 部分清空屏幕
/// @param x 起始横坐标
/// @param y 起始纵坐标
/// @param z 打印多少空格
void clear(short x, short y, int z)
{
    gotoXY(x, y);
    for(int i = 0; i < z; ++i) putchar(' ');
}