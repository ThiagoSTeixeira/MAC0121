typedef enum {NONE, BLOCK, ROBOT, PROJECTILE} TileType;

typedef enum {LEFT, TOP_LEFT, TOP_RIGHT, RIGHT, BOTTOM_RIGHT, BOTTOM_LEFT} Direction;

typedef struct {
	int hp;
	int score;
	int bullets;
	int obstacles;
	Direction dir;
	int index;
} Robot;

typedef struct {
	int turnsLeft;
	int ownerIndex;
} Block;

typedef struct {
	Direction dir;
	int ownerIndex;
} Projectile;

typedef struct {
	TileType type;
	union {
		Robot robot;
		Block block;
		Projectile projectile;
	} object;
	char isControlPoint;
} Tile;

typedef struct {
	int m, n;
	Tile map[30][30];
} Grid;

typedef struct {
	int x, y;
} Position;

typedef enum {STAND = 0, OBSTACLE_LEFT = 10, OBSTACLE_CENTER, OBSTACLE_RIGHT, WALK = 20,
	TURN_LEFT = 30, TURN_RIGHT, SHOOT_LEFT = 40, SHOOT_CENTER, SHOOT_RIGHT} Action;

/*
	Já implementada, função auxiliar que pode ajudar
	Retorna a posição vizinha a posição dada, andando um passo na direção dir
*/
Position getNeighbor(Position pos, Direction dir);

#define MAX_NOME 15
/*
	Deve ser chamada de dentro do prepareGame. Faz esse ser o nome do seu personagem.
	Note que o nome é restrito a MAX_NOME caracteres, o resto será apagado.
	Você deve limpar sua própria memória se alocou alguma.
*/
void setName(const char *name);

/*
	Toca o arquivo de som chamado songName que está na pasta sound. Chame essa função durante a execução do processTurn.
	Você deve limpar sua própria memória se alocou alguma. O nome é restrito a 100 caracteres.
	NÃO ABUSE. por favor.
*/
void playSong(const char *songName);

/*
	IMPLEMENTAR
	grid - o mapa
	pos - a posição do seu robô
	turnCont - quantos turnos o jogo vai ter
*/
void prepareGame(Grid *grid, Position pos, int turnCount);

/*
	IMPLEMENTAR
	grid - o mapa
	pos - a posição do seu robô
	turnsLeft - quantos turnos depois desse ainda restam
	Devolve:
		STAND: Não faz nada (Ou domina ControlPoint se estiver nele)
		OBSTACLE_LEFT: Coloca obstáculo na esquerda-tras
		OBSTACLE_CENTER: Coloca obstáculo atras
		OBSTACLE_RIGHT: Coloca obstáculo na direita-tras
		WALK: Anda para frente
		TURN_LEFT: Gira para a esquerda
		TURN_RIGHT: Gira para a direita
		SHOOT_LEFT: Atira para esqueda-frente
		SHOOT_CENTER: Atira para frente
		SHOOT_RIGHT: Atira para direita-frente
*/
Action processTurn(Grid *grid, Position pos, int turnsLeft);