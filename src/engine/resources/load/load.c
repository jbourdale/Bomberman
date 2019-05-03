/*
** load.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "load.h"

/**
 * @brief      Iterate recursively on the resource root dir to load all files
 *
 * @param[in]  dirname  The resources root dirname
 */
void EGB_Iterate_RootResourcesDir(const char *dirname)
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
            EGB_Iterate_RootResourcesDir(path);
        } else {
            EGB_LoadResource(path);
        }
    }
    closedir(dir);
}


/**
 * @brief      Load all the resources found in resources root dir
 * 
 * @note       See EGB_Set_Resources_RootDir()
 * 
 * @warning    Only PNG and TTF files are yet handled.
 *
 * @return     status   If the resources have been successfuly loaded
 *              <ul>
 *                  <li>0 = Successfuly loaded</li>
 *                  <li>1 = An error occured</li>
 *              </ul>
 */
int                     EGB_LoadResources()
{
    EGB_Resource_List    *manager;

    manager = EGB_ResourcesManager(EGB_Manager_Retrieve);
    if (manager->resources_dir == NULL)
        return 1;
    EGB_Iterate_RootResourcesDir(manager->resources_dir);
    return 0;
}

/**
 * @brief      Load a specific resource and add it to the manager
 *
 * @param      resource_path  The full resource path (with resource root dir)
 *
 * @return     status   If the resources have been successfuly loaded
 *              <ul>
 *                  <li>0 = Successfuly loaded</li>
 *                  <li>1 = An error occured</li>
 *              </ul>
 */
int             EGB_LoadResource(char* resource_path)
{
    char        *filename, *extension;
    EGB_Resource  *resource_entry;
    void        *resource;
    EGB_Resource_List    *manager;

    manager = EGB_ResourcesManager(EGB_Manager_Retrieve);
    filename = EGB_Str_Remove_Substr(strdup(resource_path), manager->resources_dir);
    extension = EGB_Get_FilenameExt(resource_path);
    if (filename == NULL || extension == NULL)
        return 1;
    while (*filename == '/')
        filename++;

    log_debug("resource_path : %s", resource_path);

    if (strcmp(extension, "png") == 0)
        resource = (void *)EGB_Resource_LoadPNG(resource_path);
    else if (strcmp(extension, "ttf") == 0)
        resource = (void *)EGB_Resource_LoadTTF(resource_path, EGB_DEFAULT_FONT_SIZE);
    else
        return 1;

    resource_entry = malloc(sizeof(EGB_Resource));
    resource_entry->resource_path = filename;
    resource_entry->resource = resource;
    resource_entry->font_size = 0;
    if (strcmp(extension, "ttf") == 0)
        resource_entry->font_size = EGB_DEFAULT_FONT_SIZE;

    EGB_ResourcesManager(EGB_Manager_Add, resource_entry);
    return 0;
}


/**
 * @brief      Return the extension of a filename
 *
 * @param      filename  The filename
 *
 * @return     The extension name string or NULL if not found
 */
char            *EGB_Get_FilenameExt(char *filename)
{
    char        *dot;

    dot = strrchr(filename, '.');
    if(!dot || dot == filename) return NULL;
    return dot + 1;
}

/**
 * @brief      Remove a substring from a string
 *
 * @param      str   The string
 * @param[in]  sub   The substring to remove
 *
 * @return     str   The updated string
 */
char        *EGB_Str_Remove_Substr(char *str, const char *sub) {
    size_t  len;
    char    *p;

    len = strlen(sub);
    if (len > 0) {
        p = str;
        while ((p = strstr(p, sub)) != NULL) {
            memmove(p, p + len, strlen(p + len) + 1);
        }
    }
    return str;
}
