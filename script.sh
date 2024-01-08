#!/bin/bash

option_d1() {
    echo "Traitement pour l'option -d1"
    
    cat $chemin_du_fichier | cut -d';' -f1,6 | awk -F';' '!seen[$0]++ {count[$2]+=1} END {for (name in count) print count[name]";"name}' | sort -t';' -k1 -n -r | head -n 10 > demo/demo-d1.csv
   
}

option_d2() {
    echo "Traitement pour l'option -d2"
   
    cat $chemin_du_fichier | cut -d';' -f5,6 | awk -F';' '{count[$2]+=$1} END {for (name in count) print count[name]";"name}' | sort -t';' -r -k1 -n | head -n 10 > demo/demo-d2.csv
    
}

option_l() {
    echo "Traitement pour l'option -l"
   
    cat $chemin_du_fichier | cut -d';' -f1,5| awk -F';' '{count[$1]+=$2} END {for (name in count) print name";"count[name]}' | sort -t';' -k2 -n | tail -10 | sort -k1 -n > demo/demo-l.csv
}

option_t() {
    echo "Traitement pour l'option -t"
    
    gcc progc/option_t.c -o progc/option_t
    if [ $? -ne 0 ] ; then
    echo "Probleme"
    exit 1
    fi

    cat data/data.csv  | tail +2 | cut -d';' -f1,6 | ./progc/option_t
}

option_s() {
    echo "Traitement pour l'option -s"
    gcc -o progc/option_s progc/option_s.c

    cat $chemin_du_fichier | tail +2 | cut -d';' -f1,5| ./progc/option_s > demo/demo-s.csv
}

option_h() {
    echo "-h aide (rtfm)"
   
    echo "    -d1 : conducteurs avec le plus de trajets"
    echo "    -d2 : conducteurs avec la plus grande distance"
    echo "    -l  : les 10 trajets les plus longs"
    echo "    -t  : les 10 villes les plus traversées"
    echo "    -s  : statistiques sur les étapes"
    # Ajoutez l'aide pour l'option -h ici
}

# Vérification des arguments
if [ "$#" -lt 2 ] || [ "$#" -gt 7 ]; then
    echo "Usage: $0 <chemin_du_fichier> <-d1|-d2|-l|-t|-s|-h> [autres arguments...]"
    exit 1
fi

chemin_du_fichier="$1"

if [ ! -f "$chemin_du_fichier" ]; then
    echo "Le fichier $chemin_du_fichier n'existe pas ou n'est pas accessible."
    exit 1
fi

if [ ! -d "temp" ]; then
    mkdir "temp"
    echo "Le répertoire 'temp' a été créé."
else
    echo "Le répertoire 'temp' existe déjà."
 
    if [ "$(ls -A temp)" ]; then
        rm -r temp/*
        echo "Le répertoire 'temp' a été vidé."
    else
        echo "Le répertoire 'temp' est déjà vide."
    fi
fi




# Vérification et création du répertoire 'images'
if [ ! -d "images" ]; then
    mkdir "images"
    echo "Le répertoire 'images' a été créé."
else
    echo "Le répertoire 'images' existe déjà."
fi

for arg in "$@"; do
    if [ "$arg" = "-h" ]; then
        option_h
        exit 0
    fi
done

declare -a options_vu=()

# Variable pour stocker toutes les options différentes
all_different=true

# Traitement des autres arguments
while [ "$#" -gt 0 ]; do
    case "$1" in
        -d1 | -d2 | -l | -t | -s)
            # Vérifier si l'option a déjà été utilisée
            for opt in "${options_vu[@]}"; do
                if [ "$opt" = "$1" ]; then
                    echo "L'option $1 a été utilisée plusieurs fois."
                    exit 1
                fi
            done
            options_vu+=("$1")
            ;;
        *)
            if [ "$1" != "$chemin_du_fichier" ]; then
                echo "Argument non reconnu : $1"
                exit 1
            fi
            ;;
    esac
    shift
done

# Exécution de toutes les options si elles sont toutes différentes
if [ "$all_different" = true ]; then
    for opt in "${options_vu[@]}"; do
        case "$opt" in
            -d1) option_d1 ;;
            -d2) option_d2 ;;
            -l) option_l ;;
            -t) option_t ;;
            -s) option_s ;;
        esac
    done
fi
