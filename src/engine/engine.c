/*
** engine.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "engine.h"

int                 EGB_Run()
{
    int             quit;
    SDL_Renderer    *renderer;

    renderer = EGB_SDL_GetCurrentRenderer();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    quit = 0;
    while (quit == 0)
    {
        EGB_InitFPSRegulation();
        quit = EGB_Event_Handle();
        EGB_Render_Entities();
        EGB_RegulateFPS();
    }
    return 0;
}

int EGB_Init()
{
    log_debug("start_engine");
    if(EGB_SDL_Init())
    {
        log_error("Couldn't initialize SDL.");
        return 1;
    }
    EGB_LoadResources();
    EGB_FPSIndicator_Create();
    return 0;
}

int EGB_Quit()
{
    SDL_DestroyRenderer(EGB_SDL_GetCurrentRenderer());
    SDL_DestroyWindow(SDL_GL_GetCurrentWindow());
    TTF_Quit();
    SDL_Quit();
    return 0;
}