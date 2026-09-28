#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdbool.h>
#include "item.h"
#define CAPACITY 50

typedef struct Inventory {
   int id;
   Item items[CAPACITY];
} Inventory;

int        inventory_insert    (Inventory *i);
bool       inventory_update    (int idx, const Inventory *a);
bool       inventory_delete    (int idx);
Inventory *inventory_get       (int idx);
int        inventory_find_by_id(int id);

#endif