// Text based rpg
// npc.h

#ifndef npc_h
#define npc_h

#include "entity.h"

typedef struct{
    const char *title;
    const char *description;
    void (*quest_start)();
    int (*completion_condition)();
    void (*rewards)();
}Quest;

typedef struct{
    const char *name;
    const char *description;
    int max_hp;
    int hp;
    Entity *e_weapon;
    Entity *e_armour;
    Entity *inventory[20];
    int inventoy_size;
    Entity *purse[100];
    int purse_size;
    const char *voice_lines[10];
    int n_voice_lines;
    int times_talked;
    const char *death_lines[10];
    int n_death_lines;
    Quest *quest;
}NPC;

#include "location.h"
//#include "player.h"

//  NPC npcs[];
//  NPC *npc_from_subject(const char*subject);
int is_npc_inloc(NPC *x, NPC **a, int n);
void look_NPC(NPC *a);
void talk_to(NPC *a);
int find_npc(NPC **a, int n, NPC *x);
int remove_npc(NPC **a, int n, NPC *x);
void look_NPC_combat(NPC *a);
int find_quest(Quest **a, int n, Quest *x);
int remove_quests(Quest **a, int n, Quest*x);
NPC *npc_from_subject(const char*subject);
extern NPC npcs[];
#define Orc (npcs + 0)
#define Old_man (npcs + 1)
#define end_npc (npcs + 2)

extern Quest quests[];

#define Orc_kill (quests + 0)
#define end_quests (quests +1)


// #define Orc (npcs + 0)
// #define end_npc (npcs + 1)

#endif