#ifndef __FPSTICKER_H__
#define __FPSTICKER_H__

#define FRAME_VALUES 50 // Precision of framerate calculation
#define DEFAULT_FRAME_RATE 60

#include "../../../engine.h"

void        create_fps_indicator();
void        fps_indicator_on_key_stroke(entity_t *entity, SDL_Event e);
void        fps_indicator_init();
void        fps_indicator_render();
float       fps_indicator_compute();

#endif
