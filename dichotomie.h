#include <stdio.h>
#include <stdlib.h>
#include "Cellule.h"
#define MAX_LEVEL 20 // Niveau maximum de la liste chaînée

#ifndef AGENDA_DICHOTOMIE_H
#define AGENDA_DICHOTOMIE_H

int RechercheClassique(MultiLevelList, int);
int RechercheNiveau(MultiLevelList, int);
MultiLevelList * CreationListeNiveau(int,int);
#endif //AGENDA_DICHOTOMIE_H
