/*Thiago Santos Teixeira nUSP 10736987 */
#ifndef __MYHEADER_H__
#define __MYHEADER_H__
typedef struct{
                char *palavra;
                int freq;
                } data;
typedef struct {
                char *palavra;
                int max;
                int top;
                }Buffer;
typedef struct {
                data *info;
                int max;
                int top;
                }BufferData;
typedef struct{
                data *info;
                int ultPos;
                int max;
                } stableV;
typedef struct noLG {
                    data info;
                    struct noLG *next;
                    }celulaLG;
typedef celulaLG *apontadorLG;

int nElementosLG(apontadorLG inicio); /* Conta quantos elementos uma lista ligada tem */

void mergeSortM(int inicio, int fim, data *V, char *tipoOrd); /* Ordena um vetor de uma struct com MergeSort conforome o tipo de ordenacao */

void mergeM(int inicio, int meio, int fim, data *V, char *tipoOrd); /*merge modificado*/

Buffer *criaBuffer();   /*cria um vetor dinamico e devolve um ponteiro para ele */

void realocaBuffer(Buffer *B); /* Dobra o tamanho do vetor */

void adicionaNoBuffer(Buffer *B, char c);   /*adiciona um char no buffer */

void destroiBuffer(Buffer *B); /*desaloca a memoria de um buffer */

void clearBuffer(Buffer *B);    /*reinicia o buffer */

BufferData *criaBufferData();   /*Cria um vetor dinamico e devolve um ponteiro para ele */

void realocaBufferData(BufferData *B); /*Dobra o tamanho do buffer*/

void adicionaNoBufferData(BufferData *B, data *Novo); /*Adiciona um tipo de data no buffer */

void destroiBufferData(BufferData *B);  /*desaloca a memoria de um buffer */
#endif
