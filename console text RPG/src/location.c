#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#include "../include/location.h"

Location locations[] = {{"cemetery", " You are in a cemetery, surrounded by ash, from a narrow passage you see a [field]", {}, 0, {field}, 1, {Old_man}, 1}, 
{"field", " Through the passage you emerge onto a small plain, behind you is the [cemetery], ahead the [forest]",{Potion, Rusty_sword, Leather_armour}, 3, {cemetery, forest}, 2, {Orc}, 1},
{"forest", " The plain eventually dissipates into a dense forest,\n with high tree tops and dense foliage one would be careful to traverse here",{Potion}, 1, {field}, 1, {}, 0}};

const char vowels[5] = {'a', 'e', 'i', 'o', 'u'};

#define n_locations (sizeof locations / sizeof *locations)


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

void command_look(const char * subject, Location *location){
    if(subject != NULL && strcmp(subject, "\n") != 0 && strcmp(subject, "around") == 0){
        printf("\n%s\n",location->description);
        if(location->n_actors > 0){
            printf("\n You can see:\n");
            show_loc_npcs(location);
        }
        if(location->n_entities > 0){
            printf("\n You also see a few items\n");
            show_loc_entities(location);
        }
    }
    else if(subject != NULL && strcmp(subject, "\n") != 0){
        NPC *to_look = npc_from_subject(subject);
        if(to_look != NULL && is_npc_inloc(to_look, location->actors, location->n_actors))
            look_NPC(to_look);
        else
            printf("\n Who do you wan't to look at exactly?\n");
    }
    else{
        printf("\n I'm not sure where you want me to look\n");
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


