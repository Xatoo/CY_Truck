#include"arbre_s.h"
#include<stdio.h>
#include<stdlib.h>



int main(){
	Arbre * avl = NULL;
	//Initialisation des variables qui vont stockées les données en entrée
	float d;
	int id_t;
	
	int h=0;
	//recuperation des données 
	while(scanf("%d;%f", &id_t,&d) == 2){
		//recheche si un trajet est déjà dans l'arbre 
		Arbre *p = recherche(avl,id_t);
		
		if (p == NULL){
			//Si le trajet n'est pas dans l'arbre on l'insère dedans
			avl = insertion(avl,id_t,h,d);
			
		}
		else{
			//Si le trajet est dans l'arbre on met à jour les infos du noeud concerné
			maj(d,p);
		
		 }
		
	
	}
	
	
	plusGrandesValeurs(avl);  //Recherche des 50 plus grandes valeurs (max - min)
	libererArbre(avl);  //Liberation de la mémoire utilisé pour l'arbre

	return 0;
}
