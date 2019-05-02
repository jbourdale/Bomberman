/*
** fpsticker.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "fps_indicator.h"

TTF_Font*   font;
SDL_Color   black = {0,0,0, 255};

void                        create_fps_indicator()
{
    position_component_t    *pos_comp;
    event_component_t       *event_comp;
    fpsrate_component_t     *fps_comp;

    log_debug("create_fps_indicator");
    entity_t *fps_indicator_entity = create_entity("fps_indicator");
    fps_indicator_entity->render = fps_indicator_render;
    fps_indicator_entity->displayed = 1;

    event_comp = create_event_keystroke_component(fps_indicator_on_key_stroke);
    add_component_to_entity(fps_indicator_entity, (void *)event_comp);
    
    pos_comp = create_position_component(1820, 1030, EGB_Position_AlwaysOnTop, 100, 75);
    add_component_to_entity(fps_indicator_entity, (void *)pos_comp);

    fps_comp = create_fpsrate_component(DEFAULT_FRAME_RATE);
    add_component_to_entity(fps_indicator_entity , (void *)fps_comp);

    font = (TTF_Font *)EGB_get_resource("spacefont.ttf"); //this opens a font style and sets a size
    log_debug("create_fps_indicator end");
}

void fps_indicator_on_key_stroke(entity_t *entity, SDL_Event e)
{
    if(e.key.keysym.sym == SDLK_F4 && e.type == SDL_KEYDOWN)
    {
        entity->displayed = !entity->displayed;
    }
}

void                        fps_indicator_render(SDL_Renderer *renderer, entity_t *entity)
{
    SDL_Rect                screen_position;
    position_component_t    *pos_comp;
    char                    *text;
    float                   fps;

    if (!entity->displayed)
        return;

    pos_comp = (position_component_t*)find_component_by_name(entity, "position_component");
    if (pos_comp == NULL) {
        return ;
    }
    position_component_to_rect(pos_comp, &screen_position);

    fps = fps_indicator_compute();
    text = malloc(3 * sizeof(char));
    sprintf(text, "%2.f", fps);
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, black);
    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_RenderCopy(renderer, message, NULL, &screen_position);
    SDL_DestroyTexture(message);
    SDL_FreeSurface(surfaceMessage);
}

float               fps_indicator_compute()
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
