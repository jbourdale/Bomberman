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

typedef struct 		EGB_Resource_s
{
	char 			*resource_path;
	void 			*resource;
    int             font_size; // used only for textual resources

    // Linked list
    EGB_Resource      *next;
}					EGB_Resource;

typedef struct 		EGB_Resource_List_s
{
	EGB_Resource 		*first;
    char            *resources_dir;
}					EGB_Resource_List;

int                 EGB_Set_Resources_RootDir(char *dirname);
void                *EGB_Get_Resource(const char* resource_path);
EGB_Resource_List    *EGB_ResourcesManager(Uint32 flags, ...);

#endif
