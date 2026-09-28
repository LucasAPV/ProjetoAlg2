#include "item_table.h"
#include "item.h"

TABLE_STORAGE(adventures, Adventure, MAX_ADVENTURES);
static int next_id = 1;

void item_table_up(void)   { TABLE_UP(items); next_id = 1; }
void item_table_down(void) { table_down(&items); next_id = 1; }

Table *item_table(void)        { return &items; }
int    item_table_next_id(void){ return next_id++; }