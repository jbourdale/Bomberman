#include "engine/engine.h"

/**
 * MARIO HANDLER CLICK
 */
void on_mario_click(EGB_Entity *entity, SDL_Event e)
{
    log_debug("on click on : %s", entity->name);
    log_debug("e : %p", &e);
    char *rawEncoded = EGB_Serializer_EncodeEntity(entity);
    EGB_Serializer_DecodeEntity(rawEncoded);
}

void on_explosion(EGB_Entity *entity) {
    log_debug("BOMB EXPLOSED : %s", entity->name);
    EGB_SetWindowTitle("Bomb explosed");
}
void on_start(EGB_Entity *entity) {
    log_debug("BOMB PLACED : %s", entity->name);
    EGB_SetWindowTitle("Bomb placed");
}

/**
 * On mario keystroke
 */
void on_mario_keystroke(EGB_Entity *entity) {
    EGB_Component_Position    *pos_comp;
    const Uint8             *key_state = SDL_GetKeyboardState(NULL);


    key_state = SDL_GetKeyboardState(NULL);
    pos_comp = (EGB_Component_Position*)EGB_FindComponentByName(entity, "position_component");
    if(key_state[SDL_SCANCODE_LEFT]) {
        EGB_Position_Move_Left(entity, 10);
        EGB_Network_SendEntity(entity);
    }
    if (key_state[SDL_SCANCODE_RIGHT]) {
        EGB_Position_Move_Right(entity, 10);
        EGB_Network_SendEntity(entity);
    }
    if (key_state[SDL_SCANCODE_UP]) {
        EGB_Position_Move_Up(entity, 10);
        EGB_Network_SendEntity(entity);
    }
    if (key_state[SDL_SCANCODE_DOWN]) {
        EGB_Position_Move_Down(entity, 10);
        EGB_Network_SendEntity(entity);
    }
    if (key_state[SDL_SCANCODE_SPACE])
    {
        EGB_FPSIndicator_Display(1);
        EGB_Entity *player = EGB_Entity_Create("bomb");
        EGB_Component_Position *pos_comp2 = EGB_Component_CreatePosition(
            pos_comp->x, pos_comp->y, EGB_Position_Background, 50, 50);
        EGB_Component_Animation *animation_comp = EGB_Component_CreateAnimation(
            "bomb.png", 0, 24, 24, 0
        );
        int start_keyframe = EGB_Animation_AddKeyframe(animation_comp, 400, 0, 0);
        EGB_Keyframe_Set_OnStart(animation_comp, start_keyframe, on_start);
        EGB_Animation_AddKeyframe(animation_comp, 400, 1, 0);
        EGB_Animation_AddKeyframe(animation_comp, 400, 2, 0);
        EGB_Animation_AddKeyframe(animation_comp, 200, 3, 0);
        EGB_Animation_AddKeyframe(animation_comp, 200, 0, 4);
        EGB_Animation_AddKeyframe(animation_comp, 200, 0, 3);
        EGB_Animation_AddKeyframe(animation_comp, 200, 0, 2);
        int keyframe_id = EGB_Animation_AddKeyframe(animation_comp, 200, 0, 1);
        EGB_Keyframe_Set_OnFinish(animation_comp, keyframe_id, on_explosion);
        EGB_Component_AddToEntity(player, (void *)pos_comp2);
        EGB_Component_AddToEntity(player, (void *)animation_comp);
        EGB_Component_StartAnimation(player, 0);
    }
}

int main() {
    EGB_Component_Position *pos_comp, *pos_comp2;
    EGB_Component_Collision *collide_comp, *collide_comp2;
    EGB_Component_Texture *texture_comp, *texture_comp2;

    log_info("### Starting Bomberman");

    for (int i = 0; i< 10; i++) {
        char *tmp = malloc(EGB_NETWORKABLE_ID_LENGTH + 10);
        EGB_Network_GenerateId(tmp);
        log_debug("generated id : %s", tmp);
    }

    // INIT ENGINE
    EGB_Set_Resources_RootDir("./resources");
    EGB_SetWindowTitle("Bomberman");
    EGB_Set_BackgroundColor(255, 255, 255, 255);
    EGB_FPSIndicator_Display(0);
    EGB_Network_Configuration config= { "127.0.0.1", 1337 };
    EGB_Network_SetConfiguration(config);
    EGB_Network_Enable();
    EGB_Init();

    EGB_Entity *bg = EGB_Entity_Create("background");
    pos_comp2 = EGB_Component_CreatePosition(0, 0, EGB_Position_Background, 1920, 1080);
    texture_comp = EGB_Component_CreateTexture("background.png");
    EGB_Component_AddToEntity(bg, (void *)pos_comp2);
    EGB_Component_AddToEntity(bg, (void *)texture_comp);

    EGB_Entity *mario = EGB_Entity_Create("player");
    EGB_Component_Event *keystroke_event = EGB_Component_CreateEventKeyStroke(on_mario_keystroke);
    EGB_Component_Event *click_event = EGB_Component_CreateEventClick(on_mario_click);
    pos_comp = EGB_Component_CreatePosition(0, 0, EGB_Position_Classic, 200, 200);
    collide_comp = EGB_Component_CreateCollision(1);
    texture_comp = EGB_Component_CreateTexture("Mario.png");
    EGB_Component_Networkable *networkable_comp = EGB_Component_CreateNetworkable();
    EGB_Component_AddToEntity(mario, texture_comp);
    EGB_Component_AddToEntity(mario, keystroke_event);
    EGB_Component_AddToEntity(mario, click_event);
    EGB_Component_AddToEntity(mario, pos_comp);
    EGB_Component_AddToEntity(mario, collide_comp);
    EGB_Component_AddToEntity(mario, networkable_comp);

    log_debug("mario encoded : %s", EGB_Serializer_EncodeEntity(mario));

    EGB_Entity *mario2 = EGB_Entity_Create("player");
    log_debug("1");
    pos_comp2 = EGB_Component_CreatePosition(600, 300, EGB_Position_Classic, 200, 200);
    log_debug("2");
    collide_comp2 = EGB_Component_CreateCollision(1);
    log_debug("3");
    texture_comp2 = EGB_Component_CreateTexture("Mario.png");
    log_debug("4");
    EGB_Component_AddToEntity(mario2, (void *)pos_comp2);
    log_debug("5");
    EGB_Component_AddToEntity(mario2, (void *)texture_comp2);
    log_debug("6");
    EGB_Component_AddToEntity(mario2, (void *)collide_comp2);
    log_debug("7");
    EGB_Entity *tmp = EGB_FindEntityByPosition(600, 300, EGB_Position_Classic);
    log_debug("tmp ENTITY : %s", tmp->name);

    log_debug("set framerate");
    EGB_SetFramerate(120);
    log_debug("set framerate end");
    EGB_Run();

    // STOPING ENGINE
    EGB_Quit();
}
