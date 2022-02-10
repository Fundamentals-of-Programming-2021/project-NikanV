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


//structs with their variables
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

extern bool marches_state[100];

typedef struct each_base{
    Sint16 base_x[11];
    Sint16 base_y[11];
    int base_points[11];
    int points_speed[11];
    int base_id[11];
    int max_points[11];
    bool being_attacked[11];
    struct march_info marches[100];
}each_base;

extern each_base all_bases;
extern Sint16 x[30][6]; extern Sint16 y[30][6];
extern int l;

typedef struct potions{
    Sint16 x[4];
    Sint16 y[4];
    int id[4];
    bool is_active[4];
    bool draw_potion[4];
    int timer[4];
}potions;

extern potions all_potions;
extern int potion_ran;

typedef struct player{
    char username[15];
    int ranking;
    int total_pt;
}player;

extern player all_players[100];
extern int count_players;
extern bool signed_up;

//main menu variables
extern SDL_bool shallExit;
extern SDL_bool goto_start;
extern SDL_bool goto_main_menu;
extern SDL_bool goto_game;
extern SDL_bool goto_map_picker;
extern SDL_bool goto_diff_pick;
extern SDL_bool goto_winner;
extern SDL_bool goto_leaderboard;
extern SDL_bool show_top_four;

extern char* username;
extern char number[5];


//in game variables
extern double delta_y, delta_x, theta;
extern double speed;
extern int first_base;
extern int second_base;

extern int point_adder;

extern SDL_Texture* points_tex;
extern SDL_Texture* potions_tex;
extern SDL_Rect points_rec;
extern SDL_Rect potions_rec;


//winner variables
extern int leader_base[4];

extern bool pick_easy, pick_medium, pick_hard;
extern bool won;

extern SDL_Texture* congrats;
extern SDL_Texture* winning_point;
extern SDL_Rect congrats_rec;
extern SDL_Rect winning_point_rec;