typedef struct _trajet {
  struct _trajet *fg;
  struct _trajet *fd;
  int id_trajet;
  int eq;
} Trajet;

typedef struct _arbre {
  struct _arbre *fg;
  struct _arbre *fd;
  Trajet *pTrajet;
  char nom[35];
  int eq;
  int ville;
  int nb_trajet;
  int nb_trajet_depart;
} Arbre;


int max(int a, int b);
int min(int a, int b);
int max2(int a, int b, int c);
int min2(int a, int b, int c);
Trajet *creerTrajet(int id_trajet);
Arbre *creerArbre(char nom[35], int ville, int id_trajet, int id_depart);
Arbre *rotationGauche(Arbre *avl);
Arbre *rotationDroite(Arbre *avl);
Arbre *rotationDoubleGauche(Arbre *avl);
Arbre *rotationDoubleDroite(Arbre *avl);
Trajet *rotationGauche_trajet(Trajet *trajet);
Trajet *rotationDroite_trajet(Trajet *trajet);
Trajet *rotationDoubleGauche_trajet(Trajet *trajet);
Trajet *rotationDoubleDroite_trajet(Trajet *trajet);
Arbre *equilibreAvl(Arbre *avl);
Trajet *equilibreTrajet(Trajet *trajet);
Arbre *insertion(Arbre *avl, char nom[35], int ville, int id_trajet, int id_depart, int *h);
Trajet *insertion_trajet(Trajet *trajet, int id_trajet, int *h);
Arbre *recherche(Arbre *avl, int id);
Trajet *recherche_trajet(Trajet *trajet, int id);
void maj_arbre(Arbre *avl, int id_trajet, int id_etape);
void trouverTop10(Arbre *arbre, Arbre *top[], int *index);
void trierListe(Arbre *top[], int taille);
void afficherTop10(Arbre *avl);
void libererMemoireTrajet(Trajet *trajet);
void libererMemoireArbre(Arbre *avl);
int comparerChaines(const char *chaine1, const char *chaine2);
unsigned int hash(char *str);
