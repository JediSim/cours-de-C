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


