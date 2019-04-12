#ifndef __NETWORKABLE_H__
#define __NETWORKABLE_H__

#include "../../engine.h"

typedef struct 			networkable_entity_list_s
{
	char 				*entity_name;
	int 				entity_id;
}						networkable_entity_list_t

typedef struct          networkable_component_s
{
    char        *name;
    int         entity_id;
}                       networkable_component_t;

#endif