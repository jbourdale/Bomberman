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
    char        *addr;
    int         i;

    asprintf(&addr, "%s:%d", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

    players = get_players();
    if (players == NULL)
        return NULL;
    i = 0;
    while (players[i] != NULL) {
        if(strcmp(addr, players[i]->s_addr) == 0)
            break;
        i++;
    }
    return players[i];
}
