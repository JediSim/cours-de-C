Q.1 : 
simplification avec 1
avant : [[1, -2, 3], [-1, -3, 4], [2, -4]]
après : [[-3, 4], [2, -4]]

Q.2 :
Elle est satisfiable avec a=1 et b=c=0.
En rajoutant la clause -a on trouve une autre solution : a=b=c=0

Q.3 :
On constate que les 2 solutions précédentes ne sont pas toujours données. 
Donc la satisfiabilité de la formule ne dépend pas de a.

Q.4 (BONUS) :

Q.5 :
X_1_pique X_3_trefle X_2_carreau X_4_coeur 
SATISFIABLE: 1 solution(s) found
La formule contient plusieurs parties.
La première partie correspond aux trois indices du problème
La deuxième partie dit qu'on peut avoir uniquement un as par famille
La derniere partie sert à ce que chaques emplacements aient une carte.
Les problèmes que nous avons rencontrer :
Nous avons fait une faute de frappe ce qui a rajouter des variables et rendu les choses completement fausses. On trouvais beaucoup trop de solutions.
Nous avons ensuite voulu ajouter une partie disant que il ne pouvais pas y avoir deux carte par emplacements 

Q.6 : 
Le boulanger est le proprietaire du zebre, en position 4 et il ecoute de la musique fr 

Q.8 :
Nous avons rejouter un print() dans la fonction solve de maniere a voir combien de fois nous passons dedans.
Sur la formule des cartes nous avons 10 passage avec l'option -D et sans l'option il y a significativement plus de passage (environ 70)

Nous avons comparé notre SAT avec minisat (sat solver optimisé). Pour comparer nous avons utilisé la formule du sudoku. Avec notre SAT nous avons
Attendu plusieurs minute avant de kill le processus. ALors qu'avec minisat nous avons eu la reponse en moins d'une seconde (0.03 s).

Q.10 :
Nous avions à compléter le code qui nous permet de trouver la formule qui donne la valeur de a et de b dans l'équation a + b = c en binaire.
Pour se faire nous devions compléter la fonction xor3(). Cette fonction est composée de print(). Chacun de ces print() correspondent a une clause
de la forme normale conjonctive de s = xor(a,b,c).

De plus nous devions rajouter des clauses pour contraindre les valeurs des bits de s. En d'autres termes on calcul la valeur binaire de s et on le 
rentre dans le calcul pour avoir une formule qui decrit a + b = s (en binaire). Exemple s = 7, on dit s0 = 1, s1 = 1, s2 = 1...

Pour finir on fait appelle aux fonctions xor3() et carry3() pour reppresenter le calcul a + b.

Q.12 :
Pour n1=6 et n2=7 notre SAT devient trop lent. Cela correspond à 132 variables et 659 clauses.

Avec minisat le temps de trouver la formule de la multiplication devient trop important avant que minisat ne soit en difficulté.



