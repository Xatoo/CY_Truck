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
	float diff;
	

}Arbre;


typedef struct {
	int id_trajet;
	float max;
	float min;
	float moy;
	float diff;
} NoeudInfo;

typedef struct {
	NoeudInfo* v;
	size_t comp;
	size_t capacite;
} TopValeur;


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

Arbre * creerAvl(unsigned int id_t,float d){
	Arbre * avl = malloc(sizeof(Arbre));
	avl->id_trajet = id_t;
	avl->distance = d;
	avl->fg = NULL;
	avl->fd = NULL;
	avl->eq = 0;
	avl->min = d;
	avl->max = d;
	avl->som = d;
	avl->compteur = 1;
	avl->moy =d;
	avl->diff=0;
	
	return avl;
}

void maj(float d,Arbre * avl){
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
		avl->diff = avl->max - avl->min;
		
	}
	
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
Arbre * recherche(Arbre * avl,int id){
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


Arbre * insertion(Arbre * avl,int id_trajet,int h,float distance){
	if (avl == NULL){
		h=1;
		return creerAvl(id_trajet,distance);	
	}	
	else if (id_trajet < avl->id_trajet){
			
		avl->fg = insertion(avl->fg,id_trajet,h,distance);
		h = -h;
	}
	else if (id_trajet > avl->id_trajet){
			
		avl->fd = insertion(avl->fd,id_trajet,h,distance);
	}
	else {
		h=0;
		return avl;
	
	}
	
	if (h != 0){
		
		avl->eq = avl->eq +h;
		avl = equilibreAvl(avl);
		if (avl->eq ==0){
			h=0;
		}
		else {
			h=1;
		}
	
	}
	return avl;	
}




TopValeur* initTopValeur(size_t capacite) {
	TopValeur* topvaleur = malloc(sizeof(TopValeur));
	topvaleur->v = malloc(capacite * sizeof(NoeudInfo));
	topvaleur->comp = 0;
	topvaleur->capacite = capacite;
	return topvaleur;
}

void freeTopValeur(TopValeur* topvaleur) {
	free(topvaleur->v);
	free(topvaleur);
}


void insertTopValeur(TopValeur* topvaleur, NoeudInfo value) {
	if (topvaleur->comp < topvaleur->capacite || value.diff > topvaleur->v[topvaleur->comp - 1].diff) {
		size_t i = topvaleur->comp;
		while (i > 0 && value.diff > topvaleur->v[i - 1].diff) {
			if (i < topvaleur->capacite) {
				topvaleur->v[i] = topvaleur->v[i - 1];
			}
			i--;
		}

		if (i < topvaleur->capacite) {
			topvaleur->v[i] = value;
		}

		if (topvaleur->comp < topvaleur->capacite) {
			topvaleur->comp++;
		}
	}
}





void traverseAVL(Arbre* avl, TopValeur* topvaleur) {
	if (avl != NULL) {
		traverseAVL(avl->fd, topvaleur);

		NoeudInfo NoeudInfo;
		NoeudInfo.id_trajet = avl->id_trajet;
		NoeudInfo.max = avl->max;
		NoeudInfo.min = avl->min;
		NoeudInfo.moy = avl->moy;
		NoeudInfo.diff = avl->diff;

		insertTopValeur(topvaleur, NoeudInfo);

		traverseAVL(avl->fg, topvaleur);
	}
}

int compareDecroissant(const void* a, const void* b) {
	float diffA = ((NoeudInfo*)a)->diff;
	float diffB = ((NoeudInfo*)b)->diff;

	if (diffA < diffB) {
		return 1;
	}
	else if (diffA > diffB) {
		return -1;
	}
	else {
		return 0;
	}
}


void plusGrandesValeurs(Arbre* avl) {
	size_t capacite = 50;
	TopValeur* topvaleur = initTopValeur(capacite);
	traverseAVL(avl, topvaleur);
	qsort(topvaleur->v, topvaleur->comp, sizeof(NoeudInfo), compareDecroissant);
	for (size_t i = 0; i < topvaleur->comp; i++) {
		printf("%d;%f;%f;%f;%f\n",topvaleur->v[i].id_trajet,
			topvaleur->v[i].max, topvaleur->v[i].min,
			topvaleur->v[i].moy, topvaleur->v[i].diff);
	}
	freeTopValeur(topvaleur);
}

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
	free(avl);

	return 0;
}
