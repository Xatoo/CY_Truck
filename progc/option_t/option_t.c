#include"arbre_t.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>



int main() {
  char villeA[35];
  char villeB[35];
  int trajet, etape;
  Arbre *avl = NULL;
  int h = 0;

  while (scanf("%d;%d;%[^;];%[^\n]\n", &trajet, &etape, villeA, villeB)==4) {
   

      int id_villeA = hash(villeA);
      int id_villeB = hash(villeB);

      Arbre *temp1 = recherche(avl, id_villeA);
      if (temp1 == NULL) {
        avl = insertion(avl, villeA, id_villeA, trajet, etape, &h);
      } else {
        
        maj_arbre(temp1, trajet, etape);
      }

      Arbre *temp2 = recherche(avl, id_villeB);
      if (temp2 == NULL) {
        avl = insertion(avl, villeB, id_villeB, trajet, 0, &h);
      } else {
      	
        maj_arbre(temp2, trajet, 0);
      }
  }
  
  afficherTop10(avl);
  libererMemoireArbre(avl);

  return 0;
}

