#include <stdio.h>
#include <stdlib.h>
#include "fichier_partie1.h"

int main() {
    int max_level = 3; // Niveau maximal de la liste à plusieurs niveaux

    MultiLevelList* new_list = create_multi_level_list(max_level);

    if (new_list != NULL) {
        printf("Liste a plusieurs niveaux creee avec succès : max_level = %d\n", new_list->max_level);


        // Insérer des cellules triées par ordre croissant
        insert_sorted_cell(new_list, create_cell(18, 0));
        insert_sorted_cell(new_list, create_cell(18, 1));
        insert_sorted_cell(new_list, create_cell(3, 3));
        insert_sorted_cell(new_list, create_cell(32, 2));
        insert_sorted_cell(new_list, create_cell(56, 3));
        insert_sorted_cell(new_list, create_cell(9, 2));

        // Afficher tous les niveaux de la liste
        display_all_levels(*new_list);

        // Libérer la liste
        free_multi_level_list(new_list);
    }

    return 0;
}