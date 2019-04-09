#include "engine/engine.h"

void on_mario_click(entity_t *entity, SDL_Event e)
{
    log_debug("on click on : %s", entity->name);
    log_debug("e : %p", &e);
}

void on_mario_keystroke(entity_t *entity, SDL_Event e)
{
    log_debug("on keystroke on : %s", entity->name);
    log_debug("e : %p", &e);
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

    entity_t *entity = create_entity(renderer, "mario", "./resources/Mario.png");
    entity->on_click = on_mario_click;
    pos_comp = create_position_component(0, 0, 200, 200);
    add_component_to_entity(entity, (void *)pos_comp);

    log_debug("sprites[0] is NULL ? %d", entity->sprites[0] == NULL);
    log_debug("sprites[0] : %p", entity->sprites[0]);

    run_engine(renderer);

    // STOPING ENGINE
    stop_engine(window, renderer);
}
