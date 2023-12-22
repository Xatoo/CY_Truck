#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct _etape{
	int id_etape;
	char villeA[30];
	char villeB[30];
	struct _etape * fg;
	struct _etape * fd;

}Etape;


typedef struct _trajet{
	int id_trajet;
	struct _trajet * fg;
	struct _trajet * fd;
	struct Etape * etape;
	

}Trajet;



Etape * arbreEtape(int id, char villeA,char villeB){
	Etape * etape = malloc(sizeof(Etape));
	if (etape ==NULL){
		exit(1);
	etape->id_etape = id;
	etape->villeA = villeA;
	etape->villeB = villeB;
	etape->fg = NULL;
	etape->fd = NULL;
	return etape;
} 

int main(){

	char nom[100];
	int  trajet;

	while( scanf("%d;%[^\n]\n", &trajet, nom) == 2 ){
		
		printf("%s;%d\n", nom, trajet);
		
	}




	
	return 0;


}
