#ifndef ADVENTURE_TABLE_H
#define ADVENTURE_TABLE_H

#include "table.h"

void   adventure_table_up(void);
void   adventure_table_down(void);
Table *adventure_table(void);          // acesso ao descritor
int    adventure_table_next_id(void);  // auto-incremento

#endif