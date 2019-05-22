/*
** parsing.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "../game.h"

int             parse_event_requests(int sock, char *event_request, player_t *player) {
    char        *token;

    log_debug("event request : %s", event_request);
    token = strtok(event_request, "\n");
    token = strtok(event_request, "|");
    token = strtok(NULL, "|");

    if (strcmp(token, "JOIN") == 0) {
        join_game(sock, player);
    }
    return 0;
}


int parse_request(int sock, char *payload, struct sockaddr_in clientaddr) {
    player_t *player;

    player = find_player_by_addr(clientaddr);
    if (player == NULL) {
        player = malloc(sizeof(player_t));
        player->addr = clientaddr;
    }

    switch (payload[0]) {
        case EGB_EVENT_NETWORK_IDENTIFIER:
            parse_event_requests(sock, payload, player);
            break;
        case EGB_ERROR_NETWORK_IDENTIFIER:
            break;
        case EGB_ENTITY_NETWORK_IDENTIFIER:
            break;
        default:
            log_debug("RECV UNPARSABLE DATA");
    }
    return 0;
}
