#include "common.h"

SDL_Surface *
load_surface(char *filename)
{
	SDL_Surface *surface;

	surface = IMG_Load(filename);
	if (!surface) {
		fprintf(stderr, "load_surface(): %s\n", IMG_GetError());
		return NULL;
	}

	return surface;
}

SDL_Texture *
load_texture(char *filename)
{
	SDL_Surface *surface;
	SDL_Texture *texture;

	surface = load_surface(filename);
	texture = SDL_CreateTextureFromSurface(main_renderer, surface);

	SDL_FreeSurface(surface);

	if (!texture) {
		fprintf(stderr, "load_texture(): %s\n", SDL_GetError());
		return NULL;
	}

	return texture;
}

TTF_Font *
load_font(char *filename, int size)
{
	TTF_Font *font;

	font = TTF_OpenFont(filename, size);
	if (!font) {
		fprintf(stderr, "load_font(): %s\n", TTF_GetError());
		return NULL;
	}

	return font;
}

SDL_Texture *
load_text(TTF_Font* font, const char *text, SDL_Color fg)
{
	 SDL_Surface *surface;
	 SDL_Texture *texture;

	 surface = TTF_RenderText_Solid(font, text, fg);
	 if (!surface) {
		fprintf(stderr, "load_text(): %s\n", SDL_GetError());
		return NULL;
	 }

	texture = SDL_CreateTextureFromSurface(main_renderer, surface);

	SDL_FreeSurface(surface);

	if (!texture) {
		fprintf(stderr, "load_text(): %s\n", SDL_GetError());
		return NULL;
	}

	return texture;
}

int
get_width(SDL_Texture *texture)
{
	int w;
	SDL_QueryTexture(texture, NULL, NULL, &w, NULL);

	return w;
}

int
get_height(SDL_Texture *texture)
{
	int h;
	SDL_QueryTexture(texture, NULL, NULL, NULL, &h);

	return h;
}

void
reposition(Paddle p[], Ball *ball)
{
	const int pr_x = g_main_width - p[PLAYER_RIGHT].w;
	const int pr_y = g_main_height/2 - p[PLAYER_RIGHT].h/2;
	p[PLAYER_RIGHT].x = pr_x;
	p[PLAYER_RIGHT].y = pr_y;

	const int pl_x = 0;
	const int pl_y = g_main_height/2 - p[PLAYER_LEFT].h/2;
	p[PLAYER_LEFT].x = pl_x;
	p[PLAYER_LEFT].y = pl_y;

	const int ball_x = g_main_width/2 - ball->w/2;
	const int ball_y = g_main_height/2 - ball->h/2;
	ball->x = ball_x;
	ball->y = ball_y;
}

void
clear_screen(int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(main_renderer, r, g, b, a);
	SDL_RenderClear(main_renderer);
}
