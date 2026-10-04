#ifndef ADVENTURE_H
#define ADVENTURE_H

#include <stdbool.h>
#include "inventory.h"
#include "item.h"
#include <stdio.h>

#define MAX_NAME_LENGTH 50
#define MAX_ADVENTURES 20

typedef enum {
   STATUS_SUCCESS = 0,
   STATUS_FULL_STORAGE,       // Cadastro cheio
   STATUS_DUPLICATE_ID,       // ID duplicado
   STATUS_NOT_FOUND,          // Não encontrado
   STATUS_INVALID_DATA,       // Dados inválidos
   STATUS_INVENTORY_FULL,     // Inventário sem espaço
   STATUS_INCOMPATIBLE_ITEM,  // Item incompatível com a posição
   STATUS_ITEM_NOT_FOUND,     // Item não encontrado
   STATUS_TWO_HAND_CONFLICT   // Conflito com arma de duas mãos
} StatusCode;

typedef enum Race
{
   HUMAN,
   ELF,
   DWARF,
   HALFLING
} Race;

typedef struct Adventure
{
   unsigned int id;
   unsigned int level;
   unsigned int max_life_points;
   int actual_life_points;
   unsigned int attack;
   unsigned int defense;
   int initiative;
   int power;
   char name[MAX_NAME_LENGTH];
   Inventory inv;
   Item head, chestplate, gloves,
       legs, greaves, ring, necklace, belt, left_hand, right_hand;
   /*Esses sao os itens equipados pelo personagem,
      poderiamos mudar para um vetor (talvez de chave e valor )*/
   Race race;
} Adventure;

StatusCode adventure_insert(Adventure *a);
StatusCode adventure_update(int idx, const Adventure *a);
StatusCode adventure_delete(int idx);
StatusCode adventure_get(int idx, Adventure *out_a);
StatusCode adventure_find_by_id(int id, int *out_idx);

bool is_item_in_inventory(const Adventure *a, Item i);
bool is_item_in_active_slot(const Adventure *a, Item i);
StatusCode move_item_to_active(Adventure *a, Item i);
StatusCode move_item_inventory(Adventure *a, Item i);
void list_inventory(const Adventure *a);
#endif
