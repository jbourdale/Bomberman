/*
** join.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "requests.h"

int join_game(int sock, player_t *player) {
    player_t **players;
    int      error;
    int      i;

    error = 0;
    i = -1;
    players = get_players();
    if (players != NULL) {
        i = 0;
        while (players[i] != NULL)
            i++;
        if (i >= 4)
            error = 1;
        else
            player->id = i;
    }
    if (i == -1)
        player->id = 0;

    if (error) {
        return -1;
    }

    return send_state(sock, player);
}
