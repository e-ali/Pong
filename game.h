#ifndef GAME_H
#define GAME_H

#include "main.h"
#include "paddle.h"
#include "ball.h"
#include "menu.h"
#include "common.h"

extern bool running;

PongReturn_t do_main_menu(void);
PongReturn_t do_game(void);
void do_score(Paddle [], Ball *);

//void ai(Paddle p[], Ball *ball);

#endif
