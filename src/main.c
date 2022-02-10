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
    get_img_and_rect("../images/start.jpg", &start_bg_tex);
    SDL_Texture* main_menu_bg_tex;
    get_img_and_rect("../images/start.jpg", &main_menu_bg_tex);
    SDL_Texture* map;
    get_img_and_rect("../images/map.jpg", &map);
    SDL_Rect map_rec;
    map_rec.x = -SCREEN_WIDTH/8; map_rec.y = -SCREEN_HEIGHT/16;
    map_rec.w = 22*SCREEN_WIDTH/16; map_rec.h = 20*SCREEN_HEIGHT/16;

    //start page texts
    SDL_Texture* logo_tex;
    SDL_Rect logo_rec;
    get_text_and_rect(color(70, 255, 255, 255), SCREEN_WIDTH*30/100, SCREEN_HEIGHT*78/100,
                      SCREEN_WIDTH*40/100, SCREEN_HEIGHT*5/100,"Developed by Nikan Vasei",
                      &logo_tex, &logo_rec);
    SDL_Texture* name_tex;
    SDL_Rect name_rec;
    get_text_and_rect(color(70, 255, 255, 255), SCREEN_WIDTH*23/100, SCREEN_HEIGHT*13/100,
                      SCREEN_WIDTH*56/100, SCREEN_HEIGHT*20/100,"STATE.IO",
                      &name_tex, &name_rec);

    //login box
    SDL_Texture* submit_button;
    SDL_Rect submit_button_rec;
    get_text_and_rect(color(0, 0, 0, 255), SCREEN_WIDTH*44/100, SCREEN_HEIGHT*67/100,
                      6*SCREEN_WIDTH*2/100,SCREEN_HEIGHT*4/100,
                      "Submit", &submit_button, &submit_button_rec);
    SDL_Texture* input_tex;
    SDL_Rect input_rec;
    get_text_and_rect(color(255, 255, 255, 255), SCREEN_WIDTH*31/100, SCREEN_HEIGHT*57/100,
                      19*SCREEN_WIDTH*2/100,SCREEN_HEIGHT*5/100,
                      "Enter your username", &input_tex, &input_rec);
    username = (char*)malloc(sizeof(char)*15);
    memset(username, '\0', (int)sizeof(username)*sizeof(char));
    bool render_text = false;


    //main menu boxes
    SDL_Texture* new_game, *con_game, *leaderboard, *back;
    SDL_Rect new_game_rec, con_game_rec, leaderboard_rec, back_rec;
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
    SDL_Texture* ingame_name;
    SDL_Rect ingame_name_rec;
    SDL_Texture* leaderboard_player;
    SDL_Rect leaderboard_player_rec;

    //map picker
    SDL_Texture* random_map_tex, *choose_dif_tex;
    SDL_Rect random_map, choose_dif;
    get_text_and_rect(color(0, 0, 0, 255), SCREEN_WIDTH*30/100, SCREEN_HEIGHT*28/100,
                      10*SCREEN_WIDTH*4/100,SCREEN_HEIGHT*5/100,
                      "Random Map", &random_map_tex, &random_map);
    get_text_and_rect(color(0, 0, 0, 255), SCREEN_WIDTH*22/100, SCREEN_HEIGHT*42/100,
                      14*SCREEN_WIDTH*4/100,SCREEN_HEIGHT*5/100,
                      "Choose Difficulty", &choose_dif_tex, &choose_dif);

    //diff pick
    SDL_Texture* easy, *medium, *hard;
    SDL_Rect easy_rec, medium_rec, hard_rec;
    get_text_and_rect(color(0, 0, 0, 255), SCREEN_WIDTH*42/100, SCREEN_HEIGHT*28/100,
                      4*SCREEN_WIDTH*4/100,SCREEN_HEIGHT*5/100,
                      "Easy", &easy, &easy_rec);
    get_text_and_rect(color(0, 0, 0, 255), SCREEN_WIDTH*38/100, SCREEN_HEIGHT*43/100,
                      6*SCREEN_WIDTH*4/100,SCREEN_HEIGHT*5/100,
                      "Normal", &medium, &medium_rec);
    get_text_and_rect(color(0, 0, 0, 255), SCREEN_WIDTH*42/100, SCREEN_HEIGHT*58/100,
                      4*SCREEN_WIDTH*4/100,SCREEN_HEIGHT*5/100,
                      "Hard", &hard, &hard_rec);


    //new_game
    SDL_Texture *places_tex;
    SDL_Rect places_rec;

    //randoms
    int ran = rand()%11;
    int bot_ran = rand()%11;
    potion_ran = rand()%4;

    //winning page
    SDL_Texture* back_to_menu;
    SDL_Rect back_to_menu_rec;
    get_text_and_rect(color(0, 0, 0, 255), SCREEN_WIDTH*34/100, SCREEN_HEIGHT*72/100,
                      8*SCREEN_WIDTH*4/100,SCREEN_HEIGHT*6/100,
                      "Back to menu", &back_to_menu, &back_to_menu_rec);



    while (shallExit == SDL_FALSE) {
        //starting game
        if(goto_start) {
            draw_start(start_bg_tex, logo_tex, name_tex, input_tex, submit_button, logo_rec,
                       name_rec, input_rec, submit_button_rec);

            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                switch(e.type) {
                    case SDL_QUIT:
                        shallExit = SDL_TRUE;
                        put_all_usernames_in_file();
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
                            if(strlen(username) > 0) {
                                goto_main_menu = true;
                                goto_start = false;
                                get_text_and_rect(color(255, 255, 255, 255),
                                                  SCREEN_WIDTH * 21 / 100,
                                                  SCREEN_HEIGHT * 12 / 100,
                                                  strlen(username) * SCREEN_WIDTH * 2 / 100,
                                                  SCREEN_HEIGHT * 5 / 100, username, &ingame_name,
                                                  &ingame_name_rec);
                                signed_up = false;
                            }
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
            draw_main_menu(main_menu_bg_tex, new_game, con_game, leaderboard, back, ingame_name, new_game_rec,
                           con_game_rec, leaderboard_rec, back_rec, ingame_name_rec);
            if(!signed_up){
                get_all_usernames();
                if(check_for_duplicate()){
                    add_player();
                }
                sort_players();
                signed_up = true;
            }

            SDL_Event e;
            while(SDL_PollEvent(&e)){
                switch (e.type) {
                    case SDL_QUIT:
                        shallExit = SDL_TRUE;
                        put_all_usernames_in_file();
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
                            goto_map_picker = true;
                            goto_main_menu = false;
                        }
                        else if(e.button.x >= SCREEN_WIDTH*30/100 && e.button.x <= SCREEN_WIDTH*70/100 &&
                                e.button.y >= SCREEN_HEIGHT*40/100 && e.button.y <= SCREEN_HEIGHT*50/100){
                            //continue
                        }
                        else if(e.button.x >= SCREEN_WIDTH*25/100 && e.button.x <= SCREEN_WIDTH*75/100 &&
                                e.button.y >= SCREEN_HEIGHT*55/100 && e.button.y <= SCREEN_HEIGHT*65/100){
                            //leaderboards
                            goto_leaderboard = true;
                            goto_main_menu = false;
                        }
                        break;
                    default:
                        break;
                }

            }

        }

        //leaderboard
        if(goto_leaderboard){
            draw_leaderboard(main_menu_bg_tex, back, leaderboard_player, leaderboard_player_rec, back_rec);

            SDL_Event e;
            while(SDL_PollEvent(&e)){
                switch (e.type) {
                    case SDL_QUIT:
                        shallExit = SDL_TRUE;
                        put_all_usernames_in_file();
                        break;
                    case SDL_MOUSEBUTTONUP:
                        if(e.button.x >= SCREEN_WIDTH*40/100 && e.button.x <= SCREEN_WIDTH*60/100 &&
                           e.button.y >= SCREEN_HEIGHT*70/100 && e.button.y <= SCREEN_HEIGHT*80/100){
                            //back to main menu
                            goto_main_menu = true;
                            goto_leaderboard = false;
                        }
                        break;
                    default:
                        break;
                }
            }

        }

        //map_picker
        if(goto_map_picker){
            draw_map_picker(main_menu_bg_tex, ingame_name, ingame_name_rec, random_map_tex, random_map,
                            choose_dif_tex, choose_dif, back, back_rec);

            SDL_Event e;
            while(SDL_PollEvent(&e)){
                switch (e.type) {
                    case SDL_QUIT:
                        shallExit = SDL_TRUE;
                        put_all_usernames_in_file();
                        break;
                    case SDL_MOUSEBUTTONUP:
                        if(e.button.x >= SCREEN_WIDTH*40/100 && e.button.x <= SCREEN_WIDTH*60/100 &&
                           e.button.y >= SCREEN_HEIGHT*70/100 && e.button.y <= SCREEN_HEIGHT*80/100){
                            //back to main menu
                            goto_main_menu = true;
                            goto_map_picker = false;
                        }
                        else if(e.button.x >= SCREEN_WIDTH*28/100 && e.button.x <= SCREEN_WIDTH*72/100 &&
                                e.button.y >= SCREEN_HEIGHT*25/100 && e.button.y <= SCREEN_HEIGHT*35/100){
                            //start game
                            goto_map_picker = false;
                            goto_game = true;
                            map_maker(ran);
                            input_struct();
                        }
                        else if(e.button.x >= SCREEN_WIDTH*20/100 && e.button.x <= SCREEN_WIDTH*80/100 &&
                                e.button.y >= SCREEN_HEIGHT*40/100 && e.button.y <= SCREEN_HEIGHT*50/100){
                            goto_map_picker = false;
                            goto_diff_pick = true;
                        }
                        break;
                    default:
                        break;
                }
            }

        }

        //goto diff_pick
        if(goto_diff_pick){
            draw_diff_pick(main_menu_bg_tex, ingame_name, ingame_name_rec, easy, medium, hard,
                           easy_rec, medium_rec, hard_rec, back, back_rec);

            SDL_Event e;
            while(SDL_PollEvent(&e)){
                switch (e.type) {
                    case SDL_QUIT:
                        shallExit = SDL_TRUE;
                        put_all_usernames_in_file();
                        break;
                    case SDL_MOUSEBUTTONUP:
                        if(e.button.x >= SCREEN_WIDTH*40/100 && e.button.x <= SCREEN_WIDTH*60/100 &&
                           e.button.y >= SCREEN_HEIGHT*70/100 && e.button.y <= SCREEN_HEIGHT*80/100){
                            //back to map picker
                            goto_map_picker = true;
                            goto_diff_pick = false;
                        }
                        if(e.button.x >= SCREEN_WIDTH*35/100 && e.button.x <= SCREEN_WIDTH*65/100 &&
                           e.button.y >= SCREEN_HEIGHT*25/100 && e.button.y <= SCREEN_HEIGHT*35/100){
                            //go to easy
                            goto_game = true;
                            pick_easy = true;
                            goto_diff_pick = false;
                            xy_maker(85*SCREEN_WIDTH/100, 30*SCREEN_HEIGHT/100, 0);
                            xy_maker(20*SCREEN_WIDTH/100, 20*SCREEN_HEIGHT/100, 1);
                            xy_maker(30*SCREEN_WIDTH/100, 80*SCREEN_HEIGHT/100, 2);
                            xy_maker(25*SCREEN_WIDTH/100, 60*SCREEN_HEIGHT/100, 3);
                            //friendly
                            xy_maker(75*SCREEN_WIDTH/100, 40*SCREEN_HEIGHT/100, 4);
                            xy_maker(65*SCREEN_WIDTH/100, 50*SCREEN_HEIGHT/100, 5);
                            xy_maker(65*SCREEN_WIDTH/100, 30*SCREEN_HEIGHT/100, 6);
                            xy_maker(95*SCREEN_WIDTH/100, 75*SCREEN_HEIGHT/100, 7);
                            xy_maker(60*SCREEN_WIDTH/100, 70*SCREEN_HEIGHT/100, 8);
                            xy_maker(20*SCREEN_WIDTH/100, 40*SCREEN_HEIGHT/100, 9);
                            xy_maker(40*SCREEN_WIDTH/100, 20*SCREEN_HEIGHT/100, 10);
                            input_struct();

                        }
                        if(e.button.x >= SCREEN_WIDTH*35/100 && e.button.x <= SCREEN_WIDTH*65/100 &&
                           e.button.y >= SCREEN_HEIGHT*40/100 && e.button.y <= SCREEN_HEIGHT*50/100){
                            //go to normal
                            goto_game = true;
                            pick_medium = true;
                            goto_diff_pick = false;
                            xy_maker(55*SCREEN_WIDTH/100, 60*SCREEN_HEIGHT/100, 0);
                            xy_maker(80*SCREEN_WIDTH/100, 20*SCREEN_HEIGHT/100, 1);
                            xy_maker(25*SCREEN_WIDTH/100, 30*SCREEN_HEIGHT/100, 2);
                            xy_maker(30*SCREEN_WIDTH/100, 65*SCREEN_HEIGHT/100, 3);
                            //friendly
                            xy_maker(40*SCREEN_WIDTH/100, 20*SCREEN_HEIGHT/100, 4);
                            xy_maker(65*SCREEN_WIDTH/100, 50*SCREEN_HEIGHT/100, 5);
                            xy_maker(65*SCREEN_WIDTH/100, 30*SCREEN_HEIGHT/100, 6);
                            xy_maker(85*SCREEN_WIDTH/100, 55*SCREEN_HEIGHT/100, 7);
                            xy_maker(60*SCREEN_WIDTH/100, 70*SCREEN_HEIGHT/100, 8);
                            xy_maker(20*SCREEN_WIDTH/100, 45*SCREEN_HEIGHT/100, 9);
                            xy_maker(30*SCREEN_WIDTH/100, 80*SCREEN_HEIGHT/100, 10);
                            input_struct();
                        }
                        if(e.button.x >= SCREEN_WIDTH*35/100 && e.button.x <= SCREEN_WIDTH*65/100 &&
                           e.button.y >= SCREEN_HEIGHT*55/100 && e.button.y <= SCREEN_HEIGHT*65/100){
                            //go to hard
                            goto_game = true;
                            pick_hard = true;
                            goto_diff_pick = false;
                            xy_maker(15*SCREEN_WIDTH/100, 40*SCREEN_HEIGHT/100, 0);
                            xy_maker(30*SCREEN_WIDTH/100, 20*SCREEN_HEIGHT/100, 1);
                            xy_maker(30*SCREEN_WIDTH/100, 80*SCREEN_HEIGHT/100, 2);
                            xy_maker(65*SCREEN_WIDTH/100, 50*SCREEN_HEIGHT/100, 3);
                            //friendly
                            xy_maker(40*SCREEN_WIDTH/100, 25*SCREEN_HEIGHT/100, 4);
                            xy_maker(55*SCREEN_WIDTH/100, 50*SCREEN_HEIGHT/100, 5);
                            xy_maker(65*SCREEN_WIDTH/100, 30*SCREEN_HEIGHT/100, 6);
                            xy_maker(85*SCREEN_WIDTH/100, 45*SCREEN_HEIGHT/100, 7);
                            xy_maker(60*SCREEN_WIDTH/100, 70*SCREEN_HEIGHT/100, 8);
                            xy_maker(30*SCREEN_WIDTH/100, 60*SCREEN_HEIGHT/100, 9);
                            xy_maker(20*SCREEN_WIDTH/100, 20*SCREEN_HEIGHT/100, 10);
                            input_struct();
                        }
                        break;
                    default:
                        break;
                }
            }
        }

        //goto new_game
        if(goto_game){
            SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0xff, 0xff, 0xff);
            SDL_RenderClear(sdlRenderer);
            SDL_RenderCopy(sdlRenderer, map, NULL, &map_rec);

            draw_map();
            make_march();
            draw_march();
            check_accidents();
            make_potion();
            apply_speed_point();
            stop_speed();
            bot_movements(bot_ran);
            check_winner();
            if(show_top_four) {
                top_four(places_tex, places_rec);
            }

            point_adder++;
            if(point_adder == 1000000){point_adder = 0;}
            bot_ran = rand()%10;

            SDL_Event e;
            while(SDL_PollEvent(&e)) {
                switch(e.type) {
                    case SDL_QUIT:
                        shallExit = SDL_TRUE;
                        put_all_usernames_in_file();
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        selecting_bases(e);
                        break;
                    case SDL_KEYDOWN:
                        if(e.key.keysym.sym == SDLK_TAB){
                            show_top_four = !show_top_four;
                        }
                    default:
                        break;
                }
            }
        }

        //goto winner
        if(goto_winner){
            draw_winner(main_menu_bg_tex, back_to_menu, back_to_menu_rec);

            SDL_Event e;
            while(SDL_PollEvent(&e)){
                switch (e.type) {
                    case SDL_QUIT:
                        shallExit = SDL_TRUE;
                        put_all_usernames_in_file();
                        break;
                    case SDL_MOUSEBUTTONUP:
                        if(e.button.x >= SCREEN_WIDTH*33/100 && e.button.x <= SCREEN_WIDTH*67/100 &&
                           e.button.y >= SCREEN_HEIGHT*70/100 && e.button.y <= SCREEN_HEIGHT*80/100){
                            reset_game();
                        }
                    default:
                        break;
                }
            }
        }

        SDL_RenderPresent(sdlRenderer);
        SDL_Delay(1000 / FPS);
    }

    destroy_all(start_bg_tex, main_menu_bg_tex, logo_tex, name_tex, submit_button, ingame_name, input_tex, new_game,
                con_game, leaderboard, back, map, random_map_tex, choose_dif_tex, easy, medium, hard, places_tex,
                leaderboard_player, back_to_menu);
    End();
    return 0;
}
