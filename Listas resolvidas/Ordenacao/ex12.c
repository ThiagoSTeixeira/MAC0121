#include <stdio.h>
#include <stdlib.h>

void ImprimeVetor (int v[], int ini, int fim) {
  int i;

  printf("[ ");

  for (i = ini; i < fim; i++) {
    printf("%d ", v[i]);

  }

  printf("]");

  printf("\n\n");
}

int NumeroDeInversoes (int v[], int ini, int meio, int fim) {
  int nInv = 0, p = ini, q = meio;

  while (p < meio && q < fim) {

    if (v[q] > v[p]) {
      nInv++;
      p++;
    }

    else {
      q++;

      if (q != fim)
        nInv += (p - ini);

    }

  }

  while (q < fim) {
    q++;

    if (q != fim)
      nInv += (p - ini);

  }

  return nInv;
}

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

int MergeSort (int v[], int ini, int fim) {
  int meio, inversoes = 0;

  if (fim - 1 > ini) {
  meio = (fim + ini) / 2;
  inversoes += MergeSort(v, ini, meio);
  inversoes += MergeSort(v, meio, fim);
  inversoes += NumeroDeInversoes(v, ini, meio, fim);
  Intercala(v, ini, meio, fim);
  }

  return inversoes;
}

int main () {
  int v[8] = {12, 5, 13, 8, 1, 7, 2, 10};
  // int v[8] = {5, 5, 5, 5, 5, 2, 1, 3};
  int resp;

  resp = MergeSort(v, 0, 8);
  //sol = nInversoes(v, 8);

  printf("Numero de Inversoes = %d\n", resp);
  ImprimeVetor(v, 0, 8);
  // printf("sol = %d\n", sol);
}