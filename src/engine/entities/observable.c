/*
** manager.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "entities.h"

entity_manager_t                            *EGB_Observable_Entity(Uint32 flags, ...)
{
    static entity_manager_t                 *manager;
    entity_linked_list_el_t                 *entity_iterator, *entry;
    entity_t                                *entity;
    va_list                                 argp;


    if (flags & EGB_Manager_Retrieve)
        return manager;
    if (flags & EGB_Manager_Add)
    {
        va_start(argp, flags);
        entity = va_arg(argp, entity_t*);
        va_end(argp);
        if (entity == NULL)
            return NULL;

        entry = malloc(sizeof(entity_linked_list_el_t));
        entry->entity = entity;
        entry->next = NULL;

        if (manager == NULL) {
            manager = malloc(sizeof(entity_manager_t));
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

entity_t                        *EGB_Entity_FindFirstByName(char *name)
{
    entity_manager_t            *manager;
    entity_linked_list_el_t     *manager_entry;

    manager = EGB_Observable_Entity(EGB_Manager_Retrieve);
    manager_entry = manager->first;
    while(manager_entry != NULL && manager_entry->next != NULL)
    {
        if (strcmp(manager_entry->entity->name, name) == 0)
            return manager_entry->entity;
    }
    return NULL;
}
