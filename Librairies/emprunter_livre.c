#include "emprunter_livre.h"

void ajouter_livre_emprunter(LIVRE livre_choisi){ //permet de rentrer un livre dans la base de données emprunter
  FILE *fichier2 = OpenDbFile("./Data/livres_emprunter.csv","a");
  //On entre les valeurs dans la bdd
  char ide[5];
  printf("Entrez l'id de l'emprunteur\n");
  getchar();
  fgets(ide,5,stdin);
  SuppCarriageReturn(ide);
  fprintf(fichier2,"%s,",ide);
  fprintf(fichier2, "%s,%s,%s,", livre_choisi.ISBN, livre_choisi.titre, livre_choisi.auteur);
  for(int i = 0; i < 3 ; i++){
      fprintf(fichier2,"%s,",livre_choisi.genre[i]);
  }
  time_t timestamp = time(NULL);
  struct tm *now = localtime(&timestamp);
  DATE date;
  PTR_DATE ptr_date = &date;
  date.y = now->tm_year + 1900;
  date.m = now->tm_mon + 1;
  date.d = now->tm_mday +15;
  CorrectTime(ptr_date);
  fprintf(fichier2,"%d-%02d-%02d\n",date.y,date.m,date.d);
  fclose(fichier2);
}

void supprimer_livre_emprunter(LIVRE rendre_livre){//permet de supprimer un livre de la base de données des livres empruntés
  int i_livres = nombre_livres("./Data/livres_emprunter.csv");
  LIVRE *livres = malloc(sizeof(LIVRE) * (i_livres + 1));
  char chaine_tmp[200];
  FILE *output_file = OpenDbFile("./Data/livres_emprunter.csv","r");
  int j = 0;
  for (int i = 0; i < i_livres; i++) {
    fgets(chaine_tmp, 200, output_file);
    char *lecteur_tmp = strtok(chaine_tmp, ",");
    char *ISBN_tmp = strtok(NULL, ",");
    char *titre_tmp = strtok(NULL, ",");
    char *auteur_tmp = strtok(NULL, ",");
    for (int k = 0 ; k < 3 ; k++){
      char *genre_tmp  = strtok(NULL, ",");
      strcpy(livres[j].genre[k], genre_tmp);
    }
    char *date_tmp = strtok(NULL, ",");
    
   
    if(strcmp(ISBN_tmp, rendre_livre.ISBN) != 0){
      strcpy(livres[j].ISBN, ISBN_tmp);
      strcpy(livres[j].titre, titre_tmp);
      strcpy(livres[j].auteur, auteur_tmp);
      strcpy(livres[j].date_retour, date_tmp);
      strcpy(livres[j].lecteur,lecteur_tmp);
      j++;
    }else{
      LIVRE livre_supp;
      strcpy(livre_supp.lecteur,lecteur_tmp );
      strcpy(livre_supp.ISBN, ISBN_tmp);
      strcpy(livre_supp.titre, titre_tmp);
      strcpy(livre_supp.auteur, auteur_tmp);
      strcpy(livre_supp.genre[0],livres[j].genre[0]);
      strcpy(livre_supp.genre[1],livres[j].genre[1]);
      strcpy(livre_supp.genre[2],livres[j].genre[2]);
      strcpy(livre_supp.date_retour, date_tmp);
    }
  }
  fclose(output_file);
  remove("./Data/livres_emprunter.csv");

  //on remet les livres sans celui que l'on a décidé de supprimer
  output_file = OpenDbFile("./Data/livres_emprunter.csv","w+");
  for(int i = 0; i < j; i++){
    fprintf(output_file, "%s,%s,%s,%s,",livres[i].lecteur, livres[i].ISBN, livres[i].titre, livres[i].auteur);
    for(int k = 0; k < 3 ; k++){
      fprintf(output_file,"%s,",livres[i].genre[k]);
    }
    fprintf(output_file,"%s\n",livres[i].date_retour);
  }
  fclose(output_file);
}


void ajouter_livre_rendu(LIVRE rendrelivre){// permet d'ajouter +1 à la quantité du livre dans la base de donnée des livres
  LIVRE livre_modif;
  strcpy(livre_modif.ISBN,rendrelivre.ISBN);
  strcpy(livre_modif.auteur,rendrelivre.auteur);
  strcpy(livre_modif.titre,rendrelivre.titre); 
  strcpy(livre_modif.genre[0],rendrelivre.genre[0]);
  strcpy(livre_modif.genre[1],rendrelivre.genre[1]);
  strcpy(livre_modif.genre[2],rendrelivre.genre[2]);
  int i_livres = nombre_livres("./Data/livres.csv");
  LIVRE *livres = malloc(sizeof(LIVRE) * (i_livres + 1));
  Get_livres(livres);
  for(int k = 0;k < i_livres ; k++){
    if(!strcmp(livres[k].ISBN,livre_modif.ISBN)){
      livre_modif.quantite = livres[k].quantite + 1;
    }
  }
  supprimer_livre(rendrelivre);
  FILE *fichier = fopen("./Data/livres.csv", "a");
  fprintf(fichier, "\n%s,%s,%s,", livre_modif.ISBN, livre_modif.titre, livre_modif.auteur);
  for(int i = 0; i < 3 ; i++){
      fprintf(fichier,"%s,",livre_modif.genre[i]);
  }
  fprintf(fichier, "%d", livre_modif.quantite);
  fclose(fichier);
}

void PrintLivresemprunter(LIVRE *livres,int nb_livres){// affiche le livre sélectionné
  system("clear");
  for(int i = 0; i < nb_livres; i++){
    printf("%d : %s,%s",i+1,livres[i].titre,livres[i].auteur); 
    for(int j = 0; j < 3; j++){
      if(strcmp(livres[i].genre[j],"NULL")){
        printf(",%s",livres[i].genre[j]); 
      }
    }
    printf("\n");
  }
}

void MenuRechercherLivreRestituer(char critere, LIVRE *livre){// menu permettant de rechercher le livre à restituer
  char rechercherendre[50];
  system("clear");
  printf("Recherche : ");
  scanf("%s",&rechercherendre);
  int nb_livres = nombre_livres("./Data/livres_emprunter.csv");
  LIVRE *livres = malloc(sizeof(LIVRE) * nb_livres);
  int i_livres = rechercher_livre_restituer(critere,rechercherendre,livres);
  PrintLivresemprunter(livres,i_livres);
  printf("##########\n");
  int resp;
  printf("Quel livre voulez vous choisir : ");
  scanf("%d",&resp);
  *livre = livres[resp-1];
}

int rechercher_livre_restituer(char critere, char *recherche, LIVRE *livre){//recherche le livre à restituer 
  int i_livres = nombre_livres("./Data/livres_emprunter.csv");
  LIVRE *livres = malloc(sizeof(LIVRE)* (i_livres + 1));
  Get_livres_emprunter(livres);
  int j = 0; //nombre de livres qui correspondent à la recherche
  for (int i = 0 ; i < i_livres; i++){
    switch(critere){
      case 'I': {
        if(!strcmp(livres[i].ISBN, recherche)) {
          livre[j] = livres[i];
          return j+1; 
        }
      }
      case 'T': {
        if(!strcmp(livres[i].titre, recherche)) {
          livre[j] = livres[i];
          return j+1;
        }
      }
      case 'A': { 
        if(!strcmp(livres[i].auteur, recherche)){
          livre[j] = livres[i];
          j++;
        }
      }
      case 'G':{
        for(int k = 0;k < 3;k++){
          if(!strcmp(livres[i].genre[k], recherche)){
            livre[j] = livres[i];
            j++;
            break;
          }
        }
        break;
      }
    }
  }
  return j;
}


void Get_livres_emprunter(LIVRE *livres) { //permet de prendre la donnée du livre emprunter
  int i_livres = nombre_livres("./Data/livres_emprunter.csv");
  char chaine_tmp[200];
  FILE *output_file = OpenDbFile("./Data/livres_emprunter.csv","r");
  for (int i = 0; i < i_livres; i++) {
    fgets(chaine_tmp, 200, output_file);
    char *lecteur_tmp = strtok(chaine_tmp, ",");
    char *ISBN_tmp = strtok(NULL, ",");
    char *titre_tmp = strtok(NULL, ",");
    char *auteur_tmp = strtok(NULL, ",");
    for (int j = 0 ; j < 3 ; j++){
      char *genre_tmp  = strtok(NULL, ",");
      strcpy(livres[i].genre[j], genre_tmp);
    }
    char *date_retour_tmp = strtok(NULL, ",");
    strcpy(livres[i].ISBN, ISBN_tmp);
    strcpy(livres[i].titre, titre_tmp);
    strcpy(livres[i].auteur, auteur_tmp);
    strcpy(livres[i].date_retour, date_retour_tmp);
    strcpy(livres[i].lecteur, lecteur_tmp);
  }
  fclose(output_file);
}

void menu_restituer_livre(){ //Permet de rendre un livre à la bibliothèque
  int resp;
  system("clear");
  printf("Comment souhaitez vous trouver le livre à restituer ?\n");
  printf("0: Par ISBN \n");
  printf("1: Par titre\n");
  printf("2: Par auteur\n");
  scanf("%d",&resp);
  LIVRE rendrelivre;
  LIVRE *ptr_rendrelivre = &rendrelivre;
  switch(resp){
    case 0 :
      MenuRechercherLivreRestituer('I',ptr_rendrelivre);
      supprimer_livre_emprunter(rendrelivre);
      ajouter_livre_rendu(rendrelivre);
      break;
    case 1 :
      MenuRechercherLivreRestituer('T',ptr_rendrelivre);
      supprimer_livre_emprunter(rendrelivre);
      ajouter_livre_rendu(rendrelivre);
      break;
    case 2 :
      MenuRechercherLivreRestituer('A',ptr_rendrelivre);
      supprimer_livre_emprunter(rendrelivre);
      ajouter_livre_rendu(rendrelivre);
      break;
    default:
      break;
  }
  
}

void soustraire_livre(LIVRE livreEmprunte){// Enlève 1 à la quantité de livre de la base de données
  LIVRE livre_modif;
  strcpy(livre_modif.ISBN,livreEmprunte.ISBN);
  strcpy(livre_modif.auteur,livreEmprunte.auteur);
  strcpy(livre_modif.titre,livreEmprunte.titre); 
  strcpy(livre_modif.genre[0],livreEmprunte.genre[0]);
  strcpy(livre_modif.genre[1],livreEmprunte.genre[1]);
  strcpy(livre_modif.genre[2],livreEmprunte.genre[2]);
  livre_modif.quantite = livreEmprunte.quantite-1; 
  supprimer_livre(livreEmprunte);
  FILE *fichier = OpenDbFile("./Data/livres.csv","a");
  fprintf(fichier, "\n%s,%s,%s,", livre_modif.ISBN, livre_modif.titre, livre_modif.auteur);
  for(int i = 0; i < 3 ; i++){
      fprintf(fichier,"%s,",livre_modif.genre[i]);
  }
  fprintf(fichier, "%d", livre_modif.quantite);
  fclose(fichier);
}

void menu_emprunter_livre(){//permet d'accéder au menu des emprunts de livre
  system("clear");;
  printf("0 : Rechercher un livre à emprunter\n");
  printf("1 : Rendre un livre\n");
  printf("2 : Livres non rendus\n");
  printf("3 : Revenir au menu principal\n");
  int resp;
  scanf("%d",&resp);
  switch(resp){
    case 0 : 
      menu_trouver_livre();
      break;
    case 1 :
      menu_restituer_livre();
      break;
    case 2 :
      PrintLivresNonRendus();
      break;
    default:
      break;
  }
}

void menu_trouver_livre(){/// permet de trouver un livre parmis la base de données des livres
  int resp;
  system("clear");;
  printf("0 : Par ISBN\n");
  printf("1 : Par auteur\n");
  printf("2 : Par titre\n");
  printf("3 : Annuler\n");
  scanf("%d",&resp);
  LIVRE livreEmprunte;
  LIVRE *livre_Emprunte= &livreEmprunte;
  switch(resp){
    case 0 :
      MenuRechercherLivre('I',livre_Emprunte);
      if(livre_Emprunte->quantite == 0){
        printf("Ce livre n'est plus disponible\nAppuyez sur la touche entrée pour continuer\n");
        char entree[10];
        getchar();
        fgets(entree,10,stdin);
      }else{
        ajouter_livre_emprunter(livreEmprunte);
        soustraire_livre(livreEmprunte);
      }
      break;
    case 1 :
      MenuRechercherLivre('A',livre_Emprunte);
      if(livre_Emprunte->quantite == 0){
        printf("Ce livre n'est plus disponible\nAppuyez sur la touche entrée pour continuer\n");
        char entree[10];
        getchar();
        fgets(entree,10,stdin);
      }else{
        ajouter_livre_emprunter(livreEmprunte);
        soustraire_livre(livreEmprunte);
      }
      break;
    case 2 :
      MenuRechercherLivre('T',livre_Emprunte);
      if(livre_Emprunte->quantite == 0){
        printf("Ce livre n'est plus disponible\nAppuyez sur la touche entrée pour continuer\n");
        char entree[10];
        getchar();
        fgets(entree,10,stdin);
      }else{
        ajouter_livre_emprunter(livreEmprunte);
        soustraire_livre(livreEmprunte);
      }
      break;
    default:
      break;
  }
}

void CorrectTime(PTR_DATE date){//permet d'ajuster la date si elle dépasse les critères d'une date
  if(date->d%2 == 0){
    if(date->d > 31){
      date->d = date->d - 31;
      date->m++;
    }
  }else{
    if(date->d > 30){
      date->d = date->d - 30;
      date->m++;
    }
  }
  if(date->m> 12){
    date->m = 1;
    date->y++;
  }
}

int CompDate(DATE date1,DATE date2){//permet de comparer deux date
  //date1>=date2 -> 0 else 1
  if(date1.y == date2.y){
    if(date1.m == date2.m){
        return date1.d < date2.d;
    }else{
      return date1.m  < date2.m;
    }
  }else{
    return date1.y  < date2.y;
  }
}

void PrintLivresNonRendus(){//affiche les livres non rendu quand ils ont dépassé la date limire
  system("clear");
  int i_livres = nombre_livres("./Data/livres_emprunter.csv");
  LIVRE *livres = malloc(sizeof(LIVRE)* (i_livres + 1));
  Get_livres_emprunter(livres);
  time_t timestamp = time(NULL);
  struct tm *now = localtime(&timestamp);
  DATE date_now;
  date_now.y = now->tm_year + 1900;
  date_now.m = now->tm_mon + 1;
  date_now.d = now->tm_mday;
  int j = 0;
  for(int i = 0; i < i_livres;i++){
    char str_date_retour[20];
    strcpy(str_date_retour,livres[i].date_retour);
    DATE date;
    char year[] = {str_date_retour[0],str_date_retour[1],str_date_retour[2],str_date_retour[3],'\0'};
    char month[] = {str_date_retour[5],str_date_retour[6],'\0'};
    char day[] = {str_date_retour[8],str_date_retour[9],'\0'};
    date.y = atoi(year);
    date.m = atoi(month);
    date.d = atoi(day);
    if(CompDate(date,date_now)){
        printf("%s,%s,%s,%s,%s\n",livres[i].lecteur,livres[i].ISBN,livres[i].auteur,livres[i].titre,livres[i].date_retour);
    j++;
    }
  }
  if(j == 0){
    printf("Pas de livres non rendus !\n");
  }
  printf("Appuyez sur la touche entrée pour continuer\n");
  char entree[10];
  getchar();
  fgets(entree,10,stdin);
} 

void PrintEmpruntLecteur(char *ID){// permet d'afficher les emprunts du lecteur
  system("clear");
  int i_livres = nombre_livres("./Data/livres_emprunter.csv");
  LIVRE *livres = malloc(sizeof(LIVRE)* (i_livres + 1));
  Get_livres_emprunter(livres);
  int j = 0;
  for(int i = 0; i < i_livres;i++){
    livres[i].date_retour[10] = '\0';
    if(!strcmp(ID,livres[i].lecteur)){
        printf("%s,%s,%s,%s\n",livres[i].ISBN,livres[i].auteur,livres[i].titre,livres[i].date_retour);
    j++;
    }
  }
  if(j == 0){
    printf("Pas de livres empruntés\n");
  }
  printf("Appuyez sur la touche entrée pour continuer\n");
  char entree[10];
  getchar();
  fgets(entree,10,stdin);
}