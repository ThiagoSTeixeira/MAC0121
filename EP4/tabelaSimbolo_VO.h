/*Thiago Santos Teixeira nUSP 10736987 */
#ifndef __TABELASIMBOLO_VO_H__
#define __TABELASIMBOLO_VO_H__


void imprimeVO_A(stableV *stable);  /*Recebe uma TabSim com vetor e imprime em ordem d frequencia */

void imprimeVO_O(stableV *stable);  /*Cria e devolve um ponteiro para TabSim em vetor desordenado */

stableV *criaStableVO();    /*Cria e devolve ponteiro para TabSim em vetor ordenado */


void destroiStableVO(stableV *stable);  /*Destroi TabSim em vetor ordenado */


stableV *insereStableVO(char *key, stableV *stable);    /*Insere string na TabSim de maneira ordenada */


stableV *realocaStableVO(stableV *stable);  /*Recria uma TabSim com o dobro do tamanho */


int buscaBin(char *key, stableV *stable, int ini, int fim); /*Funcao de busca binaria que devolve onde esta o item desejado, ou onde ele deveria estar para que fique ordenado */
#endif
