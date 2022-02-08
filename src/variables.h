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
extern SDL_bool goto_game;
extern SDL_bool goto_map_picker;
extern SDL_bool goto_diff_pick;
extern SDL_bool goto_winner;

extern Sint16 x[30][6]; extern Sint16 y[30][6];
extern int l;

typedef struct march_info{
    Sint16 x[200];
    Sint16 y[200];
    double vx;
    double vy;
    bool is_atk[200];
    int total_soldiers;
    int src_index;
    int des_index;
    int id;
}march_info;

typedef struct each_base{
    Sint16 base_x[10];
    Sint16 base_y[10];
    int base_points[10];
    int points_speed[10];
    int base_id[10];
    bool being_attacked[10];
    struct march_info marches[300];
}each_base;


extern each_base all_bases;
extern int point_adder;

extern double delta_y, delta_x, theta;
extern double speed;
extern int total_marches;
extern SDL_Texture* points_tex[10];

extern int leader_base[4];

extern bool pick_easy, pick_medium, pick_hard;
extern bool won;