/*
** components.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "components.h"

void                *EGB_FindComponentByName(EGB_Entity *entity, char *name)
{
    EGB_Component     **comp;
    int             i;
    int             nb_comp;

    comp = (EGB_Component **)entity->components;
    nb_comp = 0;
    while(comp != NULL && *comp++)
        nb_comp++;
    comp = (EGB_Component **)entity->components;

    i = 0;
    while(i < nb_comp)
    {
        if(strcmp(comp[i]->name, name) == 0)
            return (void *)comp[i];
        i++;
    }
    return NULL;
}

void                **EGB_FindComponentsByName(EGB_Entity *entity, char *name)
{
    EGB_Component     **comp_iterator;
    void            **result_comps = NULL;
    int             i, nb_comp, nb_result;

    comp_iterator = (EGB_Component **)entity->components;
    nb_comp = 0;
    while(comp_iterator != NULL && *comp_iterator++)
        nb_comp++;
    comp_iterator = (EGB_Component **)entity->components;

    nb_result = 0;
    i = 0;
    while(i < nb_comp)
    {
        if(strcmp(comp_iterator[i]->name, name) == 0) {
            result_comps = realloc(result_comps, (nb_result + 2) * sizeof(void *));
            result_comps[nb_result] = (void *)comp_iterator[i];
            result_comps[nb_result + 1] = NULL;
            nb_result++;
        }
        i++;
    }
    return result_comps;
}
