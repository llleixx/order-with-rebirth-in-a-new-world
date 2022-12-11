#ifndef _COMMON_H_
#define _COMMON_H_

#include "global.h"

void gotoXY(short x, short y);
bool getString(char str[], int maxlen, int putType, bool isPlaintext);
void getTime(char returnTime[]);
char getChar(char num1, char num2);
void clear(short x, short y, int z);


#endif