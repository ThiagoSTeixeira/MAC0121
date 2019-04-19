/*Thiago Santos Teixeira nUSP 10736987*/
#ifndef __TABELASIMBOLO_AB_H
#define __TABELASIMBOLO_AB_H

typedef struct noAB{
                data info;
                struct noAB *esq;
                struct noAB *dir;
                } celulaAB;

typedef celulaAB *apontadorAB;
/*Função recebe uma ABB e um vetor de tipo data dinamico, a função ira copiar
 *o conteudo da ABB para o vetor.
 */
BufferData *ABparaBuffer(apontadorAB stable, BufferData *Buffer);
/*Função recebe uma ABB e a imprime em ordem de frequencia da palavras
 */
void imprimeAB_O(apontadorAB stable);
/*função recursiva que recebe uma tabela de simbolo que usa ABB's e imprime ela
 *em ordem alfabetica.
 */
void imprimeAB_A(apontadorAB stable);
/*cria uma tabela de simbolos usando arvore de busca binaria, a função devolve
 *o inicio desta arvore.
 */
apontadorAB criaStableAB();
/*esta função recebe o inicio de uma ABB e destroi uma tabela de simbolos que
 *usa uma arvore de busca binaria.
 */
void destroiStableAB(apontadorAB inicio);
/*esta função recebe o começo de uma ABB e uma string, a função ira percorrer a
 *ABB e ira adicionar a string na arvore, se a string ja se encontrar nela, so
 *sua frequencia ira mudar, a função devolve a começo da arvore.
 */
apontadorAB insereStableAB(char *key, apontadorAB inicio);

apontadorAB insereStableABfreq(data *novo, apontadorAB inicio);
#endif
