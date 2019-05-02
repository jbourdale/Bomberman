/*
** components.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "entities.h"

int             EGB_Component_AddToEntity(entity_t *entity, void *component)
{
    void        **tmp_comp;
    int         nb_comp;

    if (component == NULL)
    {
        log_debug("no component specified, aborting");
        return 1;
    }

    tmp_comp = entity->components;
    nb_comp = 0;
    while(tmp_comp != NULL && *tmp_comp++)
        nb_comp++;

    entity->components = realloc(entity->components, (nb_comp + 2) * sizeof(void *));
    entity->components[nb_comp] = component;
    entity->components[nb_comp + 1] = NULL;
    EGB_Observables_RegisterEntity(entity, (component_t *)component);
    return 0;
}



int             EGB_Component_AddManyToEntity(entity_t *entity, void **components)
{
    void        **comp;

    comp = components;
    while (*comp++)
    {
        if(EGB_Component_AddToEntity(entity, *comp))
        {
            EGB_Entity_Destroy(entity);
            return 1;
        }
    }
    free(comp);
    return 0;
}


int EGB_Observables_RegisterEntity(entity_t *entity, component_t *component)
{
    if(strcmp(component->name, "position_component") == 0) {
        EGB_Observable_Position(EGB_Manager_Add, entity, (position_component_t *) component);
        return 0;
    }
    else if(strcmp(component->name, "event_keystroke_component") == 0) {
        EGB_Observable_Event_KeyStroke(EGB_Manager_Add, entity, (event_component_t *) component);
        return 0;
    }
    else if(strcmp(component->name, "event_click_component") == 0) {
        EGB_Observable_Event_Click(EGB_Manager_Add, entity, (event_component_t *) component);
        return 0;
    }
    else if(strcmp(component->name, "event_hover_component") == 0) {
        EGB_Observable_Event_Hover(EGB_Manager_Add, entity, (event_component_t *) component);
        return 0;
    }
    return 1;
}