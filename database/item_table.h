#ifndef ITEM_TABLE_H
#define ITEM_TABLE_H

#include "table.h"

void   item_table_up(void);
void   item_table_down(void);
Table *item_table(void);          // acesso ao descritor
int    item_table_next_id(void);  // auto-incremento

#endif