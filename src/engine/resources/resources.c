/*
** resources.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "./resources.h"

char 				*resource_dir = NULL;
resources_list_t 	*resources_list;

int 				EGB_set_resources_dir(char *dirname) 
{
	#ifndef __unix__
		log_error("[RESOURCES] Resources dir scan are not supported on Windows yet.");
		return 1;
	#endif 

	struct stat 	sb;
    if (stat(dirname, &sb) == 0 && S_ISDIR(sb.st_mode)) {
    	log_debug("RESOURCES DIR OK");
		resource_dir = dirname;
		return 0;
    }
	log_error("[RESOURCES] Enable to open resources dir (%s)", dirname);
	return 1;
}

void EGB_iterate_resources_dir(const char *dirname)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(dirname)))
        return;

    while ((entry = readdir(dir)) != NULL) {
        char path[1024];
    	snprintf(path, sizeof(path), "%s/%s", dirname, entry->d_name);
        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            EGB_iterate_resources_dir(path);
        } else {
            EGB_load_resource(path);
        }
    }
    closedir(dir);
}


int 				EGB_load_resources()
{
	if (resource_dir == NULL)
		return 1;
	EGB_iterate_resources_dir(resource_dir);
    return 0; 
}

int		EGB_load_resource(const char* resource_path)
{
	log_debug("EGB_load_resource %s", resource_path);
	return 1;
}

void 	*EGB_get_resource(const char* resource_path)
{
	log_debug("oui %s", resource_path);
	return NULL;
}