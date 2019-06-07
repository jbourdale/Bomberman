/*
** resources.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "./resources.h"

/**
 * @brief      Set the resource root dir to automatic load all the resources
 *
 * @warning    Supported only on POSIX OS (MacOS / Linux)
 *
 * @note       This must be called before EGB_Init()
 *
 * @param      dirname  The resources root dirname
 *
 * @return     status   Return 0 if the dirname is valid and availible, overwise return 1
 */
int 				EGB_Set_Resources_RootDir(char *dirname)
{
	#ifdef _WIN32
		log_error("[RESOURCES] Resources dir scan are not supported on Windows yet.");
		return 1;
	#endif

	struct stat 	sb;
    if (stat(dirname, &sb) == 0 && S_ISDIR(sb.st_mode)) {
    	log_debug("RESOURCES DIR OK");
        EGB_ResourcesManager(EGB_Resources_Manager_Set_Dir, dirname);
		return 0;
    }
	log_error("[RESOURCES] Unable to open resources dir (%s)", dirname);
	return 1;
}

/**
 * @brief      Set the fontsize for a resource. Only availible for Font files
 *
 * @param      resource_path  The font resource path
 * @param      size           font size
 *
 * @return     status 0 = OK, 1 = KO
 */
int     EGB_Resource_SetFontSize(char *resource_path, int size)
{
    log_debug("resource path : %s, size : %d", resource_path, size);
    return 1;
}

/**
 * @brief      Return the SDL resource (SDL_Texture, TTF_Font...) associated to the resource path
 *
 * @note       For a root dir `./resources/` and a file `./resources/myImg.png`,
 * the resource_path will be `myImg.png`
 *
 * @param      resource_path  The resource path
 *
 * @return     A generic pointer on your ressource
 */
void 					*EGB_Get_Resource(const char* resource_path)
{
    EGB_Resource_List    *manager;
    EGB_Resource          *resources_iterator;

    manager = EGB_ResourcesManager(EGB_Manager_Retrieve);
    resources_iterator = manager->first;
    while (resources_iterator && strcmp(resources_iterator->resource_path, resource_path) != 0) {
    	resources_iterator = resources_iterator->next;
    }
    if (resources_iterator) {
    	return resources_iterator->resource;
    }
	return NULL;
}
