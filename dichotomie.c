#include <stdio.h>
#include <stdlib.h>
#include "Cellule.h"
#include "dichotomie.h"

// Fonction de recherche 'classique' dans le niveau 0

int RechercheClassique(MultiLevelList list, int val){
    if (list.heads[0] !=NULL){
        Cell * valeur = list.heads[0];
        while ((valeur->next != NULL)&&(valeur->value <= val)){
            if (valeur->value == val)
                return 1;
            valeur = valeur->next;
        }
        return 0;
    }
}


int RechercheNiveau(MultiLevelList list, int val){
    if (list.heads[0] != NULL){
        Cell  * valeur = list.heads[list.max_level];
        Cell  * prev = valeur;
        for (int i = 0; i <= list.max_level; i++){

            while ((valeur != NULL)&&(valeur->value <= val)){
                if (valeur->value == val)
                    return 1;
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
    }
