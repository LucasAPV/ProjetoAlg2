#include <stdio.h>

void create_divider(int menu_name_length) {
    printf("*");
    for (int i = 0; i < menu_name_length + 16; i++) {
        printf("=");
    }
    printf("*");
    printf("\n");
}

void create_menu_name(char *menu_name, int menu_name_length) {

    create_divider(menu_name_length);
    printf("\t%s\t\n", menu_name);
    create_divider(menu_name_length);

}

void create_interface(char *menu_name, char **options, int num_options, int menu_name_length) {
    create_menu_name(menu_name, menu_name_length);

    for (int i = 0; i < num_options; i++) {
        printf("%d) %s\n", i + 1, options[i]);
    }
    create_divider(menu_name_length);
}