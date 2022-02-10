#include "functions.h"
#include "variables.h"

const int FPS = 60;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1440;

SDL_Window *sdlWindow;
SDL_Renderer *sdlRenderer;
TTF_Font* xeros;

bool marches_state[100];

each_base all_bases;
Sint16 x[30][6]; Sint16 y[30][6];
int l = 70;

potions all_potions;
int potion_ran = 0;

player all_players[100];
int count_players = 0;
bool signed_up = false;
int new_map_x[11], new_map_y[11];


SDL_bool shallExit = SDL_FALSE;
SDL_bool goto_start = true;
SDL_bool goto_main_menu = false;
SDL_bool goto_game = false;
SDL_bool goto_map_picker = false;
SDL_bool goto_diff_pick = false;
SDL_bool goto_winner = false;
SDL_bool goto_leaderboard = false;
SDL_bool show_top_four = false;

char* username;
char number[5];

double delta_y, delta_x, theta;
double speed = 20;
int first_base = -1;
int second_base = -1;

int point_adder = 0;

SDL_Texture* points_tex;
SDL_Texture* potions_tex;
SDL_Rect points_rec;
SDL_Rect potions_rec;

int leader_base[4];

bool pick_easy = false, pick_medium = false, pick_hard = false;
bool won = false;

SDL_Texture* congrats;
SDL_Texture* winning_point;
SDL_Rect congrats_rec;
SDL_Rect winning_point_rec;