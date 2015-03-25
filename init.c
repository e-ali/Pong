#include "init.h"

void
init_sdl(void)
{
	int flags;

	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
		fprintf(stderr, "\ninit_sdl(): %s\n", SDL_GetError());
		exit(1);
	}

	TTF_Init();

	flags = IMG_INIT_PNG;
	if (IMG_Init(flags) != flags) {
		fprintf(stderr, "\ninit_sdl(): %s\n", IMG_GetError());
		exit(1);
	}

	flags = MIX_INIT_OGG;
	if (Mix_Init(flags) != flags) {
		fprintf(stderr, "\ninit_sdl(): %s\n", Mix_GetError());
		exit(1);
	}

	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1) {
		fprintf(stderr, "\ninit_sdl(): %s\n", Mix_GetError());
		exit(1);
	}
}

void
init_main_window(void)
{
	main_window = SDL_CreateWindow(PROG_NAME,
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			WIDTH, HEIGHT,
			0);
			//SDL_WINDOW_FULLSCREEN_DESKTOP);

	SDL_GetWindowSize(main_window, &g_main_width, &g_main_height);

	if (!main_window) {
		fprintf(stderr, "\ninit_main_window(): %s\n", SDL_GetError());
		exit(1);
	}

	main_renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED);
	if (!main_renderer)
		main_renderer = SDL_CreateRenderer(main_window, -1, 0);
	if (!main_renderer) {
		fprintf(stderr, "\ninit_main_window(): %s\n", SDL_GetError());
		exit(1);
	}

	SDL_Surface *icon = load_surface("res/icon.png");
	if (icon)
		SDL_SetWindowIcon(main_window, icon);
}

void
shutdown_sdl(void)
{
	TTF_Quit();
	IMG_Quit();
	Mix_CloseAudio();
	Mix_Quit();

	SDL_DestroyRenderer(main_renderer);
	SDL_DestroyWindow(main_window);
	SDL_Quit();
}
