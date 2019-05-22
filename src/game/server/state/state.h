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
}                       player_t;

// init.c
void init_background();
void init_map();
void init_game();

// wall.c
void create_wall_entity(int x, int y);
void create_indestructible_wall(int x, int y);
void create_outer_wall(int x, int y);

// players.c
int add_players(player_t *player);
player_t **get_players();

// state.c
char *encode_state();

#endif
