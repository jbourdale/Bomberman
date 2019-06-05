/*
** serializer.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "entities.h"

void        EGBS_Serializer_DecodeEntities(char *raw)
{
    char    *token, **rawEntities;
    int     i;

    // log_debug("DECODE ENTITIES : %s", raw);
    rawEntities = malloc(1000 * sizeof(char *));
    token = strtok_r(raw, "#", &raw);
    i = 0;
    while (token != NULL) {
        rawEntities[i] = malloc(strlen(token) + 1);
        strcpy(rawEntities[i], token);
        i++;
        token = strtok_r(NULL, "#", &raw);
    }
    rawEntities[i] = NULL;

    i = 0;
    while (rawEntities[i] != NULL)
    {
        EGBS_Serializer_DecodeEntity(strdup(rawEntities[i]));
        i++;
    }
}

EGB_Entity                          *EGBS_Serializer_DecodeEntity(char *raw)
{
    EGB_Components_SerializerList   *EGB_Components_Serializers;
    EGB_Components_SerializerListEl *iterator;
    EGB_Entity                      *entity;
    void                            *recievedComp, *actualComp;
    char                            *token, *networkable_id, *network_ownership;
    char                            **serializedComponents;
    int                             i;

    EGB_Components_Serializers = EGB_Components_GetSerializers();

    token = strtok_r(raw, EGB_NETWORK_VALUE_SEPARATOR, &raw); // NETWORK IDENTIFIER
    networkable_id = strtok_r(NULL, EGB_NETWORK_VALUE_SEPARATOR, &raw);
    network_ownership = strtok_r(NULL, EGB_NETWORK_VALUE_SEPARATOR, &raw);
    entity = EGBS_Network_FindEntityByNetworkId(networkable_id);
    token = strtok_r(NULL, EGB_NETWORK_VALUE_SEPARATOR, &raw);
    if (strcmp(token, "destroy") == 0) {
        if (entity != NULL)
            EGBS_Entity_Destroy(entity);
        return NULL;
    }
    if (entity == NULL) {
        entity = EGBS_Entity_Create("tmp");
        EGB_Component_Networkable *networkable_comp = EGB_Component_CreateNetworkable();
        networkable_comp->id = networkable_id;
        networkable_comp->owner = atoi(network_ownership);
        EGB_Component_AddToEntity(entity, networkable_comp);
        // log_debug("[CREATING NEW ENTITY]");
    }
    entity->displayed = atoi(token);

    token = strtok_r(NULL, EGB_NETWORK_VALUE_SEPARATOR, &raw);
    entity->name = token;

    serializedComponents = malloc(1000 * sizeof(char *));
    token = strtok_r(NULL, EGB_NETWORK_VALUE_SEPARATOR, &raw);
    i = 0;
    while (token != NULL) {
        serializedComponents[i] = malloc(strlen(token) + 1);
        strcpy(serializedComponents[i], token);
        token = strtok_r(NULL, EGB_NETWORK_VALUE_SEPARATOR, &raw);
        i++;
    }
    serializedComponents[i] = NULL;

    i = 0;
    while(serializedComponents[i] != NULL) {
        token = strtok_r(strdup(serializedComponents[i]), ";", &raw); // retrieving the component name

        iterator = EGB_Components_Serializers->first;
        while(iterator != NULL && strcmp(iterator->component_name, token) != 0) {
            iterator = iterator->next;
        }
        if (iterator != NULL && iterator->unserializer != NULL) {
            recievedComp = iterator->unserializer(strdup(serializedComponents[i]));
            actualComp = EGB_FindComponentByName(entity, ((EGB_Component *)recievedComp)->name);
            if (actualComp == NULL) {
                EGB_Component_AddToEntity(entity, recievedComp);
            }
            else {
                EGB_Entity_ReplaceComponent(entity, recievedComp);
            }

        }
        i++;
    }
    return NULL;
}

EGB_Entity *EGBS_Network_FindEntityByNetworkId(char *id)
{
    EGB_Entity                  *entity;
    EGB_Component_Networkable   *networkable_component;
    EGB_Entity_Manager          *entities_manager;
    EGB_Entity_Manager_Element  *manager_iterator;

    entities_manager = EGBS_Manager_Entity(EGB_Manager_Retrieve);
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
