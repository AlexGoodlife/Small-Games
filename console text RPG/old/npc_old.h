// Text based rpg
// npc.h

#ifndef npc_h
#define npc_h

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

// extern NPC npcs[];
// extern NPC *npc_from_subject(const char*subject);
extern int is_npc_inloc(NPC *x, NPC **a, int n);
extern void look_NPC(NPC *a);
extern void talk_to(NPC *a);
extern int find_npc(NPC **a, int n, NPC *x);
extern int remove_npc(NPC **a, int n, NPC *x);
extern void look_NPC_combat(NPC *a);
extern int find_quest(Quest **a, int n, Quest *x);
extern int remove_quests(Quest **a, int n, Quest*x);

// #define Orc (npcs + 0)
// #define end_npc (npcs + 1)

#endif