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


#endif