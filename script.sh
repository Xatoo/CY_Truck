#!/bin/bash

option_d1() {
    echo "Traitement pour l'option -d1"
    #cat data/test.txt| cut -d';' -f1,6 > temp/temp.txt
    #sort -t';' -k6,6 -k5,5n data/test.txt > temp/temp.txt
    cat data/test.txt | cut -d';' -f1,6 | sort -t';' -k2,2 -k1,1n > temp/temp.txt
   
    awk -F';' 'NR==1{prev=$0; print $0} NR>1 && $0!=prev{prev=$0; print $0}' temp/temp.txt > temp/temp2.txt
   
    awk -F';' '{nom=$2" "$3; noms[nom]++} END {for (nom in noms) print nom";"noms[nom]}' temp/temp2.txt > temp/temp3.txt
   
   sort -t';' -k2 temp/temp3.txt > temp/temp4.txt
   
   tail -n 5 temp/temp4.txt > demo/demo-d1.txt
   
}

option_d2() {
    echo "Traitement pour l'option -d2"
   
    cat data/test.txt | cut -d';' -f5,6 | sort -t';' -k2,2 -k1,1n > temp/temp.txt
   
    awk -F';' '{count[$2]+=$1} END {for (name in count) print count[name]";"name}' temp/temp.txt > temp/temp2.txt
   
    sort -t';' -k1 -n temp/temp2.txt > temp/temp3.txt
    
    tail -n 5 temp/temp3.txt > demo/demo-d2.txt
}

option_l() {
    echo "Traitement pour l'option -l"
   
    cat data/test.txt | cut -d';' -f1,5 | sort -t';' -k1 > temp/temp.txt
   
    awk -F';' '{count[$1]+=$2} END {for (name in count) print name";"count[name]}' temp/temp.txt > temp/temp2.txt
   
   sort -t';' -k2 -n temp/temp2.txt > temp/temp3.txt
   
   tail -n 5 temp/temp3.txt > temp/temp4.txt
   
   sort -t';' -k1 -n temp/temp4.txt > demo/demo-t.txt
}

option_t() {
    echo "Traitement pour l'option -t"
    cat data/test.txt  | cut -d';' -f3,4,6,7 > temp/temp.txt
}

option_s() {
    echo "Traitement pour l'option -s"
 
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

declare -a options_seen=()

# Variable pour stocker toutes les options différentes
all_different=true

# Traitement des autres arguments
while [ "$#" -gt 0 ]; do
    case "$1" in
        -d1 | -d2 | -l | -t | -s)
            # Vérifier si l'option a déjà été utilisée
            for opt in "${options_seen[@]}"; do
                if [ "$opt" = "$1" ]; then
                    echo "L'option $1 a été utilisée plusieurs fois."
                    exit 1
                fi
            done
            options_seen+=("$1")
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
    for opt in "${options_seen[@]}"; do
        case "$opt" in
            -d1) option_d1 ;;
            -d2) option_d2 ;;
            -l) option_l ;;
            -t) option_t ;;
            -s) option_s ;;
        esac
    done
fi
