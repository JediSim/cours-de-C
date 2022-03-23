from random import randint
from utils import question

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

def assertion3(tab, k, i, x):
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
        assert assertion3(tab, k, i, x)
        tab[k+1] = x
        assert estTrieSurInterval(tab, 0, i-1)
    assert estTrieSurInterval(tab, 0, i-1)
    return tab

if __name__ == "__main__": 
    # try:
    tab = [randint(0, 100) for _ in range(10)]
    print("tab : ", tab)
    tab_trie = tri_insert_seq(tab,len(tab)-1)
    print("tab trié : ", tab_trie)
    # except AssertionError:
    #     print("Aïe! Notre sémantique n'est pas bonne...") # N'arrive jamais