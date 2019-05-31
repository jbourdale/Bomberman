#include "engine/engine.h"
#include "game/game.h"

void onNewEntityRecv(EGB_Entity *entity) {
    log_debug("new entity recv : %s", entity->name);
    if (strcmp(entity->name, "player") == 0) {
        add_idle_animations(entity);
        add_walking_animations(entity);
        EGB_Component_StartAnimation(entity, FRONT_IDLE_ANIMATION_ID);
    }
}

void onEntityUpdate(EGB_Entity *entity) {
    log_debug("entity updated : %s", entity->name);
}

int main() {
    log_info("### Starting Bomberman");

    // INIT ENGINE
    EGB_Set_Resources_RootDir("./resources");
    EGB_SetWindowTitle("Bomberman");
    EGB_Set_BackgroundColor(90, 106, 108, 255);
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
    EGB_SetFramerate(30000);

    EGB_Run();

    // STOPING ENGINE
    EGB_Quit();
}
