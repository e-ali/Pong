#include "game.h"

SDL_Window *main_window;
SDL_Renderer *main_renderer;

int g_main_width, g_main_height;

PongReturn_t
do_main_menu(void)
{
	Uint32 start;
	SDL_Event event;
	MenuItem items[3];

	load_menu_items(items, 3);
	render_menu_items(items, 3);

	while (running) {
		start = SDL_GetTicks();
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					return DO_QUIT;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_q:
							for (int i = 0; i < 3; i++)
								SDL_DestroyTexture(items[i].texture);
							return DO_QUIT;
						case SDLK_n:
							for (int i = 0; i < 3; i++)
								SDL_DestroyTexture(items[i].texture);
							return DO_GAME;
					}
				default:
					break;
			}
		}
		SDL_RenderPresent(main_renderer);

		if (1000/FPS > (SDL_GetTicks() - start))
			SDL_Delay(1000/FPS - (SDL_GetTicks() - start));
	}
}

PongReturn_t
do_game(void)
{
	Uint32 start;
	SDL_Event event;
	Paddle p[PLAYER_NUM];
	Ball ball;

	load_paddles(p);
	load_ball(&ball);
	reposition(p, &ball);

	int player_score[PLAYER_NUM] = {0};

	while (running) {
		start = SDL_GetTicks();

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					cleanup_ball(&ball);
					cleanup_paddles(p);
					return DO_QUIT;

				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_ESCAPE:
							cleanup_ball(&ball);
							cleanup_paddles(p);
							return DO_MENU;

						case SDLK_UP:
							p[PLAYER_RIGHT].direction[UP] = true;
							p[PLAYER_RIGHT].direction[STOP] = false;
							break;
						case SDLK_DOWN:
							p[PLAYER_RIGHT].direction[DOWN] = true;
							p[PLAYER_RIGHT].direction[STOP] = false;
							break;

						case SDLK_w:
							p[PLAYER_LEFT].direction[UP] = true;
							p[PLAYER_RIGHT].direction[STOP] = false;
							break;
						case SDLK_s:
							p[PLAYER_LEFT].direction[DOWN] = true;
							p[PLAYER_RIGHT].direction[STOP] = false;
							break;

						case SDLK_SPACE:
							break;
					}
					break;
				case SDL_KEYUP:
					switch (event.key.keysym.sym) {
						case SDLK_UP:
							p[PLAYER_RIGHT].direction[UP] = false;
							p[PLAYER_RIGHT].direction[STOP] = true;
							break;
						case SDLK_DOWN:
							p[PLAYER_RIGHT].direction[DOWN] = false;
							p[PLAYER_RIGHT].direction[STOP] = true;
							break;

						case SDLK_w:
							p[PLAYER_LEFT].direction[UP] = false;
							p[PLAYER_RIGHT].direction[STOP] = true;
							break;
						case SDLK_s:
							p[PLAYER_LEFT].direction[DOWN] = false;
							p[PLAYER_RIGHT].direction[STOP] = true;
							break;
					}
					break;
			}
		}
		clear_screen(GREY);

		move_paddle(&p[PLAYER_LEFT]);
		move_paddle(&p[PLAYER_RIGHT]);
		//ai(p, &ball);
		move_ball(&ball, p);

		do_score(p, &ball);

		render_ball(&ball);
		render_paddles(p);
		SDL_RenderPresent(main_renderer);

		/* Regulate FPS */
		if (1000/FPS > (SDL_GetTicks() - start))
			SDL_Delay(1000/FPS - (SDL_GetTicks() - start));
	}
}

void
do_score(Paddle p[], Ball *ball)
{
	if (ball->x < 0) {
		p[PLAYER_RIGHT].score++;
		reposition(p, ball);
		SDL_Delay(500);
		ball->x_velocity = -ball->x_velocity;
	} else if (ball->x > g_main_width) {
		p[PLAYER_LEFT].score++;
		reposition(p, ball);
		SDL_Delay(500);
		ball->x_velocity = -ball->x_velocity;
	}

	SDL_Color c = (SDL_Color) {0xff, 0xff, 0xff, 0xff};

	SDL_DestroyTexture(p[0].score_texture);
	SDL_DestroyTexture(p[1].score_texture);

	sprintf(p[PLAYER_LEFT].score_string, "%d", p[PLAYER_LEFT].score);
	sprintf(p[PLAYER_RIGHT].score_string, "%d", p[PLAYER_RIGHT].score);
	p[PLAYER_LEFT].score_texture = load_text(p[PLAYER_LEFT].score_font, p[PLAYER_LEFT].score_string, c);
	p[PLAYER_RIGHT].score_texture = load_text(p[PLAYER_RIGHT].score_font, p[PLAYER_RIGHT].score_string, c);

	SDL_RenderCopy(main_renderer, p[PLAYER_LEFT].score_texture, NULL, &p[PLAYER_LEFT].score_rect);
	SDL_RenderCopy(main_renderer, p[PLAYER_RIGHT].score_texture, NULL, &p[PLAYER_RIGHT].score_rect);
}

//void
//ai(Paddle p[], Ball *ball)
//{
//}
