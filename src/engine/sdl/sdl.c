/*
** sdl.c for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "sdl.h"

char* EGB_window_title = DEFAULT_GUI_WINDOW_TITLE;

/**
 * @brief      Init all SDL Modules needed
 *
 * @return     status   Initialisation process end status
 *              <ul>
 *                  <li>0 = Correctly init</li>
 *                  <li>1 = An error occured</li>
 *              </ul>
 */
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
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    return 0;
}

/**
 * @brief      Init SDL Window
 *
 * @param      window  The window to init
 *
 * @return     status   Initialisation process end status
 *              <ul>
 *                  <li>0 = Correctly init</li>
 *                  <li>1 = An error occured</li>
 *              </ul>
 */
int                     EGB_SDL_InitWindow(SDL_Window **window)
{
    SDL_DisplayMode     mode;
    if (SDL_GetCurrentDisplayMode(0, &mode))
        return 1;

    log_debug("init_window");

    *window = NULL;
    *window = SDL_CreateWindow(
        EGB_window_title,
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


/**
 * @brief      Return the current used SDL_Renderer
 *
 * @return     return the current renderer or NULL if none exist
 */
SDL_Renderer        *EGB_SDL_GetCurrentRenderer()
{
    SDL_Window      *window;

    window = NULL;
    window = SDL_GL_GetCurrentWindow();
    if (window == NULL) {
        return NULL;
    }
    return SDL_GetRenderer(window);
}


/**
 * @brief      Set the GUI Window title
 *
 * @param      title  The title
 */
void            EGB_SetWindowTitle(char *title) {
    SDL_Window  *window;

    window = SDL_GL_GetCurrentWindow();
    if (window != NULL) {
        SDL_SetWindowTitle(window, title);
    }
    EGB_window_title = title;
}
