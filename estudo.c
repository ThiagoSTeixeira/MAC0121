#include <stdio.h>
#include <stdlib.h>
//Prova rec MAC0121
//Pilhas

/*
    Questao 2: A C E R T O U
    Questao 3: 1-nao 2- a*l*g*o*r*t*m*o  3-omtirogla*******
    

typedef struct {
    char* v;
    int topo;
    int max;
} pilha;

typedef pilha *Pilha;

Pilha CriaPilha(int max) {
    Pilha P = malloc(sizeof(pilha));
    P -> v = malloc(max*sizeof(char));
    P->topo = 0;
    P -> max = max;
    return P;
}

int PilhaVazia(Pilha P){
    return P->topo == 0;
}

void Empilha(Pilha P, char d) {
    P->v[P->topo] = d;
    P->topo++;
}
void Desempilha(Pilha P) {
    (P->topo)--;
}
char TopoDaPilha(Pilha P){
    return P->v[P->topo -1];
}
int main() {
    Pilha P = CriaPilha(100);
char* frase = malloc(100*sizeof(char));
    frase = "ESTE EXERCICIO E MUITO FACIL. ";
    int i = 0;
    while(frase[i] != '.'){
        while(frase[i] != ' '){
            Empilha(P, frase[i]);
        }
        while(!PilhaVazia(P)){
            printf("%c",TopoDaPilha(P));
            Desempilha(P);
        }
    }
}
*/
///////////////////////////////////////////

//Recursao

//Ex 3

int Digito(n){
    if(n/10 != 0){
        return(Digito(n/10) + 1);
    }
    else return(1);
}

int main(){
    int n;
    int r;
    scanf("%d", &n);
    r = Digito(n);
    printf("%d\n", r);
    return 0;

}
