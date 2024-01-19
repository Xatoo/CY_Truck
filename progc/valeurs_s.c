#include"avl_s.h"
#include"valeurs_s.h"
#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>


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

