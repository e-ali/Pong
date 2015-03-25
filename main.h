#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>
#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#define PROG_NAME "Pong"

#define WIDTH   1024
#define HEIGHT  786

#define FPS 30

#define GREY 0x3f,0x3f,0x3f,0xff
#define BLUE 0x00,0x2d,0x62,0xff

#define PLAYER_LEFT 0
#define PLAYER_RIGHT 1

#define PLAYER_NUM 2
#define DIRECTION_NUM 5

typedef enum { DO_QUIT, DO_MENU, DO_GAME } PongReturn_t;
typedef enum { STOP, UP, DOWN, LEFT, RIGHT } PongDirection_t;

extern SDL_Renderer *main_renderer;
extern int g_main_width, g_main_height;

#endif
