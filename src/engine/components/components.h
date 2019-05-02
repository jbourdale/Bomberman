#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "../engine.h"

typedef struct          component_s
{
    char        *name;
    void        *data;
}                       component_t;

void *EGB_FindComponentByName(entity_t *entity, char *name);
void **EGB_FindComponentsByName(entity_t *entity, char *name);

#endif
