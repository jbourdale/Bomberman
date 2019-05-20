/*
** manager.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "entities.h"

/**
 * @brief      Store the list of entity to notify them
 *
 * @param  flags      The flags
 * @param  entity[optional]  The entity to add. Require flag EGB_Manager_Add
 *
 * @note Availible flag :
 *  <ul>
 *      <li>EGB_Manager_Retrieve</li>
 *      <li>EGB_Manager_Add</li>
 *      <li>EGB_Manager_Delete</li>
 *  </ul>
 * @return     if flag EGB_Manager_Retrieve is sent, return the manager. Overwise, return NULL
 */
EGB_Entity_Manager                            *EGB_Manager_Entity(Uint32 flags, ...)
{
    static EGB_Entity_Manager                 *manager;
    EGB_Entity_Manager_Element                *entity_iterator, *entry, *entity_iterator_prev;
    EGB_Entity                                *entity;
    va_list                                   argp;


    if (flags & EGB_Manager_Retrieve)
        return manager;
    if (flags & EGB_Manager_Add)
    {
        va_start(argp, flags);
        entity = va_arg(argp, EGB_Entity*);
        va_end(argp);
        if (entity == NULL) {
            return NULL;
        }
        log_debug("Adding entity %s (%p) to manager", entity->name, entity);

        entry = malloc(sizeof(EGB_Entity_Manager_Element));
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
            log_debug("iterator over manager");
        }
        log_debug("adding it to manager");
        entity_iterator->next = entry;
        return NULL;
    }
    if (flags & EGB_Manager_Delete) {
        log_debug("Deleting from manager");
        va_start(argp, flags);
        entity = va_arg(argp, EGB_Entity*);
        va_end(argp);
        if (entity == NULL || manager == NULL)
            return NULL;

        log_debug("Deleting(%p) from manager", entity);

        entity_iterator_prev = NULL;
        entity_iterator = manager->first;
        while (entity_iterator != NULL && entity_iterator->entity != entity) {
            log_debug("entity_iterator entity (%s) : %p", entity_iterator->entity->name, entity_iterator->entity);
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
        return NULL;
    }
    return NULL;
}

/**
 * @brief      Return the first added entity with the name
 *
 * @param      name  The entity name to search for
 *
 * @return     entity pointer on the entity founded. NULL if not found.
 */
EGB_Entity                        *EGB_Entity_FindFirstByName(char *name)
{
    EGB_Entity_Manager            *manager;
    EGB_Entity_Manager_Element     *manager_entry;

    manager = EGB_Manager_Entity(EGB_Manager_Retrieve);
    if (manager == NULL)
        return NULL;
    manager_entry = manager->first;
    while(manager_entry != NULL)
    {
        if (strcmp(manager_entry->entity->name, name) == 0)
            return manager_entry->entity;
        manager_entry = manager_entry->next;
    }
    return NULL;
}
