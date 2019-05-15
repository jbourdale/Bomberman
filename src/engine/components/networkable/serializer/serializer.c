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
    char                            *payload, *payload_start;
    void                            **components;

    networkable_comp = (EGB_Component_Networkable *)EGB_FindComponentByName(
        entity,
        "networkable_component"
    );
    if (networkable_comp == NULL)
        return NULL;

    log_debug("EGB_Serializer_EncodeEntity");

    payload = malloc(EGB_NETWORKABLE_ID_LENGTH);
    payload_start = payload;
    payload[0] = EGB_ENTITY_NETWORK_IDENTIFIER;
    payload[1] = EGB_NETWORK_VALUE_SEPARATOR_CHAR;
    payload[2] = '\0';

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

int                                 EGB_Component_RegisterSerializer(char *name, char *(*serializer)())
{
    EGB_Components_SerializerListEl *el, *iterator;

    log_debug("EGB_Component_RegisterSerializer");
    el = malloc(sizeof(EGB_Components_SerializerListEl));
    el->component_name = name;
    el->serializer = serializer;
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

EGB_Entity  *EGB_Serializer_DecodeEntity(char *raw)
{
    log_debug("raw : %s", raw);
    return NULL;
}
