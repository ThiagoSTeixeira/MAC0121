/*-------------------------------------------------------*/
/*                  Exercicio Programa 5                 */
/*  Nomes: Felipe Silva Felix  e Lucas de Carvalho Dias  */
/*                                                       */
/* Nusp: 8941092 e 8941241                               */
/*-------------------------------------------------------*/


#include "../robot_fight.h"
#include <math.h>

#define PI 3.14159265

static char charging;

typedef struct in{
	Position pos;
	Direction dir;
	int distanciaAtual;
	float distanciaMedia;
	int somaDist;
	int balas;
	int vida;
	int obstaculos;
	int score;
	int isInCp;
	int mirandoEmMim;
	int somaAtirou;
	int somaAndou;
	int somaBlocks;
	int somaVirou;
	float taxaDefesa;
	int tirosQueLevaria;	
	int tirosQueLevou;
	int vivo;
}inimigo;

inimigo inimigos[3];

static Position controles[10];
int turno;
static int carregando;
static int myHp;

int isRobot(Tile *t) {
	return t->type == ROBOT;
}

int isProjectile(Tile *t) {
	return t->type == PROJECTILE;
}

int isBlock(Tile *t) {
	return t->type == BLOCK;
}

int isEmptyControl(Tile *t) {
	return t->isControlPoint && t->type == NONE;
}

int isControl(Tile *t) {
	return t->isControlPoint;
}

int isValid(Position p, int m, int n) {
	return p.x >= 0 && p.x < m && p.y >= 0 && p.y < n;
}


int MaxInt(int x, int y){
	if(x > y)
		return x;
	return y;
}

int distancia(Position from, Position to){
	return (MaxInt(abs(to.x - from.x), abs(to.y - from.y)) +1 );
}

Direction shortestPath(Grid *g, Position from, Position to){

	float angle;
	int deltaY, deltaX;
	Direction dir;

	deltaY = to.y - from.y;
	deltaX = to.x - from.x;
	
	if(!deltaX){
		
		if((from.y)%2)
			angle = ((to.y - from.y) < 0)*170 + 1.0;
		else
			angle = ((to.y - from.y) > 0)*(-170) - 1.0;
	}
	else
		angle = atan2(deltaX, deltaY)*180.0/PI;
	if(angle >= 0)
		dir = floor((179.999999 - angle)/60.0) + 2;
	else{
		dir = ((int)floor((-angle)/60.0) +5)%6;
		
	}

	return dir;

}

int rayCast(Grid *g, Position me, Position him, Direction his, int d, int *dir){
	int i, j, result = 0;
	Position aux;
	
	for(i = -1; i < 2; i++){
		aux = getNeighbor(him, (6 + his + i)%6);
		for(j = 0; j < d && isValid(aux, g->m, g->n); j++){
			if(aux.x == me.x && aux.y == me.y){
				result = 1;
				if(dir != NULL)
					*dir = i;
				break;
			}
			aux = getNeighbor(aux, (6 + his + i)%6);
		}
	}
	return result;
}

void findOfensiveSpots(Grid *g, Position me, Position op[], inimigo ini){
	Position aux;
	int i, j;

	for(i = 0; i < 6; i++){
		aux = ini.pos;
		for(j = 0; j < 5 && isValid(getNeighbor(aux, i), g->m, g->n); j++)
			aux = getNeighbor(aux, i);
		if(j == 5)
			op[i] = aux;
		else{
			op[i].x = 500;
			op[i].y = 500;
		}
	}

}

void buscaMapa(Grid *g, Position p, Direction myDir){
	Robot *r;
	int i, j, k, l, err;
	Position aux;
	
	k = 0;
	l = 0;
	
	for(i = 0; i < g->m; i++)
		for(j = 0 ; j < g->n; j++){
			
			aux.x = i;
			aux.y = j;
			if(isValid(aux, g->m, g->n) && isRobot(&g->map[i][j]) && !(i == p.x && j == p.y)){
				err = (6 + myDir - shortestPath(g, p, aux))%6;
				inimigos[k].pos = aux;
				inimigos[k].distanciaAtual = distancia(p, aux) + (err > 3)*(6) + (err > 3)*(-err) + (err <= 3)*(err);
				inimigos[k].distanciaMedia = distancia(p, aux);
				inimigos[k].somaDist = distancia(p, aux);
				
				r = &g->map[aux.x][aux.y].object.robot;
				inimigos[k].dir = r->dir;
				inimigos[k].balas = r->bullets;
				inimigos[k].score = r->score;
				inimigos[k].vida = r->hp;
				inimigos[k].obstaculos = r->obstacles;
				
				inimigos[k].isInCp = g->map[aux.x][aux.y].isControlPoint;
				
				inimigos[k].somaAndou = 0;
				inimigos[k].somaAtirou = 0;
				inimigos[k].somaVirou = 0;
				inimigos[k].somaBlocks = 0;
				inimigos[k].taxaDefesa = -1;
				inimigos[k].tirosQueLevaria = 0;
				inimigos[k].tirosQueLevou = 0;
				inimigos[k].vivo = 1;
				inimigos[k].mirandoEmMim = rayCast(g, p, inimigos[k].pos, inimigos[k].dir, 4, NULL);
				k++;
				
			}
			else if(isControl(&g->map[i][j]) && l < 10){  
				
				aux.x = i;
				aux.y = j;
				controles[l] = aux;
				l++;
			}	
		}
}
void atualiza(Grid *g, Position p, Direction myDir){
	int i, j, l = 0, err;
	Robot *r;
	Position pos;
	turno += 1;
	
	for(i = 0; i < 3; i++){
		if(inimigos[i].vivo && !isRobot(&g->map[inimigos[i].pos.x][inimigos[i].pos.y])){ //QUer dizer que andou
			for(j = 0; j < 6; j++){	
				pos = getNeighbor(inimigos[i].pos, j);
				if(isValid(pos, g->m, g->n) && isRobot(&g->map[pos.x][pos.y])){	
					err = (6 + myDir - shortestPath(g, p, pos))%6;
					inimigos[i].pos = pos;
					inimigos[i].distanciaAtual = distancia(p, pos) + (err > 3)*(6) + (err > 3)*(-err) + (err <= 3)*(err);
					inimigos[i].somaDist += distancia(p, pos);
					inimigos[i].distanciaMedia = (inimigos[i].somaDist)/((float) turno);
					inimigos[i].somaAndou += 1;
					inimigos[i].isInCp = g->map[pos.x][pos.y].isControlPoint;
					inimigos[i].mirandoEmMim = rayCast(g, p, inimigos[i].pos, inimigos[i].dir, inimigos[i].distanciaAtual, NULL);
					break;
				}
				
			}
			if(j == 6)
				inimigos[i].vivo = 0;
		}
		else if(inimigos[i].vivo){
			r = &g->map[inimigos[i].pos.x][inimigos[i].pos.y].object.robot;
			if(r->dir != inimigos[i].dir){
				inimigos[i].dir = r->dir;
				inimigos[i].somaVirou += 1;
			}
			for(j = 0; j < 6; j++){
				pos = getNeighbor(inimigos[i].pos, j);
				if(isProjectile(&g->map[pos.x][pos.y])){
					Projectile *pr = &g->map[inimigos[i].pos.x][inimigos[i].pos.y].object.projectile;
					if(pr->dir == inimigos[i].dir)
						inimigos[i].somaAtirou += 1;
					else if(abs(pr->dir - j) == 3) //Significa que o tiro esta direcionado para o inimigo sendo espiado
						inimigos[i].tirosQueLevaria += 1;
						
				}
				
			}

		}
		if(inimigos[i].vivo){
			r = &g->map[inimigos[i].pos.x][inimigos[i].pos.y].object.robot;
			inimigos[i].balas = r->bullets;
			inimigos[i].score = r->score;
			if(inimigos[i].vida != r->hp)
				inimigos[i].tirosQueLevou +=1;
			inimigos[i].vida = r->hp;
			inimigos[i].obstaculos = r->obstacles;
			if(inimigos[i].tirosQueLevaria)
				inimigos[i].taxaDefesa = inimigos[i].tirosQueLevou/((float)inimigos[i].tirosQueLevaria);
		}		
	}
	if(turno == 1){
		for(i = 0; i < g->m; i++)
			for(j = 0 ; j < g->n; j++){
				if(isControl(&g->map[i][j]) && l < 10){  
					 //Aqui nao ta funcionando por alguma razao
					pos.x= i;
					pos.y = j;
					controles[l] = pos;
					l++;
				}	
			}
	}
	

}

int sendoAlvejado(Grid *g, Position p, Direction dirs[], int n, Position me){

	Position pos;
	Projectile *r;
	int i, alvejado = 0;
	
	if(n == 2)
		for(i = 0; i < 6; i++){
			pos = getNeighbor(getNeighbor(p, i), i);
			if(isValid(pos, g->m, g->n) && isProjectile(&g->map[pos.x][pos.y])){
				r = &g->map[pos.x][pos.y].object.projectile;
				if(abs(r->dir - i) == 3){
					dirs[i] = 1;
					alvejado = 1;
				}
			}
			else
				dirs[i] = 0;
		}
	
	else
		for(i = 0; i < 6; i++){
			pos = getNeighbor(p, i);
			if(isValid(pos, g->m, g->n) && isProjectile(&g->map[pos.x][pos.y])){
				r = &g->map[pos.x][pos.y].object.projectile;
				if(abs(r->dir - i) == 3){
					dirs[i] = 1;
					alvejado = 1;
				}
			}
			else if(isValid(pos, g->m, g->n) && isRobot(&g->map[pos.x][pos.y]) && !(pos.x == me.x && pos.y == me.y)){
				
				dirs[i] = 1;
				alvejado = 1;
				

			}
			else
				dirs[i] = 0;
		}
	
	return alvejado;
}

Position nearest(Grid *g, Position from, Position v[], int t, Direction myDir){
	Position n;
	int dist = 1000, aux, i, err;
	n.x = from.x;
	n.y = from.y;
	for(i = 0; i < t; i++){
		err = (6 + myDir - shortestPath(g, from, v[i]))%6;
		aux = distancia(from, v[i]) + (err > 3)*(6) + (err > 3)*(-err) + (err <= 3)*(err);
		if(aux < dist && isValid(v[i], g->m, g->n) && !isProjectile(&g->map[v[i].x][v[i].y]) && !isRobot(&g->map[v[i].x][v[i].y]) && !isBlock(&g->map[v[i].x][v[i].y])){
			dist = aux;
			n = v[i];
		}
	}
	return n;
}

inimigo nearestEnemy(Grid *g, Position from, Direction myDir, int mode){
	int aux, dist = 10000, i, err;
	inimigo titular;
	titular = inimigos[0];
	for(i = 0; i < 3; i++){
		aux = distancia(from, inimigos[i].pos);
		err = (6 + myDir - shortestPath(g, from, inimigos[i].pos))%6;
		if(mode)
			aux += (err > 3)*(6) + (err > 3)*(-err) + (err <= 3)*(err);
		if(aux < dist && isValid(inimigos[i].pos, g->m, g->n) && !isProjectile(&g->map[inimigos[i].pos.x][inimigos[i].pos.y]) && !isRobot(&g->map[inimigos[i].pos.x][inimigos[i].pos.y]) && !isBlock(&g->map[inimigos[i].pos.x][inimigos[i].pos.y]) && inimigos[i].vivo){
			dist = aux;
			titular = inimigos[i];
		}
	}
	return titular;
}

int isSafe(Grid *g, Position pos, int m, int n, Position me){
	Direction dirs[6];
	return (isValid(pos, g->m, g->n) && !isProjectile(&g->map[pos.x][pos.y]) && !sendoAlvejado(g, pos, dirs, 1, me) && !isRobot(&g->map[pos.x][pos.y]) && !isBlock(&g->map[pos.x][pos.y]));

}

Direction safe(Grid *g, Position from, Direction myDir){
	int i;
	Position poses[6];
	Position pos;
	for(i = 0; i < 6; i++){
		if(isSafe(g, getNeighbor(from, i), g->m, g->n, from))
			pos = getNeighbor(from, i);
		else{
			pos.x = 10000;
			pos.y = 10000;
		}
			
		poses[i] = pos;
	}
	pos = nearest(g, from, poses, 6, myDir);
	for(i = 0; i < 6; i++)
		if(poses[i].x == pos.x && poses[i].y == pos.y)
			return i;
	return 0;

}

void prepareGame(Grid *g, Position p, int turnCount) {
	
	charging = 0;
	setName("Bumble Bee");
	
	carregando = 0;
	myHp = 100;
	turno = 0;
	
	
	
}

Action bestTurn(Direction from, Direction to) {
	if(((6 + from - to)%6) < 3) return TURN_LEFT;
	else return TURN_RIGHT;
}

Action obstacle(int i){

	if(i == 3)
		return OBSTACLE_CENTER;
	else if(i == 2)
		return OBSTACLE_RIGHT;
	return OBSTACLE_LEFT;

}


Action processTurn(Grid *g, Position p, int turnsLeft) {
	Position posOfensiva[6];
	Direction dirs[6];	
	Direction myDir;
	Direction obj;
	inimigo inimigoPerto;
	int di, i;
	
	
	Robot *eu = &g->map[p.x][p.y].object.robot;
	myDir = eu->dir;
	if(turno == 0){
		buscaMapa(g, p, myDir);
		carregando = 0;
	}
	atualiza(g, p, myDir);
		
	inimigoPerto = nearestEnemy(g, p, myDir, 0);
	findOfensiveSpots(g, p, posOfensiva, inimigoPerto);

	if(sendoAlvejado(g, p, dirs, 1, p) || eu->hp < myHp){   /*Verifica se nos tiles vizinhos ha balas vindo em sua direcao*/
		myHp = eu->hp;
		
		if(isSafe(g,getNeighbor(p, myDir), g->m, g->n, p)){
			
			carregando = 0;
			return WALK;
		}
		else{
			
			obj = shortestPath(g, p, nearest(g, p, controles, 10, myDir));
			
			return bestTurn(myDir, safe(g, p, myDir));
		}
	}

	else if(sendoAlvejado(g, p, dirs, 2, p)){ /*verifica a 2 tiles de distancia se ha balas vindo em sua direcao*/

		for(i = 2; i < 5; i++)
			if(dirs[(6 + myDir + i)%6])	
				return obstacle(i);
		
		if(dirs[myDir] || dirs[(6 + myDir-3)%6])
			return bestTurn(myDir, safe(g, p, myDir));
		
		
		else if(isSafe(g,getNeighbor(p, myDir), g->m, g->n, p)){
			carregando = 0;
			return WALK;
		}
		else
			return bestTurn(myDir, safe(g, p, myDir));
		
		
	} 
	
	


	/*else if(distancia(p, inimigoPerto.pos) < 4 && inimigoPerto.balas >=4 && inimigoPerto.mirandoEmMim){
		if(isSafe(g,getNeighbor(p, myDir), g->m, g->n, p) && inimigoPerto.dir != (6 + myDir-3)%6){
			
			carregando = 0;
			return WALK;
		}
		else{
			
			
			obj = shortestPath(g, p, nearest(g, p, posOfensiva, 6, myDir));
			return bestTurn(myDir, obj);
		}
	}


*/

	if(rayCast(g, inimigoPerto.pos, p, myDir, 4, &di) && eu->bullets > 0){ /*Verifica se ha alguem em sua mira */
		if(di == 0)
			return SHOOT_CENTER;
		else if(di == 1)
			return SHOOT_RIGHT;
		else if(di == -1)
			return SHOOT_LEFT;
	}

	if(distancia(p, nearest(g, p, posOfensiva, 6, myDir)) < distancia(p, nearest(g, p, controles, 10, myDir)) && eu->bullets > 0){ 
		obj = shortestPath(g, p, nearest(g, p, posOfensiva, 6, myDir));
		

		if(rayCast(g, inimigoPerto.pos, p, (6 + myDir - 3)%6, 4, &di)){
			return bestTurn(myDir, di);
		}

		else if(obj == myDir && isSafe(g,getNeighbor(p, myDir), g->m, g->n, p) && !charging){
			carregando = 0;
			return WALK;
		}
		else
			return bestTurn(myDir, obj);
		
	}

	if(g->map[p.x][p.y].isControlPoint){
		carregando = 1;
		
		return STAND;
	}
	



	if(eu->bullets < 4){
		
		obj = shortestPath(g, p, nearest(g, p, controles, 10, myDir));
		
		if(obj == myDir && isSafe(g,getNeighbor(p, myDir), g->m, g->n, p)){
			
			carregando = 0;
			return WALK;
		}
		else
			return bestTurn(myDir, obj);
			
	}
	
	
	obj = shortestPath(g, p, nearest(g, p, controles, 10, myDir));
		
	if(obj == myDir && isSafe(g,getNeighbor(p, myDir), g->m, g->n, p)){
		
		carregando = 0;
		return WALK;
	}
	else{
		
		return bestTurn(myDir, obj);
	}	
	
}
