#include"avl_s.h"
#include"valeurs_s.h"
#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
int main(){
	Arbre * avl = NULL;
	float d;
	int id_t;
	int h=0;
	
	while(scanf("%d;%f", &id_t,&d) == 2){
		Arbre *p = recherche(avl,id_t);
		if (p == NULL){
			avl = insertion(avl,id_t,h,d);
		}
		else{
			maj(d,p);
		 }
	}	
	plusGrandesValeurs(avl);
	free(avl);

	return 0;
}
