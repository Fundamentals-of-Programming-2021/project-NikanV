#include "functions.h"
#include "variables.h"

void Init(){
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    TTF_Init();
}

void reset_game(){
    won = false;
    pick_hard = false;
    pick_medium = false;
    pick_easy = false;
    goto_winner = false;
    goto_main_menu = true;
    won = false;
}

void destroy_all(SDL_Texture *start_bg_tex, SDL_Texture *main_menu_bg_tex, SDL_Texture *logo_tex, SDL_Texture *name_tex,
                 SDL_Texture *submit_button, SDL_Texture *ingame_name, SDL_Texture *input_tex, SDL_Texture *new_game,
                 SDL_Texture *con_game, SDL_Texture *leaderboard, SDL_Texture *back, SDL_Texture *map,
                 SDL_Texture *random_map_tex, SDL_Texture *choose_dif_tex, SDL_Texture *easy, SDL_Texture *medium,
                 SDL_Texture *hard, SDL_Texture *places_tex,SDL_Texture *leaderboard_player, SDL_Texture *back_to_menu){
    SDL_DestroyTexture(start_bg_tex); SDL_DestroyTexture(main_menu_bg_tex);
    SDL_DestroyTexture(logo_tex); SDL_DestroyTexture(name_tex); SDL_DestroyTexture(submit_button);
    SDL_DestroyTexture(ingame_name); SDL_DestroyTexture(input_tex); SDL_DestroyTexture(new_game);
    SDL_DestroyTexture(con_game); SDL_DestroyTexture(leaderboard); SDL_DestroyTexture(back);
    SDL_DestroyTexture(map); SDL_DestroyTexture(random_map_tex); SDL_DestroyTexture(choose_dif_tex);
    SDL_DestroyTexture(easy); SDL_DestroyTexture(medium); SDL_DestroyTexture(hard);
    SDL_DestroyTexture(places_tex); SDL_DestroyTexture(leaderboard_player);
    SDL_DestroyTexture(back_to_menu); SDL_DestroyTexture(points_tex);
    SDL_DestroyTexture(potions_tex); SDL_DestroyTexture(congrats);
    SDL_DestroyTexture(winning_point);
}

void Begin(){
    sdlWindow = SDL_CreateWindow("Test_Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                 SCREEN_WIDTH,SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1,
                                     SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    xeros = TTF_OpenFont("../fonts/xeros_theorem.ttf", 24);
    SDL_StartTextInput();
    srand(time(NULL));
}

void get_text_and_rect(SDL_Color color, int x, int y, int w, int h, char *text, SDL_Texture** texture,
                       SDL_Rect* rect) {
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

void End(){
    SDL_StopTextInput();
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);
    TTF_CloseFont(xeros);
    SDL_Quit();
}