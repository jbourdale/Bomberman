/*
** ping.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "requests.h"

int             ping(int sock, player_t *player) {
    log_debug("[SERVER SIDE] [PING] RECIEVED REQUEST FROM : %s", player->s_addr);

    log_debug("SENDING PONG BACK");
    sendto(
        sock,
        "PONG",
        strlen("PONG"),
        0,
        (struct sockaddr *) &(player->addr),
        sizeof(player->addr)
    );
    return 0;
}
