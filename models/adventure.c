#include "adventure.h"
#include "adventure_table.h"
#include "inventory.h"
#include "item.h"

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

bool is_item_in_inventory(Adventure a, Item i){
   for(int i = 0; i < CAPACITY; ++i){
      if(a.inv.item[i] == i) {
         return true
      }
   }
   return false;
}

bool is_item_in_active_slot(Adventure a, Item i); //TODO
void move_item_to_active(Adventure *a, Item i);   //TODO
void move_item_inventory(Adventure *a, Item i);   //TODO
void list_inventory(Adventure a);                 //TODO
void list_inventory(Adventure a);                 //TODO