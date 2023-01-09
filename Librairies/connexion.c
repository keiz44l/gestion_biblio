#include "connexion.h"

#define DbFileUtilisateurs "./Data/utilisateurs.csv"

int Comp_Mdp(char *Mdp1, BYTE *Mdp2) {
  char *Mdp2_converted = malloc(sizeof(Mdp2) * 2 + 1);
  Mdp2_converted = ConvertByteToChar(Mdp2);
  if (!strcmp(Mdp1, Mdp2_converted)) {
    return 1;
  }
  return 0;
}

int bytelen(BYTE *byte){
  int taille = 0;
  while(byte[taille] != '\0'){
    taille++;
  }
  return taille;
}

char *ConvertByteToChar(BYTE *byte) {
  char *chaine = malloc(bytelen(byte) * 2 + 1);
  char *chaine_tmp = malloc(bytelen(byte) * 2 + 1);
  strcpy(chaine, "");
  strcpy(chaine_tmp, "");
  for (int i = 0; i < bytelen(byte); i++) {
    sprintf(chaine_tmp, "%s%x", chaine, byte[i]);
    strcpy(chaine, chaine_tmp);
  }
  free(chaine_tmp);
  return chaine;
}

FILE *OpenDbFileUtilisateurs(char *method) {
  FILE *input_file = fopen(DbFileUtilisateurs, method);
  if (!input_file) {
    printf("FOPEN ERROR");
    exit(EXIT_FAILURE);
  }
  return input_file;
}

void StockerUtilisateur(char role, char Login[], BYTE Mdp[]) {
  FILE *output_file = OpenDbFileUtilisateurs("a");
  char ID[10];
  GetNewId(role, ID);
  fprintf(output_file, "%s,", ID);

  fprintf(output_file, "%s,", Login);

  SHA256_CTX ctx;
  sha256_init(&ctx);
  sha256_update(&ctx, Mdp, bytelen(Mdp));
  sha256_final(&ctx, Mdp);

  for (int i = 0; i < bytelen(Mdp); i++) {
    fprintf(output_file, "%x", Mdp[i]);
  }
  fprintf(output_file, "\n");

  fclose(output_file);
}

void Get_utilisateurs(UTILISATEUR *utilisateurs) {
  int i_utilisateurs = nombre_utilisateurs(DbFileUtilisateurs);
  char chaine_tmp[200];
  FILE *output_file = OpenDbFileUtilisateurs("r");
  for (int i = 0; i < i_utilisateurs; i++) {
    fgets(chaine_tmp, 200, output_file);
    char *ID_tmp = strtok(chaine_tmp, ",");
    char *Login_tmp = strtok(NULL, ",");
    char *Mdp_tmp = strtok(NULL, ",");
    Mdp_tmp[strlen(Mdp_tmp) - 1] = '\0';
    strcpy(utilisateurs[i].ID, ID_tmp);
    strcpy(utilisateurs[i].Login, Login_tmp);
    strcpy(utilisateurs[i].Mdp, Mdp_tmp);
  }
  fclose(output_file);
}

int nombre_utilisateurs(char *fichier_utilisateurs) {
  FILE *output_file = OpenDbFileUtilisateurs("r");
  int nombre_lignes = 0;
  int caractereActuel = 0;
  do {
    caractereActuel = fgetc(output_file);
    if (caractereActuel == '\n') {
      nombre_lignes++;
    }
  } while (caractereActuel != EOF);
  fclose(output_file);
  return nombre_lignes;
}

int connexion(char *Login, BYTE *Mdp) {
  int i_utilisateurs = nombre_utilisateurs(DbFileUtilisateurs);
  UTILISATEUR *utilisateurs = malloc(sizeof(UTILISATEUR) * (i_utilisateurs + 1));
  Get_utilisateurs(utilisateurs);
  for (int i = 0; i < i_utilisateurs; i++) {
    if (!strcmp(utilisateurs[i].Login, Login)) {
      SHA256_CTX ctx;
      sha256_init(&ctx);
      sha256_update(&ctx, Mdp, bytelen(Mdp));
      sha256_final(&ctx, Mdp);
      if (Comp_Mdp(utilisateurs[i].Mdp, Mdp)) {
        return 1;
      }
    }
  }
  return 0;
}

void PrintAllUsers() {
  int i_utilisateurs = nombre_utilisateurs(DbFileUtilisateurs);
  UTILISATEUR *utilisateurs = malloc(sizeof(UTILISATEUR) * (i_utilisateurs + 1));
  Get_utilisateurs(utilisateurs);
  for (int i = 0; i < i_utilisateurs; i++) {
    printf("%s, %s, %s\n", utilisateurs[i].ID, utilisateurs[i].Login, utilisateurs[i].Mdp);
  }
  printf("Appuyez sur la touche entrée pour continuer\n");
  char entree[10];
  getchar();
  fgets(entree,10,stdin);
}

void Delete_utilisateur(UTILISATEUR utilisateur) {
  int i_utilisateurs = nombre_utilisateurs(DbFileUtilisateurs);
  PTR_UTILISATEUR utilisateurs = malloc(sizeof(UTILISATEUR) * (i_utilisateurs + 1));
  char chaine_tmp[200];
  FILE *output_file = OpenDbFileUtilisateurs("r");
  int j = 0;
  for (int i = 0; i < i_utilisateurs; i++) {
    fgets(chaine_tmp, 200, output_file);
    char *ID_tmp = strtok(chaine_tmp, ",");
    char *Login_tmp = strtok(NULL, ",");
    char *Mdp_tmp = strtok(NULL, ",");
    Mdp_tmp[strlen(Mdp_tmp) - 1] = '\0';
    if (strcmp(ID_tmp, utilisateur.ID) != 0) {
      strcpy(utilisateurs[j].ID, ID_tmp);
      strcpy(utilisateurs[j].Login, Login_tmp);
      strcpy(utilisateurs[j].Mdp, Mdp_tmp);
      j++;
    }
  }
  fclose(output_file);
  remove(DbFileUtilisateurs);

  output_file = OpenDbFileUtilisateurs("a");
  for (int i = 0; i < j; i++) {
    fprintf(output_file, "%s,", utilisateurs[i].ID);
    fprintf(output_file, "%s,", utilisateurs[i].Login);
    fprintf(output_file, "%s\n", utilisateurs[i].Mdp);
  }
  fclose(output_file);
}

void AddTestUsers(int nb_users) {
  char ID[5];
  char Login[10];
  BYTE Mdp[100] = "";
  for (int i = 0; i < nb_users; i++) {
    strcpy(Mdp, "test");
    sprintf(Login, "test%d", i + 1);
    StockerUtilisateur('A', Login, Mdp);
  }
}

void GetNewId(char role, char *NewID) {
  // A: Admin, L: Lecteur
  int i_utilisateurs = nombre_utilisateurs(DbFileUtilisateurs);
  UTILISATEUR *utilisateurs =
      malloc(sizeof(UTILISATEUR) * (i_utilisateurs + 1));
  Get_utilisateurs(utilisateurs);
  int *nombres_utilises = malloc(sizeof(int) * i_utilisateurs);
  int j = 0;
  for (int i = 0; i < i_utilisateurs; i++) {
    if (utilisateurs[i].ID[0] == role) {
      DeleteFirstCharInChaine(utilisateurs[i].ID);
      nombres_utilises[j] = atoi(utilisateurs[i].ID);
      j++;
    }
  }
  int IsNombreUtilise;
  int k = 1;
  while (1) {
    IsNombreUtilise = 0;
    for (int i = 0; i < j; i++) {
      if (nombres_utilises[i] == k) {
        IsNombreUtilise = 1;
      }
    }
    if (!IsNombreUtilise) {
      sprintf(NewID, "%c%d", role, k);
      return;
    }
    k++;
  }
}

void DeleteFirstCharInChaine(char *chaine) {
  int len = strlen(chaine);
  for (int i = 0; i < len - 1; i++) {
    chaine[i] = chaine[i + 1];
  }
  chaine[len - 1] = '\0';
}

int SearchUser(char critere, char *recherche, PTR_UTILISATEUR utilisateur) {
  // critère: I=par ID et L par Login
  int i_utilisateurs = nombre_utilisateurs(DbFileUtilisateurs);
  UTILISATEUR *utilisateurs = malloc(sizeof(UTILISATEUR) * (i_utilisateurs + 1));
  Get_utilisateurs(utilisateurs);
  for (int i = 0; i < i_utilisateurs; i++) {
    switch (critere) {
    case 'I': {
      if (!strcmp(utilisateurs[i].ID, recherche)) {
        *utilisateur = utilisateurs[i];
        return i;
      }
      break;
    }
    case 'L': {
      if (!strcmp(utilisateurs[i].Login, recherche)) {
        *utilisateur = utilisateurs[i];
        return i;
      }
      break;
    }
    default:
      break;
    }
  }
  strcpy(utilisateur->ID, "");
  strcpy(utilisateur->Login, "");
  strcpy(utilisateur->Mdp, "");
  return 0;
}

void ModifyPassword(UTILISATEUR utilisateur, BYTE NewMdp[]) {
  Delete_utilisateur(utilisateur);
  StockerUtilisateur(utilisateur.ID[0], utilisateur.Login, NewMdp);
}

void MenuTest(){
  printf("0 : Ajouter un utilisateur\n");
  printf("1 : Supprimer un utilisateur\n");
  printf("2 : Supprimer tous les utilisateurs\n");
  printf("3 : Modifier le MDP d'un utilisateur\n");
  printf("4 : Ajouter des utilisateurs de test\n");
  printf("5 : Se connecter\n");
  printf("6 : Afficher tous les utilisateurs\n");
  printf("7 : Quitter\n");
  int resp;
  scanf("%d",&resp);
  system("clear");
  char ID[5];
  char Login[TAILLE_LOGIN];
  BYTE Mdp[50];
  UTILISATEUR utilisateur;
  switch (resp){
    case 0 :
      printf("Login : ");
      scanf("%s",&Login);
      printf("Mdp : ");
      scanf("%s",&Mdp);
      StockerUtilisateur('A',Login,Mdp);
      break;
    case 1 :
      printf("ID de l'utilisateur a supprimer : ");
      scanf("%s",&ID);
      SearchUser('I',ID,&utilisateur);
      Delete_utilisateur(utilisateur);
      break;
    case 2 :
      remove(DbFileUtilisateurs);
      FILE* file =OpenDbFileUtilisateurs("w+");
      fclose(file);
      break;
    case 3 :
      printf("ID de l'utilisateur a modifier : ");
      scanf("%s",&ID);
      printf("Nouveau mdp : ");
      scanf("%s",&Mdp);
      SearchUser('I',ID,&utilisateur);
      ModifyPassword(utilisateur, Mdp);
      break;
    case 4 :
      AddTestUsers(5);
      break;
    case 5 :
      printf("Login : ");
      scanf("%s",&Login);
      printf("Mdp : ");
      scanf("%s",&Mdp);
      int conn = connexion(Login,Mdp);
      if(conn){
        printf("connexion réussie\n");
      }else{
        printf("Login ou mot de passe incorrect\n");
      }
      break;
    case 6 :
      PrintAllUsers();
      break;
    case 7 :
      exit(EXIT_SUCCESS);
      break;
    default :
      break;
  }
}
