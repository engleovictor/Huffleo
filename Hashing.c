#include "Hashing.h"

#define LOG_QNT_SIMB 8
#define BUFFER_SIZE 1000

char *stringFromFile(char *filename) {
    FILE *fptr = fopen(filename,"r");

    if(!fptr) {
        printf("Erro ao abrir o arquivo!");
        exit(0);
    }

    char buffer[BUFFER_SIZE];
    int readQnt;
    int allRead = 0;
    char *returnStr = NULL;

    while(!feof(fptr)) {
        readQnt = fread(buffer,sizeof(char),BUFFER_SIZE,fptr);
        char *now = (char *) malloc(sizeof(char)*(allRead+readQnt+1));
        for(int i=0;i<allRead;i++) now[i] = returnStr[i];
        for(int i=0;i<readQnt;i++) now[allRead+i] = buffer[i];
        now[allRead+readQnt] = '\0';
        free(returnStr);
        returnStr = now;
        allRead += readQnt;
    }

    fclose(fptr);

    return returnStr;
}

int *stringInfo(char *word) {
    int *p = (int *) malloc(sizeof(int)*256);
    int i = 0;
    while(i<256) p[i++] = 0;
    int tam = (int) strlen(word);
    for(i=0;i<tam;i++) {
        p[(int) word[i]]++;
    } return p;
}

char *onlyOnceString(int *stringInfo) {
    char *buff = (char *) malloc(sizeof(char)*257);
    int i=0, j=0;
    while(i<256) {
        if(stringInfo[i++]) buff[j++] = (char) (i-1);
    } buff[j] = '\0';
    return buff;
}

char **createhDict() {
    char **dict = (char **) malloc(sizeof(char *)*256);
    for(int i=0;i<256;i++) dict[i] = (char *) malloc(sizeof(char)*LOG_QNT_SIMB);
    return dict;
}

void deletehDict(char **dict) {
    for(int i=0;i<256;i++) free(dict[i]);
    free(dict);
}

