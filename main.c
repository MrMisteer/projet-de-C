#include <stdio.h>
#include "fichier.h"
int main() {

    MultiLevelList *myList = exemple_of_list();
    display_all_levels(*myList);

    int choice;
    do {
        display_menu();
        printf("Entrez votre choix : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // Rechercher un contact
                printf("Entrez les premières lettres du nom : ");
                find_contact(myList);
                break;
            }
            case 2: {
                // Afficher les rendez-vous d'un contact
                display_rdv_for_contact(*myList);
                break;
            }
            case 3: {
                // Créer un contact
                add_new_contact(myList);
                break;
            }
            case 4: {
                // Créer un rendez-vous pour un contact
                add_rdv_to_agenda(myList, create_rdv());
                break;
            }
            case 5: {
                // Supprimer un rendez-vous
                delete_rdv_from_agenda(myList);
                break;
            }
            case 6:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choice != 6);

    // Libérer la mémoire de la liste
    free_multi_level_list(myList);

    return 0;
}

