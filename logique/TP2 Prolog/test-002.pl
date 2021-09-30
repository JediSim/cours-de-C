%
% Theophile Eugenie
%    |         |
%    +----+----+
%         |
%    +----+--------------------+-------------------------------+
%    |                         |                               |
% Edith  Pierre             Louise  Francois                Jean-Francois
%   |       |                 |         |
%   +---+---+                 +----+----+
%       |                          |
%   +---+-------------+            |
%   |                 |            |
% Julie Laurent     Thomas    Isabelle   Sebastien
%   |     |                      |           |
%   +--+--+                      +-----+-----+
%      |                               |
%   +--+---------------+               |
%   |                  |               |
%  Lea  Leo          Hugo           Kevin  Samanta
%   |    |                             |      |
%   +--+-+                             +------+
%      |                               |      |
%    Gaia                            Téo     Luna
%
:- discontiguous pere/2.
:- discontiguous mere/2.
:- dynamic mere/2.

pere(theophile, edith).
mere(eugenie, edith).
pere(theophile, louise).
mere(eugenie, louise).
pere(theophile, jean_francois).
mere(eugenie, jean_francois).

mere(edith, julie).
pere(pierre, julie).
mere(edith, thomas).
pere(pierre, thomas).

mere(louise, isabelle).
pere(francois, isabelle).

mere(julie, lea).
pere(laurent, lea).
mere(julie, hugo).
pere(laurent, hugo).

mere(isabelle, kevin).
pere(sebastien, kevin).

mere(lea, gaia).
pere(leo, gaia).

mere(samanta, teo).
pere(kevin, teo).

mere(samanta, luna).
pere(kevin, luna).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

grand_pere(GP, PF) :-
    pere(GP, P),
    pere(P, PF) | mere(P, PF).

ancetre(X, Y) :-
    pere(X, Y).
ancetre(X, Y) :-
    mere(X, Y).
ancetre(X, Y) :-
    pere(X, Z),
    ancetre(Z, Y).
ancetre(X, Y) :-
    mere(X, Z),
    ancetre(Z, Y).

fratrie(X,Y) :-
    pere(P, X),
    pere(P, Y),
	X \= Y.

deuxieme(X, []) :- fail.
deuxieme(X, [Y]) :- fail.
deuxieme(X, [Y, Z | L]) :- X = Z.

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

contient1(A,[A|_]).
contient1(A,[_|L]) :- contient1(A,L).

contient2(A,[_|L]) :- contient2(A,L).
contient2(A,[A|_]).

contient3(A,[A|_]) :- !.
contient3(A,[_|L]) :- contient3(A,L).

contient4(A,[_|L]) :- contient4(A,L).
contient4(A,[A|_]) :- !.