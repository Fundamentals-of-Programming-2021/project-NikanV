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

    //images
    SDL_Texture* start_bg_tex;
    get_img_and_rect("../start.jpg", &start_bg_tex);
    SDL_Texture* main_menu_bg_tex;
    get_img_and_rect("../start.jpg", &main_menu_bg_tex);

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

    //username box
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

    //main menu boxes
    SDL_Texture* new_game;
    SDL_Texture* con_game;
    SDL_Texture* leaderboard;
    SDL_Texture* back;

    SDL_Rect new_game_rec;
    SDL_Rect con_game_rec;
    SDL_Rect leaderboard_rec;
    SDL_Rect back_rec;

    char* greeting = (char*)malloc(sizeof(char)*30);


    SDL_Texture* ingame_name;
    SDL_Rect ingame_name_rec;

    get_text_and_rect(color(0, 0, 0, 255), SCREEN_WIDTH*35/100, SCREEN_HEIGHT*28/100,
                      8*SCREEN_WIDTH*4/100,SCREEN_HEIGHT*5/100,
                      "New Game", &new_game, &new_game_rec);
    get_text_and_rect(color(0, 0, 0, 255), SCREEN_WIDTH*35/100, SCREEN_HEIGHT*43/100,
                      8*SCREEN_WIDTH*4/100,SCREEN_HEIGHT*5/100,
                      "Continue", &con_game, &con_game_rec);
    get_text_and_rect(color(0, 0, 0, 255), SCREEN_WIDTH*26/100, SCREEN_HEIGHT*58/100,
                      12*SCREEN_WIDTH*4/100,SCREEN_HEIGHT*5/100,
                      "Leaderboard", &leaderboard, &leaderboard_rec);
    get_text_and_rect(color(0, 0, 0, 255), SCREEN_WIDTH*42/100, SCREEN_HEIGHT*73/100,
                      4*SCREEN_WIDTH*4/100,SCREEN_HEIGHT*5/100,
                      "Back", &back, &back_rec);






    SDL_bool shallExit = SDL_FALSE;
    SDL_bool goto_main_menu = false;
    while (shallExit == SDL_FALSE) {
        //starting game
        if(!goto_main_menu) {
            SDL_SetRenderDrawColor(sdlRenderer, 0x00, 0x00, 0x00, 0xff);
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
                        strcpy(greeting, username);
                        get_text_and_rect(color(255, 255, 255, 255), SCREEN_WIDTH*21/100,
                                          SCREEN_HEIGHT*12/100,strlen(greeting)*SCREEN_WIDTH*2/100,
                                          SCREEN_HEIGHT*5/100,greeting , &ingame_name,
                                          &ingame_name_rec);
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
        if(goto_main_menu){
            //destroying previous ones

            //new part
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





            SDL_Event e;
            while(SDL_PollEvent(&e)){
                if (e.type == SDL_QUIT) {
                    shallExit = SDL_TRUE;
                    break;
                }
                else if(e.type == SDL_MOUSEBUTTONUP){
                    if(e.button.x >= SCREEN_WIDTH*40/100 && e.button.x <= SCREEN_WIDTH*60/100 &&
                       e.button.y >= SCREEN_HEIGHT*70/100 && e.button.y <= SCREEN_HEIGHT*80/100){
                        //back to start
                        goto_main_menu = false;
                    }
                    else if(e.button.x >= SCREEN_WIDTH*30/100 && e.button.x <= SCREEN_WIDTH*70/100 &&
                            e.button.y >= SCREEN_HEIGHT*25/100 && e.button.y <= SCREEN_HEIGHT*35/100){
                        //new_game
                    }
                    else if(e.button.x >= SCREEN_WIDTH*30/100 && e.button.x <= SCREEN_WIDTH*70/100 &&
                            e.button.y >= SCREEN_HEIGHT*40/100 && e.button.y <= SCREEN_HEIGHT*50/100){
                        //continue
                    }
                    else if(e.button.x >= SCREEN_WIDTH*25/100 && e.button.x <= SCREEN_WIDTH*75/100 &&
                            e.button.y >= SCREEN_HEIGHT*55/100 && e.button.y <= SCREEN_HEIGHT*65/100){
                        //leaderboards
                    }
                }

            }

        }

        SDL_RenderPresent(sdlRenderer);
        SDL_Delay(1000 / FPS);
    }

    SDL_StopTextInput();
    SDL_DestroyTexture(start_bg_tex);
    SDL_DestroyTexture(logo_tex);
    SDL_DestroyTexture(input_tex);

    End();

    return 0;
}
