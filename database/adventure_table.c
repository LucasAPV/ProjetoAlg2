#include "adventure_table.h"
#include "adventure.h"      // precisa do sizeof(Adventure)

TABLE_STORAGE(adventures, Adventure, MAX_ADVENTURES);
static int next_id = 1;

void adventure_table_up(void)   { TABLE_UP(adventures); next_id = 1; }
void adventure_table_down(void) { table_down(&adventures); next_id = 1; }

Table *adventure_table(void)        { return &adventures; }
int    adventure_table_next_id(void){ return next_id++; }