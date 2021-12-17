REY PICHENOT

1/ Memoire d'un processus

1.1 Stack et Malloc

Les valeurs dans la pile sont concecutives et croissantes. Dans le tas les blocs sont eux aussi concecutifs et croissant.

On voit bien que les adresses du tas evoluent dans le bon sens. Mais pour la pile on ne choisi pas l'ordre de l'empilement des variables. Donc
on ne peut rien en deduire pour la pile juste avec des variables. Il faut faire des appels de fonction à la pace.

1.2 Stack frame

 ______________
/              \
| main  |      |
| int   | cps  |
| int   | c    |
| f1    |      |
| char* | BLK1 |
| char* | BLK2 |
| char* | BLK3 |
| f2    |      |
| char* |  BLK1|
| char* |  BLK2|
| char* |  BLK3|

Dans chaques focntions les adresses de la pile et du tas sont consecutives. Mais pas entre les deux fcts.

On peut maintenant observer que les adresses de la pile sont décroissantes car les adresses de f2 sont plus petites que celles de f1.
Les addresses des blocs sont toujours croissantes.

1.3 Pointeurs

Sortie de pointeur.c
x = 0x56219365e2a0
*x = 0xdeadbeef
&x = 0x7ffdc303f7b0

x contient l'addresse qui pointe sur *x
*x contient le caste de 3735928559 en addresse.
&x contient l'adresse de la variable de x.

2/ Garbage Collector

