/*
** components.c for  in /home/dev/C/My_FTL/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "components.h"

void                *find_component_by_name(entity_t *entity, char *name)
{
    component_t     **comp;
    int             i;
    int             nb_comp;
    // log_debug("find_component_by_name");

    comp = (component_t **)entity->components;
    // log_debug("entity components is NULL : %d", comp == NULL);
    nb_comp = 0;
    while(comp != NULL && *comp++)
        nb_comp++;
    comp = (component_t **)entity->components;

    // log_debug("nb components : %d", nb_comp);
    i = 0;
    while(i < nb_comp)
    {
        // log_debug("iterate : %d", i);
        // log_debug("component is NULL : %d", comp[i] == NULL);
        // log_debug("component name : %s", comp[i]->name);
        if(strcmp(comp[i]->name, name) == 0)
            return (void *)comp[i];
        i++;
    }
    return NULL;
}
