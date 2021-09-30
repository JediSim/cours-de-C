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