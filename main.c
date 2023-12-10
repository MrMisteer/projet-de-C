#include <stdio.h>
#include <stdlib.h>
#include "Cellule.h"
#include "dichotomie.h"
#include "timer.h"

int main() {
    //initialisation de toutes les variables
    int max_level = 16; // Niveau maximal de la liste à plusieurs niveaux
    int nombreElement = 65536;
    srand((time(NULL)));  //seed pour avoir des nombres aléatoires

    MultiLevelList* new_list = create_multi_level_list(max_level);  //création de la liste

    //on va ouvrir un fichier texte pour y mettre les résultats du temps mis pour la
    //recherche au niveau 0 et au sur tous les niveaux

    FILE *log_file = fopen("log.txt","w");
    char format[] = "%d\t%s\t%s\n" ;
    int level;
    char *time_lvl0;
    char *time_all_levels;

    //on remplit une liste
    new_list = CreationListeNiveau(max_level,nombreElement);

    //on test le temps mis par le recherche au niveau 0 10 000 fois
    printf("Le temps mis pour la recherche classique est :\n");
    startTimer();
    for (int i = 0; i<10000;i++){
        RechercheClassique(*new_list,rand());
    }
    displayTime();

    stopTimer();


    time_lvl0 = getTimeAsString(); // fonction du module timer

    //on test le temps mis par la recherche sur tous les niveaux 10 000 fois
    printf("Le temps mis pour la recherche a plusieurs niveaux est :\n");
    startTimer();
    for(int j = 0;j<10000;j++) {
        RechercheNiveau(*new_list,rand());
    }
    displayTime();

    stopTimer();


    time_all_levels = getTimeAsString();

    fprintf(log_file,format,level,time_lvl0, time_all_levels);//on stock les temps mis

    fclose(log_file);

    return 0;
}




