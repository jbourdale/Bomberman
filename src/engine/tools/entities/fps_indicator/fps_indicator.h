#ifndef __FPSTICKER_H__
#define __FPSTICKER_H__

#define FRAME_VALUES 50 // Precision of framerate calculation
#define DEFAULT_FRAME_RATE 60

#include "../../../engine.h"

void        EGB_FPSIndicator_Create();
void        EGB_FPSIndicator_KeyStrokeEventHandler(EGB_Entity *entity, SDL_Event e);
void        EGB_FPSIndicator_Renderer();
float       EGB_FPSIndicator_Compute();
void        EGB_FPSIndicator_Display(int display);

#endif
