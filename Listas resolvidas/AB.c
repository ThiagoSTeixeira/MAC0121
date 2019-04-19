#include <stdio.h>
#include <stdlib.h>

typedef struct no {
	int info;
	struct no * pai;
	struct no * dir;
	struct no * esq;
} No;

typedef No * arvore;

void inOrdem(arvore raiz) {

	if (raiz != NULL) {
		inOrdem(raiz -> esq);
		printf("%d ", raiz -> info);
		inOrdem(raiz -> dir);
	}

}

void preOrdem (arvore raiz) {

	if (raiz != NULL) {
		printf("%d ", raiz -> info);
		preOrdem(raiz -> esq);
		preOrdem(raiz -> dir);
	}

}

typedef struct vet {
	int * v;
	int i;
} vetor;

typedef vetor * Vetor;

Vetor PercorreIn (arvore raiz, Vetor vetor) {

	if (raiz != NULL) {
		vetor = PercorreIn(raiz -> esq, vetor);
		vetor -> v[vetor -> i] = raiz -> info;
		vetor -> i++;
		vetor = PercorreIn(raiz -> dir, vetor);
	}

	return vetor;
}

Vetor PercorrePre (arvore raiz, Vetor vetor) {

	if (raiz != NULL) {
		vetor -> v[vetor -> i] = raiz -> info;
		vetor -> i++;
		vetor = PercorrePre(raiz -> esq, vetor);
		vetor = PercorrePre(raiz -> dir, vetor);
	}

	return vetor;
}

//Ex 1 ----------------------//----------------------

int contaNos (arvore raiz) {

	if (raiz == NULL)
		return 0;

	return contaNos(raiz -> dir) + contaNos(raiz -> esq) + 1;
}

//Ex 2 ----------------------//----------------------

int ancestralI (arvore x, arvore y) {

	if (x == NULL || y == NULL)
		return 0;

	if (x == y)
		return 1;

	return (ancestralI(x -> esq, y) || ancestralI(x -> dir, y));
}

//Ex 3 ----------------------//----------------------

int ancestralII (arvore x, arvore y) {

	if (x == NULL || y == NULL)
		return 0;

	if (x == y)
		return 1;

	return ancestralII(x, y -> pai);
}

//Ex 4 ----------------------//----------------------

/*
	In-Ordem: HJNBCGEADOMPKILF
	Pre-Ordem: ACBHJNEGDFIKMOPL
	Pos-Ordem: NJHBGECOPMKLIFDA
*/

//Ex 5 ----------------------//----------------------

int encontra (int ini, int fim, int raiz, int inO[]) {
	int i = ini;

	while (i <= fim) {

		if (inO[i] == raiz)
			return i;

		i++;
	}

	return -1;
}

arvore reconstruir (int ini, int fim, Vetor preO, Vetor inO) {

	if (fim < ini)
		return NULL;

	arvore no = malloc(sizeof(No));
	no -> info = preO -> v[preO -> i];

	int raiz = no -> info;
	int i = encontra(ini, fim, raiz, inO -> v);

	preO -> i++;
	no -> esq = reconstruir(ini, i - 1, preO, inO);
	no -> dir = reconstruir(i + 1, fim, preO, inO);

	return no;
}

arvore Reconstroi (Vetor preO, Vetor inO, int n) {
	preO -> i = 0;
	return reconstruir (0, n - 1, preO, inO);
}

//Ex 6 ----------------------//----------------------

int profundidade (arvore no) {
	// Retorna -1 quando o no eh NULL...
	int prof = -1;
	arvore aux = no;

	while (aux != NULL) {
		prof++;
		aux = aux -> pai;
	}

	return prof;
}

//Ex 7 ----------------------//----------------------

void imprimeArvore (arvore raiz, int prof) {
	int i;

	if (raiz != NULL) {
		imprimeArvore(raiz -> dir, prof + 1);

		for (i = 0; i < prof; i++)
			printf("  ");

		printf("%d\n", raiz -> info);

		imprimeArvore(raiz -> esq, prof + 1);
	}
}

//Ex 8 ----------------------//----------------------

arvore minimo (arvore raiz) {
	arvore p = raiz, q = NULL;

	while (p != NULL) {
		q = p;
		p = p -> esq;
	}

	return q;
}

arvore devolveProximoInOrdem (arvore raiz) {
	arvore p = raiz, q = NULL;

	if (raiz -> dir != NULL)
		return minimo(raiz -> dir);

	while (p != NULL && p -> dir == q) {
		q = p;
		p = p -> pai;
	}

	return p;
}

//Ex 10 ----------------------//----------------------

typedef struct ceu {
	int info;
	int efio, dfio;
	struct ceu * pai;
	struct ceu * dir;
	struct ceu * esq;
} nou;

typedef nou * apontador;

apontador Minimo (apontador raiz) {
	apontador p = raiz, q = NULL;

	while (p != NULL) {
		q = p;
		p = p -> esq;
	}

	return q;
}

apontador Maximo (apontador raiz) {
	apontador p = raiz, q = NULL;

	while (p != NULL) {
		q = p;
		p = p -> dir;
	}

	return q;
}

apontador insereAp (apontador raiz, int x) {
	apontador p, q, novo;
	q = NULL;
	p = raiz;

	novo = malloc(sizeof(No));
	novo -> info = x;
	novo -> efio = 0;
	novo -> dfio = 0;
	novo -> dir = NULL;
    novo -> esq = NULL;
    novo -> pai = NULL;

	while (p != NULL && p -> info != x) {
		q = p;

		if (p -> info > x)
			p = p -> esq;

		else
			p = p -> dir;
	}

	if (p == NULL) {

		if (q == NULL)
			return novo;

		if (q -> info > x)
			q -> esq = novo;

		else
			q -> dir = novo;

		novo -> pai = q;
	}

	return raiz;
}

apontador ant (apontador raiz) {
    apontador p = raiz;
    apontador q = raiz -> pai;

	while (q != NULL && q -> esq == p) {
		p = q;
		q = q -> pai;
	}

    return q;
}

apontador prox (apontador raiz) {
    apontador p = raiz;
    apontador q = raiz -> pai;

	while (q != NULL && q -> dir == p) {
		p = q;
		q = q -> pai;
	}

    return q;
}

apontador Fios (apontador raiz) {

	if (raiz != NULL) {

		if (raiz -> dir != NULL && Minimo(raiz -> dir) == raiz -> dir)
			raiz -> dfio = 1;

		if (raiz -> esq != NULL && Maximo(raiz -> esq) == raiz -> esq)
			raiz -> efio = 1;

		raiz -> esq = Fios(raiz -> esq);
		raiz -> dir = Fios(raiz -> dir);
	}

	return raiz;
}

apontador SEA (apontador raiz) {

	if (raiz != NULL) {
		raiz -> esq = SEA(raiz -> esq);
		raiz -> dir = SEA(raiz -> dir);
		
		if (raiz -> esq == NULL) {
			raiz -> esq = ant(raiz);
			raiz -> efio = 1;
		}

		if (raiz -> dir == NULL) {
			raiz -> dir = prox(raiz);
			raiz -> dfio = 1;
		}

	}

	return raiz;
}

apontador ArvoreComFios (apontador raiz) {
	raiz = Fios(raiz);
	raiz = SEA(raiz);
	return raiz;
}

//Ex 11 ----------------------//----------------------

/*
	a. Nao
	b. Sim
	c. Nao
*/

//Ex 12 ----------------------//----------------------

arvore insere (arvore raiz, int x) {
	arvore p, q, novo;
	q = NULL;
	p = raiz;

	novo = malloc(sizeof(No));
	novo -> info = x;
	novo -> pai = NULL;
	novo -> dir = NULL;
    novo -> esq = NULL;

	while (p != NULL && p -> info != x) {
		q = p;

		if (p -> info > x)
			p = p -> esq;

		else
			p = p -> dir;
	}

	if (p == NULL) {

		if (q == NULL)
			return novo;

		if (q -> info > x)
			q -> esq = novo;

		else
			q -> dir = novo;

		novo -> pai = q;
	}

	return raiz;
} 

//Ex 13 ----------------------//----------------------

/*
					______50______
				   /              \
			  ___30___         ___70___
			 /        \       /        \
            20        40     60        80
           /  \      /  \
          15  25    35  45
                     \
                      36

                    ______50______
				   /              \
			  ___25___         ___70___
			 /        \       /        \
            20        40     60        80
           /         /  \
          15        35  45
                     \
                      36
*/ 

//Ex 14 ----------------------//----------------------

int maiorQue (arvore raiz, int x) {

	if (raiz != NULL) {

		if (raiz -> info >= x)
			return 0;

		return (maiorQue(raiz -> esq, x) && maiorQue(raiz -> dir, x));
	}

	return 1;

}

int menorQue (arvore raiz, int x) {

	if (raiz != NULL) {

		if (raiz -> info <= x)
			return 0;

		return (maiorQue(raiz -> esq, x) && maiorQue(raiz -> dir, x));
	}

	return 1;

}

//Ex 15 ----------------------//----------------------

arvore maximo (arvore raiz) {
	arvore p = raiz, q = NULL;

	while (p != NULL) {
		q = p;
		p = p -> dir;
	}

	return q;
}

int ehABB (arvore raiz) {
	int p, q;
	arvore max, min;

	if (raiz != NULL) {
		p = ehABB(raiz -> dir);
		q = ehABB(raiz -> esq);

		if (p && q) {
			max = maximo(raiz -> esq);
			min = minimo(raiz -> dir);

			if ((max == NULL || max -> info < raiz -> info)
				&& (min == NULL || min -> info > raiz -> info)) {
				return 1;
			}

		}

		return 0;
	}

	return 1;
}

// Extra ----------------------//----------------------

arvore Constroi (Vetor vet, int ini, int fim) {

	if (fim < ini)
		return NULL;

	int meio = (fim + ini) / 2;

	arvore no = malloc(sizeof(No));
	no -> info = vet -> v[meio];

	no -> dir = Constroi(vet, meio + 1, fim);
	no -> esq = Constroi(vet, ini, meio - 1);

	return no;
}

arvore MontaArvoreBalanceada (arvore raiz, Vetor vet, int n) {
	arvore nova = Constroi(vet, 0, n - 1);
	return nova;
}

// ----------------------//----------------------

void DestroiArvore (arvore raiz) {

	if (raiz != NULL) {
		DestroiArvore(raiz -> esq);
		DestroiArvore(raiz -> dir);
		free(raiz);
	}

}

apontador Inicio (apontador raiz) {
	apontador p = raiz, q = NULL;

	while (p != NULL && p -> esq != raiz -> pai) {
		q = p;
		p = p -> esq;
	}

	if (p != NULL)
		return p;

	return q;
}

void imprimeAP(apontador raiz) {
	apontador p = Inicio(raiz);

	while (p != NULL) {
		printf("raiz = %d\n", p -> info);

		if (p -> dfio == 1)
			p = p -> dir;

		else {
			p = Inicio(p -> dir);
		}

	}

}

void imprimeApSemSEA (apontador raiz, int prof) {
	int i;

	if (raiz != NULL) {
		imprimeApSemSEA(raiz -> dir, prof + 1);

		for (i = 0; i < prof; i++)
			printf("   ");

		printf("%d\n", raiz -> info);

		imprimeApSemSEA(raiz -> esq, prof + 1);
	}

}

// ----------------------//----------------------

int main () {

	arvore raiz = NULL;
	int i, n, x;
	scanf("%d", &n);

	for (i = 0; i < n; i++) {
		scanf("%d", &x);
		raiz = insere(raiz, x);
	}

	if (ehABB(raiz))
		printf("Eh ABB\n");

	else
		printf("Nao eh ABB\n");

	DestroiArvore(raiz);
	return 0;
}