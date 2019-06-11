/*
** entities.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __SERVER_ENTITIES_H__
#define __SERVER_ENTITIES_H__


#include "../../engine.h"

EGB_Entity      *EGBS_Entity_Create(char *name);
void        	EGBS_Serializer_DecodeEntities(char *raw);
EGB_Entity      *EGBS_Serializer_DecodeEntity(char *raw);
EGB_Entity 		*EGBS_Network_FindEntityByNetworkId(char *id);
int             EGBS_Entity_Destroy(EGB_Entity *entity);

#endif
