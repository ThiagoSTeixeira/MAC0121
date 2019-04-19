/*Thiago Santos Teixeira nUSP 10736987 */
#ifndef __TABELASIMBOLO_LD_H
#define __TABELASIMBOLO_LD_H

data *LDtoVD(apontadorLG inicio);   /*cria vetor com os elementos da TabSim em lista ligada */

 
void imprimeLD_A(apontadorLG stable);   /*Imprime a TabSim em LL em ordem alfabetica */


void imprimeLD_O(apontadorLG stable); /*Imprime a TabSIm em LL em ordem de frequencia */


apontadorLG criaStableLD(); /*Cria variavel com o comeco da TabSim*/


void destroiStableLD(apontadorLG inicio);   /*Desaloca os elementos da TabSim */


apontadorLG insereStableLD(char *key ,apontadorLG inicio);  /*Insere string no final da TabSim caso ela ja nao esteja la */

#endif
