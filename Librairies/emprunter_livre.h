#ifndef EMPRUNTER_LIVRE_H
#define EMPRUNTER_LIVRE_H
#include <string.h>
#include "../main.h"
#include "gestion_livre.h"

typedef struct date{
  int y;
  int m;
  int d;
}DATE,*PTR_DATE;

void menu_emprunter_livre();
void menu_trouver_livre();
void ajouter_livre_emprunter(LIVRE livre_choisi );
int rechercher(char critere, char *recherche, LIVRE *liste_livres);
void CorrectTime(DATE* date);
void soustraire_livre(LIVRE livreEmprunte);
int rechercher_livre_restituer(char critere, char *recherche, LIVRE *livre);
void Get_livres_emprunter(LIVRE *livres);
void PrintLivresNonRendus();
int CompDate(DATE date1,DATE date2);
void supprimer_livre_emprunter(LIVRE rendre_livre);
void PrintEmpruntLecteur(char *ID);

#endif