PICHENOT - REY

1. PRELIMINAIRE

bloc : une partie de la mémoire alloué a une partie du fichier.
inoeud : identifiant d'un bloc
superbloc : des métadonnée sur les blocs et le système de fichier.

Formater un périphérique consite à supprimer les référence inoeud et changer le format des blocs.
Pour mieux formater et éviter de garder des vieilles données, il vaut mieux utiliser shred qui met 
des données aléatoire à l'ancien emplacement du fichier.

Que trouverait-on dans les blocs de données de ce fichier fs.ext2 ?
des valeurs aléatoires car nous venons d'initaliser le fichier.

après avoir fait la commande ls -ai /, on constate que c'est le même inode que le répertoire/

df -T ? cohérent ?
Le resultat de la commande est cohérent. On voit que la racine est un montage.

2. Prise en main

2.3 Manipulation 
Le montage consiste a ajouté un chemin dans l'arborescence entre le repertoire que l'on veut monter et le système.
On toujours accés aux commandes dans les nouveaux volumes car du point de vue du système il n'y a pas de différence entre les deux arborescence.
exemple : on peut utiliser les commandes même dans notre clé usb.

2.4 Manipulation directe des inodes / blocs

on recupère le numéro d'inode du fichier fic1.txt.
On execute show_inode 135 (num inode). Ca nous donne les information sur l'inode dont les numéro des blocks.
On execute dump_data 2038 (num de block). Ca nous donne le contenu du block 2038.
Ici on a "0x0000: TEST SIMPLE?...................................................." sur la première ligne.

creer un fichier 

create_file
qui renvoie un numéro d'inode.

add_entry 302 fic2.txt 235
En premier le numéro d'inode du repértoire parant, le nom du fichier et le numéro d'inode du fichier créé juste avant.

3.5 Ajout des liens physiques

Un lien physique créer un nouveau fichier avec le même inode que le fichier lié. Ils pointes sur les mêmes blocs tous les deux.

3.6 Ajout des liens logiques

Un lien logique créer un deuxième fichier avec un inode différent et qui à des blocks qui pointes sur les pointeurs de blocks du fichier lié.

3.7 Blocs à accès indirect




