/*Thiago Santos Teixeira nUSP 10736987 */
#ifndef __TABELASIMBOLO_VD_H
#define __TABELASIMBOLO_VD_H
/*esta é uma função de mergeSort que ira ordenar um vetor de uma struct, a
 *ordenção ira depender da variavel tipoOrd(pode ser por frequencia ou
 *alfabeticamente).
 */
void mergeSortVD(int inicio, int fim, stableV *stable, char *tipoOrd);
/*função de merge modificada.
 */
void mergeVD(int inicio, int meio, int fim, stableV *stable, char *tipoOrd);
/*esta função recebe uma tabela de simbolos feita com vetor dinamico e a imprime
 *na saida padrão em ordem alfabetica.
 */
void imprimeVD_A(stableV *stable);
/*esta função recebe uma tabela de simbolos feita com vetor dinamico e a imprime
 *na saida padrão em ordem de frequencia.
 */
void imprimeVD_O(stableV *stable);
/*Função que ira criar e devolver um ponteiro para uma tabela de simbolos que
 *usa um vetor desordenado.
 */
stableV *criaStableVD();
/*Função que receve uma de simbolos que usa um vetor desordenado e ira destruir
 *ela.
 */
void destroiStableVD(stableV *stable);
/*Função que recebe uma string e uma tamabela de simbolos e ira inserir essa
 *palavra na tabela, se a palavra já estiver na tabela a função só ira
 *acrecentar a frequencia dela, se a tabela se encontar cheia a funçao ira chamar
 *a função realocastableV.
 */
stableV *insereStableVD(char *key, stableV *stable);
/*Função que recebe uma tabela de simbolos e ira criar uma outra tabela de
 *simbolos com os mesmos itens porem com o dobro so tamanho da original.
 */
stableV *realocaStableVD(stableV *stable);

#endif
