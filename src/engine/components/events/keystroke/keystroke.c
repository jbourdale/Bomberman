/*
** keystroke.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "keystroke.h"

EGB_Component_Event       *EGB_Component_CreateEventKeyStroke(void(*f))
{
    EGB_Component_Event   *component;

    component = malloc(sizeof(EGB_Component_Event));
    component->name = strdup("event_keystroke_component");
    component->f = f;
    return component;
}

int                         EGB_Component_DestroyEventKeyStroke(EGB_Entity *entity)
{
    EGB_Component_Event    *comp;

    comp = (EGB_Component_Event *)EGB_FindComponentByName(entity, "event_keystroke_component");
    if (comp == NULL)
        return 1;

    free(comp->name);
    free(comp);
    return 0;
}

EGB_Entity_Manager                            *EGB_Observable_Event_KeyStroke(Uint32 flags, ...)
{
    static EGB_Entity_Manager                 *manager;
    EGB_Entity_LinkedList_Element                 *entity_iterator, *entry;
    EGB_Entity                                *entity;
    va_list                                 argp;


    log_debug("event_keystroke_manager");

    if (flags & EGB_Manager_Retrieve)
        return manager;
    if (flags & EGB_Manager_Add)
    {
        va_start(argp, flags);
        entity = va_arg(argp, EGB_Entity*);
        va_end(argp);
        if (entity == NULL)
            return NULL;

        entry = malloc(sizeof(EGB_Entity_LinkedList_Element));
        entry->entity = entity;
        entry->next = NULL;
        log_debug("will add entry (%p) to keystroke manager(%p)", entry, manager);

        if (manager == NULL) {
            manager = malloc(sizeof(EGB_Entity_Manager));
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