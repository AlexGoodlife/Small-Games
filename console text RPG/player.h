// Text based rpg
// player.h

#ifndef player_h
#define player_h

#include "entity.h"
//#include "location.h"
#include "npc.h"

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



#endif