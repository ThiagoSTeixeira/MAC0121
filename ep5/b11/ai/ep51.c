#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../robot_fight.h"

/*
ALUNOS
Erica Cope - NUSP 9299091
João Pedro Turri - NUSP 6805993 
*/

//FUNÇÕES DO RICA
//No melhor espírito do software livre, aproveitamos algumas pérolas de nosso amigo e mentor

int init;

int quickTurn(int ini, int end) {
	int i, j;
	for(i = ini, j = 0; i != end; i = (i+1)%6, j++)
		if (i >= 6) i-= 6;
	if (j > 3) j = 6-j;
	return j;
}

Action fastTurn(int ini, int end) {
	int dif = end-ini;
	if((dif <= 3 && dif >= 0) || (dif <= -3))
		return TURN_RIGHT;
	else
		return TURN_LEFT;		
}

int isControlPoint(Grid *g, Position p) {
	return (g->map[p.x][p.y].isControlPoint);	
}

int valid(Position p, int m, int n, Grid *g) {
	return ((p.x >= 0 && p.x < m && p.y >= 0 && p.y < n) && (g->map[p.x][p.y].type == NONE));
}

int searchNearestControl(Grid *g, Position p, Robot *r) {
	int i, min = 500, best_dir = 0, cont;
	for(i = 0; i < 6; i++) {
		//Conta para chegar o numero de viradas necessarias ja que elas gastam um turno
		cont = 1 + quickTurn(r->dir, i);
		Position s = getNeighbor(p,i);
		while(valid(s, g->m, g->n, g)) {
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

	//Nao existe control points no mapa
	if (min == 500)
		return -1;
	
	else
		return best_dir;
}


//NOSSAS FUNÇÕES

Action emergenciaReescrita(Grid *g, Robot *r, Position pos, int i, int j, int dirBala){
    // i = de onde vem a bala; 0 = logo em frente, 1 = direita, ..., 5 = esquerda
    // j = quão longe está. 0 = distância 1, 1 = distância 2
    if (j==0){
        //Emergência máxima. Única salvação é andar imediatamente
        Position tileAdjacente = getNeighbor(pos,r->dir);
        if (valid(tileAdjacente,g->m,g->n,g)) return WALK; //fazer mais um check pra ver se esse tile não receberá tiros?
    }
    //Atirar ou colocar barreira
    if(i==0 && r->bullets > 0) return SHOOT_CENTER;
    if(i==1 && r->bullets > 0) return SHOOT_RIGHT;
    if(i==2 && r->obstacles > 0) return OBSTACLE_RIGHT;
    if(i==3 && r->obstacles > 0) return OBSTACLE_CENTER;
    if(i==4 && r->obstacles > 0) return OBSTACLE_LEFT;  
    if(i==5 && r->bullets > 0) return SHOOT_LEFT;

    //Se nada deu certo, vamos tentar girar
    for(int k = 1;k<6;k++){
        Position fuga = getNeighbor(pos,r->dir+i);
        if (valid(fuga,g->m,g->n,g) && (r->dir+i)!=(dirBala+3)%6) return fastTurn(r->dir,r->dir+i);
    }

    //Pra garantir que exista uma ação válida caso nem o giro dê certo
    return STAND;
}

void prepareGame(Grid *grid, Position pos, int turnCount){
    init = 0;
    setName("Godot");
}

Action processTurn(Grid *grid, Position pos, int turnsLeft){

    Robot *r = &grid->map[pos.x][pos.y].object.robot;
    static int neighbors[2][6][2] = {                          
		{{-1, 0}, {-1, -1}, {0, -1}, {1, 0}, {0, 1}, {-1, 1}}, //Linha par        A partir da esquerda, em
		{{-1, 0}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}}    //Linha ímpar      sentido horário
	};

    //Verificar os conteúdos dos tiles adjacentes, em 2 níveis de distância
    for (int j=0;j<2;j++){
        for (int i=0;i<6;i++){
            Position tileAdjacente = 
            {pos.x + neighbors[pos.y % 2][(r->dir+i)%6][0] 
            + j*(neighbors[(pos.y+1) % 2][(r->dir+i)%6][0]), 
            pos.y + neighbors[pos.y % 2][(r->dir+i)%6][1] 
            + j*(neighbors[(pos.y+1) % 2][(r->dir+i)%6][1])};

            if (tileAdjacente.x >= 0 && tileAdjacente.x < grid->m && tileAdjacente.y >= 0 && tileAdjacente.y < grid->n){

                if (grid->map[tileAdjacente.x][tileAdjacente.y].type == PROJECTILE){
                    //TIRO
                    Position linhaDeTiro = 
                    {tileAdjacente.x
                    + neighbors[tileAdjacente.y % 2][grid->map[tileAdjacente.x][tileAdjacente.y].object.projectile.dir][0]
                    + j*(neighbors[(tileAdjacente.y+1) % 2][grid->map[tileAdjacente.x][tileAdjacente.y].object.projectile.dir][0]),
                    tileAdjacente.y
                    + neighbors[tileAdjacente.y % 2][grid->map[tileAdjacente.x][tileAdjacente.y].object.projectile.dir][1] 
                    + j*(neighbors[(tileAdjacente.y+1) % 2][grid->map[tileAdjacente.x][tileAdjacente.y].object.projectile.dir][1])};
                    if (linhaDeTiro.x == pos.x && linhaDeTiro.y == pos.y){
                        //ESTOU NA LINHA DE TIRO
                        
                        //int dirAbsoluta = (i+r->dir)%6;
                        int dirBala = grid->map[tileAdjacente.x][tileAdjacente.y].object.projectile.dir;
                        //if((dirBala+3)%6 == dirAbsoluta) 
                        emergenciaReescrita(grid, r, pos, i, j, dirBala);
                    }
                }

                if (grid->map[tileAdjacente.x][tileAdjacente.y].type == ROBOT){
                    //ROBÔ INIMIGO

                    if(r->bullets>0 && j==0){
                        if(i==0) return SHOOT_CENTER;
                        if(i==5) return SHOOT_LEFT;
                        if(i==1) return SHOOT_RIGHT;
                        if(i==2) return TURN_RIGHT;
                        if(i==3||i==4) return TURN_LEFT;
                    }
                }
            }
        }
    }

    //Se não está em perigo, tentar colonizar um control point
    if(!(grid->map[pos.x][pos.y].isControlPoint)){
        int control_dir = searchNearestControl(grid, pos, r);
        if (control_dir == -1) {
            int i,j;
            for(i = r->dir, j = 0; j < 6; i++,j++){
                if (i >= 6) i-=6;
                Position s = getNeighbor(pos,i);
                if(valid(s, grid->m, grid->n, grid)) {
                    if(i == r->dir) {
                        return WALK;
                    }
                    else {
                        return fastTurn(r->dir, i);
                    }
                }
            }
            return STAND;
        }
        else if(control_dir == r->dir)
            return WALK;
        else {
            return fastTurn(r->dir, control_dir);
        }
    }
    else{
        //Estou de boas no control point. Vou tentar atirar ou colocar uma barreira
    }

    //Se não achou nenhuma opção de ação, apenas fique parado
    return STAND;
}



