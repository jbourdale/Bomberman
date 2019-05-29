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
    component->name = "networkable_component";
    component->id = malloc(EGB_NETWORKABLE_ID_LENGTH + 10); // + 10 is to store pid
    component->id = EGB_Network_GenerateId(component->id);
    component->owner = 0;

    log_debug("Networkable component created : (%s, %s)", component->name, component->id);
    return component;
}

char                    *EGB_Network_GenerateId(char *str)
{
    char                *pid; // Used to generate different ID between different clients
    size_t       length = EGB_NETWORKABLE_ID_LENGTH;
    static const char   charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJK...";

    --length;
    for (size_t n = 0; n < length; n++) {
        int key = rand() % (int) (sizeof(charset) - 1);
        str[n] = charset[key];
    }
    str[length] = '\0';
    pid = malloc(10);
    sprintf(pid, "%d", getpid());
    str = strcat(str, pid);
    return str;
}

EGB_Entity *EGB_Network_FindEntityByNetworkId(char *id) {
    EGB_Entity                  *entity;
    EGB_Component_Networkable   *networkable_component;
    EGB_Entity_Manager          *entities_manager;
    EGB_Entity_Manager_Element  *manager_iterator;

    entities_manager = EGB_Manager_Entity(EGB_Manager_Retrieve);
    if (entities_manager == NULL)
        return NULL;
    manager_iterator = entities_manager->first;
    while (manager_iterator != NULL)
    {
        entity = manager_iterator->entity;
        networkable_component = EGB_FindComponentByName(
            entity,
            "networkable_component"
        );
        if (networkable_component != NULL && strcmp(networkable_component->id, id) == 0)
            return entity;
        manager_iterator = manager_iterator->next;
    }
    return NULL;
}

int                         EGB_Component_DestroyNetworkable(EGB_Entity *entity)
{
    EGB_Component_Position    *comp;

    log_debug("EGB_Component_DestroyNetworkable");
    comp = (EGB_Component_Position *)EGB_FindComponentByName(entity, "networkable_component");
    if (comp == NULL)
        return 1;

    //free(comp);
    return 0;
}

