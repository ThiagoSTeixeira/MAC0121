#include "lua-5.1.5/src/lua.h"
#include "lua-5.1.5/src/lauxlib.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define _JOIN(a,b) a ## b
#define JOIN(a, b) _JOIN(a, b)
#define __INCL_CODE(str) #str
#define _INCL_CODE(x) __INCL_CODE(x)
#define INCL_CODE _INCL_CODE(ROBOT_AI)
#include INCL_CODE
#define DB printf("LINE %d\n", __LINE__);

Position getNeighbor(Position pos, Direction dir) {
	static int neighbors[2][6][2] = {
		{{-1, 0}, {-1, -1}, {0, -1}, {1, 0}, {0, 1}, {-1, 1}},
		{{-1, 0}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}}
	};
	return (Position) {pos.x + neighbors[pos.y % 2][dir][0], pos.y + neighbors[pos.y % 2][dir][1]};
}

static char name[MAX_NOME + 1];
static char songName[101];

void setName(const char *str) {
	strncpy(name, str, MAX_NOME);
	name[MAX_NOME] = '\0';
}

void playSong(const char *str) {
	strncpy(songName, str, 100);
	songName[100] = '\0';
}

static int get_integer(lua_State *L, int ind, char *name) {
	int a;
	lua_getfield(L, ind, name);
	a = lua_tointeger(L, -1);
	lua_pop(L, 1);
	return a;
}

static void handle_block(lua_State *L, Block *block) {
	block->turnsLeft = get_integer(L, -1, "turns_left");
	block->ownerIndex = get_integer(L, -1, "owner_index");
}

static void handle_robot(lua_State *L, Robot *robot) {
	robot->hp = get_integer(L, -1, "hp");
	robot->score = get_integer(L, -1, "score");
	robot->dir = get_integer(L, -1, "dir");
	robot->index = get_integer(L, -1, "index");
	robot->bullets = get_integer(L, -1, "bullets");
	robot->obstacles = get_integer(L, -1, "obstacles");
}

static void handle_projectile(lua_State *L, Projectile *projectile) {
	projectile->dir = get_integer(L, -1, "dir"); 
	projectile->ownerIndex = get_integer(L, -1, "owner_index");
}

static void read_map(lua_State *L, Grid *g, Position *pos) {
	int i, j, m, n, aux;
	lua_rawgeti(L, 2, 1);
	pos->x = lua_tointeger(L, -1) - 1;
	lua_rawgeti(L, 2, 2);
	pos->y = lua_tointeger(L, -1) - 1;


	m = get_integer(L, 1, "m");
	n = get_integer(L, 1, "n");
	g->m = m;
	g->n = n;

	for(i = 1; i <= m; i++) {
		lua_rawgeti(L, 1, i);
		aux = lua_gettop(L);
		lua_rawgeti(L, 3, i);
		for(j = 1; j <= n; j++) {
			int type; 
			lua_rawgeti(L, aux, j); 
			lua_rawgeti(L, -1, 1); 
			type = lua_tointeger(L, -1); 
			g->map[i - 1][j - 1].type = type; 
			lua_rawgeti(L, -2, 2); 

			switch(type) { 
				case 1: 
					handle_block(L, &g->map[i - 1][j - 1].object.block); 
					break; 
				case 2: 
					handle_robot(L, &g->map[i - 1][j - 1].object.robot); 
					break; 
				case 3: 
					handle_projectile(L, &g->map[i - 1][j - 1].object.projectile); 
					break; 
			} 

 			lua_rawgeti(L, aux + 1, j); 
			lua_rawgeti(L, -1, 1); 
			g->map[i - 1][j - 1].isControlPoint = lua_toboolean(L, -1); 
			lua_settop(L, aux + 1); 
		}
	}
}

static int l_prepare_game(lua_State *L) {
	Grid g;
	Position pos;
	int turnCount = lua_tointeger(L, 4);
	read_map(L, &g, &pos);
	name[0] = '\0';
	prepareGame(&g, pos, turnCount);
	if(name[0]) {
		lua_pushstring(L, name);
		return 1;
	} else
		return 0;
}

static int l_process_turn(lua_State *L) {
	static Grid g;
	Position pos;
	int turnsLeft = lua_tointeger(L, 4);
	read_map(L, &g, &pos);
	songName[0] = '\0';
	lua_pushinteger(L, processTurn(&g, pos, turnsLeft));
	if(songName[0]) {
		lua_pushstring(L, songName);
		return 2;
	} else
		return 1;
}

static const struct luaL_reg funcs[] = {
	{"process_turn", l_process_turn},
	{"prepare_game", l_prepare_game},
	{NULL, NULL}  /* sentinel */
};

int JOIN(luaopen_robot_ai, PLAYER)(lua_State *L) {
	char name[100];
	srand(time(NULL));
	rand(); rand();
	sprintf(name, "robot_ai%d", PLAYER);
	luaL_openlib(L, name, funcs, 0);
	return 1;
}