#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "functions.h"
#include "variables.h"

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