#include "listaligada.h"

lista InsereNoFim (lista l, int x) {
	lista p = l, novo;

	novo = malloc(sizeof(celula));
	novo -> val = x;
	novo -> prox = NULL;
	novo -> ant = NULL;

	if (p == NULL)
		return novo;

	while (p -> prox != NULL)
		p = p -> prox;

	p -> prox = novo;
	novo -> ant = p;
}

void InsereOrdenado (lista l, int x) {
	lista novo, p, q;
	novo = malloc(sizeof(celula));
	novo -> val = x;
	novo -> prox = NULL;
	novo -> ant = NULL;

	p = l;

	while (p != NULL && p.val < x)
		p = p -> prox;

	if (p != NULL) {
		q = p -> ant;
		q -> prox = novo;
		novo -> ant = q;
		novo -> prox = p;
		p -> ant = novo;
	}

	else {
		p -> prox = novo;
		novo -> ant = p;
	}

}

void Remove (lista l, int x) {
	lista p = l;

	while (p != NULL && p -> val != x)
		p = p -> prox;

	if (p != NULL) {
		q = p -> ant;
		p = p -> prox;
		q -> prox = p;

		if (p != NULL)
			p -> ant = q;
	}

}