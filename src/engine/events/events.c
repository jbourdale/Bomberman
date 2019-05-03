/*
** events.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "events.h"

/**
 * @brief      Handle SDL Events
 *
 * @return     return -1 if a QUIT Event has been triggered. This will stop the main engine loop. Return 0 overwise.
 */
int 			EGB_Event_Handle()
{
	SDL_Event 	e;

	if (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT) {
            return -1;
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN) {
            EGB_Event_HandleClick(e);
        }
        else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
            EGB_Event_HandleKeyStroke(e);
        }
    }

    return 0;
}

/**
 * @brief      Handle click event. Iterate over all the entities that have a click EGB_Component_Event and notify them if the click is on them
 *
 * @param  e     The SDL_Event to compute
 *
 * @return     status   The main loop execution status 
 *              <ul>
 *                  <li>0 = OK</li>
 *                  <li>1 = An error occured</li>
 *              </ul>
 */
int                         EGB_Event_HandleClick(SDL_Event e)
{
    EGB_Entity_Manager        *entities_manager;
    EGB_Entity_LinkedList_Element *manager_iterator;
    EGB_Entity                *entity;
    SDL_Rect                entity_rect;
    SDL_Point               click;
    EGB_Component_Position    *pos_comp;
    EGB_Component_Event       *event_comp;

    click.x = e.button.x;
    click.y = e.button.y;

    entities_manager = EGB_Observable_Event_Click(EGB_Manager_Retrieve);
    if (entities_manager == NULL)
        return 1;
    manager_iterator = entities_manager->first;
    while(manager_iterator != NULL)
    {
        entity = manager_iterator->entity;
        pos_comp = (EGB_Component_Position *)EGB_FindComponentByName(entity, "position_component");
        event_comp = (EGB_Component_Event *)EGB_FindComponentByName(entity, "event_click_component");
        EGB_Component_PositionToRect(pos_comp, &entity_rect);

        if (SDL_PointInRect(&click, &entity_rect) == SDL_TRUE) {
            event_comp->f(entity, e);
        }
        manager_iterator = manager_iterator->next;
    }
    return 0;
}


/**
 * @brief      Handle keyboard events. Iterate over all the entities that have a keystroke EGB_Component_Event and notify them
 *
 * @param  e   SDL_Event to handle
 *
 * @return     status   The main loop execution status 
 *              <ul>
 *                  <li>0 = OK</li>
 *                  <li>1 = An error occured</li>
 *              </ul>
 */
int                             EGB_Event_HandleKeyStroke(SDL_Event e)
{
    EGB_Entity_Manager            *entities_manager;
    EGB_Entity_LinkedList_Element     *manager_iterator;
    EGB_Entity                    *entity;
    EGB_Component_Event           *event_comp;
    
    entities_manager = EGB_Observable_Event_KeyStroke(EGB_Manager_Retrieve);
    if (entities_manager == NULL)
        return 1;
    manager_iterator = entities_manager->first;
    while(manager_iterator != NULL)
    {
        entity = manager_iterator->entity;
        event_comp = (EGB_Component_Event *)EGB_FindComponentByName(entity, "event_keystroke_component");
        event_comp->f(entity, e);
        manager_iterator = manager_iterator->next;
    }
    return 0;
}
