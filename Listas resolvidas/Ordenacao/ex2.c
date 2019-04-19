#include <stdio.h>
#include <stdlib.h>

void imprime (int v[], int n);
void separa (int v[], int n);

int main () {
    int v[10] = {1, 1, 1, 1, 1, 0, 0, 0, 0, 0};
    imprime(v, 10);
    separa(v, 10);
    imprime(v, 10);
    return 0;
}

void imprime (int v[], int n) {
    int i;

    for (i = 0; i < n; i++)
        printf("%d ", v[i]);
    
    printf("\n");
}

void separa (int v[], int n) {
    int aux, valor, pivo, i;

    if (n > 0) {
        valor = 0;
        pivo = v[0];
        i = n - 1;

        while (i != valor) {

            while (i > valor && v[i] == pivo)
                i--;

            if (i != valor) {
                v[valor] = v[i];
                v[i] = pivo;
                aux = valor;
                valor = i;
                i = aux + 1;
            }

            while (i < valor && v[i] != pivo)
                i++;
            
            if (i != valor) {
                v[valor] = v[i];
                v[i] = pivo;
                aux = valor;
                valor = i;
                i = aux - 1;
            }
            
        }
    }

}