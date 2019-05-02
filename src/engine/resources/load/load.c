/*
** load.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "load.h"

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


int                     EGB_load_resources()
{
    resources_list_t    *manager;

    manager = EGB_resources_manager(EGB_Manager_Retrieve);
    if (manager->resources_dir == NULL)
        return 1;
    EGB_iterate_resources_dir(manager->resources_dir);
    return 0;
}

int             EGB_load_resource(char* resource_path)
{
    char        *filename, *extension;
    resource_t  *resource_entry;
    void        *resource;
    resources_list_t    *manager;

    manager = EGB_resources_manager(EGB_Manager_Retrieve);
    filename = EGB_str_remove_substr(strdup(resource_path), manager->resources_dir);
    extension = EGB_get_filename_ext(resource_path);
    if (filename == NULL || extension == NULL)
        return 1;
    while (*filename == '/')
        filename++;

    log_debug("resource_path : %s", resource_path);

    if (strcmp(extension, "png") == 0)
        resource = (void *)EGB_load_png_resource(resource_path);
    else if (strcmp(extension, "ttf") == 0)
        resource = (void *)EGB_load_ttf_resource(resource_path, EGB_DEFAULT_FONT_SIZE);
    else
        return 1;

    resource_entry = malloc(sizeof(resource_t));
    resource_entry->resource_path = filename;
    resource_entry->resource = resource;
    resource_entry->font_size = 0;
    if (strcmp(extension, "ttf") == 0)
        resource_entry->font_size = EGB_DEFAULT_FONT_SIZE;

    EGB_resources_manager(EGB_Manager_Add, resource_entry);
    return 0;
}


char            *EGB_get_filename_ext(char *filename)
{
    char        *dot;

    dot = strrchr(filename, '.');
    if(!dot || dot == filename) return NULL;
    return dot + 1;
}

char        *EGB_str_remove_substr(char *str, const char *sub) {
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
