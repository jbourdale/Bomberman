/*
** click.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "click.h"

event_component_t       *create_event_click_component(void(*f))
{
    event_component_t   *component;

    component = malloc(sizeof(event_component_t));
    component->name = strdup("event_click_component");
    component->f = f;
    return component;
}

int                         destroy_event_click_component(entity_t *entity)
{
    event_component_t       *comp;

    comp = (event_component_t *)find_component_by_name(entity, "event_click_component");
    if (comp == NULL)
        return 1;

    free(comp->name);
    free(comp);
    return 0;
}

entity_manager_t                            *event_click_manager(Uint32 flags, ...)
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