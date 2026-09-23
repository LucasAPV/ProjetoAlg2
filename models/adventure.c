#include "adventure.h"
#include "adventure_table.h"

int adventure_insert(Adventure *a) {
   Table *t = adventure_table();
   if (t->count >= t->capacity) return -1;   // não gasta id se estiver cheia
   a->id = adventure_table_next_id();
   return table_insert(t, a);
}

bool adventure_update(int idx, const Adventure *a) {
   return table_update(adventure_table(), idx, a);
}

bool adventure_delete(int idx) {
   return table_delete(adventure_table(), idx);
}

Adventure *adventure_get(int idx) {
   return table_get(adventure_table(), idx);
}

static bool match_id(const void *row, const void *ctx) {
   return ((const Adventure *)row)->id == *(const int *)ctx;
}

int adventure_find_by_id(int id) {
   return table_find(adventure_table(), match_id, &id);
}