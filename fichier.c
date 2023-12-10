//
// Created by Proventus on 05/12/2023.
//
// Structure pour stocker un contact
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fichier.h"
#include <ctype.h>



// Fonction pour la saisie d'une chaîne de caractères dynamique
char *scanString(void) {
    char buffer[100]; // Taille de buffer arbitraire, ajustez selon vos besoins
    scanf(" %99[^\n]", buffer);  // Lire jusqu'au caractère newline, en évitant les espaces initiaux

    // Convertir la chaîne en minuscules
    for (int i = 0; buffer[i] != '\0'; i++) {
        buffer[i] = tolower(buffer[i]);
        // Remplacer les espaces par des underscores
        if (buffer[i] == ' ') {
            buffer[i] = '_';
        }
    }

    // Nettoyer le tampon d'entrée
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    return strdup(buffer);
}

// Fonction pour créer une cellule pour un contact
Cell *create_agenda_cell(char *nom_prenom) {

    Cell *new_cell = (Cell *)malloc(sizeof(Cell));

    new_cell->data = (Agenda *)malloc(sizeof(Agenda));

    ((Agenda *)(new_cell->data))->contact.nom_prenom = strdup(nom_prenom);

    ((Agenda *)(new_cell->data))->rdv = NULL; // Initialiser la liste de rendez-vous à NULL
    new_cell->level = 0; // Niveau initialisé à 0

    new_cell->next = (Cell**)malloc(sizeof(Cell*) * (1));
    new_cell->next[0] = NULL;

    return new_cell;
}

MultiLevelList* create_multi_level_list() {

    MultiLevelList* new_list = (MultiLevelList*)malloc(sizeof(MultiLevelList));
    new_list->max_level = 3;

    // Allouer de l'espace pour le tableau dynamique de pointeurs heads
    new_list->heads = (Cell**)malloc(sizeof(Cell*) * (4));

    // Initialiser les pointeurs heads à NULL
    for (int i = 0; i <= 3; i++) {
        new_list->heads[i] = NULL;
    }

    return new_list;
}

// Fonction pour la saisie sécurisée d'une heure
Heure input_heure(const char *prompt) {
    Heure heure;
    do {
        printf("%s (hh mm) : ", prompt);
        scanf("%d %d", &heure.heure, &heure.minute);
        printf("\n");
    } while (heure.heure < 0 || heure.heure > 23 || heure.minute < 0 || heure.minute > 59);

    return heure;
}

// Fonction pour la saisie sécurisée d'une date
Date input_date(const char *prompt) {
    Date date;
    do {
        printf("%s (jj mm aaaa) : ", prompt);
        scanf("%d %d %d", &date.jour, &date.mois, &date.annee);
        printf("\n");
    } while (date.jour < 1 || date.jour > 31 || date.mois < 1 || date.mois > 12 || date.annee < 0);

    return date;
}
// Fonction pour créer un rendez-vous
RendezVous *create_rdv() {
    RendezVous *rdv = (RendezVous *)malloc(sizeof(RendezVous));
    if (rdv != NULL) {
        // Saisir la date
        rdv->date = input_date("Entrez la date du rendez-vous");

        // Saisir l'heure de début
        rdv->debut = input_heure("Entrez l'heure de debut du rendez-vous");

        // Saisir l'heure de fin
        do {
            rdv->fin = input_heure("Entrez l'heure de fin du rendez-vous");
        } while (rdv->fin.heure < rdv->debut.heure || (rdv->fin.heure == rdv->debut.heure && rdv->fin.minute <= rdv->debut.minute));

        // Saisir l'objet du rendez-vous
        printf("Entrez l'objet du rendez-vous : ");
        rdv->objet = scanString();

        rdv->suivant = NULL; // Initialiser le suivant à NULL
    }
    return rdv;
}

// Fonction pour ajouter un rendez-vous à la liste de rendez-vous d'un Agenda
void add_rdv_to_agenda(MultiLevelList *list, RendezVous *rdv) {
    if (list == NULL || rdv == NULL) {
        fprintf(stderr, "Erreur d'ajout du rendez-vous a l'agenda : liste ou rendez-vous invalide.\n");
        return;
    }

    // Demander à l'utilisateur de saisir un nouveau contact
    printf("Entrez le nom et le prenom du contact : ");
    char *nom_prenom = scanString();

    // Rechercher le contact dans la liste sur tous les niveaux
    Cell *current;
    int level = 3;
    current = list->heads[level];
    while (level >= 0 && current != NULL) {
        while (current != NULL && strcmp(nom_prenom, current->data->contact.nom_prenom) != 0) {
            current = current->next[level];
        }
        if (current != NULL && strcmp(nom_prenom, current->data->contact.nom_prenom) == 0) {
            level = -1;  // Terminer la boucle externe
        } else {
            level--;
            if (level >= 0) {
                current = list->heads[level];
            }
        }
    }

    if (current == NULL) {
        // Le contact n'est pas dans la liste, demander à l'utilisateur s'il veut l'ajouter
        printf("Le contact n'est pas dans la liste. Voulez-vous l'ajouter ? (o/n) : ");
        char response;
        scanf(" %c", &response);

        if (response == 'o' || response == 'O') {
            // Ajouter le nouveau contact dans la liste
            Cell *new_cell = create_agenda_cell(nom_prenom);
            insert_sorted_cell(list, new_cell);
            rearrange_levels(list);

            // Réaffecter la valeur de current pour le contact nouvellement ajouté
            current = new_cell;
        } else {
            // Libérer la mémoire du nom_prenom puis du rdv et quitter la fonction
            free(nom_prenom);
            free(rdv->objet);
            free(rdv);
            return;
        }
    }

    // Le contact a été trouvé ou ajouté, ajouter le rendez-vous à la liste de rendez-vous
    rdv->suivant = current->data->rdv;
    current->data->rdv = rdv;

    printf("Le rendez-vous a ete ajoute avec succes.\n");
}
// Fonction pour afficher les rendez-vous d'une cellule
void display_rdv_for_contact(MultiLevelList list) {
    // Saisir le nom et prénom du contact
    printf("Entrez le nom et le prenom du contact : ");
    char *nom_prenom = scanString();

    // Rechercher le contact dans la liste sur tous les niveaux
    Cell *current;
    int level = 3;
    current = list.heads[level];
    while (level >= 0) {
        while (current != NULL && strcmp(nom_prenom, current->data->contact.nom_prenom) != 0) {
            current = current->next[level];
        }
        if (current != NULL && strcmp(nom_prenom, current->data->contact.nom_prenom) == 0) {
            level = -1;
        } else {
            level--;
            current = list.heads[level];
        }
    }

    if (current == NULL) {
        printf("Le contact n'est pas dans la liste.\n");
    } else {
        // Afficher les rendez-vous du contact
        RendezVous *rdv = current->data->rdv;
        printf("Rendez-vous pour %s :\n", nom_prenom);
        while (rdv != NULL) {
            printf("- Date : %02d/%02d/%04d, Heure debut : %02d:%02d, Heure fin : %02d:%02d, Objet : %s\n",
                   rdv->date.jour, rdv->date.mois, rdv->date.annee,
                   rdv->debut.heure, rdv->debut.minute, rdv->fin.heure, rdv->fin.minute, rdv->objet);
            rdv = rdv->suivant;
        }
    }

    // Libérer la mémoire du nom_prenom
    free(nom_prenom);
}
void display_rdv_list(RendezVous *rdv) {
    while (rdv != NULL) {
        printf("[%02d/%02d/%04d %02d:%02d - %02d:%02d] %s\n",
               rdv->date.jour, rdv->date.mois, rdv->date.annee,
               rdv->debut.heure, rdv->debut.minute,
               rdv->fin.heure, rdv->fin.minute,
               rdv->objet);

        rdv = rdv->suivant;
    }
}
int count_rdv(RendezVous *rdv) {
    int count = 0;
    while (rdv != NULL) {
        count++;
        rdv = rdv->suivant;
    }
    return count;
}
RendezVous *delete_rdv_at_index(RendezVous *rdv, int index) {
    if (index == 1) {
        RendezVous *temp = rdv;
        rdv = rdv->suivant;
        free(temp->objet);
        free(temp);
    } else {
        RendezVous *current = rdv;
        for (int i = 1; i < index - 1 && current != NULL; i++) {
            current = current->suivant;
        }

        if (current != NULL && current->suivant != NULL) {
            RendezVous *temp = current->suivant;
            current->suivant = temp->suivant;
            free(temp->objet);
            free(temp);
        }
    }

    return rdv;
}
void delete_rdv_from_agenda(MultiLevelList *list) {
    if (list == NULL) {
        fprintf(stderr, "Erreur de suppression du rendez-vous : liste invalide.\n");
        return;
    }

    // Demander à l'utilisateur de saisir un nom et prénom
    printf("Entrez le nom et le prenom du contact : ");
    char *nom_prenom = scanString();

    // Rechercher le contact dans la liste sur tous les niveaux
    Cell *current;
    int level = 3;
    current = list->heads[level];
    while (level >= 0) {
        while (current != NULL && strcmp(nom_prenom, current->data->contact.nom_prenom) != 0) {
            current = current->next[level];
        }
        if (current != NULL && strcmp(nom_prenom, current->data->contact.nom_prenom) == 0) {
            level = -1;
        } else {
            level--;
            current = list->heads[level];
        }
    }

    if (current == NULL) {
        // Le contact n'est pas dans la liste
        printf("Le contact n'est pas dans la liste.\n");
        free(nom_prenom);
        return;
    }

    // Le contact a été trouvé, vérifier s'il a des rendez-vous
    if (current->data->rdv == NULL) {
        printf("Ce contact n'a pas de rendez-vous.\n");
        free(nom_prenom);
        return;
    }

    // Afficher les rendez-vous
    printf("Rendez-vous pour le contact %s :\n", nom_prenom);
    display_rdv_list(current->data->rdv);

    // Demander à l'utilisateur de choisir le rendez-vous à supprimer
    int rdv_count = count_rdv(current->data->rdv);
    if (rdv_count == 1) {
        // Il y a un seul rendez-vous, demander s'il veut le supprimer
        printf("Voulez-vous supprimer ce rendez-vous ? (o/n) : ");
        char response;
        scanf(" %c", &response);

        if (response == 'o' || response == 'O') {
            free_rdv_list(current->data->rdv);
            current->data->rdv = NULL;
            printf("Le rendez-vous a ete supprime avec succes.\n");
        }
    } else {
        // Il y a plusieurs rendez-vous, demander à l'utilisateur de choisir l'indice à supprimer
        int index;
        do {
            printf("Entrez l'indice du rendez-vous à supprimer (1-%d) : ", rdv_count);
            scanf("%d", &index);
        } while (index < 1 || index > rdv_count);

        // Supprimer le rendez-vous à l'indice choisi
        current->data->rdv = delete_rdv_at_index(current->data->rdv, index);

        printf("Le rendez-vous a ete supprime avec succès.\n");
    }

    free(nom_prenom);
}


// Fonction pour insérer une cellule uniquement au niveau 0
void insert_sorted_cell(MultiLevelList *list, Cell *new_cell) {
    if (list == NULL || new_cell == NULL) {
        printf("Erreur d'insertion dans la liste.\n");
        return;
    }

    Cell *current = list->heads[0];

    if (current == NULL) {
        list->heads[0] = new_cell;
    }
    else {
        Cell *prev =current;
        while (current != NULL && strcmp(new_cell->data->contact.nom_prenom, current->data->contact.nom_prenom) > 0)
        {
            prev = current;
            current = current->next[0];
        }

        // Insérer la nouvelle cellule à la position actuelle
        if(current==list->heads[0])
        {
            new_cell->next[0] = current;
            list->heads[0] = new_cell;
        }
        else
        {
            new_cell->next[0] = current;
            prev->next[0] = new_cell;
        }
    }
}

void rearrange_levels(MultiLevelList *list) {
    if (list == NULL) {
        printf("Erreur de rearrangement des niveaux : liste invalide.\n");
        return;
    }


    Cell *prev = list->heads[0];
    prev->level=3;
    Cell *current = prev->next[0];
    while (current != NULL) {

        int level = 0;
        // Niveau 3 : Première lettre différente
        if (current->data->contact.nom_prenom[0] != prev->data->contact.nom_prenom[0]) {
                level = 3;
        }
        // Niveau 2 : Deuxième lettre différente
        else if (current->data->contact.nom_prenom[1] != prev->data->contact.nom_prenom[1]) {
            level = 2;
        }
        // Niveau 1 : Troisième lettre différente
        else if (current->data->contact.nom_prenom[2] != prev->data->contact.nom_prenom[2]) {
            level = 1;
        }
        current->level = level;
        prev=current;
        current = current->next[0];

    }

    // Utilisez une nouvelle variable pour parcourir la liste sans affecter current
    Cell *update_current = list->heads[0];
    for (int i = 3; i > 0; i--) {
        list->heads[i] = update_current;
    }

    prev = update_current;
    update_current = update_current->next[0];

    for (int j = 3; j > 0; j--) {
        while (update_current != NULL) {
            if (update_current->level >= j) {
                prev->next[j] = update_current;
                prev = update_current;
            }
            update_current = update_current->next[0];
        }
        prev->next[j]=NULL;
        prev = list->heads[0];
        update_current = prev->next[0];
    }
}

void display_cells_at_level(MultiLevelList list, int level) {
    if (level < 0 || level > list.max_level) {
        printf("Niveau invalide. Doit être entre 0 et %d.\n", list.max_level);
        return;
    }

    printf("[list head_%d @-]-->", level);
    Cell* current = list.heads[level];

    while (current != NULL) {
        printf("[ %s|@-]-->", current->data->contact.nom_prenom);
        current = current->next[level];
    }

    printf("NULL\n");
}
void display_all_levels(MultiLevelList list) {
    for (int level = 0; level <= list.max_level; level++) {
        display_cells_at_level(list, level);
    }
}

void add_new_contact(MultiLevelList *list) {
    printf("Entrez le nom et prenom du nouveau contact : ");
    char *nom_prenom = scanString();

    // Créer une nouvelle cellule pour le contact
    Cell *new_cell = create_agenda_cell(nom_prenom);

    // Insérer la cellule dans la liste
    insert_sorted_cell(list, new_cell);

    // Réarranger les niveaux de la liste
    rearrange_levels(list);

    printf("Le nouveau contact a ete ajoute avec succes.\n");
    display_all_levels(*list); //afficher la liste après modification

    // Libérer la mémoire allouée
    free(nom_prenom);
}

// Fonction pour libérer la mémoire de la liste
void free_multi_level_list(MultiLevelList *list) {
    for (int level = 0; level <= list->max_level; level++) {
        Cell *current = list->heads[level];
        while (current != NULL) {
            Cell *temp = current;
            current = current->next[level];
            free(temp->data);
            free(temp->next);
            free(temp);
        }
    }
    free(list->heads);
    free(list);
}
void free_rdv_list(RendezVous *rdv) {
    while (rdv != NULL) {
        RendezVous *temp = rdv;
        rdv = rdv->suivant;
        free(temp->objet);
        free(temp);
    }
}

void save_list_to_file(MultiLevelList *list, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s en ecriture.\n", filename);
        return;
    }

    // Parcourir la liste au niveau 0 et écrire les données dans le fichier
    Cell *current = list->heads[0];
    while (current != NULL) {
        fprintf(file, "%s\n", current->data->contact.nom_prenom);
        current = current->next[0];

        // Écrire les rendez-vous
        RendezVous *rdv = current->data->rdv;
        while (rdv != NULL) {
            fprintf(file, "\t%02d/%02d/%04d %02d:%02d-%02d:%02d %s",
                    rdv->date.jour, rdv->date.mois, rdv->date.annee,
                    rdv->debut.heure, rdv->debut.minute,
                    rdv->fin.heure, rdv->fin.minute,
                    rdv->objet);
            rdv = rdv->suivant;
        }

        fprintf(file, "\n");
        current = current->next[0];
    }
    fclose(file);
}

void load_list_from_file(MultiLevelList *list, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s en lecture.\n", filename);
        return;
    }

    // Lire les données du fichier et insérer les cellules dans la liste
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Découper la ligne en noms de contact et rendez-vous
        char *token = strtok(buffer, "\t");
        while (token != NULL) {
            // Insérer la cellule dans la liste
            Cell *new_cell = create_agenda_cell(token);
            insert_sorted_cell(list, new_cell);

            // Passer au prochain token
            token = strtok(NULL, "\t");
        }

        rearrange_levels(list); // Réorganiser les niveaux après chaque insertion
    }

    fclose(file);
}
MultiLevelList* exemple_of_list() {
    MultiLevelList *new_list = create_multi_level_list();
    // Insérer des contacts et des rendez-vous
    insert_sorted_cell(new_list, create_agenda_cell("gallouin"));
    insert_sorted_cell(new_list, create_agenda_cell("flamel"));
    insert_sorted_cell(new_list, create_agenda_cell("garnier"));
    insert_sorted_cell(new_list, create_agenda_cell("humbert"));
    insert_sorted_cell(new_list, create_agenda_cell("guetta"));
    insert_sorted_cell(new_list, create_agenda_cell("grandin"));
    insert_sorted_cell(new_list, create_agenda_cell("gartner"));
    insert_sorted_cell(new_list, create_agenda_cell("gruss"));
    rearrange_levels(new_list);
    return new_list;
}
// Fonction pour afficher le menu
void display_menu() {
    printf("\nMenu :\n");
    printf("1. Rechercher un contact\n");
    printf("2. Afficher les rendez-vous d'un contact\n");
    printf("3. Creer un contact\n");
    printf("4. Creer un rendez-vous pour un contact\n");
    printf("5. Supprimer un rendez-vous\n");
    printf("6. Quitter\n");
}
void find_contact(MultiLevelList *list){
    // Demander à l'utilisateur de saisir un nom et prénom
    printf("Entrez le nom et le prenom du contact : ");
    char *nom_prenom = scanString();

    // Rechercher le contact dans la liste sur tous les niveaux
    Cell *current;
    int level = 3;
    current = list->heads[level];
    while (level >= 0) {
        while (current != NULL && strcmp(nom_prenom, current->data->contact.nom_prenom) != 0) {
            current = current->next[level];
        }
        if (current != NULL && strcmp(nom_prenom, current->data->contact.nom_prenom) == 0) {
            level = -1;
        } else {
            level--;
            current = list->heads[level];
        }
    }

    if (current == NULL) {
        printf("Le contact n'est pas dans la liste.\n");
    } else {
        printf("Le contact %s est dans la liste.\n",current->data->contact.nom_prenom);
    }
}