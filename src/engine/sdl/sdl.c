/*
** sdl.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "sdl.h"

int                 EGB_SDL_Init()
{
    SDL_Window      *window;
    SDL_Renderer    *renderer;

    log_debug("init_SDL");

    window = NULL;
    renderer = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return 1;

    if (!TTF_Init())
    {
        if (EGB_SDL_InitWindow(&window) != 0 || window == NULL) {
            printf("SDL_Init failed: %s\n", SDL_GetError());
            return 1;
        }
        log_debug("window created");
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        SDL_RenderSetLogicalSize(renderer, LOGICAL_WINDOW_WIDTH, LOGICAL_WINDOW_HEIGHT);
    }
    else {
        log_debug("Can't init TTF INIT");
        return 1;
    }
    return 0;
}

int                     EGB_SDL_InitWindow(SDL_Window **window)
{
    SDL_DisplayMode     mode;
    if (SDL_GetCurrentDisplayMode(0, &mode))
        return 1;

    log_debug("init_window");

    *window = NULL;
    *window = SDL_CreateWindow(
        GUI_WINDOW_TITLE,
        0,
        0,
        mode.w,
        mode.h,
        SDL_WINDOW_SHOWN |
        SDL_WINDOW_RESIZABLE |
        SDL_WINDOW_INPUT_FOCUS |
        SDL_WINDOW_MOUSE_FOCUS |
        SDL_WINDOW_OPENGL
    );
    return 0;
}


SDL_Renderer        *EGB_SDL_GetCurrentRenderer()
{
    SDL_Window      *window;

    window = NULL;
    window = SDL_GL_GetCurrentWindow();
    if (window == NULL) {
        log_debug("WINDOW NULL!!!!!!!!!!!!");
        return NULL;
    }
    return SDL_GetRenderer(window);
}
