#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#include "entity.h"


int MAX_LOC_ENTITIES = 20;

Entity entities[] ={{"your fists", "Can still knock a few teeth out", "Weapon", 1, 0},
{"loin cloth", "Torn piece of cloth to keep the game PG13", "Weapon", 0, 6},
{"rusty sword", "Has seen better days but can still help in a pinch", "Weapon", 4, 0},
{"coin", "Nice golden coin, can be used to buy things", "Money", 0, 0},
{"potion", "Red and glowy, must be good for health", "Consumable", 10, 0},
{"leather armour", "Light and will protect you from most cuts and bruises", "Armour", 0, 10},
{"club", "Crude woodden club good for blunt attacks", "Weapon", 3, 0},
{"gigachad sword", "Instant kills anything", "Weapon", 100, 0}};

#define n_entities (sizeof entities / sizeof *entities)

int rand_to(int n)
{
  assert(n > 0);
  long long int m = RAND_MAX + 1L;
  long long int w = m / n;
  long long int limit = n * w;
  long long r;
  do
    r = rand();  
  while (r >= limit); 
  return (int)(r / w);
}

void command_inspect(const char* subject){
    if(subject != NULL && strcmp(subject, "\n") != 0){
        // printf("%s\n", subject);
        for(int i = 0; i < n_entities;i++)
            if(strcmp(subject, entities[i].name) == 0)
                printf("%s\n",entities[i].description);
    }
    else
        printf("\n I can't inspect that\n");
}

int index_of_entity(const char* subject){
    for(int i = 0; i < n_entities;i++)
        if(strcmp(subject,entities[i].name) == 0)
            return i;
    return -1;
}

int remove_entities(Entity **a, int n, Entity *x){
    int index_to_remove = -1;
    for(int i = 0; i < n; i++){
        if(a[i] == x)
            index_to_remove = i;
    }
    if(index_to_remove != -1){
        for(int i = index_to_remove; i < n-1;i++){
           a[i] = a[i+1];
        }
        n--;
    }
    return n;
}

void entity_exchange_point(Entity **a, int x, int y)
{
  Entity* m = a[x];
  a[x] = a[y];
  a[y] = m;
}

void entity_isort_point(Entity **a, int n)
{
  for (int i = 1; i < n; i++)
  {
    int j = i;
    while (j > 0 && strcmp(a[j-1]->name, a[j]->name) > 0)
    {
      entity_exchange_point(a, j-1, j);
      j--;
    }
  }
}

// void add_quantity(Entity **a, int n, Entity *x,int y){
//     for(int i = 0; i < n; i++)
//         if(a[i] == x)
//             a[i]->quantity += y;
// }

int entity_int_cmp(Entity x, Entity y){
    int result = strcmp(x.name, y.name);
    return result;
}

int string_int_cmp_ref(Entity *x, Entity *y){
    return entity_int_cmp(*x, *y);
}

int entity_int_cmp2(const void *x, const void *y)
{
  return string_int_cmp_ref((Entity *)x, (Entity *)y);
}

int Entity_count_while(Entity **a, int n, Entity *x){
    int result = 0;
    while (result < n && a[result] == x)
        result++;
    return result;
}


int print_unique_items(Entity **a,int n){
    printf("\n");
    int size = n;
    entity_isort_point(a, n);
    int i = 0;
    while (i < n)
    {
        int z = Entity_count_while(a+i, n-i, a[i]);
        if(z > 1)
            printf(" %d %ss\n", z, a[i]->name);
        else
            printf(" %s\n",a[i]->name);
        i += z;
    }
    return size;
}



