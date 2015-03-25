#include "menu.h"

void
load_menu_items(MenuItem items[], int count)
{
	//TTF_Font *menu_font = load_font("res/Droid.ttf", 30);
	//SDL_Color c1, c2;
	//c1 = (SDL_Color) {255, 255, 255, 100};
	//c2 = (SDL_Color) {0xff,0x00,0x7f,0xff};

	//items[0].texture = load_text(menu_font, "Fabulous Pong!", c2);
	//items[1].texture = load_text(menu_font, "(N)ew game?", c1);
	//items[2].texture = load_texture("res/newgame.png");
	items[0].texture = load_texture("res/title.png");
	items[1].texture = load_texture("res/newgame.png");
	items[2].texture = load_texture("res/quit.png");

	for (int i = 0; i < count; i++) {
		items[i].w = get_width(items[i].texture);
		items[i].h = get_height(items[i].texture);
		items[i].x = g_main_width/2-(items[i].w/2);
	}

	items[0].y = g_main_height*0.15;
	items[1].y = g_main_height*0.70;
	items[2].y = g_main_height*0.78;

	clear_screen(BLUE);
	//TTF_CloseFont(menu_font);
}

void
render_menu_items(MenuItem items[], int count)
{
	for (int i = 0; i < count; i++) {
		SDL_Rect dest_rect = {items[i].x, items[i].y, items[i].w, items[i].h};
		SDL_RenderCopy(main_renderer, items[i].texture, NULL, &dest_rect);
	}
}
