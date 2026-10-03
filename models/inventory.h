#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdbool.h>
#include "item.h"
#define CAPACITY 50

typedef struct Inventory {
   int id;
   Item items[CAPACITY];
   int actual_capacity;
   int last_free_space;
} Inventory;

int        inventory_insert    (Inventory *i);
bool       inventory_update    (int idx, const Inventory *a);
bool       inventory_delete    (int idx);
Inventory *inventory_get       (int idx);
int        inventory_find_by_id(int id);
Item       find_item_by_id     (Inventory i, int id);
bool       add_item            (Inventory *i, Item item);
/*
Item* items(Inventory i);
*/
#endif
