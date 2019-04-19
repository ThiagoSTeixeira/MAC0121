#include <stdio.h>
#include<stdlib.h>


int nFlips = 0;     //Inicia a variavel global nFlips, que armazenara o numero de flips realizados

int ImprimeArray(int v[], int n){
    int i;
    printf("\n");
    for(i=0; i<n; i++){
            printf("%d ",v[i]);
        }
    return(0);
}

void flip(int v[], int p, int n){   // "Flipa" os elementos em v[p ,..., n-1]
    int tamanho = n-1;
    int atual;
    while (p < tamanho){
        atual = v[p];
        v[p] = v[tamanho];
        v[tamanho] = atual;
        p++;
        tamanho--;
    }
}
int PosMax(int v[], int n, int Pa){        //Encontra o maximo em v[Pa, ..., n-1] --- Pa = posicao atual
    int pos = Pa;
    int in;
    for(in = Pa; in<n; in++){
        if(v[in] > v[pos]){
            pos = in;
        }
    }
    //printf("eh %d \n", pos);
    return(pos);
}

void Ordena(int *v, int n){          //Ordena o array v[0, ..., n-1]
    int Pa = 0;
    for(Pa = 0; Pa < n; Pa++){      //Coloca o maior valor de v[Pa, ..., n-1] na posicao Pa
        int posmax = PosMax(v, n, Pa);
        if(posmax != Pa){
            if(posmax != n-1){
                flip(v, posmax, n);
                nFlips++;
                printf("%d ", posmax);
                //ImprimeArray(v, n);
            }
            flip(v, Pa, n); // Coloca o maior elemento de v[Pa, ..., n-1] na posicao Pa
            printf("%d ", Pa);
            //ImprimeArray(v, n);
            nFlips++;
        }
    }
}

int main(){
    int i = 0;
    int n;
   // printf("Digite n \n");
    scanf("%d",&n);         //Recebe o numero n de panquecas
    int v[5000];
    for (i=0; i < n; i++){
        scanf("%d ",&v[i]);     //Recebe os diametros das panquecas
    }
    Ordena(v, n);
    //ImprimeArray(v, n);
    //printf("\n %d", nFlips);
}
