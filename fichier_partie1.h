#include <stdio.h>
#include <stdlib.h>

#ifndef AGENDA_FICHIER_H
#define AGENDA_FICHIER_H

// Structure de la cellule
typedef struct Cell {
    int value;
    int level;
    struct Cell** next;
} Cell;

// Structure de la liste à plusieurs niveaux
typedef struct MultiLevelList {
    int max_level;
    struct Cell** heads;
} MultiLevelList;


Cell* create_cell(int, int);
void free_cell(Cell* cell);

MultiLevelList* create_multi_level_list(int);
void free_multi_level_list(MultiLevelList*);
void insert_cell_in_head_list(MultiLevelList* , Cell*, int);
void display_cells_at_level(MultiLevelList list, int level);
void display_all_levels(MultiLevelList);
void insert_sorted_cell(MultiLevelList*, Cell*);


#endif //AGENDA_FICHIER_H
