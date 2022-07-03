#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#include "entity.h"
#include "npc.h"
#include "player.h"
#include "combat.h"
#include "location.h"

Location locations[] = {{"cemetery", " You are in a cemetery, surrounded by ash, from a narrow passage you see a [field]", {}, 0, {field}, 1, {Old_man}, 1}, 
{"field", " Through the passage you emerge onto a small plain, behind you is the [cemetery], ahead the [forest]",{Potion, Rusty_sword, Leather_armour}, 3, {cemetery, forest}, 2, {Orc}, 1},
{"forest", " The plain eventually dissipates into a dense forest,\n with high tree tops and dense foliage one would be careful to traverse here",{Potion}, 1, {field}, 1, {}, 0}};

const char vowels[5] = {'a', 'e', 'i', 'o', 'u'};

#define n_locations (sizeof locations / sizeof *locations)

void issue_quests(Player *player, NPC *x){
    if(x->quest != NULL){
    x->quest->quest_start();
    player->questlog[player->n_quests++] = x->quest;
    x->times_talked++;
    }
}

Location *location_from_subject(const char *subject){
    int index = -1;
    Location *result;
    for(int i = 0; i < n_locations;i++){
        if(strcmp(subject, locations[i].name) == 0)
            index = i;
    }
    if(index == -1)
        return NULL;
    result = &locations[index];
    return result;
}

int is_destinations(Location *current, Location *destination){
    for(int i = 0; i<current->n_destinations;i++)
        if(current->destinations[i] == destination)
            return 1;
    return 0;
}

void show_loc_entities(Location *location){
    print_unique_items(location->l_entities, location->n_entities);
}

int str_find(const char *s, char x){
  for (int i = 0; s[i] != '\0'; i++)
    if (s[i] == x)
      return i;
  return -1;
}

int is_vowel(const char *s, char x){
    return str_find(s, x) != -1;
}

void show_loc_npcs(Location *location){
    printf("\n");
    for(int i = 0; i < location->n_actors; i++){
        if(is_vowel(vowels, location->actors[i]->name[0]))
            printf(" An %s\n", location->actors[i]->name);
        else
            printf(" A %s\n", location->actors[i]->name);
    }
}

void command_look(const char * subject, Player *player){
    if(subject != NULL && strcmp(subject, "\n") != 0 && strcmp(subject, "around") == 0){
        printf("\n%s\n",player->location->description);
        if(player->location->n_actors > 0){
            printf("\n You can see:\n");
            show_loc_npcs(player->location);
        }
        if(player->location->n_entities > 0){
            printf("\n You also see a few items\n");
            show_loc_entities(player->location);
        }
    }
    else if(subject != NULL && strcmp(subject, "\n") != 0){
        NPC *to_look = npc_from_subject(subject);
        if(to_look != NULL && is_npc_inloc(to_look, player->location->actors, player->location->n_actors))
            look_NPC(to_look);
        else
            printf("\n Who do you wan't to look at exactly?\n");
    }
    else{
        printf("\n I'm not sure where you want me to look\n");
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
                    command_look("around", player);
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

int find_npc_in_literal(NPC *x, Location *y){
    for(int i = 0; i < y->n_actors;i++)
        if(y->actors[i] == x)
            return i;
    return -1;
}

void tutorial_event(void){
    printf("\n In a coffin you sleep, tranquil, but as a light shines on your dead body you seem to reanimate and stand up, you hear a voice\n");
    printf("\n [old man] : Hey you seem to be asleep for a long time, dont forget to [look around] the place, you might find somewhere to [go], items to [get] or people to [talkto] , or [fight] if thats your thing.\n");
    printf("\n [old man] : Well I'll be staying here, [talkto] me if you need anything and if you need [help].\n");
}

void help_command(void){
    printf("You seem to know how to:\n [look] \n [go] \n [inspect] \n [backpack] \n [purse] \n [equip] \n [status] \n [get] \n [equipment] \n [drop] \n [use]");
}


// // First quest start
// int orc_kill_complete(){
//     return !is_npc_inloc(Orc, field->actors, field->n_actors);
// }

// void orc_kill_quest_start(){
//     printf("\n [old man] : Hey I would leave here but that orc over in the [field] is really causing me trouble can you deal with him?\n");
//     printf("\n QUEST ISSUED: \n Kill the [orc] in the [field] and come back \n");
// }

// void orc_kill_reward(){
//     printf("\n [old man] : Thanks for getting rid of the orc, but I'm actually quite confortable here \n");
// }

// First quest end


// Quest quests[] = {{"Big green baddie", "Kill the orc in the field", &orc_kill_quest_start, &orc_kill_complete, &orc_kill_reward}};


