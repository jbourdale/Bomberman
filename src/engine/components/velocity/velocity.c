/*
** velocity.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "velocity.h"

EGB_Component_Velocity 	*EGB_Component_CreateVelocity(int x, int y)
{
	EGB_Component_Velocity *comp;

	comp = malloc(sizeof(EGB_Component_Velocity));
	comp->name = strdup("velocity_component");
    comp->x = x;
    comp->y = y;

	return comp;
}

void 	EGB_Component_Velocity_SetX(EGB_Entity *entity, int x)
{
	EGB_Component_Velocity *comp;

	comp = EGB_FindComponentByName(entity, "velocity_component");
	if (comp == NULL) {
		log_debug("Entity doesn't have velocity component to affect");
		return;
	}
	comp->x = x;
}

void 	EGB_Component_Velocity_SetY(EGB_Entity *entity, int y)
{
	EGB_Component_Velocity *comp;

	comp = EGB_FindComponentByName(entity, "velocity_component");
	if (comp == NULL) {
		log_debug("Entity doesn't have velocity component to affect");
		return;
	}
	comp->y = y;
}

char    *EGB_Component_VelocitySerializer(void **comp)
{
    EGB_Component_Velocity *component, *cpy;
    char *payload;


    component = (EGB_Component_Velocity *)*comp;

    cpy = malloc(sizeof(EGB_Component_Velocity));
    cpy->name = strdup(component->name);
    cpy->x = component->x;
    cpy->y = component->y;

    payload = malloc(1000);
    sprintf(payload, "velocity_component;%d;%d", cpy->x, cpy->y);
    return payload;
}

void                        *EGB_Component_VelocityUnserializer(char *raw)
{
    char    *x, *y;


    if (raw == NULL) {
        log_debug("no raw data to parse");
        return NULL;
    }
    strtok(raw, ";");
    x = strtok(NULL, ";");
    y = strtok(NULL, ";");

    return EGB_Component_CreateVelocity(atoi(x), atoi(y));
}


int 		EGB_Component_DestroyVelocity() {
	return 1;
}
