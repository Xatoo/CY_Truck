#include"arbre_t.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>



int main() {
  #Initialisation des variables qui vont stockés les données en entrée
  char villeA[35];
  char villeB[35];
  int trajet, etape;
  
  Arbre *avl = NULL;
  int h = 0;
  
  #recuperation des données 
  while (scanf("%d;%d;%[^;];%[^\n]\n", &trajet, &etape, villeA, villeB)==4) {
   
      #On attribue a chaque ville un identifiant unique ( exemple  : marseille devient 55423) pour pouvoir faire l'AVL
    
      int id_villeA = hash(villeA);
      int id_villeB = hash(villeB);

      #recherche si la première ville en entrée est déjà dans l'arbre ou non
      Arbre *temp1 = recherche(avl, id_villeA);
      if (temp1 == NULL) {
        #Si la ville n'est pas dans l'arbre, on l'insère dedans
        avl = insertion(avl, villeA, id_villeA, trajet, etape, &h);
      } else {
        #Si la ville est dans l'arbre, on modifie les informations pour cette ville
        maj_arbre(temp1, trajet, etape);
      }

      Arbre *temp2 = recherche(avl, id_villeB);
       #recherche si la deuxieme ville en entrée est déjà dans l'arbre ou non
    if (temp2 == NULL) {
      #Si la ville n'est pas dans l'arbre, on l'insère dedans
        avl = insertion(avl, villeB, id_villeB, trajet, 0, &h);
      } else {
      	#Si la ville est dans l'arbre, on modifie les informations pour cette ville
        maj_arbre(temp2, trajet, 0);
      }
  }
  
  afficherTop10(avl); #Recherche des 10 villes les plus traverser
  
  libererMemoireArbre(avl); #Liberation de la mémoire utilisé pour l'arbre

  return 0;
}

