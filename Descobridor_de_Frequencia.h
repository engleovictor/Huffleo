#ifndef __DESCOBRIDOR_DE_FREQUECIA_H__
#define __DESCOBRIDOR_DE_FREQUECIA_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct string_info {
    char *caracs;
    int  *vals;
    int  qnt;
} String_Info;

char *stringFromFile(char *filename);
String_Info *returnInfo(char *caracs);
int retirarChar(int *tam, char *frase, char val);

#endif // __DESCOBRIDOR_DE_FREQUECIA_H__