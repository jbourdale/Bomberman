/*
** manager.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "manager.h"

/**
 * @brief      Store the list of entity server side
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
EGB_Entity_Manager              *EGBS_Manager_Entity(Uint32 flags, ...)
{
    static EGB_Entity_Manager   *manager;
    EGB_Entity_Manager_Element  *entity_iterator, *entry, *entity_iterator_prev;
    EGB_Entity                  *entity;
    va_list                     argp;


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
        while (entity_iterator->next != NULL) {
            entity_iterator = entity_iterator->next;
        }
        entity_iterator->next = entry;
        return NULL;
    }
    if (flags & EGB_Manager_Delete) {
        va_start(argp, flags);
        entity = va_arg(argp, EGB_Entity*);
        va_end(argp);
        if (entity == NULL || manager == NULL)
            return NULL;


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
        return NULL;
    }
    return NULL;
}

EGB_Entity                        **EGBS_Entity_FindByName(char *name)
{
    EGB_Entity                    **founded;
    int                           nb_founded;
    EGB_Entity_Manager            *manager;
    EGB_Entity_Manager_Element    *manager_entry;

    manager = EGBS_Manager_Entity(EGB_Manager_Retrieve);
    if (manager == NULL)
        return NULL;
    manager_entry = manager->first;

    nb_founded = 0;
    founded = NULL;
    while(manager_entry != NULL)
    {
        if (strcmp(manager_entry->entity->name, name) == 0) {
            founded = realloc(founded, (nb_founded + 2) * sizeof(void *));
            founded[nb_founded] = manager_entry->entity;
            founded[nb_founded + 1] = NULL;
            nb_founded++;
        }
        manager_entry = manager_entry->next;
    }
    return founded;
}


EGB_Entity *EGBS_FindEntityByPosition(int x, int y, int z)
{
    EGB_Entity                  *entity;
    EGB_Entity_Manager          *entities_manager;
    EGB_Entity_Manager_Element  *manager_iterator;
    EGB_Component_Position      *position_comp;

    entities_manager = EGBS_Manager_Entity(EGB_Manager_Retrieve);
    if (entities_manager == NULL)
        return NULL;
    manager_iterator = entities_manager->first;
    while (manager_iterator != NULL)
    {
        entity = manager_iterator->entity;
        position_comp = EGB_FindComponentByName(
            entity,
            "position_component"
        );
        if (position_comp->x == x
            && position_comp->y == y
            && position_comp->z == z)
            return entity;
        manager_iterator = manager_iterator->next;
    }
    return NULL;
}
