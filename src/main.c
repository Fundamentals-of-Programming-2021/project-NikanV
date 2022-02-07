
#include "variables.h"
#include "functions.h"

#ifdef main
#undef main
#endif

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

    //new_game
    SDL_Texture* map;
    get_img_and_rect("../map.jpg", &map);
    SDL_Rect map_rec;
    map_rec.x = -SCREEN_WIDTH/8; map_rec.y = -SCREEN_HEIGHT/16;
    map_rec.w = 22*SCREEN_WIDTH/16; map_rec.h = 20*SCREEN_HEIGHT/16;
    srand(time(NULL));
    int first = -1, second = -1;
    int ran = rand()%10;
    xy_maker(rand()%(14*SCREEN_WIDTH/100) + 11*SCREEN_WIDTH/100,
             rand()%(17*SCREEN_HEIGHT/100) + 28*SCREEN_HEIGHT/100, ran);
    xy_maker(rand()%(8*SCREEN_WIDTH/100) + 29*SCREEN_WIDTH/100,
             rand()%(15*SCREEN_HEIGHT/100) + 65*SCREEN_HEIGHT/100, (ran+1)%10);
    xy_maker(rand()%(12*SCREEN_WIDTH/100) + 85*SCREEN_WIDTH/100,
             rand()%(24*SCREEN_HEIGHT/100) + 23*SCREEN_HEIGHT/100, (ran+2)%10);
    xy_maker(rand()%(6*SCREEN_WIDTH/100) + 59*SCREEN_WIDTH/100,
             rand()%(14*SCREEN_HEIGHT/100) + 63*SCREEN_HEIGHT/100, (ran+3)%10);
    //friendly
    xy_maker(rand()%(13*SCREEN_WIDTH/100) + 57*SCREEN_WIDTH/100,
             rand()%(10*SCREEN_HEIGHT/100) + 30*SCREEN_HEIGHT/100, (ran+4)%10);
    xy_maker(rand()%(6*SCREEN_WIDTH/100) + 59*SCREEN_WIDTH/100,
             rand()%(10*SCREEN_HEIGHT/100) + 45*SCREEN_HEIGHT/100, (ran+5)%10);
    xy_maker(rand()%(5*SCREEN_WIDTH/100) + 92*SCREEN_WIDTH/100,
             rand()%(14*SCREEN_HEIGHT/100) + 66*SCREEN_HEIGHT/100, (ran+6)%10);
    xy_maker(rand()%(12*SCREEN_WIDTH/100) + 28*SCREEN_WIDTH/100,
             rand()%(13*SCREEN_HEIGHT/100) + 12*SCREEN_HEIGHT/100, (ran+7)%10);
    xy_maker(rand()%(8*SCREEN_WIDTH/100) + 75*SCREEN_WIDTH/100,
             rand()%(24*SCREEN_HEIGHT/100) + 23*SCREEN_HEIGHT/100, (ran+8)%10);
    xy_maker(rand()%(9*SCREEN_WIDTH/100) + 17*SCREEN_WIDTH/100,
             rand()%(15*SCREEN_HEIGHT/100) + 47*SCREEN_HEIGHT/100, (ran+9)%10);

    //logic
    input_struct();



    while (shallExit == SDL_FALSE) {
        //starting game
        if(goto_start) {
            SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0x00, 0x00, 0xff);
            SDL_RenderClear(sdlRenderer);

            draw_start(start_bg_tex, logo_tex, name_tex, input_tex, submit_button, logo_rec,
                       name_rec, input_rec, submit_button_rec);


            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                switch(e.type) {
                    case SDL_QUIT:
                        shallExit = SDL_TRUE;
                        break;
                    case SDL_KEYDOWN:
                        if (e.key.keysym.sym == SDLK_BACKSPACE && strlen(username) > 0) {
                            memset(username + strlen(username) - 1, '\0', sizeof(char));
                            render_text = true;
                        }
                        break;
                    case SDL_TEXTINPUT:
                        if (strlen(username) < 15) {
                            memset(username + strlen(username), e.text.text[0], sizeof(char));
                        }
                        render_text = true;
                        break;
                    case SDL_MOUSEBUTTONUP:
                        if (e.button.x >= SCREEN_WIDTH * 42 / 100 && e.button.x <= SCREEN_WIDTH * 58 / 100 &&
                            e.button.y >= SCREEN_HEIGHT * 66 / 100 && e.button.y <= SCREEN_HEIGHT * 72 / 100) {
                            //go to main menu
                            goto_main_menu = true;
                            goto_start = false;
                            get_text_and_rect(color(255, 255, 255, 255), SCREEN_WIDTH*21/100,
                                              SCREEN_HEIGHT*12/100,strlen(username)*SCREEN_WIDTH*2/100,
                                              SCREEN_HEIGHT*5/100,username , &ingame_name,
                                              &ingame_name_rec);
                        }
                        break;
                    default:
                        break;
                }
            }
            if (render_text) {
                if (strlen(username) > 0) {
                    get_text_and_rect(color(255, 255, 255, 255), SCREEN_WIDTH * 35 / 100,
                                      SCREEN_HEIGHT * 57 / 100,
                                      (int) strlen(username) * SCREEN_WIDTH * 2 / 100,
                                      SCREEN_HEIGHT * 5 / 100,
                                      username, &input_tex, &input_rec);
                }
                else {
                    get_text_and_rect(color(255, 255, 255, 255), SCREEN_WIDTH * 31 / 100,
                                      SCREEN_HEIGHT * 57 / 100,
                                      19 * SCREEN_WIDTH * 2 / 100, SCREEN_HEIGHT * 5 / 100,
                                      "Enter your username", &input_tex, &input_rec);
                }
            }

        }

        //main menu
        if(goto_main_menu){

            SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0x00, 0xff, 0xff);
            SDL_RenderClear(sdlRenderer);

            draw_main_menu(main_menu_bg_tex, new_game, con_game, leaderboard, back, ingame_name, new_game_rec,
                           con_game_rec, leaderboard_rec, back_rec, ingame_name_rec);


            SDL_Event e;
            while(SDL_PollEvent(&e)){
                switch (e.type) {
                    case SDL_QUIT:
                        shallExit = SDL_TRUE;
                        break;
                    case SDL_MOUSEBUTTONUP:
                        if(e.button.x >= SCREEN_WIDTH*40/100 && e.button.x <= SCREEN_WIDTH*60/100 &&
                           e.button.y >= SCREEN_HEIGHT*70/100 && e.button.y <= SCREEN_HEIGHT*80/100){
                            //back to start
                            goto_main_menu = false;
                            goto_start = true;
                        }
                        else if(e.button.x >= SCREEN_WIDTH*30/100 && e.button.x <= SCREEN_WIDTH*70/100 &&
                                e.button.y >= SCREEN_HEIGHT*25/100 && e.button.y <= SCREEN_HEIGHT*35/100){
                            //new_game
                            goto_new_game = true;
                            goto_main_menu = false;
                        }
                        else if(e.button.x >= SCREEN_WIDTH*30/100 && e.button.x <= SCREEN_WIDTH*70/100 &&
                                e.button.y >= SCREEN_HEIGHT*40/100 && e.button.y <= SCREEN_HEIGHT*50/100){
                            //continue
                        }
                        else if(e.button.x >= SCREEN_WIDTH*25/100 && e.button.x <= SCREEN_WIDTH*75/100 &&
                                e.button.y >= SCREEN_HEIGHT*55/100 && e.button.y <= SCREEN_HEIGHT*65/100){
                            //leaderboards
                        }
                        break;
                    default:
                        break;
                }

            }

        }

        //goto new_game
        if(goto_new_game){
            SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0xff, 0xff, 0xff);
            SDL_RenderClear(sdlRenderer);
            SDL_RenderCopy(sdlRenderer, map, NULL, &map_rec);

            point_adder++;
            draw_map();
            make_march();
            draw_march();
            apply_speed_point();
            stop_speed();

            SDL_Event e;
            while(SDL_PollEvent(&e)) {
                switch(e.type) {
                    case SDL_QUIT:
                        shallExit = SDL_TRUE;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        selecting_bases(e, &first, &second);
                        break;
                    default:
                        break;
                }
            }

        }




        SDL_RenderPresent(sdlRenderer);
        SDL_Delay(1000 / FPS);
    }


    SDL_DestroyTexture(start_bg_tex);
    SDL_DestroyTexture(main_menu_bg_tex);
    SDL_DestroyTexture(logo_tex);
    SDL_DestroyTexture(name_tex);
    SDL_DestroyTexture(submit_button);
    SDL_DestroyTexture(ingame_name);
    SDL_DestroyTexture(input_tex);
    SDL_DestroyTexture(new_game);
    SDL_DestroyTexture(con_game);
    SDL_DestroyTexture(leaderboard);
    SDL_DestroyTexture(back);
    SDL_DestroyTexture(map);

    End();

    return 0;
}
