#include "engine/engine.h"

void on_mario_click(entity_t *entity, SDL_Event e)
{
    log_debug("on click on : %s", entity->name);
    log_debug("e : %p", &e);
}

void on_mario_keystroke(entity_t *entity, SDL_Event e)
{
    log_debug("on mario keystroke, animated : %d", entity->animate);
    position_component_t *pos_comp;

    pos_comp = (position_component_t*)find_component_by_name(entity, "position_component");
    if (e.type == SDL_KEYUP)
    {
        log_debug("RELACHÉ");
        disable_entity_animation(entity);
        return ;
    }
    if(e.key.keysym.sym == SDLK_LEFT)
    {
        if (!entity->animate)
        {
            enable_entity_animation(entity);
        }
        move_position_component_left(pos_comp, 10);
    }
    else if (e.key.keysym.sym == SDLK_RIGHT)
    {
        if (!entity->animate)
        {
            enable_entity_animation(entity);
        }
        move_position_component_right(pos_comp, 10);
    }
    else if (e.key.keysym.sym == SDLK_UP)
    {
        if (!entity->animate)
        {
            enable_entity_animation(entity);
        }
        move_position_component_up(pos_comp, 10);
    }
    else if (e.key.keysym.sym == SDLK_DOWN)
    {
        if (!entity->animate)
        {
            enable_entity_animation(entity);
        }
        move_position_component_down(pos_comp, 10);
    }
}

int main() {
    SDL_Window *window;
    SDL_Renderer *renderer;
    position_component_t *pos_comp;

    log_info("### Starting Bomberman");

    // INIT ENGINE
    window = NULL;
    renderer = NULL;
    start_engine(&window, &renderer);



    char **array = malloc(2 * sizeof(char *));
    array[0] = "./resources/Mario.png";
    array[1] = "./resources/Mario2.png";

    entity_t *entity = create_animated_entity(renderer, "mario", array, 2);
    entity->on_click = on_mario_click;
    entity->on_key_stroke = on_mario_keystroke;
    pos_comp = create_position_component(0, 0, 200, 200);
    add_component_to_entity(entity, (void *)pos_comp);

    log_debug("sprites[0] is NULL ? %d", entity->sprites[0] == NULL);
    log_debug("sprites[0] : %p", entity->sprites[0]);


    run_engine(renderer);

    // STOPING ENGINE
    stop_engine(window, renderer);
}
