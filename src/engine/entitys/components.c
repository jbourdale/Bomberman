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
    int         new_size;
    int         nb_comp;
    log_debug("add_component_to_entity");

    if (component == NULL)
    {
        log_debug("no component specified, aborting");
        return 1;
    }

    tmp_comp = entity->components;
    log_debug("tmp_comp == NULL : %d", tmp_comp == NULL);
    nb_comp = 0;
    while(tmp_comp != NULL && *tmp_comp++)
        nb_comp++;
    log_debug("nb of components on this entity : %d", nb_comp);
    free(tmp_comp);

    new_size = (nb_comp + 2) * sizeof(void *);
    log_debug("adding 1 component (total: %d), new components array size : %d", (nb_comp + 1), new_size);
    entity->components = realloc(entity->components, new_size);
    entity->components[nb_comp] = component;
    entity->components[nb_comp + 1] = NULL;
    log_debug("component successfuly added");
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
