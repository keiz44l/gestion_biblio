#include "aide.h"


void MenuAideBase(){
  int resp;
  system("clear");
  printf("0 : Aide connexion\n");
  printf("1 : Retour au menu de connexion\n");
  scanf("%d", &resp);
  switch(resp){
    case 0:
      AideConnexion();
      break;
    default:
      break;
  }
  
}

void MenuAideAdmin(){
  int resp;
  system("clear");
  printf("0 : Aide ajout de livre\n");
  printf("1 : Aide modifier livre\n");
  printf("2 : Aide suppression de livre\n");
  printf("3 : Aide emprunt de livre\n");
  printf("4 : Retour au menu principal\n");
  scanf("%d",&resp);
  switch(resp){
    case 0 :
      AideAjout();
      break;
    case 1 :
      AideModification();
      break;
    case 2 :
      AideSuppression();
      break;
    case 3 : 
      AideEmprunt();
      break;
    case 4:
      break;
    default:
      return;
  }
}

void AideConnexion(){
  int resp;
  system("clear");
  printf("Pour vous connecter, assurez-vous d'avoir un compte au préalable.\n Si ce n'est pas le cas, merci de demander à un administrateur.\n Un compte lecteur ne vous permettra que d'avoir accès à la liste des livres, tandis qu'un compte utilisateur vous permettra d'emprunter un ou plusieurs livres.\n");
  printf("##############\n");
  printf("0 : Retourner au menu de connexion\n");
  printf("1 : Retourner au menu d'aide\n");
  scanf("%d",&resp);
  switch(resp){
    case 1 :
      MenuAideBase();
      break;
    default:
      break;
  }
}

void AideAjout(){
  int resp;
  system("clear");
  printf("Vous pouvez ajouter un livre de multiples façons.\n Si vous connaissez son ISBN (Numéro international normalisé du livre), il est possible de l'ajouter automatiquement en rentrant celui-ci.\n Cependant, si vous souhaitez ajouter manuellement un livre, vous pouvez également le faire.\n pour cela, veillez à avoir son ISBN, son titre, son auteur, son ou ses genres (jusque 3), ainsi que la quantité que vous souhaitez ajouter.\n");
  printf("##############\n");
  printf("0 : Retourner au menu principal\n");
  printf("1 : retourner au menu d'aide\n");
  scanf("%d",&resp);
  switch(resp){
    case 1 :
      MenuAideAdmin();
      break;
    default:
      break;
  }
  
}

void AideSuppression(){
  int resp;
  system("clear");
  printf("Pour supprimer un livre, vous pouvez d'abord le sélectionner en recherchant selon les différents critères :\n -Par ISBN\n -Par titre\n -Par auteur\n -Par genre(s)\n La suppression se fera automatiquement après la sélection du livre.\n");
  printf("##############\n");
  printf("0 : Retourner au menu principal\n");
  printf("1 : retourner au menu d'aide\n");
  scanf("%d",&resp);
  switch(resp){
    case 1 :
      MenuAideAdmin();
      break;
    default:
      break;
  }
}

void AideModification(){
  int resp;
  system("clear");
  printf("Pour modifier un livre, vous pouvez d'abord le sélectionner en recherchant selon les différents critères :\n -Par ISBN\n -Par titre\n -Par auteur\n -Par genre(s)\n Ensuite, les différentes possibilités de changement vous seront données, permettant de modifier une catégorie contenant une erreur par exemple, ou bien d'augmenter la quantité, ou la réduire pour une quelconque raison.\n");
  printf("##############\n");
  printf("0 : Retourner au menu principal\n");
  printf("1 : retourner au menu d'aide\n");
  scanf("%d",&resp);
  switch(resp){
    case 1 :
      MenuAideAdmin();
      break;
    default:
      break;
  }
  
}

void AideEmprunt(){
  int resp;
  system("clear");
  printf("Pour emprunter un livre, vous pouvez d'abord le sélectionner en recherchant selon les différents critères :\n -Par ISBN\n -Par titre\n -Par auteur\n -Par genre(s)\n Ensuite, l'emprunt se fera automatiquement, vous donnant un délai de quinze jours pour le restituer à la bibliothèque.\n");
  printf("##############\n");
  printf("0 : Retourner au menu principal\n");
  printf("1 : retourner au menu d'aide\n");
  scanf("%d",&resp);
  switch(resp){
    case 1 :
      MenuAideAdmin();
      break;
    default:
      break;
  }
}