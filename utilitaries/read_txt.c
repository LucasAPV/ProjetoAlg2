/*
    [TODO]
        title="Encapsular leitura e mudanca de arquivos"
        desc="Desenvolver funcoes de encapsulamento de leitura de mudanca de arquivos"
        relevance=Importante
    [/TODO]
 */

#include <stdio.h>
#include <stdlib.h>

FILE* open_file(char* file_name, char* mode){
    FILE *f;
    f = fopen(file_name, mode);
    return f;
}

/*
    Estou passando a responsabilidade de free do arquivo para o caller desta funcao,
  ou seja, quem chama tem que liberar o arquivo depois.
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
