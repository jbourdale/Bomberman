/*
** engine.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "network.h"

int		EGB_Network_Enabled = EGB_DEFAULT_NETWORK_ACTIVATION;
void 	EGB_Network_Enable() {
	EGB_Network_Enabled = EGB_DEFAULT_NETWORK_ACTIVATED;
}

void 	EGB_Network_Disable() {
	EGB_Network_Enabled = EGB_DEFAULT_NETWORK_DISACTIVATED;
}

int     EGB_Network_IsEnabled() {
    return EGB_Network_Enabled;
}

EGB_Network_Configuration		EGB_Network_Config;
void	EGB_Network_SetConfiguration(EGB_Network_Configuration config) {
	log_debug("SET CONFIGURATION %s:%d", config.ip, config.port);
	EGB_Network_Config = config;
}

EGB_Network_Configuration	EGB_Network_GetConfiguration() {
	return EGB_Network_Config;
}

void (*EGB_OnEntityUpdatedCallback)(EGB_Entity *) = NULL;
void    EGB_Network_OnEntityUpdated(void (*callback)(EGB_Entity *))
{
    EGB_OnEntityUpdatedCallback = callback;
}

void EGB_Network_TriggerOnEntityUpdatedCallback(EGB_Entity *entity)
{
    return EGB_OnEntityUpdatedCallback(entity);
}

void (*EGB_OnNewEntityRecvCallback)(EGB_Entity *) = NULL;
void    EGB_Network_OnNewEntityRecv(void (*callback)(EGB_Entity *))
{
    EGB_OnNewEntityRecvCallback = callback;
}

void EGB_Network_TriggerOnNewEntityRecvCallback(EGB_Entity *entity)
{
    return EGB_OnNewEntityRecvCallback(entity);
}
