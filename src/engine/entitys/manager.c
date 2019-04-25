/*
** manager.c for  in /Bomberman/bourda_j
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

    if (entity == NULL) {
        log_debug("entitys manager : %p", entitys);
        return entitys;
    }

    tmp = entitys;
    nb_entity = 0;
    while (tmp != NULL && *tmp != NULL) {
        log_debug("entity[%d] : %p", nb_entity, *tmp);
        ++nb_entity;
        tmp++;
    }
    log_debug("nb_entity : %d", nb_entity);

    entitys = realloc(entitys, (nb_entity + 2) * sizeof(entity_t *));
    entitys[nb_entity] = entity;

    entitys[nb_entity + 1] = NULL;

    log_debug("ADD ENTITY AT %d : %p", nb_entity,entitys[nb_entity]);
    log_debug("ADD ENTITY AT %d : %p", nb_entity + 1,entitys[nb_entity + 1]);
    return NULL;
}

entity_t            *find_first_entity_by_name(char *name)
{
    entity_t        **entities;
    int             i;

    i = 0;
    entities = entitys_manager(NULL);
    while(entities != NULL && entities[i] != NULL)
    {
        if (strcmp(entities[i]->name, name) == 0)
            return entities[i];
        i++;
    }
    return NULL;
}
