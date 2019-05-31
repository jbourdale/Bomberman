/*
** components.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "entities.h"


/**
 * @brief      Add component to an entity
 *
 * @param      entity     The entity
 * @param      component  The component
 *
 * @return     status   Return 0 if the entity successfuly destroy, overwise return 1
 */
int             EGB_Component_AddToEntity(EGB_Entity *entity, void *component)
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

    if (!entity->server_side)
        EGB_Observables_RegisterEntity(entity, (EGB_Component *)component);
    return 0;
}



/**
 * @brief      Add multiple components to an entity
 *
 * @param      entity      The entity
 * @param      components  The components. Must be array finishing by NULL
 *
 * @return     status   Return 0 if the entity successfuly destroy, overwise
 *             return 1
 */
int             EGB_Component_AddManyToEntity(EGB_Entity *entity, void **components)
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
    //free(comp);
    return 0;
}


/**
 * @brief      Observables are built to notify entity depending on their component.
 *             This register an entity to a specific observable on the component param.
 *
 * @param      entity     The entity
 * @param      component  The component
 *
 * @return     status   Return 0 if the entity successfuly destroy, overwise return 1
 */
int EGB_Observables_RegisterEntity(EGB_Entity *entity, EGB_Component *component)
{
    if (entity == NULL || component == NULL)
        return 1;

    if(strcmp(component->name, "position_component") == 0) {
        EGB_Observable_Position(EGB_Manager_Add, entity, (EGB_Component_Position *) component);
        return 0;
    }
    else if(strcmp(component->name, "event_keystroke_component") == 0) {
        EGB_Observable_Event_KeyStroke(EGB_Manager_Add, entity, (EGB_Component_Event *) component);
        return 0;
    }
    else if(strcmp(component->name, "event_click_component") == 0) {
        EGB_Observable_Event_Click(EGB_Manager_Add, entity, (EGB_Component_Event *) component);
        return 0;
    }
    else if(strcmp(component->name, "event_hover_component") == 0) {
        EGB_Observable_Event_Hover(EGB_Manager_Add, entity, (EGB_Component_Event *) component);
        return 0;
    }
    else if (strcmp(component->name, "collision_component") == 0) {
        EGB_Manager_Collision(EGB_Manager_Add, entity, (EGB_Component_Collision *) component);
    }
    return 1;
}


int EGB_Entity_ReplaceComponent(EGB_Entity *entity, EGB_Component *component)
{
    void        **tmp_comp;
    int         nb_comp;

    if (component == NULL || entity == NULL)
        return 1;

    tmp_comp = entity->components;
    if (entity->components == NULL)
        return 1;
    nb_comp = 0;
    while(*tmp_comp != NULL) {
        EGB_Component *comp = (*tmp_comp);
        if (comp == NULL)
            continue;
        if (strcmp(comp->name, component->name) == 0) {
            break;
        }
        tmp_comp++;
        nb_comp++;
    }

    // EGB_Component *comp = entity->components[nb_comp];
    entity->components[nb_comp] = component;

    return 0;
}
