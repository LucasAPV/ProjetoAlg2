#include "./read_txt.h"
#include "./size_of_objs.h"
#include <string.h>

FILE* open_file(char* file_name, char* mode){
    FILE *f;
    f = fopen(file_name, mode);
    return f;
}

/*
    Estou passando a responsabilidade de free do arquivo para o caller desta funcao,
  ou seja, quem chama tem que liberar o arquivo depois.

  Alem do mais, acredito que se for passar o intervalo [a,a] ele pega a linha a
*/

char* get_file_text(FILE *f, const int intervalo[2]){
    if (f == NULL) return NULL;

    char *buffer = NULL;
    long size_to_read = 0;

    if (intervalo != NULL) {
        int start = intervalo[0];
        int end = intervalo[1];

        if (end < start) return NULL;
        fseek(f, start, SEEK_SET);
        size_to_read = end - start;

        buffer = (char *)malloc(size_to_read + 1); //to add \0 after
        if(buffer == NULL) return NULL;

        size_t been_read = fread(buffer, 1, size_to_read, f);
        buffer[been_read] = '\0';
    } else {
        fseek(f, 0, SEEK_END);
        long tamanho_total = ftell(f);
        rewind(f);

        buffer = (char *)malloc(tamanho_total + 1);
        if (buffer == NULL) return NULL;

        size_t lidos = fread(buffer, 1, tamanho_total, f);
        buffer[lidos] = '\0';
    }

    return buffer;
}


ColValue line_to_struct(char* col_buffer, char* value_buffer) {
    ColValue cv = {0};
    cv.value = value_buffer;
    cv.col_name = (ColumnBeast)-1; // Caso nao ache

    // Calcula size da tabela
    size_t num_maps = sizeof(COLUMN_MAPS) / sizeof(COLUMN_MAPS[0]);

    // Percorre a tabela buscando a correspondencia
    for (size_t i = 0; i < num_maps; i++) {
        if (strcmp(col_buffer, COLUMN_MAPS[i].str) == 0) {
            cv.col_name = COLUMN_MAPS[i].beast;
            break;
        }
    }

    return cv;
}

ColValue parse_line(char* line){
    ColValue cv = {0};
    char* col_buffer = (char*)malloc(sizeof(char)*TEXT_SIZE);
    char* value_buffer = (char*)malloc(sizeof(char)*TEXT_SIZE);
    int found_separator = 0;
    int counter = 0;

    for(int i = 0; i < TEXT_SIZE; ++i){
        if(strcmp(&line[i], "\0") == 0) break;

        if(strcmp(&line[i], "=") == 0) found_separator = 1;

        if(found_separator == 0) {
            col_buffer[i] = line[i];
        } else {
            value_buffer[counter] = line[i];
            counter++;
        }
    }
    cv = line_to_struct(col_buffer,value_buffer);

    return cv;
}
