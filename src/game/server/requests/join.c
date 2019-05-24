/*
** join.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "requests.h"

int can_connect(player_t *player) {
    player_t    **players;
    int         i;

    players = get_players();
    if (players == NULL) {
        player->id = 0;
        return 1;
    }

    if (players != NULL) {
        i = 0;
        while (players[i] != NULL)
            i++;
        if (i >= 4)
            return 0;
    }
    return 1;
}

int             join_game(int sock, player_t *player) {
    EGB_Entity  *player_entity;
    char        *encodedPlayer;


    log_debug("[SERVER SIDE] [JOIN GAME] RECIEVED REQUEST FROM : %s", player->s_addr);

    if (!can_connect(player)) {
        return -1;
    }

    player_entity = add_player(player);
    if (player_entity == NULL)
        return -1;

    send_state(sock, player);
    encodedPlayer = EGB_Serializer_EncodeEntity(player_entity);
    return broadcast_to_players(sock, encodedPlayer);
}
