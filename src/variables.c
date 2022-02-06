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
int tmp_point[10] = {0};
int tmp_index[10] = {0};


each_base all_bases;
int l = 50;
int point_adder = 0;
float delta_y, delta_x, theta;
Sint16 speed = 10;
int total_marches = 0;