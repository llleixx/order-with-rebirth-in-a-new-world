#ifndef _FILE_H_
#define _FILE_H_

#include "global.h"
#include "list.h"

void readFile(char *str, LinkList *head, int size);
void writeFile(char *str, LinkList *head, int size);

#endif