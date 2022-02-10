#include "functions.h"
#include "variables.h"

void get_all_usernames(){
    FILE* f = fopen("username.txt", "r");
    for(int i = 0;!feof(f);i++){
        fscanf(f, "%d %d %[^\n]s", &all_players[i].ranking, &all_players[i].total_pt,
               all_players[i].username);
        count_players = i;
    }
    fclose(f);
}

void put_all_usernames_in_file(){
    remove("username.txt");
    FILE* f = fopen("username.txt", "w");
    for(int i = 0;i < count_players;i++){
        fprintf(f, "%d %d %s\n", all_players[i].ranking,  all_players[i].total_pt,
                all_players[i].username);
    }
    fclose(f);
}

int compare_by_points(const void* first, const void* second){
    player* p1 = (player*)first;
    player* p2 = (player*)second;

    return p2->total_pt - p1->total_pt;
}

void add_player(){
    all_players[count_players] = create_player();
    count_players++;
}

player create_player(){
    player new_player;
    strcpy(new_player.username, username);
    new_player.ranking = 0;
    new_player.total_pt = 0;
    return new_player;
}

int check_for_duplicate(){
    for(int i = 0;i < count_players;i++){
        if(!strcmp(username, all_players[i].username)){
            return 0;
        }
    }
    return 1;
}

void sort_players(){
    qsort(all_players, count_players, sizeof(player), compare_by_points);
    for(int i = 0;i <= count_players;i++){
        all_players[i].ranking = i+1;
    }
}

void add_point_to_player(int point){
    for(int i = 0;i <= count_players;i++){
        if(!strcmp(all_players[i].username, username)){
            if((point < 0 && all_players[i].total_pt >= 15) || point > 0) {
                all_players[i].total_pt += point;
            }
            break;
        }
    }
}

void read_old_map(){
    FILE* f = fopen("map.txt", "r");
    char* tmp_username = (char*)malloc(sizeof(char)*15);
    for(int i = 0;i < 11;i++){
        if(i == 0){
            fscanf(f, "%s\n", tmp_username);
        }
        fscanf(f, "%d %d\n", &new_map_x[i], &new_map_y[i]);
        xy_maker(new_map_x[i], new_map_y[i], i);
    }
}

void save_map(){
    remove("map.txt");
    FILE* f = fopen("map.txt", "w");
    fprintf(f, "%s\n", username);
    for(int i = 0;i < 11;i++){
        fprintf(f, "%d %d\n", all_bases.base_x[i], all_bases.base_y[i]);
    }
    fclose(f);
}
