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
    register_entity_to_managers(entity, (component_t *)component);
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


int register_entity_to_managers(entity_t *entity, component_t *component)
{
    if(strcmp(component->name, "position_component") == 0) {
        entities_position_manager(EGB_Manager_Add, entity, (position_component_t *) component);
        return 0;
    }
    return 1;
}