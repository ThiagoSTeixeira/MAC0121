#include <stdio.h>
#include <stdlib.h>

int main () {
	return 0;
}

void ordena (int V[], int n) {
	int i, j, *cont, *aux;

	cont = malloc(sizeof(int) * n);
	aux = malloc(sizeof(int) * n);

	for (i = 0; i < n; i++)
		cont[i] = 0;

	for (i = 0; i < n; i++) {

		for (j = 0; j < n; j++)

			if (i != j && V[j] < V[i]) cont[i]++;

		aux[cont[i]] = V[i];
	}

	for (i = 0; i < n; i++)
		V[i] = aux[i];

	free(aux);
	free(cont);
}