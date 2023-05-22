#include "Arvore_de_Huffman.h"

#define LOG_QNT_SIMB 20


Arvore_de_Huffman *newNoSimbolo(int freq, char simbolo) {
    Arvore_de_Huffman *new = (Arvore_de_Huffman *) malloc(sizeof(Arvore_de_Huffman)*1);
    new->dir = NULL;
    new->esq = NULL;
    new->e_folha = 1;
    new->freq = freq;
    char *buff = (char *) malloc(sizeof(char)*2);
    sprintf(buff,"%c",simbolo);
    buff[1] = '\0';
    new->simbolo = buff;
    return new;
}

Arvore_de_Huffman *newNoNaoSimbolo(int val, Arvore_de_Huffman *esq, Arvore_de_Huffman *dir) {
    Arvore_de_Huffman *new = (Arvore_de_Huffman *) malloc(sizeof(Arvore_de_Huffman)*1);
    new->dir = dir;
    new->esq = esq;
    new->freq = dir->freq + esq->freq;
    new->e_folha = 0;
    char *buff = (char *) malloc(sizeof(char)*LOG_QNT_SIMB);
    sprintf(buff,"no%d", val);
    new->simbolo = buff;
    return new;
}

void juntarMenores(Arvore_de_Huffman **allNos, int *tam, int val) {
    int menorFreq0 = 2147483647, menorFreqIndice0;
    for(int i=0;i<*tam;i++) {
        if(menorFreq0 > allNos[i]->freq) {
            menorFreq0 = allNos[i]->freq;
            menorFreqIndice0 = i;
            if(menorFreq0 == 1) break;
        }
    }

    int menorFreq1 = 2147483647, menorFreqIndice1;
    for(int i=0;i<*tam;i++) {
        if(menorFreq1 > allNos[i]->freq && menorFreqIndice0 != i) {
            menorFreq1 = allNos[i]->freq;
            menorFreqIndice1 = i;
            if(menorFreq1 == 1) break;
        }
    }

    Arvore_de_Huffman *aux = newNoNaoSimbolo(val,allNos[menorFreqIndice0],allNos[menorFreqIndice1]);
    allNos[menorFreqIndice0] = aux;
    allNos[menorFreqIndice1] = allNos[(*tam)-1];
    (*tam)--;
}

Arvore_de_Huffman *montarArvComSimFreq(int tam, char *simbolos, int *vals) {
    int tam0 = tam;
    Arvore_de_Huffman **allNos = (Arvore_de_Huffman **) malloc(sizeof(Arvore_de_Huffman *)*tam);
    for(int i=0;i<tam;i++) allNos[i] = newNoSimbolo(vals[i], simbolos[i]);
    
    int j=0;    
    while(1) {
        if(tam0 == 1) break;
        juntarMenores(allNos,&tam0,j++); ///
    }

    Arvore_de_Huffman *aux = allNos[0];
    free(allNos);
    return aux;
}

void printPreOrdem(Arvore_de_Huffman *T) {
    if(T) {
        printf("%s, ", T->simbolo);
        printPreOrdem(T->esq);
        printPreOrdem(T->dir);
    }
}

void printSimetric(Arvore_de_Huffman *T) {
    if(T) {
        printSimetric(T->esq);
        printf("%s, ", T->simbolo);
        printSimetric(T->dir);
    }
}

void freePosOrdem(Arvore_de_Huffman *T) {
    if(T) {
        freePosOrdem(T->esq);
        freePosOrdem(T->dir);
        free(T->simbolo);
        free(T);
    }
}

void criarDict(Arvore_de_Huffman *T, Dicionario **dict) {
    char *buff = (char *) malloc(sizeof(char)*LOG_QNT_SIMB);
    buff[0] = '\0';
    int p = 0;
    criarAbsDict(T,buff,1,dict,&p);
    free(buff);
}

void criarAbsDict(Arvore_de_Huffman *T, char *buff, int tam, Dicionario **dict, int *index) {
    // A principio nunca vamos ter uma arvore que um NoX não tenha 2 filhos.
    if(T->e_folha) {
        dict[*index]->simbolo = T->simbolo[0];
        dict[*index]->repres = (char *) malloc(sizeof(char)*LOG_QNT_SIMB);
        strcpy(dict[(*index)++]->repres,buff);
    } else {
        sprintf(buff,"%s0",buff);
        criarAbsDict(T->esq,buff,tam+1,dict,index);
        buff[tam-1] = '\0';
        sprintf(buff,"%s1",buff);
        criarAbsDict(T->dir,buff,tam+1,dict,index);
        buff[tam-1] = '\0';
    }
}

int func_map(char val, Dicionario **dict) {
    int i=0;
    while(dict[i]->simbolo != val) i++;
    return i;
}

void mostrarDict(int tam, Dicionario **dict) {
    for(int i = 0;i< tam;i++) printf("%c %s\n", dict[i]->simbolo, dict[i]->repres);
}

Arvore_de_Huffman *montarArvComSimFreq_hash(char *onlyOnceString, int *freqs) {
    int tam0 = (int) strlen(onlyOnceString);
    Arvore_de_Huffman **allNos = (Arvore_de_Huffman **) malloc(sizeof(Arvore_de_Huffman *)*tam0);
    int j=0; 
    
    for(int i=0;i<256;i++) {
        if(freqs[i]) {
            allNos[j++] = newNoSimbolo(freqs[i], (char) i);
        }
    }

    j=0;
    while(1) {
        if(tam0 == 1) break;
        juntarMenores(allNos,&tam0,j++);
    }

    Arvore_de_Huffman *aux = allNos[0];
    free(allNos);
    return aux;
}

void gerarDict(Arvore_de_Huffman *T, char **dict) {
    char *buff = (char *) malloc(sizeof(char)*LOG_QNT_SIMB);
    buff[0] = '\0';
    int p = 0;
    gerarAbsDict(T,buff,1,dict,&p);
    free(buff);
}

void attachValueToDict(char **dict, char val, char *repres) {
    strcpy(dict[(int) val],repres);
}

void gerarAbsDict(Arvore_de_Huffman *T, char *buff, int tam, char **dict, int *index) {
    // A principio nunca vamos ter uma arvore que um NoX não tenha 2 filhos.
    if(T->e_folha) {
        attachValueToDict(dict,T->simbolo[0],buff);
    } else {
        sprintf(buff,"%s0",buff);
        gerarAbsDict(T->esq,buff,tam+1,dict,index);
        buff[tam-1] = '\0';
        sprintf(buff,"%s1",buff);
        gerarAbsDict(T->dir,buff,tam+1,dict,index);
        buff[tam-1] = '\0';
    }
}
