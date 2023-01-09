#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include "Librairies/connexion.h"

typedef struct livre{
  char ISBN[13];
  char titre[100];
  char auteur[30];
  char genre[3][20]; 
  int quantite;
  char date_retour[11]; //07/04/2022
  char lecteur[5];
}LIVRE;

void menu_principal(char *ID);

#include "Librairies/historique.h"
#include "Librairies/gestion_livre.h"
#include "Librairies/emprunter_livre.h"
#include "Librairies/gestion_comptes_utilisateurs.h"
#include "Librairies/aide.h"
#endif
