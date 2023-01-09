#include "gestion_livre.h"

void ajouter_livre_auto(){ //fonction qui lance le programme python
  system("chmod +x -v ajout_livre.py"); //on lance en mode execution
  const char *commande = "./ajout_livre.py";
  int cr = system(commande);
  if ( cr != 0 ) {
    fprintf(stderr, "Impossible de lancer la commande : %s\n", commande );
    }
}

void SuppCarriageReturn(char* chaine){ //supprime le retour chariot pour une meilleure lisibilité dans le CSV 
  for(int i = 0; i < strlen(chaine);i++ ){
    if(chaine[i] == '\n'){
      chaine[i] = '\0';
    }
  }
}

FILE *OpenDbFile(char* DbFile,char *method) { //Méthode d'ouverture d'un fichier voulu 
  FILE *input_file = fopen(DbFile, method);
  if (!input_file) {
    printf("FOPEN ERROR");
    exit(EXIT_FAILURE);
  }
  return input_file;
}

int nombre_livres(char *fichier_livres) { //Retourne le nombre de livres présents dans la bdd de livres.
  FILE *output_file = OpenDbFile(fichier_livres,"r");
  int nombre_lignes = 0;
  int caractereActuel = 0;
  do {
    caractereActuel = fgetc(output_file);
    if (caractereActuel == '\n') { //On est passé à la ligne, donc on a un nouveau livre
      nombre_lignes++;
    }
  } while (caractereActuel != EOF);
  fclose(output_file);
  return nombre_lignes;
}

void Get_livres(LIVRE *livres) {//Permet de récupérer toutes les données de la bdd de livres.
  int i_livres = nombre_livres("./Data/livres.csv");
  char chaine_tmp[200];
  FILE *output_file = OpenDbFile("./Data/livres.csv","r");
  fgets(chaine_tmp, 200, output_file); //enlève la première ligne de la recherche
  for (int i = 0; i < i_livres; i++) {//on parcourt chaque livre et on les stocke dans notre pointeur de livres
    fgets(chaine_tmp, 200, output_file);
    char *ISBN_tmp = strtok(chaine_tmp, ",");
    char *titre_tmp = strtok(NULL, ",");
    char *auteur_tmp = strtok(NULL, ",");
    for (int j = 0 ; j < 3 ; j++){
      char *genre_tmp  = strtok(NULL, ",");
      strcpy(livres[i].genre[j], genre_tmp);
    }
    int quantite_tmp = atoi(strtok(NULL, ",")); //fonction de str à int 
    strcpy(livres[i].ISBN, ISBN_tmp); //on copie les données du livre courant dans la liste de livres
    strcpy(livres[i].titre, titre_tmp);
    strcpy(livres[i].auteur, auteur_tmp);
    livres[i].quantite = quantite_tmp;
  }
  fclose(output_file);
}

void ajouter_livre(){
  LIVRE livre;
  FILE *fichier = NULL;
  system("clear");
  getchar();
  printf("Entrez l'ISBN du livre\n");
  fgets(livre.ISBN, 13, stdin);
  SuppCarriageReturn(livre.ISBN);
  printf("Entrez le titre du livre\n");
  fgets(livre.titre, 100, stdin);
  SuppCarriageReturn(livre.titre);
  printf("Entrez l'auteur du livre\n");
  fgets(livre.auteur, 30, stdin);
  SuppCarriageReturn(livre.auteur);
  printf("Entrez les genres du livre\n");
  for(int i = 0 ; i < 3 ; i++){
    fgets(livre.genre[i], 20, stdin);
    SuppCarriageReturn(livre.genre[i]);
    if(strlen(livre.genre[i]) == 0){
      strcpy(livre.genre[i],"NULL");//cas où il n'y a pas de genre ajouté
    }
  }
  printf("Entrez la quantité voulue : ");
  scanf("%d", &livre.quantite);
  
  //On entre les valeurs dans la bdd
  fichier = fopen("./Data/livres.csv", "a");
  fprintf(fichier , "\n%s,%s,%s,", livre.ISBN, livre.titre, livre.auteur);
  for(int i = 0; i < 3 ; i++){
      fprintf(fichier,"%s,",livre.genre[i]);
  }
  fprintf(fichier, "%d", livre.quantite);
  fclose(fichier);
  AddBookHistory(livre,"Ajout"); //On ajoute dans l'historique l'action réalisée
}

int rechercher_livre(char critere, char *recherche, LIVRE *livre){
  int i_livres = nombre_livres("./Data/livres.csv");
  LIVRE *livres = malloc(sizeof(LIVRE)* (i_livres + 1));
  Get_livres(livres);
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

void supprimer_livre(LIVRE livre) {
  int i_livres = nombre_livres("./Data/livres.csv");
  LIVRE *livres = malloc(sizeof(LIVRE) * (i_livres + 1));
  char chaine_tmp[200];
  FILE *output_file = OpenDbFile("./Data/livres.csv","r");
  fgets(chaine_tmp, 200, output_file); //enlève la première ligne de la recherche
  int j = 0;
  for (int i = 0; i < i_livres; i++) {
    fgets(chaine_tmp, 200, output_file);
    char *ISBN_tmp = strtok(chaine_tmp, ",");
    char *titre_tmp = strtok(NULL, ",");
    char *auteur_tmp = strtok(NULL, ",");
    for (int k = 0 ; k < 3 ; k++){
      char *genre_tmp  = strtok(NULL, ",");
      strcpy(livres[j].genre[k], genre_tmp);
    }
    int quantite_tmp = atoi(strtok(NULL, ",")); //fonction de str à int 
    if(strcmp(ISBN_tmp, livre.ISBN) != 0 ){
      strcpy(livres[j].ISBN, ISBN_tmp);
      strcpy(livres[j].titre, titre_tmp);
      strcpy(livres[j].auteur, auteur_tmp);
      livres[j].quantite = quantite_tmp;
      j++;
    }else{
      LIVRE livre_supp;
      strcpy(livre_supp.ISBN, ISBN_tmp);
      strcpy(livre_supp.titre, titre_tmp);
      strcpy(livre_supp.auteur, auteur_tmp);
      strcpy(livre_supp.genre[0],livres[j].genre[0]);
      strcpy(livre_supp.genre[1],livres[j].genre[1]);
      strcpy(livre_supp.genre[2],livres[j].genre[2]);
      livre_supp.quantite = quantite_tmp;
      AddBookHistory(livre_supp,"Supression");
    }
  }
  fclose(output_file);
  remove("./Data/livres.csv");

  //on remet les livres sans celui que l'on a décidé de supprimer
  output_file = OpenDbFile("./Data/livres.csv","w+");
  fprintf(output_file,"ISBN,TITRE,AUTEUR(S),GENRE1,GENRE2,GENRE3,QUANTITE");
  for(int i = 0; i < j; i++){
    fprintf(output_file, "\n%s,%s,%s,", livres[i].ISBN, livres[i].titre, livres[i].auteur);
    for(int k = 0; k < 3 ; k++){
      fprintf(output_file,"%s,",livres[i].genre[k]);
    }
    fprintf(output_file, "%d", livres[i].quantite);
  }
  fclose(output_file);
}

void PrintLivres(LIVRE *livres,int nb_livres){
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

void PrintAllBooks(){
  int nb_livres = nombre_livres("./Data/livres.csv");
  LIVRE *livres = malloc(sizeof(LIVRE) * nb_livres);
  Get_livres(livres);
  PrintLivres(livres,nb_livres);
  printf("Appuyez sur la touche entrée pour continuer\n");
  char entree[10];
  getchar();
  fgets(entree,10,stdin);
}

void modifier_livre(LIVRE livre){
  int resp;
  LIVRE livre_mod;
  strcpy(livre_mod.ISBN,livre.ISBN);
  strcpy(livre_mod.auteur,livre.auteur);
  strcpy(livre_mod.titre,livre.titre); 
  strcpy(livre_mod.genre[0],livre.genre[0]);
  strcpy(livre_mod.genre[1],livre.genre[1]);
  strcpy(livre_mod.genre[2],livre.genre[2]);
  livre_mod.quantite = livre.quantite; 
  system("clear");
  printf("0 : Modifier l'ISBN\n");
  printf("1 : Modifier l'auteur\n");
  printf("2 : Modifier le titre\n");
  printf("3 : Modifier le genre 1\n");
  printf("4 : Modifier le genre 2\n");
  printf("5 : Modifier le genre 3\n");
  printf("6 : Modifier la quantité\n");
  printf("7 : Annuler\n");
  scanf("%d",&resp);
  getchar();
  switch(resp){
    case 0:
      printf("Nouvel ISBN");
      fgets(livre_mod.ISBN, 13, stdin);
      break;
    case 1:
      printf("Nouvel auteur");
      fgets(livre_mod.auteur, 100, stdin);
      break;
    case 2:
      printf("Nouveau titre");
      fgets(livre_mod.titre, 30, stdin);
      break;
    case 3:
      printf("Nouveau genre : ");
      fgets(livre_mod.genre[0], 20, stdin);
      break;
    case 4:
      printf("Nouveau genre : ");
      fgets(livre_mod.genre[1], 20, stdin);
      break;
    case 5:
      printf("Nouveau genre : ");
      fgets(livre_mod.genre[2], 20, stdin);
      break;
    case 6:
      printf("Nouvelle quantité : ");
      scanf("%d",&livre_mod.quantite);
      break;
    default :
      break;
  }
  supprimer_livre(livre);
  FILE *fichier = fopen("./Data/livres.csv", "a");
  fprintf(fichier, "\n%s,%s,%s,", livre_mod.ISBN, livre_mod.titre, livre_mod.auteur);
  for(int i = 0; i < 3 ; i++){
      fprintf(fichier,"%s,",livre_mod.genre[i]);
  }
  fprintf(fichier, "%d", livre_mod.quantite);
  fclose(fichier);
}

void MenuAjoutLivre(){
  int resp;
  system("clear");
  printf("0 : Ajout automatique\n");
  printf("1 : Ajout manuel\n");
  printf("2 : Annuler\n");
  scanf("%d",&resp);
  switch(resp){
    case 0 :
      ajouter_livre_auto();
      break;
    case 1 :
      ajouter_livre();
      break;
    default:
      break;
  }
}

void MenuRechercherLivre(char critere, LIVRE *livre){
  char recherche[50];
  system("clear");
  printf("Recherche : ");
  scanf("%s",&recherche);
  int nb_livres = nombre_livres("./Data/livres.csv");
  LIVRE *livres = malloc(sizeof(LIVRE) * nb_livres);
  int i_livres = rechercher_livre(critere,recherche,livres);
  PrintLivres(livres,i_livres);
  printf("##########\n");
  int resp;
  printf("Quel livre voulez vous choisir : ");
  scanf("%d",&resp);
  *livre = livres[resp-1];
}

void MenuSupprimerLivre(){
  int resp;
  system("clear");
  printf("0 : Par ISBN\n");
  printf("1 : Par auteur\n");
  printf("2 : Par titre\n");
  printf("3 : Par genre\n");
  printf("4 : Annuler\n");
  scanf("%d",&resp);
  LIVRE livre;
  LIVRE *ptr_livre = &livre;
  switch(resp){
    case 0 :
      MenuRechercherLivre('I',ptr_livre);
      supprimer_livre(livre);
      break;
    case 1 :
      MenuRechercherLivre('A',ptr_livre);
      supprimer_livre(livre);
      break;
    case 2 :
      MenuRechercherLivre('T',ptr_livre);
      supprimer_livre(livre);
      break;
    case 3 :
      MenuRechercherLivre('G',ptr_livre);
      supprimer_livre(livre);
      break;
    default:
      break;
  }
}

void MenuModifierLivre(){
  int resp;
  system("clear");
  printf("0 : Par ISBN\n");
  printf("1 : Par auteur\n");
  printf("2 : Par titre\n");
  printf("3 : Par genre\n");
  printf("4 : Annuler\n");
  scanf("%d",&resp);
  LIVRE livre;
  LIVRE *ptr_livre = &livre;
  switch(resp){
    case 0 :
      MenuRechercherLivre('I',ptr_livre);
      modifier_livre(livre);
      break;
    case 1 :
      MenuRechercherLivre('A',ptr_livre);
      modifier_livre(livre);
      break;
    case 2 :
      MenuRechercherLivre('T',ptr_livre);
      modifier_livre(livre);
      break;
    case 3 :
      MenuRechercherLivre('G',ptr_livre);
      modifier_livre(livre);
      break;
    default:
      break;
  }
}

void MenuGestionLivres(){
  int resp;
  system("clear");
  printf("0 : Ajouter un livre\n");
  printf("1 : Supprimer un livre\n");
  printf("2 : Modifier un livre\n");
  printf("3 : Liste des livres\n");
  printf("4 : Retour au menu principal\n");
  scanf("%d",&resp);
  switch(resp){
    case 0 :
      MenuAjoutLivre();
      break;
    case 1 :
      MenuSupprimerLivre();
      break;
    case 2 :
      MenuModifierLivre();
      break;
    case 3 :
      PrintAllBooks();
      break;
    default:
      return;
  }
}

