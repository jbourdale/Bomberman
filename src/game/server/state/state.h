/*
** state.h for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __STATE_H__
#define __STATE_H__

#include "../../../engine/engine.h"

typedef struct          player_s
{
    int                 id;
    struct sockaddr_in  addr;
    char 				*s_addr;
}                       player_t;

// init.c
void init_background();
EGB_Entity *init_new_player(int id, struct sockaddr_in addr);
void init_map();
void init_game();

// wall.c
void create_wall_entity(int x, int y);
void create_indestructible_wall(int x, int y);
void create_outer_wall(int x, int y);
void create_floor(int x, int y);

// players.c
EGB_Entity *add_player(player_t *player);
player_t **get_players();
int     get_nb_players();

// state.c
char *encode_state();

#endif
