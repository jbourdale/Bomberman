/*
** manager.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "position.h"

EGB_Entity_Manager                            *EGB_Observable_Position(Uint32 flags, ...)
{
    static EGB_Entity_Manager                 *manager;
    EGB_Entity_LinkedList_Element                 *entity_iterator, *entry;
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
        while (
            entity_iterator->next != NULL && 
            ((EGB_Component_Position*)EGB_FindComponentByName(entity_iterator->next->entity, "position_component"))->z <= entity_pos->z
        ) {
            entity_iterator = entity_iterator->next;
        }

        if (((EGB_Component_Position*)EGB_FindComponentByName(entity_iterator->entity, "position_component"))->z > entity_pos->z) {
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