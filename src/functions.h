#ifndef FOP_PROJECT_FUNCTIONS_H
#define FOP_PROJECT_FUNCTIONS_H

#endif //FOP_PROJECT_FUNCTIONS_H

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


void Init();

void Begin();

void reset_game();

void destroy_all(SDL_Texture *start_bg_tex, SDL_Texture *main_menu_bg_tex, SDL_Texture *logo_tex, SDL_Texture *name_tex,
                 SDL_Texture *submit_button, SDL_Texture *ingame_name, SDL_Texture *input_tex, SDL_Texture *new_game,
                 SDL_Texture *con_game, SDL_Texture *leaderboard, SDL_Texture *back, SDL_Texture *map,
                 SDL_Texture *random_map_tex, SDL_Texture *choose_dif_tex, SDL_Texture *easy, SDL_Texture *medium,
                 SDL_Texture *hard, SDL_Texture *places_tex,SDL_Texture *leaderboard_player, SDL_Texture *back_to_menu);

void End();

SDL_Color color(int r, int g, int b, int a);

void get_text_and_rect(SDL_Color color, int x, int y, int w, int h, char *text, SDL_Texture** texture,
                       SDL_Rect* rect);

void get_img_and_rect(char* path, SDL_Texture** texture);

void map_maker(int ran);

void xy_maker(Sint16 mid_x, Sint16 mid_y, int index);

void input_struct();

void draw_start(SDL_Texture* start_bg_tex, SDL_Texture* logo_tex, SDL_Texture* name_tex, SDL_Texture* input_tex,
                SDL_Texture* submit_button, SDL_Rect logo_rec, SDL_Rect name_rec, SDL_Rect input_rec,
                SDL_Rect submit_button_rec);

void draw_main_menu(SDL_Texture* main_menu_bg_tex, SDL_Texture* new_game, SDL_Texture* con_game,
                    SDL_Texture* leaderboard, SDL_Texture* back, SDL_Texture* ingame_name, SDL_Rect new_game_rec,
                    SDL_Rect con_game_rec, SDL_Rect leaderboard_rec, SDL_Rect back_rec, SDL_Rect ingame_name_rec);

void draw_leaderboard(SDL_Texture *main_menu_bg_tex, SDL_Texture *back, SDL_Texture *leaderboard_player,
                      SDL_Rect leaderboard_player_rec, SDL_Rect back_rec);

void draw_map_picker(SDL_Texture *main_menu_bg_tex, SDL_Texture *ingame_name, SDL_Rect ingame_name_rec,
                     SDL_Texture *random_map_tex, SDL_Rect random_map, SDL_Texture *choose_dif_tex,
                     SDL_Rect choose_dif, SDL_Texture *back, SDL_Rect back_rec);

void draw_diff_pick(SDL_Texture *main_menu_bg_tex, SDL_Texture *ingame_name, SDL_Rect ingame_name_rec,
                    SDL_Texture *easy, SDL_Texture *medium, SDL_Texture *hard, SDL_Rect easy_rec, SDL_Rect medium_rec,
                    SDL_Rect hard_rec, SDL_Texture* back, SDL_Rect back_rec);

void draw_winner(SDL_Texture *main_menu_bg_tex, SDL_Texture *back_to_menu, SDL_Rect back_to_menu_rec);

void draw_map();

void selecting_bases(SDL_Event e);

void make_attack();

void make_march();

void apply_speed_point();

void stop_speed();

void draw_march();

void bot_movements(int index);

void make_potion();

void check_accidents();

void top_four(SDL_Texture *places_tex, SDL_Rect places_rec);

void check_winner();

void get_all_usernames();

void add_player();

struct player create_player();

int check_for_duplicate();

int compare_by_points(const void*, const void*);

void sort_players();

void add_point_to_player(int point);

void put_all_usernames_in_file();
