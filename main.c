#include <stdio.h>
#include <stdlib.h>
#include "interface/adventure_interface.h" 
#include "adventure_table.h"
#include "inventory_table.h"
#include "item_table.h"

void exibir_menu() {
    printf("\n==================================\n");
    printf("        MENU DE AVENTURAS         \n");
    printf("==================================\n");
    printf("1 - Cadastrar personagem\n");
    printf("2 - Consultar personagem por ID\n");
    printf("3 - Alterar personagem\n");
    printf("4 - Remover personagem\n");
    printf("5 - Listar personagens\n");
    printf("6 - Administrar inventario\n");
    printf("7 - Consultar equipamentos\n");
    printf("8 - Equipar item\n");
    printf("9 - Desequipar item\n");
    printf("10 - Exibir atributos totais\n");
    printf("0 - Encerrar\n");
    printf("==================================\n");
    printf("Escolha uma opcao: ");
}

int main() {
    int opcao;

    // INICIALIZA O BANCO DE DADOS (Ativa as tabelas na memória)
    adventure_table_up();
    inventory_table_up();
    item_table_up();

    do {
        exibir_menu();
        
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
            case 0:
                printf("\nA encerrar o sistema. Ate logo!\n");
                break;
            default:
                printf("\n[Erro] Opcao invalida! Escolha um numero entre 0 e 10.\n");
        }
    } while (opcao != 0);

    adventure_table_down();
    inventory_table_down();
    item_table_down();

    return 0;
}