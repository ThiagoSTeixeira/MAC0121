 /******************************************************************************
 *
 * MAC0121 - Algoritmos e Estruturas de Dados I
 * Alunos:  Iggor Francis Numata Mathews    - 10262572
 *          Victor Pereira Lima             - 10737028
 * Tarefa: EP5 - "A Batalha Final"
 * Data: 02/12/2018
 *
 * DECLARO QUE SOMOS OS UNICO AUTORES E RESPONSAVEIS POR ESTE PROGRAMA.  TODAS
 * AS PARTES DO PROGRAMA, EXCETO AS QUE SAO BASEADAS EM MATERIAL FORNECIDO
 * PELO PROFESSOR OU COPIADAS DO LIVRO DA DISCIPLINA, FORAM DESENVOLVIDAS POR
 * NÓS.  DECLARO TAMBEM SERMOS RESPONSAVEIS POR TODAS AS COPIAS DESTE PROGRAMA
 * E NAO DISTRIBUIMOS NEM FACILITAMOS A DISTRIBUICAO DE COPIAS DESTA PROGRAMA.
 *
 *****************************************************************************/


#include "../robot_fight.h"

static int goal_dir; /*Variável que decide a melhor direção para onde as ações
                        serão realizadas*/

/*Checa se a posicao dada esta dentro do mapa e nao esta sendo ocupada*/
int valid(Position p, int m, int n, Grid *g){
    return ((p.x >= 0 && p.x < m && p.y >= 0 && p.y < n) &&
            (g->map[p.x][p.y].type == NONE));
}

void prepareGame(Grid *g, Position p, int turnCount){
    /*Define um nome à altura do nosso robô*/
    setName("The Challenger");
}

/*Dada uma direcao inicial e uma direcao final, ve qual
o menor numero de viradas sao necessarias*/
int quickTurn(int ini, int end){
    /*Código base dos exemplos fornecidos*/
    int i, j;
    for (i = ini, j = 0; i != end; i = (i+1)%6, j++)
        if (i >= 6) i-= 6;
    if (j > 3) j = 6-j;
    return j;
}

/*Dada uma direcao inicial e uma direcao final, ve
para qual lado virando eh mais rapido de se chegar*/
Action fastTurn(int ini, int end){
    /*Código base dos exemplos fornecidos*/
    int dif = end-ini;
    if ((dif <= 3 && dif >= 0) || (dif <= -3))
        return TURN_RIGHT;
    else
        return TURN_LEFT;
}

int isControlPoint(Grid *g, Position p){
    /*Código base dos exemplos fornecidos*/
    return (g->map[p.x][p.y].isControlPoint);
    /*Retorna se o tile analisado é um ControlPoint*/
}

int isRobot(Grid *g, Position p){
    /*Código adaptado com base nos exemplos fornecidos*/
    return (g->map[p.x][p.y].type == ROBOT);
    /*Returna se no tile analisado tem um Robô*/
}

/*Dado uma posicao, checa se para alguma direcao
existe um control point, e retorna qual direcao esta
o mais perto, contando giradas necessárias*/
int searchNearestControl(Grid *g, Position p, Robot *r){
    /*Código base dos exemplos fornecidos*/
    int i, min = 500, best_dir = 0, cont;
    for (i = 0; i < 6; i++){
        /*Conta para chegar o numero de viradas necessarias
        ja que elas gastam um turno*/
        cont = 1 + quickTurn(r->dir, i);
        Position s = getNeighbor(p,i);

        while (valid(s, g->m, g->n, g)){

            if (isControlPoint(g,s)){

                if (cont < min){
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

int searchNearestEnemy(Grid *g, Position p, Robot *r){
    /*Código adaptado com base nos exemplos fornecidos*/
    /*Verifica em qual direção está o inimigo mais próximo*/
    int i, min = 500, best_dir = 0, cont;
    for (i = 0; i < 6; i++){

        cont = 1 + quickTurn(r->dir, i);
        Position s = getNeighbor(p,i);

        while (valid(s, g->m, g->n, g)){

            if (isRobot(g,s)){

                if (cont < min){
                    min = cont;
                    best_dir = i;
                    break;
                }
            }

            cont++;
            s = getNeighbor(s, i);
        }
    }

    if (min == 500)
        return -1;
    else
        return best_dir;
}

Action shoot(Direction from, Direction to){
    /*Decide o lado pra qual lado atirar*/
    if (from == to)
        return SHOOT_CENTER;

    else if (fastTurn(from, to) == TURN_RIGHT)
        return SHOOT_RIGHT;

    else
        return SHOOT_LEFT;
}

Action explorer(Direction goal, Direction robot){
    /*Movimentos pra seguir em direção ao ControlPoint*/
    if (goal == robot) /*Se estiver na direção certa, andar em frente*/
        return WALK;

    else /*Se não, girar em direção ao ControlPoint*/
        return fastTurn(robot, goal);
}

Action brawler(Direction goal_dir, Robot *r){
    /*Movimentos de combate*/
    if (r->bullets == 0) /*Se não houver munição, recarrega*/
        return STAND;

    else if (quickTurn(r->dir, goal_dir) <= 1)
        return shoot(r->dir, goal_dir);
        /*Se o inimigo estiver na mira,atirar*/
    
    else
        return fastTurn(r->dir, goal_dir);
        /*Se não estiver na mira, girar procurando o inimigo*/
}

Action processTurn(Grid *g, Position p, int turnsLeft){
    int i, j;
    Position s;
    Robot *r = &g->map[p.x][p.y].object.robot;

    if (!isControlPoint(g,p)){
    /*Veridfica se não está encima de um ControlPoint*/

        goal_dir = searchNearestControl(g, p, r);
        /*Procura o ControlPoint mais próximo*/

        if (goal_dir == -1) {
            goal_dir = searchNearestEnemy(g, p, r);
            /*Se não houverem ControlPoints disponíveis, procura o inimigo mais
            próximo*/

            if (goal_dir == -1){
                setName("WINNER!!");
                /*Se não houverem mais inimigos, nós ganhamos! (?)*/
                return STAND;
            }

            else
                return brawler(goal_dir, r);
                /*Se houverem inimigos, excecutar movimentos de combate*/
        }

        else
            return explorer(goal_dir, r->dir);
            /*Se houver um ControlPoint disponível, ir até o tile*/
    }

    else
        return brawler(goal_dir, r);
        /*Se estiver em um ControlPoint, excecutar movimentos de combate*/
}