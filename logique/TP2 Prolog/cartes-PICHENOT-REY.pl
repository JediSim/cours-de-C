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


solution(L) :-
    L = [_,_,_,_],            % la solution contient 4 éléments

    contient(L, pique),       % la solution contient les 4 as
    contient(L, coeur),       % ...
    contient(L, trefle),      % ...
    contient(L, carreau),     % ...

    % en position 2, il n'y a ni l'as de trefle, ni l'as de pique
    \+ deuxieme(trefle,L),
    \+ deuxieme(pique,L),

    % l'as de trefle est plus a droite que l'as de carreau
    devant(carreau,trefle,L),

    % l'as de carreau et l'as de coeur ne sont pas voisins
    \+ voisin(coeur,carreau,L).