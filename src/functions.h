#ifndef FOP_PROJECT_FUNCTIONS_H
#define FOP_PROJECT_FUNCTIONS_H

#endif //FOP_PROJECT_FUNCTIONS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

void get_text_and_rect(SDL_Color color, int x, int y, int w, int h, char *text, SDL_Texture** texture,
                       SDL_Rect* rect);
void get_img_and_rect(char* path, SDL_Texture** texture);
