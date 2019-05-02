/*
** resources.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "./resources.h"

int 				EGB_set_resources_dir(char *dirname)
{
	#ifdef _WIN32
		log_error("[RESOURCES] Resources dir scan are not supported on Windows yet.");
		return 1;
	#endif

	struct stat 	sb;
    if (stat(dirname, &sb) == 0 && S_ISDIR(sb.st_mode)) {
    	log_debug("RESOURCES DIR OK");
        EGB_resources_manager(EGB_Resources_Manager_Set_Dir, dirname);
		return 0;
    }
	log_error("[RESOURCES] Unable to open resources dir (%s)", dirname);
	return 1;
}

int     EGB_set_resource_font_size(char *resource_path, int size)
{
    log_debug("resource path : %s, size : %d", resource_path, size);
    return 1;
}

void 					*EGB_get_resource(const char* resource_path)
{
    resources_list_t    *manager;
    resource_t          *resources_iterator;

    manager = EGB_resources_manager(EGB_Manager_Retrieve);
    resources_iterator = manager->first;
    while (resources_iterator && strcmp(resources_iterator->resource_path, resource_path) != 0) {
    	resources_iterator = resources_iterator->next;
    }
    if (resources_iterator) {
    	return resources_iterator->resource;
    }
	return NULL;
}
