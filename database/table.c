/*Se necessario, podemos mudar tudo para armazenamento de arquivo :)*/
#include "table.h"
#include <string.h>

static void *row_at(const Table *t, size_t i) {
    return (char *)t->rows + i * t->elem_size;
}

static bool valid(const Table *t, int idx) {
    return idx >= 0 && (size_t)idx < t->capacity && t->used[idx];
}

// "up": liga a tabela ao armazenamento e zera tudo
void table_up(Table *t, void *rows, bool *used, size_t elem_size, size_t capacity) {
    t->rows = rows;
    t->used = used;
    t->elem_size = elem_size;
    t->capacity = capacity;
    t->count = 0;
    memset(used, 0, capacity * sizeof *used);
    memset(rows, 0, capacity * elem_size);
}

// "down": marca tudo como livre
void table_down(Table *t) {
    memset(t->used, 0, t->capacity * sizeof *t->used);
    memset(t->rows, 0, t->capacity * t->elem_size);
    t->count = 0;
}

static int find_free(const Table *t) {
    for (size_t i = 0; i < t->capacity; ++i)
        if (!t->used[i]) return (int)i;
    return -1;
}

int table_insert(Table *t, const void *data) {
    int pos = find_free(t);
    if (pos < 0) return -1;                       // tabela cheia

    memcpy(row_at(t, pos), data, t->elem_size);
    t->used[pos] = true;
    t->count++;
    return 1;
}

bool table_update(Table *t, int idx, const void *data) {
    if (!valid(t, idx)) return false;
    memcpy(row_at(t, idx), data, t->elem_size);
    return true;
}

bool table_delete(Table *t, int idx) {
    if (!valid(t, idx)) return false;
    memset(row_at(t, idx), 0, t->elem_size);
    t->used[idx] = false;
    t->count--;
    return true;
}

void *table_get(const Table *t, int idx) {
    return valid(t, idx) ? row_at(t, idx) : NULL;
}

int table_find(const Table *t, RowPredicate pred, const void *ctx) {
    for (size_t i = 0; i < t->capacity; ++i)
        if (t->used[i] && pred(row_at(t, i), ctx))
            return (int)i;
    return -1;
}

void table_foreach(const Table *t, RowVisitor fn, void *ctx) {
    for (size_t i = 0; i < t->capacity; ++i)
        if (t->used[i]) fn(row_at(t, i), ctx);
}