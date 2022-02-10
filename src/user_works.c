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
