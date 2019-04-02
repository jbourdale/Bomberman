/*
** components.c for  in /home/dev/C/My_FTL/bourda_j
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

    if (component == NULL)
        return 1;

    tmp_comp = entity->components;
    nb_comp = 0;
    while(*tmp_comp++)
        nb_comp++;
    free(tmp_comp);

    new_size = (nb_comp + 1) * sizeof(void *);
    entity->components = realloc(entity->components, new_size);
    entity->components[nb_comp + 1] = component;
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
