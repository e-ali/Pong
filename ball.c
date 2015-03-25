#include "ball.h"
#include "paddle.h"
#include "common.h"

void
load_ball(Ball *ball)
{
	ball->texture = load_texture("res/ball.png");

	ball->w = get_width(ball->texture);
	ball->h = get_height(ball->texture);

	ball->y_velocity = 6;
	ball->x_velocity = 10;
	ball->hit_effect = Mix_LoadWAV("res/hit.wav");
}

void
render_ball(Ball *ball)
{
	SDL_Rect dest_rect = {ball->x, ball->y, ball->w, ball->h};
	SDL_RenderCopy(main_renderer, ball->texture, NULL, &dest_rect);
}

void
move_ball(Ball *ball, Paddle p[])
{
	ball->x += ball->x_velocity;
	ball->y += ball->y_velocity;

	if (ball->y <= 0)
		ball->y_velocity = -ball->y_velocity;
	if (ball->y + ball->h > g_main_height)
		ball->y_velocity = -ball->y_velocity;

	if (collision(ball, &p[PLAYER_LEFT])) {
		if (ball->hit_effect)
			Mix_PlayChannel(-1, ball->hit_effect, 0);
		if (ball->x < p[PLAYER_LEFT].x+p[PLAYER_LEFT].w)
			ball->x_velocity = -ball->x_velocity;
		else
			ball->y_velocity = -ball->y_velocity;
	}

	if (collision(ball, &p[PLAYER_RIGHT])) {
		if (ball->hit_effect)
			Mix_PlayChannel(-1, ball->hit_effect, 0);
		if (ball->x+ball->w > p[PLAYER_RIGHT].x) {
			ball->x_velocity = -ball->x_velocity;
		} else {
			ball->y_velocity = -ball->y_velocity;
		}
	}

}

void
cleanup_ball(Ball *ball)
{
	SDL_DestroyTexture(ball->texture);
	Mix_FreeChunk(ball->hit_effect);
}

bool
collision(Ball *ball, Paddle *p)
{
	if (ball->y >= p->y + p->h)
		return false;
	if (ball->x >= p->x + p->w)
		return false;
	if (ball->y + ball->h <= p->y)
		return false;
	if (ball->x + ball->w <= p->x)
		return false;
	return true;
}
