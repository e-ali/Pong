#ifndef MENU_H
#define MENU_H

#include "main.h"
#include "common.h"

struct MenuItem {
	int x;
	int y;
	int w;
	int h;
	SDL_Texture *texture;
};
typedef struct MenuItem MenuItem;

void load_menu_items(MenuItem [], int);
void render_menu_items(MenuItem [], int);

#endif
