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

void xy_maker(int l, int ran, Sint16 x[30][6], Sint16 y[30][6],
              Sint16 mid_x, Sint16 mid_y, Sint16 mid_xs[30], Sint16 mid_ys[30]){
    srand(time(NULL));
    int tmp = 0;
    int end = 0;

    for(int i = 0;i < 30;i++) {
        x[i][0] = mid_x - l; x[i][1] = mid_x - l / 2; x[i][2] = mid_x + l / 2;
        x[i][3] = mid_x + l; x[i][4] = mid_x + l / 2; x[i][5] = mid_x - l / 2;
        y[i][0] = mid_y; y[i][1] = mid_y - 86 * l / 100; y[i][2] = mid_y - 86 * l / 100;
        y[i][3] = mid_y; y[i][4] = mid_y + 86 * l / 100; y[i][5] = mid_y + 86 * l / 100;
        switch (ran) {
            case 0:
                mid_x += 3 * l / 2;
                mid_y -= 86 * l / 100;
                if(mid_x < l || mid_x > SCREEN_WIDTH-l || mid_y < 86*l/100 || mid_y > SCREEN_HEIGHT-86*l/100){
                    mid_x -= 3 * l / 2;
                    mid_y += 86 * l / 100;
                    tmp = 1;
                }
                for(int j = 0;j <= i;j++){
                    if(tmp == 1){break;}
                    if(mid_xs[j] == mid_x && mid_ys[j] == mid_y){
                        mid_x -= 3 * l / 2;
                        mid_y += 86 * l / 100;
                        tmp = 1;
                        break;
                    }
                }
                break;
            case 1:
                mid_x += 0;
                mid_y -= 2 * 86 * l / 100;
                if(mid_x < l || mid_x > SCREEN_WIDTH-l || mid_y < 86*l/100 || mid_y > SCREEN_HEIGHT-86*l/100){
                    mid_x -= 0;
                    mid_y += 2 * 86 * l / 100;
                    tmp = 1;
                }
                for(int j = 0;j <= i;j++){
                    if(tmp == 1){break;}
                    if(mid_xs[j] == mid_x && mid_ys[j] == mid_y){
                        mid_x -= 0;
                        mid_y += 2 * 86 * l / 100;
                        tmp = 1;
                        break;
                    }
                }
                break;
            case 2:
                mid_x -= 3 * l / 2;
                mid_y -= 86 * l / 100;
                if(mid_x < l || mid_x > SCREEN_WIDTH-l || mid_y < 86*l/100 || mid_y > SCREEN_HEIGHT-86*l/100){
                    mid_x += 3 * l / 2;
                    mid_y += 86 * l / 100;
                    tmp  = 1;
                }
                for(int j = 0;j <= i;j++){
                    if(tmp == 1){break;}
                    if(mid_xs[j] == mid_x && mid_ys[j] == mid_y){
                        mid_x += 3 * l / 2;
                        mid_y += 86 * l / 100;
                        tmp  = 1;
                        break;
                    }
                }
                break;
            case 3:
                mid_x -= 3 * l / 2;
                mid_y += 86 * l / 100;
                if(mid_x < l || mid_x > SCREEN_WIDTH-l || mid_y < 86*l/100 || mid_y > SCREEN_HEIGHT-86*l/100){
                    mid_x += 3 * l / 2;
                    mid_y -= 86 * l / 100;
                    tmp = 1;
                }
                for(int j = 0;j <= i;j++){
                    if(tmp == 1){break;}
                    if(mid_xs[j] == mid_x && mid_ys[j] == mid_y){
                        mid_x += 3 * l / 2;
                        mid_y += 86 * l / 100;
                        tmp  = 1;
                        break;
                    }
                }
                break;
            case 4:
                mid_x += 0;
                mid_y += 2 * 86 * l / 100;
                if(mid_x < l || mid_x > SCREEN_WIDTH-l || mid_y < 86*l/100 || mid_y > SCREEN_HEIGHT-86*l/100){
                    mid_x -= 0;
                    mid_y -= 2 * 86 * l / 100;
                    tmp = 1;
                }
                for(int j = 0;j <= i;j++){
                    if(tmp == 1){break;}
                    if(mid_xs[j] == mid_x && mid_ys[j] == mid_y){
                        mid_x -= 0;
                        mid_y -= 2 * 86 * l / 100;
                        tmp = 1;
                        break;
                    }
                }
                break;
            case 5:
                mid_x += 3 * l / 2;
                mid_y += 86 * l / 100;
                if(mid_x < l || mid_x > SCREEN_WIDTH-l || mid_y < 86*l/100 || mid_y > SCREEN_HEIGHT-86*l/100){
                    mid_x -= 3 * l / 2;
                    mid_y -= 86 * l / 100;
                    tmp = 1;
                }
                for(int j = 0;j <= i;j++){
                    if(tmp == 1){break;}
                    if(mid_xs[j] == mid_x && mid_ys[j] == mid_y){
                        mid_x -= 3 * l / 2;
                        mid_y -= 86 * l / 100;
                        tmp = 1;
                        break;
                    }
                }
                break;
            default:
                break;
        }
        if(tmp == 1){
            tmp = ran;
            while(ran == tmp){
                ran = rand()%6;
            }
            end++;
            tmp = 0;
            i--;
            if(end == 6){break;}
            continue;
        }
        end = 0;
        ran = rand()%6;
        mid_xs[i] = mid_x; mid_ys[i] = mid_y;
        max_shapes++;
    }
}

void draw_map(Sint16 nx[6], Sint16 ny[6], Sint16 x[30][6], Sint16 y[30][6]){
    for(int i = 0;i < 30;i++){
        for(int j = 0; j < 6;j++){
            nx[j] = x[i][j];
            ny[j] = y[i][j];
        }
        filledPolygonColor(sdlRenderer, nx, ny, 6, 0xffffffff);
        polygonColor(sdlRenderer, nx, ny, 6, 0xff000000);
    }
}