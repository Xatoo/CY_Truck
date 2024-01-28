#include"arbre_s.h"
#include<stdio.h>
#include<stdlib.h>



int main(){
	Arbre * avl = NULL;
	float d;
	int id_t;
	int h=0;
	
	while(scanf("%d;%f", &id_t,&d) == 2){
		Arbre *p = avl;
		if (recherche(avl,id_t) == NULL){
			avl = insertion(avl,id_t,h,d);
			
		}
		else{
			p=recherche(avl,id_t);
			maj(d,p);
		
		 }
		
	
	}
	
	
	plusGrandesValeurs(avl);
	libererArbre(avl);

	return 0;
}

