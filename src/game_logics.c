#include "functions.h"
#include "variables.h"

//initializing
void map_maker(int ran){
    xy_maker(rand()%(14*SCREEN_WIDTH/100) + 11*SCREEN_WIDTH/100,
             rand()%(17*SCREEN_HEIGHT/100) + 28*SCREEN_HEIGHT/100, ran);
    xy_maker(rand()%(8*SCREEN_WIDTH/100) + 29*SCREEN_WIDTH/100,
             rand()%(15*SCREEN_HEIGHT/100) + 65*SCREEN_HEIGHT/100, (ran+1)%11);
    xy_maker(rand()%(12*SCREEN_WIDTH/100) + 85*SCREEN_WIDTH/100,
             rand()%(24*SCREEN_HEIGHT/100) + 23*SCREEN_HEIGHT/100, (ran+2)%11);
    xy_maker(rand()%(6*SCREEN_WIDTH/100) + 59*SCREEN_WIDTH/100,
             rand()%(14*SCREEN_HEIGHT/100) + 63*SCREEN_HEIGHT/100, (ran+3)%11);
    xy_maker(rand()%(13*SCREEN_WIDTH/100) + 57*SCREEN_WIDTH/100,
             rand()%(10*SCREEN_HEIGHT/100) + 30*SCREEN_HEIGHT/100, (ran+4)%11);
    xy_maker(rand()%(6*SCREEN_WIDTH/100) + 59*SCREEN_WIDTH/100,
             rand()%(10*SCREEN_HEIGHT/100) + 45*SCREEN_HEIGHT/100, (ran+5)%11);
    xy_maker(rand()%(5*SCREEN_WIDTH/100) + 92*SCREEN_WIDTH/100,
             rand()%(14*SCREEN_HEIGHT/100) + 66*SCREEN_HEIGHT/100, (ran+6)%11);
    xy_maker(rand()%(12*SCREEN_WIDTH/100) + 28*SCREEN_WIDTH/100,
             rand()%(13*SCREEN_HEIGHT/100) + 12*SCREEN_HEIGHT/100, (ran+7)%11);
    xy_maker(rand()%(8*SCREEN_WIDTH/100) + 75*SCREEN_WIDTH/100,
             rand()%(24*SCREEN_HEIGHT/100) + 23*SCREEN_HEIGHT/100, (ran+8)%11);
    xy_maker(rand()%(9*SCREEN_WIDTH/100) + 17*SCREEN_WIDTH/100,
             rand()%(15*SCREEN_HEIGHT/100) + 49*SCREEN_HEIGHT/100, (ran+9)%11);
    xy_maker(rand()%(4*SCREEN_WIDTH/100) + 4*SCREEN_WIDTH/100,
             rand()%(5*SCREEN_WIDTH/100) + 25*SCREEN_HEIGHT/100, (ran+10)%11);
}

void xy_maker(Sint16 mid_x, Sint16 mid_y, int index){
    x[index][0] = mid_x - l;
    x[index][1] = mid_x - l / 2;
    x[index][2] = mid_x + l / 2;
    x[index][3] = mid_x + l;
    x[index][4] = mid_x + l / 2;
    x[index][5] = mid_x - l / 2;
    y[index][0] = mid_y;
    y[index][1] = mid_y - 86 * l / 100;
    y[index][2] = mid_y - 86 * l / 100;
    y[index][3] = mid_y;
    y[index][4] = mid_y + 86 * l / 100;
    y[index][5] = mid_y + 86 * l / 100;
    all_bases.base_x[index] = mid_x;
    all_bases.base_y[index] = mid_y;
}

void input_struct(){
    for(int i = 0; i < 11;i++){
        all_bases.base_id[i] = 0xaaffffff;
        all_bases.base_points[i] = 10;
        all_bases.being_attacked[i] = false;
        all_bases.points_speed[i] = 1;
        all_bases.max_points[i] = 50;
    }
    for(int i = 0;i < 100;i++){
        for(int j = 0;j < 200;j++) {
            all_bases.marches[i].x[j] = 0;
            all_bases.marches[i].y[j] = 0;
            all_bases.marches[i].is_atk[j] = false;
        }
        all_bases.marches[i].vx = 0;
        all_bases.marches[i].vy = 0;
        marches_state[i] = false;
    }
    all_bases.base_id[0] = 0xaaffff46;
    all_bases.base_id[1] = 0xaaf010ff;
    all_bases.base_id[2] = 0xaae81815;
    all_bases.base_id[3] = 0xaa7a0a53;
    //for memory test
//    all_bases.base_id[2] = 0xaaffff46; all_bases.base_id[3] = 0xaaffff46; all_bases.base_id[4] = 0xaaffff46;
//    all_bases.base_id[5] = 0xaaffff46; all_bases.base_id[6] = 0xaaffff46; all_bases.base_id[7] = 0xaaffff46;
//    all_bases.base_id[8] = 0xaaffff46; all_bases.base_id[9] = 0xaaffff46; all_bases.base_id[10] = 0xaaffff46;
    for(int i = 0;i < 4;i++){
        all_potions.x[i] = 0;
        all_potions.y[i] = 0;
        all_potions.is_active[i] = false;
        all_potions.draw_potion[i] = false;
        all_potions.id[i] = -1;
        all_potions.timer[i] = -1;
    }
}

//drawings
void draw_map(){
    for(int i = 0;i < 11;i++){
        if(i == 0){
            filledPolygonColor(sdlRenderer, x[i], y[i], 6, all_bases.base_id[i]);
            polygonColor(sdlRenderer, x[i], y[i], 6, 0xff000000);
        }
        else if(i == 1){
            filledPolygonColor(sdlRenderer, x[i], y[i], 6, all_bases.base_id[i]);
            polygonColor(sdlRenderer, x[i], y[i], 6, 0xff000000);
        }
        else if(i == 2){
            filledPolygonColor(sdlRenderer, x[i], y[i], 6, all_bases.base_id[i]);
            polygonColor(sdlRenderer, x[i], y[i], 6, 0xff000000);
        }
        else if(i == 3){
            filledPolygonColor(sdlRenderer, x[i], y[i], 6, all_bases.base_id[i]);
            polygonColor(sdlRenderer, x[i], y[i], 6, 0xff000000);
        }
        else{
            filledPolygonColor(sdlRenderer, x[i], y[i], 6, all_bases.base_id[i]);
            polygonColor(sdlRenderer, x[i], y[i], 6, 0xff000000);
        }
        if(all_bases.base_id[i] != 0xaaffffff){
            if(all_bases.base_id[i] == 0xaaffff46) {
                filledCircleColor(sdlRenderer, all_bases.base_x[i], all_bases.base_y[i], l / 2,
                                  0xffffff46);
            }
            else if(all_bases.base_id[i] == 0xaaf010ff){
                filledCircleColor(sdlRenderer, all_bases.base_x[i], all_bases.base_y[i], l / 2,
                                  0xfff010ff);
            }
            else if(all_bases.base_id[i] == 0xaae81815){
                filledCircleColor(sdlRenderer, all_bases.base_x[i], all_bases.base_y[i], l / 2,
                                  0xffe81815);
            }
            else{
                filledCircleColor(sdlRenderer, all_bases.base_x[i], all_bases.base_y[i], l / 2,
                                  0xff7a0a53);
            }
        }
        sprintf(number, "%d", all_bases.base_points[i]);
        get_text_and_rect(color(0, 0, 0, 255), all_bases.base_x[i] - SCREEN_WIDTH/100,
                          all_bases.base_y[i] - SCREEN_HEIGHT/100, 2*SCREEN_WIDTH/100, 2*SCREEN_HEIGHT/100,
                          number, &points_tex,&points_rec);
        SDL_RenderCopy(sdlRenderer, points_tex, NULL, &points_rec);
    }
    if(all_potions.draw_potion[0]) {
        potions_rec.x = all_potions.x[0];
        potions_rec.y = all_potions.y[0];
        potions_rec.w = 50;
        potions_rec.h = 50;
        get_img_and_rect("../images/potion1.png", &potions_tex);
        SDL_RenderCopy(sdlRenderer, potions_tex, NULL, &potions_rec);
    }
    else if(!all_potions.draw_potion[0] && all_potions.is_active[0]){
        potions_rec.x = 5*SCREEN_WIDTH/100;
        potions_rec.y = 5*SCREEN_HEIGHT/100;
        potions_rec.w = 5*SCREEN_WIDTH/100;
        potions_rec.h = 5*SCREEN_WIDTH/100;
        sprintf(number, "%d", all_potions.timer[0]);
        if(all_potions.id[0] == 0xaaffff46){
            get_text_and_rect(color(70, 255, 255, 255), 5*SCREEN_WIDTH/100, 5*SCREEN_WIDTH/100,
                              5*SCREEN_WIDTH/100, 5*SCREEN_WIDTH/100, number, &potions_tex,
                              &potions_rec);
            SDL_RenderCopy(sdlRenderer, potions_tex, NULL, &potions_rec);
        }
        else if(all_potions.id[0] == 0xaaf010ff){
            get_text_and_rect(color(255, 160, 240, 255), 5*SCREEN_WIDTH/100, 5*SCREEN_WIDTH/100,
                              5*SCREEN_WIDTH/100, 5*SCREEN_WIDTH/100, number, &potions_tex,
                              &potions_rec);
            SDL_RenderCopy(sdlRenderer, potions_tex, NULL, &potions_rec);
        }
        else if(all_potions.id[0] == 0xaae81815){
            get_text_and_rect(color(21, 24, 232, 255), 5*SCREEN_WIDTH/100, 5*SCREEN_WIDTH/100,
                              5*SCREEN_WIDTH/100, 5*SCREEN_WIDTH/100, number, &potions_tex,
                              &potions_rec);
            SDL_RenderCopy(sdlRenderer, potions_tex, NULL, &potions_rec);
        }
        else if(all_potions.id[0] == 0xaa7a0a53){
            get_text_and_rect(color(83, 10, 122, 255), 5*SCREEN_WIDTH/100, 5*SCREEN_WIDTH/100,
                              5*SCREEN_WIDTH/100, 5*SCREEN_WIDTH/100, number, &potions_tex,
                              &potions_rec);
            SDL_RenderCopy(sdlRenderer, potions_tex, NULL, &potions_rec);
        }
    }
    else if(all_potions.draw_potion[1]) {
        potions_rec.x = all_potions.x[1];
        potions_rec.y = all_potions.y[1];
        potions_rec.w = 50;
        potions_rec.h = 50;
        get_img_and_rect("../images/potion2.png", &potions_tex);
        SDL_RenderCopy(sdlRenderer, potions_tex, NULL, &potions_rec);
    }
    else if(!all_potions.draw_potion[1] && all_potions.is_active[1]){
        potions_rec.x = 5*SCREEN_WIDTH/100;
        potions_rec.y = 5*SCREEN_HEIGHT/100;
        potions_rec.w = 5*SCREEN_WIDTH/100;
        potions_rec.h = 5*SCREEN_WIDTH/100;
        sprintf(number, "%d", all_potions.timer[1]);
        if(all_potions.id[1] == 0xaaffff46){
            get_text_and_rect(color(70, 255, 255, 255), 5*SCREEN_WIDTH/100, 5*SCREEN_WIDTH/100,
                              5*SCREEN_WIDTH/100, 5*SCREEN_WIDTH/100, number, &potions_tex,
                              &potions_rec);
            SDL_RenderCopy(sdlRenderer, potions_tex, NULL, &potions_rec);
        }
        else if(all_potions.id[1] == 0xaaf010ff){
            get_text_and_rect(color(255, 160, 240, 255), 5*SCREEN_WIDTH/100, 5*SCREEN_WIDTH/100,
                              5*SCREEN_WIDTH/100, 5*SCREEN_WIDTH/100, number, &potions_tex,
                              &potions_rec);
            SDL_RenderCopy(sdlRenderer, potions_tex, NULL, &potions_rec);
        }
        else if(all_potions.id[1] == 0xaae81815){
            get_text_and_rect(color(21, 24, 232, 255), 5*SCREEN_WIDTH/100, 5*SCREEN_WIDTH/100,
                              5*SCREEN_WIDTH/100, 5*SCREEN_WIDTH/100, number, &potions_tex,
                              &potions_rec);
            SDL_RenderCopy(sdlRenderer, potions_tex, NULL, &potions_rec);
        }
        else if(all_potions.id[1] == 0xaa7a0a53){
            get_text_and_rect(color(83, 10, 122, 255), 5*SCREEN_WIDTH/100, 5*SCREEN_WIDTH/100,
                              5*SCREEN_WIDTH/100, 5*SCREEN_WIDTH/100, number, &potions_tex,
                              &potions_rec);
            SDL_RenderCopy(sdlRenderer, potions_tex, NULL, &potions_rec);
        }
    }
    else if(all_potions.draw_potion[2]) {
        potions_rec.x = all_potions.x[2];
        potions_rec.y = all_potions.y[2];
        potions_rec.w = 50;
        potions_rec.h = 50;
        get_img_and_rect("../images/potion3.png", &potions_tex);
        SDL_RenderCopy(sdlRenderer, potions_tex, NULL, &potions_rec);
    }
    else if(!all_potions.draw_potion[2] && all_potions.is_active[2]){
        potions_rec.x = 5*SCREEN_WIDTH/100;
        potions_rec.y = 5*SCREEN_HEIGHT/100;
        potions_rec.w = 5*SCREEN_WIDTH/100;
        potions_rec.h = 5*SCREEN_WIDTH/100;
        sprintf(number, "%d", all_potions.timer[2]);
        if(all_potions.id[2] == 0xaaffff46){
            get_text_and_rect(color(70, 255, 255, 255), 5*SCREEN_WIDTH/100, 5*SCREEN_WIDTH/100,
                              5*SCREEN_WIDTH/100, 5*SCREEN_WIDTH/100, number, &potions_tex,
                              &potions_rec);
            SDL_RenderCopy(sdlRenderer, potions_tex, NULL, &potions_rec);
        }
        else if(all_potions.id[2] == 0xaaf010ff){
            get_text_and_rect(color(255, 160, 240, 255), 5*SCREEN_WIDTH/100, 5*SCREEN_WIDTH/100,
                              5*SCREEN_WIDTH/100, 5*SCREEN_WIDTH/100, number, &potions_tex,
                              &potions_rec);
            SDL_RenderCopy(sdlRenderer, potions_tex, NULL, &potions_rec);
        }
        else if(all_potions.id[2] == 0xaae81815){
            get_text_and_rect(color(21, 24, 232, 255), 5*SCREEN_WIDTH/100, 5*SCREEN_WIDTH/100,
                              5*SCREEN_WIDTH/100, 5*SCREEN_WIDTH/100, number, &potions_tex,
                              &potions_rec);
            SDL_RenderCopy(sdlRenderer, potions_tex, NULL, &potions_rec);
        }
        else if(all_potions.id[2] == 0xaa7a0a53){
            get_text_and_rect(color(83, 10, 122, 255), 5*SCREEN_WIDTH/100, 5*SCREEN_WIDTH/100,
                              5*SCREEN_WIDTH/100, 5*SCREEN_WIDTH/100, number, &potions_tex,
                              &potions_rec);
            SDL_RenderCopy(sdlRenderer, potions_tex, NULL, &potions_rec);
        }
    }
    else if(all_potions.draw_potion[3]) {
        potions_rec.x = all_potions.x[3];
        potions_rec.y = all_potions.y[3];
        potions_rec.w = 50;
        potions_rec.h = 50;
        get_img_and_rect("../images/potion4.png", &potions_tex);
        SDL_RenderCopy(sdlRenderer, potions_tex, NULL, &potions_rec);
    }
    else if(!all_potions.draw_potion[3] && all_potions.is_active[3]){
        potions_rec.x = 5*SCREEN_WIDTH/100;
        potions_rec.y = 5*SCREEN_HEIGHT/100;
        potions_rec.w = 5*SCREEN_WIDTH/100;
        potions_rec.h = 5*SCREEN_WIDTH/100;
        sprintf(number, "%d", all_potions.timer[3]);
        if(all_potions.id[3] == 0xaaffff46){
            get_text_and_rect(color(70, 255, 255, 255), 5*SCREEN_WIDTH/100, 5*SCREEN_WIDTH/100,
                              5*SCREEN_WIDTH/100, 5*SCREEN_WIDTH/100, number, &potions_tex,
                              &potions_rec);
            SDL_RenderCopy(sdlRenderer, potions_tex, NULL, &potions_rec);
        }
        else if(all_potions.id[3] == 0xaaf010ff){
            get_text_and_rect(color(255, 160, 240, 255), 5*SCREEN_WIDTH/100, 5*SCREEN_WIDTH/100,
                              5*SCREEN_WIDTH/100, 5*SCREEN_WIDTH/100, number, &potions_tex,
                              &potions_rec);
            SDL_RenderCopy(sdlRenderer, potions_tex, NULL, &potions_rec);
        }
        else if(all_potions.id[3] == 0xaae81815){
            get_text_and_rect(color(21, 24, 232, 255), 5*SCREEN_WIDTH/100, 5*SCREEN_WIDTH/100,
                              5*SCREEN_WIDTH/100, 5*SCREEN_WIDTH/100, number, &potions_tex,
                              &potions_rec);
            SDL_RenderCopy(sdlRenderer, potions_tex, NULL, &potions_rec);
        }
        else if(all_potions.id[3] == 0xaa7a0a53){
            get_text_and_rect(color(83, 10, 122, 255), 5*SCREEN_WIDTH/100, 5*SCREEN_WIDTH/100,
                              5*SCREEN_WIDTH/100, 5*SCREEN_WIDTH/100, number, &potions_tex,
                              &potions_rec);
            SDL_RenderCopy(sdlRenderer, potions_tex, NULL, &potions_rec);
        }
    }
}

void draw_march(){
    for(int i = 0;i < 100;i++){
        for(int j = 0;j < 200;j++){
            if(all_bases.marches[i].is_atk[j] == true){
                filledCircleColor(sdlRenderer, all_bases.marches[i].x[j],all_bases.marches[i].y[j],
                                  7,all_bases.marches[i].id);
            }
        }
    }
}

void top_four(SDL_Texture *places_tex, SDL_Rect places_rec){
    for(int i = 0;i < 4;i++){
        leader_base[i] = 0;
    }
    for(int i = 0;i < 10;i++){
        if(all_bases.base_id[i] == 0xaaffff46){
            leader_base[0]++;
        }
        else if(all_bases.base_id[i] == 0xaaf010ff){
            leader_base[1]++;
        }
        else if(all_bases.base_id[i] == 0xaae81815){
            leader_base[2]++;
        }
        else if(all_bases.base_id[i] == 0xaa7a0a53){
            leader_base[3]++;
        }
    }
    int first = -1;
    if(leader_base[0] >= leader_base[1] && leader_base[0] >= leader_base[2] && leader_base[0] >= leader_base[3]){
        first = 0;
    }
    else if(leader_base[1] >= leader_base[0] && leader_base[1] >= leader_base[2] && leader_base[1] >= leader_base[3]){
        first = 1;
    }
    else if(leader_base[2] >= leader_base[0] && leader_base[2] >= leader_base[1] && leader_base[2] >= leader_base[3]){
        first = 2;
    }
    else{
        first = 3;
    }
    boxColor(sdlRenderer, 83*SCREEN_WIDTH/100, SCREEN_HEIGHT/100, 99*SCREEN_WIDTH/100,
             7*SCREEN_HEIGHT/100, 0xffffffff);
    sprintf(number, "%d", leader_base[first]);
    if(first == 0) {
        get_text_and_rect(color(70, 255, 255, 255), 85 * SCREEN_WIDTH / 100,
                          2 * SCREEN_HEIGHT / 100,6 * SCREEN_WIDTH / 100, 4 * SCREEN_HEIGHT / 100,
                          "You", &places_tex,&places_rec);
        SDL_RenderCopy(sdlRenderer, places_tex, NULL, &places_rec);
        get_text_and_rect(color(70, 255, 255, 255), 95*SCREEN_WIDTH/100, 2*SCREEN_HEIGHT/100,
                          2*SCREEN_WIDTH/100, 4*SCREEN_HEIGHT/100, number, &places_tex,
                          &places_rec);
        SDL_RenderCopy(sdlRenderer, places_tex, NULL, &places_rec);
    }
    else if(first == 1) {
        get_text_and_rect(color(255, 160, 240, 255), 85 * SCREEN_WIDTH / 100,
                          2 * SCREEN_HEIGHT / 100,8 * SCREEN_WIDTH / 100, 4 * SCREEN_HEIGHT / 100,
                          "Pink", &places_tex,&places_rec);
        SDL_RenderCopy(sdlRenderer, places_tex, NULL, &places_rec);
        get_text_and_rect(color(255, 160, 240, 255), 95*SCREEN_WIDTH/100, 2*SCREEN_HEIGHT/100,
                          2*SCREEN_WIDTH/100, 4*SCREEN_HEIGHT/100, number, &places_tex,
                          &places_rec);
        SDL_RenderCopy(sdlRenderer, places_tex, NULL, &places_rec);
    }
    else if(first == 2) {
        get_text_and_rect(color(21, 24, 232, 255), 85 * SCREEN_WIDTH / 100,
                          2 * SCREEN_HEIGHT / 100,8 * SCREEN_WIDTH / 100, 4 * SCREEN_HEIGHT / 100,
                          "Blue", &places_tex,&places_rec);
        SDL_RenderCopy(sdlRenderer, places_tex, NULL, &places_rec);
        get_text_and_rect(color(21, 24, 232, 255), 95*SCREEN_WIDTH/100, 2*SCREEN_HEIGHT/100,
                          2*SCREEN_WIDTH/100, 4*SCREEN_HEIGHT/100, number, &places_tex,
                          &places_rec);
        SDL_RenderCopy(sdlRenderer, places_tex, NULL, &places_rec);
    }
    else if(first == 3) {
        get_text_and_rect(color(83, 10, 122, 255), 85 * SCREEN_WIDTH / 100,
                          2 * SCREEN_HEIGHT / 100,9 * SCREEN_WIDTH / 100, 4 * SCREEN_HEIGHT / 100,
                          "Purple", &places_tex,&places_rec);
        SDL_RenderCopy(sdlRenderer, places_tex, NULL, &places_rec);

        get_text_and_rect(color(83, 10, 122, 255), 95*SCREEN_WIDTH/100, 2*SCREEN_HEIGHT/100,
                          2*SCREEN_WIDTH/100, 4*SCREEN_HEIGHT/100, number, &places_tex,
                          &places_rec);
        SDL_RenderCopy(sdlRenderer, places_tex, NULL, &places_rec);
    }
}

//logics
void selecting_bases(SDL_Event e){
    for(int i = 0;i < 11;i++){
        if(abs(e.button.x - all_bases.base_x[i]) < l && abs(e.button.y - all_bases.base_y[i]) < l){
            if(first_base == -1 && all_bases.base_id[i] == 0xaaffff46){
                first_base = i;
            }
            else{
                second_base = i;
                if(second_base != first_base) {
                    make_attack();
                }
            }
            break;
        }
    }
}

void make_attack(){
    if(first_base >= 0 && second_base >= 0 && first_base <= 10 && second_base <= 10) {
        delta_y = (double) (all_bases.base_y[second_base] - all_bases.base_y[first_base]);
        delta_x = (double) (all_bases.base_x[second_base] - all_bases.base_x[first_base]);
        theta = atan(delta_y / delta_x);
        for(int i = 0;i < 100;i++){
            if(marches_state[i] == false){
                all_bases.marches[i].vx = speed * cos(theta);
                all_bases.marches[i].vy = speed * sin(theta);
                if (delta_x < 0 && all_bases.marches[i].vx > 0) {
                    all_bases.marches[i].vx *= -1;
                }
                else if (delta_x > 0 && all_bases.marches[i].vx < 0) {
                    all_bases.marches[i].vx *= -1;
                }
                if (delta_y < 0 && all_bases.marches[i].vy > 0) {
                    all_bases.marches[i].vy *= -1;
                }
                else if (delta_y > 0 && all_bases.marches[i].vy < 0) {
                    all_bases.marches[i].vy *= -1;
                }
                all_bases.marches[i].total_soldiers = all_bases.base_points[first_base];
                all_bases.base_points[first_base] = 0;
                all_bases.being_attacked[second_base] = true;
                all_bases.marches[i].src_index = first_base;
                all_bases.marches[i].des_index = second_base;
                all_bases.marches[i].id = all_bases.base_id[first_base];
                marches_state[i] = true;
                first_base = -1;
                second_base = -1;
                break;
            }
        }
    }
}

void make_potion(){
    int tmp_ran1 = rand()%10, tmp_ran2 = (tmp_ran1+3)%10;
    switch (potion_ran) {
        case 0:
            if(!all_potions.draw_potion[potion_ran] && !all_potions.is_active[potion_ran]){
                all_potions.x[potion_ran] = (all_bases.base_x[tmp_ran1]+all_bases.base_x[tmp_ran2])/2;
                all_potions.y[potion_ran] = (all_bases.base_y[tmp_ran1]+all_bases.base_y[tmp_ran2])/2;
                all_potions.draw_potion[potion_ran] = true;
            }
            if(all_potions.is_active[potion_ran] == false){
                for(int i = 0;i < 100;i++){
                    for(int j = 0;j < 200;j++){
                        if(abs(all_bases.marches[i].x[j] - all_potions.x[potion_ran]) < 50 &&
                           abs(all_bases.marches[i].y[j] - all_potions.y[potion_ran]) < 50){
                            all_potions.is_active[potion_ran] = true;
                            all_potions.timer[potion_ran] = 10;
                            all_potions.id[potion_ran] = all_bases.marches[i].id;

                            all_potions.draw_potion[potion_ran] = false;
                            return;
                        }
                    }
                }
            }
            else if((all_potions.is_active[potion_ran] && all_potions.timer[potion_ran] > 0)){
                if(point_adder%10 == 0){
                    all_potions.timer[potion_ran]--;
                }
            }
            else if(all_potions.timer[potion_ran] == 0){
                all_potions.is_active[potion_ran] = false;
                all_potions.timer[potion_ran] = -1;
                all_potions.id[potion_ran] = -1;
                potion_ran++;
                potion_ran %= 4;
            }
            break;
        case 1:
            if(!all_potions.draw_potion[potion_ran] && !all_potions.is_active[potion_ran]){
                all_potions.x[potion_ran] = (all_bases.base_x[tmp_ran1]+all_bases.base_x[tmp_ran2])/2;
                all_potions.y[potion_ran] = (all_bases.base_y[tmp_ran1]+all_bases.base_y[tmp_ran2])/2;
                all_potions.draw_potion[potion_ran] = true;
            }
            if(all_potions.is_active[potion_ran] == false){
                for(int i = 0;i < 100;i++){
                    for(int j = 0;j < 200;j++){
                        if(abs(all_bases.marches[i].x[j] - all_potions.x[potion_ran]) < 50 &&
                           abs(all_bases.marches[i].y[j] - all_potions.y[potion_ran]) < 50){
                            all_potions.is_active[potion_ran] = true;
                            all_potions.timer[potion_ran] = 10;
                            all_potions.id[potion_ran] = all_bases.marches[i].id;
                            all_potions.draw_potion[potion_ran] = false;
                            return;
                        }
                    }
                }
            }
            else if((all_potions.is_active[potion_ran] && all_potions.timer[potion_ran] > 0)){
                if(point_adder%10 == 0){
                    all_potions.timer[potion_ran]--;
                }
            }
            else if(all_potions.timer[potion_ran] == 0){
                all_potions.is_active[potion_ran] = false;
                all_potions.timer[potion_ran] = -1;
                all_potions.id[potion_ran] = -1;
                potion_ran++;
                potion_ran %= 4;
            }
            break;
        case 2:
            if(!all_potions.draw_potion[potion_ran] && !all_potions.is_active[potion_ran]){
                all_potions.x[potion_ran] = (all_bases.base_x[tmp_ran1]+all_bases.base_x[tmp_ran2])/2;
                all_potions.y[potion_ran] = (all_bases.base_y[tmp_ran1]+all_bases.base_y[tmp_ran2])/2;
                all_potions.draw_potion[potion_ran] = true;
            }
            if(all_potions.is_active[potion_ran] == false){
                for(int i = 0;i < 100;i++){
                    for(int j = 0;j < 200;j++){
                        if(abs(all_bases.marches[i].x[j] - all_potions.x[potion_ran]) < 50 &&
                           abs(all_bases.marches[i].y[j] - all_potions.y[potion_ran]) < 50){
                            all_potions.is_active[potion_ran] = true;
                            all_potions.timer[potion_ran] = 10;
                            all_potions.id[potion_ran] = all_bases.marches[i].id;
                            for(int k = 0;k < 11;k++){
                                if(all_bases.base_id[k] == all_potions.id[potion_ran]){
                                    all_bases.max_points[k] = 1000;
                                }
                            }
                            all_potions.draw_potion[potion_ran] = false;
                            return;
                        }
                    }
                }
            }
            else if((all_potions.is_active[potion_ran] && all_potions.timer[potion_ran] > 0)){
                for(int k = 0;k < 11;k++){
                    if(all_bases.base_id[k] == all_potions.id[potion_ran]){
                        all_bases.max_points[k] = 1000;
                    }
                }
                if(point_adder%10 == 0){
                    all_potions.timer[potion_ran]--;
                }
            }
            else if(all_potions.timer[potion_ran] == 0){
                all_potions.is_active[potion_ran] = false;
                all_potions.timer[potion_ran] = -1;
                for(int k = 0;k < 11;k++){
                    if(all_bases.base_id[k] == all_potions.id[potion_ran]){
                        all_bases.max_points[k] = 50;
                    }
                }
                all_potions.id[potion_ran] = -1;
                potion_ran++;
                potion_ran %= 4;
            }
            break;
        case 3:
            if(!all_potions.draw_potion[potion_ran] && !all_potions.is_active[potion_ran]){
                all_potions.x[potion_ran] = (all_bases.base_x[tmp_ran1]+all_bases.base_x[tmp_ran2])/2;
                all_potions.y[potion_ran] = (all_bases.base_y[tmp_ran1]+all_bases.base_y[tmp_ran2])/2;
                all_potions.draw_potion[potion_ran] = true;
            }
            if(all_potions.is_active[potion_ran] == false){
                for(int i = 0;i < 100;i++){
                    for(int j = 0;j < 200;j++){
                        if(abs(all_bases.marches[i].x[j] - all_potions.x[potion_ran]) < 50 &&
                           abs(all_bases.marches[i].y[j] - all_potions.y[potion_ran]) < 50){
                            all_potions.is_active[potion_ran] = true;
                            all_potions.timer[potion_ran] = 10;
                            all_potions.id[potion_ran] = all_bases.marches[i].id;
                            for(int k = 0;k < 11;k++){
                                if(all_bases.base_id[k] == all_potions.id[potion_ran]){
                                    all_bases.points_speed[k] = 2;
                                }
                            }
                            all_potions.draw_potion[potion_ran] = false;
                            return;
                        }
                    }
                }
            }
            else if((all_potions.is_active[potion_ran] && all_potions.timer[potion_ran] > 0)){
                for(int k = 0;k < 11;k++){
                    if(all_bases.base_id[k] == all_potions.id[potion_ran]){
                        all_bases.points_speed[k] = 2;
                    }
                }
                if(point_adder%10 == 0){
                    all_potions.timer[potion_ran]--;
                }
            }
            else if(all_potions.timer[potion_ran] == 0){
                all_potions.is_active[potion_ran] = false;
                all_potions.timer[potion_ran] = -1;
                for(int k = 0;k < 11;k++){
                    if(all_bases.base_id[k] == all_potions.id[potion_ran]){
                        all_bases.points_speed[k] = 1;
                    }
                }
                all_potions.id[potion_ran] = -1;
                potion_ran++;
                potion_ran %= 4;
            }
            break;
        default:
            break;
    }

}

void make_march(){
    for(int i = 0;i < 100;i++){
        if (all_bases.marches[i].total_soldiers > 0) {
            all_bases.marches[i].x[all_bases.marches[i].total_soldiers] +=
                    all_bases.base_x[all_bases.marches[i].src_index] + all_bases.marches[i].vx;
            all_bases.marches[i].y[all_bases.marches[i].total_soldiers] +=
                    all_bases.base_y[all_bases.marches[i].src_index] + all_bases.marches[i].vy;
            all_bases.marches[i].is_atk[all_bases.marches[i].total_soldiers] = true;
            all_bases.marches[i].total_soldiers--;
        }
    }
}

void apply_speed_point(){
    for(int i = 0;i < 11;i++) {
        if (all_bases.base_id[i] != 0xaaffffff) {
            if (point_adder % 2 == 0 && all_bases.base_points[i] < all_bases.max_points[i]) {
                all_bases.base_points[i] += all_bases.points_speed[i];
            }
        }
    }
    for(int j = 0;j < 100;j++){
        for (int z = 0; z < 200; z++) {
            if (all_bases.marches[j].is_atk[z] == true) {
                delta_y = (double)(all_bases.base_y[all_bases.marches[j].des_index]-all_bases.marches[j].y[z]);
                delta_x = (double)(all_bases.base_x[all_bases.marches[j].des_index]-all_bases.marches[j].x[z]);

                theta = atan(delta_y/delta_x);
                all_bases.marches[j].vx = speed*cos(theta);
                all_bases.marches[j].vy = speed*sin(theta);
                if(delta_x < 0 && all_bases.marches[j].vx > 0){
                    all_bases.marches[j].vx *= -1;
                }
                else if(delta_x > 0 && all_bases.marches[j].vx < 0){
                    all_bases.marches[j].vx *= -1;
                }
                if(delta_y < 0 && all_bases.marches[j].vy > 0){
                    all_bases.marches[j].vy *= -1;
                }
                else if(delta_y > 0 && all_bases.marches[j].vy < 0){
                    all_bases.marches[j].vy *= -1;
                }
                if(all_potions.is_active[0] && all_potions.id[0] == all_bases.marches[j].id){
                    all_bases.marches[j].vx *= 2;
                    all_bases.marches[j].vy *= 2;
                }
                else if(all_potions.is_active[1] && all_potions.id[1] != all_bases.marches[j].id){
                    all_bases.marches[j].vx *= 0.5;
                    all_bases.marches[j].vy *= 0.5;
                }
                all_bases.marches[j].x[z] += all_bases.marches[j].vx;
                all_bases.marches[j].y[z] += all_bases.marches[j].vy;
            }
        }
    }
}

void stop_speed(){
    for(int i = 0;i < 100;i++){
        for(int j = 0;j < 200;j++){
            if(all_bases.marches[i].is_atk[j] == true){
                if((abs(all_bases.marches[i].x[j]-all_bases.base_x[all_bases.marches[i].des_index]) < l/2 &&
                    abs(all_bases.marches[i].y[j]-all_bases.base_y[all_bases.marches[i].des_index]) < l/2)){
                    all_bases.marches[i].is_atk[j] = false;
                    all_bases.marches[i].x[j] = 0;
                    all_bases.marches[i].y[j] = 0;
                    if(all_bases.marches[i].id == all_bases.base_id[all_bases.marches[i].des_index]){
                        all_bases.base_points[all_bases.marches[i].des_index]++;
                    }
                    else{
                        if(all_bases.base_points[all_bases.marches[i].des_index] < 2){
                            all_bases.base_id[all_bases.marches[i].des_index] = all_bases.marches[i].id;
                        }
                        else {
                            if(all_bases.base_id[all_bases.marches[i].des_index] == 0xaaffffff) {
                                all_bases.base_points[all_bases.marches[i].des_index]--;
                            }
                            else{
                                all_bases.base_points[all_bases.marches[i].des_index] -= 2;
                            }
                        }

                    }
                    if(j <= 1){
                        all_bases.being_attacked[all_bases.marches[i].des_index] = false;
                        marches_state[i] = false;
                    }
                }
            }
        }
    }
}

void check_accidents(){
    for(int i = 0;i < 99;i++){
        for(int j = i+1;j < 100;j++){
            for(int k = 0;k < 200;k++){
                for(int z = 0;z < 200;z++){
                    if(all_bases.marches[i].is_atk[k] && all_bases.marches[j].is_atk[z] && all_bases.marches[i].id !=
                                                                                           all_bases.marches[j].id) {
                        if (abs(all_bases.marches[i].x[k] - all_bases.marches[j].x[z]) < 14 &&
                            abs(all_bases.marches[i].y[k] - all_bases.marches[j].y[z]) < 14) {
                            all_bases.marches[i].x[k] = 0;
                            all_bases.marches[i].y[k] = 0;
                            all_bases.marches[j].x[z] = 0;
                            all_bases.marches[j].x[z] = 0;
                            all_bases.marches[i].is_atk[k] = false;
                            all_bases.marches[j].is_atk[z] = false;
                        }
                    }
                }
            }
        }
    }
}

void bot_movements(int index){
    if(point_adder%10 == 0) {
        if (all_bases.base_id[index] != 0xaaffff46 && all_bases.base_id[index] != 0xaaffffff) {
            for (int i = 0; i < 11; i++) {
                if (i != index && all_bases.base_id[i] == 0xaaffffff && all_bases.being_attacked[i] == false) {
                    first_base = index;
                    second_base = i;
                    make_attack();
                    break;
                } else if (i != index && all_bases.base_id[i] == all_bases.base_id[index] &&
                           all_bases.being_attacked[i] == true &&
                           all_bases.base_points[i] < all_bases.base_points[index]) {
                    first_base = index;
                    second_base = i;
                    make_attack();
                    break;
                } else if (i != index && all_bases.base_points[index] >= 20 && all_bases.base_id[i] !=
                                                                               all_bases.base_id[index] &&
                           all_bases.being_attacked[i] == false &&
                           all_bases.base_points[index] > all_bases.base_points[i] + 10 && leader_base[0] > 4) {
                    first_base = index;
                    second_base = i;
                    make_attack();
                    break;
                } else if (i != index && point_adder > 100 && leader_base[0] < 4 &&
                           all_bases.base_id[i] == 0xaaffff46 &&
                           all_bases.being_attacked[i] == false) {
                    first_base = index;
                    second_base = i;
                    make_attack();
                    break;
                }
            }
        }
    }
}

void check_winner(){
    int flag = 0;
    for(int i = 0;i < 11;i++){
        if(all_bases.base_id[i] == 0xaaffff46){
            flag++;
        }
    }
    if(flag == 11){
        won = true;
        goto_game = false;
        goto_winner = true;
        save_map();
        get_text_and_rect(color(70, 255, 255, 255), 13*SCREEN_WIDTH/100, 35*SCREEN_HEIGHT/100,
                          75*SCREEN_WIDTH/100, 8*SCREEN_HEIGHT/100, "Congrats on your win!",
                          &congrats, &congrats_rec);
        if(pick_easy){
            get_text_and_rect(color(70, 255, 255, 255), 35*SCREEN_WIDTH/100,
                              45*SCREEN_HEIGHT/100,30*SCREEN_WIDTH/100, 8*SCREEN_HEIGHT/100,
                              "You won 20 pts", &winning_point, &winning_point_rec);
            add_point_to_player(20);
        }
        else if(pick_medium){
            get_text_and_rect(color(70, 255, 255, 255), 35*SCREEN_WIDTH/100,
                              45*SCREEN_HEIGHT/100,30*SCREEN_WIDTH/100, 8*SCREEN_HEIGHT/100,
                              "You won 40 pts", &winning_point, &winning_point_rec);
            add_point_to_player(40);
        }
        else if(pick_hard){
            get_text_and_rect(color(70, 255, 255, 255), 35*SCREEN_WIDTH/100,
                              45*SCREEN_HEIGHT/100,30*SCREEN_WIDTH/100, 8*SCREEN_HEIGHT/100,
                              "You won 60 pts", &winning_point, &winning_point_rec);
            add_point_to_player(60);
        }
        else{
            get_text_and_rect(color(70, 255, 255, 255), 35*SCREEN_WIDTH/100,
                              45*SCREEN_HEIGHT/100,30*SCREEN_WIDTH/100, 8*SCREEN_HEIGHT/100,
                              "You won 40 pts", &winning_point, &winning_point_rec);
            add_point_to_player(40);
        }
        sort_players();
    }
    else if(flag == 0){
        won = false;
        goto_game = false;
        goto_winner = true;
        save_map();
        get_text_and_rect(color(70, 255, 255, 255), 13*SCREEN_WIDTH/100, 35*SCREEN_HEIGHT/100,
                          75*SCREEN_WIDTH/100, 8*SCREEN_HEIGHT/100, "Better luck next time :(",
                          &congrats, &congrats_rec);
        get_text_and_rect(color(70, 255, 255, 255), 35*SCREEN_WIDTH/100,
                          45*SCREEN_HEIGHT/100,30*SCREEN_WIDTH/100, 8*SCREEN_HEIGHT/100,
                          "You lost 15 pts", &winning_point, &winning_point_rec);
        add_point_to_player(-15);
        sort_players();
    }
}




