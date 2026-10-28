#ifndef __BEASTS__
#define __BEASTS__

#define MAX_TEXT_LENGTH_MOB 50
#define GRID 2
#define VARIETY 5
#define QTD_COLUMNS 37

/*
[TODO]
    title="Impl e Rearranjo"
    desc="Implementar cada estrutrura e enum, e pensar a possibilidade de estrutura-las cada uma em seu arquivo"
    relevance=Medio
[/TODO]
 */

typedef enum    {} Freq;
typedef enum    {} Active;

typedef struct  {} Dice;
typedef struct  {} Treasure;
typedef struct  {} Moveset;
typedef struct  {} Attack;
typedef struct  {} Defence;
typedef struct  {} TerrainMod;


typedef struct {
    int id;
    char nome[MAX_TEXT_LENGTH_MOB];
    char descricao[MAX_TEXT_LENGTH_MOB];
    Freq frequencia;
    Dice numeroEncontrado;
    int covil[GRID];
    char climas[MAX_TEXT_LENGTH_MOB];
    char terrenos[MAX_TEXT_LENGTH_MOB][MAX_TEXT_LENGTH_MOB];
    char organizacao[MAX_TEXT_LENGTH_MOB];
    Active atividade;
    char dieta[MAX_TEXT_LENGTH_MOB];
    int inteligencia;
    Treasure tesouro;
    char ordem[MAX_TEXT_LENGTH_MOB];
    char moralidade[MAX_TEXT_LENGTH_MOB];
    int ca;
    Moveset movimentos;
    Dice dv;
    int thac0;
    Attack ataques;
    Attack ataquesEspeciais;
    Defence defesasEspeciais;
    int resistenciaMagia;
    char tamanho[MAX_TEXT_LENGTH_MOB];
    float altura[VARIETY];
    int moral;
    char classificacaoMoral[MAX_TEXT_LENGTH_MOB];
    int xp;
    int poderBase;
    int modDia;
    int modNoite;
    TerrainMod modTerreno;
    int bonusPorAdicional;
    int limiteGrupoGrande;
    int bonusGrupoGrande;
    char descricaoCombate[MAX_TEXT_LENGTH_MOB];
    char habitatSociedade[MAX_TEXT_LENGTH_MOB];
    char descricaoEcologia[MAX_TEXT_LENGTH_MOB];
} Beast;

typedef enum ColumnBeast {
    ID,
    NOME,
    DESCRICAO,
    FREQUENCIA,
    NUMERO_ENCONTRADO,
    COVIL,
    CLIMAS,
    TERRENOS,
    ORGANIZACAO,
    ATIVIDADE,
    DIETA,
    INTELIGENCIA,
    TESOURO,
    ORDEM,
    MORALIDADE,
    CA,
    MOVIMENTOS,
    DV,
    THAC_0,
    ATAQUES,
    ATAQUES_ESPECIAIS,
    DEFESAS_ESPECIAIS,
    RESISTENCIA_MAGIA,
    TAMANHO,
    ALTURA,
    MORAL,
    CLASSIFICACAO_MORAL,
    XP,
    PODER_BASE,
    MOD_DIA,
    MOD_NOITE,
    MOD_TERRENO,
    BONUS_POR_ADICIONAL,
    LIMITE_GRUPO_GRANDE,
    BONUS_GRUPO_GRANDE,
    DESCRICAO_COMBATE,
    HABITAT_SOCIEDADE,
    DESCRICAO_ECOLOGIA,
} ColumnBeast;

typedef struct {
    const char* str;
    ColumnBeast beast;
} ColumnMap;

static const ColumnMap COLUMN_MAPS[] = {
    {"id", ID},
    {"nome", NOME},
    {"descricao", DESCRICAO},
    {"frequencia", FREQUENCIA},
    {"numeroEncontrado", NUMERO_ENCONTRADO},
    {"covil", COVIL},
    {"climas", CLIMAS},
    {"terrenos", TERRENOS},
    {"organizacao", ORGANIZACAO},
    {"atividade", ATIVIDADE},
    {"dieta", DIETA},
    {"inteligencia", INTELIGENCIA},
    {"tesouro", TESOURO},
    {"ordem", ORDEM},
    {"moralidade", MORALIDADE},
    {"ca", CA},
    {"movimentos", MOVIMENTOS},
    {"dv", DV},
    {"thac0", THAC_0},
    {"ataques", ATAQUES},
    {"ataquesEspeciais", ATAQUES_ESPECIAIS},
    {"defesasEspeciais", DEFESAS_ESPECIAIS},
    {"resistenciaMagia", RESISTENCIA_MAGIA},
    {"tamanho", TAMANHO},
    {"altura", ALTURA},
    {"moral", MORAL},
    {"classificacaoMoral", CLASSIFICACAO_MORAL},
    {"xp", XP},
    {"poderBase", PODER_BASE},
    {"modDia", MOD_DIA},
    {"modNoite", MOD_NOITE},
    {"modTerreno", MOD_TERRENO},
    {"bonusPorAdicional", BONUS_POR_ADICIONAL},
    {"limiteGrupoGrande", LIMITE_GRUPO_GRANDE},
    {"bonusGrupoGrande", BONUS_GRUPO_GRANDE},
    {"descricaoCombate", DESCRICAO_COMBATE},
    {"habitatSociedade", HABITAT_SOCIEDADE},
    {"descricaoEcologia", DESCRICAO_ECOLOGIA}
};




#endif