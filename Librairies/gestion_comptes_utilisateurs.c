#include "gestion_comptes_utilisateurs.h"

void menu_gestion_comptes(){
  int resp;
  system("clear");
  printf("0 : Créer un compte\n");
  printf("1 : Supprimer un compte\n");
  printf("2 : Modifier le mot de passe d'un utilisateur\n");
  printf("3 : Liste des comptes\n");
  printf("4 : Retour au menu principal\n");
  scanf("%d",&resp);
  switch(resp){
    case 0 :
      menu_creer_compte();
      break;
    case 1 :
      menu_supprimer_compte();
      break;
    case 2 :
      menu_modifier_mdp();
      break;
    case 3 :
      PrintAllUsers();
      break;
    default:
      return;
  }
}

void menu_creer_compte(){
  int resp;
  system("clear");
  printf("0 : Créer un compte administrateur\n");
  printf("1 : Créer un compte lecteur\n");
  printf("2 : retour au menu précedent\n");
  scanf("%d",&resp);
  char role;
  switch(resp){
    case 0 :
      role = 'A';
      break;
    case 1 :
      role = 'L';
      break;
    default:
      return;
  }
  char Login[TAILLE_LOGIN];
  BYTE Mdp[50];
  printf("Login : ");
  scanf("%s",&Login);
  printf("Mdp : ");
  scanf("%s",&Mdp);
  StockerUtilisateur(role,Login,Mdp);
}

void menu_supprimer_compte(){
  int resp;
  system("clear");
  printf("0 : Supprimer à l'aide de l'ID\n");
  printf("1 : Supprimer à l'aide du login\n");
  printf("2 : retour au menu précedent\n");
  scanf("%d",&resp);
  UTILISATEUR utilisateur;
  switch(resp){
    case 0 :;
      char ID[5];
      printf("ID de l'utilisateur a supprimer : ");
      scanf("%s",&ID);
      SearchUser('I',ID,&utilisateur);
      break;
    case 1 :;
      char Login[TAILLE_LOGIN];
      printf("Login de l'utilisateur a supprimer : ");
      scanf("%s",&Login);
      SearchUser('L',Login,&utilisateur);
      break;
    default:
      return;
  }
  Delete_utilisateur(utilisateur);
}

void menu_modifier_mdp(){
  int resp;
  system("clear");
  printf("0 : Modifier à l'aide de l'ID\n");
  printf("1 : Modifier à l'aide du login\n");
  printf("2 : retour au menu précedent\n");
  scanf("%d",&resp);
  UTILISATEUR utilisateur;
  switch(resp){
    case 0 :;
      char ID[5];
      printf("ID de l'utilisateur a modifier : ");
      scanf("%s",&ID);
      SearchUser('I',ID,&utilisateur);
      break;
    case 1 :;
      char Login[TAILLE_LOGIN];
      printf("Login de l'utilisateur a modifier : ");
      scanf("%s",&Login);
      SearchUser('L',Login,&utilisateur);
      break;
    default:
      return;
  }
  BYTE Mdp[100];
  printf("Nouveau mdp : ");
  scanf("%s",&Mdp);
  ModifyPassword(utilisateur, Mdp);
}