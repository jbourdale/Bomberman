/*
** keystroke.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "keystroke.h"

event_component_t       *create_event_keystroke_component(void(*f))
{
    event_component_t   *component;

    component = malloc(sizeof(event_component_t));
    component->name = strdup("event_keystroke_component");
    component->f = f;
    return component;
}

int                         destroy_event_keystroke_component(entity_t *entity)
{
    event_component_t    *comp;

    comp = (event_component_t *)find_component_by_name(entity, "event_keystroke_component");
    if (comp == NULL)
        return 1;

    free(comp->name);
    free(comp);
    return 0;
}

entity_manager_t                            *event_keystroke_manager(Uint32 flags, ...)
{
    static entity_manager_t                 *manager;
    entity_linked_list_el_t                 *entity_iterator, *entry;
    entity_t                                *entity;
    va_list                                 argp;


    log_debug("event_keystroke_manager");

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
        log_debug("will add entry (%p) to keystroke manager(%p)", entry, manager);

        if (manager == NULL) {
            manager = malloc(sizeof(entity_manager_t));
            manager->first = entry;
            log_debug("create keystroke manager : %p", manager);
            return NULL;
        }
        // Add entry to manager
        entity_iterator = manager->first;
        while (entity_iterator->next != NULL)
            entity_iterator = entity_iterator->next;
        log_debug("add entry(%p) to %p", entry, entity_iterator);
        entity_iterator->next = entry;
        return NULL;
    }
    if (flags & EGB_Manager_Delete) {
        return NULL;
    }
    return NULL;
}