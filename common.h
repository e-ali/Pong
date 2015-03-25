#ifndef COMMON_H
#define COMMON_H

#include "main.h"
#include "paddle.h"
#include "ball.h"

extern SDL_Renderer *main_renderer;

extern int g_main_width, g_main_height;

SDL_Surface *load_surface(char *);
SDL_Texture *load_texture(char *);
TTF_Font *load_font(char *, int);
SDL_Texture *load_text(TTF_Font *, const char *, SDL_Color);

int get_width(SDL_Texture *);
int get_height(SDL_Texture *);
void reposition(Paddle [], Ball *);
void clear_screen(int, int, int, int);

#endif
