#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entity.h"
#include "npc.h"

// NPC npcs[]= {{"orc", " A big green orc, doesn't seem too friendly", 20, 20, Club, Loin_cloth, {Potion}, 1, {Coin, Coin, Coin, Coin, Club}, 4, {"Oy get out of 'ere human", "I don't talk to no humies", "WAAAAGH"}, 3, 0, {"Puny human.... beat me", "WAAAGH WHAT SHAME *fucking dies*"}, 2}};

// #define n_npcs (sizeof npcs / sizeof *npcs)


// NPC *npc_from_subject(const char*subject){
//     for(int i=0; i < n_npcs;i++){
//         if(strcmp(subject, npcs[i].name)==0)
//             return &npcs[i];
//     }
//     return NULL;   
// }

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


