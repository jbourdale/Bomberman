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
    SDL_Renderer            *renderer;
    entity_manager_t        *entities_manager;
    entity_linked_list_el_t *manager_iterator;
    entity_t                *entity;
    SDL_Rect                entity_rect;
    SDL_Point               clic;
    position_component_t    *comp;


    renderer = get_current_renderer();
    clic.x = e.button.x;
    clic.y = e.button.y;

    entities_manager = entitys_manager(EGB_Manager_Retrieve);
    manager_iterator = entities_manager->first;
    while(manager_iterator != NULL)
    {
        entity = manager_iterator->entity;
        comp = (position_component_t *)find_component_by_name(entity, "position_component");
        position_component_to_rect(comp, &entity_rect);

        if (entity->on_click != NULL && SDL_PointInRect(&clic, &entity_rect) == SDL_TRUE) {
            entity->on_click(renderer, entity, e);
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
    
    entities_manager = entitys_manager(EGB_Manager_Retrieve);
    manager_iterator = entities_manager->first;
    while(manager_iterator != NULL)
    {
        entity = manager_iterator->entity;
        if(entity->on_key_stroke != NULL)
        {
            entity->on_key_stroke(entity, e);
        }
        manager_iterator = manager_iterator->next;
    }
    return 0;
}
