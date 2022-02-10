#include "functions.h"
#include "variables.h"

void draw_start(SDL_Texture* start_bg_tex, SDL_Texture* logo_tex, SDL_Texture* name_tex, SDL_Texture* input_tex,
                SDL_Texture* submit_button, SDL_Rect logo_rec, SDL_Rect name_rec, SDL_Rect input_rec,
                SDL_Rect submit_button_rec){
    SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0x00, 0x00, 0xff);
    SDL_RenderClear(sdlRenderer);
    SDL_RenderCopy(sdlRenderer, start_bg_tex, NULL, NULL);
    SDL_RenderCopy(sdlRenderer, logo_tex, NULL, &logo_rec);
    SDL_RenderCopy(sdlRenderer, name_tex, NULL, &name_rec);
    SDL_RenderCopy(sdlRenderer, input_tex, NULL, &input_rec);
    boxColor(sdlRenderer, SCREEN_WIDTH * 27 / 100, SCREEN_HEIGHT * 55 / 100,
             SCREEN_WIDTH * 73 / 100, SCREEN_HEIGHT * 56 / 100, 0xfff010ff);
    boxColor(sdlRenderer, SCREEN_WIDTH * 27 / 100, SCREEN_HEIGHT * 64 / 100,
             SCREEN_WIDTH * 73 / 100, SCREEN_HEIGHT * 65 / 100, 0xfff010ff);
    boxColor(sdlRenderer, SCREEN_WIDTH * 42 / 100, SCREEN_HEIGHT * 66 / 100,
             SCREEN_WIDTH * 58 / 100, SCREEN_HEIGHT * 72 / 100, 0xfff010ff);
    SDL_RenderCopy(sdlRenderer, submit_button, NULL, &submit_button_rec);
}

void draw_main_menu(SDL_Texture* main_menu_bg_tex, SDL_Texture* new_game, SDL_Texture* con_game,
                    SDL_Texture* leaderboard, SDL_Texture* back, SDL_Texture* ingame_name, SDL_Rect new_game_rec,
                    SDL_Rect con_game_rec, SDL_Rect leaderboard_rec, SDL_Rect back_rec, SDL_Rect ingame_name_rec){
    SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0x00, 0xff, 0xff);
    SDL_RenderClear(sdlRenderer);
    SDL_RenderCopy(sdlRenderer, main_menu_bg_tex, NULL, NULL);
    boxColor(sdlRenderer, SCREEN_WIDTH*30/100, SCREEN_HEIGHT*25/100,
             SCREEN_WIDTH*70/100, SCREEN_HEIGHT*35/100, 0xffffff44);
    boxColor(sdlRenderer, SCREEN_WIDTH*30/100, SCREEN_HEIGHT*40/100,
             SCREEN_WIDTH*70/100, SCREEN_HEIGHT*50/100, 0xffffff44);
    boxColor(sdlRenderer, SCREEN_WIDTH*25/100, SCREEN_HEIGHT*55/100,
             SCREEN_WIDTH*75/100, SCREEN_HEIGHT*65/100, 0xffffff44);
    boxColor(sdlRenderer, SCREEN_WIDTH*40/100, SCREEN_HEIGHT*70/100,
             SCREEN_WIDTH*60/100, SCREEN_HEIGHT*80/100, 0xffffff44);
    SDL_RenderCopy(sdlRenderer, new_game, NULL, &new_game_rec);
    SDL_RenderCopy(sdlRenderer, con_game, NULL, &con_game_rec);
    SDL_RenderCopy(sdlRenderer, leaderboard, NULL, &leaderboard_rec);
    SDL_RenderCopy(sdlRenderer, back, NULL, &back_rec);
    SDL_RenderCopy(sdlRenderer, ingame_name, NULL, &ingame_name_rec);
}

void draw_map_picker(SDL_Texture *main_menu_bg_tex, SDL_Texture *ingame_name, SDL_Rect ingame_name_rec,
                     SDL_Texture *random_map_tex, SDL_Rect random_map, SDL_Texture *choose_dif_tex,
                     SDL_Rect choose_dif, SDL_Texture *back, SDL_Rect back_rec){
    SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0x00, 0xff, 0xff);
    SDL_RenderClear(sdlRenderer);
    SDL_RenderCopy(sdlRenderer, main_menu_bg_tex, NULL, NULL);
    SDL_RenderCopy(sdlRenderer, ingame_name, NULL, &ingame_name_rec);
    boxColor(sdlRenderer, SCREEN_WIDTH*28/100, SCREEN_HEIGHT*25/100,
             SCREEN_WIDTH*72/100, SCREEN_HEIGHT*35/100, 0xffffff44);
    boxColor(sdlRenderer, SCREEN_WIDTH*20/100, SCREEN_HEIGHT*40/100,
             SCREEN_WIDTH*80/100, SCREEN_HEIGHT*50/100, 0xffffff44);
    boxColor(sdlRenderer, SCREEN_WIDTH*40/100, SCREEN_HEIGHT*70/100,
             SCREEN_WIDTH*60/100, SCREEN_HEIGHT*80/100, 0xffffff44);
    SDL_RenderCopy(sdlRenderer, random_map_tex, NULL, &random_map);
    SDL_RenderCopy(sdlRenderer, choose_dif_tex, NULL, &choose_dif);
    SDL_RenderCopy(sdlRenderer, back, NULL, &back_rec);
}

void draw_leaderboard(SDL_Texture *main_menu_bg_tex, SDL_Texture *back, SDL_Texture *leaderboard_player,
                      SDL_Rect leaderboard_player_rec, SDL_Rect back_rec){
    SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0x00, 0xff, 0xff);
    SDL_RenderClear(sdlRenderer);
    SDL_RenderCopy(sdlRenderer, main_menu_bg_tex, NULL, NULL);
    boxColor(sdlRenderer, SCREEN_WIDTH*40/100, SCREEN_HEIGHT*70/100,
             SCREEN_WIDTH*60/100, SCREEN_HEIGHT*80/100, 0xffffff44);
    boxColor(sdlRenderer, SCREEN_WIDTH*15/100, SCREEN_HEIGHT*15/100,
             SCREEN_WIDTH*85/100, SCREEN_HEIGHT*65/100, 0xffffff44);
    SDL_RenderCopy(sdlRenderer, back, NULL, &back_rec);
    for(int i = 0, j = 2;i < count_players;i++, j++){
        get_text_and_rect(color(0, 0, 0, 255), 23*SCREEN_WIDTH/100,
                          (j)*8*SCREEN_HEIGHT/100, strlen(all_players[i].username)*3*SCREEN_WIDTH/100,
                          7*SCREEN_HEIGHT/100,all_players[i].username, &leaderboard_player,
                          &leaderboard_player_rec);
        SDL_RenderCopy(sdlRenderer, leaderboard_player, NULL,
                       &leaderboard_player_rec);
        sprintf(number, "%d", all_players[i].ranking);
        strcat(number, ".");
        get_text_and_rect(color(0, 0, 0, 255), 18*SCREEN_WIDTH/100,
                          (j)*8*SCREEN_HEIGHT/100, 3*SCREEN_WIDTH/100, 7*SCREEN_HEIGHT/100,
                          number, &leaderboard_player,&leaderboard_player_rec);
        SDL_RenderCopy(sdlRenderer, leaderboard_player, NULL,
                       &leaderboard_player_rec);
        sprintf(number, "%d", all_players[i].total_pt);
        get_text_and_rect(color(0, 0, 0, 255), 72*SCREEN_WIDTH/100,
                          (j)*8*SCREEN_HEIGHT/100, strlen(number)*3*SCREEN_WIDTH/100,
                          7*SCREEN_HEIGHT/100,number, &leaderboard_player,
                          &leaderboard_player_rec);
        SDL_RenderCopy(sdlRenderer, leaderboard_player, NULL,
                       &leaderboard_player_rec);
    }
}

void draw_diff_pick(SDL_Texture *main_menu_bg_tex, SDL_Texture *ingame_name, SDL_Rect ingame_name_rec,
                    SDL_Texture *easy, SDL_Texture *medium, SDL_Texture *hard, SDL_Rect easy_rec, SDL_Rect medium_rec,
                    SDL_Rect hard_rec, SDL_Texture* back, SDL_Rect back_rec){
    SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0x00, 0xff, 0xff);
    SDL_RenderClear(sdlRenderer);
    SDL_RenderCopy(sdlRenderer, main_menu_bg_tex, NULL, NULL);
    SDL_RenderCopy(sdlRenderer, ingame_name, NULL, &ingame_name_rec);
    boxColor(sdlRenderer, SCREEN_WIDTH*35/100, SCREEN_HEIGHT*25/100,
             SCREEN_WIDTH*65/100, SCREEN_HEIGHT*35/100, 0xffffff44);
    boxColor(sdlRenderer, SCREEN_WIDTH*35/100, SCREEN_HEIGHT*40/100,
             SCREEN_WIDTH*65/100, SCREEN_HEIGHT*50/100, 0xffffff44);
    boxColor(sdlRenderer, SCREEN_WIDTH*35/100, SCREEN_HEIGHT*55/100,
             SCREEN_WIDTH*65/100, SCREEN_HEIGHT*65/100, 0xffffff44);
    boxColor(sdlRenderer, SCREEN_WIDTH*40/100, SCREEN_HEIGHT*70/100,
             SCREEN_WIDTH*60/100, SCREEN_HEIGHT*80/100, 0xffffff44);
    SDL_RenderCopy(sdlRenderer, easy, NULL, &easy_rec);
    SDL_RenderCopy(sdlRenderer, medium, NULL, &medium_rec);
    SDL_RenderCopy(sdlRenderer, hard, NULL, &hard_rec);
    SDL_RenderCopy(sdlRenderer, back, NULL, &back_rec);
}

void draw_winner(SDL_Texture *main_menu_bg_tex, SDL_Texture *back_to_menu, SDL_Rect back_to_menu_rec){
    SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(sdlRenderer);
    SDL_RenderCopy(sdlRenderer, main_menu_bg_tex, NULL, NULL);
    SDL_RenderCopy(sdlRenderer, congrats, NULL, &congrats_rec);
    boxColor(sdlRenderer, SCREEN_WIDTH*33/100, SCREEN_HEIGHT*70/100,
             SCREEN_WIDTH*67/100, SCREEN_HEIGHT*80/100, 0xffffff44);
    SDL_RenderCopy(sdlRenderer, winning_point, NULL, &winning_point_rec);
    SDL_RenderCopy(sdlRenderer, back_to_menu, NULL, &back_to_menu_rec);
}


