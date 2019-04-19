#include <stdio.h>
#include <stdlib.h>

typedef struct cel {
	int val;
	struct cel * prox;
} celula;

typedef celula* lista;

typedef struct cab {
	lista prox;
} cabeca;

typedef cabeca* inicio;

//a)

inicio InsereOrdenado (inicio l, int x) {
	lista novo, p, q;
	novo = malloc(sizeof(celula));
	novo -> val = x;
	novo -> prox = NULL;
	p = l -> prox;

	while (p != NULL && p -> val < x) {
		q = p;
		p = p -> prox;
	}

	if (p != NULL) {
		q -> prox = novo;
		novo -> prox = p;
	}

	else
		p -> prox = novo;

	return l;
}