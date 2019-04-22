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
    int         new_size;

    if (entity == NULL)
        return entitys;

    tmp = entitys;
    nb_entity = 0;
    while (tmp != NULL && *tmp++)
        nb_entity++;

    if (nb_entity == 0)
    {
        entitys = malloc(2 * sizeof(entity_t *));
        entitys[0] = entity;
        entitys[1] = NULL;
    } else
    {
        new_size = (nb_entity + 2) * sizeof(entity_t *);
        entitys = realloc(entitys, new_size);
        entitys[nb_entity] = entity;
        entitys[nb_entity + 1] = NULL;
    }
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
