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
	EGB_Network_Config = config;
}

EGB_Network_Configuration	EGB_Network_GetConfiguration() {
	return EGB_Network_Config;
}
