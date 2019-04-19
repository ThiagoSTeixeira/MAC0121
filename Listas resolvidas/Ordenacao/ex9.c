#include <stdio.h>
#include <stdlib.h>

void ImprimeVetor (int v[], int n) {
  int i;

  for (i = 0; i < n; i++) {
    printf("%d ", v[i]);

  }

  printf("\n\n");
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

void MergeSort (int v[], int ini, int fim) {
  int meio;

  if (fim - 1 > ini) {
  meio = (rand() % (fim - ini)) + ini;
  MergeSort(v, ini, meio);
  MergeSort(v, meio, fim);
  Intercala(v, ini, meio, fim);
  }

}

int main () {
	int n = 8;
	int v[8] = {7, 8, 10, 12, 13, 1, 2, 5};
	ImprimeVetor(v, n);
	MergeSort(v, 0, n);
	ImprimeVetor(v, n);
	return 0;
}