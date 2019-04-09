/*
** manager.c for  in /home/dev/C/My_FTL/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "entitys.h"

entity_t        **entitys_manager(entity_t *entity)
{
    static      entity_t **entitys;
    entity_t    **tmp;
    int         nb_entity;
    int         new_size;

    if (entity == NULL)
        return entitys;

    tmp = entitys;
    nb_entity = 0;
    while (tmp != NULL && *tmp++)
        nb_entity++;

    log_debug("nb_entity : %d", nb_entity);
    if (nb_entity == 0)
    {
        entitys = malloc(2 * sizeof(entity_t *));
        entitys[0] = entity;
        entitys[1] = NULL;
    } else
    {
        new_size = (nb_entity + 2) * sizeof(entity_t *);
        log_debug("new_size : %d", new_size);
        entitys = realloc(entitys, new_size);
        entitys[nb_entity] = entity;
        entitys[nb_entity + 1] = NULL;
        log_debug("entitys[%d] : %p", nb_entity, entity);
        log_debug("entitys[%d] : %p", nb_entity + 1, entity);
    }
    return NULL;
}


