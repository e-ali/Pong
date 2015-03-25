#ifndef INIT_H
#define INIT_H

#include "common.h"
#include "main.h"

extern SDL_Window *main_window;
extern SDL_Renderer *main_renderer;

extern int g_main_width;
extern int g_main_height;

void init_sdl(void);
void init_main_window(void);
void shutdown_sdl(void);

#endif
