#include <stdio.h>
#include <stdlib.h>
#include "fichier_partie1.h"
#define MAX_LEVEL 5 // Niveau maximum de la liste chaînée


// Fonction pour créer une nouvelle cellule
Cell* create_cell(int value, int level) {
    if (level < 0 || level > MAX_LEVEL) {
        printf("Niveau invalide. Doit être entre 0 et %d.\n", MAX_LEVEL);
        return NULL;
    }

    Cell* new_cell = (Cell*)malloc(sizeof(Cell));
    new_cell->value = value;
    new_cell->level = level;

    // Allouer de l'espace pour le tableau dynamique de pointeurs next
    new_cell->next = (Cell**)malloc(sizeof(Cell*) * (level + 1));

    // Initialiser les pointeurs next à NULL
    for (int i = 0; i <= level; i++) {
        new_cell->next[i] = NULL;
    }

    return new_cell;
}


// Fonction pour libérer une cellule
void free_cell(Cell* cell) {
    free(cell->next);
    free(cell);
}


MultiLevelList* create_multi_level_list(int max_level) {
    if (max_level < 0 || max_level > MAX_LEVEL) {
        printf("Niveau maximal invalide. Doit être entre 0 et %d.\n", MAX_LEVEL);
        return NULL;
    }
    MultiLevelList* new_list = (MultiLevelList*)malloc(sizeof(MultiLevelList));
    new_list->max_level = max_level;

    // Allouer de l'espace pour le tableau dynamique de pointeurs heads
    new_list->heads = (Cell**)malloc(sizeof(Cell*) * (max_level + 1));

    // Initialiser les pointeurs heads à NULL
    for (int i = 0; i <= max_level; i++) {
        new_list->heads[i] = NULL;
    }

    return new_list;
}


// Fonction pour libérer la liste à plusieurs niveaux
void free_multi_level_list(MultiLevelList* list) {

    for (int i = 0; i <= list->max_level; i++) {
        Cell *current = list->heads[i];
        while (current != NULL) {
            Cell *temp = current;
            current = current->next[i];
            free_cell(temp);
        }
    }
    free(list->heads);
    free(list);
}


// Fonction pour insérer une cellule à plusieurs niveaux en tête de liste
void insert_cell_in_head_list(MultiLevelList* list, Cell* new_cell, int level) {

    new_cell->next[level] = list->heads[level];
    list->heads[level] = new_cell;
}



void display_cells_at_level(MultiLevelList list, int level) {
    if (level < 0 || level > list.max_level) {
        printf("Niveau invalide. Doit être entre 0 et %d.\n", list.max_level);
        return;
    }

    printf("[list head_%d @-]-->", level);
    Cell* current = list.heads[level];

    while (current != NULL) {
        printf("[ %d|@-]-->", current->value);
        current = current->next[level];
    }

    printf("NULL\n");
}


void display_all_levels(MultiLevelList list) {
    for (int level = 0; level <= list.max_level; level++) {
        display_cells_at_level(list, level);
    }
}



void insert_sorted_cell(MultiLevelList* list, Cell* new_cell) {

    if (new_cell->level > list->max_level) {
        printf("Niveau de la cellule superieur au niveau maximal de la liste.\n");
        return;
    }

    // Insérer la nouvelle cellule à chaque niveau de manière triée
    for (int level = new_cell->level; level >= 0; level--) {
        Cell* current = list->heads[level];
        Cell* prev = NULL;

        while (current != NULL && current->value < new_cell->value) {
            prev = current;
            current = current->next[level];
        }

        // Insérer la nouvelle cellule
        if (prev == NULL) {
            // Insérer en tête
            insert_cell_in_head_list(list, new_cell, level);
        } else {
            new_cell->next[level] = prev->next[level];
            prev->next[level] = new_cell;
        }
    }
}





