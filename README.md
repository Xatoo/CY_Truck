# CY_Truck

Afin d'utiliser l'application, veuillez vous rendre depuis le terminal dans le dossier contenant le fichier script.sh, vous pouvez utiliser la commande suivante :

bash script.sh chemin_fichier -option1 -option2 ...

Sinon vous pouvez les droits d'exécution, avec cette commande:

chmod +x script.sh

Maintenant, l'application est prête à être exécutée. La compilation des fichiers nécessaire au fonctionnement de l'application se fait au début de l'exécution du script. En cas de problème, un message d'erreur s'affichera.

Pour l'exécuter, utilisez la commande :

./script.sh chemin_fichier -option1 -option2 ...

Les options sont indiquées si vous utilisez l'option -h (aide), qui détaille le résultat de chaque option. Si vous entrez l'option d'aide (-h) ou de version (-v), seul celle ci serons éxécuté.

Le nombre d'options importe peu tant qu'elles sont valides. Veillez à ne pas entrer deux fois la même option (une vérification est effectuée dans le script shell qui arrête l'exécution en cas de doublon).

Une fois exécuté, vous retrouverez les graphiques dans un dossier indiqué lors de l'exécution du script.
