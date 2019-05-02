/*
** resources.h for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __RESOURCES_H__
#define __RESOURCES_H__

#include "../engine.h"

typedef struct 		resource_s
{
	char 			*resource_path;
	void 			*resource;
}					resource_t;

typedef struct 		resources_list_s
{
	resource_t 		*first;
}					resources_list_t;

int 	EGB_set_resources_dir(char *dirname);
int 	EGB_load_resources();
int		EGB_load_resource(const char* resource_path);
void 	*EGB_get_resource(const char* resource_path);

#endif