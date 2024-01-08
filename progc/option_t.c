#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct _arbre{
	struct _arbre *fg;
	struct _arbre *fd;
	struct Trajet *pTrajet;
	int eq;
	int ville;
	int nb_trajet;
	int nb_trajet_depart;
} Arbre;


typedef struct _trajet{
	int id_trajet;
	struct _trajet *pNext;
} Trajet;


int max(int a,int b){
	return (a>b)? a:b;
}
int min(int a,int b){
	return (a<b)? a:b;
}

int max2(int a,int b,int c){
	return max(max(a,b),c);
}

int min2(int a,int b,int c){
	return min(min(a,b),c);
}

Arbre *creerArbre(int elmt) {
    Arbre *avl = malloc(sizeof(Arbre));
    avl->ville = elmt; // A voir pour ça 
    avl->eq = 1;
    avl->nb_trajet = 0;
    avl->nb_trajet_depart = 0;
    avl->pTrajet = malloc(sizeof(Trajet));
    avl->fg = NULL;
    avl->fd = NULL;

    return avl;
}

Arbre *rotationGauche(Arbre *avl) {
    Arbre *pivot = avl->fd;
    avl->fd = pivot->fg;
    pivot->fg = avl;

    int eq_avl = avl->eq;
    int eq_piv = pivot->eq;

    avl->eq = eq_avl - max(eq_piv, 0) - 1;
    pivot->eq = min2(eq_avl - 2, eq_avl + eq_piv - 2, eq_piv - 1);

    return pivot;
}

Arbre *rotationDroite(Arbre *avl) {
    Arbre *pivot = avl->fg;
    avl->fg = pivot->fd;
    pivot->fd = avl;

    int eq_avl = avl->eq;
    int eq_piv = pivot->eq;

    avl->eq = eq_avl - min(eq_piv, 0) + 1;
    pivot->eq = max2(eq_avl + 2, eq_avl + eq_piv + 2, eq_piv + 1);

    return pivot; 
}

Arbre *rotationDoubleGauche(Arbre *avl) {
    avl->fd = rotationDroite(avl->fd);
    return rotationGauche(avl);
}

Arbre *rotationDoubleDroite(Arbre *avl) {  
    avl->fg = rotationGauche(avl->fg);
    return rotationDroite(avl);
}

int main(){

	char nom[100];
	int  trajet;

	while( scanf("%d;%[^\n]\n", &trajet, nom) == 2 ){
		
		printf("%s;%d\n", nom, trajet);
		
	}




	
	return 0;


}
