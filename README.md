# CY_Truck

Afin d'utiliser l'application, tâcher de vous rendre depuis le terminal dans le dossier contenant le fichier script.sh, il se peut qu'il ne possède pas les droits en éxécution, donc afin de pouvoir utiliser l'application par la suite, vous pouvez faire la commande : 

chmod +x script.sh 

Maintenant l'application est prète à être éxecuté. La compilation des fichiers néccessaire au fonctionnement de l'application se fait au début de l'éxecution du script, en cas de problème, un message d'erreur s'affichera.

Pour l'éxecuter utiliser la commande : 

./script.sh chemin_fichier -option 

Les options sont indiqués si vous utiliser l'option -h (aide), qui détaille le resultat de chaque option (si vous entrée -h et une autre option seulement le -h sera traité).

Le nomre d'option importe peu tant qu'elles sont valide, veiller à ne pas entrer deux fois la même option (une vérification est effectuer dans le script shell qui arrete l'éxecution en cas de doublon)

Une fois executer vous retrouver les graphiques dans un dossier dans un dossier indiqué lors de l'éxecution du script. 

