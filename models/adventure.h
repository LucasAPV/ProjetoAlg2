#ifndef ADVENTURE_H
#define ADVENTURE_H

#include <stdbool.h>
#include "inventory.h"
#include "item.h"

#define MAX_NAME_LENGTH 50
#define MAX_ADVENTURES  20

typedef enum Race { HUMAN, ELF, DWARF, HALFLING } Race;

typedef struct Adventure {
   unsigned int id;
   unsigned int level;
   unsigned int max_life_points;
   int   actual_life_points;
   unsigned int attack;
   unsigned int defense;
   int   initiative;
   int   power;
   char name[MAX_NAME_LENGTH];
   Inventory inv;
   Item head, chestplate, gloves,
      legs, greaves, ring, necklace, belt, left_hand, right_hand;
      /*Esses sao os itens equipados pelo personagem,
         poderiamos mudar para um vetor (talvez de chave e valor )*/
   Race race;
} Adventure;

int        adventure_insert(Adventure *a);
bool       adventure_update(int idx, const Adventure *a);
bool       adventure_delete(int idx);
Adventure *adventure_get(int idx);
int        adventure_find_by_id(int id);
void       move_item_to_active(Adventure *a, Item item);  //TODO
void       move_item_inventory(Adventure *a, Item item);  //TODO
void       list_inventory(Adventure a);                //TODO
bool       is_item_in_inventory(Adventure a, Item item);  //TODO
bool       is_item_in_active_slot(Adventure a, Item item);//TODO
#endif