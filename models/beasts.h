#define MAX_TEXT_LENGTH_MOB 50
#define GRID 2
#define VARIETY 5


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
    Defence resistenciaMagia;
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