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

    // log_debug("building payload : %s", payload);

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
    log_debug("Encoded entity : %s", payload);
    return payload;
}

int EGB_Component_RegisterSerializer(
    char *name,
    char *(*serializer)(),
    void *(*unserializer)()
) {
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

EGB_Components_SerializerList *EGB_Components_GetSerializers() 
{
    return EGB_Components_Serializers;
}


void        EGB_Serializer_DecodeEntities(char *raw)
{
    char    *token, **rawEntities;
    int     i;

    log_debug("[CLIENT SIDE] DECODE ENTITIES : %s", raw);
    rawEntities = malloc(1000 * sizeof(char *));
    if (raw[strlen(raw) -1] != '#')
        return ;
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
        EGB_Serializer_DecodeEntity(strdup(rawEntities[i]));
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

    log_debug("[CLIENT SIDE] DECODE ENTITY : %s", raw);

    token = strtok_r(raw, EGB_NETWORK_VALUE_SEPARATOR, &raw); // NETWORK IDENTIFIER
    networkable_id = strtok_r(NULL, EGB_NETWORK_VALUE_SEPARATOR, &raw);
    network_ownership = strtok_r(NULL, EGB_NETWORK_VALUE_SEPARATOR, &raw);
    entity = EGB_Network_FindEntityByNetworkId(networkable_id);
    
    if (entity != NULL) {
        log_debug("REQUEST AFFECTING ENTITY %s", entity->name);
    }

    token = strtok_r(NULL, EGB_NETWORK_VALUE_SEPARATOR, &raw);
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
        char *raw_comp = strdup(serializedComponents[i]);
        log_debug("handling serializedComponents[%d] : %s", i, raw_comp);
        token = strtok_r(raw_comp, ";", &raw_comp); // retrieving the component name
        raw_comp = strdup(serializedComponents[i]);
        log_debug("after strtok_r : %s", raw_comp);

        iterator = EGB_Components_Serializers->first;
        while(iterator != NULL && strcmp(iterator->component_name, token) != 0) {
            iterator = iterator->next;
        }
        if (iterator != NULL && iterator->unserializer != NULL) {
            log_debug("SENDING TO %s UNSERIALIZER : %s", iterator->component_name, raw_comp);
            recievedComp = iterator->unserializer(strdup(raw_comp));
            actualComp = EGB_FindComponentByName(entity, ((EGB_Component *)recievedComp)->name);
            if (actualComp == NULL) {
                EGB_Component_AddToEntity(entity, recievedComp);
            }
            else {
                log_debug("replacing component : %s", ((EGB_Component *)recievedComp)->name);
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
