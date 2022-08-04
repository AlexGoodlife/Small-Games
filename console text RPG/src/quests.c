#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>


#include  "../include/quests.h"



// First quest start
int orc_kill_complete(){
    // printf("%d\n", is_in_inventory_literal(Club, player));
    return Orc->hp<= 0;
}

void orc_kill_quest_start(){
    printf("\n [old man] : Hey I would leave here but that orc over in the [field] is really causing me trouble can you deal with him? You gotta show me his club too\n");
    printf("\n QUEST ISSUED: \n Kill the [orc] in the [field] and come back \n");
}

void orc_kill_reward(){
    printf("\n [old man] : Thanks for getting rid of the orc, but I'm actually quite confortable here \n");
}

// First quest end

Quest quests[] = {{"Big green baddie", "Kill the orc in the field", &orc_kill_quest_start, &orc_kill_complete, &orc_kill_reward}};

#define n_questss (sizeof quests / sizeof *quests)

