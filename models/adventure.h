#ifndef ADVENTURE_H
#define ADVENTURE_H

#include <stdbool.h>

#define MAX_NAME_LENGTH 50
#define MAX_ADVENTURES  20

typedef enum Race { HUMAN, ELF, DWARF, HALFLING } Race;

typedef struct Adventure {
   int id;
   unsigned int level : 5;
   unsigned int max_life_points : 10;
   signed int   actual_life_points : 10;
   unsigned int attack : 5;
   unsigned int defense : 5;
   signed int   initiative : 5;
   signed int   power : 7;
   char name[MAX_NAME_LENGTH];
   Race race;
} Adventure;

int        adventure_insert(Adventure *a);
bool       adventure_update(int idx, const Adventure *a);
bool       adventure_delete(int idx);
Adventure *adventure_get(int idx);
int        adventure_find_by_id(int id);

#endif