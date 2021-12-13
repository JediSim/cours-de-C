PICHENOT Simon - REY Hugo 

2.1/ Fin de processus
a) Y a-t'il une différence entre ces deux méthodes. Décrivez ce qui se passe dans l'une et dans l'autre. Vous pouvez illustrer votre propos avec le code de la fonction sys_exit du noyau.
avec un exit failure, le parent reçois un message comme quoi le processus fil c'est terminé avec une erreur.
Avec exit sucess, le parent reçois un message comme quoi le processus fil c'est terminé avec un succes. 
Dans les deux cas le processus père reçois un message comme quoi le processus fil c'est terminé.

-- 3.3 Répertoire de travail d'un processus --
a) Comment le processus est-il lié à cette notion ?
un processus s'execute dans le répertoir dans lequel il est créé.

b) Quelle autre répertoire est associé au processus ?
Il existe le répertoir /proc/ qui contient un répertoir par processus.
Ces repertoires sont temportaires et stockes les informations des processus.

-- 6 Exécuter un programme --

a) Expliquez le fonctionnement de fork() vu en cours, ce nouveau processus s'exécute t'il immédiatement ?
à l'appel de fork, on duplique le contexte d'execution actuel dans un nouveau processus. Il s'exécute immédiatement.

b) Quels sont les éléments communs au père et au fils?
le contexte au moment de l'appel fork()

c)  Quels sont les éléments conservés du processus après un appel à exec ?
Le processus revient dans l'état ou il etait avant la commande execv().

-- 6.1 Utilisation de la redirection > --

a) Expliquez le fonctionnement de cet appel système "dup2 ( fd , STDOUT_FILENO) ;"
set la sortie standard (tout les prints suivants) vers la sortie indiquée.

NOTE : nous avons voulu créer la fonction commandes dans laquelle se trouve tous nos test afin de ne pas dupliquer le code.
Cependants, la fonction exec ne marche pas lorsqu'elle se trouve dans la fonction commandes mais fonctionne dans le main. Nous
N'avons pas pu trouver de solution. Le print commenté affiche pourtant la même chose dans le main et dans la fonctione commandes.
