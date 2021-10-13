##### Question 1 #####

3/
?- chien(socrate).
	false
?- chien(toto).
	false
?- souris(milou).
	procedure `souris(A)' does not exist

4/
?- mortel(X).
	X = socrate
	X = louis_XIV

##### Question 2 #####

Il n'y auras pas de résultat, car c'est une affectation

##### Question 3 #####

bug corrigé dans le fichier test-002-PICHENOT-REY.pl

##### Question 4 #####

Solution apportée dans le fichier test-002-PICHENOT-REY.pl

##### Question 6 #####

1/ Contient parcourt la liste jusqu'a la fin et ne s'arrete pas au premier élément trouvé.

##### Question 7 #####
2/ ils s'arrêtent au premier élément trouvé.
3/ member corresond probablement à contient2

##### Question 8 #####

X = [pique, carreau, trefle, coeur]

##### Question 9 #####

X = [
	maison(jaune, footballeur, poisson, jazz, biere), 
	maison(immeuble, architecte, hamster, classique, eau),
	maison(briques, chercheur, chat, hardrock, soda),
	maison(bois, boulanger, zebre, chanson, wisky),
	maison(blanche, musicien, tortue, hiphop, the)
	]

##### JEU #####

## PARTIE SANS SPOILS
Dans ce jeu vous incarnez Jean Pasjean, un élève de la fac qui doit se rendre en cours et compléter certaines taches.
Vous pouvez parler à un pnj, récupèrer des objets dans votre sac (attention votre sac ne peut prendre que trois objets) et effectuer des actions. Vous pouvez gagner ou perdre la partie, si vous gagnez, il est possible que vous ayez à rejouer pour avoir un score plus élevé.

## PARTIE TECHNIQUE
Pour le sac ou le score, nous avons mis en place un fait appelé sac(x) ou score(x) et x est la valeur initiale. Au fur et a mesure des actions du joueurs nous incrémentons ou décrémentons la valeur x à l'aide des assert et retract.

## SPOILS
Pour obtenir le meilleur score possible il faut :
- prendre son petit déjeuner (à la maison, il est possible de manger à l'hélice mais cela n'augmente pas le score car Jean essaye d'économiser)
- donner les papiers du crous à l'acceuil 
- réussir à obtenir le numéro de janette

attention !
si vous effectuez de mauvais choix (ou actions), vous pouvez perdre et fini le jeu plus tôt. La jeu se fini à la fin du cours.
