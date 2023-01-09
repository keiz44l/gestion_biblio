#ifndef CONNEXION_H
#define CONNEXION_H
#include "sha256.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_LOGIN 25

typedef struct utilisateur {
  char ID[10];
  char Login[TAILLE_LOGIN];
  char Mdp[140];
} UTILISATEUR, *PTR_UTILISATEUR;

void SHA256(BYTE *data);
void StockerUtilisateur(char role, char Login[], BYTE Mdp[]);
int connexion(char *Login, BYTE *Mdp);
int nombre_utilisateurs(char *fichier_utilisateurs);
void PrintAllUsers();
void Delete_utilisateur(UTILISATEUR utilisateur);
void ModifyPassword(UTILISATEUR utilisateur, BYTE NewMdp[]);

int Comp_Mdp(char *Mdp1, BYTE *Mdp2);
char *ConvertByteToChar(BYTE *byte);
void ByteToStringArray(BYTE *input, char *output);
void Get_utilisateurs(UTILISATEUR *utilisateurs);
void GetNewId(char role, char *NewID);
void DeleteFirstCharInChaine(char *chaine);
int SearchUser(char critere, char *recherche, PTR_UTILISATEUR utilisateur);
int bytelen(BYTE *byte);

#endif

