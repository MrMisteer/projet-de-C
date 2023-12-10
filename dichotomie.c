#include <stdio.h>
#include <stdlib.h>
#include "Cellule.h"
#include "dichotomie.h"
#include "timer.h"

// Fonction de recherche 'classique' dans le niveau 0

int RechercheClassique(MultiLevelList list, int val){
    Cell * valeur = list.heads[0];

    while ((valeur != NULL)&&(valeur->value <= val)){
        if (valeur->value == val) {

            return 1;
        }
        valeur = valeur->next[0];
    }

    return 0;
}

//Fonction pour faire la recherche dans tous les niveaux de la liste

int RechercheNiveau(MultiLevelList list, int val){

    Cell  * valeur = list.heads[list.max_level];
    Cell  * prev = valeur;
    for (int i = 0; i <= list.max_level; i++){
        while ((valeur != NULL)&&(valeur->value <= val)){

            if (valeur->value == val) {
                return 1;
            }
            prev = valeur;
            valeur = valeur ->next[list.max_level-i];
        }
        if(prev->value < val){

            valeur = list.heads[list.max_level-i-1];
            prev = valeur;
        }
        else{

            valeur = valeur->next[list.max_level-i-1];
            prev = valeur;
        }
    }
    return 0;
}

//Fonction pour pouvoir remplir une liste de "max_level" niveaux. Il doit y avoir a plus 2^maxlevel élément dans la liste
MultiLevelList * CreationListeNiveau(int max_level, int nombreElem){
    if (max_level < 0 || max_level > MAX_LEVEL) {
        printf("Niveau maximal invalide. Doit être entre 0 et %d.\n", MAX_LEVEL);
        return NULL;
    }
    MultiLevelList* list = create_multi_level_list(max_level);
    int *levels = (int*)calloc(nombreElem,sizeof(int));
    int LePas = 2;
    while(LePas<nombreElem){
        for(int i = -1;i<nombreElem;i+=LePas){
            levels[i] +=1;
        }
        LePas *=2;
    }

    list->max_level = max_level-1;
    for(int i = 0;i<nombreElem;i++){
        insert_sorted_cell(list, create_cell(i, levels[i]));
    }
    return list;
    }

