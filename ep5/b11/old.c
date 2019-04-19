#include "../robot_fight.h"

/* Broona, um(a) guerreiro(a) que as vezes vira um pão
 *
 *
 */

static enum {
	AGGRO, BREAD
} mode;

static int life_before;
static int life;

static int livre(Position p, int m, int n, Grid *g) {
	return ((p.x >= 0 && p.x < m && p.y >= 0 && p.y < n) && (g->map[p.x][p.y].type == NONE));
}

static int num_viradas(int ini, int end) {
	int i, j;
	for(i = ini, j = 0; i != end; i = (i+1)%6, j++)
		if (i >= 6) i-= 6;
	if (j > 3) j = 6-j;
	return j;
}

static Action sentido_virada(int ini, int end) {
	int dif = end-ini;
	if((dif <= 3 && dif >= 0) || (dif <= -3))
		return TURN_RIGHT;
	else
		return TURN_LEFT;		
}

static int eh_ponto_de_controle(Grid *grid, Position pos) {
	return grid->map[pos.x][pos.y].isControlPoint;
}

static int eh_inimigo(Grid *grid, Position pos) {
	return grid->map[pos.x][pos.y].type == ROBOT;
}

static int ponto_proximo(Grid *g, Position p, Robot *r) {
	int i, min = 500, best_dir = 0, cont;
	for(i = 0; i < 6; i++) {
		/*Conta para chegar o numero de viradas necessarias
		ja que elas gastam um turno*/
		cont = 1 + num_viradas(r->dir, i);
		Position s = getNeighbor(p,i);
		while(livre(s, g->m, g->n, g)) {
			if(eh_ponto_de_controle(g,s)) {
				if(cont < min) {
					min = cont;
					best_dir = i;
					break;
				}
			}
			cont++;
			s = getNeighbor(s, i);
		}
	}

	/*Nao existe control points no mapa*/
	if (min == 500)
		return -1;
	
	else
		return best_dir;
}

static int inimigo_proximo(Grid *g, Position p, Robot *r) {
	int i, min = 500, best_dir = 0, cont;
	for(i = 0; i < 6; i++) {
		/*Conta para chegar o numero de viradas necessarias
		ja que elas gastam um turno*/
		cont = 1 + num_viradas(r->dir, i);
		Position s = getNeighbor(p,i);
		while(livre(s, g->m, g->n, g)) {
			if(eh_inimigo(g,s)) {
				if(cont < min) {
					min = cont;
					best_dir = i;
					break;
				}
			}
			cont++;
			s = getNeighbor(s, i);
		}
	}

	/*Nao existe control points no mapa*/
	if (min == 500)
		return -1;
	
	else
		return best_dir;
}

void prepareGame(Grid *grid, Position pos, int turnCount) {
	mode = BREAD;
	setName("Broona (^_^)");
	Robot *r = &grid->map[pos.x][pos.y].object.robot;
	life = r->hp;
	life_before = r->hp;

}

Action processTurn(Grid *grid, Position pos, int turnsLeft) {
	Robot *r = &grid->map[pos.x][pos.y].object.robot;
	Position s;
	int control_dir, i, j;

	life_before = life;
	life = r->hp;

	if(life_before > life) mode = AGGRO;

	switch(mode) {
		case AGGRO:
			setName("Broona Brava >.<");
			if(grid->map[pos.x][pos.y].object.robot.bullets < 5) mode = BREAD;
			control_dir = inimigo_proximo(grid, pos, r);
			if (control_dir == -1) {
				for(i = r->dir, j = 0; j < 6; i++,j++){
					if (i >= 6) i-=6;
					s = getNeighbor(pos,i);
					if(livre(s, grid->m, grid->n, grid)) {
						if(i == r->dir) {
							return SHOOT_CENTER;
						}
						else {
							return sentido_virada(r->dir, i);
						}
					}
				}
				/*Se nenhuma posicao em volta eh valida, SAD TIME*/
				return STAND;
			}
			else if(control_dir == r->dir)
				return WALK;
			else
				return sentido_virada(r->dir, control_dir);
		break;
		case  BREAD:
			if(eh_ponto_de_controle(grid, pos)) break;
			control_dir = ponto_proximo(grid, pos, r);
			if (control_dir == -1) {
				for(i = r->dir, j = 0; j < 6; i++,j++){
					if (i >= 6) i-=6;
					s = getNeighbor(pos,i);
					if(livre(s, grid->m, grid->n, grid)) {
						if(i == r->dir) {
							return WALK;
						}
						else {
							return sentido_virada(r->dir, i);
						}
					}
				}
				/*Se nenhuma posicao em volta eh valida, SAD TIME*/
				return STAND;
			}
			else if(control_dir == r->dir)
				return WALK;
			else
				return sentido_virada(r->dir, control_dir);
		break;
		default:
			return STAND;
	}
	return STAND;
}
