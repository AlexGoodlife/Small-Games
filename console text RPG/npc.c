#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "npc.h"

NPC npcs[]= {{"orc", " A big green orc, doesn't seem too friendly", 20, 20, Club, Loin_cloth, {Potion, Club}, 2, {Coin, Coin, Coin, Coin}, 4, {"Oy get out of 'ere human", "I don't talk to no humies", "WAAAAGH"}, 3, 0, {"Puny human.... beat me", "WAAAGH WHAT SHAME *fucking dies*"}, 2,NULL},
{"old man", " A weird looking old man", 20, 20, Rusty_sword, Leather_armour, {Potion}, 1, {Coin, Coin, Coin, Coin}, 4, {"Hey, was the cemetery confy?", "Don't mind me just a friendly old man"}, 1, 0, {"Welp, guess this is the end"}, 1, Orc_kill}};
#define n_npcs (sizeof npcs / sizeof *npcs)


int find_npc(NPC **a, int n, NPC *x){
    for(int i = 0; i < n;i++)
        if(a[i] == x)
            return i;
    return -1;
}

int remove_npc(NPC **a, int n, NPC *x){
    int index = find_npc(a, n, x);
    if(index != -1){
        for(int i = index; i < n -1;i++){
            a[i] = a[i+1];
        }
        n--;
    }
    return n;
}

int is_npc_inloc(NPC *x, NPC **a, int n){
    if(x != NULL){
        for(int i = 0; i < n;i++){
            if(x == a[i])
                return 1;
        }
        return 0;
    }
    else{
        printf("\n That person does not exist\n");
        return 0;
    }
}

void look_NPC(NPC *a){
    printf("%s\n", a->description);
    printf("\n The %s is holding a [%s] and wearing [%s]\n", a->name, a->e_weapon->name, a->e_armour->name);
}

void look_NPC_combat(NPC *a){
    printf("%s\n", a->description);
    printf("\n The %s is holding a [%s] and wearing [%s]\n", a->name, a->e_weapon->name, a->e_armour->name);
    printf("\n Max hp is: %d\n Current is %d\n", a->max_hp, a->hp);
}

void talk_to(NPC *a){
    if(a->times_talked <= a->n_voice_lines){
        printf("\n [%s]: %s\n", a->name, a->voice_lines[a->times_talked]);
        a->times_talked++;
    }
    else{
        int random = rand_to(a->n_voice_lines);
        printf("\n [%s]: %s\n", a->name, a->voice_lines[random]);
    }
}

int find_quest(Quest **a, int n, Quest *x){
    for(int i = 0; i < n; i++)
        if(a[i] == x)
            return i;
    return -1;
}

int remove_quests(Quest **a, int n, Quest*x){
    int index_to_remove = -1;
    for(int i = 0; i < n; i++){
        if(a[i] == x)
            index_to_remove = i;
    }
    if(index_to_remove != -1){
        for(int i = index_to_remove; i < n-1;i++){
           a[i] = a[i+1];
        }
        n--;
    }
    return n;
}

NPC *npc_from_subject(const char*subject){
    for(int i=0; i < n_npcs;i++){
        if(strcmp(subject, npcs[i].name)==0)
            return &npcs[i];
    }
    return NULL;   
}

// First quest start
int orc_kill_complete(){
    // printf("%d\n", is_in_inventory_literal(Club, player));
    return Orc->hp<= 0;
}

void orc_kill_quest_start(){
    printf("\n [old man] : Hey I would leave here but that orc over in the [field] is really causing me trouble can you deal with him? You gotta show me his club too\n");
    printf("\n QUEST ISSUED: \n Kill the [orc] in the [field] and come back \n");
}

void orc_kill_reward(){
    printf("\n [old man] : Thanks for getting rid of the orc, but I'm actually quite confortable here \n");
}

// First quest end

Quest quests[] = {{"Big green baddie", "Kill the orc in the field", &orc_kill_quest_start, &orc_kill_complete, &orc_kill_reward}};

#define n_questss (sizeof quests / sizeof *quests)


