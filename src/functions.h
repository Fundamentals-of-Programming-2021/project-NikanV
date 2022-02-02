#ifndef FOP_PROJECT_FUNCTIONS_H
#define FOP_PROJECT_FUNCTIONS_H

#endif //FOP_PROJECT_FUNCTIONS_H

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void Init();

void Begin();

void End();
void get_text_and_rect(SDL_Color color, int x, int y, int w, int h, char *text, SDL_Texture** texture,
                       SDL_Rect* rect);

void get_img_and_rect(char* path, SDL_Texture** texture);

SDL_Color color(int r, int g, int b, int a);

void xy_maker(int l, int ran, Sint16 x[30][6], Sint16 y[30][6],
              Sint16 mid_x, Sint16 mid_y, Sint16 mid_xs[30], Sint16 mid_ys[30]);

void draw_map(Sint16 nx[6], Sint16 ny[6], Sint16 x[30][6], Sint16 y[30][6]);

