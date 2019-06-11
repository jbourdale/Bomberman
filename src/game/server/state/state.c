/*
** state.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "../../../engine/engine.h"

char                            *encode_state()
{
    char                        *payload, *encodedEntity;
    EGB_Entity_Manager          *manager;
    EGB_Entity_Manager_Element  *iterator;

    manager = EGBS_Manager_Entity(EGB_Manager_Retrieve);
    if (manager == NULL)
        return "";
    iterator = manager->first;

    payload = malloc(10000);
    memset(payload, '\0', 10000);
    while (iterator != NULL)
    {
        log_debug("iterator->entity (%p) : %s", iterator->entity, iterator->entity->name);
        encodedEntity = EGB_Serializer_EncodeEntity(iterator->entity);
        strcat(payload, encodedEntity);
        iterator = iterator->next;
    }
    log_debug("[SERVER SIDE] encoded state len : %d", strlen(payload));
    return payload;
}
