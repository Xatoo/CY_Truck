#!/bin/bash

chemin_opt_d1="demo/demo-d1.csv"
chemin_opt_d2="demo/demo-d2.csv"
chemin_opt_l="demo/demo-l.csv"
chemin_opt_t="demo/demo-t.csv"
chemin_opt_s="demo/demo-s.csv"

chemin_img_d1="images/image-d1.png"
chemin_img_d2="images/image-d2.png"
chemin_img_l="images/image-l.png"
chemin_img_t="images/image-t.png"
chemin_img_s="images/image-s.png"

affiche="false"


# Fonction pour l'option -d1
option_d1() {
    echo "Traitement pour l'option -d1"

    # Traitement des données, création du fichier demo/demo-d1.csv
    time cat $chemin_du_fichier | tail +2 | cut -d';' -f1,6 | awk -F';' '!seen[$0]++ {count[$2]+=1} END {for (name in count) print count[name]";"name}' | sort -t';' -k1 -n -r | head -n 10 > $chemin_opt_d1
    
    gnuplot <<EOF
reset
set size square 1,1.1
set term png size 600,800
set grid y
set datafile separator ";"
set style fill solid border -1
set boxwidth 1.5 relative

set xlabel "Conducteurs" rotate by 90 offset -30,2
set x2label "Trajets" rotate by 90 offset 28,2 
set ylabel "Conducteurs avec le plus de trajets" font '0,15' offset 2,0
set xtic rotate by 90 font '0,10' offset 0,-9.5
set ytics rotate by 90 font '0,11' offset 59,1
set style data histograms

set output '$chemin_img_d1'
plot "$chemin_opt_d1" using 1:xticlabels(2) notitle lc rgb "purple"
EOF

    convert -rotate 90 $chemin_img_d1 $chemin_img_d1
    if [ $affiche = "true" ]; then
        display "$chemin_img_d1" &
    fi
    
    echo ""
    echo "Le traitement s'est bien passé. Le graphique a été enregistré dans 'images/image-d1.png'."
}

# Fonction pour l'option -d2
option_d2() {
    echo "Traitement pour l'option -d2"

    # Traitement des données, création du fichier demo/demo-d2.csv
    time cat $chemin_du_fichier | cut -d';' -f5,6 | LC_NUMERIC=C awk -F';' '{count[$2]+=$1} END {for (name in count) printf "%.3f;%s\n", count[name], name}' | sort -t';' -r -k1 -n | head -n 10 > $chemin_opt_d2


    gnuplot <<EOF
reset
set size square 1,1.1
set term png size 600,820
set grid y
set datafile separator ";"
set style fill solid border -1
set boxwidth 1.5 relative

set xlabel "Conducteurs" rotate by 90 offset -30,2
set x2label "Distance (km)" rotate by 90 offset 28,3 
set ylabel "Conducteurs et la plus grande distance" font '0,15' offset 2,0
set xtic rotate by 90 font '0,10' offset 0,-9.5
set ytics rotate by 90 font '0,11' offset 59,1
set style data histograms

set output '$chemin_img_d2'
plot "$chemin_opt_d2" using 1:xticlabels(2) notitle lc rgb "orange"
EOF
    convert -rotate 90 $chemin_img_d2 $chemin_img_d2
    if [ $affiche = "true" ]; then
        display "$chemin_img_d2" &
    fi
    
    echo ""
    echo "Le traitement s'est bien passée."
}

# Fonction pour l'option -l
option_l() {
    echo "Traitement pour l'option -l"

    # Traitement des données, création du fichier demo/demo-l.csv
    time cat "$chemin_du_fichier" | tail +2 | cut -d';' -f1,5 | awk -F';' '{count[$1]+=$2} END {for (name in count) print name";"count[name]}' | sort -t';' -k2 -n | tail -10 | sort -t';' -k1 -n > "$chemin_opt_l"

    gnuplot <<EOF
reset
set term png
set title 'Les 10 trajets les plus longs' font '0,15'
set xlabel "Identifiants Trajets" 
set ylabel "Distances (km)"

set datafile separator ";"
set style data histograms
set style fill solid border -1
set boxwidth 1.5 relative
set xtic rotate by -45
set output '$chemin_img_l'
plot "$chemin_opt_l" using 2:xtic(1) lc rgb "red" notitle
EOF

    if [ $affiche = "true" ]; then
        display "$chemin_img_l" &
    fi
    echo ""
    echo "Le traitement s'est bien passée."
}

# Fonction pour l'option -t
option_t() {

    # Compilation du programme option_t.c
    gcc -o progc/option_t progc/option_t.c
    if [ $? -ne 0 ]; then
        echo "Erreur lors de la compilation"
        exit 1
    else 
    	echo "La compilation s'est bien passée."
    fi
    
    echo "Traitement pour l'option -t"
    # Traitement des données, création du fichier demo/demo-t.csv
    time cat $chemin_du_fichier | tail +2 | cut -d';' -f1,2,3,4 | ./progc/option_t > $chemin_opt_t
    
    code_sortie=$?

    if [ $code_sortie -eq 0 ]; then
        echo ""
        echo "Le traitement s'est bien passée."
    else
        echo "Il y a eu une erreur avec un code de sortie $code_sortie."
        exit 1
    fi
    
    gnuplot <<EOF
reset
set term png
set title 'Les 10 villes les plus traversées' font '0,15'
set datafile separator ";"
set grid
set xlabel "Villes"
set ylabel "Nombres de trajets"
set style data histograms
set style histogram cluster gap 1
set style fill solid border -1
set boxwidth 1.5
set xtic rotate by -45
set output '$chemin_img_t'
plot "$chemin_opt_t" using 2:xtic(1) title 'Trajet' lc rgb "blue", \
     "" using 3:x2tic(1) title 'Ville de départ' lc rgb "green"
EOF
    
    if [ $affiche = "true" ]; then
        display "$chemin_img_t" &
    fi
}

# Fonction pour l'option -s
option_s() {

    # Compilation du programme option_s.c
    gcc -o progc/option_s progc/option_s.c
    if [ $? -ne 0 ]; then
        echo "Erreur lors de la compilation"
        exit 1
    else 
    	echo "La compilation s'est bien passée."
    fi

    echo "Traitement pour l'option -s"
    # Traitement des données, création du fichier demo/demo-s.csv
    time cat $chemin_du_fichier | tail +2 | cut -d';' -f1,5 | ./progc/option_s > $chemin_opt_s
    
    code_sortie=$?

    if [ $code_sortie -eq 0 ]; then
        echo ""
        echo "Le traitement s'est bien passée."
    else
        echo "Il y a eu une erreur avec un code de sortie $code_sortie."
        exit 1
    fi
    
    gnuplot <<EOF
set term pngcairo enhanced font 'arial,10'

set datafile separator ";"
set xtic rotate by 45 font '0,6' offset -2,-1.5
set xlabel "Identifiants Trajets"
set ylabel "Distance (km)"
set xlabel "Identifiants Trajets"
set title 'Statistiques sur les étapes' font '0,15'

set output '$chemin_img_s'
plot "$chemin_opt_s" using 2:xtic(3) with filledcurves above fillcolor rgb '#E6ADAD' title 'Distance moyenne' lt rgb '#E6ADAD', \
     '' u 3:xtic(1) w filledcurves above fillcolor rgb '#FFFFFF' notitle lt rgb '#FFFFFF', \
     '' u 4:xtic(1) w l lw 2 title 'Moyenne', \
     '' u 2:xtic(1) w l lc rgb "white" lw 2 notitle, \
     '' u 3:xtic(1) w l lc rgb "white" lw 2 notitle

EOF
    if [ $affiche = "true" ]; then
        display "$chemin_img_s" &
    fi
}

# Fonction pour l'option -h
option_h() {

    echo "Usage: $0 FICHIER OPTION..."
    echo "Chaque option est traité indépendament"
    echo "    -d1 	    : conducteurs avec le plus de trajets"
    echo "    -d2 	    : conducteurs avec la plus grande distance"
    echo "    -l  	    : les 10 trajets les plus longs"
    echo "    -t  	    : les 10 villes les plus traversées"
    echo "    -s  	    : statistiques sur les étapes"
    echo ""
    echo "Exemple: $0 user/fichier.csv -d1"
    echo ""
    echo "Utilitaire:"    
    echo "    -a, --afficher : permet l'affichage automatique pour toute les options"
    echo "    -h, --help      : afficher cette aide et quitter"
    echo "    -v, --version   : afficher cette version et quitter"
    echo ""
    echo "Aide en ligne sur Github : <https://github.com/Xatoo/CY_Truck>"
}

# Fonction pour l'option -v
option_v() {

    echo "$0 (Cy PreIng2 MI5-H) Version 1.2"
    echo "Ceci est un logiciel libre. Vous êtes libre de le modifier et de le redistribuer."
    echo "Ce logiciel n'est accompagné d'ABSOLUMENT AUCUNE GARANTIE, dans les limites permises par la loi."
    echo ""
    echo "Écrit par Hugo Delhelle, Lucas Matthes et Matheo Costa."
}

# Vérification de l'option d'aide ou de l'option version
for arg in "$@"; do
    if [ "$arg" = "-h" ] || [ "$arg" = "--help" ]; then
        option_h
        exit 0
    fi
    if [ "$arg" = "-v" ] || [ "$arg" = "--version" ]; then
        option_v
        exit 0
    fi
done

# Vérification du nombre d'arguments
if [ "$#" -lt 2 ]; then
    echo "Nombre d'arguments incorrect"
    exit 1
fi

chemin_du_fichier="$1"

# Vérification de l'existence et de la lisibilité du fichier
if [ ! -r "$chemin_du_fichier" ]; then
    echo "Le fichier $chemin_du_fichier n'existe pas ou n'est pas accessible."
    exit 1
fi

# Initialisation du tableau d'options
options_vu=()
shift

# Vérification des options
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
    -a | --afficher)
        affiche="true"
        ;;
    *)
        echo "Argument non reconnu : $1"
        exit 1
    esac
    shift
done

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

echo ""

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

echo "L'exécution s'est bien passée."
