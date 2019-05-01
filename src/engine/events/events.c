/*
** events.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "events.h"

int 			handle_events()
{
	SDL_Event 	e;

	if (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT) {
            return -1;
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN) {
            handle_entitys_click(e);
        }
        else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
            handle_entity_key_events(e);
        }
    }

    return 0;
}

int                         handle_entitys_click(SDL_Event e)
{
    entity_manager_t        *entities_manager;
    entity_linked_list_el_t *manager_iterator;
    entity_t                *entity;
    SDL_Rect                entity_rect;
    SDL_Point               click;
    position_component_t    *pos_comp;
    event_component_t       *event_comp;

    click.x = e.button.x;
    click.y = e.button.y;

    entities_manager = event_click_manager(EGB_Manager_Retrieve);
    if (entities_manager == NULL)
        return 1;
    manager_iterator = entities_manager->first;
    while(manager_iterator != NULL)
    {
        entity = manager_iterator->entity;
        pos_comp = (position_component_t *)find_component_by_name(entity, "position_component");
        event_comp = (event_component_t *)find_component_by_name(entity, "event_click_component");
        position_component_to_rect(pos_comp, &entity_rect);

        if (SDL_PointInRect(&click, &entity_rect) == SDL_TRUE) {
            event_comp->f(entity, e);
        }
        manager_iterator = manager_iterator->next;
    }
    return 0;
}


int                             handle_entity_key_events(SDL_Event e)
{
    entity_manager_t            *entities_manager;
    entity_linked_list_el_t     *manager_iterator;
    entity_t                    *entity;
    event_component_t           *event_comp;
    
    entities_manager = event_keystroke_manager(EGB_Manager_Retrieve);
    if (entities_manager == NULL)
        return 1;
    manager_iterator = entities_manager->first;
    while(manager_iterator != NULL)
    {
        entity = manager_iterator->entity;
        event_comp = (event_component_t *)find_component_by_name(entity, "event_keystroke_component");
        event_comp->f(entity, e);
        manager_iterator = manager_iterator->next;
    }
    return 0;
}
