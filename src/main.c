#include "engine/engine.h"

int main() {
    SDL_Window *window;
    SDL_Renderer *renderer;

    log_info("### Starting Bomberman");

    start_engine(&window, &renderer);

    SDL_Event e;
    SDL_PollEvent(&e);

    SDL_Delay(3000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit(); // On quitte la SDL
}
