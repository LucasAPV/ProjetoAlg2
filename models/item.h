#ifndef ITEM_H
#define ITEM_H

#include <stdbool.h>

#define MAX_LENGTH 50
#define MAX_ITEMS 50

typedef enum Type {
   HELMET,
   CHESTPLATE,
   GLOVES,
   LEGGINGS,
   GREAVES,
   RING,
   NECKLACE,
   BELT,
   ONE_HAND_SWORD,
   TWO_HAND_SWORD // isso deve ocupar tanto a left e right hand
} Type;

typedef struct Item {
   unsigned int id;
   char name[MAX_LENGTH];
   Type type;
   unsigned int space_ocuppied;
   int attack_bonus;
   int defence_bonus;
   int life_bonus;
   int initiative_bunus;
   unsigned int power;
} Item;

int        item_insert    (Item *i);
bool       item_update    (int idx, const Item *a);
bool       item_delete    (int idx);
Item      *item_get       (int idx);
int        item_find_by_id(int id);

#endif