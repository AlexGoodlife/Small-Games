#ifndef commands_h
#define commands_h

#include "entity.h"
#include "npc.h"
#include "location.h"
#include "player.h"
#include "combat.h"
#include "quests.h"
#include "commands.h"

void command_look(const char * subject, Location *location);
void command_go(const char *subject, Player *player);
void command_talk(const char * subject, Player *player);
int command_fight(const char * subject, Player *player);
void check_questlog(Player *player);
void help_command(void);


#endif