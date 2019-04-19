//Thiago Santos Teixeira nUSP 10736987

#include "../robot_fight.h"
#include <stdlib.h>
static int adjacentes[6];
typedef enum {SAUDAVEL, RISCO} vidaRobo;


int isRobot (Grid *g, Position p) { //tem um robo aqui?
	if (g->map[p.x][p.y].type == ROBOT) return 1;
	return 0;
}


int DentroDoMapa (Position pos, int m, int n){  //esta dentro do mapa?
	return ((pos.x >= 0 && pos.x < m) && (pos.y >= 0 && pos.y < n));
}


int valida (Position p, int m, int n, Grid *g) {     //esta vazia e dentro do mapa?
	return ((p.x >= 0 && p.x < m && p.y >= 0 && p.y < n) && (g->map[p.x][p.y].type == NONE));
}

int isControlPoint (Grid *g, Position p) {  //eh ponto de controle?
	return (g->map[p.x][p.y].isControlPoint);	
}

int isProjectile (Grid *g, Position p) {    //eh um tiro?
	if (g->map[p.x][p.y].type == PROJECTILE)
		return 1;
	return 0;
}

vidaRobo vidaAtual (Grid *g, Position p) {      //o robo esta em risco ou nao?
	int hpAtual;
	hpAtual = g->map[p.x][p.y].object.robot.hp;
	if (hpAtual >= 20) return (SAUDAVEL);
	return (RISCO);
}

// preenche o vetor das posicoes ao redor do robo 
void encontrarAdjacentes (Position pos, Grid *grid){
	int i;
	Position p;
	for (i = 0; i < 6; i++){
		p = getNeighbor (pos, i);
		if (DentroDoMapa (p, grid->m, grid->n)) adjacentes[i] = grid->map[p.x][p.y].type;
		else adjacentes[i] = -1;
	}
}


int nViradas (int ini, int end) {  //qual o menor n de viradas necessarias?
	int i, j;
	for(i = ini, j = 0; i != end; i = (i+1)%6, j++)
		if (i >= 6) i-= 6;
	if (j > 3) j = 6-j;
	return j;
}


Action ladoVirada (int ini, int end) {    //qual direcao?
	int dif = end-ini;
	if((dif <= 3 && dif >= 0) || (dif <= -3))
		return TURN_RIGHT;
	else
		return TURN_LEFT;		
}


int inimigoProximo (Position pos, Grid *grid, Robot *r)   // Ha inimigos ao lado?
{
	int i;
	Position rob_pos;
	Robot *rob;
	for (i = 0; i < 6; i++){
		if (adjacentes[i] == ROBOT){
			rob_pos = getNeighbor (pos, i);
			rob = &grid->map[rob_pos.x][rob_pos.y].object.robot;
			if ((rob->dir + 3)%6 == i) return 1;
		}
	}
	return 0;
}
//funcao retirada do controller_basic
/*Dado uma posicao, checa se para alguma direcao
existe um control point, e retorna qual direcao esta
o mais perto, contando giradas necessárias*/
int searchNearestControl(Grid *g, Position p, Robot *r) {
	int i, min = 500, best_dir = 0, cont;
	for(i = 0; i < 6; i++) {
		/*Conta para chegar o numero de viradas necessarias
		ja que elas gastam um turno*/
		cont = 1 + ladoVirada(r->dir, i);
		Position s = getNeighbor(p,i);
		while(valida(s, g->m, g->n, g)) {
			if(isControlPoint(g,s)) {
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
//Similar a searchNearestControl, mas com projeteis.
int searchNearestProjectile (Grid *g, Position p, Robot *r) {
	int i, min = 500, best_dir = 0, cont;
	Position s;

	for (i = 0; i < 6; i++) {
		cont = 1 + nViradas (r->dir, i);
		s = getNeighbor (p, i);
		while (DentroDoMapa (s, g->m, g->n)) {
			if (isProjectile (g, s)) {
				if(cont < min) {
					min = cont;
					best_dir = i;
					break;
				}
			}
			s = getNeighbor (s, i);
		}
	}
    //sem tiroteio
	if (min == 500)
		return -1;
	else
		return best_dir;
}


//Similar a nearest_control_point, mas com robos.
int encontraRobo (Grid *g, Position p, Robot *r) {  //tem robos ao alcance? Qual esta mais perto?
	int i, min = 500, best_dir = 0, cont;
	Position s;

	for (i = 0; i < 6; i++) {
		cont = 1 + nViradas (r->dir, i);
		s = getNeighbor (p, i);
		while (DentroDoMapa (s, g->m, g->n)) {
			if (isRobot (g, s)) {
				if(cont < min) {
					min = cont;
					best_dir = i;
					break;
				}
			}
			s = getNeighbor (s, i);
		}
	}
	//limpo de robos
	if (min == 500)
		return -1;
	
	else
		return best_dir;
}

Action FIREorAIM (Grid *g, Position p, Robot *r)    //atira ou mira
{
	Direction inimigo_dir;

	inimigo_dir = encontraRobo (g, p, r);
	if (inimigo_dir == -1 || r->bullets == 0)
		return STAND;

	if (inimigo_dir == r->dir)
		return SHOOT_CENTER;
    if (inimigo_dir == (r->dir + 1)%6)
            return SHOOT_RIGHT;
	if (inimigo_dir == (r->dir - 1)%6)
		return SHOOT_LEFT;

	return ladoVirada (r->dir, inimigo_dir);
}

Action poeParede (Position pos, Grid *grid, Robot *r) {      //usa o E do braum
	Direction inimigo_dir;
	Position inimigo; 
	
	inimigo_dir = encontraRobo (grid, pos, r);
	if (inimigo_dir == -1 || r->obstacles == 0)
		return STAND;
	
	inimigo = getNeighbor (pos, inimigo_dir);
	if (grid->map[inimigo.x][inimigo.y].type == 0 || grid->map[inimigo.x][inimigo.y].type == 2) {
		if (inimigo_dir == (r->dir + 3)%6)
			return OBSTACLE_CENTER;
		if (inimigo_dir == (r->dir + 2)%6)
			return OBSTACLE_RIGHT;
		if (inimigo_dir == (r->dir + 4)%6)
			return OBSTACLE_LEFT;
	}
	return ladoVirada (r->dir, (inimigo_dir + 3)%6);
}



int analisaDibre (Position pos, Grid *grid, Robot *r)    //Eh necessario tentar desviar?
{
	int i;
	Projectile *proj;
	Position proj_pos, andar_pos;
	for (i = 0; i < 6; i++)
	{
		if (adjacentes[i] == 3)
		{
			proj_pos = 	getNeighbor (pos, i);
			proj = &grid->map[proj_pos.x][proj_pos.y].object.projectile;
			andar_pos = getNeighbor (pos, r->dir);
			if ((proj->dir + 3)%6 == i) {
				if (valida (andar_pos, grid->m, grid->n, grid))
					if (r->dir != i && r->dir != (i + 3)%6)
						return 1; //pode dibrar reto
					else 
						return -2; //atira para destruir o tiro, ou põe bloco
				else
					return -1; //gira e tenta fugir
			}
		}
	}
	return 0;
}

Action Dibra (Position pos, Grid *grid, Robot *r){  //Dibra os tiros
	int deve, i, dir_proj, dir_ini;
	Position p, proj_pos;
	Projectile *proj;
	deve = analisaDibre (pos, grid, r);
	
	if (isControlPoint (grid, pos)) {       //se em um ponto de controle e sem estar sendo atirado.
		dir_proj = searchNearestProjectile (grid, pos, r);
		dir_ini = encontraRobo (grid, pos, r);

		// Caso seja encontrado um projetil e caso exista municao realizamos uma acao
		if (dir_ini != -1 && dir_proj != -1 && r->bullets > 0 )
		{
			if (dir_proj == r->dir) return SHOOT_CENTER;
			if (dir_proj == (r->dir + 1)%6) return SHOOT_RIGHT;
            if (dir_proj == (r->dir + 5)%6) return SHOOT_LEFT;

			if (dir_proj == (r->dir + 2)%6) return OBSTACLE_RIGHT;
			if (dir_proj == (r->dir + 3)%6) return OBSTACLE_CENTER;
			if (dir_proj == (r->dir + 4)%6) return OBSTACLE_LEFT;
		}
	}
	else {
		if(deve==1) return WALK;
		else if(deve==-1) {
			p=getNeighbor (pos, (r->dir+1)%6);
			if(DentroDoMapa (p, grid->m, grid->n) && (grid->map[p.x][p.y].type == NONE)) return TURN_RIGHT;
			else return TURN_LEFT;
			//Tenta virar, se nao conseguir da uma volta
		}
		else { 
			for (i = 0; i < 6; i++){
				if (adjacentes[i] == 3){
					proj_pos = getNeighbor (pos, i);
					proj = &grid->map[proj_pos.x][proj_pos.y].object.projectile;
					if ((proj->dir + 3)%6 == i){
						if (r->dir == i) return SHOOT_CENTER;
						if (r->dir == (i + 3)%6) return OBSTACLE_CENTER;
					}
				}
			}
		}
	}
	return STAND;	
}


Action acaoSaudavel (Grid *g, Position p) { //acao para quando o robo esta safe
	int i, j, control_dir;
	Position s;
	Robot *r = &g->map[p.x][p.y].object.robot;
	//se estiver em control point, segurar.
	if (isControlPoint (g, p) && !inimigoProximo (p, g, r)) {
		if (analisaDibre (p, g, r)) return Dibra (p, g, r);
		return FIREorAIM (g, p, r);
	}
	else {
		//procura contrl point
		control_dir = searchNearestControl (g, p, r);
		if (control_dir == -1) {    //se nao achar cntrl point anda.
			for(i = r->dir, j = 0; j < 6; i++,j++){
				if (i >= 6) i-=6;
				s = getNeighbor(p,i);
				if(valida(s, g->m, g->n, g)) {
					if(i == r->dir) {
						return WALK;
					}
					else {
						return ladoVirada (r->dir, i);
					}
				}
			}
			return STAND;   //se chegar aqui nao ha oq fazer
		}
		//vai ate o cntrl point achado
		else if(control_dir == r->dir)
			return WALK;
		else {
			return ladoVirada (r->dir, control_dir);
		}
	}
}

Action acaoRisco (Grid *g, Position p) {    //DONT PANIC !!!!
	int i, j, control_dir;
	Position s;
	Robot *r = &g->map[p.x][p.y].object.robot;
	
	//Se estiver em cima de um control point, segurar.
	if(isControlPoint (g,p) && !inimigoProximo (p, g, r)) {
		if (analisaDibre (p, g, r)) return Dibra (p, g, r);
		return poeParede (p, g, r);
	}
	else {
		//procura control point
		control_dir = searchNearestControl(g, p, r);
		if (control_dir == -1) {    //procura cntrl point
			for(i = r->dir, j = 0; j < 6; i++,j++){
				if (i >= 6) i-=6;
				s = getNeighbor (p,i);
				if(valida (s, g->m, g->n, g)) {
					if(i == r->dir) {
						return WALK;
					}
					else {
						return ladoVirada (r->dir, i);
					}
				}
			}
			//nao ha oq fzer
			return STAND;
		}
		//ir ate o control point achado
		else if(control_dir == r->dir)
			return WALK;
		else
			return ladoVirada (r->dir, control_dir);
	}
}

void prepareGame (Grid *g, Position p, int turnCount) {     //inicio do jgo
		setName("ririmas");

}

Action processTurn (Grid *g, Position p, int turnsLeft) {   //roda a cada turno
	int estadoVida;
	encontrarAdjacentes (p, g);
	estadoVida = vidaAtual (g, p);
	switch(estadoVida)
	{
		case SAUDAVEL:
			return acaoSaudavel (g, p);
		break;
		case RISCO:
			return acaoRisco (g, p);
		break;
	}
	return STAND;
}
