from random import randint
from re import T
from utils import question

# ===================================================================== tri insertion

# test si un tableau est trié de 0 à n
def estTrieSurInterval(tab, start, stop):
    """
    vérifie si tab est trié sur [stard..stop], deux bornes incluses
    """
    return tab[start:stop+1] == sorted(tab[start:stop+1])

def assertion1(tab, k, i, x):
    # all = la condition est vrai pour tout j
    premier_membre = all([ tab[j] > x
                            for j in range(k,i+1) ]) 
    second_membre = (tab[i-1] > tab[i]) and estTrieSurInterval(tab,0,i-1)

    return premier_membre or second_membre

def assertion2(tab, k, i, x):
    premier_membre = all([ tab[j] > x
                            for j in range(k,i+1) ])
    second_membre = estTrieSurInterval(tab,0,i-1) and tab[k+1] == tab[k]
    
    return premier_membre and second_membre

def assertion3(tab, k, i, x):
    premier_membre = all([ (tab[j] > x ) 
                            for j in range(k+1,i+1) ])
    second_membre = estTrieSurInterval(tab,1,i-1) and tab[k+2] == tab[k+1]
    
    return premier_membre and second_membre

def assertion4(tab, k, i, x):
    premier_membre = True
    if k > 1:
        premier_membre = all([ (tab[j] <= x ) for j in range(0,k+1) ])

    second_membre = all([ (tab[j] >= x ) for j in range(k+1,i+1)])

    troisieme_membre = True
    if k <= 0:
        troisieme_membre = all([ (tab[j] >= x ) for j in range(0,i+1)])

    quatrieme_membre = estTrieSurInterval(tab,0,i)
    if k+2 < len(tab):
        quatrieme_membre = quatrieme_membre and tab[k+2] == tab[k+1]

    return premier_membre and second_membre or troisieme_membre and quatrieme_membre

def tri_insert_seq(tab, i):
    if i > 0:
        tri_insert_seq(tab,i-1)
        assert estTrieSurInterval(tab, 0, i-2)
        k = i-1
        x = tab[i]
        while k >= 0 and tab[k] > x:
            assert assertion1(tab, k, i, x)
            tab[k+1] = tab[k]
            assert assertion2(tab, k, i, x)

            k-=1
            assert assertion3(tab, k, i, x)
        assert assertion4(tab, k, i, x)
        tab[k+1] = x
        assert estTrieSurInterval(tab, 0, i-1)
    assert estTrieSurInterval(tab, 0, i-1)
    return tab

# ===================================================================== tri tas

def assertion_est_tas(t, p):
    for i in range(1, p):
        if 2*i < p and 2*i+1 < p:
            if t[i] > t[2*i] or t[i] > t[2*i+1]:
                return False
    return True 

implique = lambda p, q: not p or q
# { p = n ET t[1..p] est un tas } => { t[1..n] est un tas }
def assertion2_tas(t):
    n = len(t) - 1
    return implique(
        t[0] == n and assertion_est_tas(t, t[0]),
        assertion_est_tas(t,n)
    )

def assertion3_tas(t):
    """
    La fonction assertion3_tas(t) renvoie Vrai si t est un tas et si les éléments de t sont en ordre
    strictement decroissant
    
    :param t: the tableau
    :return: Vrai ou faux
    """
    p = t[0]
    est_tas = assertion_est_tas(t, p)
    decroissant = True
    petit = True
    for i in range(p+1, len(t)-1):
        if t[i] < t[i+1]:
            decroissant = False
    
    for i in range(1,p):
        if t[i] < t[p+1]:
            petit = False

    return est_tas and decroissant and petit
    
# { p = 1 ET t[1] >= t[2] ET t[2..n] est trié dans l'ordre décroissant } => { t[1..n] est trié dans l'ordre décroissant }
def assertion4_tas(t):
    p = t[0]
    p_est_1 = p == 1 and t[1] >= t[2]
    decroissant = True
    for i in range(2, len(t)-1):
        if t[i] < t[i+1]:
            decroissant = False
    
    partie1 = p_est_1 and decroissant

    partie2 = True
    for i in range(1,len(t)-1):
        if t[i] < t[i+1]:
            partie2 = False

    return not partie1 or partie2

def assertion5_tas(t, j):
    """ { t[j] est la plus petit des 2 fils s'ils existent ou le fils unique le cas échéant } """

    if j % 2 == 0: # j est le fils gauche
        # si j+1 n'existe pas, on retourne true
        if j+1 >= t[0]: # t[0] == taile du tas
            return True
        return t[j] <= t[j+1]
    else: # j est le fils droit
        return t[j] <= t[j-1]


# Permute les éléments i et j du tab
def permuter(tab, i, j):
    temp = tab[i]
    tab[i] = tab[j]
    tab[j] = temp

# ajoute un élement dans le tas
def ajouter_tas(t, x):
    t[0] = t[0] + 1
    i = t[0]
    t[i] = x
    
    while i>1 and t[int(i/2)] > t[i]: ######## assertion 
        permuter(t, i, int(i/2))
        i = int(i/2)
    
# retire le racine du tas (i.e. le plus petit élément) et le renvoie, puis réorganise le tas
def retirer_min(t):
    min = t[1]
    t[1] = t[t[0]]
    t[0] = t[0] - 1
    i = 1
    fini = False

    while i <= int(t[0]/2) and not fini:

        if t[0] == 2*i or t[2*i] < t[2*i + 1]:
            j = 2*i
        else:
            j = 2*i + 1

        # { t[j] est la plus petit des 2 fils s'ils existent ou le fils unique le cas échéant }
        assert assertion5_tas(t, j)

        if t[i] > t[j]:
            permuter(t, i, j)
            i = j
        else:
            fini = True
    
    return min

# tri le tableau avec l'algorithme du tri par tas.
def tri_tas(t):
    t[0] = 1

    while t[0] < len(t)-1:
        ajouter_tas(t, t[t[0]+1])
        # { t[1..p] est un tas }
        assert assertion_est_tas(t, t[0])
    
    # { p = n ET t[1..p] est un tas } => { t[1..n] est un tas }
    assert assertion2_tas(t)

    while t[0] > 1:
        min = retirer_min(t)
        t[t[0]+1] = min
        # { t[1..p] est un tas ET t[p+1..n] est trié dans l'ordre décroissant ET Pour tout e€[1..p], t[e] >= t[p+1] }
        assert assertion3_tas(t)

    # { p = 1 ET t[1] >= t[2] ET t[2..n] est trié dans l'ordre décroissant } => { t[1..n] est trié dans l'ordre décroissant }
    assert assertion4_tas(t)

def printNiveau(a,nb,n):
    for _ in range(0,2*n):
        print(" "*2,end="")
    print(a[nb])

def affiche_arbre(a,i,niveau):
    if i < len(a):
        affiche_arbre(a,i*2+1,niveau+1)
        printNiveau(a,i,niveau)
        affiche_arbre(a,i*2+2,niveau+1)

if __name__ == "__main__": 
    # try:
    # tab = [None]
    tab = [randint(0, 100) for _ in range(100)]
    print("tab : ", tab)
    tab_trie = tri_insert_seq(tab,len(tab)-1)
    # print("tab trié : ", tab_trie)
    # except AssertionError:
    #     print("Aïe! Notre sémantique n'est pas bonne...") # N'arrive jamais
    # tri_tas(tab)
    print("tab trié : ", tab_trie)
    # affiche_arbre(tab[1:],0,1)
