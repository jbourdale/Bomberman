/*
** requests.h for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __SERVER_REQUEST_H__
#define __SERVER_REQUEST_H__

#include "../state/state.h"

int join_game(int sock, player_t *player);

// requests.c
int broadcast_event_to_players(int sock, char *event);
int broadcast_to_players(int sock, char *payload, player_t *player);
int send_state(int sock, player_t *player);

// entities.c
void destroy_entity(int sock, EGB_Entity *entity);

// ping.c
int             ping(int sock, player_t *player);

#endif
