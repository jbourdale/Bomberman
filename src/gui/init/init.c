/*
** init.c for  in /home/dev/C/My_FTL/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
** Started on  Tue Mar  19 16:57:41 2017 BOURDALE Jules
*/
#include "../gui.h"

// int init_SDL(SDL_Window **window, SDL_Renderer **renderer)
// {
// 	*renderer = NULL;
// 	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
// 		printf("SDL_Init failed");
// 		return 1;
// 	}
// 	else
// 	{
// 		if (!TTF_Init())
// 		{
// 			*window = NULL;
// 			*window = SDL_CreateWindow(
// 				GUI_WINDOW_TITLE,
// 				SDL_WINDOWPOS_UNDEFINED,
// 				SDL_WINDOWPOS_UNDEFINED,
// 				800,
// 				600,
// 				SDL_WINDOW_SHOWN
// 			);
// 			if (*window != NULL)
// 				*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
// 			else {
// 				printf("SDL_CreateWindow failed");
// 				return 1;
// 			}
// 		}
// 		else {
// 			printf("TTF_Init failed");
// 			return 1;
// 		}
// 	}
// 	return 0;
// }
