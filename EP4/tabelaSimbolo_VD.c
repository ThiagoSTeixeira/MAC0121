/*Thiago Santos Teixeira nUSP 10736987 */
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include"myHeader.h"
#include"tabelaSimbolo_VD.h"

void imprimeVD_A(stableV *stable)
{
    int i;
    mergeSortM(0, stable->ultPos, stable->info, "A");
    for(i = 0; i < stable->ultPos; i++){
        printf("%s ", stable->info[i].palavra);
        printf("%d\n", stable->info[i].freq);
    }
    return;
}
void imprimeVD_O(stableV *stable)
{
    int i;
    /*antes iremos ordenar o vetor por ordem alfabetica para que quando formos
     *imprimir o vetor as palavras "menores" tomem prescedencia se tiverem a mesma
     *frequencia, como iremos usar um sort estavel isso é garantido.
     */
    mergeSortM(0, stable->ultPos, stable->info, "A");
    mergeSortM(0, stable->ultPos, stable->info, "O");
    for(i = stable->ultPos - 1; i >= 0; i--){
        printf("%s ", stable->info[i].palavra);
        printf("%d\n", stable->info[i].freq);
    }
    return;
}
stableV *criaStableVD()
{
    stableV *stable = malloc(sizeof(stableV));
    stable->max = 8;
    stable->ultPos = 0;
    stable->info = malloc(stable->max*sizeof(data));
    return(stable);
}

void destroiStableVD(stableV *stable)
{
    int i;
    for(i = 0; i < stable->ultPos; i++)
        free(stable->info[i].palavra);
    free(stable->info);
    free(stable);
    return;
}

stableV *insereStableVD(char *key, stableV *stable)
{
    int i;
    /*primeiro iremos procurar se o elemto se encontra na lista e mudar sua
     *frequencia se nescessario.
    */
    for(i = 0; i < stable->ultPos; i++){
        if(!strcmp(key,stable->info[i].palavra)){
            stable->info[i].freq++;
            return stable;
        }
    }
    /*antes de inserirmos a palavra pode ser que a tabela esteja cheia.
    */
    if(stable->ultPos == stable->max){
        stable = realocaStableVD(stable);
    }
    /*como a tabela tem espaço para a palavra nova e ela não estava na lista
     *simplesmente podemos adicionar a palavra no final da tabela.
     */
    stable->info[i].palavra = malloc(strlen(key)*sizeof(char));
    strcpy(stable->info[i].palavra,key);
    stable->info[i].freq = 1;
    stable->ultPos++;
    return stable;
}

stableV *realocaStableVD(stableV *stable)
{
    stableV *stableNova;
    int i;
    stableNova = malloc(sizeof(stableV));
    stableNova->max = stable->max*2;
    stableNova->ultPos = stable->ultPos;
    stableNova->info = malloc(stableNova->max*sizeof(data));
    /*ao dobrarmos o tamanho garantimos que não iremos fazer essa operação
     *muitas vezes
     */
    for(i = 0; i < stable->ultPos; i++){
        stableNova->info[i].freq = stable->info[i].freq;
        stableNova->info[i].palavra = malloc(strlen(stable->info[i].palavra)*sizeof(char));
        strcpy(stableNova->info[i].palavra, stable->info[i].palavra);
    }
    destroiStableVD(stable);
    return(stableNova);
}
