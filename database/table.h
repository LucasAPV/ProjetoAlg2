/*
   Um modelo generico para podermos criar qualquer tipo de estrutura sem precisar recopiar codigo.
   Depois, se for pedido, sera mais facil mudar para um armazenamento em arquivo.
*/

#ifndef TABLE_H
#define TABLE_H

#include <stddef.h>
#include <stdbool.h>

typedef struct Table {
    void   *rows;       // aponta para o array estático (de qualquer tipo)
    bool   *used;       // used[i] == true -> slot i está ocupado
    size_t  elem_size;  // sizeof(tipo da linha)
    size_t  capacity;   // n maximo de linhas
    size_t  count;      // n de linhas ocupadas
} Table;

// Predicado para buscas: retorna true se a linha bate com o criterio
typedef bool (*RowPredicate)(const void *row, const void *ctx);
typedef void (*RowVisitor)(const void *row, void *ctx);

void  table_up(Table *t, void *rows, bool *used, size_t elem_size, size_t capacity);
void  table_down(Table *t);

int   table_insert(Table *t, const void *data);            // retorna indice ou -1
bool  table_update(Table *t, int idx, const void *data);
bool  table_delete(Table *t, int idx);
void *table_get(const Table *t, int idx);                  // NULL se invalido

int   table_find(const Table *t, RowPredicate pred, const void *ctx);
void  table_foreach(const Table *t, RowVisitor fn, void *ctx);

//declara o armazenamento estatico de uma tabela
#define TABLE_STORAGE(name, type, cap) \
   static type name##_rows[cap];      \
   static bool name##_used[cap];      \
   static Table name

/* Para criar as tabela da estrutura de uma vez */
#define TABLE_UP(name) \
    table_up(&(name), name##_rows, name##_used, \
             sizeof *name##_rows, sizeof name##_rows / sizeof *name##_rows)

#endif