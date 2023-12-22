#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int main(){

	char nom[100];
	int  trajet;

	while( scanf("%d;%[^\n]\n", &trajet, nom) == 2 ){
		
		printf("%s;%d\n", nom, trajet);
		
	}




	
	return 0;


}
