#!/usr/bin/env python3

###
# tous les attribut que l'on peut associer à un emplacement
things = [
    # type de maison
    ["blanche", "bois", "brique", "immeuble", "jaune"],

    # animal
    ["chat", "hamster", "poisson", "tortue", "zebre"],

    # profession
    ["architecte", "boulanger", "chercheur", "footballeur", "musicien"],

    # boisson
    ["biere", "eau", "soda", "the", "whisky"],

    # style de musique
    ["chanson", "classique", "hardrock", "hiphop", "jazz"],
]


def check(a):
    """vérifie que l'argument apparait bien dans les ``things``"""
    from sys import exit, stderr
    for L in things:
        if a in L:
            return
    print(f">>> Problem, the thing '{a}' doesn't exist", file=stderr)
    exit(1)


def implies(a, b):
    """ajoute les clauses correspondant à 'a et b sont au meme endroit'"""
    check(a)
    check(b)
    for i in range(1, 6):
        print(f"-E_{i}_{a} E_{i}_{b}")


def left_of(a, b):
    """ajoute les clauses correspondant à 'a est juste à gauche de b'"""
    check(a)
    check(b)
    for i in range(1, 5):
        print(f"-E_{i}_{a} E_{i+1}_{b}")


def next_to(a, b):
    """ajoute les clauses correspondant à 'a est voisin b'"""
    check(a)
    check(b)
    print(f"-E_1_{a} E_2_{b}")
    for i in range(2, 5):
        print(f"-E_{i}_{a} E_{i-1}_{b} E_{i+1}_{b}")
    print(f"-E_5_{a} E_4_{b}")


def exact(i, a):
    """ajoute les clauses correspondant à 'a est à l'emplacement i'"""
    check(a)
    print(f"E_{i}_{a}")


def constraints_1():
    """ajoute les clauses exprimant 'tous les attributs sont à un emplacement'"""
    print("# TODO")
    for L in things :
        for e in L:
            ligne=""
            for j in range(1,6):
                ligne+=f"E_{j}_{e} "
            print(ligne)


def constraints_2():
    """ajoute les clauses exprimant 'aucun attribut n'est dans 2
    emplacements'"""
    for L in things:
        for a in L:
            for i in range(1, 6):
                for j in range(i+1, 6):
                        print(f"-E_{i}_{a} -E_{j}_{a}")


def constraints_3():
    """ajoute les clauses exprimant 'il n'y a pas deux attribut d'une même
    catégorie sur un emplacement'"""
    for i in range(1, 6):
        for L in things:
            for k in range(len(L)):
                for l in range(k):
                    print(f"-E_{i}_{L[k]} -E_{i}_{L[l]}")


#######################################################################
#######################################################################
#######################################################################

###
# indices

# 1. Le musicien a une tortue
implies("musicien", "tortue")

# 2. Le propriétaire de la maison jaune écoute du jazz.
implies("jaune", "jazz")

# 3. La personne qui écoute du hard-rock a un chat.
implies("hardrock", "chat")

# 4. La maison en bois se trouve juste à gauche de la maison blanche.
left_of("bois","blanche")

# 5. Le chercheur habite dans la maison en briques.
implies("chercheur","brique")

# 6. Le footballeur habite juste à coté de l'immeuble.
next_to("footballeur","immeuble")

# 7. La personne qui écoute de la musique classique est voisine de celle qui boit de la bière.
next_to("classique","biere")

# 8. La personne qui écoute du hiphop boit du thé.
implies("hiphop","the")

# 9. La personne qui habite dans la maison du milieu boit beaucoup de soda.
exact(3,"soda")

# 10. Le footballeur habite dans la première maison.
exact(1,"footballeur")

# 11. La personne qui écoute de la musique classique est voisine de la personne qui a des poissons.
next_to("classique","poisson")

# 12. Le boulanger écoute de la chanson française.
implies("boulanger","chanson")

# 13. La personne qui a un hamster est voisine de celle qui écoute du jazz.
next_to("hamster","jazz")

# 14. L'architecte boit de l'eau
implies("architecte","eau")

# 15. Le propriétaire de la maison en bois aime bien le whisky.
implies("bois","whisky")


###
# contraintes logiques
constraints_1()
constraints_2()
constraints_3()
