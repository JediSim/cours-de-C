% pour montrer qu'un "truc" est mortel, il suffit de montrer que c'est un humain
% Autrement dit "tous les humains sont mortels"
mortel(X) :- humain(X).

% pour montrer qu'un "truc" est un humain, il suffit de montrer que c'est un philosophe
% Autrement dit "tous les philosophes sont des humains"
humain(X) :- philosophe(X).

% Louis XIV est un humain
humain(louis_XIV).

% Socrate est un philosophe
philosophe(socrate).

% Milou est un chien !
chien(milou).
