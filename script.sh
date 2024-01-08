#!/bin/bash

# Fonction pour l'option -d1
option_d1() {
    echo "Traitement pour l'option -d1"

    # Traitement des données, création du fichier demo/demo-d1.csv
    cat $chemin_du_fichier | cut -d';' -f1,6 | awk -F';' '!seen[$0]++ {count[$2]+=1} END {for (name in count) print count[name]";"name}' | sort -t';' -k1 -n -r | head -n 10 > demo/demo-d1.csv
}

# Fonction pour l'option -d2
option_d2() {
    echo "Traitement pour l'option -d2"

    # Traitement des données, création du fichier demo/demo-d2.csv
    cat $chemin_du_fichier | cut -d';' -f5,6 | awk -F';' '{count[$2]+=$1} END {for (name in count) print count[name]";"name}' | sort -t';' -r -k1 -n | head -n 10 > demo/demo-d2.csv
}

# Fonction pour l'option -l
option_l() {
    echo "Traitement pour l'option -l"

    # Traitement des données, création du fichier demo/demo-l.csv
    cat $chemin_du_fichier | cut -d';' -f1,5 | awk -F';' '{count[$1]+=$2} END {for (name in count) print name";"count[name]}' | sort -t';' -k2 -n | tail -10 | sort -k1 -n > demo/demo-l.csv
}

# Fonction pour l'option -t
option_t() {
    echo "Traitement pour l'option -t"

    # Compilation du programme option_t.c
    gcc progc/option_t.c -o progc/option_t
    if [ $? -ne 0 ]; then
        echo "Erreur lors de la compilation"
        exit 1
    fi

    # Traitement des données, création du fichier demo/demo-t.csv
    cat $chemin_du_fichier | tail +2 | cut -d';' -f1,6 | ./progc/option_t > demo/demo-t.csv
}

# Fonction pour l'option -s
option_s() {
    echo "Traitement pour l'option -s"

    # Compilation du programme option_s.c
    gcc -o progc/option_s progc/option_s.c
    if [ $? -ne 0 ]; then
        echo "Erreur lors de la compilation"
        exit 1
    fi

    # Traitement des données, création du fichier demo/demo-s.csv
    cat $chemin_du_fichier | tail +2 | cut -d';' -f1,5 | ./progc/option_s > demo/demo-s.csv
}

# Fonction pour l'option -h
option_h() {
    echo "-h aide (rtfm)"

    echo "Usage: $0 <chemin_du_fichier> <-d1|-d2|-l|-t|-s|-h> [autres arguments...]"
    echo "    -d1 : conducteurs avec le plus de trajets"
    echo "    -d2 : conducteurs avec la plus grande distance"
    echo "    -l  : les 10 trajets les plus longs"
    echo "    -t  : les 10 villes les plus traversées"
    echo "    -s  : statistiques sur les étapes"
}

# Vérification de l'option d'aide
for arg in "$@"; do
    if [ "$arg" = "-h" ] || [ "$arg" = "--help" ]; then
        option_h
        exit 0
    fi
done

# Vérification du nombre d'arguments
if [ "$#" -lt 2 ] || [ "$#" -gt 7 ]; then
    echo "Nombre d'arguments incorrect"
    exit 1
fi

chemin_du_fichier="$1"

# Vérification de l'existence et de la lisibilité du fichier
if [ ! -r "$chemin_du_fichier" ]; then
    echo "Le fichier $chemin_du_fichier n'existe pas ou n'est pas accessible."
    exit 1
fi

# Création du répertoire temporaire
if [ ! -d "temp" ]; then
    mkdir "temp"
    echo "Le répertoire 'temp' a été créé."
else
    echo "Le répertoire 'temp' existe déjà."

    # Vérification si le répertoire temporaire n'est pas vide
    if [ "$(ls -A temp)" ]; then
        rm -r temp/*
        echo "Le répertoire 'temp' a été vidé."
    else
        echo "Le répertoire 'temp' est déjà vide."
    fi
fi

# Création du répertoire 'images'
if [ ! -d "images" ]; then
    mkdir "images"
    echo "Le répertoire 'images' a été créé."
else
    echo "Le répertoire 'images' existe déjà."
fi

# Initialisation du tableau d'options
options_vu=()
shift

# Traitement des options en ligne de commande
while [ "$#" -gt 0 ]; do
    case "$1" in
    -d1 | -d2 | -l | -t | -s)

        # Vérification des doublons d'options
        for opt in "${options_vu[@]}"; do
            if [ "$opt" = "$1" ]; then
                echo "L'option $1 a été utilisée plusieurs fois."
                exit 1
            fi
        done
        options_vu+=("$1")
        ;;

    *)
        echo "Argument non reconnu : $1"
        exit 1
    esac
    shift
done

# Traitement des options sélectionnées
for opt in "${options_vu[@]}"; do
    case "$opt" in
    -d1) option_d1 ;;
    -d2) option_d2 ;;
    -l) option_l ;;
    -t) option_t ;;
    -s) option_s ;;
    esac
done
