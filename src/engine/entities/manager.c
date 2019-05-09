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
    EGB_Entity_Manager_Element                 *entity_iterator, *entry;
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
        }
        entity_iterator->next = entry;
        return NULL;
    }
    if (flags & EGB_Manager_Delete) {
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
