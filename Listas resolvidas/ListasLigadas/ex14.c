#include <stdio.h>
#include <stdlib.h>

typedef struct cel {
	float coef;
	int expo;
	struct cel * prox;
} celula;

typedef celula * polinomio;

polinomio soma (polinomio x1, polinomio x2) {
	polinomio p = x1, q = x2, ant = NULL;

	while (p != NULL && p != NULL) {

		if (p -> expo == q -> expo) {

			if (p -> coef + q -> coef == 0)

				if (ant == NULL) {
					ant = p;
					p = p -> prox;
					an
				}
		}
	}
}