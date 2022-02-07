#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "functions.h"
#include "variables.h"


void Init(){
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    TTF_Init();
}

void Begin(){
    sdlWindow = SDL_CreateWindow("Test_Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                 SCREEN_WIDTH,SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1,
                                     SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    xeros = TTF_OpenFont("../fonts/xeros_theorem.ttf", 24);
    SDL_StartTextInput();

}

void End(){
    SDL_StopTextInput();
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);
    TTF_CloseFont(xeros);
    SDL_Quit();

}

void get_text_and_rect(SDL_Color color, int x, int y, int w, int h, char *text,
                       SDL_Texture** texture, SDL_Rect* rect) {
    SDL_Surface *surface;

    surface = TTF_RenderText_Solid(xeros, text, color);
    *texture = SDL_CreateTextureFromSurface(sdlRenderer, surface);
    SDL_FreeSurface(surface);
    rect->x = x; rect->y = y; rect->w = w; rect->h = h;
}

void get_img_and_rect(char* path, SDL_Texture** texture){
    SDL_Surface* surface = IMG_Load(path);
    *texture = SDL_CreateTextureFromSurface(sdlRenderer, surface);
    SDL_FreeSurface(surface);
}

SDL_Color color(int r, int g, int b, int a){
    SDL_Color col = {r, g, b, a};

    return col;
}

void xy_maker(Sint16 mid_x, Sint16 mid_y, int index){
    x[index][0] = mid_x - l;
    x[index][1] = mid_x - l / 2;
    x[index][2] = mid_x + l / 2;
    x[index][3] = mid_x + l;
    x[index][4] = mid_x + l / 2;
    x[index][5] = mid_x - l / 2;
    y[index][0] = mid_y;
    y[index][1] = mid_y - 86 * l / 100;
    y[index][2] = mid_y - 86 * l / 100;
    y[index][3] = mid_y;
    y[index][4] = mid_y + 86 * l / 100;
    y[index][5] = mid_y + 86 * l / 100;
    all_bases.base_x[index] = mid_x;
    all_bases.base_y[index] = mid_y;
}

void input_struct(){
    for(int i = 0; i < 10;i++){
        all_bases.base_id[i] = 0xaaffffff;
        all_bases.base_points[i] = 10;
        all_bases.being_attacked[i] = false;
        all_bases.points_speed[i] = 1;
    }
    for(int i = 0;i < 40;i++){
        for(int j = 0;j < 100;j++) {
            all_bases.marches[i].x[j] = 0;
            all_bases.marches[i].y[j] = 0;
            all_bases.marches[i].is_atk[j] = false;
        }
        all_bases.marches[i].vx = 0;
        all_bases.marches[i].vy = 0;
    }
    all_bases.base_id[0] = 0xaaffff46;
    all_bases.base_id[1] = 0xaaf010ff;
    all_bases.base_id[2] = 0xaae81815;
    all_bases.base_id[3] = 0xaa7a0a53;
}

void draw_map(){
    char number[5];
    for(int i = 0;i < 10;i++){
        SDL_Rect points_rec;
        if(i == 0){
            filledPolygonColor(sdlRenderer, x[i], y[i], 6, all_bases.base_id[i]);
            polygonColor(sdlRenderer, x[i], y[i], 6, 0xff000000);
        }
        else if(i == 1){
            filledPolygonColor(sdlRenderer, x[i], y[i], 6, all_bases.base_id[i]);
            polygonColor(sdlRenderer, x[i], y[i], 6, 0xff000000);
        }
        else if(i == 2){
            filledPolygonColor(sdlRenderer, x[i], y[i], 6, all_bases.base_id[i]);
            polygonColor(sdlRenderer, x[i], y[i], 6, 0xff000000);
        }
        else if(i == 3){
            filledPolygonColor(sdlRenderer, x[i], y[i], 6, all_bases.base_id[i]);
            polygonColor(sdlRenderer, x[i], y[i], 6, 0xff000000);
        }
        else{
            filledPolygonColor(sdlRenderer, x[i], y[i], 6, all_bases.base_id[i]);
            polygonColor(sdlRenderer, x[i], y[i], 6, 0xff000000);
        }
        if(all_bases.base_id[i] != 0xaaffffff){
            if(all_bases.base_id[i] == 0xaaffff46) {
                filledCircleColor(sdlRenderer, all_bases.base_x[i], all_bases.base_y[i], l / 2,
                                  0xffffff46);
            }
            else if(all_bases.base_id[i] == 0xaaf010ff){
                filledCircleColor(sdlRenderer, all_bases.base_x[i], all_bases.base_y[i], l / 2,
                                  0xfff010ff);
            }
            else if(all_bases.base_id[i] == 0xaae81815){
                filledCircleColor(sdlRenderer, all_bases.base_x[i], all_bases.base_y[i], l / 2,
                                  0xffe81815);
            }
            else{
                filledCircleColor(sdlRenderer, all_bases.base_x[i], all_bases.base_y[i], l / 2,
                                  0xff7a0a53);
            }
        }
        sprintf(number, "%d", all_bases.base_points[i]);
        get_text_and_rect(color(0, 0, 0, 255), all_bases.base_x[i] - SCREEN_WIDTH/100,
                          all_bases.base_y[i] - SCREEN_HEIGHT/100, 2*SCREEN_WIDTH/100, 2*SCREEN_HEIGHT/100,
                          number, &points_tex[i],&points_rec);
        SDL_RenderCopy(sdlRenderer, points_tex[i], NULL, &points_rec);
    }
}

void draw_start(SDL_Texture* start_bg_tex, SDL_Texture* logo_tex, SDL_Texture* name_tex, SDL_Texture* input_tex,
                SDL_Texture* submit_button, SDL_Rect logo_rec, SDL_Rect name_rec, SDL_Rect input_rec,
                SDL_Rect submit_button_rec){
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

void draw_diff_pick(SDL_Texture *main_menu_bg_tex, SDL_Texture *ingame_name, SDL_Rect ingame_name_rec,
                    SDL_Texture *easy, SDL_Texture *medium, SDL_Texture *hard, SDL_Rect easy_rec, SDL_Rect medium_rec,
                    SDL_Rect hard_rec, SDL_Texture* back, SDL_Rect back_rec){
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

void make_march(){
    for(int i = 0;i < total_marches;i++){
        if(point_adder%20 == 0) {
            if (all_bases.marches[i].total_soldiers > 0) {
                all_bases.marches[i].x[all_bases.marches[i].total_soldiers] +=
                        (Sint16)all_bases.base_x[all_bases.marches[i].src_index] +
                                (Sint16)all_bases.marches[i].vx;
                all_bases.marches[i].y[all_bases.marches[i].total_soldiers] +=
                        (Sint16)all_bases.base_y[all_bases.marches[i].src_index] +
                                (Sint16)all_bases.marches[i].vy;
                all_bases.marches[i].is_atk[all_bases.marches[i].total_soldiers] = true;
                all_bases.marches[i].total_soldiers--;
            }
        }
    }
}

void draw_march(){
    for(int i = 0;i < total_marches;i++){
        for(int j = 0;j < 100;j++){
            if(all_bases.marches[i].is_atk[j] == true){
                filledCircleColor(sdlRenderer, all_bases.marches[i].x[j],
                                  all_bases.marches[i].y[j], 7,
                                  all_bases.base_id[all_bases.marches[i].src_index]);
            }
        }
    }
}

void apply_speed_point(){
    for(int i = 0;i < 10;i++){
        if(all_bases.base_id[i] != 0xaaffffff) {
            if(point_adder%40 == 0 && all_bases.base_points[i] < 50) {
                if(all_bases.being_attacked[i] == false) {
                    all_bases.base_points[i] += all_bases.points_speed[i];
                }
            }
        }
        for(int j = 0;j < total_marches;j++){
            if(point_adder%20 == 0) {
                for (int z = 0; z < 100; z++) {
                    if (all_bases.marches[j].is_atk[z] == true) {
                        delta_y = (double)(all_bases.base_y[all_bases.marches[j].des_index]-all_bases.marches[j].y[z]);
                        delta_x = (double)(all_bases.base_x[all_bases.marches[j].des_index]-all_bases.marches[j].x[z]);
                        theta = atan(delta_y/delta_x);
                        all_bases.marches[j].vx = speed*cos(theta);
                        all_bases.marches[j].vy = speed*sin(theta);
                        if(delta_x < 0 && all_bases.marches[j].vx > 0){
                            all_bases.marches[j].vx *= -1;
                        }
                        if(delta_x > 0 && all_bases.marches[j].vx < 0){
                            all_bases.marches[j].vx *= -1;
                        }
                        if(delta_y < 0 && all_bases.marches[j].vy > 0){
                            all_bases.marches[j].vy *= -1;
                        }
                        if(delta_y > 0 && all_bases.marches[j].vy < 0){
                            all_bases.marches[j].vy *= -1;
                        }
                        all_bases.marches[j].x[z] += all_bases.marches[j].vx;
                        all_bases.marches[j].y[z] += all_bases.marches[j].vy;
                    }
                }
            }
        }
    }
}

void stop_speed(){
    for(int i = 0;i < total_marches;i++){
        for(int j = 0;j < 100;j++){
            if(all_bases.marches[i].is_atk[j] == true){
                if((all_bases.marches[i].vy == 0 &&
                        abs(all_bases.marches[i].x[j]-all_bases.base_x[all_bases.marches[i].des_index]) < l/2) ||
                        (all_bases.marches[i].vx == 0 &&
                        abs(all_bases.marches[i].y[j]-all_bases.base_y[all_bases.marches[i].des_index]) < l/2) ||
                        (abs(all_bases.marches[i].x[j]-all_bases.base_x[all_bases.marches[i].des_index]) < l/2 &&
                        abs(all_bases.marches[i].y[j]-all_bases.base_y[all_bases.marches[i].des_index]) < l/2)){
                    all_bases.marches[i].is_atk[j] = false;
                    all_bases.marches[i].x[j] = 0;
                    all_bases.marches[i].y[j] = 0;
                    all_bases.being_attacked[all_bases.marches[i].des_index] = true;
                    if(all_bases.base_id[all_bases.marches[i].src_index] ==
                            all_bases.base_id[all_bases.marches[i].des_index]){
                        all_bases.base_points[all_bases.marches[i].des_index]++;
                    }
                    else{
                        if(all_bases.base_points[all_bases.marches[i].des_index] < 2){
                            all_bases.base_id[all_bases.marches[i].des_index] =
                                    all_bases.base_id[all_bases.marches[i].src_index];
                        }
                        else {
                            all_bases.base_points[all_bases.marches[i].des_index]--;
                        }

                    }
                    if(j == 1){
                        all_bases.being_attacked[all_bases.marches[i].des_index] = false;
                    }
                }
            }
        }
    }
}

void selecting_bases(SDL_Event e, int* first, int* second){
    for(int i = 0;i < 10;i++){
        if(abs(e.button.x - all_bases.base_x[i]) < l &&
           abs(e.button.y - all_bases.base_y[i]) < l){
            if(*first == -1){
                if(all_bases.base_id[i] == 0xaaffff46) {
                    *first = i;
                }
            }
            else{
                *second = i;
                if(*second != *first) {
                    delta_y = (double) (all_bases.base_y[*second] - all_bases.base_y[*first]);
                    delta_x = (double) (all_bases.base_x[*second] - all_bases.base_x[*first]);
                    theta = atan(delta_y / delta_x);
                    all_bases.marches[total_marches].vx = speed * cos(theta);
                    all_bases.marches[total_marches].vy = speed * sin(theta);
                    if (delta_x < 0 && all_bases.marches[total_marches].vx > 0) {
                        all_bases.marches[total_marches].vx *= -1;
                    }
                    if (delta_x > 0 && all_bases.marches[total_marches].vx < 0) {
                        all_bases.marches[total_marches].vx *= -1;
                    }
                    if (delta_y < 0 && all_bases.marches[total_marches].vy > 0) {
                        all_bases.marches[total_marches].vy *= -1;
                    }
                    if (delta_y > 0 && all_bases.marches[total_marches].vy < 0) {
                        all_bases.marches[total_marches].vy *= -1;
                    }
                    all_bases.marches[total_marches].total_soldiers = all_bases.base_points[*first];
                    all_bases.base_points[*first] = 0;
                    all_bases.marches[total_marches].src_index = *first;
                    all_bases.marches[total_marches].des_index = *second;
                    total_marches++;
                    *first = -1;
                    *second = -1;
                }
            }
            break;
        }
    }
}