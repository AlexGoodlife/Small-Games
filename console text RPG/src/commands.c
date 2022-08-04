#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "../include/commands.h" 


void issue_quests(Player *player, NPC *x){
    if(x->quest != NULL){
        x->quest->quest_start();
        player->questlog[player->n_quests++] = x->quest;
        x->times_talked++;
    }
}

void command_go(const char * subject, Player *player){
    if(subject != NULL && strcmp(subject, " \n") != 0){
        Location *to_go = location_from_subject(subject);
        if(strcmp(subject, player->location->name)== 0 && to_go != NULL)
                printf(" You're already there\n");
        else {
            if(is_destinations(player->location, to_go) && to_go != NULL){
                    player->location = to_go;
                    printf("\n You travel to [%s]\n", to_go->name);
                    command_look("around", player->location);
                }
            else
                printf("\n You can't go there from here\n");
        }
    }
    else
        printf("\n I'm not sure where you want me to go\n");
}

void command_talk(const char * subject, Player *player){
    if(subject != NULL && strcmp(subject, "\n") != 0){
        NPC *to_look = npc_from_subject(subject);
        if(to_look != NULL && is_npc_inloc(to_look, player->location->actors, player->location->n_actors) && to_look->times_talked == 0 && to_look->quest != NULL)
            issue_quests(player, to_look);
        else if(to_look != NULL && is_npc_inloc(to_look, player->location->actors, player->location->n_actors)){
            check_npc_quest(player->questlog, player->n_quests, to_look, player);
            talk_to(to_look);
        }
        else
            printf("\n Who do you want to talk to exactly?\n");
    }
    else{
        printf("\n I'm not sure where you want me to look\n");
    }
}

int command_fight(const char * subject, Player *player){
    int check = 1;
    if(subject != NULL && strcmp(subject, "\n") != 0){
        NPC *to_fight = npc_from_subject(subject);
        if(to_fight != NULL && is_npc_inloc(to_fight, player->location->actors, player->location->n_actors))
            check = combat_start(player, to_fight);
        else{
            printf("\n Who do you want to fight exactly?\n");
            return check;
        }
        if(check == 3){
            check = 1;
            combat_end(player, to_fight);
            player->location->n_actors = remove_npc(player->location->actors, player->location->n_actors, to_fight);
        }
        if(check == 2){
            printf("\n You ran away from [%s]!A tactical move or a cowardly one?\n", to_fight->name);
            check = 1;
        }
        return check;

    }
    else{
        printf("\n I'm not sure who you want me to fight\n");
        return check;
    }
}

void check_questlog(Player *player){
    printf("\n These are your active quests:\n");
    for(int i = 0; i < player->n_quests;i++){
        printf(" %s -> %s", player->questlog[i]->title, player->questlog[i]->description);
    }
}

void help_command(void){
    printf("You seem to know how to:\n [look] \n [go] \n [inspect] \n [backpack] \n [purse] \n [equip] \n [status] \n [get] \n [equipment] \n [drop] \n [use]");
}

