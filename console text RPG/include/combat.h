// Text based rpg
// combat.h

#ifndef combat_h
#define combat_h

#include "entity.h"
#include "npc.h"
#include "location.h"
#include "player.h"

int combat_start(Player *player, NPC *enemy);
void combat_end(Player *player, NPC *enemy);




#endif