#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "./src/ecosys.h"



#define NB_PROIES 20
#define NB_PREDATEURS 20
#define T_WAIT 40000





int main(void) {
  srand(time(NULL));

  Animal* liste_proies = NULL ; 
  Animal* liste_predateurs = NULL ; 
  int monde[SIZE_Y][SIZE_X];
  FILE*f = fopen("Evol_Pop.txt", "w");

  // Initialisations des animaux
  for (int i = 0; i < NB_PREDATEURS; i++)
  {
    liste_predateurs = ajouter_en_tete_animal(liste_predateurs,creer_animal(rand()%SIZE_X , rand()%SIZE_Y ,  25.0)) ;
  }
  for (int i = 0; i < NB_PROIES; i++)
  {
    liste_proies = ajouter_en_tete_animal(liste_proies,creer_animal(rand()%SIZE_X , rand()%SIZE_Y ,  20.0)) ; 
  }


  int tab[SIZE_Y][SIZE_X] ; 
  for (int i = 0; i < SIZE_Y; i++)
  {
    for (int j = 0; j < SIZE_X; j++)
    {
      monde[i][j] = 0 ; 
    }
    
  }
  

  // Simulation 
  afficher_ecosys(liste_proies , liste_predateurs) ; 
  int nb_it = 1 ;
  while (compte_animal_it(liste_predateurs)!= 0 || compte_animal_it(liste_proies) != 0 )
  {
    fprintf(f, "%d %d %d \n" , nb_it , compte_animal_it(liste_proies) , compte_animal_it(liste_predateurs) );
    afficher_ecosys(liste_proies , liste_predateurs) ; 
    rafraichir_monde(monde);
    rafraichir_predateurs(&liste_predateurs,&liste_proies );
    rafraichir_proies(&liste_proies,monde);
    
    //sleep(1) ; 
    //system("clear");
    nb_it++;
  } 
  afficher_ecosys(liste_proies , liste_predateurs) ;
  printf("%d \n" , nb_it) ; 
  fclose(f);





  return 0;
}




// Pour le graphe 
// gnuplot 
// set terminal png
// set output "evo.png"
// plot "Evol_Pop.txt" using 1:2 with lines title "proies"
// set output "evo.png"
// replot "Evol_Pop.txt" using 1:3 with lines title "predateurs"