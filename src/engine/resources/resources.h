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
    int             font_size; // used only for textual resources

    // Linked list
    resource_t      *next;
}					resource_t;

typedef struct 		resources_list_s
{
	resource_t 		*first;
    char            *resources_dir;
}					resources_list_t;

int                 EGB_set_resources_dir(char *dirname);
void                *EGB_get_resource(const char* resource_path);
resources_list_t    *EGB_resources_manager(Uint32 flags, ...);

#endif
