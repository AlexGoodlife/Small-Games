// Text based rpg
// entity.h

#ifndef entity_h
#define entity_h

typedef struct{
    const char *name;
    const char *description;
    const char *type;
    int dmg;
    int arm_class;
}Entity;


extern int MAX_LOC_ENTITIES;
extern void command_inspect(const char * subject);
extern int remove_entities(Entity **a, int n, Entity *x);
extern int index_of_entity(const char* subject);
extern int print_unique_items(Entity **a,int n);
extern Entity entities[];
extern int rand_to(int n);

#define Fists (entities + 0)
#define Loin_cloth (entities + 1)
#define Rusty_sword (entities + 2)
#define Coin (entities + 3)
#define Potion (entities + 4)
#define Leather_armour (entities + 5)
#define Club (entities + 6)
#define Giga_sword (entities + 7)
#define end_of_entities (entities + 8)



#endif