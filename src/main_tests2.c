#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ecosys.h"

int main(){
    srand(time(NULL));
    Animal* liste_predateurs = NULL ; 
    Animal* liste_proies = NULL ; 
    Animal** ptr_liste_predateurs_2 = NULL ; 
    Animal** ptr_liste_proies_2 = NULL ; 


    for (int i = 0; i < 20; i++)
    {
        Animal* new_proie = creer_animal( (rand()%20) , (rand()%50) ,  10.0 ) ; 
        liste_proies = ajouter_en_tete_animal( liste_proies , new_proie ) ; 

        Animal* new_predateur = creer_animal( (rand()%20) , (rand()%50) ,  10.0 ) ; 
        liste_predateurs = ajouter_en_tete_animal( liste_predateurs , new_predateur ) ;
    }

    ecrire_ecosys("ecosys_txt" , liste_predateurs , liste_proies);
    lire_ecosys("ecosys_txt", ptr_liste_predateurs_2 , ptr_liste_proies_2) ;


    assert(compte_animal_it(liste_predateurs) == 20 ) ;
    assert(compte_animal_it(liste_proies) == 20 ) ;

    /* TME3 - EX3
    afficher_ecosys(liste_proies , liste_predateurs) ; 
    afficher_ecosys(*ptr_liste_proies_2 , *ptr_liste_predateurs_2) ; 
    */

    /* TME3 - EX4.1 
    Animal* pixel = creer_animal(0 , 0,  10.0 ) ;
    afficher_ecosys(pixel,NULL);
    bouger_animaux(pixel); 
    afficher_ecosys(pixel,NULL);
    */

    /* TM3 - EX4.3 
    Animal* pixel = creer_animal(0 , 0,  10.0 ) ;
    printf("%d \n" , compte_animal_it(pixel)) ;
    printf("%f \n" , pixel ->energie ) ;
    reproduce(&pixel,0); 
    printf("%d \n" , compte_animal_it(pixel)) ; 
    printf("%f \n" , pixel -> energie ) ;
    */

   /*TME3 - EX6 
    Animal* pixel = creer_animal(0 , 0,  10.0 ) ;
    printf("%d \n" , compte_animal_it(pixel)) ;
    pixel = animal_en_XY(pixel,1,0);
    printf("%d \n" , compte_animal_it(pixel)) ;
    */





    liste_predateurs = liberer_liste_animaux(liste_predateurs); 
    liste_proies = liberer_liste_animaux(liste_proies);





    return  0 ; 
}