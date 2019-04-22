#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "../engine.h"

typedef struct          component_s
{
    char        *name;
    void        *data;
}                       component_t;

void *find_component_by_name(entity_t *entity, char *name);
void **find_components_by_name(entity_t *entity, char *name);

#endif
