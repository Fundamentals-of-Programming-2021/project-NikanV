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
SDL_bool goto_game = false;
SDL_bool goto_map_picker = false;
SDL_bool goto_diff_pick = false;
SDL_bool goto_winner = false;
SDL_bool goto_leaderboard = false;



Sint16 x[30][6]; Sint16 y[30][6];

each_base all_bases;
player all_players[100];
int l = 70;
int point_adder = 0;

int count_players = 0;

double delta_y, delta_x, theta;
double speed = 3;
int total_marches = 0;
SDL_Texture* points_tex;

int leader_base[4];

bool pick_easy = false, pick_medium = false, pick_hard = false;
bool won = false;
