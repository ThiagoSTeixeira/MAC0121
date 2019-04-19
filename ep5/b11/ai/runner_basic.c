#include "../robot_fight.h"
#include <time.h>
#include <stdlib.h>

/*Runner_basic -- Codename: Billy the Robot*/
/*Criado e desenvolvido pelo meu melhor amigo, Ricardo Fonseca*/
/*                                            

	Billy the Robot nao conhece limites. Ele
	nao conhece dor. Ele nao sabe o que eh score.
	Ele apenas conhece uma palavra: correr.
	E ele faz isso. Muito bem. Estupidamente bem.
	Tão bem que de vez em quando ele corre em cima
	de algumas tiros ou fica encarando paredes,
	mas nada que pare seu espirito de corredor.
	Exceto a morte, isso deixa Billy parado muito bem.

*/

/*Segura a direcao aleatoria que Billy esta seguindo*/
static int turn_dir = -1;

/*Checa se a posicao dada esta dentro do mapa e nao esta
sendo ocupada*/
int valid(Position p, int m, int n, Grid *g) {
	return ((p.x >= 0 && p.x < m && p.y >= 0 && p.y < n) && (g->map[p.x][p.y].type == NONE));
}

void prepareGame(Grid *g, Position p, int turnCount) {
	
}

/*Dada uma direcao inicial e uma direcao final, ve
para qual lado virando eh mais rapido de se chegar*/
Action fastTurn(int ini, int end) {
	int dif = end-ini;
	if((dif <= 3 && dif >= 0) || (dif <= -3))
		return TURN_RIGHT;
	else
		return TURN_LEFT;		
}

/*Escolha uma direcao validao aleatoria. Se
apos 20 tentativas nao encontrar nenhuma, manda ficar
parado.*/
int chooseDir(Grid *g, Position p) {
	int i, j;
	Position s;
	i = rand() % 6;
	s = getNeighbor(s, i);
	j = 0;
	while(!valid(s, g->m, g->n, g) && j < 20) {
		i = rand() % 6;
		s = getNeighbor(s, i);
		j++;
	}
	if (j == 10)
		return -1;
	else
		return i;
}

/*Como Billy faz sua pseudo-magia*/
Action run(Grid *g, Position p, Robot *r) {
	int i;
	Position s;
	/*Se Billy ja esta em sua direcao de vida, ele
	a persegue sem fim... ou ate encontrar um
	obstaculo.*/
	if(r->dir == turn_dir) {
		s = getNeighbor(p, turn_dir);
		if(valid(s, g->m, g->n, g)){
			return WALK;
		}
		turn_dir = -1;
	}
	/*Billy chegou aos limites fisicos do mundo, e
	precisa encontrar uma nova direcao de vida*/
	if(turn_dir == -1) {
		i = chooseDir(g, p);
		if (i == -1)
			return STAND;
		else {
			turn_dir = i;
		}
	}
	return fastTurn(r->dir, turn_dir);
}

/*Simples e concisa, Billy so precisa correr para viver*/
Action processTurn(Grid *g, Position p, int turnsLeft) {
	Robot *r = &g->map[p.x][p.y].object.robot;
	
	return run(g, p, r);
}