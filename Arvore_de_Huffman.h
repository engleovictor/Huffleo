#ifndef __ARVORE_DE_HUFFMAN_H__
#define __ARVORE_DE_HUFFMAN_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arvore_de_huffman {
    short int e_folha;
    int freq;
    char *simbolo;
    struct arvore_de_huffman *esq, *dir;
} Arvore_de_Huffman;

typedef struct __dict__ {
    char simbolo;
    char *repres;
} Dicionario;


Arvore_de_Huffman *newNoSimbolo(int freq, char simbolo);
Arvore_de_Huffman *newNoNaoSimbolo(int val, Arvore_de_Huffman *esq, Arvore_de_Huffman *dir);
void juntarMenores(Arvore_de_Huffman **allNos, int *tam, int val);
Arvore_de_Huffman *montarArvComSimFreq(int tam, char *simbolos, int *vals);
void printPreOrdem(Arvore_de_Huffman *T);
void printSimetric(Arvore_de_Huffman *T);
void freePosOrdem(Arvore_de_Huffman *T);
void criarDict(Arvore_de_Huffman *T, Dicionario **dict);
void criarAbsDict(Arvore_de_Huffman *T, char *buff, int tam, Dicionario **dict, int *index); // Abstraida;
int func_map(char val, Dicionario **dict);
void mostrarDict(int tam, Dicionario **dict);

#endif // __ARVORE_DE_HUFFMAN_H__