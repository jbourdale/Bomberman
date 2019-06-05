#include "engine/engine.h"
#include "game/game.h"

void onNewEntityRecv(EGB_Entity *entity) {
    if (strcmp(entity->name, "player") == 0) {
        entity->on_destroy = on_player_destroy;
        entity->render = player_custom_renderer;
        add_idle_animations(entity);
        add_walking_animations(entity);
        EGB_Component_StartAnimation(entity, FRONT_IDLE_ANIMATION_ID);
    } else if (strcmp(entity->name, "bomb") == 0) {
        create_bomb_animation(entity);
        EGB_Component_StartAnimation(entity, BOMB_ANIMATION_ID);
    } else if (strcmp(entity->name, "explosion") == 0) {
        create_explosion_animation(entity);
        EGB_Component_StartAnimation(entity, EXPLOSION_ANIMATION_ID);
    } else if (strcmp(entity->name, "range_bonus") == 0) {
        create_range_bonus_animation(entity);
        EGB_Component_StartAnimation(entity, RANGE_BONUS_ANIMATION_ID);
    } else if (strcmp(entity->name, "add_bomb_bonus") == 0) {
        create_add_bomb_bonus_animation(entity);
        EGB_Component_StartAnimation(entity, ADD_BOMB_BONUS_ANIMATION_ID);
    }
}

void onEntityUpdate(EGB_Entity *entity) {
    if (strcmp(entity->name, "player") == 0) {
        start_walking_animation(entity);
    }
}

int main() {
    log_info("### Starting Bomberman");

    // INIT ENGINE
    EGB_Set_Resources_RootDir("./resources");
    EGB_SetWindowTitle("Bomberman");
    EGB_FPSIndicator_Display(0);
    EGB_Network_OnEntityUpdated(onEntityUpdate);
    EGB_Network_OnNewEntityRecv(onNewEntityRecv);
    EGB_Network_Configuration config= { "127.0.0.1", 1337 };
    EGB_Network_SetConfiguration(config);
    EGB_Network_Enable();
    EGB_Init();

    // init_map();
    // init_player();
    setup_home_menu();
    EGB_SetFramerate(40);

    EGB_Run();

    // STOPING ENGINE
    EGB_Quit();
}
