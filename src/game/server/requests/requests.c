/*
** requests.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "requests.h"

int         broadcast_to_players(int sock, char *payload)
{
    player_t    **players;
    int         i;

    players = get_players();
    i = 0;
    while (players[i] != NULL) {
        sendto(
            sock,
            payload,
            strlen(payload),
            0,
            (struct sockaddr *) &(players[i]->addr),
            sizeof(players[i]->addr)
        );
        i++;
    }
    return 0;
}

int                            send_state(int sock, player_t *player)
{
    char                        *encodedEntity;
    EGB_Entity_Manager          *manager;
    EGB_Entity_Manager_Element  *iterator;

    manager = EGBS_Manager_Entity(EGB_Manager_Retrieve);
    if (manager == NULL)
        return -1;

    iterator = manager->first;
    while (iterator != NULL)
    {
        log_debug("iterator->entity (%p) : %s", iterator->entity, iterator->entity->name);
        encodedEntity = EGB_Serializer_EncodeEntity(iterator->entity);
        if (encodedEntity == NULL) {
            log_error("ENCODED ENTITY : %s", encodedEntity);
            continue;
        }
        log_debug("[SERVER]::send_state > sending %d bytes", strlen(encodedEntity));
        sendto(
            sock,
            encodedEntity,
            strlen(encodedEntity),
            0,
            (struct sockaddr *) &(player->addr),
            sizeof(player->addr)
        );
        iterator = iterator->next;
    }
    return 0;
}
