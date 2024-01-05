#include<stdio.h>
#include<stdlib.h>




typedef struct _arbre{
	int id_trajet;
	float distance;
	struct _arbre *fg;
	struct _arbre *fd;
	int eq;
	float min;
	float max;
	float som;
	int compteur;
	float moy;
	

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
	avl->eq = 0;
	avl->fg = NULL;
	avl->fd = NULL;
	avl->eq = 0;
	avl->min = d;
	avl->max = d;
	avl->som = d;
	avl->compteur = 1;
	avl->moy =d;

}



Arbre * maj(float d,Arbre * avl){
	if (avl != NULL){
		
		if (avl-> min > d){
			avl->min = d;
		}
		if (avl->max < d){
			avl->max =d;
		}
		avl->som +=d;
		avl->compteur +=1;
		avl->moy = avl->som/avl->compteur;
		
	}
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
	avl = pivot;
	return avl;


}

Arbre * recherche(Arbre * avl, int id){
	if (avl == NULL){
		return NULL;
	}
	else if (avl->id_trajet == id){
		return avl;
	}
	else if (id < avl->id_trajet){
		return recherche(avl->fg,id);
	}
	else {
		return recherche(avl->fd,id);
	}

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


Arbre * equilibreAvl(Arbre * avl){
	if (avl->eq >=2){
		if (avl->fd->eq >=0){
			return rotationGauche(avl);
		}
		else {
			return rotationDoubleGauche(avl);
		}
	
	}
	else if (avl->eq <= -2){
		if (avl->fg->eq <=0){
			return rotationDroite(avl);
		}
		else {
			return rotationDoubleDroite(avl);
		}
	
	
	}
	return avl;
}




Arbre * insertion(Arbre * avl, int id_trajet,int *h,float distance){
	
	if (avl == NULL){
		*h=1;
		return creerAvl(id_trajet,distance);	
	}	
	else if (id_trajet < avl->id_trajet){
		avl->fg = insertion(avl->fg,id_trajet,h,distance);
		*h = -*h;
	}
	else if (id_trajet > avl->id_trajet){
		avl->fd = insertion(avl->fd,id_trajet,h,distance);
	}
	else {
		*h=0;
		return avl;
	
	}
	if (*h != 0){
		avl->eq = avl->eq +*h;
		avl = equilibreAvl(avl);
		if (avl->eq ==0){
			*h=0;
		}
		else {
			*h=1;
		}
	
	}
	return avl;	
}



void infixe(Arbre * avl){	
	if (avl != NULL){
	
		infixe(avl->fg);
		printf("%d", avl->id_trajet);
		infixe(avl->fd);
	
}
}


int main(){

	
	Arbre * avl = NULL;
	float d;
	int id_t;
	int *h;
	printf("hello");
	while(scanf("%d;%f", &id_t,&d) == 2){
		
		Arbre * p = avl; 	
		
		if (recherche(avl,id_t) == NULL){
			avl=insertion(avl,id_t,h,d);
		}
		else {
			p = recherche(avl,id_t);
			p = maj(d,p);
		
		}
		
		
	}
	
	
	
	
	infixe(avl);
	
	
	
	
	
	free(avl);
	


	return 0;
}
