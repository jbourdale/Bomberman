/*
** serializer.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "serializer.h"

EGB_Components_SerializerList *EGB_Components_Serializers = NULL;

/**
 * @brief      Return the string payload that describe an entity
 *
 * @param      entity  The entity
 *
 * @return     payload
 */
char                                *EGB_Serializer_EncodeEntity(EGB_Entity *entity)
{
    EGB_Components_SerializerListEl *iterator;
    EGB_Component_Networkable       *networkable_comp;
    char                            *payload, *displayed, *network_owner;
    void                            **components;

    networkable_comp = (EGB_Component_Networkable *)EGB_FindComponentByName(
        entity,
        "networkable_component"
    );
    if (networkable_comp == NULL) {
        log_error("TRYING TO SERIALIZE ENTITY (%s) THAT DOESN'T HAVE NETWORKABLE COMP", entity->name);
        return NULL;
    }

    payload = malloc(1000);
    payload[0] = EGB_ENTITY_NETWORK_IDENTIFIER;
    payload[1] = EGB_NETWORK_VALUE_SEPARATOR_CHAR;
    payload[2] = '\0';
    strcat(payload, networkable_comp->id);
    strcat(payload, EGB_NETWORK_VALUE_SEPARATOR);

    network_owner = malloc(2);
    sprintf(network_owner, "%d", networkable_comp->owner);
    strcat(payload, network_owner);
    strcat(payload, EGB_NETWORK_VALUE_SEPARATOR);

    displayed = malloc(2);
    sprintf(displayed, "%d", entity->displayed);
    strcat(payload, displayed);
    strcat(payload, EGB_NETWORK_VALUE_SEPARATOR);
    strcat(payload, entity->name);
    strcat(payload, EGB_NETWORK_VALUE_SEPARATOR);

    log_debug("building payload : %s", payload);

    components = entity->components;
    while (components != NULL && *components != NULL) {
        if (EGB_Components_Serializers == NULL)
            break;
        iterator = EGB_Components_Serializers->first;
        EGB_Component *comp = (EGB_Component *)(*components);
        if (comp->name == NULL)
            continue;
        while(iterator != NULL && strcmp(iterator->component_name, comp->name) != 0) {
            iterator = iterator->next;
        }
        if (iterator != NULL && iterator->serializer != NULL) {
            strcat(payload, strdup(iterator->serializer(components)));
            strcat(payload, EGB_NETWORK_VALUE_SEPARATOR);
        }
        components++;
    }
    payload[strlen(payload) - 1] = '#';
    log_debug("payload returned : %s", payload);
    return payload;
}

int                                 EGB_Component_RegisterSerializer(char *name, char *(*serializer)(), void *(*unserializer)())
{
    EGB_Components_SerializerListEl *el, *iterator;

    el = malloc(sizeof(EGB_Components_SerializerListEl));
    el->component_name = name;
    el->serializer = serializer;
    el->unserializer = unserializer;
    el->next = NULL;

    if (EGB_Components_Serializers == NULL) {
        EGB_Components_Serializers = malloc(sizeof(EGB_Components_SerializerList));
        EGB_Components_Serializers->first = el;
        return 0;
    }
    iterator = EGB_Components_Serializers->first;
    while(iterator->next != NULL) {
        iterator = iterator->next;
    }
    iterator->next = el;
    return 0;
}

void        EGB_Serializer_DecodeEntities(char *raw)
{
    char    *token, **rawEntities;
    int     i;

    log_debug("DECODE ENTITIES : %s", raw);
    rawEntities = malloc(1000 * sizeof(char *));
    token = strtok(raw, "#");
    i = 0;
    while (token != NULL) {
        rawEntities[i] = malloc(strlen(token) + 1);
        strcpy(rawEntities[i], token);
        i++;
        token = strtok(NULL, "#");
    }
    rawEntities[i] = NULL;

    i = 0;
    while (rawEntities[i] != NULL)
    {
        log_debug("decode entity : %s", rawEntities[i]);
        EGB_Serializer_DecodeEntity(rawEntities[i]);
        i++;
    }
}

EGB_Entity                          *EGB_Serializer_DecodeEntity(char *raw)
{
    int                             update = 1; // if we are updating or creating a entity
    EGB_Components_SerializerListEl *iterator;
    EGB_Entity                      *entity;
    void                            *recievedComp, *actualComp;
    char                            *token, *networkable_id, *network_ownership;
    char                            **serializedComponents;
    int                             i;

    // raw = strtok(raw, "#");
    token = strtok(raw, EGB_NETWORK_VALUE_SEPARATOR); // NETWORK IDENTIFIER

    networkable_id = strtok(NULL, EGB_NETWORK_VALUE_SEPARATOR);
    network_ownership = strtok(NULL, EGB_NETWORK_VALUE_SEPARATOR);
    log_debug("[DECODE ENTITY] NETWORK OWNERSHIP : %s", network_ownership);
    entity = EGB_Network_FindEntityByNetworkId(networkable_id);

    token = strtok(NULL, EGB_NETWORK_VALUE_SEPARATOR);
    log_debug("NEXT TOKEN  : %s", token);
    if (strcmp(token, "destroy") == 0) {
        if (entity != NULL)
            EGB_Entity_Destroy(entity);
        return NULL;
    }
    if (entity == NULL) {
        update = 0;
        entity = EGB_Entity_Create("tmp");
        EGB_Component_Networkable *networkable_comp = EGB_Component_CreateNetworkable();
        networkable_comp->id = networkable_id;
        networkable_comp->owner = atoi(network_ownership);
        EGB_Component_AddToEntity(entity, networkable_comp);
        log_debug("[CREATING NEW ENTITY]");
    }
    entity->displayed = atoi(token);

    token = strtok(NULL, EGB_NETWORK_VALUE_SEPARATOR);
    entity->name = token;

    serializedComponents = malloc(1000 * sizeof(char *));
    token = strtok(NULL, EGB_NETWORK_VALUE_SEPARATOR);
    i = 0;
    while (token != NULL) {
        serializedComponents[i] = malloc(strlen(token) + 1);
        strcpy(serializedComponents[i], token);
        token = strtok(NULL, EGB_NETWORK_VALUE_SEPARATOR);
        i++;
    }
    serializedComponents[i] = NULL;

    i = 0;
    while(serializedComponents[i] != NULL) {
        token = strtok(strdup(serializedComponents[i]), ";"); // retrieving the component name

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
    if (update)
        EGB_Network_TriggerOnEntityUpdatedCallback(entity);
    else
        EGB_Network_TriggerOnNewEntityRecvCallback(entity);

    return NULL;
}
