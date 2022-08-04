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


Player* initialize_player(int max_hp,int hp, Entity *e_weapon, Entity *e_armour,Location *location);
void true_inspect(const char* subject, Player *player);
void command_get(const char *subject, Player *player);
void show_inventory(Player *player);
void show_equipment(Player *player);
void equip_item(const char * subject, Player *player);
void drop_item(const char *subject, Player *player);
void command_use(const char*subject, Player *player);
void show_purse(Player *player);
void show_status(Player *player);
void give_money(Player *player, NPC *giver);
void add_loot_to_location(Location *location, Entity **a, int n);
void check_npc_quest(Quest **a, int n, NPC *x, Player *player);



#endif