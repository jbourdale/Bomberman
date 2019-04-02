#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "../engine.h"

struct          component_s
{
    char        *name;
    void        *data;
} typedef       component_t;

void *find_component_by_name(entity_t *entity, char *name);

#endif
