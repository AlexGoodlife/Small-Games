// Text based rpg
// location.h

#ifndef location_h
#define location_h

#include "entity.h"
#include "npc.h"

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



void tutorial_event(void);
Location *location_from_subject(const char *subject);
int is_destinations(Location *current, Location *destination);
extern Location locations[];


#define cemetery (locations + 0)
#define field (locations + 1)
#define forest (locations + 2)
#define end_of_locations  (locations + 3)





#endif