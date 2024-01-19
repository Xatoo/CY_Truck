
#include<stddef.h>
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

void maj(float d,Arbre * avl);
TopValeur* initTopValeur(size_t capacite);
void freeTopValeur(TopValeur* topvaleur);
void insertTopValeur(TopValeur* topvaleur, NoeudInfo value);
void traverseAVL(Arbre* avl, TopValeur* topvaleur);
int compareDecroissant(const void* a, const void* b);
void plusGrandesValeurs(Arbre* avl);
