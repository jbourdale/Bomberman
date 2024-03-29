/*
** serializer.h for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __SERIALIZER_H__
#define __SERIALIZER_H__

#include "../../../engine.h"

#define EGB_ENTITY_NETWORK_IDENTIFIER '1'
#define EGB_EVENT_NETWORK_IDENTIFIER '2'
#define EGB_ERROR_NETWORK_IDENTIFIER '3'
#define EGB_NETWORK_VALUE_SEPARATOR "|"
#define EGB_NETWORK_VALUE_SEPARATOR_CHAR '|'
#define EGB_NETWORK_VALUE_EOF "#"

typedef struct EGB_Components_SerializerListEl_s EGB_Components_SerializerListEl;

struct                      EGB_Components_SerializerListEl_s
{
    char                            *component_name;
    char                            *(*serializer)();
    void                            *(*unserializer)();
    EGB_Components_SerializerListEl *next;
};

typedef struct                      EGB_Components_SerializerList_s
{
    EGB_Components_SerializerListEl *first;
}                                   EGB_Components_SerializerList;

char        *EGB_Serializer_EncodeEntity(EGB_Entity *entity);
int         EGB_Component_RegisterSerializer(char *name, char *(*serializer)(), void *(*unserializer)());
EGB_Components_SerializerList *EGB_Components_GetSerializers();
EGB_Entity  *EGB_Serializer_DecodeEntity(char *raw);
void        EGB_Serializer_DecodeEntities(char *raw);

#endif
