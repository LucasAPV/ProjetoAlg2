#include <stdio.h>
#include <string.h>
#include "interface/adventure_interface.h"
#include "database/adventure_table.h"
#include "database/inventory_table.h"
#include "database/item_table.h"
#include "interface/interface.h"

void exibir_menu() {

    char menu_name[] = "MENU DE AVENTURAS";
    int menu_name_length = strlen(menu_name);
    int num_options = 11;
    char *option_names[] = {
        "Cadastrar personagem",
        "Consultar personagem por ID",
        "Alterar personagem",
        "Remover personagem",
        "Listar personagens",
        "Administrar inventario",
        "Consultar equipamentos",
        "Equipar item",
        "Desequipar item",
        "Exibir atributos totais",
        "Encerrar"
    };

    create_interface(menu_name, option_names, num_options, menu_name_length);
}

int main() {
    int opcao;

    // INICIALIZA O BANCO DE DADOS (Ativa as tabelas na memória)
    adventure_table_up();
    inventory_table_up();
    item_table_up();

    do {
        exibir_menu();
        printf("Escolha uma opcao: ");

        //Proteção caso o utilizador digite uma letra em vez de número
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n'); //Limpa o buffer do teclado
            opcao = -1;
        }

        switch (opcao) {
            case 1:
                printf("\n--- Cadastrar Personagem ---\n");
                interface_cadastrar_personagem();
                break;
            case 2:
                printf("\n--- Consultar por ID ---\n");
                interface_consultar_personagem();
                break;
            case 3:
                printf("\n--- Alterar Personagem ---\n");
                interface_alterar_personagem();
                break;
            case 4:
                printf("\n--- Remover Personagem ---\n");
                interface_remover_personagem();
                break;
            case 5:
                printf("\n--- Listar Personagens ---\n");
                interface_listar_personagens();
                break;
            case 6:
                printf("\n--- Administrar Inventario ---\n");
                interface_administrar_inventario();
                break;
            case 7:
                printf("\n--- Consultar Equipamentos ---\n");
                interface_consultar_equipamentos();
                break;
            case 8:
                printf("\n--- Equipar Item ---\n");
                interface_equipar_item();
                break;
            case 9:
                printf("\n--- Desequipar Item ---\n");
                interface_desequipar_item();
                break;
            case 10:
                printf("\n--- Exibir Atributos Totais ---\n");
                interface_exibir_atributos();
                break;
            case 11:
                printf("\nA encerrar o sistema. Ate logo!\n");
                break;
            case 0:
                printf("\nA encerrar o sistema. Ate logo!\n");
                break;
            default:
                printf("\n[Erro] Opcao invalida! Escolha um numero entre 0 e 10.\n");
        }
    } while (opcao != 0 && opcao != 11);

    adventure_table_down();
    inventory_table_down();
    item_table_down();

    return 0;
}