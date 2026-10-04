#include "adventure.h"
#include "../database/adventure_table.h"
#include "inventory.h"
#include "item.h"

// Função auxiliar para validar as regras da ficha
static bool is_adventure_valid(const Adventure *a) {
   if (a->name[0] == '\0') return false;

   if (a->race < HUMAN || a->race > HALFLING) return false;

   if ((unsigned int)a->actual_life_points > a->max_life_points) return false;

   return true;
}

// --- Funções de Banco de Dados ---
StatusCode adventure_insert(Adventure *a) {
   Table *t = adventure_table();
   if (!is_adventure_valid(a)) return STATUS_INVALID_DATA;

   if (t->count >= t->capacity) return STATUS_FULL_STORAGE;

   a->id = adventure_table_next_id();
   if (table_insert(t, a)) return STATUS_SUCCESS;

   return STATUS_INVALID_DATA;
}

StatusCode adventure_update(int idx, const Adventure *a) {
   if (table_update(adventure_table(), idx, a)) return STATUS_SUCCESS;
   return STATUS_NOT_FOUND;
}

StatusCode adventure_delete(int idx) {
   if (table_delete(adventure_table(), idx)) return STATUS_SUCCESS;
   return STATUS_NOT_FOUND;
}

StatusCode adventure_get(int idx, Adventure *out_a) {
   Adventure *found = table_get(adventure_table(), idx);
   if (found) {
       *out_a = *found;
       return STATUS_SUCCESS;
   }
   return STATUS_NOT_FOUND;
}

static bool match_id(const void *row, const void *ctx) {
   return ((const Adventure *)row)->id == *(const unsigned int *)ctx;
}

StatusCode adventure_find_by_id(int id, int *out_idx) {
   int idx = table_find(adventure_table(), match_id, &id);
   if (idx >= 0) {
       *out_idx = idx;
       return STATUS_SUCCESS;
   }
   return STATUS_NOT_FOUND;
}

// --- Funções de Inventário ---
StatusCode move_item_to_active(Adventure *a, Item i){
   int index = -1;
   for (int j = 0; j < a->inv.last_free_space; j++) {
      if (a->inv.items[j].id == i.id) {
         index = j;
         break;
      }
   }

   if (index == -1) return STATUS_ITEM_NOT_FOUND;

   Item temp = {0};
   bool equipou = false;

   if (i.type == CHESTPLATE) { temp = a->chestplate; a->chestplate = i; equipou = true; }
   else if (i.type == HELMET) { temp = a->head; a->head = i; equipou = true; }
   else if (i.type == GLOVES) { temp = a->gloves; a->gloves = i; equipou = true; }
   else if (i.type == LEGGINGS) { temp = a->legs; a->legs = i; equipou = true; }
   else if (i.type == GREAVES) { temp = a->greaves; a->greaves = i; equipou = true; }
   else if (i.type == RING) { temp = a->ring; a->ring = i; equipou = true; }
   else if (i.type == NECKLACE) { temp = a->necklace; a->necklace = i; equipou = true; }
   else if (i.type == BELT) { temp = a->belt; a->belt = i; equipou = true; }
   else if (i.type == TWO_HAND_SWORD) {
      if (a->left_hand.id != 0 && a->inv.last_free_space == CAPACITY) {
          return STATUS_TWO_HAND_CONFLICT;
      }
      temp = a->right_hand;
      if (a->left_hand.id != 0) {
         add_item(&(a->inv), a->left_hand);
      }
      a->right_hand = i;
      a->left_hand = i;
      equipou = true;
   }
   else if (i.type == ONE_HAND_SWORD) {
      if (a->right_hand.id == 0) { a->right_hand = i; equipou = true; }
      else if (a->left_hand.id == 0) { a->left_hand = i; equipou = true; }
      else { temp = a->right_hand; a->right_hand = i; equipou = true; }
   }

   if (equipou) {
        if (temp.id != 0) {
            a->inv.items[index] = temp;
        } else {
            for (int k = index; k < a->inv.last_free_space - 1; k++) {
                a->inv.items[k] = a->inv.items[k + 1];
            }
            a->inv.last_free_space--;
        }
        return STATUS_SUCCESS;
    }
    return STATUS_INCOMPATIBLE_ITEM;
}

StatusCode move_item_inventory(Adventure *a, Item i){
   bool guardou = add_item(&(a->inv), i);
   if (!guardou) return STATUS_INVENTORY_FULL;

   Item vazio = {0};

   if (a->head.id == i.id) a->head = vazio;
   else if (a->chestplate.id == i.id) a->chestplate = vazio;
   else if (a->gloves.id == i.id) a->gloves = vazio;
   else if (a->legs.id == i.id) a->legs = vazio;
   else if (a->greaves.id == i.id) a->greaves = vazio;
   else if (a->ring.id == i.id) a->ring = vazio;
   else if (a->necklace.id == i.id) a->necklace = vazio;
   else if (a->belt.id == i.id) a->belt = vazio;
   else if (a->left_hand.id == i.id) a->left_hand = vazio;
   else if (a->right_hand.id == i.id) a->right_hand = vazio;

   return STATUS_SUCCESS;
}

void list_inventory(const Adventure *a){
   printf("\n=== Inventario de %s ===\n", a->name);

   if(a->inv.last_free_space == 0){
      printf("A Mochila esta vazia!\n");
      return;
   }

   for(int j = 0; j < a->inv.last_free_space; ++j){
      Item atual = a->inv.items[j];
      printf("[%d] %s (Ataque: %d | Defesa: %d | Vida: %d)\n",
               atual.id, atual.name, atual.attack_bonus, atual.defence_bonus, atual.life_bonus);
   }
   printf("==================================\n");
}

bool is_item_in_inventory(const Adventure *a, Item i){
   for(int j = 0; j < a->inv.last_free_space; ++j){
      if(a->inv.items[j].id == i.id) return true;
   }
   return false;
}

bool is_item_in_active_slot(const Adventure *a, Item i){
   if(a->head.id == i.id) return true;
   else if(a->chestplate.id == i.id) return true;
   else if(a->gloves.id == i.id) return true;
   else if(a->legs.id == i.id) return true;
   else if(a->greaves.id == i.id) return true;
   else if(a->ring.id == i.id) return true;
   else if(a->necklace.id == i.id) return true;
   else if(a->belt.id == i.id) return true;
   else if(a->left_hand.id == i.id) return true;
   else if(a->right_hand.id == i.id) return true;

   return false;
}
