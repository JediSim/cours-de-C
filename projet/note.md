## fonction tablette pour coder

1. recupère la zone texte de la tablette
2. connexion serveur d'éval en ssh (login, password parametré en local dans LaWeb config.js)
3. le serv execute dossier/script.sh avec zone de texte en parametre. Il génère un uuid --> fichier source.C avec le parametre d'entrée
               --> fichier log
compilation... si ca marche il lance les tests :
    - si ca marche il renvoie OK
    - sinon NOK ou message explicite
Si pas compiler res charger dans les logs. Logs renvoyer sur le flux de sortie
Tous les renvoie sont affichés sur l'IHM

## Reu

mardi 1 fevrier

## 1. Présentation des APIs

### srv exo

L'id mettre se qu'on veut. Il peut varier suivant les contextes (nom de l'exo). Solution nouveau champs pour le nom.

data set pour que chaque etudiant est un enoncé différent. Exemple faire un exo de trie, un élève avec croissant l'autre avec décroissant.

Modifier le jeu de test pour le mettre dans le data set

ID différent pour chaque tentative. L'etudiant peut abandonner temporairement.

template des fonctions pour la fenètre de l'etudiant. Exemple le corps du main.

Définir le contexte (TP avec un prof sur un langage). Retirer l'année d'étude et autre info lié au contexte.

A force avoir plus de critère sur /exercices/"query string".

### srv éval

add ID de tentative + data set.

Passer au suivant peut-il se faire même avec une reponse partiel ?

Pas de distinction entre erreur de compilation et d'execution.

Il reste une erreur de timeOut à gérer.

### srv strategie

Il manque le système session etc... Pour définir la strategie.

## 2. Présentation des schémas / modèles de BDD

### bdd exo

ajout du template (corps de fct).

connaitre les champs optionels.

### bdd resultat

ajout l'ID de tentative (cf srv exo)

## 3. Backlog

chemin avec des query string ++

user stories choisi : 1 2 4 8

ajout stories : 

#8 recupère un exo a partir des critères (query string).

## 4. Conclusion/Planifier la réunion suivant

Dans gitlab mettre les specs openAPI (mettre openAPI dans le nom pour que ca marche).

utiliser https pour le git c'est le seul moyen.

Pour discuter il vaut mieux passer par une merge request et discuter dessus.

Mardi 1 mars 10h15.

/!\ Il faut faire attention à bien demander ce qu'on veut savoir. Rentrez plus dans le dur /!\