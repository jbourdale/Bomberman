#include "engine/engine.h"
#include "game/game.h"

void onNewEntityRecv(EGB_Entity *entity) {
    log_debug("new entity recv : %s", entity->name);
}

void onEntityUpdate(EGB_Entity *entity) {
    log_debug("entity updated : %s", entity->name);
}

int main() {
    log_info("### Starting Bomberman");

    // INIT ENGINE
    EGB_Set_Resources_RootDir("./resources");
    EGB_SetWindowTitle("Bomberman");
    EGB_Set_BackgroundColor(255, 255, 255, 255);
    EGB_FPSIndicator_Display(0);
    EGB_Network_OnEntityUpdated(onEntityUpdate);
    EGB_Network_OnNewEntityRecv(onNewEntityRecv);
    EGB_Network_Configuration config= { "127.0.0.1", 1337 };
    EGB_Network_SetConfiguration(config);
    EGB_Network_Enable();
    EGB_Init();

    //init_map();
    init_player();

    EGB_SetFramerate(120);
    log_debug("set framerate end");
    EGB_Run();

    // STOPING ENGINE
    EGB_Quit();
}
