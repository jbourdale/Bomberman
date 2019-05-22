/*
** player.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "../../engine/engine.h"
#include "server.h"

player_t        *find_player_by_addr(struct sockaddr_in clientaddr)
{
    player_t    **players;
    int         i;

    players = get_players();
    if (players == NULL)
        return NULL;
    i = 0;
    while (players[i] != NULL) {
        if(
            players[i]->addr.sin_addr.s_addr == clientaddr.sin_addr.s_addr
            && players[i]->addr.sin_port == clientaddr.sin_port
        )
            break;
        i++;
    }
    return players[i];
}
