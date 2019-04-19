/*Thiago Santos Teixeira nUSP 10736987 */
#ifndef __TABELASIMBOLO_LO_H
#define __TABELASIMBOLO_LO_H
/*esta função uma tabela de simbolos que usa uma Lista ligada e ira criar um
 *vetor com os elementos desta tabela.
 */
data *LOtoVD(apontadorLG inicio);
/*esta função recebe uma tabela de simbolos feita com lista ligada e a imprime
 *na saida padrão em ordem alfabetica.
 */
void imprimeLO_A(apontadorLG stable);
/*esta função recebe uma tabela de simbolos feita com lista ligada e a imprime
 *na saida padrão em ordem de frequencia.
 */
void imprimeLO_O(apontadorLG stable);
/*função cria uma variavel com o começo da tabela de simbolos.
 */
apontadorLG criaStableLO();
/*função recebe o inicio da tabela de simbolos e ira desalocar a memória de
 *todos seus elementos.
 */
void destroiStableLO(apontadorLG inicio);
/*função recebe o inicio da tabela de simbolos e uma string e ira inserir essa
 *string no local que ira deixar a tabela ordenada se ela não se encontar na
 tabela, se o ultímo for verdade a função ira aumentar a frequencia da palavra,
 a função devolve o inicio da tabela pois ele pode mudar;
 */
apontadorLG insereStableLO(char *key ,apontadorLG inicio);

#endif
