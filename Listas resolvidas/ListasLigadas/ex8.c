#include <stdio.h>
#include <stdlib.h>

typedef struct cel {
	int info;
	struct cel * prox;
} celula;

typedef celula* lista;

lista Remove (lista fim, int x) {
	lista ant, p;

	if (fim == NULL)
		return fim;

	p = fim -> prox;
	ant = fim;

	while (p != fim) {

		if (p -> info == x) {
			ant -> prox = p -> prox;
			free(p);
			p = ant -> prox;
		}

		else {
			ant = p;
			p = p -> prox;
		}

	}

	if (p -> info == x) {

		if (ant != p) {
			ant -> prox = p -> prox;
			free(p);
			fim = ant;
		}

		else {
			free(p);
			fim = NULL;
		}

	}

	return fim;

}