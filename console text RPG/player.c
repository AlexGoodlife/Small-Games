#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#include "player.h"

int MAX_INVENTORY_SIZE = 20;
int MAX_PURSE_SIZE = 100;


Player *initialize_player(int max_hp,int hp, Entity *e_weapon, Entity *e_armour, Location *location){
    Player x = {max_hp, hp, e_weapon, e_armour,location};
    Player *result = (Player *) malloc(sizeof(Player));
    *result = x;
    return result;
}

int is_visible(const char*subject, Player *player){
    for(int i = 0; i < player->location->n_entities; i++){
        if(strcmp(subject, player->location->l_entities[i]->name) == 0)
            return 1;
    }
    return 0;
}

int item_index_location(Entity *subject, Location *location){
    for(int i = 0; i < location->n_entities; i++){
        if(strcmp(subject->name, location->l_entities[i]->name) == 0)
            return i;
    }
    return -1;
}

void remove_from_location(Entity *subject, Location *location){
    int index_to_remove = -1;
    for(int i = 0; i < location->n_entities; i++){
        if(strcmp(subject->name, location->l_entities[i]->name) == 0)
            index_to_remove = i;
    }
    if(index_to_remove != -1){
        for(int i = index_to_remove; i < location->n_entities -1;i++){
            location->l_entities[i] = location->l_entities[i+1];
        }
        location->n_entities--;
    }

}

void add_to_location(const char *subject, Location *location){
    int index = index_of_entity(subject);
    location->l_entities[location->n_entities++] = &entities[index];
}

void add_item_to_location(Location *location, Entity *x){
    location->l_entities[location->n_entities++] = x;
}

void add_loot_to_location(Location *location, Entity **a, int n){
    for(int i = 0; i< n; i++){
        location->l_entities[location->n_entities++] = a[i];
    }
}

int is_in_inventory(const char*subject, Player *player){
    for(int i = 0; i < player->inventoy_size; i++){
        if(strcmp(subject, player->inventory[i]->name) == 0)
            return 1;
    }
    return 0;
}

int is_in_inventory_literal(Entity *x, Player *player){
    // printf("%s\n", x->name);
    // printf("%s\n", player->name);
    for(int i = 0; i < player->inventoy_size; i++){
        if(player->inventory[i] == x)
            return 1;
    }
    return 0;
}

int find_in_inventory(const char*subject, Player *player){
    for(int i = 0; i < player->inventoy_size; i++){
        if(strcmp(subject, player->inventory[i]->name) == 0)
            return i;
    }
    return -1;
}

int find_in_purse(const char*subject, Player *player){
    for(int i = 0; i < player->purse_size; i++){
        if(strcmp(subject, player->purse[i]->name) == 0)
            return i;
    }
    return -1;
}

void remove_from_inventory(const char*subject, Player *player){
    int find = find_in_inventory(subject, player);
    player->inventoy_size = remove_entities(player->inventory, player->inventoy_size, player->inventory[find]);  
}

void remove_from_purse(const char*subject, Player *player){
    int find = find_in_inventory(subject, player);
    player->purse_size = remove_entities(player->purse, player->purse_size, player->purse[find]);  
}

void put_in_inventory(const char*subject, Player *player){
    if(player->inventoy_size < 20){
        int index = index_of_entity(subject);
        Entity *add = &entities[index];
        printf(" Picked up [%s]\n", add->name);
        player->inventory[player->inventoy_size++] = add;
        remove_from_location(add, player->location);
    }
    else if(player->inventoy_size >= 20)
        printf("\n Your inventory is full, drop some stuff maybe\n");
    else
        printf("\n Weird error occured tf\n");
}

void put_in_purse(const char *subject, Player *player){
    if(player->purse_size < 100){
        int index = index_of_entity(subject);
        Entity *add = &entities[index];
        printf("Picked up a [%s]\n", add->name);
        player->purse[player->purse_size++] = add;
        remove_from_location(add, player->location);
    }
    else if(player->purse_size >= MAX_PURSE_SIZE)
        printf("\n Your purse is full, spend some money!\n");
    else
        printf("\n Weird error occured tf\n");

}

int is_in_purse(const char*subject, Player *player){
    return (strcmp(subject, "Coin") == 0) && player->purse_size > 0;
}

void command_get(const char *subject, Player *player){
    if(is_visible(subject, player) && strcmp(subject, "Coin") != 0)
        put_in_inventory(subject, player);
    else if(strcmp(subject, "Coin") == 0)
        put_in_purse(subject, player);
    else
        printf("\n Can't see the item to get\n");
}

void true_inspect(const char* subject, Player *player){
    if(subject != NULL && (is_visible(subject, player) || is_in_inventory(subject, player) || is_in_purse(subject, player)))
        command_inspect(subject);
    else
        printf("\n I can't see that here");
}

void show_inventory(Player *player){
    int space_left = (MAX_INVENTORY_SIZE - player->inventoy_size);
    if(space_left == MAX_INVENTORY_SIZE){
        printf("You have nothing to your name \n");
    }
    else if(space_left > 0)
        printf("\n Backpack, it can still hold %d items:\n", space_left);
    else
        printf("\n Full backpack, contains:");
    print_unique_items(player->inventory, player->inventoy_size);
        
}

void show_purse(Player *player){
    int space_left = (MAX_PURSE_SIZE - player->purse_size);
    if(space_left == MAX_PURSE_SIZE){
        printf("\n You have no money, a poor person indeed\n");
    }
    else if(space_left > 0)
        printf("\n Your purse, it can still hold %d coins:\n", space_left);
    else
        printf("\n Your purse is full, spend some money:");
    printf("\n You have %d coins \n", player->purse_size);
}

void show_equipment(Player *player){
    printf("\n Weapon -> %s: %s\n", player->e_weapon->name, player->e_weapon->description);
    printf(" It does %d damage\n", player->e_weapon->dmg);
    printf("\n");
    printf(" Armour -> %s: %s\n", player->e_armour->name, player->e_armour->description);
    printf(" It has %d armour class\n", player->e_armour->arm_class);
}

void equip_item(const char * subject, Player *player){
    int i = find_in_inventory(subject, player);
    if(i != -1 && strcmp(player->inventory[i]->type, "Weapon") == 0){
        printf("\n Equipped [%s]\n", player->inventory[i]->name);
        player->e_weapon = player->inventory[i];
    }
    else if(i != -1 && strcmp(player->inventory[i]->type, "Armour") == 0){
        printf("\n Equipped [%s]\n", player->inventory[i]->name);
        player->e_armour = player->inventory[i];
    }
    else if( i != -1)
        printf("\n Can't equip things of type %s\n", player->inventory[i]->type);
    else
        printf("\n That item is not in my inventory\n");
}


void drop_item(const char *subject, Player *player){
    if(is_in_inventory(subject, player)){
        // int find = find_in_inventory(subject, player);
        // Entity *bruh = &entities[find];
        remove_from_inventory(subject, player);
        add_to_location(subject, player->location);
        printf("\n Dropped %s from backpack\n", subject);
    }
    else if(is_in_purse(subject, player)){
        remove_from_purse(subject, player);
        add_to_location(subject, player->location);
        printf("\n Dropped %s from backpack\n", subject);
    }
    else
        printf("\n Can't drop something I don't have\n");
}

void handle_consumables(Entity *a, Player *player){
    if(strcmp(a->name, "potion") == 0){
        if(player->hp < player->max_hp){
        printf("\n Used potion and healed %d hitpoints\n", a->dmg);
        player->hp = (((player->hp + a->dmg) < player->max_hp) ? (player->hp + a->dmg) : player->max_hp);
        printf(" HP is now %d\n", player->hp);
        int size = remove_entities(player->inventory, player->inventoy_size, a);
        player->inventoy_size = size;
        }
        else
            printf("\n Health is already maxed\n");
    }
    // TODO other consumables
}

void command_use(const char*subject, Player *player){
    if(is_in_inventory(subject, player)){
        int i = find_in_inventory(subject, player);
        Entity *use = player->inventory[i];
        if(strcmp(use->type, "Consumable") == 0)
            handle_consumables(use, player);
        else
            printf("\n That item isn't consumable\n");
    }
    else
        printf("\n Can't use something that I don't have on me\n");
}

void show_status(Player *player){
    printf("\n Current Health Status\n");
    printf(" Max hp : [%d]\n", player->max_hp);
    printf(" Current hp : [%d]\n", player->hp);
}

void transfer_money_until(Player *player, NPC *giver, int n){
    for(int i = 0; i < n; i++)
        player->purse[player->purse_size++] = giver->purse[giver->purse_size--];
}

void give_money(Player *player, NPC *giver){
    int space_left = MAX_PURSE_SIZE - player->purse_size;
    if(space_left >= giver->purse_size){
        printf("\n Transfered %d [coins] to your purse \n", giver->purse_size);
        transfer_money_until(player, giver, giver->purse_size);
    }
    else{
        printf("\n Seems your purse can't hold all these coins, the rest were dropped on the ground\n");
        transfer_money_until(player, giver, space_left);
        add_loot_to_location(player->location, giver->purse, giver->purse_size);
    }
}

void give_item(Player *player, Entity *x){
    int space_left = MAX_INVENTORY_SIZE - player->inventoy_size;
    if(space_left > 0){
        printf("\n You got [%s]! \n", x->name);
        player->inventory[player->inventoy_size++] = x;
    }
    else{
        printf("\n Your backpack is full, dropping items on the ground \n");
        add_item_to_location(player->location, x);
    }
}

void check_npc_quest(Quest **a, int n, NPC *x, Player *player){
    for(int i = 0; i < n; i++){
        if(a[i] == x->quest){
            if(a[i]->completion_condition()){
                printf("\n QUEST COMPLETE \n");
                a[i]->rewards();
                player->n_quests = remove_quests(player->questlog, player->n_quests, x->quest);
            }
        }
    }
}

