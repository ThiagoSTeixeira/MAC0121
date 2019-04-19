/*Thiago Santos Teixeira nUSP 10736987 */
#include<string.h>
#include"myHeader.h"
#include"tabelaSimbolo_LD.h"
data *LDtoVD(apontadorLG inicio){
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
void imprimeLD_A(apontadorLG stable)
{
    int i;
    data *V;
    /*ordena usando um vetor auxiliar */
    V = LDtoVD(stable);
    mergeSortM(0, nElementosLG(stable), V, "A");
    for(i = 0; i < nElementosLG(stable); i++){
        printf("%s ", V[i].palavra);
        printf("%d\n", V[i].freq);
    }
    /*destroi o vetor auxiliar */
    for(i = 0; i < nElementosLG(stable); i++)
        free(V[i].palavra);
    free(V);
    return;
}
void imprimeLD_O(apontadorLG stable)
{
    int i;
    data *V;
    /*cria um vetor com os elementos da tabela e ordena-o em NlogN usando um mergeSort modificado
     iremos ordenar o vetor por ordem alfabetica para que quando formos
     imprimir o vetor as palavras "menores" tomem prescedencia se tiverem a mesma frequencia
     */
    V = LDtoVD(stable);
    mergeSortM(0, nElementosLG(stable), V, "A");
    mergeSortM(0, nElementosLG(stable), V, "O");
    for(i = nElementosLG(stable) -1; i >= 0; i--){
        printf("%s ", V[i].palavra);
        printf("%d\n", V[i].freq);
    }
    /*destroi o vetor auxiliar */
    for(i = 0; i < nElementosLG(stable); i++)
        free(V[i].palavra);
    free(V);
    return;
}
apontadorLG criaStableLD()
{
    apontadorLG inicio = NULL;
    return(inicio);
}
void destroiStableLD(apontadorLG inicio)
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
apontadorLG insereStableLD(char *key ,apontadorLG inicio)
{
    apontadorLG temp, anterior;
    apontadorLG novoItem;
    /*verifica se a lista esta vazia. */
    if(!inicio){
        inicio = malloc(sizeof(celulaLG));
        inicio->info.palavra = malloc(strlen(key)*sizeof(char));
        strcpy(inicio->info.palavra, key);
        inicio->info.freq = 1;
        inicio->next = NULL;
        return inicio;
    }
    anterior = NULL;
    for(temp = inicio; temp != NULL; anterior = temp, temp = temp->next){
        if(!strcmp(key, temp->info.palavra)){
            temp->info.freq++;
            return inicio;
        }
    }
    /*insere a palavra no final caso a funcao tenha chegado ate aqui */
    novoItem = malloc(sizeof(celulaLG));
    novoItem->info.palavra = malloc(strlen(key)*sizeof(char));
    strcpy(novoItem->info.palavra, key);
    novoItem->info.freq = 1;
    novoItem->next = NULL;
    anterior->next = novoItem;
    return inicio;
}
