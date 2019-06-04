/*
** engine.h for  in /Bomberman/bourda_j
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#ifndef __ENGINE_H__
#define __ENGINE_H__

// Forward declaration
typedef struct EGB_Entity_s EGB_Entity;
typedef struct EGB_Component_s EGB_Component;
typedef struct EGB_Component_Position_s EGB_Component_Position;
typedef struct EGB_Component_Animation_s EGB_Component_Animation;
typedef struct EGB_Component_Velocity_s EGB_Component_Velocity;
typedef struct EGB_Component_Event_s EGB_Component_Event;
typedef struct EGB_Component_Id_s EGB_Component_Id;
typedef struct EGB_Component_Collision_s EGB_Component_Collision;
typedef struct EGB_Entity_Manager_s EGB_Entity_Manager;
typedef struct EGB_Resource_s EGB_Resource;
typedef struct EGB_Resource_List_s EGB_Resource_List;

// Va args
#include <stdarg.h>

// limits
#include <limits.h>

// directory handling
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

// SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// Network
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>

// LOGS
#include "./log/log.h"

// FRAMERATE
#include "./framerate/framerate.h"

// ENTITY
#include "./entities/entities.h"

// COMPONENTS
#include "./components/animation/animation.h"
#include "./components/velocity/velocity.h"
#include "./components/collision/collision.h"
#include "./components/position/position.h"
#include "./components/texture/texture.h"
#include "./components/fpsrate/fpsrate.h"
#include "./components/components.h"
#include "./components/events/events.h"
#include "./components/id/id.h"
#include "./components/range/range.h"
#include "./components/events/click/click.h"
#include "./components/events/hover/hover.h"
#include "./components/events/keystroke/keystroke.h"
// NETWORK
#include "./components/networkable/networkable.h"
#include "./components/networkable/serializer/serializer.h"
#include "./network/network.h"
#include "./network/events/events.h"

// RESOURCES
#include "./resources/resources.h"
#include "./resources/load/load.h"

// SDL
#include "./sdl/sdl.h"

// EVENTS
#include "./events/events.h"

// TOOLS
#include "./tools/entities/fps_indicator/fps_indicator.h"

// SERVER SIDE
#include "./server/entities/entities.h"
#include "./server/manager/manager.h"

int EGB_Run();
int EGB_Init();
int EGB_Quit();
void EGB_Set_BackgroundColor(int r, int g, int b, int a);
void EGB_RegisterSerializers();

int EGB_SDL_LoadTexture(SDL_Renderer* renderer, char *filename, SDL_Texture **sprite);

EGB_Entity_Manager      *EGB_Manager_Collision(Uint32 flags, ...);
#endif
