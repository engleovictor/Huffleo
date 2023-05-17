#include <stdio.h>

#include "Descobridor_de_Frequencia.h"
#include "../Arvore_de_Huffman.h"

int main(int argc,char *argv[]) {

    char *myStr = stringFromFile(argv[1]);
    String_Info *new = returnInfo(myStr);

    Arvore_de_Huffman *T = montarArvComSimFreq(new->qnt,new->caracs,new->vals);

    printf("SIMETRICA:");
    printSimetric(T);
    printf("\n");
    printf("PRE-ORDEM:");
    printPreOrdem(T);
    printf("\n");

    Dicionario **dict = (Dicionario **) malloc(sizeof(Dicionario *)*new->qnt);
    for(int i=0;i<new->qnt;i++) dict[i] = (Dicionario *) malloc(sizeof(Dicionario)*1);
    
    criarDict(T,dict);
    
    char *myNewStr = stringFromFile(argv[1]);
    long unsigned int tamanho = (long unsigned int) strlen(myNewStr);

    // A principio, pro trabalho queremos mandar uma string pro companheiro;
    for(long unsigned int i=0;i<tamanho;i++) {
        printf("%s",dict[func_map(myNewStr[i],dict)]->repres);
    } printf("\n");

    // Free de tudo:
    for(int i=0;i<new->qnt;i++) free(dict[i]->repres);
    for(int i=0;i<new->qnt;i++) free(dict[i]);
    free(dict);
    freePosOrdem(T);
    freeString_Info(&new);
    free(myStr);
    free(myNewStr);

    return 0;
}