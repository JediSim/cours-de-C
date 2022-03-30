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
    second_membre = (tab[i-1] > tab[i]) and estTrieSurInterval(tab,0,i-2)

    return premier_membre or second_membre

def assertion2(tab, k, i, x):
    premier_membre = all([ tab[j] > x
                            for j in range(k,i+1) ])
    second_membre = estTrieSurInterval(tab,0,i-2) and tab[k+1] == tab[k]
    
    return premier_membre and second_membre

def assertion3(tab, k, i, x):
    premier_membre = all([ (tab[j] > x ) 
                            for j in range(k+1,i+1) ])
    second_membre = estTrieSurInterval(tab,1,i-1) and tab[k+2] == tab[k+1]
    
    return premier_membre and second_membre

def assertion4(tab, k, i, x):
    premier_membre = True
    if k > 1:
        premier_membre = all([ (tab[j] <= x ) for j in range(k+1,i+1) ])

    second_membre = all([ (tab[j] >= x ) for j in range(k+1,i)])

    troisieme_membre = True
    if k <= 0:
        troisieme_membre = all([ (tab[j] >= x ) for j in range(1,i)])

    quatrieme_membre = tab[k+2] == tab[k+1] and estTrieSurInterval(tab,0,i-1)

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

def swap(tab,i,j):
    tmp = tab[i]
    tab[i] = tab[j]
    tab[j] = tmp
    return tab

def ajout_tas(tab,p,x):
    p = p+1
    tab[p] = x
    i = p
    while i > 0 and tab[i//2] > tab[i]:
        tab = swap(tab,i,i//2)
        i = i//2

def retire_min_tas(tab,p):
    mini = tab[0]
    tab[0] = tab[p]
    # p -= 1
    i = 0
    fini = False
    while (i <= (p//2)) and not fini:
        if p == 2*i or tab[2*i] < tab[2*i+1]:
            j = 2*i
        else:
            j = 2*i+1
        
        if tab[i] > tab[j]:
            tab = swap(tab,i,j)
            i = j
        else:
            fini = True

    return mini


def tri_tas(tab):
    p = 0
    while p < len(tab)-1:
        ajout_tas(tab,p,tab[p+1])
        p+=1

    assert p == len(tab)-1

    # p-=1
    while p > 0:
        p-=1
        mini = retire_min_tas(tab,p)
        tab[p+1] = mini
    
    return tab


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
    tab = [randint(0, 100) for _ in range(10)]
    print("tab : ", tab)
    # tab_trie = tri_insert_seq(tab,len(tab)-1)
    # print("tab trié : ", tab_trie)
    # except AssertionError:
    #     print("Aïe! Notre sémantique n'est pas bonne...") # N'arrive jamais
    tab_tri = tri_tas(tab)
    print("tab trié : ", tab_tri)
    affiche_arbre(tab_tri,0,1)
    print(tab[::-1])

