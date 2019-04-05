#include "engine/engine.h"

int main() {
    SDL_Window *window;
    SDL_Renderer *renderer;
    position_component_t *pos_comp;

    log_info("### Starting Bomberman");

    // INIT ENGINE
    window = NULL;
    renderer = NULL;
    start_engine(&window, &renderer);

    entity_t *entity = create_entity(renderer, "mario", "./resources/mario.png");
    pos_comp = create_position_component(0, 0, 200, 200);
    add_component_to_entity(entity, (void *)pos_comp);

    log_debug("sprites[0] is NULL ? %d", entity->sprites[0] == NULL);
    log_debug("sprites[0] : %p", entity->sprites[0]);

    run_engine(renderer);

    // STOPING ENGINE
    stop_engine(window, renderer);
}
