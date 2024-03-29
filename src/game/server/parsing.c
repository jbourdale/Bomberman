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
    // token = strtok_r(event_request, "\n", &event_request);
    token = strtok_r(event_request, "|", &event_request);
    log_debug("token : %s", token);
    token = strtok_r(NULL, "|", &event_request);
    log_debug("token : %s", token);

    if (strcmp(token, "JOIN") == 0) {
        join_game(sock, player);
    } else if (strcmp(token, "START") == 0) {
        broadcast_event_to_players(sock, "START");
    } else if (strcmp(token, "PING") == 0) {
        ping(sock, player);
    }
    return 0;
}


int parse_request(int sock, char *payload, struct sockaddr_in clientaddr) {
    player_t *player;
    char     *addr;

    player = find_player_by_addr(clientaddr);
    if (player == NULL) {
        player = malloc(sizeof(player_t));
        asprintf(&addr, "%s:%d", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
        player->addr = clientaddr;
        player->s_addr = addr;
    }

    switch (payload[0]) {
        case EGB_EVENT_NETWORK_IDENTIFIER:
            parse_event_requests(sock, strdup(payload), player);
            break;
        case EGB_ERROR_NETWORK_IDENTIFIER:
            break;
        case EGB_ENTITY_NETWORK_IDENTIFIER:
            handle_entities_request(sock, strdup(payload), player);
            break;
        default:
            log_debug("RECV UNPARSABLE DATA");
    }
    return 0;
}
