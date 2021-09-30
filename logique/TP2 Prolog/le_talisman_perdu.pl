%%% INFO-501, TP3
%%% Arthur Dent
%%%
%%% Lancez la "requête"
%%% jouer.
%%% pour commencer une partie !
%

% il faut déclarer les prédicats "dynamiques" qui vont être modifiés par le programme.
:- dynamic position/2, position_courante/1.

% on remet à jours les positions des objets et du joueur
:- retractall(position(_, _)), retractall(position_courante(_)).

% on déclare des opérateurs, pour autoriser `prendre torche` au lieu de `prendre(torche)`
:- op(1000, fx, prendre).
:- op(1000, fx, lacher).
:- op(1000, fx, aller).


% position du joueur. Ce prédicat sera modifié au fur et à mesure de la partie (avec `retract` et `assert`)
position_courante(entree_grotte).


% positions relatives des emplacements
passage(entree_grotte, est, espace_de_vie).
passage(espace_de_vie, ouest, entree_grotte).

passage(entree_grotte, ouest, alcove) :- position(torche, en_main).
passage(entree_grotte, ouest, alcove) :-
    write("Aller dans cette petite alcove sombre ?"), nl,
    write("Sans lumière ?"), nl,
    write("Hors de question..."), nl,
    !, fail.

passage(alcove, est, entree_grotte) :-
    write("Mmm... Ça fait du bien de retrouver la lumière du jours."), nl.


passage(entree_grotte, nord, petite_gallerie).
passage(petite_gallerie, sud, entree_grotte).

passage(petite_gallerie, bas, crevasse) :-
    position(corde, en_main),
    position(torche, en_main),
    write("Vous fixez la corde sur un piton rocheux et descendez dans la crevasse."), nl,
    write("En descendant, la torche que vous avez en main vous brule."), nl,
    write("Vous lachez la corde et tombez..."), nl,
    write("Avec une jambe cassée, vous ne pourrez pas finir cette aventure..."), nl,
    fin.


passage(petite_gallerie, bas, crevasse) :-
    position(corde, en_main),
    write("Vous fixez la corde sur un piton rocheux et descendez dans la crevasse."), nl.


passage(petite_gallerie, bas, crevasse) :-
    write("Zzuippp..."), nl,
    write("En essayant de descendre dans la crevasse, vous glissez et tombez."), nl,
    write("Avec une jambe cassée, vous ne pourrez pas finir cette aventure..."), nl,
    fin.


passage(crevasse, haut, petite_gallerie).


% position de quelques objets
position(torche, espace_de_vie).
position(corde, alcove).
position(caillou, crevasse).


% ramasser un objet
prendre(X) :-
        atom(X),
        position(X, en_main),
        write("Vous l'avez déjà !"), nl,
        !.

prendre(X) :-
        atom(X),
        position_courante(P),
        position(X, P),
        retract(position(X, P)),
        assert(position(X, en_main)),
        write("OK."), nl,
        !.

prendre(X) :-
        write("??? Je ne vois pas de "),
        write(X),
        write(" ici."), nl,
        fail.


% laisser un objet
lacher(X) :-
        atom(X),
        position(X, en_main),
        position_courante(P),
        retract(position(X, en_main)),
        assert(position(X, P)),
        write("OK."), nl,
        !.

lacher(_) :-
        write("Vous n'avez pas ça en votre possession !"), nl,
        fail.


% quelques raccourcis
n :- aller(nord).
s :- aller(sud).
e :- aller(est).
o :- aller(ouest).


% déplacements
aller(Direction) :-
        atom(Direction),
        position_courante(Ici),
        passage(Ici, Direction, La),
        retract(position_courante(Ici)),
        assert(position_courante(La)),
        regarder, !.

aller(_) :-
        write("Vous ne pouvez pas aller par là."),
        fail.


% regarder autour de soi
regarder :-
        position_courante(Place),
        decrire(Place), nl,
        lister_objets(Place), nl.


% afficher la liste des objets à l'emplacement donné
lister_objets(Place) :-
        position(X, Place),
        write("Il y a "), decrire(X), write(" ici."), nl,
        fail.

lister_objets(_).

% fin de partie
fin :-
        nl, write("La partie est finie."), nl,
        halt.


% affiche les instructions du jeu
instructions :-
        nl,
        write("Les commandes doivent être données avec la syntaxe Prolog habituelle."), nl,
        write("Les commandes existantes sont :"), nl,
        write("jouer.                   -- pour commencer une partie."), nl,
        write("n.  s.  e.  o.           -- pour aller dans cette direction (nord / sud / est / ouest)."), nl,
        write("aller(direction)         -- pour aller dans cette direction."), nl,
        write("prendre(objet).          -- pour prendre un objet."), nl,
        write("lacher(objet).           -- pour lacher un objet en votre possession."), nl,
        write("regarder.                -- pour regarder autour de vous."), nl,
        write("instructions.            -- pour revoir ce message !."), nl,
        write("fin.                     -- pour terminer la partie et quitter."), nl,
        nl.


% lancer une nouvelle partie
jouer :-
        instructions,
        write("Bonjour Groumf !"), nl,
        write("Vous êtes un petit garçon de Cro-Magnon 8 ans !"), nl, nl,
        regarder.


% descriptions des objets et emplacements
% objets
decrire(corde) :-
        write("une vielle corde en chanvre tressé ('corde')").

decrire(torche) :-
        write("une branche qui dépasse du feu ('torche')").

decrire(caillou) :-
        write("un caillou brillant ('caillou')").


% emplacements
decrire(espace_de_vie) :-
    write("Cette grande salle est éclairée par un grand feu."), nl,
    write("Tout le clan est présent et les chasseurs préparent une sortie."), nl,
    write("Votre grande soeur est absente."), nl,
    write("La sortie se trouve à l'ouest."), nl.

decrire(alcove) :-
    write("Cette petite alcove servait d'espace de rangement."), nl,
    write("Elle ne sert plus car l'absence de lumière du jours rendait son utilisation hasardeuse."), nl,
    write("La sortie, vers l'entrée de la grotte, se trouve à l'est.").

decrire(crevasse) :-
    write("La crevasse s'élargit vers le bas."), nl,
    write("Les paroies sont humides, et le fond tapissée d'argile molle."), nl,
    write("Il faudra remonter (direction 'haut') pour sortir de cette crevasse."), nl.

decrire(entree_grotte) :-
        position(caillou, en_main),
        write("En vous voyant sortir avec le talisman, votre grande soeur retrouve le sourire."), nl,
        write("Bravo !!"), nl,
        fin, !.

decrire(entree_grotte) :-
    write("Vous êtes à l'entrée de la grotte."), nl,
    write("À l'est se trouve la salle de vie commune où les membres du clan se réchauffent.."), nl,
    write("À l'ouest se trouve un petit passage sombre."), nl,
    write("Tout droit, au nord, la grotte s'enfonce dans la montagne."), nl,
    write("Votre grande soeur est là. Elle doit remplacer le shaman, emporté par une maladie."), nl,
    write("Elle n'ose pas rejoindre le reste clan, car elle n'a toujours pas trouvé le cailloux scintillant,"),nl,
    write("talisman de la tribu."), nl.

decrire(petite_gallerie) :-
    write("La petite gallerie s'enfonce dans la montagne mais est bientôt barrée par une crevasse."), nl,
    write("Il doit être possible de descendre (direction 'bas') en faisant attention."), nl.
