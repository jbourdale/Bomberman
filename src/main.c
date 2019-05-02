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

void on_explosion(entity_t *entity) {
    log_debug("BOMB EXPLOSED : %s", entity->name);
}
void on_start(entity_t *entity) {
    log_debug("BOMB PLACED : %s", entity->name);
}

void on_mario_keystroke(entity_t *entity, SDL_Event e) {
    position_component_t    *pos_comp;
    const Uint8             *key_state = SDL_GetKeyboardState(NULL);

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
        entity_t *player = create_entity("bomb");
        position_component_t *pos_comp2 = create_position_component(pos_comp->x, pos_comp->y, EGB_Position_Background, 50, 50);
        animation_component_t *animation_comp = create_animation_component("./resources/bomb.png", 0, 24, 24, 0);
        int start_keyframe = add_animation_keyframe(animation_comp, 400, 0, 0);
        add_keyframe_on_start_event(animation_comp, start_keyframe, on_start);
        add_animation_keyframe(animation_comp, 400, 1, 0);
        add_animation_keyframe(animation_comp, 400, 2, 0);
        add_animation_keyframe(animation_comp, 400, 1, 0);
        add_animation_keyframe(animation_comp, 400, 2, 0);
        add_animation_keyframe(animation_comp, 200, 3, 0);
        add_animation_keyframe(animation_comp, 200, 0, 4);
        add_animation_keyframe(animation_comp, 200, 0, 3);
        add_animation_keyframe(animation_comp, 200, 0, 2);
        int keyframe_id = add_animation_keyframe(animation_comp, 200, 0, 1);
        add_keyframe_on_finish_event(animation_comp, keyframe_id, on_explosion);

        animation_component_t *animation_comp2 = create_animation_component("./resources/bomb.png", 1, 24, 24, 0);
        add_animation_keyframe(animation_comp2, 1000, 5, 2);
        add_animation_keyframe(animation_comp2, 1000, 6, 1);
        add_animation_keyframe(animation_comp2, 1000, 7, 0);
        add_animation_keyframe(animation_comp2, 1000, 8, 1);

        add_component_to_entity(player, (void *)pos_comp2);
        add_component_to_entity(player, (void *)animation_comp);
        add_component_to_entity(player, (void *)animation_comp2);

        start_entity_animation(player, 0);
    }
}

int main() {
    position_component_t *pos_comp;
    texture_component_t *texture_comp;

    log_info("### Starting Bomberman");

    // INIT ENGINE
    EGB_set_resources_dir("./resources");
    start_engine();

    entity_t *mario = create_entity("player");
    event_component_t *keystroke_event = create_event_keystroke_component(on_mario_keystroke);
    pos_comp = create_position_component(0, 0, EGB_Position_Classic, 200, 200);
    texture_comp = create_texture_component("./resources/Mario.png");
    add_component_to_entity(mario, (void *)keystroke_event);
    add_component_to_entity(mario, (void *)pos_comp);
    add_component_to_entity(mario, (void *)texture_comp);

    set_framerate(120);
    run_engine();

    // STOPING ENGINE
    stop_engine();
}
