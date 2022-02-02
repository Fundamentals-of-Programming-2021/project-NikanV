#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "functions.h"
#include "variables.h"

const int FPS = 60;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1440;

SDL_Window *sdlWindow;
SDL_Renderer *sdlRenderer;

TTF_Font* xeros;
char* username;

SDL_bool shallExit = SDL_FALSE;
SDL_bool goto_start = true;
SDL_bool goto_main_menu = false;
SDL_bool goto_new_game = false;

Sint16 mid_xs[30]; Sint16 mid_ys[30];
Sint16 x[30][6]; Sint16 y[30][6];
Sint16 nx[6]; Sint16 ny[6];
Sint16 max_shapes = 0;

