#include <stdio.h>
#include <stdlib.h>

void imprimematriz(int** v, int m, int n);
int BuscaNaMatriz(int** v, int m, int n, int x);

int main () {
    int m, n, i, j, x;
    int** v;

    scanf("%d %d", &m, &n);

    if (m != 0 && n != 0) {
        v = malloc(sizeof(int*) * m);

        for (i = 0; i < m; i++) {
            v[i] = malloc(sizeof(int) * n);

            for (j = 0; j < n; j++)
                scanf("%d", &v[i][j]);

        }
    
    }
    
    scanf("%d", &x);

    if (!BuscaNaMatriz(v, m, n, x))
        printf("Não achou :-(\n\n");

    return 0;
}

void imprimematriz (int** v, int m, int n) {
    int i, j;

    for (i = 0; i < m; i++) {

        for (j = 0; j < n; j++)
            printf("%d ", v[i][j]);

        printf("\n");
    }

}

int BuscaNaMatriz (int** v, int m, int n, int x) {
    int i = 0, j = n - 1;

    while (i < m && j >= 0) {

        if (v[i][j] < x)
            i++;

        else if (v[i][j] > x)
            j--;

        else {
            printf("[%d, %d]\n", i, j);
            return 1;
        }

    }
    return 0;
}