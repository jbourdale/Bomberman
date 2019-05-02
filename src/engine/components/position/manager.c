/*
** manager.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "position.h"

entity_manager_t                            *entities_position_manager(Uint32 flags, ...)
{
    static entity_manager_t                 *manager;
    entity_linked_list_el_t                 *entity_iterator, *entry;
    entity_t                                *entity;
    position_component_t                    *entity_pos; 
    va_list                                 argp;


    if (flags & EGB_Manager_Retrieve)
        return manager;
    if (flags & EGB_Manager_Add)
    {
        va_start(argp, flags);
        entity = va_arg(argp, entity_t*);
        entity_pos = va_arg(argp, position_component_t*);
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
        while (
            entity_iterator->next != NULL && 
            ((position_component_t*)find_component_by_name(entity_iterator->next->entity, "position_component"))->z <= entity_pos->z
        ) {
            entity_iterator = entity_iterator->next;
        }

        if (((position_component_t*)find_component_by_name(entity_iterator->entity, "position_component"))->z > entity_pos->z) {
            entry->next = entity_iterator;
            entity_iterator = entry;
            if (manager->first == entry->next)
                manager->first = entry;
        } else {
            entry->next = entity_iterator->next;
            entity_iterator->next = entry;
        }
        return NULL;
    }
    if (flags & EGB_Manager_Delete) {
        return NULL;
    }
    return NULL;
}