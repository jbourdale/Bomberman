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
        log_debug("adding entity (%p) to position manager", entity);
        if (entity == NULL)
            return NULL;
        log_debug("ENTITY ZINDEX : %d", entity_pos->z);

        entry = malloc(sizeof(entity_linked_list_el_t));
        entry->entity = entity;
        entry->next = NULL;
        entry->prev = NULL;
        log_debug("adding entry : %p", entry);

        if (manager == NULL) {
            log_debug("ADDING ENTRY (%p) AS FIRST ITEM", entry);
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
            log_debug("iterate over position manager (%p)", entity_iterator);
            log_debug("ACTUAL ENTITY ZINDEX : %d", ((position_component_t*)find_component_by_name(entity_iterator->entity, "position_component"))->z);
            entity_iterator = entity_iterator->next;
        }
        log_debug("entity_iterator after loop : %p", entity_iterator);

        if (((position_component_t*)find_component_by_name(entity_iterator->entity, "position_component"))->z > entity_pos->z) {
            log_debug("entity_iterator(%p)->z is bigger than entity->z", entity_iterator);
            entry->next = entity_iterator;
            log_debug("entry(%p)->next = %p", entry, entry->next);
            entity_iterator = entry;
            log_debug("entity_iterator = %p", entity_iterator);
            log_debug("manager->first = %p", manager->first);
            if (manager->first == entry->next)
                manager->first = entry;
        } else {
            entry->next = entity_iterator->next;
            entity_iterator->next = entry;
        }
        log_debug("entity_iterator (%p) -> next = %p", entity_iterator, entity_iterator->next);
        log_debug("manager (%p) -> first = %p", manager, manager->first);
        return NULL;
    }
    if (flags & EGB_Manager_Delete) {
        return NULL;
    }
    return NULL;
}