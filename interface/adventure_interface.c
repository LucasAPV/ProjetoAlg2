#include <stdio.h>
#include "adventure_interface.h"

// --- FUNÇÕES AUXILIARES ---
static void limpa_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Helper para buscar o personagem e o índice dele na tabela de uma vez
static StatusCode get_personagem_by_id(int id, int *out_idx, Adventure *out_a) {
    StatusCode st = adventure_find_by_id(id, out_idx);
    if (st != STATUS_SUCCESS) return st;
    return adventure_get(*out_idx, out_a);
}

static void print_status_error(StatusCode st) {
    switch (st) {
        case STATUS_FULL_STORAGE: printf("[Erro] Cadastro ou Mochila cheia!\n"); break;
        case STATUS_DUPLICATE_ID: printf("[Erro] ID duplicado!\n"); break;
        case STATUS_NOT_FOUND: printf("[Erro] Personagem nao encontrado!\n"); break;
        case STATUS_INVALID_DATA: printf("[Erro] Dados invalidos!\n"); break;
        case STATUS_INVENTORY_FULL: printf("[Erro] Inventario sem espaco!\n"); break;
        case STATUS_INCOMPATIBLE_ITEM: printf("[Erro] Item incompativel com a posicao!\n"); break;
        case STATUS_ITEM_NOT_FOUND: printf("[Erro] Item nao encontrado!\n"); break;
        case STATUS_TWO_HAND_CONFLICT: printf("[Erro] Conflito com arma de duas maos! Suas maos estao ocupadas ou mochila cheia.\n"); break;
        default: printf("[Erro] Falha desconhecida.\n");
    }
}

// --- IMPLEMENTAÇÃO DO MENU ---

void interface_cadastrar_personagem() {
    Adventure novo = {0};
    printf("Nome do personagem: ");
    scanf(" %49[^\n]", novo.name);
    limpa_buffer();

    printf("Raca (0-Humano, 1-Elfo, 2-Anao, 3-Halfling): ");
    scanf("%u", (unsigned int*)&novo.race);

    printf("Nivel inicial: "); scanf("%u", &novo.level);
    printf("HP Maximo: "); scanf("%u", &novo.max_life_points);
    novo.actual_life_points = novo.max_life_points;

    printf("HP Atual: "); scanf("%d", &novo.actual_life_points);

    printf("Ataque base: "); scanf("%u", &novo.attack);
    printf("Defesa base: "); scanf("%u", &novo.defense);

    StatusCode st = adventure_insert(&novo);

    if (st == STATUS_SUCCESS) {
        printf("\n[Sucesso] '%s' cadastrado! ID gerado: %d\n", novo.name, novo.id);
    } else {
        print_status_error(st);
    }
}

void interface_consultar_personagem() {
    int id, idx; Adventure a;
    printf("Digite o ID do personagem: "); scanf("%d", &id);

    if (get_personagem_by_id(id, &idx, &a) == STATUS_SUCCESS) {
        printf("\n--- Dados do Personagem ---\n");
        printf("ID: %d | Nome: %s | Nivel: %d\n", a.id, a.name, a.level);
        printf("HP: %d/%d | Ataque: %d | Defesa: %d\n", a.actual_life_points, a.max_life_points, a.attack, a.defense);
    } else {
        printf("[Erro] Personagem ID %d nao encontrado.\n", id);
    }
}

void interface_alterar_personagem() {
    int id, idx; Adventure a;
    printf("Digite o ID do personagem a alterar: "); scanf("%d", &id);

    if (get_personagem_by_id(id, &idx, &a) == STATUS_SUCCESS) {
        printf("Novo Nivel (Atual %d): ", a.level); scanf("%u", &a.level);
        printf("Novo Ataque (Atual %d): ", a.attack); scanf("%u", &a.attack);
        printf("Nova Defesa (Atual %d): ", a.defense); scanf("%u", &a.defense);

        if (adventure_update(idx, &a) == STATUS_SUCCESS) {
            printf("[Sucesso] Personagem atualizado!\n");
        }
    } else {
        printf("[Erro] Personagem nao encontrado.\n");
    }
}

void interface_remover_personagem() {
    int id, idx;
    printf("Digite o ID do personagem a remover: "); scanf("%d", &id);

    if (adventure_find_by_id(id, &idx) == STATUS_SUCCESS) {
        if (adventure_delete(idx) == STATUS_SUCCESS) {
            printf("[Sucesso] Personagem removido com sucesso!\n");
        }
    } else {
        printf("[Erro] Personagem nao encontrado.\n");
    }
}

void interface_listar_personagens() {
    bool encontrou_algum = false;
    for (int i = 0; i < MAX_ADVENTURES; i++) {
        Adventure a;
        if (adventure_get(i, &a) == STATUS_SUCCESS) {
            printf("[%d] %s (Nvl %d)\n", a.id, a.name, a.level);
            encontrou_algum = true;
        }
    }
    if (!encontrou_algum) printf("Nenhum personagem cadastrado.\n");
}

void criar_item(Item *novo_item) {
    printf("ID do Item: "); scanf("%u", &novo_item->id);
    printf("Nome do Item: "); scanf(" %49[^\n]", novo_item->name); limpa_buffer();
    printf("Tipo (0-Helmet, 1-Chestplate, 2-Gloves, 3-Leggings, 4-Greaves, 5-Ring, 6-Necklace, 7-Belt, 8-Espada 1M, 9-Espada 2M): ");
    scanf("%u", (unsigned int*)&novo_item->type);

    printf("Ataque bonus: "); scanf("%d", &novo_item->attack_bonus);
    printf("Defesa bonus: "); scanf("%d", &novo_item->defence_bonus);
    printf("Vida bonus: "); scanf("%d", &novo_item->life_bonus);
    printf("Iniciativa bonus: "); scanf("%d", &novo_item->initiative_bunus);
    printf("Poder: "); scanf("%u", &novo_item->power);

    printf("Espaco ocupado (1 a 50): ");
    scanf("%u", (unsigned int*)&novo_item->space_ocuppied);
}

void interface_administrar_inventario() {
    int id, idx; Adventure a;
    printf("ID do personagem: "); scanf("%d", &id);

    if (get_personagem_by_id(id, &idx, &a) == STATUS_SUCCESS) {
        list_inventory(&a);

        printf("\nDeseja adicionar um item a mochila? (1-Sim, 0-Nao): ");
        int op; scanf("%d", &op);
        if (op == 1) {
            Item novo_item = {0};

            criar_item(&novo_item);

            if (add_item(&(a.inv), novo_item)) {
                adventure_update(idx, &a);
                printf("[Sucesso] Item adicionado a mochila!\n");
            } else {
                printf("[Erro] Mochila cheia!\n");
            }
        }
    } else {
        printf("[Erro] Personagem nao encontrado.\n");
    }
}

void interface_consultar_equipamentos() {
    int id, idx; Adventure a;
    printf("ID do personagem: "); scanf("%d", &id);

    if (get_personagem_by_id(id, &idx, &a) == STATUS_SUCCESS) {
        printf("\n--- Equipamentos Ativos ---\n");
        printf("Cabeca: %s\n", a.head.id ? a.head.name : "Vazio");
        printf("Peito: %s\n", a.chestplate.id ? a.chestplate.name : "Vazio");
        printf("Mao Direita: %s\n", a.right_hand.id ? a.right_hand.name : "Vazio");
        printf("Mao Esquerda: %s\n", a.left_hand.id ? a.left_hand.name : "Vazio");
        printf("Luvas: %s\n", a.gloves.id ? a.gloves.name : "Vazio");
        printf("Calcas: %s\n", a.legs.id ? a.legs.name : "Vazio");
        printf("Grevas: %s\n", a.greaves.id ? a.greaves.name : "Vazio");
        printf("Anel: %s\n", a.ring.id ? a.ring.name : "Vazio");
        printf("Colar: %s\n", a.necklace.id ? a.necklace.name : "Vazio");
        printf("Cinto: %s\n", a.belt.id ? a.belt.name : "Vazio");
    } else {
        printf("[Erro] Personagem nao encontrado.\n");
    }
}

void interface_equipar_item() {
    int id, idx, item_id; Adventure a;
    printf("ID do personagem: "); scanf("%d", &id);

    if (get_personagem_by_id(id, &idx, &a) == STATUS_SUCCESS) {
        printf("Digite o ID do item da mochila que deseja equipar: "); scanf("%d", &item_id);

        Item item_para_equipar = {0};
        bool encontrou = false;
        for (int j = 0; j < a.inv.last_free_space; j++) {
            if (a.inv.items[j].id == (unsigned int)item_id) {
                item_para_equipar = a.inv.items[j];
                encontrou = true;
                break;
            }
        }

        if (!encontrou) {
            printf("[Erro] Item ID %d nao esta na mochila!\n", item_id);
            return;
        }

        StatusCode st = move_item_to_active(&a, item_para_equipar);

        if (st == STATUS_SUCCESS) {
            adventure_update(idx, &a);
            printf("[Sucesso] Item equipado!\n");
        } else {
            print_status_error(st);
        }
    } else {
        printf("[Erro] Personagem nao encontrado.\n");
    }
}

void interface_desequipar_item() {
    int id, idx, item_id; Adventure a;
    printf("ID do personagem: "); scanf("%d", &id);

    if (get_personagem_by_id(id, &idx, &a) == STATUS_SUCCESS) {
        printf("Digite o ID do item equipado que deseja guardar na mochila: "); scanf("%d", &item_id);

        Item item_para_guardar = {0};
        if      (a.head.id       == (unsigned int)item_id) item_para_guardar = a.head;
        else if (a.chestplate.id == (unsigned int)item_id) item_para_guardar = a.chestplate;
        else if (a.right_hand.id == (unsigned int)item_id) item_para_guardar = a.right_hand;
        else if (a.left_hand.id  == (unsigned int)item_id) item_para_guardar = a.left_hand;
        else if (a.gloves.id     == (unsigned int)item_id) item_para_guardar = a.gloves;
        else if (a.legs.id       == (unsigned int)item_id) item_para_guardar = a.legs;
        else if (a.greaves.id    == (unsigned int)item_id) item_para_guardar = a.greaves;
        else if (a.ring.id       == (unsigned int)item_id) item_para_guardar = a.ring;
        else if (a.necklace.id   == (unsigned int)item_id) item_para_guardar = a.necklace;
        else if (a.belt.id       == (unsigned int)item_id) item_para_guardar = a.belt;

        if (item_para_guardar.id == 0) {
            printf("[Erro] O item %d nao esta equipado no momento.\n", item_id);
            return;
        }

        StatusCode st = move_item_inventory(&a, item_para_guardar);

        if (st == STATUS_SUCCESS) {
            adventure_update(idx, &a);
            printf("[Sucesso] Item removido e guardado na mochila!\n");
        } else {
            print_status_error(st);
        }
    } else {
        printf("[Erro] Personagem nao encontrado.\n");
    }
}

void interface_exibir_atributos() {
    int id, idx; Adventure a;
    printf("ID do personagem: "); scanf("%d", &id);

    if (get_personagem_by_id(id, &idx, &a) == STATUS_SUCCESS) {
        int total_atk = a.attack;
        int total_def = a.defense;

        printf("\n--- Atributos Totais de %s ---\n", a.name);
        printf("Ataque (Base + Equipamentos): %d\n", total_atk);
        printf("Defesa (Base + Equipamentos): %d\n", total_def);
    } else {
        printf("[Erro] Personagem nao encontrado.\n");
    }
}
