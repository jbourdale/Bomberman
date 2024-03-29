/*
** fpsticker.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "fps_indicator.h"

SDL_Color   EGB_Color_Black = {0,0,0, 255};
int         EGB_FPSIndicator_IsDisplayed = 1;

/**
 * @brief      Create a FPS counter on corner bottom right
 */
void                        EGB_FPSIndicator_Create()
{
    EGB_Component_Position    *pos_comp;
    EGB_Component_Event       *event_comp;
    EGB_Component_FPSRate     *fps_comp;

    log_debug("create_fps_indicator");
    EGB_Entity *fps_indicator_entity = EGB_Entity_Create("fps_indicator");
    fps_indicator_entity->render = EGB_FPSIndicator_Renderer;
    fps_indicator_entity->displayed = EGB_FPSIndicator_IsDisplayed;

    event_comp = EGB_Component_CreateEventKeyStroke(EGB_FPSIndicator_KeyStrokeEventHandler);
    EGB_Component_AddToEntity(fps_indicator_entity, (void *)event_comp);

    pos_comp = EGB_Component_CreatePosition(1820, 1030, EGB_Position_AlwaysOnTop, 100, 75);
    EGB_Component_AddToEntity(fps_indicator_entity, (void *)pos_comp);

    fps_comp = EGB_Component_CreateFPSRate(DEFAULT_FRAME_RATE);
    EGB_Component_AddToEntity(fps_indicator_entity , (void *)fps_comp);

    log_debug("create_fps_indicator end");
}

/**
 * @brief      FPS indicator keyboard event handler
 *
 * @param      entity  The entity
 * @param      e       The SDL_Event
 */
void EGB_FPSIndicator_KeyStrokeEventHandler(EGB_Entity *entity, SDL_Event e)
{
    if(e.key.keysym.sym == SDLK_F4 && e.type == SDL_KEYDOWN)
    {
        entity->displayed = !entity->displayed;
    }
}

/**
 * @brief      Custom renderer for fps indicator entity
 *
 * @param      renderer  The renderer
 * @param      entity    The entity
 */
void                        EGB_FPSIndicator_Renderer(SDL_Renderer *renderer, EGB_Entity *entity)
{
    SDL_Rect                screen_position;
    EGB_Component_Position  *pos_comp;
    char                    *text;
    float                   fps;
    TTF_Font                *font;

    if (!entity->displayed)
        return;

    font = (TTF_Font *)EGB_Get_Resource("spacefont.ttf"); //this opens a font style and sets a size

    pos_comp = (EGB_Component_Position*)EGB_FindComponentByName(entity, "position_component");
    if (pos_comp == NULL) {
        return ;
    }
    EGB_Component_PositionToRect(pos_comp, &screen_position);

    fps = EGB_FPSIndicator_Compute();
    text = malloc(3 * sizeof(char));
    sprintf(text, "%2.f", fps);
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, EGB_Color_Black);
    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_RenderCopy(renderer, message, NULL, &screen_position);
    SDL_DestroyTexture(message);
    SDL_FreeSurface(surfaceMessage);
}

/**
 * @brief      Compute current FPS rate
 *
 * @return     current FPS rate
 */
float               EGB_FPSIndicator_Compute()
{
    static int      *frametimes = NULL; // An array to store frame times:
    static int      framecount = 0;
    static int      frametimelast = 0;
    float           framespersecond = 0;
    int             frametimesindex;
    int             getticks;
    int             count;
    int             i;

    if (frametimes == NULL)
    {
        frametimes = malloc(FRAME_VALUES * sizeof(int));
        memset(frametimes, 0, FRAME_VALUES * sizeof(int));
        frametimelast = SDL_GetTicks();
    }

    frametimesindex = framecount % FRAME_VALUES;
    getticks = SDL_GetTicks();
    frametimes[frametimesindex] = getticks - frametimelast;
    frametimelast = getticks;
    framecount++;

    if (framecount < FRAME_VALUES) {
        count = framecount;
    } else {
        count = FRAME_VALUES;
    }

    framespersecond = 0;
    for (i = 0; i < count; i++) {
        framespersecond += frametimes[i];
    }
    framespersecond /= count;
    framespersecond = 1000.f / framespersecond;

    return framespersecond;
}


void        EGB_FPSIndicator_Display(int display) {
    EGB_Entity *fps_indicator_entity;

    EGB_FPSIndicator_IsDisplayed = display;

    fps_indicator_entity = EGB_Entity_FindFirstByName("fps_indicator");
    if (fps_indicator_entity != NULL)
        fps_indicator_entity->displayed = display;
}
