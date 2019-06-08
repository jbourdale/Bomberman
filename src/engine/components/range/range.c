/*
** range.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "range.h"

EGB_Component_Range 	*EGB_Component_CreateRange(int range)
{
	EGB_Component_Range *comp;

	comp = malloc(sizeof(EGB_Component_Range));
	comp->name = strdup("range_component");
    comp->range = range;

	return comp;
}

char    *EGB_Component_RangeSerializer(void **comp)
{
    EGB_Component_Range *component, *cpy;
    char *payload;

    component = (EGB_Component_Range *)*comp;

    cpy = malloc(sizeof(EGB_Component_Range));
    cpy->name = strdup(component->name);
    cpy->range = component->range;

    payload = malloc(1000);
    sprintf(payload, "range_component;%d", cpy->range);
    return payload;
}

void                        *EGB_Component_RangeUnserializer(char *raw)
{
    char    *token;

    if (raw == NULL) {
        log_debug("no raw data to parse");
        return NULL;
    }
    token = strtok_r(raw, ";", &raw);
    token = strtok_r(NULL, ";", &raw);

    return EGB_Component_CreateRange(atoi(token));
}


int 		EGB_Component_DestroyRange() {
	return 1;
}
