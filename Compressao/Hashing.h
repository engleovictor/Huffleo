#ifndef __HASHING_H__
#define __HASHING_H__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *stringFromFile(char *filename);
int *stringInfo(char *word);
char *onlyOnceString(int *stringInfo);
void attachValueToDict(char **dict, char val, char *repres);
char **createhDict();
void deletehDict(char **dict);

#endif // __HASHING_H__