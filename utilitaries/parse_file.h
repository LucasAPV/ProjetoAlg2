#ifndef __PARSE_FILE__
#define __PARSE_FILE__
#define FILE_PATH "../beastiary/bestiario.txt"
#include "../models/beasts.h"
/*
  Essa funcao vai achar a parte do txt que e um monstro, ou seja, vai retornar:

  [MONSTRO]
  *def do monstro*
  [/MONSTRO]

  tentar retonar uma matriz para poder ficar assim:

  0: [MONSTRO]
  1: id
  2: ...
  ...
  n: [/MONSTRO]
 */

/*
 [TODO]
    title="next_beast_definition"
    relevance=Importante
 [/TODO]
 */
char* next_beast_definition(int start_pos);

/*
    Essa funcao vai permitir transformar o texto na estrutura em C do monstro
 */
/*
 [TODO]
    title="parse_beast"
    relevance=Importante
 [/TODO]
 */
Beast parse_beast(char** beast_def);



#endif