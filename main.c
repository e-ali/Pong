#include "game.h"
#include "init.h"

bool running;

int
main(int argc, char **argv)
{
	SDL_Event event;
	running = true;

	init_sdl();
	init_main_window();

	Mix_Music *menu_music;
	menu_music = Mix_LoadMUS("res/menu.ogg");
	Mix_PlayMusic(menu_music, -1);

	while (running) {
		int return_val = do_main_menu();
		switch (return_val) {
			case DO_QUIT:
				running = false;
				Mix_FreeMusic(menu_music);
				break;
			case DO_MENU:
				do_main_menu();
				break;
			case DO_GAME:
				do_game();
				break;
		}
	}
	shutdown_sdl();

	return 0;
}
