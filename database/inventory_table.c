#include "inventory_table.h"
#include "../models/inventory.h"

#define MAX_INVENTORYS 50
TABLE_STORAGE(inventorys, Inventory, MAX_INVENTORYS);
static int next_id = 1;

void inventory_table_up(void)   { TABLE_UP(inventorys); next_id = 1; }
void inventory_table_down(void) { table_down(&inventorys); next_id = 1; }

Table *inventory_table(void)        { return &inventorys; }
int    inventory_table_next_id(void){ return next_id++; }
