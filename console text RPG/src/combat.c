#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "../include/combat.h"

static char combat_input[100] = " ";

const char *your_misses[] = {"A narrow miss!", "Your weapon scrapes the enemy's armour", "You swing and miss completely", "Your blow was completely deflected", "Despite putting all your might into it, the enemy dodges"};

#define n_your_misses (sizeof your_misses / sizeof *your_misses)

const char *your_hits[] = {"A devastating blow", "You hit right at center mass", "Your weapon damages the opponent", "A Huge blow to the head", "A Crushing blow to the body"};

#define n_your_hits (sizeof your_hits / sizeof *your_hits)

const char *enemy_misses[] = {"Close call! The blow missed", "You armour saves you yet again", "You dodge skillfully", "With some luck, you scrape by the blow", "Your mighty armour is too strong for blows like those", "The blow was masterfully blocked"};

#define n_enemy_misses (sizeof enemy_misses / sizeof *enemy_misses)

const char *enemy_hits[] = {"You suffer a great blow!", "The attack goes through your guard", "Your armour couldn't protect you", "Thats gotta hurt", "You face the blow head on"};

#define n_enemy_hits (sizeof enemy_hits / sizeof *enemy_hits)

void print_random_statement(const char **a, int n){
    int random = rand_to(n);
    printf("\n %s\n --------------------------------------------------- \n", a[random]);
}

void command_attack(Player *player, NPC *enemy){
    int roll = rand_to(21);
    if(roll > enemy->e_armour->arm_class){
        enemy->hp -= player->e_weapon->dmg;
        print_random_statement(your_hits, n_your_hits);
        printf(" You did: %d damage! [%s] has: %d hitpoints left\n --------------------------------------------------- \n", player->e_weapon->dmg, enemy->name, enemy->hp);

    }
    else
        print_random_statement(your_misses, n_your_misses);
}

void command_defend(Player* player){
    int roll = rand_to(21);
    if(roll > 7 && player->e_armour->arm_class <= 15){
        printf("\n You brace and defend for the enemy's attack, your armour class rises!\n --------------------------------------------------- \n");
        player->e_armour->arm_class++;
    }
    else
        printf("\n The situation is dire, you attempted to brace but the enemy is too ferocious\n --------------------------------------------------- \n");
}

void command_maneuver(Player *player){
    int roll = rand_to(21);
    if(roll > 12 && player->e_weapon->dmg <= 15){
        printf("\n You manage to maneuver into an advantageous position! Your attack rises!\n --------------------------------------------------- \n");
        player->e_weapon->dmg++;
    }
    else
        printf("\n You attempted to maneuver into a better position but to no avail, you must hold your ground\n --------------------------------------------------- \n");
}

int command_run(void){
    int roll = rand_to(21);
    return roll < 12 ? 1 : 2;
}

void command_look_combat(const char *subject, NPC *enemy, Player *player){
    if(subject != NULL && strcmp(subject, "\n") != 0){
        NPC *to_look = npc_from_subject(subject);
        if(to_look != NULL && strcmp(to_look->name, subject) == 0)
            look_NPC_combat(enemy);
        else
            printf("\n Who do you wan't to look at exactly?, We are kinda fighting here\n --------------------------------------------------- \n");
    }
    else{
        printf("\n I'm not sure where you want me to look\n --------------------------------------------------- \n");
    }
}

void enemy_attack(Player *player, NPC *enemy){
    int roll = rand_to(21);
    if(roll > player->e_armour->arm_class){
        player->hp -= enemy->e_weapon->dmg;
        print_random_statement(enemy_hits, n_enemy_hits);
        printf(" [%s] did: %d damage! You have %d hitpoints left\n", enemy->name, enemy->e_weapon->dmg, player->hp);

    }
    else
        print_random_statement(enemy_misses, n_enemy_misses);
}

void enemy_defend(NPC *enemy){
    int roll = rand_to(21);
    if(roll > 7 && enemy->e_armour->arm_class <= 15){
        printf("\n Your opponent braces for your mighty attacks, break through its guard!\n --------------------------------------------------- \n");
        enemy->e_armour->arm_class++;
    }
    else
        printf("\n A foolish attempt to brace, strike now!\n --------------------------------------------------- \n");
}

void enemy_maneuver(NPC *enemy){
    int roll = rand_to(21);
    if(roll > 12 && enemy->e_weapon->dmg <= 15){
        printf("\n You let yourself be outmaneuvered, the enemy attack rises!\n --------------------------------------------------- \n");
        enemy->e_weapon->dmg++;
    }
    else
        printf("\n The enemy attempted to maneuver but your footwork is too fast\n --------------------------------------------------- \n");
}

int player_is_alive(Player *player){
    return player->hp > 0;
}

int enemy_is_alive(NPC *enemy){
    return enemy->hp > 0;
}

int combat_status(Player *player, NPC *enemy){
    return player_is_alive(player) && enemy_is_alive(enemy) ? 1 : player_is_alive(player) && !enemy_is_alive(enemy) ? 3 : 0;
}

int get_combat_Input(void){
    printf("\n-->>");
    return fgets(combat_input, sizeof combat_input, stdin) != NULL;
}

void enemy_turn(Player *player,NPC *enemy){
    printf("\n [%s]'s turn!\n --------------------------------------------------- \n", enemy->name);
    int roll = rand_to(21);
    if(roll > 10)
        enemy_attack(player, enemy);
    else if(roll > 5 && roll < 10)
        enemy_defend(enemy);
    else
        enemy_maneuver(enemy);
    printf("\n Your turn!\n --------------------------------------------------- \n");
}


int combat_loop(char*input, Player *player, NPC *enemy){
    if(input == NULL || strcmp(input, "\n") == 0 || strcmp(input, " ") == 0){
        printf("\n Type a command please\n");
        return 3;
    }
    const char * command = strtok(input, " \n");
    const char * subject = strtok(NULL, "\n");
    if(strcmp(command, "look") == 0){
        command_look_combat(subject, enemy, player);
        return 3;
    }
    else if(strcmp(command, "go") == 0){
        printf("\n You can't really go anywhere right now, maybe you want to [run]?\n");
        return 3;
    }
    else if(strcmp(command, "inspect") == 0){
        // printf("%s\n", subject);
        true_inspect(subject, player);
        return 3;
    }
    else if(strcmp(command, "get") == 0){
        printf("\n Now is not the time to be picking up stuff\n");
        return 3;
    }
    else if(strcmp(command, "backpack") == 0){
        // printf("%s\n", subject);
        show_inventory(player);
        return 3;
    }
    else if(strcmp(command, "purse") == 0){
        // printf("%s\n", subject);
        show_purse(player);
        return 3;
    }
    else if(strcmp(command, "equipment") == 0){
        // printf("%s\n", subject);
        show_equipment(player);
        return 3;
    }
    else if(strcmp(command, "equip") == 0){
        equip_item(subject, player);
        return 3;
    }
    else if(strcmp(command, "drop") == 0){
        // printf("%s\n", subject);
        drop_item(subject, player);
        return 3;
    }
    else if(strcmp(command, "use") == 0){
        // printf("%s\n", subject);
        command_use(subject, player);
        return 3;
    }
    else if(strcmp(command, "status") == 0){
        // printf("%s\n", subject);
        show_status(player);
        return 3;
    }
    else if(strcmp(command, "talkto") == 0){
        printf("\n We've gone past the point of talking");
        return 3;
    }
    else if(strcmp(command, "attack") == 0){
        command_attack(player, enemy);
        return 1;
    }
    else if(strcmp(command, "defend") == 0){
        command_defend(player);
        return 1;
    }
    else if(strcmp(command, "maneuver") == 0){
        command_maneuver(player);
        return 1;
    }
    else if(strcmp(command, "run") == 0){
        printf("\n You try to run\n");
        return command_run();
    }
    else if(strcmp(command, "quit") == 0){
        return 0;
    }
    else{
        printf(" Do not know how to do that\n");
        return 3;
    }
}

int combat_first(char *input, Player *player, NPC *enemy){
    int combat = combat_loop(input, player, enemy);
    while(combat == 3){
        get_combat_Input();
        combat = combat_loop(input, player, enemy);
    }
    if(combat == 0)
        return 0;
    if(combat_status(player, enemy) == 3)
        return combat_status(player, enemy);
    enemy_turn(player, enemy);
    return combat == 2 ? 2 : combat_status(player, enemy);

}

int combat_second(char *input, Player *player, NPC *enemy){
    enemy_turn(player, enemy);
    int combat = combat_loop(input, player, enemy);
    while(combat == 3){
        get_combat_Input();
        combat = combat_loop(input, player, enemy);
    }
    if(combat == 0)
        return 0;
    if(combat_status(player, enemy) == 3)
        return combat_status(player, enemy);
    return combat == 2 ? 2 : combat_status(player, enemy);
}

int combat_handler_first(Player *player, NPC * enemy){
    int save_dmg_player = player->e_weapon->dmg;
    int save_ac_player = player->e_armour->arm_class;
    int save_dmg_en = enemy->e_weapon->dmg;
    int save_ac_en = enemy->e_armour->arm_class;
    printf("\n COMBAT START! You are fighting [%s], and you go first!\n", enemy->name);
    int combat;
    do 
        combat = combat_first(combat_input, player, enemy);
    while(combat != 0 && combat != 2  && combat != 3 && get_combat_Input());
   if(player->hp <= 0){
       printf("\n You died to [%s]\n GAME OVER", enemy->name);
        combat = 0;
    }
    player->e_weapon->dmg = save_dmg_player;
    player->e_armour->arm_class = save_ac_player;
    enemy->e_weapon->dmg = save_dmg_en;
    enemy->e_armour->arm_class = save_ac_en;
    return combat;
}

int combat_handler_second(Player *player, NPC *enemy){
    int save_dmg_player = player->e_weapon->dmg;
    int save_ac_player = player->e_armour->arm_class;
    int save_dmg_en = enemy->e_weapon->dmg;
    int save_ac_en = enemy->e_armour->arm_class;
    printf("\n COMBAT START! You are fighting [%s], and you go second!\n", enemy->name);
    int combat;
    do 
        combat = combat_second(combat_input, player, enemy);
    while(combat != 0 && combat != 2 && combat != 3 && get_combat_Input());
   if(player->hp <= 0){
        printf("\n You died to [%s]\n GAME OVER", enemy->name);
        combat = 0;
   }
   player->e_weapon->dmg = save_dmg_player;
   player->e_armour->arm_class = save_ac_player;
   enemy->e_weapon->dmg = save_dmg_en;
   enemy->e_armour->arm_class = save_ac_en;
    return combat;
}

int combat_start(Player *player, NPC *enemy){
    int roll_player = rand_to(21);
    int roll_enemy = rand_to(21);
    if( roll_player >= roll_enemy)
        return combat_handler_first(player, enemy);
    else
        return combat_handler_second(player, enemy);
}

void combat_end(Player *player, NPC *enemy){
    printf("\n You've defeated [%s]! Its loot scatters the floors and its money into your purse \n", enemy->name);
    int death_line = rand_to(enemy->n_death_lines);
    printf("\n [%s]: %s\n", enemy->name,enemy->death_lines[death_line]);
    give_money(player, enemy);
    add_loot_to_location(player->location, enemy->inventory, enemy->inventoy_size);
}





