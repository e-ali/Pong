#ifndef PADDLE_H
#define PADDLE_H

#include "main.h"

struct Paddle {
	int x;
	int y;
	int w;
	int h;
	int y_velocity;
	bool direction[5];
	SDL_Texture *texture;

	/* score */
	SDL_Rect score_rect;
	unsigned int score;
	char score_string[50];
	SDL_Texture *score_texture;
	TTF_Font *score_font;
};
typedef struct Paddle Paddle;

void load_paddles(Paddle []);
void render_paddles(Paddle []);
void move_paddle(Paddle *);
void cleanup_paddles(Paddle []);

#endif
