/*
** network.h for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __NETWORK_H__
#define __NETWORK_H__

#include "../engine.h"

typedef int SOCKET;

#define EGB_DEFAULT_NETWORK_ACTIVATION 		0
#define EGB_DEFAULT_NETWORK_ACTIVATED 		1
#define EGB_DEFAULT_NETWORK_DISACTIVATED 	0

#define EGB_NETWORK_SUCCESS                 0
#define EGB_NETWORK_ERROR                   -1
#define EGB_NETWORK_DISABLED                -2
#define EGB_NETWORK_NODATA                  -3

typedef struct 			EGB_Network_Configuration_s
{
	char 				*ip;
	int 				port;
}						EGB_Network_Configuration;

// network.c
int EGB_Network_Handle();
int EGB_Network_SendEntity(EGB_Entity *entity);

//configuration.c
void    EGB_Network_Enable();
void    EGB_Network_Disable();
int     EGB_Network_IsEnabled();
void    EGB_Network_SetConfiguration(EGB_Network_Configuration config);
EGB_Network_Configuration   EGB_Network_GetConfiguration();
void    EGB_Network_OnEntityUpdated(void (*callback)(EGB_Entity *));
void    EGB_Network_TriggerOnEntityUpdatedCallback(EGB_Entity *entity);
void    EGB_Network_OnNewEntityRecv(void (*callback)(EGB_Entity *));
void    EGB_Network_TriggerOnNewEntityRecvCallback(EGB_Entity *entity);

#endif
