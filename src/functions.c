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

void xy_maker(int l, Sint16 mid_x, Sint16 mid_y, Sint16 x[30][6], Sint16 y[30][6], int index){
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
    mid_xs[index] = mid_x;
    mid_ys[index] = mid_y;
}

void draw_map(){
    for(int i = 0;i < 4;i++){
        if(i == 0){
            filledPolygonColor(sdlRenderer, x[i], y[i], 6, 0xff0000ff);
            polygonColor(sdlRenderer, x[i], y[i], 6, 0xff000000);
        }
        else if(i == 1){
            filledPolygonColor(sdlRenderer, x[i], y[i], 6, 0xffff0000);
            polygonColor(sdlRenderer, x[i], y[i], 6, 0xff000000);
        }
        else if(i == 2){
            filledPolygonColor(sdlRenderer, x[i], y[i], 6, 0xff00ff00);
            polygonColor(sdlRenderer, x[i], y[i], 6, 0xff000000);
        }
        else{
            filledPolygonColor(sdlRenderer, x[i], y[i], 6, 0xffffffff);
            polygonColor(sdlRenderer, x[i], y[i], 6, 0xff000000);
        }
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