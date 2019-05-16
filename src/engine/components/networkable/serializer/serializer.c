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
    char                            *payload, *displayed;
    void                            **components;

    networkable_comp = (EGB_Component_Networkable *)EGB_FindComponentByName(
        entity,
        "networkable_component"
    );
    if (networkable_comp == NULL)
        return NULL;

    log_debug("EGB_Serializer_EncodeEntity");

    payload = malloc(1000);
    payload[0] = EGB_ENTITY_NETWORK_IDENTIFIER;
    payload[1] = EGB_NETWORK_VALUE_SEPARATOR_CHAR;
    payload[2] = '\0';
    displayed = malloc(50);
    sprintf(displayed, "%d", entity->displayed);
    strcat(payload, displayed);
    strcat(payload, EGB_NETWORK_VALUE_SEPARATOR);
    strcat(payload, entity->name);
    strcat(payload, EGB_NETWORK_VALUE_SEPARATOR);

    components = entity->components;
    log_debug("entity->components (%p)", entity->components);
    log_debug("components (%p) == NULL : %d", components, components == NULL);
    log_debug("*components (%p) == NULL : %d", *components, *components == NULL);
    while (components != NULL && *components != NULL) {
        if (EGB_Components_Serializers == NULL)
            break;
        iterator = EGB_Components_Serializers->first;
        EGB_Component *comp = (EGB_Component *)(*components);
        log_debug("COMPONENT NAME : %s", comp->name);
        if (comp->name == NULL)
            continue;
        while(iterator != NULL && strcmp(iterator->component_name, comp->name) != 0) {
            log_debug("iterator->component_name = %s", iterator->component_name);
            iterator = iterator->next;
        }
        if (iterator != NULL && iterator->serializer != NULL) {
            strcat(payload, strdup(iterator->serializer(components)));
            strcat(payload, EGB_NETWORK_VALUE_SEPARATOR);
        }
        components++;
    }
    log_debug("AFTER THE LOOP entity->components (%p)", entity->components);
    return payload;
}

int                                 EGB_Component_RegisterSerializer(char *name, char *(*serializer)(), void *(*unserializer)())
{
    EGB_Components_SerializerListEl *el, *iterator;

    log_debug("EGB_Component_RegisterSerializer");
    el = malloc(sizeof(EGB_Components_SerializerListEl));
    el->component_name = name;
    el->serializer = serializer;
    el->unserializer = unserializer;
    el->next = NULL;
    log_debug("adding serializer for %s : %p, next = ", el->component_name, el, el->next);

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

EGB_Entity                          *EGB_Serializer_DecodeEntity(char *raw)
{
    EGB_Components_SerializerListEl *iterator;
    EGB_Entity                      *entity;
    char                            *token, **serializedComponents;
    int                             i;

    entity = EGB_Entity_Create("tmp");
    log_debug("raw : %s", raw);
    token = strtok(raw, EGB_NETWORK_VALUE_SEPARATOR); // NETWORK IDENTIFIER

    token = strtok(NULL, EGB_NETWORK_VALUE_SEPARATOR);
    log_debug("displayed : %s", token);
    entity->displayed = atoi(token);

    token = strtok(NULL, EGB_NETWORK_VALUE_SEPARATOR);
    entity->name = token;

    log_debug("entity (%s) -> displayed : %d", entity->name, entity->displayed);

    serializedComponents = malloc(1000 * sizeof(char *));
    token = strtok(NULL, EGB_NETWORK_VALUE_SEPARATOR);
    i = 0;
    while (token != NULL) {
        log_debug("loop");
        serializedComponents[i] = malloc(strlen(token) + 1);
        strcpy(serializedComponents[i], token);
        log_debug("token : %s", token);
        log_debug("serializedComponents[%d] : %s", i, serializedComponents[i]);
        token = strtok(NULL, EGB_NETWORK_VALUE_SEPARATOR);
        i++;
    }
    log_debug("HELLO");
    serializedComponents[i] = NULL;

    i = 0;
    while(serializedComponents[i] != NULL) {
        log_debug("coucou");
        token = strtok(strdup(serializedComponents[i]), ";"); // retrieving the component name

        iterator = EGB_Components_Serializers->first;
        while(iterator != NULL && strcmp(iterator->component_name, token) != 0) {
            iterator = iterator->next;
        }
        if (iterator != NULL && iterator->unserializer != NULL) {
            void *comp = iterator->unserializer(strdup(serializedComponents[i]));
            log_debug("created component : %s", ((EGB_Component *)comp)->name);
            EGB_Component_AddToEntity(entity, comp);
        }
        i++;
    }
    return NULL;
}
