// Text based rpg
// player.h

#ifndef player_h
#define player_h


typedef struct loc{
    const char *name;
    const char *description;
    Entity *l_entities[50];
    int n_entities;
    struct loc *destinations[5];
    int n_destinations;
    NPC *actors[10];
    int n_actors;
}Location;

typedef struct{
    int max_hp;
    int hp;
    Entity *e_weapon;
    Entity *e_armour;
    Location *location;
    Entity *inventory[20];
    int inventoy_size;
    Entity *purse[100];
    int purse_size;
    Quest *questlog[100];
    int n_quests;
}Player;


extern Player* initialize_player(int max_hp,int hp, Entity *e_weapon, Entity *e_armour,Location *location);
extern void true_inspect(const char* subject, Player *player);
extern void command_get(const char *subject, Player *player);
extern void show_inventory(Player *player);
extern void show_equipment(Player *player);
extern void equip_item(const char * subject, Player *player);
extern void drop_item(const char *subject, Player *player);
extern void command_use(const char*subject, Player *player);
extern void show_purse(Player *player);
extern void show_status(Player *player);
extern void give_money(Player *player, NPC *giver);
extern void add_loot_to_location(Location *location, Entity **a, int n);
extern void check_npc_quest(Quest **a, int n, NPC *x, Player *player);
extern NPC *npc_from_subject(const char*subject);
extern NPC npcs[];
extern Quest quests[];
#define Orc (npcs + 0)
#define Old_man (npcs + 1)
#define end_npc (npcs + 2)

#define Orc_kill (quests + 0)
#define end_quests (quests +1)


#endif