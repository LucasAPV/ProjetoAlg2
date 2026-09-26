#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdbool.h>

#define CAPACITY 50

typedef struct Inventory {
   int id;
   Item items[CAPACITY];
} Inventory;

int        Inventory_insert    (Inventory *i);
bool       Inventory_update    (int idx, const Inventory *a);
bool       Inventory_delete    (int idx);
Inventory *Inventory_get       (int idx);
int        Inventory_find_by_id(int id);

#endif