#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#ifdef main
#undef main
#endif

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>


const int FPS = 60;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1440;

SDL_Window *sdlWindow;
SDL_Renderer *sdlRenderer;

TTF_Font* xeros;

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int mod(int a, int b) {
    return ((a % b) + b) % b;
}


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

}

void End(){
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



int main() {
    //initialize
    Init();

    //essentials
    Begin();

    //menu image
    SDL_Texture* bg_tex;
    get_img_and_rect("../main_menu.jpg", &bg_tex);

    //strings
    //credits
    SDL_Color credits = {70, 255, 255};
    SDL_Texture* logo_tex;
    SDL_Rect logo_rec;
    get_text_and_rect(credits, SCREEN_WIDTH*29/100, SCREEN_HEIGHT*78/100,
                      SCREEN_WIDTH*40/100, SCREEN_HEIGHT*5/100,"Developed by Nikan Vasei",
                      &logo_tex, &logo_rec);
    //logo
    SDL_Texture* name_tex;
    SDL_Rect name_rec;
    get_text_and_rect(credits, SCREEN_WIDTH*23/100, SCREEN_HEIGHT*13/100,
                      SCREEN_WIDTH*56/100, SCREEN_HEIGHT*20/100,"STATE.IO",
                      &name_tex, &name_rec);

    //text box
    char* username = (char*)malloc(sizeof(char)*50);
    username = "S";
    SDL_Texture* input_tex;
    SDL_Rect input_rec;
    bool render_text = false;
    get_text_and_rect(credits, 500, 500,200, 100,username,
                      &input_tex, &input_rec);
    SDL_StartTextInput();


    SDL_bool shallExit = SDL_FALSE;
    while (shallExit == SDL_FALSE) {
        SDL_SetRenderDrawColor(sdlRenderer, 0x00, 0x00, 0x00, 0xff);
        SDL_RenderClear(sdlRenderer);
        SDL_RenderCopy(sdlRenderer, bg_tex, NULL, NULL);
        SDL_RenderCopy(sdlRenderer, logo_tex, NULL, &logo_rec);
        SDL_RenderCopy(sdlRenderer, name_tex, NULL, &name_rec);
        SDL_RenderCopy(sdlRenderer, input_tex, NULL, &input_rec);


        SDL_Event Event;
        while (SDL_PollEvent(&Event)) {

            if (Event.type == SDL_QUIT) {
                shallExit = SDL_TRUE;
                break;
            }
            else if(Event.type == SDL_KEYDOWN){
                if( Event.key.keysym.sym == SDLK_BACKSPACE && strlen(username) > 0 ){
                    *(username + strlen(username) - 1) = '\0';
                    printf("%s|", username);
                    render_text = true;
                }
            }
            else if(Event.type == SDL_TEXTINPUT){
                printf("%s|", username);
                *(username + strlen(username)) = 'n';
                render_text = true;
            }

        }
        if(render_text){
            if(strlen(username) > 0){
                get_text_and_rect(credits, 500, 500,200, 100,username,
                                  &input_tex, &input_rec);
            }
            else{
                get_text_and_rect(credits, 500, 500,200, 100," ",
                                  &input_tex, &input_rec);
            }
        }


        SDL_RenderPresent(sdlRenderer);
        SDL_Delay(1000 / FPS);
    }

    SDL_StopTextInput();
    SDL_DestroyTexture(bg_tex);
    SDL_DestroyTexture(logo_tex);
    SDL_DestroyTexture(input_tex);

    End();

    return 0;
}
