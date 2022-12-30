#ifndef _COMMON_H_
#define _COMMON_H_

#include "global.h"

void gotoXY(short x, short y);
bool getString(char str[], int maxlen, int putType, bool isPlaintext);
void getTime(char returnTime[]);
char getChar(char num1, char num2);
void clear(short x, short y, int z);



// 以下是 MD5 加密内容
// MD5 加密用到的结构体
typedef struct{
    unsigned int count[2];
    unsigned int state[4]; // 分别代表 MD5 加密中的 ABCD
    unsigned char buffer[64];
} MD5_CTX;

// 以下是 F 的 1~64 次运算方法
// 1~16 次运算
#define F(x, y, z) ((x & y) | (~x & z))
// 17~32 次运算
#define G(x, y, z) ((x & z) | (y & ~z))
// 33~48 次运算
#define H(x, y, z) (x ^ y ^ z)
// 49~64 次运算
#define I(x, y, z) (y ^ (x | ~z))

// 向左位移 n 位，同时位移溢出放在右边
#define ROTATE_LEFT(x, n) ((x << n) | (x >> (32 - n)))

// 以下是 64次运算，x 是每四个字节一组的 M[i] 中的第 i个，s 是位移表中对应位移量，ac 是常量表 K[i] 中的第 i 个
// 1~16 次运算
#define FF(a, b, c, d, x, s, ac)  \
    {                             \
        a += F(b, c, d) + x + ac; \
        a = ROTATE_LEFT(a, s);    \
        a += b;                   \
    }
// 17~32 次运算
#define GG(a, b, c, d, x, s, ac)  \
    {                             \
        a += G(b, c, d) + x + ac; \
        a = ROTATE_LEFT(a, s);    \
        a += b;                   \
    }
// 33~48 次运算
#define HH(a, b, c, d, x, s, ac)  \
    {                             \
        a += H(b, c, d) + x + ac; \
        a = ROTATE_LEFT(a, s);    \
        a += b;                   \
    }
// 49~64 次运算
#define II(a, b, c, d, x, s, ac)  \
    {                             \
        a += I(b, c, d) + x + ac; \
        a = ROTATE_LEFT(a, s);    \
        a += b;                   \
    }
void MD5Init(MD5_CTX *context);
void MD5Update(MD5_CTX *context, unsigned char *input, unsigned int inputlen);
void MD5Final(MD5_CTX *context, unsigned char digest[16]);
void MD5Transform(unsigned int state[4], unsigned char block[64]);
void MD5Encode(unsigned char *output, unsigned int *input, unsigned int len);
void MD5Decode(unsigned int *output, unsigned char *input, unsigned int len);
void MD5Get(char *str);


#endif