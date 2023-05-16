#include "Descobridor_de_Frequencia.h"

#define CARACS_SIZE 100
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

String_Info *returnInfo(char *caracs) {

    String_Info *new = (String_Info *) malloc(sizeof(String_Info));
    new->caracs = (char *) malloc(sizeof(char)*CARACS_SIZE);
    for(int i=0;i<CARACS_SIZE;i++) new->caracs[i] = '\0';
    new->vals   = (int  *) malloc(sizeof(int)*CARACS_SIZE);
    for(int i=0;i<CARACS_SIZE;i++) new->vals[i] = 0;
    new->qnt    = 0;

    int size = (int) strlen(caracs);

    while(size > 0) {

        int begp = 0;
        new->caracs[new->qnt] = caracs[0];
        while(retirarChar(&size,caracs,new->caracs[new->qnt])) new->vals[new->qnt]++;
        new->qnt++;
        
    }
    
    return new;
}

int retirarChar(int *tam, char *frase, char val) {
    int i = 0;
    while(i < *tam && frase[i] != val) i++;
    if(frase[i] == val) {
        frase[i] = frase[*tam - 1];
        frase[--(*tam)] = '\0';
        return 1;
    } else return 0;
}

void freeString_Info(String_Info **si) {
    free((*si)->caracs);
    free((*si)->vals);
    free(*si);
}
