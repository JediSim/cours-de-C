%reveil 5h55
%train 6h48

%prédicats dynamiques
:- dynamic position/2, action/2, position_courante/1, inventaire/1, passage/3, position_dialogue/1, score/1.

% on remet à jours les positions des objets et du joueur. On met a jour les actions et l'inventaire
:- retractall(position(_, _)), retractall(position_courante(_)), retractall(inventaire(_)), retractall(action(_,_)), retractall(position_dialogue(_)).

% on déclare des opérateurs, pour autoriser `prendre torche` au lieu de `prendre(torche)`
:- op(1000, fx, prendre).
:- op(1000, fx, faire).
:- op(1000, fx, lacher).
:- op(1000, fx, aller).


% position du joueur. Ce prédicat sera modifié au fur et à mesure de la partie (avec `retract` et `assert`)
%   /|\                                                   /|\
%  / | \ remettre la position de départ après les tests. / | \
% /  !  \                                               /  !  \
position_courante(chambre).

position_dialogue(null).

% init score
score(0).

%nombre d'objet dans l'inventaire, MAX 3
inventaire(0).
%objets
objet(stylo).
objet(papier_CROUS).
objet(pc).
objet(bloc_note).
objet(bouteille).
objet(portefeuille).

% position des objets et des actions
position(stylo, chambre).
position(papier_CROUS,chambre).
position(pc,chambre).
position(bloc_note,chambre).
position(portefeuille,chambre).
position(bouteille,chambre).
position(douche,salle_de_bain).
position(petit_dejeuner,salon).
position(janette_parler,janette).
position(cookie,helice).
position(muffin,helice).
position(formule_dej,helice).
position(janette,salle_de_cours).

%action
action(douche,non).
action(petit_dejeuner,non).
action(cookie,non).
action(muffin,non).
action(formule_dej,non).
action(janette,non).
action(personne_acceuil_trouve,non).

%passages
%chambre
passage(chambre,ouest,salle_de_bain).
passage(chambre,nord,salon).
%salle de bain
passage(salle_de_bain,est,chambre).
%salon
passage(salon,nord,gare).
passage(salon,sud,chambre).
%gare
passage(gare,nord,fac).
%fac
passage(fac,nord,crous).
passage(fac,ouest,salle_de_cours).
passage(fac,est,eve). % mettre la carte etudiant à jour.
passage(fac,sud,helice).
%salle de cours
passage(salle_de_cours,est,fac).
%crous
passage(crous,nord,crous_etage).
passage(crous,sud,fac).
passage(crous,ouest,crous_bureau).
passage(crous,est,crous_salle_de_pause).

passage(crous_bureau,nord,crous_ordi).
passage(crous_ordi,sud,crous_bureau).

passage(crous_bureau,sud,crous).
passage(crous_etage,sud,crous).
passage(crous_salle_de_pause,sud,crous).



%choix dialogue
choix(janette,a,janette_dialogue1a).
choix(janette,b,janette_dialogue1b).

%afficher le sac

sac :-
        write("votre sac contient :"),nl,
        position(X, sac),
        decrire(X), nl,
        fail.

sac.

incr(X, X1) :-
    X1 is X+1.

decr(Y, Y1) :-
    Y1 is Y-1.

add(X, X1, NB) :-
        X1 is X+NB.

sous(Y, Y1, NB) :-
        Y1 is Y+NB.

% faire une action
faire(X) :-
        atom(X),
        position_courante(P),
        position(X, P),
        action(X,non),
        retract(action(X, non)),
        assert(action(X, oui)),
        write("action faite."), nl,
        !.

faire(X) :-
        atom(X),
        position_courante(P),
        position(X, P),
        action(X, oui),
        write("Vous l'avez déjà fait !"), nl,
        !.

faire(X) :-
        atom(X),
        write("Vous ne pouvez pas faire ça."), nl,
        !.

%commander
commander(X) :-
    position(portefeuille,sac),
    faire(X).

commander(_) :-
    not(position(portefeuille,sac)),
    write("Vous n'avez pas de portefeuille pour commander."),nl.


% parler
% X est le non du dialogue. il doit correspondre à l'action correspondant ex : parler(janette) -> action(janette,non)
parler(X) :-
        action(X,non),
        position_courante(ICI),
        position(X, ICI),
        retract(position_courante(ICI)),
        assert(position_courante(salle_dialogue)),
        position_dialogue(DIA),
        retract(position_dialogue(DIA)),
        assert(position_dialogue(X)),
        dialogue(X),
        !. 

parler(_) :-
        write("Vous ne pouvez pas parler à cette personne"),
        fail.

% choisir une reponse dans dialogue

% alias choisir
a :- choisir(a).
b :- choisir(b).

choisir(Choix) :-
        position_dialogue(Ici),
        choix(Ici, Choix, La),
        retract(position_dialogue(Ici)),
        assert(position_dialogue(La)),
        dialogue(La),
        !.

choisir(_) :-
        write("Ce choix n'existe pas !"),nl,
        fail.

% ramasser un objet
prendre(X) :-
        atom(X),
        position(X, sac),
        write("Vous l'avez déjà !"), nl,
        !.

prendre(X) :-
        atom(X),
        position_courante(P),
        position(X, P),
        inventaire(3),
        write("Vous n'avez plus de place dans votre sac."), nl,
        !.

prendre(X) :-
        atom(X),
        position_courante(P),
        position(X, P),
        retract(position(X, P)),
        assert(position(X, sac)),
        retract(inventaire(I)),
        incr(I,Y),
        assert(inventaire(Y)),
        write("Vous avez mis l'objet dans votre sac."), nl,
        !.

prendre(X) :-
        write("??? Je ne vois pas de "),
        write(X),
        write(" ici."), nl,
        fail.


% laisser un objet
lacher(X) :-
        atom(X),
        position(X, sac),
        position_courante(P),
        retract(position(X, sac)),
        assert(position(X, P)),
        retract(inventaire(Number)),
        decr(Number, NumberDecr),
        assert(inventaire(NumberDecr)),
        write("Vous avez bien enlevé de votre sac cet objet."), nl,
        !.

lacher(_) :-
        write("Vous n'avez pas ça dans votre sac !"), nl,
        fail.

% quelques raccourcis
z :- aller(nord).
s :- aller(sud).
d :- aller(est).
q :- aller(ouest). 

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
        lister_objets(Place), nl,
        lister_actions(Place),nl.

% afficher la liste des actions à l'emplacement donné
lister_actions(Place) :-
        action(X,non),
        position(X, Place),
        decrire(X), nl,
        fail.

lister_actions(_).

% afficher la liste des objets à l'emplacement donné
lister_objets(Place) :-
        objet(X),
        position(X, Place),
        decrire(X), nl,
        fail.

lister_objets(_).


% fin de partie
fin :-
        nl, write("La partie est finie."), nl,
        write("score : "),
        score(Score),
        write(Score),nl,
        halt.

%defaite
perdu :-
        nl,write("--<<{{ GAME OVER }}>>--"),nl.

% affiche les instructions du jeu
instructions :-
        nl,
        write("Les commandes doivent être données avec la syntaxe Prolog habituelle."), nl,
        write("Les commandes existantes sont :"), nl,
        write("jouer.                   -- pour commencer une partie."), nl,
        write("z.  s.  d.  q.           -- pour aller dans cette direction (nord / sud / est / ouest)."), nl,
        write("aller(direction)         -- pour aller dans cette direction."), nl,
        write("faire(action).           -- pour faire une action. Une action possible est indiquée par une *"), nl,
        write("prendre(objet).          -- pour prendre un objet."), nl,
        write("commander(objet).        -- pour commander un objet Les commandes sont indiquée par un +."), nl,
        write("lacher(objet).           -- pour lacher un objet en votre possession."), nl,
        write("sac.                     -- pour regarder dans votre sac."), nl,
        write("regarder.                -- pour regarder autour de vous."), nl,
        write("instructions.            -- pour revoir ce message !."), nl,
        write("fin.                     -- pour terminer la partie et quitter."), nl,
        nl.


% lancer une nouvelle partie
jouer :-
        instructions,
        write("## { Lundi matin 6h10 } ##"), nl,
        write("Bonjour Jean Pasjean !"), nl,
        write("Vous venez de vous réveiller dans votre chambre, vous regardez le reveil qui affiche -6:10-"), nl,
        write("Vous êtes en retard pour l'université ! dépéchez vous de vous préparer avant d'aller prendre le train"), nl,
        regarder.


% ############### Descriptions des objets ###############
% ----- papier crous -----
decrire(papier_CROUS) :-
        position(papier_CROUS,chambre),
        write("votre demande d'appartement pour le crous traine sur le bureau ('papier_CROUS')").
decrire(papier_CROUS) :-
        position(papier_CROUS,sac),
        write("votre demande d'appartement pour le crous ('papier_CROUS')").

% ----- stylo -----
decrire(stylo) :-
        position(stylo,chambre),
        write("un stylo est posé sur votre table de nuit ('stylo')").
decrire(stylo) :-
        position(stylo,sac),
        write("un stylo ('stylo')").

% ----- bloc note -----
decrire(bloc_note) :-
        position(bloc_note,chambre),
        write("un bloc note est posé sur le bureau ('bloc_note')").
decrire(bloc_note) :-
        position(bloc_note,sac),
        write("un bloc note ('bloc_note')").

% ----- ordinateur portable -----
decrire(pc) :-
        position(pc,chambre),
        write("votre ordinateur portable est sur votre bureau ('pc')").
decrire(pc) :-
        position(pc,sac),
        write("un ordinateur portable ('pc')").

% ----- portefeuille -----
decrire(portefeuille) :-
        position(portefeuille,chambre),
        write("votre portefeuille est sur votre table de nuit ('portefeuille')").
decrire(portefeuille) :-
        position(portefeuille,sac),
        write("votre portefeuille ('portefeuille')").

% ----- bouteille -----
decrire(bouteille) :-
        position(bouteille,chambre),
        write("votre bouteille d'eau est sur votre table de nuit ('bouteille')").
decrire(bouteille) :-
        position(bouteille,sac),
        write("votre bouteille d'eau ('bouteille')").

% ############### descritpions actions ###############
decrire(douche) :-
        write("Vous pouvez vous doucher ('douche')*."),nl.

decrire(petit_dejeuner) :-
        write("Vous pouvez prendre votre petit déjeuner ('petit_dejeuner')*."),nl.

decrire(cookie) :-
        position(portefeuille,sac),
        write("Vous pouvez commander un cookie ('cookie')+."),nl.

decrire(muffin) :-
        position(portefeuille,sac),
        write("Vous pouvez commander un muffin ('muffin')+."),nl.

decrire(formule_dej) :-
        position(portefeuille,sac),
        write("Vous pouvez commander la formule petit déjeuner('formule_dej')+."),nl.


% ############### descritpions des lieux ###############

% ----- chambre -----
decrire(chambre) :-
        write("[[ CHAMBRE ]]"),nl,
        write("Vous êtes dans votre chambre, en face de vous se trouve votre porte pour aller dans le salon."),nl,
        write("A gauche, votre douche"),nl.

% ----- salle de bain -----
decrire(salle_de_bain) :-
        action(douche,oui),
        write("[[ SALLE DE BAIN ]]"),nl,
        write("Vous vous regardez dans le mirroir, le peu de cheveux restants sur votre crâne sont encore mouillés... Vous n'êtes clairement pas encore bien réveillé"),nl,
        write("à l'est la porte donne sur votre chambre."),nl.
decrire(salle_de_bain) :-
        action(douche,non),
        write("[[ SALLE DE BAIN ]]"),nl,
        write("Vous voyez votre reflet dans le miroir, vous ne semblez pas bien réveillé..."),nl,
        write("à l'est la porte donne sur votre chambre."),nl.

% ----- salon -----
decrire(salon) :-
        action(petit_dejeuner,oui),
        write("[[ SALON ]]"),nl,
        write("Les céréales sont encore sur la table mais vous n'avez pas le temps de débarrasser votre petit déjeuner..."),nl,
        write("derrière vous se trouve la porte de votre chambre, en face la porte d'entrée pour aller à la gare."),nl.
decrire(salon) :-
        action(petit_dejeuner,non),
        write("[[ SALON ]]"),nl,
        write("Sur la table se trouve vos céréales préféré, du lait et du jus d'orange."),nl,
        write("derrière vous se trouve la porte de votre chambre, en face la porte d'entrée pour aller à la gare."),nl.

% ----- gare -----
decrire(gare) :-
        action(douche,oui),
        position(portefeuille,sac),
        write("[[ GARE ]]"),nl,
        write("Votre douche vous à mis en retard ! vous avez raté votre train ! heureusement, vous avez pris votre portefeuille vous pouvez prendre un taxi jusqu'a la fac."),nl,
        write("Il y a un taxi en face de vous."),nl,
        !.

decrire(gare) :-
        action(douche,oui),
        retract(passage(gare,nord,fac)),
        write("[[ GARE ]]"),nl,
        write("Votre douche vous à mis en retard ! vous avez raté votre train ! malheursement vous avez oublié votre portefeuille, vous n'avez pas de moyen d'aller à la fac... vous avez perdu."),nl,
        perdu,
        !.

decrire(gare) :-
        action(douche,non),
        write("[[ GARE ]]"),nl,
        write("Vous arrivez à l'heure pour prendre votre train,"),nl,
        write("En face se trouve le train pour aller à la fac."),nl,
        !.

% ----- fac -----
decrire(fac) :-
        action(petit_dejeuner,non),
        write("[[ USMB ]]"),nl,
        write("Vous êtes sur le campus. Au nord, se trouve la batiment du crous."),nl,
        write("à l'ouest la salle de cours, à l'est le batiment EVE"),nl,
        write("derrière vous se trouve l'hélice."),nl,
        write("-Brlbrlbr- Votre estomac est bien vide..."),nl,
        !.

decrire(fac) :-
        write("[[ USMB ]]"),nl,
        write("Vous êtes sur le campus. Au nord, se trouve la batiment du crous."),nl,
        write("à l'ouest la salle de cours, à l'est le batiment EVE"),nl,
        write("derrière vous se trouve l'hélice."),nl,
        !.

% ----- helice -----
decrire(helice) :-
        action(douche,non),
        position(portefeuille,sac),
        action(muffin,non),
        action(cookie,non),
        action(formule_dej,non),
        write("[[ HELICE ]]"),nl,
        write("Un peu de monde attend et c'est enfin à votre tour"),nl,
        write("'Que désirez vous ?' La vendeuse vous regarde en attendant votre choix"),nl,
        write("derrière vous se trouve la sortie."),nl,
        !.

decrire(helice) :-
        action(douche,non),
        position_courante(P),
        position(A,P),
        action(A,oui),
        write("[[ HELICE ]]"),nl,
        write("Vous avez déjà acheté de quoi mangé ce matin."),nl,
        write("derrière vous se trouve la sortie."),nl,
        !.
decrire(helice) :-
        not(position(portefeuille,sac)),
        write("[[ HELICE ]]"),nl,
        write("Vous avez oublié votre portefeuille vous ne pouvez donc pas commander quoi que ce soit."),nl,
        write("derrière vous se trouve la sortie."),nl,
        !.

decrire(helice) :-
        action(douche,oui),
        write("[[ HELICE ]]"),nl,
        write("Vous êtes en retard et il y a trop de monde pour avoir le temps de commander quoi que ce soit."),nl,
        write("derrière vous se trouve la sortie."),nl,
        !.


% ----- crous -----
decrire(crous) :-
        action(personne_acceuil_trouve,non),
        position(papier_CROUS,sac),
        write("[[ CROUS ]]"),nl,
        write("L'acceuil est vide...Essayez de retrouver la responsable pour lui donner les papiers."),nl,
        write("Devant vous se trouve la porte donnant sur l'étage"),nl,
        write("A votre gauche un bureau, et à votre droite une salle de pause"),nl,
        !.
decrire(crous) :-
        action(personne_acceuil_trouve,non),
        position(papier_CROUS,_),
        write("[[ CROUS ]]"),nl,
        write("L'acceuil est vide...De toute façon vous n'avez pas les papier."),nl,
        write("Devant vous se trouve la porte donnant sur l'étage"),nl,
        write("A votre gauche un bureau, et à votre droite une salle de pause"),nl,
        !.

decrire(crous) :-
        action(personne_acceuil_trouve,oui),
        position(papier_CROUS,sac),
        retract(position(papier_CROUS,sac)),
        assert(position(papier_CROUS,personne_crous)),
        retract(score(Scr)),
        add(Scr,Nscr,150),
        assert(score(Nscr)),
        write("[[ CROUS ]]"),nl,
        write("La personne de l'acceuil vous attend, vous lui donnez vos papiers."),nl,
        write("Vous pouvez sortir du crous. (la porte se trouve derrière vous)"),nl,
        write("A votre gauche un bureau, et à votre droite une salle de pause"),nl,
        !.
decrire(crous) :-
        action(personne_acceuil_trouve,oui),
        position(papier_CROUS,personne_crous),
        write("[[ CROUS ]]"),nl,
        write("La personne de l'acceuil est là, vous lui avez déjà donné vos papiers."),nl,
        write("Vous pouvez sortir du crous. (la porte se trouve derrière vous)"),nl,
        write("A votre gauche un bureau, en face des escaliers et à votre droite une salle de pause"),nl,
        !.
decrire(crous) :-
        action(personne_acceuil_trouve,oui),
        position(papier_CROUS,_),
        write("[[ CROUS ]]"),nl,
        write("La personne de l'acceuil vous attend, mais vous n'avez pas vos papiers."),nl,
        write("Vous pouvez sortir du crous. (la porte se trouve derrière vous)"),nl,
        write("A votre gauche un bureau, en face des escaliers et à votre droite une salle de pause"),nl,
        !.

decrire(crous_etage) :-
        write("[[ CROUS - ETAGE ]]"),nl,
        write("L'étage semble vide...Vous avez perdu votre temps a monter"),nl,
        write("Derrière vous se trouve l'escalier pour redescendre"),nl,
        !.
decrire(crous_bureau) :-
        write("[[ CROUS - BUREAU ]]"),nl,
        write("Le bureau est vide... l'ordinateur devant vous est encore allumé..."),nl,
        write("Derrière vous se trouve la porte."),nl,
        !.

decrire(crous_ordi) :-
        write("[[ CROUS - BUREAU - ORDINATEUR ]]"),nl,
        write("Le navigateur est ouvert sur krunker.io"),nl,
        write("vous pouvez vous éloigner de l'ordinateur."),nl,
        !.

decrire(crous_salle_de_pause) :-
        position(papier_CROUS,personne_crous),
        write("[[ CROUS - SALLE DE PAUSE ]]"),nl,
        write("la salle de pause est vide..."),nl,
        write("derrière vous se trouve la sortie"),nl,
        !.

decrire(crous_salle_de_pause) :-
        write("[[ CROUS - SALLE DE PAUSE ]]"),nl,
        retract(action(personne_acceuil_trouve,_)),
        assert(action(personne_acceuil_trouve,oui)),
        write("Une personne se tient devant la machine à café ! vous avez trouvé la personne de l'acceuil !"),nl,
        write("'Je fini mon café et je vous rejoins, attendez moi à l'acceuil' - Personne de l'acceuil."),nl,
        write("derrière vous se trouve la sortie"),nl,
        !.

% ----- salle de cours -----
decrire(salle_de_cours) :-
        action(janette,non),
        write("[[ 4A 62 ]]"),nl,
        write("Jeannette est en face de vous. Vous pouvez aller lui parler (parler(janette))"),nl,
        !.

decrire(salle_de_cours) :-
        action(janette,oui),
        write("[[ 4A 62 ]]"),nl,
        !.

% ----- EVE -----
decrire(eve) :-
        write("[[ EVE ]]").

% ######################## dialogue ###################

%janette_dialogue1
dialogue(janette) :-
        write("Jean : Bonjour janette ! Comment tu vas ?"),nl,
        write("Janette : Je n'est pas de stylo et je ne pourrais pas suivre le cours sans."),nl,
        nl,
        nl,
        write("a - je peux te donner le mien si tu veux"),nl,
        write("b - Je n'ai pas de stylo, je suis desolé."),nl,
        !.

dialogue(janette_dialogue1a) :-
        \+ position(stylo,sac),
        % mettre deux retour à la ligne pour le dernier dialogue
        write("Janette : Oh non !!! Tu ne devais pas etre reveillé tu as oublié ton stylo."),nl,nl,
        retract(action(janette, non)),
        assert(action(janette, oui)),
        dialogue_fin(salle_de_cours),
        !.

dialogue(janette_dialogue1a) :-
        position(stylo,sac),
        % mettre deux retour à la ligne pour le dernier dialogue
        write("Janette : Oh !!! Merci beaucoup tu es mon sauveur <3 <3 !!!"),nl,nl,
        retract(action(janette, non)),
        assert(action(janette, oui)),
        retract(position(stylo,sac)),
        retract(inventaire(I)),
        decr(I,Y),
        assert(inventaire(Y)),
        retract(score(Scr)),
        add(Scr,Nscr,150),
        assert(score(Nscr)),
        dialogue_fin(salle_de_cours),
        !.

dialogue(janette_dialogue1b) :-
        % mettre deux retour à la ligne pour le dernier dialogue
        write("Janette : C'est pas grave. Je n'avais qu'à y penser."),nl,nl,
        retract(action(janette,non)),
        assert(action(janette,oui)),
        dialogue_fin(salle_de_cours),
        !.

% Sortie du labyrinthe de dialogue et retour dans celui de salle
dialogue_fin(Salle_de_retour) :-
        write("Le dialogue est fini."),nl,nl,
        position_dialogue(DIA),
        retract(position_dialogue(DIA)),
        assert(position_dialogue(null)),
        position_courante(ICI),
        retract(position_courante(ICI)),
        assert(position_courante(Salle_de_retour)),
        regarder,
        !.
