#include "engine/engine.h"

/**
 * MARIO HANDLER CLICK
 */
void on_mario_click(entity_t *entity, SDL_Event e)
{
    log_debug("on click on : %s", entity->name);
    log_debug("e : %p", &e);
    set_framerate(30);
}

void on_mario_keystroke(entity_t *entity, SDL_Event e) {
    position_component_t    *pos_comp;
    const Uint8             *key_state = SDL_GetKeyboardState(NULL);

    log_debug("on mario keystroke");


    key_state = SDL_GetKeyboardState(NULL);
    pos_comp = (position_component_t*)find_component_by_name(entity, "position_component");
    if (e.type == SDL_KEYUP)
    {
        return ;
    }

    if(key_state[SDL_SCANCODE_LEFT])
    {
        move_position_component_left(pos_comp, 10);
    }
    if (key_state[SDL_SCANCODE_RIGHT])
    {
        move_position_component_right(pos_comp, 10);
    }
    if (key_state[SDL_SCANCODE_UP])
    {
        move_position_component_up(pos_comp, 10);
    }
    if (key_state[SDL_SCANCODE_DOWN])
    {
        move_position_component_down(pos_comp, 10);
    }
    if (key_state[SDL_SCANCODE_SPACE])
    {
        entity_t *player = create_entity("player");
        position_component_t *pos_comp2 = create_position_component(pos_comp->x, pos_comp->y, 50, 50);
        log_debug("create animation_comp");
        animation_component_t *animation_comp = create_animation_component("./resources/bomb.png", 0, 24, 24, 0);
        log_debug("add keyframe");
        add_animation_keyframe(animation_comp, 400, 0, 0);
        log_debug("add keyframe");
        add_animation_keyframe(animation_comp, 400, 1, 0);
        log_debug("add keyframe");
        add_animation_keyframe(animation_comp, 400, 2, 0);
        log_debug("add keyframe");
        add_animation_keyframe(animation_comp, 400, 1, 0);
        log_debug("add keyframe");
        add_animation_keyframe(animation_comp, 400, 2, 0);
        log_debug("add keyframe");
        add_animation_keyframe(animation_comp, 200, 3, 0);
        log_debug("add keyframe");
        add_animation_keyframe(animation_comp, 200, 0, 4);
        log_debug("add keyframe");
        add_animation_keyframe(animation_comp, 200, 0, 3);
        log_debug("add keyframe");
        add_animation_keyframe(animation_comp, 200, 0, 2);
        log_debug("add keyframe");
        add_animation_keyframe(animation_comp, 200, 0, 1);
        log_debug("add keyframe");

        add_component_to_entity(player, (void *)pos_comp2);
        add_component_to_entity(player, (void *)animation_comp);

        log_debug("start_entity_animation");
        start_entity_animation(player, 0);
        log_debug("bomb created");
    }
}

int main() {
    position_component_t *pos_comp;
    texture_component_t *texture_comp;

    log_info("### Starting Bomberman");

    // INIT ENGINE
    start_engine();

    entity_t *mario = create_entity("mario");
    mario->on_key_stroke = on_mario_keystroke;
    pos_comp = create_position_component(0, 0, 200, 200);
    texture_comp = create_texture_component("./resources/Mario.png");
    add_component_to_entity(mario, (void *)pos_comp);
    add_component_to_entity(mario, (void *)texture_comp);

    set_framerate(50);
    run_engine();

    // STOPING ENGINE
    stop_engine();
}
