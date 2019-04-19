/*Thiago Santos Teixeira nUSP 10736987 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"myHeader.h"
#include"tabelaSimbolo_LO.h"
data *LOtoVD(apontadorLG inicio)
{
    int j;
    apontadorLG i;
    data *V = NULL;
    V = malloc(nElementosLG(inicio)*sizeof(data));
    for(i = inicio, j = 0; i != NULL; i = i->next, j++){
        V[j].palavra = malloc(strlen(i->info.palavra)*sizeof(char));
        strcpy(V[j].palavra, i->info.palavra);
        V[j].freq = i->info.freq;
    }
    return V;
}
void imprimeLO_A(apontadorLG stable)
{
    apontadorLG i;
    /*como a tabela já esta ordenada só iremos imprimir seus elemntos na ordem
     *que eles se encontram.
     */
    for(i = stable; i != NULL; i = i->next){
        printf("%s ", i->info.palavra);
        printf("%d\n", i->info.freq);
    }
    return;
}
void imprimeLO_O(apontadorLG stable)
{
    int i;
    data *V;
    /*como ordenar uma lista ligada é muito dificil iremos criar um vetor com
     *os elementos da tabela e ordenalo em NlogN.
     */
    V = LOtoVD(stable);
    mergeSortM(0, nElementosLG(stable), V, "O");
    for(i = nElementosLG(stable) -1; i >= 0; i--){
        printf("%s ", V[i].palavra);
        printf("%d\n", V[i].freq);
    }
    /*vamos destruir nosso vetor auxiliar;
     */
    for(i = 0; i < nElementosLG(stable); i++)
        free(V[i].palavra);
    free(V);
    return;
}
apontadorLG criaStableLO()
{
    apontadorLG inicio = NULL;
    return(inicio);
}

void destroiStableLO(apontadorLG inicio)
{
    apontadorLG prox;
    while(inicio != NULL){
        prox = inicio->next;
        free(inicio->info.palavra);
        free(inicio);
        inicio = prox;
    }
    return;
}

apontadorLG insereStableLO(char *key ,apontadorLG inicio)
{
    apontadorLG temp, anterior, novoItem;
    temp = inicio;
    anterior = NULL;
    /*primeiro devemos verificar se a lista esta vazia.
     */
    if(!inicio){
        inicio = malloc(sizeof(celulaLG));
        inicio->info.palavra = malloc(strlen(key)*sizeof(char));
        strcpy(inicio->info.palavra, key);
        inicio->info.freq = 1;
        inicio->next = NULL;
        return inicio;
    }
    /*agora iremos procurar o iten desejado na lista e mudar sua frequencia se
     *ele estiver presente na lista.
     */
    while(temp != NULL && strcmp(key, temp->info.palavra) >= 0){
        if(!strcmp(key, temp->info.palavra)){
            temp->info.freq++;
            return(inicio);
        }
        anterior = temp;
        temp = temp->next;
    }
    novoItem = malloc(sizeof(celulaLG));
    novoItem->info.palavra = malloc(strlen(key)*sizeof(char));
    strcpy(novoItem->info.palavra, key);
    novoItem->info.freq = 1;
    novoItem->next = temp;
    /*Agora vamos verificar se temos que mudar o inicio da lista.
     */
    if(anterior == NULL){
        inicio = novoItem;
        return(inicio);
    }
    anterior->next = novoItem;
    return(inicio);
}
