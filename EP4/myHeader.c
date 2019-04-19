/*Thiago Santos Teixeira nUSP 10736987 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<myHeader.h>
int nElementosLG(apontadorLG inicio)
{
    int j;
    apontadorLG i;
    for(i = inicio, j = 0; i != NULL; i = i->next, j++);
    return j;
}

void mergeSortM(int inicio, int fim, data *V, char *tipoOrd)
{
    int meio;
    if (inicio < fim - 1) {
        meio = (inicio + fim)/2;
        mergeSortM(inicio, meio, V, tipoOrd);
        mergeSortM(meio, fim, V, tipoOrd);
        mergeM(inicio, meio, fim, V, tipoOrd);
    }
}

void mergeM(int inicio, int meio, int fim, data *V, char *tipoOrd)
{
    int i, j, k;
    data *w;
    w = malloc ((fim - inicio) * sizeof (data));
    i = inicio; j = meio;
    k = 0;
    while (i < meio && j < fim) {
        if(!strcmp(tipoOrd, "A")){
            if (strcmp(V[i].palavra,V[j].palavra) <= 0){
                w[k].palavra = malloc(strlen(V[i].palavra)*sizeof(char));
                strcpy(w[k].palavra, V[i].palavra);
                free(V[i].palavra);
                w[k].freq = V[i].freq;
                k++;
                i++;
            }
            else{
                w[k].palavra = malloc(strlen(V[j].palavra)*sizeof(char));
                strcpy(w[k].palavra, V[j].palavra);
                free(V[j].palavra);
                w[k].freq = V[j].freq;
                k++;
                j++;
            }
        }
        else{
            if (V[i].freq <=  V[j].freq){
                w[k].palavra = malloc(strlen(V[i].palavra)*sizeof(char));
                strcpy(w[k].palavra, V[i].palavra);
                free(V[i].palavra);
                w[k].freq = V[i].freq;
                k++;
                i++;
            }
            else{
                w[k].palavra = malloc(strlen(V[j].palavra)*sizeof(char));
                strcpy(w[k].palavra, V[j].palavra);
                free(V[j].palavra);
                w[k].freq = V[j].freq;
                k++;
                j++;
            }
        }
    }
    while (i < meio){
        w[k].palavra = malloc(strlen(V[i].palavra)*sizeof(char));
        strcpy(w[k].palavra, V[i].palavra);
        free(V[i].palavra);
        w[k].freq = V[i].freq;
        k++;
        i++;
    }

    while (j < fim){
        w[k].palavra = malloc(strlen(V[j].palavra)*sizeof(char));
        strcpy(w[k].palavra, V[j].palavra);
        free(V[j].palavra);
        w[k].freq = V[j].freq;
        k++;
        j++;
    }
    for (i = inicio; i < fim; ++i){
        V[i].palavra = malloc(strlen(w[i - inicio].palavra)*sizeof(char));
        strcpy(V[i].palavra, w[i - inicio].palavra);
        free(w[i - inicio].palavra);
        V[i].freq = w[i - inicio].freq;
    }
    free(w);
}
Buffer *criaBuffer()
{
    Buffer *B = malloc(sizeof(Buffer));
    B->max = 8;
    B->top = 0;
    B->palavra = malloc(B->max*sizeof(char));
    return B;
}
BufferData *criaBufferData()
{
    BufferData *B = malloc(sizeof(BufferData));
    B->max = 8;
    B->top = 0;
    B->info = malloc(B->max*sizeof(data));
    return B;
}
void realocaBuffer(Buffer *B)
{
    int i;
    char *Temp;
    Temp = malloc(2*B->max*sizeof(char));
    for(i = 0; i < B->max; i++)
        Temp[i] = B->palavra[i];
    free(B->palavra);
    B->max = 2*B->max;
    B->palavra = Temp;
    return;
}
void realocaBufferData(BufferData *B)
{
    int i;
    data *Temp;
    Temp = malloc(2*B->max*sizeof(data));
    for(i = 0; i < B->top; i++){
        Temp[i].palavra = malloc(strlen(B->info[i].palavra)*sizeof(char));
        strcpy(Temp[i].palavra, B->info[i].palavra);
        Temp[i].freq = B->info[i].freq;
    }
    for(i = 0; i < B->max; i++){
        free(B->info[i].palavra);
    }
    free(B->info);
    B->max = 2*B->max;
    B->info = Temp;
    return;
}
void adicionaNoBuffer(Buffer *B, char c)
{
   
    if(B->top == B->max) realocaBuffer(B);
    B->palavra[B->top] = c;
    B->top++;
    return;
}
void adicionaNoBufferData(BufferData *B, data *Novo)
{
    
    if(B->top == B->max) realocaBufferData(B);
    B->info[B->top].palavra = malloc(strlen(Novo->palavra)*sizeof(char));
    strcpy(B->info[B->top].palavra, Novo->palavra);
    B->info[B->top].freq = Novo->freq;
    B->top++;
    return;
}
void destroiBuffer(Buffer *B)
{
    free(B->palavra);
    free(B);
    return;
}
void destroiBufferData(BufferData *B)
{
    int i;
    for(i = 0; i < B->top; i++){
        free(B->info[i].palavra);
    }
    free(B->info);
    free(B);
    return;
}
void clearBuffer(Buffer *B)
{
   /*reinicia o buffer */
    B->top = 0;
    return;
}
