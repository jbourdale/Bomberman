/*
** components.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "entitys.h"

int             add_component_to_entity(entity_t *entity, void *component)
{
    void        **tmp_comp;
    int         nb_comp;
    log_debug("add_component_to_entity");

    if (component == NULL)
    {
        log_debug("no component specified, aborting");
        return 1;
    }

    tmp_comp = entity->components;
    nb_comp = 0;
    while(tmp_comp != NULL && *tmp_comp++)
        nb_comp++;

    entity->components = realloc(entity->components, (nb_comp + 2) * sizeof(void *));
    entity->components[nb_comp] = component;
    entity->components[nb_comp + 1] = NULL;
    return 0;
}

int             add_components_to_entity(entity_t *entity, void **components)
{
    void        **comp;

    comp = components;
    while (*comp++)
    {
        if(add_component_to_entity(entity, *comp))
        {
            destroy_entity(entity);
            return 1;
        }
    }
    free(comp);
    return 0;
}
