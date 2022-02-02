#ifndef FOP_PROJECT_VARIABLES_H
#define FOP_PROJECT_VARIABLES_H

#endif //FOP_PROJECT_VARIABLES_H

#include "functions.h"

extern const int FPS;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern SDL_Window *sdlWindow;
extern SDL_Renderer *sdlRenderer;

extern TTF_Font* xeros;
extern char* username;

extern SDL_bool shallExit;
extern SDL_bool goto_start;
extern SDL_bool goto_main_menu;
extern SDL_bool goto_new_game;

extern Sint16 mid_xs[30]; extern Sint16 mid_ys[30];
extern Sint16 x[30][6]; extern Sint16 y[30][6];
extern Sint16 nx[6]; extern Sint16 ny[6];
extern Sint16 max_shapes;