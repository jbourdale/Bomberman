/*
** counter.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "counter.h"

EGB_Component_Counter 	*EGB_Component_CreateCounter(int counter, int max)
{
	EGB_Component_Counter *comp;

	comp = malloc(sizeof(EGB_Component_Counter));
	comp->name = strdup("counter_component");
    comp->counter = counter;
    comp->max = max;

	return comp;
}

char    *EGB_Component_CounterSerializer(void **comp)
{
    EGB_Component_Counter *component, *cpy;
    char *payload;


    component = (EGB_Component_Counter *)*comp;

    cpy = malloc(sizeof(EGB_Component_Counter));
    cpy->name = strdup(component->name);
    cpy->counter = component->counter;
    cpy->max = component->max;

    payload = malloc(1000);
    sprintf(payload, "counter_component;%d;%d", cpy->max, cpy->counter);
    return payload;
}

void                        *EGB_Component_CounterUnserializer(char *raw)
{
    char    *counter, *max;


    if (raw == NULL) {
        log_debug("no raw data to parse");
        return NULL;
    }
    strtok(raw, ";");
    max = strtok(NULL, ";");
    counter = strtok(NULL, ";");

    return EGB_Component_CreateCounter(atoi(counter), atoi(max));
}


int 		EGB_Component_DestroyCounter() {
	return 1;
}
