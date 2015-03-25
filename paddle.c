#include "paddle.h"
#include "common.h"

void
load_paddles(Paddle p[])
{
	p[PLAYER_LEFT].texture = load_texture("res/paddle1.png");
	p[PLAYER_RIGHT].texture = load_texture("res/paddle2.png");
	for (int i = 0; i < PLAYER_NUM; i++) {
		p[i].w = get_width(p[i].texture);
		p[i].h = get_height(p[i].texture);
		p[i].y_velocity = 13;
		for (int i = 0; i < DIRECTION_NUM; i++)
			p[i].direction[i] = false;
		p[i].score = 0;
		p[i].score_string[0] = '\0';

		/* The scores*/
		int w, h;
		SDL_Color c = (SDL_Color) {255, 255, 255, 100};
		SDL_Rect rect;

		p[i].score_font = load_font("res/Droid.ttf", 26);

		sprintf(p[i].score_string, "%d", p[i].score);

		p[i].score_texture = load_text(p[i].score_font, p[i].score_string, c);
		SDL_QueryTexture(p[i].score_texture,NULL,NULL,&w,&h);

		p[i].score_rect.w = w;
		p[i].score_rect.h = h;
	}

	p[PLAYER_LEFT].score_rect.x = 40;
	p[PLAYER_LEFT].score_rect.y = 30;
	p[PLAYER_RIGHT].score_rect.x = g_main_width-30;
	p[PLAYER_RIGHT].score_rect.y = 30;
}

void
render_paddles(Paddle p[])
{
	for (int i = 0; i < PLAYER_NUM; i++) {
		SDL_Rect dest_rect = {p[i].x, p[i].y, p[i].w, p[i].h};
		SDL_RenderCopy(main_renderer, p[i].texture, NULL, &dest_rect);
	}
}

void
move_paddle(Paddle *p)
{
	if (!p) return;
	if (p->direction[STOP]) return;

	if (p->direction[UP] && p->y >= 0) {
		p->y -= p->y_velocity;
	} else if (p->direction[DOWN] && p->y + p->h <= g_main_height) {
		p->y += p->y_velocity;
	}
}

void
cleanup_paddles(Paddle p[])
{
	for (int i = 0; i < 2; i++) {
		SDL_DestroyTexture(p[i].texture);
		SDL_DestroyTexture(p[i].score_texture);
		TTF_CloseFont(p[i].score_font);

		p[i].score = 0;
		p[i].score_string[0] = '\0';
	}
}
