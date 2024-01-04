#include<stdio.h>
#include<stdlib.h>

typedef struct _stat{
	float min;
	float max;
	float som;
	int compteur;
	float moy;
}Stat;


typedef struct _arbre{
	int id_trajet;
	float distance;
	int eq;
	struct _arbre *fg;
	struct _arbre *fd;
	
	

}Arbre;

int taille(Arbre * avl){
	if (avl==NULL){
		return 0;
	}
	return 1 + taille(avl->fg)+taille(avl->fd);
}

int equilibre(Arbre * avl){
	if (avl ==NULL){
		return 0;
	}
	return taille(avl->fg) - taille (avl->fd);	
}


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

Arbre * creerAvl(int id_t,float d){
	Arbre * avl = malloc(sizeof(Arbre));
	avl->id_trajet = id_t;
	avl->distance = d;
	avl->eq = equilibre(avl);
	avl->fg = NULL;
	avl->fd = NULL;



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

Arbre * rotationDoubleDroite(Arbre * avl){
	avl->fd = rotationGauche(avl->fg);
	return rotationDroite(avl);
	


}

Arbre * insertion(Arbre * avl, int id_trajet,float distance){
	
	if (avl == NULL){
		return creerAvl(id_trajet,distance);	
	}	
	if (id_trajet < avl->id_trajet){
		avl->fg = insertion(avl->fg,id_trajet,distance);
	}
	else if (id_trajet > avl->id_trajet){
		avl->fd = insertion(avl->fd,id_trajet,distance);
	}
	else {
		return avl;
	}

	avl->eq = equilibre(avl);
	
	

	if (avl->eq >1 && id_trajet < avl->fg->id_trajet){
		return rotationGauche(avl);

	}
	if (avl->eq < -1 && id_trajet > avl->fd->id_trajet){
		return rotationGauche(avl);

	}
	if (avl->eq >1 && id_trajet > avl->fd->id_trajet){
		return rotationDoubleDroite(avl);

	}

	if (avl->eq < -1 && id_trajet < avl->fd->id_trajet){
		return rotationDoubleGauche(avl);

	}
	return avl;
	
}

void stat(Arbre * avl){

	if (avl != NULL){
		
		stat(avl->fg);
		
		float min = avl -> distance;
		float max = avl -> distance;
		float som = avl -> distance;
		int compteur = 1;

		while (avl ->fd != NULL && avl->fd->id_trajet == avl->id_trajet){
			avl = avl->fd;
			min=(min >avl->distance) ? avl->distance : min;
			max=(max >avl->distance) ? avl->distance : max;
			som += avl->distance;
			compteur ++;
		}
		
		float moyenne = som /compteur;
		
		printf("Trajet %d; min = %.2f;max = %.2f, moyenne =%.2f\n", avl->id_trajet,min,max,moyenne);
	}
}

void infixe(Arbre * avl){	
	if (avl != NULL){
	
		infixe(avl->fg);
		printf("%d", avl->id_trajet);
		infixe(avl->fd);
	
}

}

int main(){

	printf("bonjour");
	Arbre * avl = NULL;
	float d;
	int id_t;
	
	
	while(scanf("%d;%f", &id_t,&d) == 2){
		
		avl=insertion(avl,id_t,d);
		
	}
	
	infixe(avl);
	
	stat(avl);
	
	
	
	free(avl);
	


	return 0;
}
