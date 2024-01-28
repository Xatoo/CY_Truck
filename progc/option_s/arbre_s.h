#include<stddef.h>
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



int max(int a,int b);
int min(int a,int b);
int max2(int a,int b,int c);
int min2(int a,int b,int c);
Arbre * creerAvl(unsigned int id_t,float d);
Arbre * rotationGauche(Arbre * avl);
Arbre * recherche(Arbre * avl,int id);
Arbre * rotationDroite(Arbre * avl);
Arbre * rotationDoubleGauche(Arbre * avl);
Arbre * rotationDoubleDroite(Arbre * avl);
Arbre * equilibreAvl(Arbre * avl);
Arbre * insertion(Arbre * avl,int id_trajet,int h,float distance);
void maj(float d,Arbre * avl);
TopValeur* initTopValeur(size_t capacite);
void freeTopValeur(TopValeur* topvaleur);
void insertTopValeur(TopValeur* topvaleur, NoeudInfo value);
void traverseAVL(Arbre* avl, TopValeur* topvaleur);
int compareDecroissant(const void* a, const void* b);
void plusGrandesValeurs(Arbre* avl);
void libererArbre(Arbre * avl);
