#include "main.h"

int main(){
  system("clear");
  printf("0 : Quitter l'application\n");
  printf("1 : Se connecter\n");
  printf("2 : Menu aide\n");
  int resp;
  scanf("%d",&resp);
  switch (resp){
    case 0 : 
      exit(EXIT_SUCCESS); 
      break;
    case 1 :;
      char Login[TAILLE_LOGIN];
      BYTE Mdp[50];
      printf("Login : ");
      scanf("%s",&Login);
      printf("Mot de passe : ");
      scanf("%s",&Mdp);
      if(connexion(Login,Mdp)){
        UTILISATEUR utilisateur;
        SearchUser('L', Login,&utilisateur);
        AddLogInToHistory(utilisateur.ID);
        printf("Connecté\n");
        menu_principal(utilisateur.ID);
      }else{
        printf("Login ou mot de passe incorrect!\n");
        main();
      }; 
      break;
    case 2 :
      MenuAideBase();
      main();
      break;
    default :
      main();
  }
  return 0;
}

void menu_principal(char *ID){
  system("clear");
  printf("0 : Quitter l'application\n");
  if(ID[0] == 'A'){
    printf("1 : Gestion des livres\n");
    printf("2 : Emprunter un livre\n");
    printf("3 : Gestion des comptes\n");
    printf("4 : Historique\n");
    printf("5 : Menu aide\n");
  }else{
    printf("1 : Liste des livres\n");
    printf("2 : Listes livres empruntés\n");
  }
  int resp;
  scanf("%d",&resp);
  switch(resp){
    case 0 : 
      exit(EXIT_SUCCESS); 
      break;
    case 1 :
      if(ID[0] == 'A'){
        MenuGestionLivres();
      }else{
        PrintAllBooks();
      }
      break;
    case 2:
      if(ID[0] == 'A'){
        menu_emprunter_livre();
      }else{
        PrintEmpruntLecteur(ID);
      }
      break;
    case 3 :
      if(ID[0] == 'A'){
        menu_gestion_comptes();
      }
      break;
    case 4 :
      if(ID[0] == 'A'){
        menu_historique();
      }
      break;
    case 5 : 
      if(ID[0] == 'A'){
        MenuAideAdmin();
      }
      break;
    default:
      break;
  }
  menu_principal(ID);
}


  