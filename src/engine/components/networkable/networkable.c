/*
** networkable.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "networkable.h"

EGB_Component_Networkable       *EGB_Component_CreateNetworkable()
{
    EGB_Component_Networkable   *component;

    log_debug("EGB_Component_CreateNetworkable");

    component = malloc(sizeof(EGB_Component_FPSRate));
    component->name = strdup("networkable_component");
    component->id = malloc(EGB_NETWORKABLE_ID_LENGTH);
    component->id = EGB_Network_GenerateId(component->id);
    return component;
}

char                    *EGB_Network_GenerateId(char *str)
{
    static size_t       length = EGB_NETWORKABLE_ID_LENGTH;
    static const char   charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJK...";

    log_debug("EGB_Network_GenerateId");
    --length;
    for (size_t n = 0; n < length; n++) {
        int key = rand() % (int) (sizeof(charset) - 1);
        str[n] = charset[key];
    }
    str[length] = '\0';
    return str;
}

int                         EGB_Component_DestroyNetworkable(EGB_Entity *entity)
{
    EGB_Component_Position    *comp;

    log_debug("EGB_Component_DestroyNetworkable");
    comp = (EGB_Component_Position *)EGB_FindComponentByName(entity, "networkable_component");
    if (comp == NULL)
        return 1;

    free(comp);
    return 0;
}

