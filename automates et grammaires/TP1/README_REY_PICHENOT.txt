QUESTION 1
1/ La commande pour lister les fichier .c ou .h est : $ ls *.[ch]
2/ avant dernier caractère n'est pas le . : $ ls *?[!.]?

QUESTION 2
1/ La commande affiche tout les fichiers car il y à une * et on peut "mettre" n'importe quelle chaine de caractère dans *, de plus !(.jpeg|.jpg) reconnais 1 et vu qu'il n'y as pas de caractère séparant * de !(.jpeg|.jpg) alors !(.jpeg|.jpg) est inutile
2/ pour lister tout les fichiers sauf les .jpg ou .jpeg faire : $ ls !(*.jpeg|*.jpg)

QUESTION 3
1/ toutes les lignes sont reconnues
2/ la ligne aaa est reconnue car elle contient aa qui lui est reconnu par le regex.
3/ regex corrigé : $ grep --color '^(aa)*$' test.txt -E

QUESTION 4
pour reconnaitre abcde dans l'ordre :
$ grep --color '(.)*a(.)*b(.)*c(.)*d(.)*e(.)*' american-english.txt -E

QUESTION 5 
lister les mots avec lettre doublé :
$ grep --color '(.*)(.)\2(.*)' american-english.txt -E
(il y en a 22262)
$ grep --color '[^A-Z](.*)(.)\2(.*)' american-english.txt -E
(il y en a 21906)

QUESTION 6
lister les mots avec 6 fois la même lettre (sauf le s) :
$ grep --color '(.*)([^s])((.*)(\2)){5}(.*)' american-english.txt -E

QUESTION 7

QUESTION 8
mots qui commencent et finissent par la même lettre et qui on 5 fois une même lettre :

$ grep --color '^(.)(.*)\1$' american-english.txt -E -i | grep --color '(.*)(.)((.*)(\2)){4}(.*)' -E -i

QUESTION 9
liste de tout les processus de navigateur internet :
$ ps aux | grep 'grep' -v | grep --color '(firefox|chromium|safari)' -E

QUESTION 10
lignes qui on une tabulation ou un espace avant le retour a la ligne :
$ grep --color '^.*(\t| )+\s$' MobyDick.txt -E

lignes qui commencent par une tabulation :
$ grep --color '^(\t)+.*$' MobyDick.txt -E

QUESTION 11
pour supprimer tout les espace en début de ligne :
$ sed -i 's/^ *//g' MobyDick.txt

QUESTION 13
inverser les colonnes :
$ sed -i 's/\(.*\), \(.*\)/\2, \1/g' db.csv

QUESTION 14
Nous avons fait avec sed dès le départ, voir réponses précédentes.

QUESTION 15
affichage du pourcentage du CPU utilisé :

$ ps aux | awk '{p="reyh"}/p/{sum+=$3}END{printf "%s %f%s\n",p, sum, "%" }'




