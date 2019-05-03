/*
** manager.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "entities.h"

EGB_Entity_Manager                            *EGB_Observable_Entity(Uint32 flags, ...)
{
    static EGB_Entity_Manager                 *manager;
    EGB_Entity_LinkedList_Element                 *entity_iterator, *entry;
    EGB_Entity                                *entity;
    va_list                                 argp;


    if (flags & EGB_Manager_Retrieve)
        return manager;
    if (flags & EGB_Manager_Add)
    {
        va_start(argp, flags);
        entity = va_arg(argp, EGB_Entity*);
        va_end(argp);
        if (entity == NULL)
            return NULL;

        entry = malloc(sizeof(EGB_Entity_LinkedList_Element));
        entry->entity = entity;
        entry->next = NULL;

        if (manager == NULL) {
            manager = malloc(sizeof(EGB_Entity_Manager));
            manager->first = entry;
            return NULL;
        }
        // Add entry to manager
        entity_iterator = manager->first;
        while (entity_iterator->next != NULL) {
            entity_iterator = entity_iterator->next;
        }
        entity_iterator->next = entry;
        return NULL;
    }
    if (flags & EGB_Manager_Delete) {
        return NULL;
    }
    return NULL;
}

EGB_Entity                        *EGB_Entity_FindFirstByName(char *name)
{
    EGB_Entity_Manager            *manager;
    EGB_Entity_LinkedList_Element     *manager_entry;

    manager = EGB_Observable_Entity(EGB_Manager_Retrieve);
    manager_entry = manager->first;
    while(manager_entry != NULL && manager_entry->next != NULL)
    {
        if (strcmp(manager_entry->entity->name, name) == 0)
            return manager_entry->entity;
    }
    return NULL;
}
