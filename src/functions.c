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
    for(int i = 0;i < 100;i++){
        for(int j = 0;j < 200;j++) {
            all_bases.marches[i].x[j] = 0;
            all_bases.marches[i].y[j] = 0;
            all_bases.marches[i].is_atk[j] = false;
        }
        all_bases.marches[i].vx = 0;
        all_bases.marches[i].vy = 0;
        marches_state[i] = false;
    }
    all_bases.base_id[0] = 0xaaffff46;
    all_bases.base_id[1] = 0xaaf010ff;
    all_bases.base_id[2] = 0xaae81815;
    all_bases.base_id[3] = 0xaa7a0a53;
    for(int i = 0;i < 4;i++){
        all_potions.x[i] = 0;
        all_potions.y[i] = 0;
        all_potions.is_active[i] = false;
        all_potions.id[i] = -1;
        all_potions.timer[i] = -1;
    }
}

void draw_map(){
    for(int i = 0;i < 10;i++){
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
                          number, &points_tex,&points_rec);
        SDL_RenderCopy(sdlRenderer, points_tex, NULL, &points_rec);
    }
    if(all_potions.is_active[0]) {
        potions_rec.x = all_potions.x[0];
        potions_rec.y = all_potions.y[0];
        potions_rec.w = 50;
        potions_rec.h = 50;
        get_img_and_rect("../images/potion1.png", &potions_tex);
        SDL_RenderCopy(sdlRenderer, potions_tex, NULL, &potions_rec);
    }
    else if(all_potions.is_active[1]) {
        potions_rec.x = all_potions.x[1];
        potions_rec.y = all_potions.y[1];
        potions_rec.w = 50;
        potions_rec.h = 50;
        get_img_and_rect("../images/potion2.png", &potions_tex);
        SDL_RenderCopy(sdlRenderer, potions_tex, NULL, &potions_rec);
    }
    else if(all_potions.is_active[2]) {
        potions_rec.x = all_potions.x[2];
        potions_rec.y = all_potions.y[2];
        potions_rec.w = 50;
        potions_rec.h = 50;
        get_img_and_rect("../images/potion3.png", &potions_tex);
        SDL_RenderCopy(sdlRenderer, potions_tex, NULL, &potions_rec);
    }
    else if(all_potions.is_active[3]) {
        potions_rec.x = all_potions.x[3];
        potions_rec.y = all_potions.y[3];
        potions_rec.w = 50;
        potions_rec.h = 50;
        get_img_and_rect("../images/potion4.png", &potions_tex);
        SDL_RenderCopy(sdlRenderer, potions_tex, NULL, &potions_rec);
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
    for(int i = 0;i < 100;i++){
        if(point_adder%1 == 0) {
            if (all_bases.marches[i].total_soldiers > 0) {
                all_bases.marches[i].x[all_bases.marches[i].total_soldiers] +=
                        (Sint16)all_bases.base_x[all_bases.marches[i].src_index] + (Sint16)all_bases.marches[i].vx;
                all_bases.marches[i].y[all_bases.marches[i].total_soldiers] +=
                        (Sint16)all_bases.base_y[all_bases.marches[i].src_index] + (Sint16)all_bases.marches[i].vy;
                all_bases.marches[i].is_atk[all_bases.marches[i].total_soldiers] = true;
                all_bases.marches[i].total_soldiers--;
            }
        }
    }
}

void draw_march(){
    for(int i = 0;i < 100;i++){
        for(int j = 0;j < 200;j++){
            if(all_bases.marches[i].is_atk[j] == true){
                filledCircleColor(sdlRenderer, all_bases.marches[i].x[j],all_bases.marches[i].y[j],
                                  7,all_bases.marches[i].id);
            }
        }
    }
}

void apply_speed_point(){
    for(int i = 0;i < 10;i++){
        if(all_bases.base_id[i] != 0xaaffffff) {
            if(point_adder%2 == 0 && all_bases.base_points[i] < 50) {
                all_bases.base_points[i] += all_bases.points_speed[i];
            }
        }
        for(int j = 0;j < 100;j++){
            if(point_adder%1 == 0) {
                for (int z = 0; z < 200; z++) {
                    if (all_bases.marches[j].is_atk[z] == true) {
                        delta_y = (double)(all_bases.base_y[all_bases.marches[j].des_index]-all_bases.marches[j].y[z]);
                        delta_x = (double)(all_bases.base_x[all_bases.marches[j].des_index]-all_bases.marches[j].x[z]);
                        theta = atan(delta_y/delta_x);
                        all_bases.marches[j].vx = speed*cos(theta);
                        all_bases.marches[j].vy = speed*sin(theta);
                        if(delta_x < 0 && all_bases.marches[j].vx > 0){
                            all_bases.marches[j].vx *= -1;
                        }
                        else if(delta_x > 0 && all_bases.marches[j].vx < 0){
                            all_bases.marches[j].vx *= -1;
                        }
                        if(delta_y < 0 && all_bases.marches[j].vy > 0){
                            all_bases.marches[j].vy *= -1;
                        }
                        else if(delta_y > 0 && all_bases.marches[j].vy < 0){
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
    for(int i = 0;i < 100;i++){
        for(int j = 0;j < 200;j++){
            if(all_bases.marches[i].is_atk[j] == true){
                if((abs(all_bases.marches[i].x[j]-all_bases.base_x[all_bases.marches[i].des_index]) < l/2 &&
                        abs(all_bases.marches[i].y[j]-all_bases.base_y[all_bases.marches[i].des_index]) < l/2)){
                    all_bases.marches[i].is_atk[j] = false;
                    all_bases.marches[i].x[j] = 0;
                    all_bases.marches[i].y[j] = 0;
                    if(all_bases.marches[i].id == all_bases.base_id[all_bases.marches[i].des_index]){
                        all_bases.base_points[all_bases.marches[i].des_index]++;
                    }
                    else{
                        if(all_bases.base_points[all_bases.marches[i].des_index] < 2){
                            all_bases.base_id[all_bases.marches[i].des_index] = all_bases.marches[i].id;
                        }
                        else {
                            if(all_bases.base_id[all_bases.marches[i].des_index] == 0xaaffffff) {
                                all_bases.base_points[all_bases.marches[i].des_index]--;
                            }
                            else{
                                all_bases.base_points[all_bases.marches[i].des_index] -= 2;
                            }
                        }

                    }
                    if(j <= 1){
                        all_bases.being_attacked[all_bases.marches[i].des_index] = false;
                        marches_state[i] = false;
                    }
                }
            }
        }
    }
}

void make_attack(int* first, int* second){
    if(all_bases.base_points[*first] > 0) {
        delta_y = (double) (all_bases.base_y[*second] - all_bases.base_y[*first]);
        delta_x = (double) (all_bases.base_x[*second] - all_bases.base_x[*first]);
        theta = atan(delta_y / delta_x);
        for(int i = 0;i < 100;i++){
            if(marches_state[i] == false){
                printf("%d|", i);
                all_bases.marches[i].vx = speed * cos(theta);
                all_bases.marches[i].vy = speed * sin(theta);
                if (delta_x < 0 && all_bases.marches[i].vx > 0) {
                    all_bases.marches[i].vx *= -1;
                }
                else if (delta_x > 0 && all_bases.marches[i].vx < 0) {
                    all_bases.marches[i].vx *= -1;
                }
                if (delta_y < 0 && all_bases.marches[i].vy > 0) {
                    all_bases.marches[i].vy *= -1;
                }
                else if (delta_y > 0 && all_bases.marches[i].vy < 0) {
                    all_bases.marches[i].vy *= -1;
                }
                all_bases.marches[i].total_soldiers = all_bases.base_points[*first];
                all_bases.base_points[*first] = 0;
                all_bases.being_attacked[*second] = true;
                all_bases.marches[i].src_index = *first;
                all_bases.marches[i].des_index = *second;
                all_bases.marches[i].id = all_bases.base_id[*first];
                marches_state[i] = true;
                *first = -1;
                *second = -1;
                break;
            }
        }
    }
}

void bot_movements(int* first, int* second, int index){
    if (all_bases.base_id[index] != 0xaaffff46 && all_bases.base_id[index] != 0xaaffffff) {
        for (int i = 0; i < 10; i++) {
            if (i != index && all_bases.base_id[i] == 0xaaffffff && all_bases.being_attacked[i] == false){
                *first = index;
                *second = i;
                make_attack(first, second);
                break;
            }
            else if(i != index && all_bases.base_id[i] == all_bases.base_id[index] &&
                    all_bases.being_attacked[i] == true && all_bases.base_points[i] < all_bases.base_points[index]){
                *first = index;
                *second = i;
                make_attack(first, second);
                break;
            }
            else if(i != index && all_bases.base_points[index] >= 20 && all_bases.base_id[i] !=
                    all_bases.base_id[index] && all_bases.being_attacked[i] == false &&
                    all_bases.base_points[index] > all_bases.base_points[i]+10 && leader_base[0] > 4){
                *first = index;
                *second = i;
                make_attack(first, second);
                break;
            }
            else if(i !=index && point_adder > 1000 && leader_base[0] < 4 && all_bases.base_id[i] == 0xaaffff46 &&
                    all_bases.being_attacked[i] == false){
                *first = index;
                *second = i;
                make_attack(first, second);
                break;
            }
        }
    }
}

void check_accidents(){
    for(int i = 0;i < 99;i++){
        for(int j = i+1;j < 100;j++){
            for(int k = 0;k < 200;k++){
                for(int z = 0;z < 200;z++){
                    if(all_bases.marches[i].is_atk[k] && all_bases.marches[j].is_atk[z] && all_bases.marches[i].id !=
                       all_bases.marches[j].id) {
                        if (abs(all_bases.marches[i].x[k] - all_bases.marches[j].x[z]) < 14 &&
                            abs(all_bases.marches[i].y[k] - all_bases.marches[j].y[z]) < 14) {
                            all_bases.marches[i].x[k] = 0;
                            all_bases.marches[i].y[k] = 0;
                            all_bases.marches[j].x[z] = 0;
                            all_bases.marches[j].x[z] = 0;
                            all_bases.marches[i].is_atk[k] = false;
                            all_bases.marches[j].is_atk[z] = false;
                        }
                    }
                }
            }
        }
    }
}

void selecting_bases(SDL_Event e, int* first, int* second){
    for(int i = 0;i < 10;i++){
        if(abs(e.button.x - all_bases.base_x[i]) < l && abs(e.button.y - all_bases.base_y[i]) < l){
            if(*first == -1 && all_bases.base_id[i] == 0xaaffff46){
                *first = i;
            }
            else{
                *second = i;
                if(*second != *first) {
                    make_attack(first, second);
                }
            }
            break;
        }
    }
}

void top_four(SDL_Texture *places_tex, SDL_Rect places_rec){
    for(int i = 0;i < 4;i++){
        leader_base[i] = 0;
    }
    for(int i = 0;i < 10;i++){
        if(all_bases.base_id[i] == 0xaaffff46){
            leader_base[0]++;
        }
        else if(all_bases.base_id[i] == 0xaaf010ff){
            leader_base[1]++;
        }
        else if(all_bases.base_id[i] == 0xaae81815){
            leader_base[2]++;
        }
        else if(all_bases.base_id[i] == 0xaa7a0a53){
            leader_base[3]++;
        }
    }
    int first = -1;
    if(leader_base[0] >= leader_base[1] && leader_base[0] >= leader_base[2] && leader_base[0] >= leader_base[3]){
        first = 0;
    }
    else if(leader_base[1] >= leader_base[0] && leader_base[1] >= leader_base[2] && leader_base[1] >= leader_base[3]){
        first = 1;
    }
    else if(leader_base[2] >= leader_base[0] && leader_base[2] >= leader_base[1] && leader_base[2] >= leader_base[3]){
        first = 2;
    }
    else{
        first = 3;
    }
    boxColor(sdlRenderer, 83*SCREEN_WIDTH/100, SCREEN_HEIGHT/100, 99*SCREEN_WIDTH/100,
             7*SCREEN_HEIGHT/100, 0xffffffff);
    sprintf(number, "%d", leader_base[first]);
    if(first == 0) {
        get_text_and_rect(color(70, 255, 255, 255), 85 * SCREEN_WIDTH / 100,
                          2 * SCREEN_HEIGHT / 100,6 * SCREEN_WIDTH / 100, 4 * SCREEN_HEIGHT / 100,
                          "You", &places_tex,&places_rec);
        SDL_RenderCopy(sdlRenderer, places_tex, NULL, &places_rec);
        get_text_and_rect(color(70, 255, 255, 255), 95*SCREEN_WIDTH/100, 2*SCREEN_HEIGHT/100,
                          2*SCREEN_WIDTH/100, 4*SCREEN_HEIGHT/100, number, &places_tex,
                          &places_rec);
        SDL_RenderCopy(sdlRenderer, places_tex, NULL, &places_rec);
    }
    else if(first == 1) {
        get_text_and_rect(color(255, 160, 240, 255), 85 * SCREEN_WIDTH / 100,
                          2 * SCREEN_HEIGHT / 100,8 * SCREEN_WIDTH / 100, 4 * SCREEN_HEIGHT / 100,
                          "Pink", &places_tex,&places_rec);
        SDL_RenderCopy(sdlRenderer, places_tex, NULL, &places_rec);
        get_text_and_rect(color(255, 160, 240, 255), 95*SCREEN_WIDTH/100, 2*SCREEN_HEIGHT/100,
                          2*SCREEN_WIDTH/100, 4*SCREEN_HEIGHT/100, number, &places_tex,
                          &places_rec);
        SDL_RenderCopy(sdlRenderer, places_tex, NULL, &places_rec);
    }
    else if(first == 2) {
        get_text_and_rect(color(21, 24, 232, 255), 85 * SCREEN_WIDTH / 100,
                          2 * SCREEN_HEIGHT / 100,8 * SCREEN_WIDTH / 100, 4 * SCREEN_HEIGHT / 100,
                          "Blue", &places_tex,&places_rec);
        SDL_RenderCopy(sdlRenderer, places_tex, NULL, &places_rec);
        get_text_and_rect(color(21, 24, 232, 255), 95*SCREEN_WIDTH/100, 2*SCREEN_HEIGHT/100,
                          2*SCREEN_WIDTH/100, 4*SCREEN_HEIGHT/100, number, &places_tex,
                          &places_rec);
        SDL_RenderCopy(sdlRenderer, places_tex, NULL, &places_rec);
    }
    else if(first == 3) {
        get_text_and_rect(color(83, 10, 122, 255), 85 * SCREEN_WIDTH / 100,
                          2 * SCREEN_HEIGHT / 100,9 * SCREEN_WIDTH / 100, 4 * SCREEN_HEIGHT / 100,
                          "Purple", &places_tex,&places_rec);
        SDL_RenderCopy(sdlRenderer, places_tex, NULL, &places_rec);

        get_text_and_rect(color(83, 10, 122, 255), 95*SCREEN_WIDTH/100, 2*SCREEN_HEIGHT/100,
                          2*SCREEN_WIDTH/100, 4*SCREEN_HEIGHT/100, number, &places_tex,
                          &places_rec);
        SDL_RenderCopy(sdlRenderer, places_tex, NULL, &places_rec);
    }
}

void check_winner(){
    int flag = 0;
    for(int i = 0;i < 10;i++){
        if(all_bases.base_id[i] == 0xaaffff46){
            flag++;
        }
    }
    if(flag == 10){
        won = true;
        goto_game = false;
        goto_winner = true;
    }
    else if(flag == 0){
        won = false;
        goto_game = false;
        goto_winner = true;
    }
}

void add_point(){

}

void get_all_usernames(){
    FILE* f = fopen("username.txt", "r");
    if(f == NULL){fprintf(stderr, "couldn't open username file");
        exit(1);
    }
    for(int i = 0;!feof(f);i++){
        fscanf(f, "%d %d %[^\n]s", &all_players[i].total_pt, &all_players[i].ranking,
               all_players[i].username);
        count_players = i;
    }
    fclose(f);
}

void put_in_file(){
    remove("username.txt");
    FILE* f = fopen("username.txt", "w");
    if(f == NULL){fprintf(stderr, "couldn't open username file");
        exit(1);
    }
    for(int i = 0;i <= count_players;i++){
        fprintf(f, "%d %d %s\n", all_players[i].total_pt, all_players[i].ranking,
               all_players[i].username);
    }
    fclose(f);
}

player create_player(){
    player new_player;
    strcpy(new_player.username, username);
    new_player.ranking = 0;
    new_player.total_pt = 0;
    return new_player;
}

int comp(const void* first, const void* second){
    player* p1 = (player*)first;
    player* p2 = (player*)second;

 return p2->total_pt - p1->total_pt;
}

void sort_players(){
    qsort(all_players, count_players, sizeof(player), comp);
    for(int i = 0;i <= count_players;i++){
        all_players[i].ranking = i+1;
    }
}

int comp_duplicate(const void* first, const void* second){
    player* p1 = (player*)first;
    player* p2 = (player*)second;

 return strcmp(p2->username, p1->username);
}

void rmv_duplicate(){
    for(int i = 0;i <= count_players;i++){
        if (!strcmp(all_players[i].username, all_players[i+1].username)) {
            if (all_players[i].total_pt != 0) {
                strcpy(all_players[i+1].username, "\0");
            } else {
                strcpy(all_players[i].username, "\0");
            }
        }
        qsort(all_players, count_players + 1, sizeof(player), comp);
        qsort(all_players, count_players + 1, sizeof(player), comp_duplicate);
    }
    int tmp_count = count_players;
    for(int i = tmp_count; i >= 0;i--){
        if(!strcmp(all_players[i].username, "\0")){
            count_players--;
            break;
        }
    }
}

void add_player(){
    all_players[count_players] = create_player();
    count_players++;
    sort_players();
}

void make_potion(){
    int tmp_ran1 = rand()%10, tmp_ran2 = (tmp_ran1+3)%10;
    switch (potion_ran) {
        case 0:
            if(!all_potions.is_active[potion_ran] && !potion_active){
                all_potions.x[potion_ran] = (all_bases.base_x[tmp_ran1]+all_bases.base_x[tmp_ran2])/2;
                all_potions.y[potion_ran] = (all_bases.base_x[tmp_ran1]+all_bases.base_y[tmp_ran2])/2;
                for(int i = 0;i < 100;i++){
                    for(int j = 0;j < 200;j++){
                        if(abs(all_bases.marches[i].x[j] - all_potions.x[potion_ran]) < 50 &&
                                abs(all_bases.marches[i].y[j] - all_potions.y[potion_ran]) < 50){
                            all_potions.is_active[potion_ran] = true;
                            all_potions.timer[potion_ran] = 10;
                            all_potions.id[potion_ran] = all_bases.marches[i].id;
                            for(int k = 0;k < 100;k++){
                                if(all_bases.marches[k].id == all_potions.id[potion_ran]){
                                    all_bases.marches[k].vx *= 2;
                                    all_bases.marches[k].vy *= 2;
                                }
                            }
                            potion_ran++;
                            potion_ran %= 4;
                            potion_active = true;
                            return;
                        }
                    }
                }
            }
            else if((all_potions.is_active[potion_ran] && all_potions.timer[potion_ran] > 0)){
                for(int k = 0;k < 100;k++){
                    if(all_bases.marches[k].id == all_potions.id[potion_ran]){
                        all_bases.marches[k].vx *= 2;
                        all_bases.marches[k].vy *= 2;
                    }
                }
                if(point_adder%30 == 0){
                    all_potions.timer[potion_ran]--;
                }
            }
            else if(all_potions.timer[potion_ran] == 0){
                all_potions.is_active[potion_ran] = false;
                all_potions.timer[potion_ran] = -1;
                all_potions.id[potion_ran] = -1;
                for(int k = 0;k < 100;k++){
                    if(all_bases.marches[k].id == all_potions.id[potion_ran]){
                        all_bases.marches[k].vx *= 1/2;
                        all_bases.marches[k].vy *= 1/2;
                    }
                }
                potion_active = false;
            }
            break;
        case 1:
            if(!all_potions.is_active[potion_ran] && !potion_active){
                all_potions.x[potion_ran] = (all_bases.base_x[tmp_ran1]+all_bases.base_x[tmp_ran2])/2;
                all_potions.y[potion_ran] = (all_bases.base_x[tmp_ran1]+all_bases.base_y[tmp_ran2])/2;
                for(int i = 0;i < 100;i++){
                    for(int j = 0;j < 200;j++){
                        if(abs(all_bases.marches[i].x[j] - all_potions.x[potion_ran]) < 50 &&
                           abs(all_bases.marches[i].y[j] - all_potions.y[potion_ran]) < 50){
                            all_potions.is_active[potion_ran] = true;
                            all_potions.timer[potion_ran] = 10;
                            all_potions.id[potion_ran] = all_bases.marches[i].id;
                            for(int k = 0;k < 100;k++){
                                if(all_bases.marches[k].id == all_potions.id[potion_ran]){
                                    all_bases.marches[k].vx *= 2;
                                    all_bases.marches[k].vy *= 2;
                                }
                            }
                            potion_ran++;
                            potion_ran %= 4;
                            potion_active = true;
                            return;
                        }
                    }
                }
            }
            else if((all_potions.is_active[potion_ran] && all_potions.timer[potion_ran] > 0)){
                for(int k = 0;k < 100;k++){
                    if(all_bases.marches[k].id == all_potions.id[potion_ran]){
                        all_bases.marches[k].vx *= 2;
                        all_bases.marches[k].vy *= 2;
                    }
                }
                if(point_adder%30 == 0){
                    all_potions.timer[potion_ran]--;
                }
            }
            else if(all_potions.timer[potion_ran] == 0){
                all_potions.is_active[potion_ran] = false;
                all_potions.timer[potion_ran] = -1;
                all_potions.id[potion_ran] = -1;
                for(int k = 0;k < 100;k++){
                    if(all_bases.marches[k].id == all_potions.id[potion_ran]){
                        all_bases.marches[k].vx *= 1/2;
                        all_bases.marches[k].vy *= 1/2;
                    }
                }
                potion_active = false;
            }
            break;
        case 2:
            if(!all_potions.is_active[potion_ran] && !potion_active){
                all_potions.x[potion_ran] = (all_bases.base_x[tmp_ran1]+all_bases.base_x[tmp_ran2])/2;
                all_potions.y[potion_ran] = (all_bases.base_x[tmp_ran1]+all_bases.base_y[tmp_ran2])/2;
                for(int i = 0;i < 100;i++){
                    for(int j = 0;j < 200;j++){
                        if(abs(all_bases.marches[i].x[j] - all_potions.x[potion_ran]) < 50 &&
                           abs(all_bases.marches[i].y[j] - all_potions.y[potion_ran]) < 50){
                            all_potions.is_active[potion_ran] = true;
                            all_potions.timer[potion_ran] = 10;
                            all_potions.id[potion_ran] = all_bases.marches[i].id;
                            for(int k = 0;k < 100;k++){
                                if(all_bases.marches[k].id == all_potions.id[potion_ran]){
                                    all_bases.marches[k].vx *= 2;
                                    all_bases.marches[k].vy *= 2;
                                }
                            }
                            potion_ran++;
                            potion_ran %= 4;
                            potion_active = true;
                            return;
                        }
                    }
                }
            }
            else if((all_potions.is_active[potion_ran] && all_potions.timer[potion_ran] > 0)){
                for(int k = 0;k < 100;k++){
                    if(all_bases.marches[k].id == all_potions.id[potion_ran]){
                        all_bases.marches[k].vx *= 2;
                        all_bases.marches[k].vy *= 2;
                    }
                }
                if(point_adder%30 == 0){
                    all_potions.timer[potion_ran]--;
                }
            }
            else if(all_potions.timer[potion_ran] == 0){
                all_potions.is_active[potion_ran] = false;
                all_potions.timer[potion_ran] = -1;
                all_potions.id[potion_ran] = -1;
                for(int k = 0;k < 100;k++){
                    if(all_bases.marches[k].id == all_potions.id[potion_ran]){
                        all_bases.marches[k].vx *= 1/2;
                        all_bases.marches[k].vy *= 1/2;
                    }
                }
                potion_active = false;
            }
            break;
        case 3:
            if(!all_potions.is_active[potion_ran] && !potion_active){
                all_potions.x[potion_ran] = (all_bases.base_x[tmp_ran1]+all_bases.base_x[tmp_ran2])/2;
                all_potions.y[potion_ran] = (all_bases.base_x[tmp_ran1]+all_bases.base_y[tmp_ran2])/2;
                for(int i = 0;i < 100;i++){
                    for(int j = 0;j < 200;j++){
                        if(abs(all_bases.marches[i].x[j] - all_potions.x[potion_ran]) < 50 &&
                           abs(all_bases.marches[i].y[j] - all_potions.y[potion_ran]) < 50){
                            all_potions.is_active[potion_ran] = true;
                            all_potions.timer[potion_ran] = 10;
                            all_potions.id[potion_ran] = all_bases.marches[i].id;
                            for(int k = 0;k < 100;k++){
                                if(all_bases.marches[k].id == all_potions.id[potion_ran]){
                                    all_bases.marches[k].vx *= 2;
                                    all_bases.marches[k].vy *= 2;
                                }
                            }
                            potion_ran++;
                            potion_ran %= 4;
                            potion_active = true;
                            return;
                        }
                    }
                }
            }
            else if((all_potions.is_active[potion_ran] && all_potions.timer[potion_ran] > 0)){
                for(int k = 0;k < 100;k++){
                    if(all_bases.marches[k].id == all_potions.id[potion_ran]){
                        all_bases.marches[k].vx *= 2;
                        all_bases.marches[k].vy *= 2;
                    }
                }
                if(point_adder%30 == 0){
                    all_potions.timer[potion_ran]--;
                }
            }
            else if(all_potions.timer[potion_ran] == 0){
                all_potions.is_active[potion_ran] = false;
                all_potions.timer[potion_ran] = -1;
                all_potions.id[potion_ran] = -1;
                for(int k = 0;k < 100;k++){
                    if(all_bases.marches[k].id == all_potions.id[potion_ran]){
                        all_bases.marches[k].vx *= 1/2;
                        all_bases.marches[k].vy *= 1/2;
                    }
                }
                potion_active = false;
            }
            break;
        default:
        break;
    }

}