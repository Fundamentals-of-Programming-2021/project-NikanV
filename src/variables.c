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

Sint16 x[30][6]; Sint16 y[30][6];

each_base all_bases;
int l = 70;
int point_adder = 0;
double delta_y, delta_x, theta;
double speed = 7;
int total_marches = 0;