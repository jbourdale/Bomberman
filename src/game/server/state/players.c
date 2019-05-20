/*
** players.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "state.h"

player_t **players = NULL;
int add_players(player_t *player) {
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
        return -1;
    players[i] = player;
    return 0;
}

player_t **get_players() {
    return players;
}
