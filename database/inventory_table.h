#ifndef INVENTORY_TABLE_H
#define INVENTORY_TABLE_H

#include "table.h"

void   inventory_table_up(void);
void   inventory_table_down(void);
Table *inventory_table(void);          // acesso ao descritor
int    inventory_table_next_id(void);  // auto-incremento

#endif