/*
** manager.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "entitys.h"

entity_t        **entitys_manager(Uint32 flags, ...)
{
    static      entity_t **entitys;
    va_list     argp;
    entity_t    *entity;
    entity_t    **tmp;
    int         nb_entity;

    if (flags & EGB_Manager_Retrieve)
        return entitys;
    if (flags & EGB_Manager_Add)
    {
        va_start(argp, flags);
        entity = va_arg(argp, entity_t*);
        if (entity == NULL)
            return NULL;
        tmp = entitys;
        nb_entity = 0;
        while (tmp != NULL && *tmp != NULL) {
            ++nb_entity;
            tmp++;
        }
        entitys = realloc(entitys, (nb_entity + 2) * sizeof(entity_t *));
        entitys[nb_entity] = entity;
        entitys[nb_entity + 1] = NULL;
        va_end(argp);
        return NULL;
    }
    if (flags & EGB_Manager_Delete) {
        return NULL;
    }
    return NULL;
}

entity_t            *find_first_entity_by_name(char *name)
{
    entity_t        **entities;
    int             i;

    i = 0;
    entities = entitys_manager(EGB_Manager_Retrieve);
    while(entities != NULL && entities[i] != NULL)
    {
        if (strcmp(entities[i]->name, name) == 0)
            return entities[i];
        i++;
    }
    return NULL;
}
