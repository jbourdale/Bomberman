#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "../engine.h"

typedef struct          EGB_Component_s
{
    char        *name;
    void        *data;
}                       EGB_Component;

void *EGB_FindComponentByName(EGB_Entity *entity, char *name);
void **EGB_FindComponentsByName(EGB_Entity *entity, char *name);

#endif
