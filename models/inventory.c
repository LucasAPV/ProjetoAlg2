#include "inventory.h"
#include "../database/inventory_table.h"
#include <stdbool.h>

int inventory_insert(Inventory *a) {
   Table *t = inventory_table();
   if (t->count >= t->capacity) return -1;   // não gasta id se estiver cheia
   a->id = inventory_table_next_id();
   return table_insert(t, a);
}

bool inventory_update(int idx, const Inventory *a) {
   return table_update(inventory_table(), idx, a);
}

bool inventory_delete(int idx) {
   return table_delete(inventory_table(), idx);
}

Inventory *inventory_get(int idx) {
   return table_get(inventory_table(), idx);
}

static bool match_id(const void *row, const void *ctx) {
   return ((const Inventory *)row)->id == *(const int *)ctx;
}

int inventory_find_by_id(int id) {
   return table_find(inventory_table(), match_id, &id);
}

Item find_item_by_id(Inventory i, int id) {
   if(id >= CAPACITY || id < 0 || id > i.last_free_space) return (Item) {};
   return i.items[id];
}

bool add_item (Inventory *i, Item item) {
   if (item.space_ocuppied < 1 || item.space_ocuppied > 50) {
      return false;
   }

   unsigned int espaco_total = 0;
   for (int j = 0; j < i->last_free_space; j++) {
      espaco_total += i->items[j].space_ocuppied;
   }

   if (espaco_total + item.space_ocuppied > 50) {
      return false;
   }

   if(i->last_free_space >= CAPACITY) return false;

   i->items[i->last_free_space] = item;
   i->last_free_space++;
   return true;
}

/*
Item* items (Inventory i) {
   return (Item*) i.items;
}
*/
