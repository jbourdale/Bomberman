/*
** click.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "click.h"

/**
 * @brief      Create a Event click component
 *
 * @note       Allow callback to be bind on the entity
 *
 * @param      f     callback
 *
 * @return     Event click component created
 */
EGB_Component_Event       *EGB_Component_CreateEventClick(void(*f))
{
    EGB_Component_Event   *component;

    component = malloc(sizeof(EGB_Component_Event));
    component->name = strdup("event_click_component");
    component->f = f;
    return component;
}

/**
 * @brief      Destroy the Event Click component from entity
 *
 * @param      entity  The entity
 *
 * @return     status
 *              <ul>
 *                  <li>0 = Component successfuly destroy</li>
 *                  <li>1 = An error occured</li>
 *              </ul>
 */
int                         EGB_Component_DestroyEventClick(EGB_Entity *entity)
{
    EGB_Component_Event       *comp;

    comp = (EGB_Component_Event *)EGB_FindComponentByName(entity, "event_click_component");
    if (comp == NULL)
        return 1;

    //free(comp->name);
    //free(comp);
    return 0;
}

/**
 * @brief      Event click manager. Store entity that subscribe to an event click
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
EGB_Entity_Manager                            *EGB_Observable_Event_Click(Uint32 flags, ...)
{
    static EGB_Entity_Manager                 *manager;
    EGB_Entity_Manager_Element             *entity_iterator, *entry;
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
        return NULL;
    }
    return NULL;
}
