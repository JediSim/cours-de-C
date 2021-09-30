deuxieme(X, [_, X | _]).

contient([X | _], X).
contient([_ | L], X) :- contient(L, X).

dernier(X,[X]).
dernier( X,[_ | L]) :- dernier(X, L).

voisin(X,Y,[X,Y|_]).
voisin(X,Y,[Y,X|_]).
voisin(X,Y,[_ | L]) :- voisin(X,Y,L).

devant(X,Y,[X|L]) :-
    contient(L,Y).
devant(X,Y,[_ | L]) :- devant(X,Y,L).

solution2(L) :-
    L = [_, _, _, _, _],              % il y a 5 maisons
    
   	%le musicien a une tortue
    contient(L, maison(_,musicien,tortue,_,_)),
    %le propriétaire de la maison jaune écoute du jazz ;
    contient(L, maison(jaune,_,_,jazz,_)),
    %la personne qui écoute du hardrock a un chat ;
    contient(L, maison(_,_,chat,hardrock,_)),          
    %la maison en bois se trouve juste à gauche de la maison blanche ;
    voisin(maison(bois,_,_,_,_),maison(blanche,_,_,_,_),L),
    devant(maison(bois,_,_,_,_),maison(blanche,_,_,_,_),L),
    %le chercheur habite dans la maison en briques ;
    contient(L, maison(briques,chercheur,_,_,_)),
    %le footballeur habite juste à coté de l'immeuble ;
    voisin(maison(_,footballeur,_,_,_),maison(immeuble,_,_,_,_),L),
    %la personne qui écoute de la musique classique est voisine de celle qui boit de la bière ;
    voisin(maison(_,_,_,classique,_),maison(_,_,_,_,biere),L), 
    
    contient(L, maison(_,_,_,hiphop,the)), %8

	L = [_,_,maison(_,_,_,_,soda),_,_], %9
    
    L = [maison(_,footballeur,_,_,_),_,_,_,_], %10
    
    voisin(maison(_,_,_,classique,_),maison(_,_,poisson,_,_),L), %11
    
    contient(L, maison(_,boulanger,_,chanson,_)), %12
    
    voisin(maison(_,_,hamster,_,_),maison(_,_,_,jazz,_),L), %13
    
    contient(L, maison(_,architecte,_,_,eau)), %14
    
    contient(L, maison(bois,_,_,_,wisky)), %15

	contient(L, maison(_,_,zebre,_,_)). %