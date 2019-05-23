/*
** players.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "state.h"

player_t **players = NULL;
EGB_Entity  *add_player(player_t *player) {
    int i;
    if (players == NULL) {
        players = malloc(sizeof(player_t *) * 5);
        for (i = 0; i < 5; i++) {
            players[i] = NULL;
        }
    }
    i = 0;
    while (i < 4 && players[i] != NULL) {
        i++;
    }
    if (i == 4)
        return NULL;
    player->id = i;
    players[i] = player;
    log_debug("[SERVER SIDE] Player accepted with id : %d", i);
    return init_new_player(player->id);
}

player_t **get_players() {
    return players;
}
