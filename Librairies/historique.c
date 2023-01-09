#include "historique.h"

FILE *OpenDbFileConnexionHistory(char *method) {
  FILE *input_file = fopen(ConnexionHistory, method);
  if (!input_file) {
    printf("FOPEN ERROR");
    exit(EXIT_FAILURE);
  }
  return input_file;
}

FILE *OpenDbFileBookHistory(char *method) {
  FILE *input_file = fopen(BookHistory, method);
  if (!input_file) {
    printf("FOPEN ERROR");
    exit(EXIT_FAILURE);
  }
  return input_file;
}

void AddLogInToHistory(char *ID) {
  FILE *histo_file = OpenDbFileConnexionHistory("a");
  fprintf(histo_file, "%s,", ID);

  time_t timestamp = time(NULL);
  struct tm *now = localtime(&timestamp);

  fprintf(histo_file, "%d-%02d-%02d|%02d:%02d:%02d\n", now->tm_mday,now->tm_mon + 1, now->tm_year + 1900, now->tm_hour+2, now->tm_min,now->tm_sec);
  fclose(histo_file);
}

void AddBookHistory(LIVRE book,char* action) {
  //Action : Ajout ou Supression
  FILE *histo_file = OpenDbFileBookHistory("a");
  
  fprintf(histo_file, "%s,%s,%s,%s,",action, book.ISBN, book.titre, book.auteur);
  for(int i = 0; i < 3 ; i++){
    if(strcmp(book.genre[i],"NULL")!=0){
      fprintf(histo_file,"%s ",book.genre[i]);
    }
  }
  fprintf(histo_file,",%d,",book.quantite);

  time_t timestamp = time(NULL);
  struct tm *now = localtime(&timestamp);
  
  fprintf(histo_file, "%d-%02d-%02d|%02d:%02d:%02d\n", now->tm_mday,
          now->tm_mon + 1, now->tm_year + 1900, now->tm_hour+2, now->tm_min,
          now->tm_sec);
  
  fclose(histo_file);
}

void PrintLoginHistory(){
  FILE *fichier = OpenDbFileConnexionHistory("r");
  char ligne[100];
  while(! feof(fichier)){
    fgets(ligne,100,fichier);
    printf("%s",ligne);
  }
  fclose(fichier);
  printf("Appuyez sur la touche entrée pour continuer\n");
  char entree[10];
  getchar();
  fgets(entree,10,stdin);
}

void PrintBookHistory(){
  FILE *fichier = OpenDbFileBookHistory("r");
  char ligne[100];
  while(! feof(fichier)){
    fgets(ligne,100,fichier);
    printf("%s",ligne);
  }
  fclose(fichier);
  printf("Appuyez sur la touche entrée pour continuer\n");
  char entree[10];
  getchar();
  fgets(entree,10,stdin);
}

void menu_historique(){
  int resp;
  system("clear");
  printf("0 : Afficher l'historique de connexion\n");
  printf("1 : Afficher l'historique des livres\n");
  printf("2 : Annuler\n");
  scanf("%d",&resp);
  switch(resp){
    case 0 : 
      PrintLoginHistory();
      break;
    case 1 :
      PrintBookHistory();
      break;
    default:
      break;
  }
}
