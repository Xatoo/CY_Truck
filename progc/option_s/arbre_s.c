#include"arbre_s.h"
#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>

//Fonction qui renvoie la plus grande valeur entre deux entiers passer en paramètre
int max(int a,int b){
	return (a>b)? a:b;
}
//Fonction qui renvoie la plus petite valeur entre deux entiers passer en paramètre
int min(int a,int b){
	return (a<b)? a:b;
}
//Fonction qui renvoie la plus grande valeur entre trois entiers passer en paramètre
int max2(int a,int b,int c){
	return max(max(a,b),c);
}
//Fonction qui renvoie la plus petite valeur entre trois entiers passer en paramètre
int min2(int a,int b,int c){
	return min(min(a,b),c);
}
//Fonction de création d'un nouveau noeud AVL
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

//Rotation simple à gauche pour l'équilibrage de l'AVL
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
//Fonction de recherche d'un noeud AVL avec un certain id
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
//Rotation simple à droite pour l'équilibrage de l'AVL
Arbre * rotationDroite(Arbre * avl){
	Arbre * pivot = avl->fg;
	avl->fg = pivot->fd;
	pivot->fd = avl;
	
	int eq_avl = avl->eq;
	int eq_piv = pivot->eq;
	
	avl->eq = eq_avl - min(eq_piv,0) +1;
	pivot->eq = max2(eq_avl+2,eq_avl+eq_piv+2,eq_piv+1);
	avl = pivot;
	return avl;

}
//Rotation double à gauche pour l'équilibrage de l'AVL
Arbre * rotationDoubleGauche(Arbre * avl){
	avl->fd = rotationDroite(avl->fd);
	return rotationGauche(avl);
	


}
//Rotation double à droite pour l'équilibrage de l'AVL
Arbre * rotationDoubleDroite(Arbre * avl){
	avl->fd = rotationGauche(avl->fg);
	return rotationDroite(avl);

}
//fonction pour équilibrer l'AVL
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
//Fonction pour inserer un noeud AVL
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

//Mise à jour des statistiques d'un noeud AVL
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



//Initialise la structure TopValeur avec une capacité donnée
TopValeur* initTopValeur(size_t capacite) {
	TopValeur* topvaleur = malloc(sizeof(TopValeur));
	topvaleur->v = malloc(capacite * sizeof(NoeudInfo));
	topvaleur->comp = 0;
	topvaleur->capacite = capacite;
	return topvaleur;
}
//libère la memoire alloué pour la structure TopValeur
void freeTopValeur(TopValeur* topvaleur) {
	free(topvaleur->v);
	free(topvaleur);
}

//Insere une valeur dans le top des valeurs;
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




//Parcour l'AVL et insère les informations dans le top des valeurs
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

//Fonction de comparaison pour le tri decroissant du tableau top valeur
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

//Affiche les plus grandes valeurs du top des valeurs
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

//libère la mémoire alloué pour l'arbre AVL
void libererArbre(Arbre * avl){
	if(avl!=NULL){
		libererArbre(avl->fg);
		libererArbre(avl->fd);
		free(avl);
	
	}
	

}
