#ifndef HISTORIQUE_H
#define HISTORIQUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../main.h"

#define ConnexionHistory "./Data/ConnexionHistory.csv"
#define BookHistory "./Data/BookHistory.csv"

void AddLogInToHistory(char* ID);
void AddBookHistory(LIVRE book,char* action);
FILE *OpenDbFileConnexionHistory(char *method);
FILE *OpenDbFileBookHistory(char *method);
void PrintLoginHistory();
void PrintBookHistory();
void menu_historique();
#endif