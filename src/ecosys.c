#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "ecosys.h"
#include <string.h> 

float p_ch_dir=0.01; //probabilite de changer de direction de deplacement
float p_reproduce_proie=0.4;
float p_reproduce_predateur=0.65;
int temps_repousse_herbe=-15;

/* PARTIE 1*/
/* Fourni: Part 1, exercice 4, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}


/* Fourni: Part 1, exercice 4, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* A faire. Part 1, exercice 6, question 2 */
void ajouter_animal(int x, int y,  float energie, Animal **liste_animal) {
  assert(x<SIZE_X);
  assert(y<SIZE_Y);
  Animal * na = creer_animal(x,y,energie) ; 
  na -> suivant= (*liste_animal);
  (*liste_animal)= na;
}

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) {
  /*A Completer*/
  Animal *tmp;
  assert(liste);
  tmp =*liste;
  if(*liste==animal){ // si c'est la tete qu'il faut supprimer
    *liste=(*liste)->suivant;
    free(tmp);
  } else { // si c'est au milieu on se place juste avant 
    while (tmp)
    {
      if (tmp -> suivant = animal)
      {
        Animal* tmp2 = tmp-> suivant ; 
        tmp -> suivant = tmp2 -> suivant ; 
        free(tmp2) ; 
        return ; 
      }
      tmp = tmp -> suivant ;
    } 
  }
}


/* A Faire. Part 1, exercice 6, question 7 */
Animal* liberer_liste_animaux(Animal *liste) {
  Animal* tmp = liste ; 
  while (liste)
  {
    tmp = liste  ; 
    liste = liste -> suivant ; 
    free( tmp ) ;  
  }
   

  return NULL;
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_it(Animal *la) {
  int cpt=0;
  while (la) {
    ++cpt;
    la=la->suivant;
  }
  return cpt;
}



/* Part 1. Exercice 5, question 1, ATTENTION, ce code est susceptible de contenir des erreurs... */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
  unsigned int i, j;
  char ecosys[SIZE_Y][SIZE_X];
  Animal *pa=NULL;

  /* on initialise le tableau */
  for (i = 0; i < SIZE_Y; ++i) {
    for (j = 0; j < SIZE_X; ++j) {
      ecosys[i][j]=' ';
    }
  }

  /* on ajoute les proies */
  pa = liste_proie;
  while (pa) {
    ecosys[pa->y][pa->x] = '*';
    pa=pa->suivant;
  }

  /* on ajoute les predateurs */
  pa = liste_predateur;
  while (pa) {
      if ((ecosys[pa->y][pa->x] == '@') || (ecosys[pa->y][pa->x] == '*')) { /* proies aussi present */
        ecosys[pa->y][pa->x] = '@';
      } else {
        ecosys[pa->y][pa->x] = 'O';
      }
    pa = pa->suivant;
  }

  /* on affiche le tableau */
  printf("+");
  for (j = 0; j < SIZE_X; ++j) {
    printf("-");
  }  
  printf("+\n");
  for (i = 0; i < SIZE_Y; ++i) {
    printf("|");
    for (j = 0; j < SIZE_X; ++j) {
      putchar(ecosys[i][j]);
    }
    printf("|\n");
  }
  printf("+");
  for (j = 0; j<SIZE_X; ++j) {
    printf("-");
  }
  printf("+\n");
  int nbproie=compte_animal_it(liste_proie);
  int nbpred=compte_animal_it(liste_predateur);
  
  printf("Nb proies : %5d\tNb predateurs : %5d\n", nbproie, nbpred);

}


void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/

/* Part 2. Exercice 4, question 1 */
void bouger_animaux(Animal *la) {
    /*A Completer*/
  int pas;
  while(la) {
    // dir[0]
    if(rand()/RAND_MAX < p_ch_dir){
      la->dir[0]=rand()%3-1;
    }
    //dir[1]
    if(rand()/RAND_MAX < p_ch_dir){
      la->dir[1]=rand()%3-1;
    }
    la->y = (la->y - la->dir[0] + SIZE_Y)%SIZE_Y;
    la->x = (la->x - la->dir[1] + SIZE_X)%SIZE_X;
    la=la->suivant;
  }
}


/* Part 2. Exercice 4, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
  float proba = 0.0 ;
  Animal * tmp = *liste_animal ; 
  while (tmp)
  {
    proba = (rand()%(99)+1)/100.0 ;
    if (proba > p_reproduce)
    {
      Animal* baby = creer_animal(tmp->x,tmp->y,(tmp->energie)/2) ; 
      tmp ->energie = ( tmp ->energie )/ 2 ; 
      *liste_animal = ajouter_en_tete_animal(*liste_animal , baby) ; 
    }
    tmp = tmp->suivant ;
}
}



/* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_Y][SIZE_X]) {
  bouger_animaux(*liste_proie) ; 
  Animal * tmp = *liste_proie;
  while (tmp)
  {
    if (monde[tmp->y][tmp->x] > -1 )   
    {
      tmp ->energie = (tmp ->energie) + monde[tmp->y][tmp->x] ; 
      monde[tmp->y][tmp->x] = temps_repousse_herbe ;
    }

    
    tmp ->energie = (tmp ->energie) - 1 ;
    if (tmp -> energie < 0 ){
      enlever_animal(liste_proie , tmp) ; 
    }
    tmp = tmp->suivant ; 
  }
  reproduce(liste_proie,p_reproduce_proie);
  

}


/* Part 2. Exercice 7, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {
    /*A Completer*/
    while (l)
    {
      if (l->x == x && l->y == y)
      {
        return l;
      }
      l = l -> suivant ; 
    }
    

  return NULL;
} 

/* Part 2. Exercice 7, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
  bouger_animaux(*liste_predateur) ; 
  Animal * tmp = *liste_predateur;
  while (tmp)
  {
    tmp ->energie = (tmp ->energie) - 1 ;
    if (tmp -> energie < 0 ){
      enlever_animal(liste_predateur , tmp) ; 
    }
    Animal* presence = animal_en_XY(*liste_proie , tmp ->x , tmp ->y) ; 
    if (presence)
    {
      tmp ->energie = (tmp->energie) + (presence ->energie) ; 
      enlever_animal(liste_proie,presence) ; 
    }
    
    tmp = tmp->suivant ; 
  }
  reproduce(liste_predateur,p_reproduce_predateur);

}

/* Part 2. Exercice 5, question 2 */
void rafraichir_monde(int monde[SIZE_Y][SIZE_X]){

  for (int i = 0; i < SIZE_Y; i++)
  {
    for (int j = 0; j < SIZE_X; j++)
    {
      monde[i][j] = monde[i][j] + 1 ; 
    }
    
  }


}

void ecrire_ecosys(const char *nom_fichier, Animal *liste_predateur, Animal *liste_proie){
  FILE*f = fopen(nom_fichier, "w"); // open a file 
  if ( f == NULL) { 
    printf("erreur ouverture fichier \n"); 
    return ; 
  }
  fprintf(f, "<proies>\n");  
  Animal * tmp = liste_proie ; 
  while ( tmp) {
    fprintf(f, " x = %d y = %d dir = [%d %d] e = %f \n" , tmp -> x , tmp -> y , tmp -> dir[0] , tmp -> dir[1] , tmp -> energie);
    tmp = tmp -> suivant ;
  }
  fprintf(f, "</proies>\n");
  fprintf(f, "<predateurs>\n");
  tmp = liste_predateur ; 
  while ( tmp ) {
    fprintf(f, " x = %d y = %d dir = [%d %d] e = %f \n" , tmp -> x , tmp -> y , tmp -> dir[0] , tmp -> dir[1] , tmp -> energie);
    tmp = tmp -> suivant ;
  }
  fprintf(f, "</predateurs>\n");
  fclose(f); //ferme le fichier 
}

void lire_ecosys(const char *nom_fichier, Animal **liste_predateur, Animal **liste_proie){
  FILE * f = fopen( nom_fichier , "r");
  if ( f== NULL ) {
    printf("Erreur ouverture fichier \n");
    return ; 
  }
  Animal* liste_predateurs_tmp = NULL ;
  Animal* liste_proies_tmp = NULL ;  
  char buff[256];
  // proies 
  fgets(buff , 256 , f); 
  assert(strncmp(buff,"<proies>", 8)==0); 
  int x , y , dir0 , dir1 ;
  float e ; 
  while (strncmp (buff , "</proies>",9) != 0 ){
    sscanf(buff, "x=%d y=%d dir=[%d %d] e=%f", &x, &y , &dir0 , &dir1 ,&e);
    Animal * na = creer_animal(x,y,e); 
    na -> dir[0] = dir0; 
    na -> dir[1] = dir1 ;
    liste_proies_tmp =  ajouter_en_tete_animal (liste_proies_tmp , na);
    fgets(buff,256,f); 
  }

  // predateurs 
  fgets(buff , 256 , f); 
  assert(strncmp(buff,"<predateurs>", 12)==0); 
  fgets(buff , 256 , f);
  while (strncmp (buff , "</predateurs>",13) != 0 ){
    sscanf(buff, "x=%d y=%d dir=[%d %d] e=%f", &x, &y , &dir0 , &dir1 ,&e);
    Animal * na = creer_animal(x,y,e);
    na -> dir[0] = dir0; 
    na -> dir[1] = dir1 ;
    liste_predateurs_tmp =  ajouter_en_tete_animal (liste_predateurs_tmp , na);
    fgets(buff,256,f); 
  }
  fclose(f);
  liste_predateur = &liste_predateurs_tmp ; 
  liste_proie  = &liste_proies_tmp ; 
}
