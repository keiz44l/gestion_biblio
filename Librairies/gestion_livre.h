#ifndef GESTION_LIVRE_H
#define GESTION_LIVRE_H
#include <string.h>
#include "../main.h"
#include "historique.h"

void ajouter_livre_auto();
void ajouter_livre();
int rechercher_livre(char critere, char *recherche, LIVRE *livre);
void modifier_livre(LIVRE livre);
void supprimer_livre(LIVRE livre);
FILE *OpenDbFile(char* DbFile,char *method);
void Get_livres(LIVRE *livres);
int nombre_livres(char *fichier_livres);
void PrintLivres(LIVRE *livres,int nb_livres);
void PrintAllBooks();
void MenuGestionLivres();
void MenuRechercherLivre(char critere, LIVRE *livre);
void SuppCarriageReturn(char* chaine);
#endif



