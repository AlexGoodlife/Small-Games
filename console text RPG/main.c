#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "entity.h"
#include "npc.h"
#include "location.h"
#include "player.h"
#include "combat.h"
#include "commands.h"

#define MAX_INPUT 128
const char* author = "Alexandre Boavida 68781";

static char input[100] = " ";

int getInput(void){
    printf("\n-->");
    return fgets(input, sizeof input, stdin) != NULL;

}


int game_loop(Player *player, char *input){
    if(input == NULL || strcmp(input, "\n") == 0 || strcmp(input, " ") == 0){
        printf("\n Type a command please\n");
        return 1;
    }
    const char * command = strtok(input, " \n");
    const char * subject = strtok(NULL, "\n");
    if(strcmp(command, "quit") == 0)
        return 0;
    else if(strcmp(command, "look") == 0){
        command_look(subject, player->location);
        return 1;
    }
     else if(strcmp(command, "go") == 0){
        command_go(subject, player);
        return 1;
    }
    else if(strcmp(command, "inspect") == 0){
        // printf("%s\n", subject);
        true_inspect(subject, player);
        return 1;
    }
    else if(strcmp(command, "get") == 0){
        // printf("%s\n", subject);
        command_get(subject, player);
        return 1;
    }
    else if(strcmp(command, "backpack") == 0){
        // printf("%s\n", subject);
        show_inventory(player);
        return 1;
    }
    else if(strcmp(command, "purse") == 0){
        // printf("%s\n", subject);
        show_purse(player);
        return 1;
    }
    else if(strcmp(command, "equipment") == 0){
        // printf("%s\n", subject);
        show_equipment(player);
        return 1;
    }
    else if(strcmp(command, "equip") == 0){
        // printf("%s\n", subject);
        equip_item(subject, player);
        return 1;
    }
    else if(strcmp(command, "drop") == 0){
        // printf("%s\n", subject);
        drop_item(subject, player);
        return 1;
    }
    else if(strcmp(command, "use") == 0){
        // printf("%s\n", subject);
        command_use(subject, player);
        return 1;
    }
    else if(strcmp(command, "status") == 0){
        // printf("%s\n", subject);
        show_status(player);
        return 1;
    }
    else if(strcmp(command, "talkto") == 0){
        // printf("%s\n", subject);
        command_talk(subject, player);
        return 1;
    }
    else if(strcmp(command, "fight") == 0){
        // printf("%s\n", subject);
        return command_fight(subject, player);
    }
    else if(strcmp(command, "questlog") == 0){
        // printf("%s\n", subject);
        check_questlog(player);
        return 1;
    }
    else if(strcmp(command, "help") == 0){
        // printf("%s\n", subject);
        help_command();
        return 1;
    }
    else{
        printf(" Do not know how to do that\n");
        return 1;
    }
}


int main(void){
    time_t seconds = time(NULL);
    srand(seconds);
    printf(" Welcome stupid fucking rpg\n");
    tutorial_event();
    Player *player = initialize_player(25,20, Fists, Loin_cloth,cemetery);
    // Player *test_player = initialize_player(25, 20, Giga_sword, Loin_cloth, cemetery);
    while(game_loop(player,input) && getInput());
    printf(" \n Thank you for playing! Press any key to close\n");
    while(!kbhit());
    return 0;
}
