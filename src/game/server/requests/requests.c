/*
** requests.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "requests.h"

int         broadcast_event_to_players(int sock, char *event) 
{
    char        *payload;

    payload = malloc(1000);
    payload[0] = EGB_EVENT_NETWORK_IDENTIFIER;
    payload[1] = EGB_NETWORK_VALUE_SEPARATOR_CHAR;
    payload[2] = '\0';
    strcat(payload, event);

    return broadcast_to_players(sock, payload, NULL);
}

int         broadcast_to_players(int sock, char *payload, player_t *player)
{
    player_t    **players;
    int         i;

    players = get_players();
    i = 0;
    while (players[i] != NULL && players[i] != player) {
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
    EGB_Component_Networkable   *networkable_component;

    manager = EGBS_Manager_Entity(EGB_Manager_Retrieve);
    if (manager == NULL)
        return -1;

    iterator = manager->first;
    while (iterator != NULL)
    {
        networkable_component = NULL;
        if (strcmp(iterator->entity->name, "player") == 0) {
            networkable_component = EGB_FindComponentByName(iterator->entity, "networkable_component");
            if(strcmp(networkable_component->owner_addr, player->s_addr) == 0) {
                networkable_component->owner = 1;
            }
        }
        encodedEntity = EGB_Serializer_EncodeEntity(iterator->entity);
        if (networkable_component != NULL) {
            networkable_component->owner = 0;
        }
        if (encodedEntity == NULL) {
            continue;
        }
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
