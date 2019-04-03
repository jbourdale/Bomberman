/*
** manager.c for  in /home/dev/C/My_FTL/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "entitys.h"

entity_t **entitys_manager()
{
    static entity_t **entitys;

    return entitys;
}

int             add_entity_to_manager(entity_t *entity)
{
    entity_t    **entitys;
    entity_t    **tmp;
    int         nb_entity;
    int         new_size;

    entitys = entitys_manager();
    tmp = entitys;
    nb_entity = 0;
    while (tmp != NULL && *tmp++)
        nb_entity++;

    log_debug("nb_entity : %d", nb_entity);
    new_size = (nb_entity + 1) * sizeof(entity_t *);
    log_debug("new_size : %d", new_size);
    entitys = realloc(entitys, new_size);
    entitys[nb_entity] = entity;

    return 0;
}



