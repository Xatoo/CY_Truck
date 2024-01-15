
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

int max(int a,int b);
int min(int a,int b);
int max2(int a,int b,int c);
int min2(int a,int b,int c);
Arbre * creerAvl(unsigned int id_t,float d);
Arbre * rotationGauche(Arbre * avl);
Arbre * rotationDroite(Arbre * avl);
Arbre * rotationDoubleGauche(Arbre * avl);
Arbre * rotationDoubleDauche(Arbre * avl);
Arbre * recherche(Arbre * avl,int id);
Arbre * equilibreAvl(Arbre * avl);
Arbre * insertion(Arbre * avl,int id_trajet,int h,float distance);
