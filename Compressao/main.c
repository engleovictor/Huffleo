#include <stdio.h>

#include "Hashing.h"
#include "Arvore_de_Huffman.h"

int main(int argc, char *argv[]) {
    char *myStr = stringFromFile(argv[1]);
    int *freqs  = stringInfo(myStr);
    char *onlyOnceMyStr = onlyOnceString(freqs);

    Arvore_de_Huffman *T = montarArvComSimFreq_hash(onlyOnceMyStr,freqs);

    printf("SIMETRICA:");
    printSimetric(T);
    printf("\n");
    printf("PRE-ORDEM:");
    printPreOrdem(T);
    printf("\n");

    char **dict = createhDict();
    gerarDict(T,dict);
    for(int i=0;i<(int) strlen(myStr);i++) printf("%s", dict[(int) myStr[i]]);
    printf("\n");

    // Frees;
    free(myStr);
    free(freqs);
    free(onlyOnceMyStr);
    deletehDict(dict);
    freePosOrdem(T);

    return 0;
}