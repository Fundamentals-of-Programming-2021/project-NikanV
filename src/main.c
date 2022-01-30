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
char* username;

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

SDL_Color color(int r, int g, int b, int a){
    SDL_Color col = {r, g, b, a};

   return col;
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
    SDL_Texture* logo_tex;
    SDL_Rect logo_rec;
    get_text_and_rect(color(70, 255, 255, 255), SCREEN_WIDTH*30/100, SCREEN_HEIGHT*78/100,
                      SCREEN_WIDTH*40/100, SCREEN_HEIGHT*5/100,"Developed by Nikan Vasei",
                      &logo_tex, &logo_rec);
    //logo
    SDL_Texture* name_tex;
    SDL_Rect name_rec;
    get_text_and_rect(color(70, 255, 255, 255), SCREEN_WIDTH*23/100, SCREEN_HEIGHT*13/100,
                      SCREEN_WIDTH*56/100, SCREEN_HEIGHT*20/100,"STATE.IO",
                      &name_tex, &name_rec);

    //text box
    username = (char*)malloc(sizeof(char)*15);
    memset(username, '\0', (int)sizeof(username)*sizeof(char));
    SDL_Texture* input_tex;
    SDL_Rect input_rec;
    get_text_and_rect(color(255, 255, 255, 255), SCREEN_WIDTH*31/100, SCREEN_HEIGHT*57/100,
                      19*SCREEN_WIDTH*2/100,SCREEN_HEIGHT*5/100,
                      "Enter your username", &input_tex, &input_rec);

    bool render_text = false;
    SDL_StartTextInput();

    //text box submit
    SDL_Texture* submit_button;
    SDL_Rect submit_button_rec;
    get_text_and_rect(color(0, 0, 0, 255), SCREEN_WIDTH*44/100, SCREEN_HEIGHT*67/100,
                      6*SCREEN_WIDTH*2/100,SCREEN_HEIGHT*4/100,
                      "Submit", &submit_button, &submit_button_rec);


    SDL_bool shallExit = SDL_FALSE;
    SDL_bool goto_main_menu = false;
    while (shallExit == SDL_FALSE) {
        //starting game
        if(!goto_main_menu) {
            SDL_SetRenderDrawColor(sdlRenderer, 0x00, 0x00, 0x00, 0xff);
            SDL_RenderClear(sdlRenderer);
            SDL_RenderCopy(sdlRenderer, bg_tex, NULL, NULL);
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


            SDL_Event Event;
            while (SDL_PollEvent(&Event)) {

                if (Event.type == SDL_QUIT) {
                    shallExit = SDL_TRUE;
                    break;
                }
                else if (Event.type == SDL_KEYDOWN) {
                    if (Event.key.keysym.sym == SDLK_BACKSPACE && strlen(username) > 0) {
                        memset(username + strlen(username) - 1, '\0', sizeof(char));
                        render_text = true;
                    }
                }
                else if (Event.type == SDL_TEXTINPUT) {
                    if (strlen(username) < 15) {
                        memset(username + strlen(username), Event.text.text[0], sizeof(char));
                    }
                    render_text = true;
                }
                else if (Event.type == SDL_MOUSEBUTTONUP) {
                    if (Event.button.x >= SCREEN_WIDTH * 42 / 100 && Event.button.x <= SCREEN_WIDTH * 58 / 100 &&
                        Event.button.y >= SCREEN_HEIGHT * 66 / 100 && Event.button.y <= SCREEN_HEIGHT * 72 / 100) {
                        //go to main menu
                        goto_main_menu = true;
                        SDL_StopTextInput();
                        SDL_DestroyTexture(bg_tex);
                        SDL_DestroyTexture(logo_tex);
                        SDL_DestroyTexture(input_tex);
                    }

                }

            }
            if (render_text) {
                if (strlen(username) > 0) {
                    get_text_and_rect(color(255, 255, 255, 255), SCREEN_WIDTH * 35 / 100, SCREEN_HEIGHT * 57 / 100,
                                      (int) strlen(username) * SCREEN_WIDTH * 2 / 100, SCREEN_HEIGHT * 5 / 100,
                                      username, &input_tex, &input_rec);
                }
                else {
                    get_text_and_rect(color(255, 255, 255, 255), SCREEN_WIDTH * 31 / 100, SCREEN_HEIGHT * 57 / 100,
                                      19 * SCREEN_WIDTH * 2 / 100, SCREEN_HEIGHT * 5 / 100,
                                      "Enter your username", &input_tex, &input_rec);
                }
            }


        }
        //main menu
        else if(goto_main_menu){
            SDL_SetRenderDrawColor(sdlRenderer, 0x00, 0x00, 0x00, 0xff);
            SDL_RenderClear(sdlRenderer);


            SDL_Event e;
            while(SDL_PollEvent(&e)){
                if (e.type == SDL_QUIT) {
                    shallExit = SDL_TRUE;
                    break;
                }

            }
        }


        SDL_RenderPresent(sdlRenderer);
        SDL_Delay(1000 / FPS);
    }


    End();

    return 0;
}
