/*
** manager.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "position.h"

void        EGB_Debug_DisplayPositionManager() {
    EGB_Entity_Manager *manager;
    EGB_Entity_Manager_Element *iterator;

    log_debug("########## Manager");
    manager = EGB_Observable_Position(EGB_Manager_Retrieve);
    if (manager == NULL || manager->first == NULL) {
        log_debug("Manager not initialized");
        return ;
    }
    iterator = manager->first;
    while(iterator != NULL) {
        log_debug("Entity %s (%p)", iterator->entity->name, iterator->entity);
        iterator = iterator->next;
    }
    log_debug("##########");
}


EGB_Entity_Manager                            *EGB_Observable_Position(Uint32 flags, ...)
{
    static EGB_Entity_Manager                 *manager;
    EGB_Entity_Manager_Element                *entity_iterator, *entity_iterator_prev, *entry;
    EGB_Entity                                *entity;
    EGB_Component_Position                    *entity_pos;
    va_list                                 argp;


    if (flags & EGB_Manager_Retrieve)
        return manager;
    if (flags & EGB_Manager_Add)
    {
        va_start(argp, flags);
        entity = va_arg(argp, EGB_Entity*);
        entity_pos = va_arg(argp, EGB_Component_Position*);
        va_end(argp);
        if (entity == NULL)
            return NULL;

        entry = malloc(sizeof(EGB_Entity_Manager_Element));
        entry->entity = entity;
        entry->next = NULL;

        if (manager == NULL) {
            manager = malloc(sizeof(EGB_Entity_Manager));
            manager->first = entry;
            return NULL;
        }
        if (manager->first == NULL) {
            manager->first = entry;
            return NULL;
        }
        // Add entry to manager
        entity_iterator = manager->first;
        while (
            entity_iterator->next != NULL &&
            ((EGB_Component_Position*)EGB_FindComponentByName(
                entity_iterator->next->entity, "position_component")
            )->z <= entity_pos->z
        ) {
            entity_iterator = entity_iterator->next;
        }

        if (((EGB_Component_Position*)EGB_FindComponentByName(
                entity_iterator->entity, "position_component"
            ))->z > entity_pos->z
        ) {
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
        log_debug("Deleting from position manager");
        EGB_Debug_DisplayPositionManager();
        va_start(argp, flags);
        entity = va_arg(argp, EGB_Entity*);
        va_end(argp);
        if (entity == NULL || manager == NULL)
            return NULL;

        log_debug("Deleting(%p) from position manager", entity);

        entity_iterator_prev = NULL;
        entity_iterator = manager->first;
        while (entity_iterator != NULL && entity_iterator->entity != entity) {
            entity_iterator_prev = entity_iterator;
            entity_iterator = entity_iterator->next;
        }
        if (entity_iterator == NULL)
            return NULL;
        if (entity_iterator_prev == NULL) {
            manager->first = entity_iterator->next;
        }
        else {
            entity_iterator_prev->next = entity_iterator->next;
        }
        EGB_Debug_DisplayPositionManager();
        return NULL;
    }
    return NULL;
}
