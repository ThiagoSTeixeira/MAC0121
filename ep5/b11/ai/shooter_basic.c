#include "../robot_fight.h"
#include <stdlib.h>

/*Shooter_basic -- Codename: Jill Valenbot*/
/*Criado e desenvolvido pelo meu melhor amigo, Ricardo Fonseca*/
/*                                            

	Eh dificil descrever a visao que eh Jill Valenbot
	no campo de batalha. Ou por que sua visao esta sendo
	coberta por nuvens de tiro.
	Ou por que essa visao eh Jill girando descontroladamente
	atirando para todos os lados.
	Esse eh seu estilo, essa eh sua vida. Se quiser se tornar
	campeao dos robos, primeiro tera de passar por essa fera.

*/

/*Define se eh hora de Jill se mover , atirar, ou virar*/
static int move_time = 0;
static int shoot = 1;
static int turn = 0;

/*Checa se a posicao dada esta dentro do mapa e nao esta
sendo ocupada*/
int valid(Position p, int m, int n, Grid *g) {
	return ((p.x >= 0 && p.x < m && p.y >= 0 && p.y < n) && (g->map[p.x][p.y].type == NONE));
}

void prepareGame(Grid *g, Position p, int turnCount) {

}

/*Jill esta pronta para o tiroteio*/
Action shootTime(Grid *g, Position p, Robot *r) {
	int j;
	Position s;
	/*Hora de atirar! Jill vai ficar rotacionando
	em sentido horario e atirando, ate que ela ache
	necessario mudar de posicao*/
	if(move_time == 0){
		j = rand()%200;
		if(j < 5) {
			move_time = 1;
		}
		if(shoot){
			shoot = 0;
			turn = 1;
			return SHOOT_CENTER;
		}
		else {
			shoot = 1;
			turn = 0;
			return TURN_RIGHT;
		}
	}
	/*Jill percebeu que eh hora de surpreender
	o inimigo, e mudar sua posicao tatica*/
	else {
		move_time = 0;
		s = getNeighbor(p, r->dir);
		if(valid(s, g->m, g->n, g)){
			return WALK;
		}
		else
			return SHOOT_CENTER;
	}
	/*Jill para um momento para refletir sobre a vida*/
	return STAND;
}

/*Com apenas um pensamento, Jill entra no campo de batalha:
só poder haver um campeão*/
Action processTurn(Grid *g, Position p, int turnsLeft) {
	Robot *r = &g->map[p.x][p.y].object.robot;
	
	return shootTime(g, p, r);
}