#include "engine/engine.h"

int main() {
    SDL_Window *window;
    SDL_Renderer *renderer;

    log_info("### Starting Bomberman");

    window = NULL;
    renderer = NULL;
    start_engine(window, renderer);
    stop_engine(window, renderer);
}
