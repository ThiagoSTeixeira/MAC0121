#include <stdio.h>
#include <stdlib.h>

void ImprimeVetor (int v[], int n);
void MergeSort (int v[], int ini, int fim);
void QuickSort (int v[], int ini, int fim);
void HeapSort (int v[], int n);
void BubbleSort (int v[], int n);

int main () {
  int n = 17;

  printf("MergeSort:\n\n");

  int v[17] = { 12, 23, 5, 9, 19, 0, 24, 4, 1, 12, 21, 2, 5, 14, -9, 10, 14 };
  ImprimeVetor(v, n);
  MergeSort(v, 0, n);
  ImprimeVetor(v, n);

  printf("----------//----------\n");
  printf("QuickSort:\n\n");

  int b[17] = { 12, 23, 5, 9, 19, 0, 24, 4, 1, 12, 21, 2, 5, 14, -9, 10, 14 };
  ImprimeVetor(b, n);
  QuickSort(b, 0, n);
  ImprimeVetor(b, n);

  printf("----------//----------\n");
  printf("HeapSort:\n\n");

  int m[17] = { 12, 23, 5, 9, 19, 0, 24, 4, 1, 12, 21, 2, 5, 14, -9, 10, 14 };
  ImprimeVetor(m, n);
  HeapSort(m, n);
  ImprimeVetor(m, n);

  printf("----------//----------\n");
  printf("BubbleSort:\n\n");

  int x[17] = { 12, 23, 5, 9, 19, 0, 24, 4, 1, 12, 21, 2, 5, 14, -9, 10, 14 };
  ImprimeVetor(x, n);
  BubbleSort(x, n);
  ImprimeVetor(x, n);

  return 0;
}

void ImprimeVetor (int v[], int n) {
  int i;

  for (i = 0; i < n; i++) {
    printf("%d ", v[i]);

  }

  printf("\n\n");
}

//--------------------MERGE SORT--------------------

void Intercala (int v[], int ini, int meio, int fim) {
  int k = ini, i = meio, j = 0, m, n;
  int *aux = malloc(sizeof(int) * (fim - ini));

  while (i < fim && k < meio) {

    if (v[i] < v[k]) {
      aux[j] = v[i];
      i++;
    }

    else {
      aux[j] = v[k];
      k++;
    }

    j++;
  }

  while (i < fim) {
    aux[j] = v[i];
    i++;
    j++;
  }

  while (k < meio) {
    aux[j] = v[k];
    k++;
    j++;
  }

  for (m = ini, n = 0; m < fim; m++, n++)
    v[m] = aux[n];

  free(aux);
}

void MergeSort (int v[], int ini, int fim) {
  int meio;

  if (fim - 1 > ini) {
  meio = (fim + ini) / 2;
  MergeSort(v, ini, meio);
  MergeSort(v, meio, fim);
  Intercala(v, ini, meio, fim);
  }

}

//--------------------HEAP SORT--------------------

void Heapfica (int v[], int n) {
  int aux, f, i, k;

  for (i = 1; i < n; i++) {
    f = i;
    k = (f - 1) / 2;

    while (f >= 1 && f < n && v[k] < v[f]) {
      aux = v[f];
      v[f] = v[k];
      v[k] = aux;
      f = k;
      k = (f - 1) / 2;
    }

  }

}

void HeapSort (int v[], int n) {
  int aux;

  if (n > 1) {
    Heapfica(v, n);
    aux = v[0];
    v[0] = v[n - 1];
    v[n - 1] = aux;
    HeapSort(v, n - 1);
  }

}

//--------------------QUICK SORT--------------------

void QuickSort (int v[], int ini, int fim) {
  int i, indP = ini, aux, pivo;

  if (fim - ini > 1) {
    pivo = v[indP];
    i = fim - 1;

    while (i != indP) {

      while (i > indP) {

        if (v[i] < pivo) {
          v[indP] = v[i];
          v[i] = pivo;
          aux = i;
          i = indP + 1;
          indP = aux;
        }

        i--;
      }

      while (i < indP) {

        if (v[i] > pivo) {
          v[indP] = v[i];
          v[i] = pivo;
          aux = i;
          i = indP - 1;
          indP = aux;
        }

        i++;
      }

    }

    QuickSort(v, ini, indP);
    QuickSort(v, indP + 1, fim);

  }

}

//--------------------BUBBLE SORT--------------------

void BubbleSort (int v[], int n) {
  int trocou = 1, i, aux;

  while (trocou) {
    i = 0;
    trocou = 0;

    while (i <= n - 1) {

      if (v[i] > v[i + 1]) {
        trocou = 1;
        aux = v[i + 1];
        v[i + 1] = v[i];
        v[i] = aux;
      }

      i++;
    }

  }

}
