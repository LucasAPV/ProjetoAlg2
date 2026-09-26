#include "inventory.h"
#include "inventory_table.h"

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