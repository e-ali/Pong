#ifndef BALL_H
#define BALL_H

#include "paddle.h"

struct Ball {
	int x;
	int y;
	int w;
	int h;
	int x_velocity;
	int y_velocity;
	SDL_Texture *texture;
	Mix_Chunk *hit_effect;
};
typedef struct Ball Ball;

void load_ball(Ball *);
void render_ball(Ball *);
void move_ball(Ball *, Paddle []);

void cleanup_ball(Ball *);

bool collision(Ball *, Paddle *);

#endif
