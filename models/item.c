#include "item.h"
#include "item_table.h"

int item_insert(Item *a) {
   Table *t = item_table();
   if (t->count >= t->capacity) return -1;   // não gasta id se estiver cheia
   a->id = item_table_next_id();
   return table_insert(t, a);
}

bool item_update(int idx, const Item *a) {
   return table_update(item_table(), idx, a);
}

bool item_delete(int idx) {
   return table_delete(item_table(), idx);
}

Item *item_get(int idx) {
   return table_get(item_table(), idx);
}

static bool match_id(const void *row, const void *ctx) {
   return ((const Item *)row)->id == *(const int *)ctx;
}

int item_find_by_id(int id) {
   return table_find(item_table(), match_id, &id);
}