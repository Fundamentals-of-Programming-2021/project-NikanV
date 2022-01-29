#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#ifdef main
#undef main
#endif

#include <stdio.h>
#include <stdbool.h>


const int FPS = 60;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1440;

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int mod(int a, int b) {
    return ((a % b) + b) % b;
}

void get_text_and_rect(SDL_Renderer *renderer, SDL_Color color, int x, int y, int w, int h, char *text,
                       TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect) {
    SDL_Surface *surface;
    SDL_Color textColor = color;

    surface = TTF_RenderText_Solid(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    rect->x = x; rect->y = y; rect->w = w; rect->h = h;
}

int main() {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    SDL_Window *sdlWindow = SDL_CreateWindow("Test_Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                             SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    //menu image
    SDL_Surface* surface  = IMG_Load("../main_menu.jpg");
    SDL_Texture* tex = SDL_CreateTextureFromSurface(sdlRenderer, surface);
    SDL_FreeSurface(surface);

    //menu strings
    TTF_Init();
    TTF_Font* xeros = TTF_OpenFont("../fonts/xeros_theorem.ttf", 24);
    SDL_Color credits = {70, 255, 255};
    SDL_Texture* logo_tex;
    SDL_Rect logo_rec;
    get_text_and_rect(sdlRenderer, credits, SCREEN_WIDTH*29/100, SCREEN_HEIGHT*78/100,
                      SCREEN_WIDTH*40/100, SCREEN_HEIGHT*5/100,"Developed by Nikan Vasei", xeros, &logo_tex, &logo_rec);
    SDL_Texture* name_tex;
    SDL_Rect name_rec;
    get_text_and_rect(sdlRenderer, credits, SCREEN_WIDTH*23/100, SCREEN_HEIGHT*13/100,
                      SCREEN_WIDTH*56/100, SCREEN_HEIGHT*20/100,"STATE.IO", xeros, &name_tex, &name_rec);


    SDL_bool shallExit = SDL_FALSE;
    while (shallExit == SDL_FALSE) {
        SDL_SetRenderDrawColor(sdlRenderer, 0x00, 0x00, 0x00, 0xff);
        SDL_RenderClear(sdlRenderer);
        SDL_RenderCopy(sdlRenderer, tex, NULL, NULL);
        SDL_RenderCopy(sdlRenderer, logo_tex, NULL, &logo_rec);
        SDL_RenderCopy(sdlRenderer, name_tex, NULL, &name_rec);

        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent)) {
            switch (sdlEvent.type) {
                case SDL_QUIT:
                    shallExit = SDL_TRUE;
                    break;
            }
        }


        SDL_RenderPresent(sdlRenderer);
        SDL_Delay(1000 / FPS);
    }

    SDL_DestroyTexture(tex);
    SDL_DestroyTexture(logo_tex);
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);
    TTF_CloseFont(xeros);
    SDL_Quit();
    return 0;
}
