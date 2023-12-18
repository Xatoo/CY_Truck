#include<stdio.h>
#include<stdlib.h>

typedef struct _arbre{
	int v;
	int eq;
	struct _arbre * fg; 
	struct _arbre * fd; 

}Arbre;

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


Arbre * creerArbre(int elmt){
	Arbre *avl  = malloc(sizeof(Arbre));
	avl->v=elmt;
	avl->eq=1;
	avl->fg=NULL;
	avl->fd=NULL;

	return avl;
}

Arbre * rotationGauche(Arbre * avl){
	Arbre * pivot = avl->fd;
	avl->fd = pivot->fg;
	pivot->fg = avl;
	
	int eq_avl = avl->eq;
	int eq_piv = pivot->eq;
	
	avl->eq = eq_avl - max(eq_piv,0) -1;
	pivot->eq = min2(eq_avl-2,eq_avl+eq_piv-2,eq_piv-1);

	return avl;


}


Arbre * rotationDroite(Arbre * avl){
	Arbre * pivot = avl->fg;
	avl->fg = pivot->fd;
	pivot->fd = avl;
	
	int eq_avl = avl->eq;
	int eq_piv = pivot->eq;
	
	avl->eq = eq_avl - min(eq_piv,0) +1;
	pivot->eq = max2(eq_avl+2,eq_avl+eq_piv+2,eq_piv+1);

	return avl;


}

Arbre * rotationDoubleGauche(Arbre * avl){
	avl->fd = rotationDroite(avl->fd);
	return rotationGauche(avl);
	


}

Arbre * rotationDoubleDauche(Arbre * avl){
	avl->fd = rotationGauche(avl->fg);
	return rotationDroite(avl);
	


}




int main(){
	return 0;
}
