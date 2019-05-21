/*
** hover.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "hover.h"

/**
 * @brief      Create a Event mouse hover component
 *
 * @note       Allow callback to be bind on the entity
 *
 * @param      f     callback
 *
 * @return     Event mouse hover component created
 */
EGB_Component_Event       *EGB_Component_CreateEventHover(void(*f))
{
    EGB_Component_Event   *component;

    component = malloc(sizeof(EGB_Component_Event));
    component->name = strdup("event_hover_component");
    component->f = f;
    return component;
}

/**
 * @brief      Destroy the Event Mouse hover component from entity
 *
 * @param      entity  The entity
 *
 * @return     status
 *              <ul>
 *                  <li>0 = Component successfuly destroy</li>
 *                  <li>1 = An error occured</li>
 *              </ul>
 */
int                         EGB_Component_DestroyEventHover(EGB_Entity *entity)
{
    EGB_Component_Event       *comp;

    comp = (EGB_Component_Event *)EGB_FindComponentByName(entity, "event_hover_component");
    if (comp == NULL)
        return 1;

    //free(comp->name);
    //free(comp);
    return 0;
}

/**
 * @brief      Event hover manager. Store entity that subscribe to an event hover
 *
 * @param      flags      The flags
 * @param      entity[optional]  The entity to add. Require flag EGB_Manager_Add
 *
 * @note Availible flag :
 *  <ul>
 *      <li>EGB_Manager_Retrieve</li>
 *      <li>EGB_Manager_Add</li>
 *      <li>EGB_Manager_Delete</li>
 *  </ul>
 *
 * @return     if flag EGB_Manager_Retrieve is sent, return the manager. Overwise, return NULL
 */
EGB_Entity_Manager                            *EGB_Observable_Event_Hover(Uint32 flags, ...)
{
    static EGB_Entity_Manager                 *manager;
    EGB_Entity_Manager_Element                *entity_iterator, *entity_iterator_prev, *entry;
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
        while (entity_iterator->next != NULL)
            entity_iterator = entity_iterator->next;
        entity_iterator->next = entry;
        return NULL;
    }
    if (flags & EGB_Manager_Delete) {
        log_debug("Deleting from hover manager");
        va_start(argp, flags);
        entity = va_arg(argp, EGB_Entity*);
        va_end(argp);
        if (entity == NULL || manager == NULL)
            return NULL;

        log_debug("Deleting(%p) from hover manager", entity);

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
