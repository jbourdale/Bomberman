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

    comp = (component_t **)entity->components;

    while(*comp++ && strcmp((*comp)->name, name) != 0);
    return (void *)comp;
}
