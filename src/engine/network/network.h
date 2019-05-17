/*
** network.h for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __NETWORK_H__
#define __NETWORK_H__

#include "../../engine.h"

#define EGB_DEFAULT_NETWORK_ACTIVATION 		0
#define EGB_DEFAULT_NETWORK_ACTIVATED 		1
#define EGB_DEFAULT_NETWORK_DISACTIVATED 	0

typedef struct 			EGB_Network_Configuration_s
{
	char 				*ip;
	int 				port;
}						EGB_Network_Configuration;

#endif