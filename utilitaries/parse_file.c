#include "./parse_file.h"
#include "./read_txt.h"
#include <stdlib.h>

char* next_beast_definition(int start_pos){
    FILE *beasts_file = open_file(FILE_PATH, "r");
    char *beast_instance = (char*) malloc(sizeof(char) * QTD_COLUMNS);

    const int range[2] = {start_pos, start_pos + QTD_COLUMNS};
    beast_instance = get_file_text(beasts_file,  range);

    fclose(beasts_file);
    return beast_instance;
}

Beast parse_beast(char** beast_def){
    Beast b = (Beast) {};
    ColValue cv = {};
    for(int i = 0; i < QTD_COLUMNS; ++i) {
        cv = parse_line(beast_def[i]);

        switch (cv.col_name) {

            /* Tratando o que for inteiro */
            case ID:
                b.id = atoi(cv.value);
                break;
            case INTELIGENCIA:
                b.inteligencia = atoi(cv.value);
                break;
            case CA:
                b.ca = atoi(cv.value);
                break;
            case THAC_0:
                b.thac0 = atoi(cv.value);
                break;
            case RESISTENCIA_MAGIA:
                b.resistenciaMagia = atoi(cv.value);
                break;
            case MORAL:
                b.moral = atoi(cv.value);
                break;
            case XP:
                b.xp = atoi(cv.value);
                break;
            case PODER_BASE:
                b.poderBase = atoi(cv.value);
                break;
            case MOD_DIA:
                b.modDia = atoi(cv.value);
                break;
            case MOD_NOITE:
                b.modNoite = atoi(cv.value);
                break;
            case BONUS_POR_ADICIONAL:
                b.bonusPorAdicional = atoi(cv.value);
                break;
            case BONUS_GRUPO_GRANDE:
                b.bonusGrupoGrande = atoi(cv.value);
                break;
            case LIMITE_GRUPO_GRANDE:
                b.limiteGrupoGrande = atoi(cv.value);
                break;

            /*Tratando o que for objetos compostos*/
            /*Criar funcao para parsear esses objetos especificos*/
            
            /*Tratando o que for vetores*/
            /*Criar funcao para parsear os vetores especificos*/
        }
    }
    return b;
}


/*
    [TODO]
        title="Objetos compostos"
        desc="Criar essa funcao para gerar os objetos compostos para colocar em cada bicho"
        relevance=Importante
    [/TODO]

*/

void generate_compost_obj(Beast *b, ColValue cv) {
    switch(cv.col_name){
        case TESOURO:
            b.trasure; /*ASCII TO TREASURE*/
            break;
    }
}
