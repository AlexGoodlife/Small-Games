#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entity.h"
#include "npc.h"
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

int is_in_inventory(const char*subject, Player *player){
    for(int i = 0; i < player->inventoy_size; i++){
        if(strcmp(subject, player->inventory[i]->name) == 0)
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
        printf("Picked up [%s]\n", add->name);
        player->inventory[player->inventoy_size++] = add;
        remove_from_location(add, player->location);
    }
    else if(player->inventoy_size >= 20)
        printf("Your inventory is full, drop some stuff maybe\n");
    else
        printf(" Weird error occured tf\n");
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
        printf("Your purse is full, spend some money!\n");
    else
        printf(" Weird error occured tf\n");

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
        printf("Can't see the item to get\n");
}

void true_inspect(const char* subject, Player *player){
    if(subject != NULL && (is_visible(subject, player) || is_in_inventory(subject, player) || is_in_purse(subject, player)))
        command_inspect(subject);
    else
        printf("I can't see that here");
}

void show_inventory(Player *player){
    int space_left = (MAX_INVENTORY_SIZE - player->inventoy_size);
    if(space_left == MAX_INVENTORY_SIZE){
        printf("You have nothing to your name \n");
    }
    else if(space_left > 0)
        printf("Backpack, it can still hold %d coins:\n", space_left);
    else
        printf("Full backpack, contains:");
    print_unique_items(player->inventory, player->inventoy_size);
        
}

void show_purse(Player *player){
    int space_left = (MAX_PURSE_SIZE - player->purse_size);
    if(space_left == MAX_PURSE_SIZE){
        printf("You have no money, a poor person indeed\n");
    }
    else if(space_left > 0)
        printf("Your purse, it can still hold %d items:\n", space_left);
    else
        printf("Your purse is full, spend some money:");
    print_unique_items(player->purse, player->purse_size);
}

void show_equipment(Player *player){
    printf("Weapon -> %s: %s\n", player->e_weapon->name, player->e_weapon->description);
    printf("It does %d damage\n", player->e_weapon->dmg);
    printf("\n");
    printf("Armour -> %s: %s\n", player->e_armour->name, player->e_armour->description);
    printf("It has %d armour class\n", player->e_armour->arm_class);
}

void equip_item(const char * subject, Player *player){
    int i = find_in_inventory(subject, player);
    if(i != -1 && strcmp(player->inventory[i]->type, "Weapon") == 0){
        printf("Equipped [%s]\n", player->inventory[i]->name);
        player->e_weapon = player->inventory[i];
    }
    else if(i != -1 && strcmp(player->inventory[i]->type, "Armour") == 0){
        printf("Equipped [%s]\n", player->inventory[i]->name);
        player->e_armour = player->inventory[i];
    }
    else if( i != -1)
        printf("Can't equip things of type %s\n", player->inventory[i]->type);
    else
        printf("That item is not in my inventory\n");
}


void drop_item(const char *subject, Player *player){
    if(is_in_inventory(subject, player)){
        // int find = find_in_inventory(subject, player);
        // Entity *bruh = &entities[find];
        remove_from_inventory(subject, player);
        add_to_location(subject, player->location);
        printf("Dropped %s from backpack\n", subject);
    }
    else if(is_in_purse(subject, player)){
        remove_from_purse(subject, player);
        add_to_location(subject, player->location);
        printf("Dropped %s from backpack\n", subject);
    }
    else
        printf("Can't drop something I don't have\n");
}

void handle_consumables(Entity *a, Player *player){
    if(strcmp(a->name, "Potion") == 0){
        if(player->hp < player->max_hp){
        printf("Used potion and healed %d hitpoints\n", a->dmg);
        player->hp = (((player->hp + a->dmg) < player->max_hp) ? (player->hp + a->dmg) : player->max_hp);
        printf("HP is now %d\n", player->hp);
        int size = remove_entities(player->inventory, player->inventoy_size, a);
        player->inventoy_size = size;
        }
        else
            printf("Health is already maxed\n");
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
            printf("That item isn't consumable\n");
    }
    else
        printf("Can't use something that I don't have on me\n");
}

void show_status(Player *player){
    printf("Current Health Status\n");
    printf("Max hp : [%d]\n", player->max_hp);
    printf("Current hp : [%d]\n", player->hp);

}
