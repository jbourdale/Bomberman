/*
** gui.c for  in /home/dev/C/My_FTL/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
** Started on  Tue Mar  19 16:57:41 2017 BOURDALE Jules
*/
#include "gui.h"

int                 run()
{
    int             is_game_running;
    SDL_Renderer    *renderer;
    SDL_Window      *window;

    if (init_SDL(&window, &renderer)) {
        printf("Enable to init SDL");
        return 1;
    }

    is_game_running = 1;
    while(is_game_running) {
        printf("Loop \n");
        sleep(1);
    }

    return 0;
}

