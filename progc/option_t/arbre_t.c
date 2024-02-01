#include "arbre_t.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>



int max(int a, int b) { return (a > b) ? a : b; }  //renvoie la plus grande valeur entre deux entiers passer en paramètre
int min(int a, int b) { return (a < b) ? a : b; }  //renvoie la plus petite valeur entre deux entiers passer en paramètre

int max2(int a, int b, int c) { return max(max(a, b), c); }  //renvoie la plus grande valeur entre trois entiers passer en paramètre

int min2(int a, int b, int c) { return min(min(a, b), c); }  //renvoie la plus petite valeur entre trois entiers passer en paramètre

//Fonction pour créer un nouveau noeud Trajet dans l'arbre
Trajet *creerTrajet(int id_trajet) { 
 //Allocation de mémoire pour le Trajet
  Trajet *trajet = malloc(sizeof(Trajet));
  if (trajet==NULL){
  	exit(1);
  }
  //Initialisation des champs du Trajet
  trajet->id_trajet = id_trajet;
  trajet->fg = NULL;
  trajet->fd = NULL;
  trajet->eq = 0;

  return trajet;
}
// Fonction pour créer un nouvel arbre AVL
Arbre *creerArbre(char nom[35], int ville, int id_trajet, int id_depart) {
  // Allocation de mémoire pour l'arbre
  Arbre *avl = malloc(sizeof(Arbre));
  if (avl==NULL){
  	exit(1);
  }
   // Initialisation des champs de l'arbre
  avl->ville = ville;
  strncpy(avl->nom, nom, sizeof(avl->nom) - 1);
  avl->eq = 0;
  avl->nb_trajet = 1;
  if (id_depart == 1) {
    avl->nb_trajet_depart = 1;
  }
  // Création du premier noeud Trajet dans l'arbre
  avl->pTrajet = creerTrajet(id_trajet);
  avl->fg = NULL;
  avl->fd = NULL;
  return avl;
}
// Fonction pour effectuer une rotation gauche dans l'arbre AVL
Arbre *rotationGauche(Arbre *avl) {
  // Rotation gauche entre avl et son sous-arbre droit (pivot)
  Arbre *pivot = avl->fd;
  avl->fd = pivot->fg;
  pivot->fg = avl;
  // Mise à jour des facteurs d'équilibre après la rotation
  int eq_avl = avl->eq;
  int eq_piv = pivot->eq;

  avl->eq = eq_avl - max(eq_piv, 0) - 1;
  pivot->eq = min2(eq_avl - 2, eq_avl + eq_piv - 2, eq_piv - 1);
  avl=pivot;
  return avl;
}
// Fonction pour effectuer une rotation droite dans l'arbre AVL
Arbre *rotationDroite(Arbre *avl) {
  // Rotation droite entre avl et son sous-arbre gauche
  Arbre *pivot = avl->fg;
  avl->fg = pivot->fd;
  pivot->fd = avl;
   // Mise à jour des facteurs d'équilibre après la rotation
  int eq_avl = avl->eq;
  int eq_piv = pivot->eq;

  avl->eq = eq_avl - min(eq_piv, 0) + 1;
  pivot->eq = max2(eq_avl + 2, eq_avl + eq_piv + 2, eq_piv + 1);
  avl=pivot;
  return avl;
}
// Fonction pour effectuer une double rotation gauche-droite dans l'arbre AVL
Arbre *rotationDoubleGauche(Arbre *avl) {
  avl->fd = rotationDroite(avl->fd);
  return rotationGauche(avl);
}
// Fonction pour effectuer une double rotation droite-gauche dans l'arbre AVL
Arbre *rotationDoubleDroite(Arbre *avl) {
  avl->fg = rotationGauche(avl->fg);
  return rotationDroite(avl);
}
// Fonction pour effectuer une rotation gauche dans le sous-arbre Trajet
Trajet *rotationGauche_trajet(Trajet *trajet) {
  // Rotation gauche entre trajet et son sous-arbre droit (pivot)
  Trajet *pivot = trajet->fd;
  trajet->fd = pivot->fg;
  pivot->fg = trajet;
   // Mise à jour des facteurs d'équilibre après la rotation
  int eq_trajet = trajet->eq;
  int eq_piv = pivot->eq;

  trajet->eq = eq_trajet - max(eq_piv, 0) - 1;
  pivot->eq = min2(eq_trajet - 2, eq_trajet + eq_piv - 2, eq_piv - 1);
  trajet=pivot;
  return trajet;
}
// Fonction pour effectuer une rotation droite dans le sous-arbre Trajet
Trajet *rotationDroite_trajet(Trajet *trajet) {
  // Rotation droite entre trajet et son sous-arbre gauche (pivot)
  Trajet *pivot = trajet->fg;
  trajet->fg = pivot->fd;
  pivot->fd = trajet;
  // Mise à jour des facteurs d'équilibre après la rotation
  int eq_trajet = trajet->eq;
  int eq_piv = pivot->eq;

  trajet->eq = eq_trajet - min(eq_piv, 0) + 1;
  pivot->eq = max2(eq_trajet + 2, eq_trajet + eq_piv + 2, eq_piv + 1);
  trajet=pivot;
  return trajet;
}
// Fonction pour effectuer une double rotation gauche-droite dans le sous-arbre Trajet
Trajet *rotationDoubleGauche_trajet(Trajet *trajet) {
  trajet->fd = rotationDroite_trajet(trajet->fd);
  return rotationGauche_trajet(trajet);
}
// Fonction pour effectuer une double rotation droite-gauche dans le sous-arbre Trajet
Trajet *rotationDoubleDroite_trajet(Trajet *trajet) {
  trajet->fg = rotationGauche_trajet(trajet->fg);
  return rotationDroite_trajet(trajet);
}
// Fonction pour rééquilibrer l'arbre AVL après une insertion
Arbre *equilibreAvl(Arbre *avl) {
  if (avl->eq >= 2) {
    if (avl->fd->eq >= 0) {
      avl = rotationGauche(avl);
    } else {
      avl = rotationDoubleGauche(avl);
    }
  } else if (avl->eq <= -2) {
    if (avl->fg->eq <= 0) {
      avl = rotationDroite(avl);
    } else {
      avl = rotationDoubleDroite(avl);
    }
  }
  return avl;
}
// Fonction pour rééquilibrer le sous-arbre Trajet après une insertion
Trajet *equilibreTrajet(Trajet *trajet) {
  if (trajet->eq >= 2) {
    if (trajet->fd->eq >= 0) {
      return rotationGauche_trajet(trajet);
    } else {
      return rotationDoubleGauche_trajet(trajet);
    }
  } else if (trajet->eq <= -2) {
    if (trajet->fg->eq <= 0) {
      return rotationDroite_trajet(trajet);
    } else {
      return rotationDoubleDroite_trajet(trajet);
    }
  }
  return trajet;
}
// Fonction pour insérer un nouvel élément dans l'arbre AVL
Arbre *insertion(Arbre *avl, char nom[35], int ville, int id_trajet, int id_depart, int *h) {
    if (avl == NULL) {
      // L'arbre est vide, on crée un nouveau noeud
        *h = 1;
        return creerArbre(nom, ville, id_trajet, id_depart);
    } else if (ville < avl->ville) {
       // Insertion dans le sous-arbre gauche
        avl->fg = insertion(avl->fg, nom, ville, id_trajet, id_depart, h);
        avl->eq--;
        avl = equilibreAvl(avl);
    } else if (ville > avl->ville) {
       // Insertion dans le sous-arbre droit
        avl->fd = insertion(avl->fd, nom, ville, id_trajet, id_depart, h);
        avl->eq++;
        avl = equilibreAvl(avl);
    } else {
         // La ville existe déjà dans l'arbre
        *h = 0;
    }
    
    return avl;
}

// Fonction pour insérer un nouveau Trajet dans le sous-arbre Trajet
Trajet *insertion_trajet(Trajet *trajet, int id_trajet, int *h) {
    if (trajet == NULL) {
       // Le sous-arbre Trajet est vide, on crée un nouveau Trajet
        *h = 1;
        return creerTrajet(id_trajet);
    } else if (id_trajet < trajet->id_trajet) {
      // Insertion dans le sous-arbre gauche du Trajet
        trajet->fg = insertion_trajet(trajet->fg, id_trajet, h);
        trajet->eq--;
        trajet = equilibreTrajet(trajet);
    } else if (id_trajet > trajet->id_trajet) {
      // Insertion dans le sous-arbre droit du Trajet
        trajet->fd = insertion_trajet(trajet->fd, id_trajet, h);
        trajet->eq++;
        trajet = equilibreTrajet(trajet);
    } else {
       // Le Trajet existe déjà dans le sous-arbre Trajet
        *h = 0;
    }
    
    return trajet;
}
// Fonction pour rechercher un élément dans l'arbre AVL
Arbre *recherche(Arbre *avl, int id) {
  if (avl == NULL) {
     // L'arbre est vide, l'élément n'est pas trouvé
    return NULL;
  } else if (avl->ville == id) {
    // L'élément est trouvé dans le noeud actuel
    return avl;
  } else if (id < avl->ville) {
     // Recherche dans le sous-arbre gauche
    return recherche(avl->fg, id);
    
  } else {
    // Recherche dans le sous-arbre droit
    return recherche(avl->fd, id);
  }
}
// Fonction pour rechercher un Trajet dans le sous-arbre Trajet
Trajet *recherche_trajet(Trajet *trajet, int id) {
  if (trajet == NULL) {
     // Le sous-arbre Trajet est vide, le Trajet n'est pas trouvé
    return NULL;
  } else if (trajet->id_trajet == id) {
    // Le Trajet est trouvé dans le noeud actuel du sous-arbre Trajet
    return trajet;
  } else if (id < trajet->id_trajet) {
    // Recherche dans le sous-arbre gauche du Trajet
    return recherche_trajet(trajet->fg, id);
  } else {
    // Recherche dans le sous-arbre droit du Trajet
    return recherche_trajet(trajet->fd, id);
  }
}
// Fonction pour mettre à jour l'arbre AVL après l'ajout d'un Trajet
void maj_arbre(Arbre *avl, int id_trajet, int id_etape) {
  if (avl != NULL) {
    // Mise à jour du nombre de trajets au départ de cette ville
    if (id_etape == 1) {
      avl->nb_trajet_depart += 1;
    }
     // Recherche du Trajet dans le sous-arbre Trajet
    if (recherche_trajet(avl->pTrajet, id_trajet) == NULL) {
      // Le Trajet n'existe pas, on l'ajoute dans le sous-arbre Trajet
      int h = 0;
      avl->pTrajet = insertion_trajet(avl->pTrajet, id_trajet, &h);
      avl->nb_trajet += 1;
    }
  }
}
// Fonction pour trouver les 10 villes avec le plus grand nombre de trajets
void trouverTop10(Arbre *arbre, Arbre *top[], int *index) {
  if (arbre == NULL) {
    // L'arbre est vide, on retourne
    return;
  }
  // Parcours en ordre décroissant (droite - racine - gauche)
  trouverTop10(arbre->fd, top, index);
  // Ajout de l'élément actuel dans le tableau top si possible
  if (*index <10) {
    top[*index] = arbre;
    (*index)++;
  } else {
    // Si le tableau est plein, recherche et remplacement du minimum
    int minIndex = 0;
    for (int i = 1; i <10; i++) {
      if (top[i]->nb_trajet < top[minIndex]->nb_trajet) {
        minIndex = i;
      }
    }
     // Remplacement du minimum si l'élément actuel a un nombre de trajets supérieur
    if (arbre->nb_trajet > top[minIndex]->nb_trajet) {
      top[minIndex] = arbre;
    }
  }
  // Parcours en ordre décroissant du sous-arbre gauche
  trouverTop10(arbre->fg, top, index);
}
// Fonction de hachage pour une chaîne de caractères
unsigned int hash(char *str) {
  unsigned int hash = 5381;
  int c;

  while ((c = *str++)) {
    hash = ((hash << 5) + hash) + c;
  }
  return hash;
}


// Fonction pour comparer deux chaînes de caractères, en ignorant les espaces
int comparerChaines(const char *chaine1, const char *chaine2) {
  while (*chaine1 && *chaine2) {

    if (*chaine1 == ' ') {
      chaine1++;
      continue;
    }
    if (*chaine2 == ' ') {
      chaine2++;
      continue;
    }

    if (*chaine1 < *chaine2) {
      return -1;
    } else if (*chaine1 > *chaine2) {
      return 1;
    }

    chaine1++;
    chaine2++;
  }

  if (*chaine1) {
    return 1;
  } else if (*chaine2) {
    return -1;
  }

  return 0;
}
// Fonction de tri pour le tableau top en fonction des noms de villes
void trierListe(Arbre *top[], int taille) {
  int i, j;
  Arbre *temp;

  for (i = 0; i < taille - 1; i++) {
    for (j = 0; j < taille - 1 - i; j++) {
      if (top[j] != NULL && top[j + 1] != NULL && comparerChaines(top[j]->nom, top[j + 1]->nom) > 0) {

        temp = top[j];
        top[j] = top[j + 1];
        top[j + 1] = temp;
      }
    }
  }
}

// Fonction pour afficher les 10 villes avec le plus grand nombre de trajets
void afficherTop10(Arbre *avl) {
  Arbre *top[10];
  for (int i = 0; i <10; i++) {
    top[i] = NULL;
  }

  int index = 0;
  trouverTop10(avl, top, &index);

  trierListe(top,10);

  for (int i = 0; i <10; i++) {
    if (top[i] != NULL) {
      printf("%s;%d;%d\n",  top[i]->nom,top[i]->nb_trajet,top[i]->nb_trajet_depart);
    }
  }
}
// Fonction pour libérer la mémoire occupée par le sous-arbre Trajet
void libererMemoireTrajet(Trajet *trajet) {
  if (trajet != NULL) {
    // Libération récursive de la mémoire pour le sous-arbre Trajet
    libererMemoireTrajet(trajet->fg);
    libererMemoireTrajet(trajet->fd);
    free(trajet);
  }
}
// Fonction pour libérer la mémoire occupée par l'arbre AVL
void libererMemoireArbre(Arbre *avl) {
  if (avl != NULL) {
   // Libération récursive de la mémoire pour le sous-arbre Trajet
   libererMemoireTrajet(avl->pTrajet);
     // Libération récursive de la mémoire pour les sous-arbres gauche et droit
    libererMemoireArbre(avl->fg);
    libererMemoireArbre(avl->fd);
   // Libération de la mémoire pour le noeud actuel
    
    free(avl);
  }
}

