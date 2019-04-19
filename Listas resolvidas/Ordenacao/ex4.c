#include <stdio.h>
#include <stdlib.h>

void imprime (int v[], int n);
int* merge (int a[], int m, int b[], int n);

int main () {

    // ------------------//------------------
    // int m = 5;
    // int n = 10;
    // int a[5] = {1, 2, 3, 4, 5};
    // int b[10] = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    // ------------------//------------------
    // int m = 5;
    // int n = 10;
    // int a[5] = {11, 12, 13, 14, 15};
    // int b[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // ------------------//------------------
    int m = 10;
    int n = 10;
    int a[10] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int b[10] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    // ------------------//------------------
    int* c = merge(a, m, b, n);
    imprime(c, m + n);
    return 0;

}

void imprime (int v[], int n) {
    int i;

    for (i = 0; i < n; i++)
        printf("%d ", v[i]);
    
    printf("\n");
}

int* merge (int a[], int m, int b[], int n) {
    int x = 0, z = m + n, contA = 0, contB = 0;
    int* c = malloc(sizeof(int) * z);

    while (contA < m && contB < n) {

        if (a[contA] < b[contB]) {
            c[x] = a[contA];
            contA++;
        }

        else if (a[contA] > b[contB]) {
            c[x] = b[contB];
            contB++;
        }

        else {
            c[x] = a[contA];
            contA++;
            contB++;
        }

        x++;
    }

    while (contA < m) {
        c[x] = a[contA];
        contA++;
        x++;
    }

    while (contB < n) {
        c[x] = b[contB];
        contB++;
        x++;
    }

    return c;
}