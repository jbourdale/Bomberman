/*
** resources.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "./resources.h"

EGB_Resource_List            *EGB_ResourcesManager(Uint32 flags, ...)
{
    static EGB_Resource_List *manager = NULL;
    EGB_Resource              *resources_iterator, *entry;
    char                    *resources_dir;
    va_list                 argp;

    if (manager == NULL) {
        manager = malloc(sizeof(EGB_Entity_Manager));
        manager->first = NULL;
        manager->resources_dir = NULL;
    }

    if (flags & EGB_Manager_Retrieve)
        return manager;
    if (flags & EGB_Resources_Manager_Set_Dir) {
        if (manager->resources_dir != NULL)
            return NULL;

        va_start(argp, flags);
        resources_dir = va_arg(argp, char*);
        manager->resources_dir = resources_dir;
        va_end(argp);
    }
    if (flags & EGB_Manager_Add)
    {
        va_start(argp, flags);
        entry = va_arg(argp, EGB_Resource*);
        va_end(argp);
        if (entry == NULL ||
            entry->resource == NULL ||
            entry->resource_path == NULL ||
            manager->resources_dir == NULL
        )
            return NULL;


        entry->next = NULL;
        // Add entry to manager
        resources_iterator = manager->first;
        if (resources_iterator == NULL)
            manager->first = entry;
        else {
            while (resources_iterator->next != NULL)
                resources_iterator = resources_iterator->next;
            resources_iterator->next = entry;
        }
        return NULL;
    }
    if (flags & EGB_Manager_Delete) {
        return NULL;
    }
    return NULL;
}
