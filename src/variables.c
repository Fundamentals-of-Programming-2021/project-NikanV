#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "functions.h"
#include "variables.h"

const int FPS = 60;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1440;

SDL_Window *sdlWindow;
SDL_Renderer *sdlRenderer;

TTF_Font* xeros;
char* username;

