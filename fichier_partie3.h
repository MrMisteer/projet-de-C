//
// Created by Proventus on 05/12/2023.
//

#ifndef TEST_FICHIER_PARTIE3_H
#define TEST_FICHIER_PARTIE3_H

// Structure pour une date
typedef struct {
    int jour;
    int mois;
    int annee;
} Date;

// Structure pour une heure
typedef struct {
    int heure;
    int minute;
} Heure;

// Structure pour un rendez-vous
typedef struct RendezVous {
    Date date;
    Heure debut;
    Heure fin;
    char *objet;
    struct RendezVous *suivant; // Pointeur vers le rendez-vous suivant dans la liste
} RendezVous;

// Structure pour un contact
typedef struct {
    char *nom_prenom; // Utilisation de la chaîne 'nom_prenom'
} Contact;

// Structure pour un rendez-vous et un contact associé
typedef struct {
    Contact contact;
    RendezVous *rdv; // Pointeur vers la liste de rendez-vous associée
} Agenda;

// Structure pour une cellule de la liste à plusieurs niveaux
typedef struct Cell {
    Agenda *data; // Pointeur générique pour stocker un Agenda
    int level;  // Niveau de la cellule pour la liste à plusieurs niveaux
    struct Cell **next; // Tableau de pointeurs vers les niveaux suivants
} Cell;

// Structure pour la liste à plusieurs niveaux
typedef struct {
    int max_level;     // Niveau maximal de la liste
    Cell **heads;      // Tableau de pointeurs vers les têtes de chaque niveau
} MultiLevelList;

char *scanString(void);
char *scanString_objet(void);
void insert_sorted_cell(MultiLevelList *, Cell *);
void display_all_levels(MultiLevelList);
void display_cells_at_level(MultiLevelList , int );
void free_multi_level_list(MultiLevelList *);
Date input_date(const char *);
Heure input_heure(const char *);
void add_rdv_to_agenda(MultiLevelList *, RendezVous *);
RendezVous *create_rdv();
Cell *create_agenda_cell(char *);
MultiLevelList* create_multi_level_list();
void rearrange_levels(MultiLevelList *list);
void add_new_contact(MultiLevelList *list);
void display_rdv_for_contact(MultiLevelList list);
void display_rdv_list(RendezVous *);
int count_rdv(RendezVous *);
RendezVous *delete_rdv_at_index(RendezVous *, int);
void delete_rdv_from_agenda(MultiLevelList *);
void free_rdv_list(RendezVous *);
void save_list_to_file(MultiLevelList *, const char *);
void load_list_from_file(MultiLevelList *, const char *);
MultiLevelList* exemple_of_list();
void display_menu();
void find_contact(MultiLevelList *list);


#endif //TEST_FICHIER_PARTIE3_H
