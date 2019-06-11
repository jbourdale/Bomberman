/*
** id.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "id.h"

EGB_Component_Id 	*EGB_Component_CreateId(int id)
{
	EGB_Component_Id *comp;

	comp = malloc(sizeof(EGB_Component_Id));
	comp->name = strdup("id_component");
    comp->id = id;

	return comp;
}

char    *EGB_Component_IdSerializer(void **comp)
{
    EGB_Component_Id *component, *cpy;
    char *payload;


    component = (EGB_Component_Id *)*comp;

    cpy = malloc(sizeof(EGB_Component_Id));
    cpy->name = strdup(component->name);
    cpy->id = component->id;

    payload = malloc(1000);
    sprintf(payload, "id_component;%d", cpy->id);
    return payload;
}

void                        *EGB_Component_IdUnserializer(char *raw)
{
    char    *token;


    if (raw == NULL) {
        log_debug("no raw data to parse");
        return NULL;
    }
    token = strtok_r(raw, ";", &raw);
    token = strtok_r(NULL, ";", &raw);

    return EGB_Component_CreateId(atoi(token));
}


int 		EGB_Component_DestroyId() {
	return 1;
}
