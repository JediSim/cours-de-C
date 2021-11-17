# TP2 Algorithmique info503
import random
import time
#-----QUESTION 1
def tri_bulle(T):
    """
    Fonction de tri à bulle
    param :
        - T : [list] liste à trier
    return :
        - T : [list] liste triée
    """
    for i in range(len(T)-1,1,-1):
        for j in range(0,i):
            if T[j+1] > T[j]:
                T[j+1], T[j] = T[j], T[j+1]
    return T
#-----QUESTION 2
def tri_dobosiewicz(tab):
    intv = len(tab)
    fini = True
    while intv > 1 or fini:
        intv = max(1, int(intv / 1.3))
        fini = False
        for i in range(len(tab) - intv):
            j = i+intv
            if tab[i] > tab[j]:
                tab[i], tab[j] = tab[j], tab[i]
                fini = True
#Fonctionnement de l'algo :
#
#   XXXXXXXXXXXXXXXxx
#
# L'idée maîtresse de la conception est de comparer un élément avec un autre qui est éspacé d'un certain intervalle.
# On réduit cet intervalle à chaque passe de l'agorithme. Jusqu'à un intervalle de 1 en fin de traitement.
                
#-----QUESTION 3

list_size=5000
l = [random.randint(0,100) for i in range(list_size)]

print("liste init")
#Bulle
start_bulle = time.perf_counter()
trie = tri_bulle(l)
end_bulle = time.perf_counter()
print("Temps pour le trie par bulle :",end_bulle-start_bulle)

#Dobosiewicz
start_dobosiewicz = time.perf_counter()
trie = tri_dobosiewicz(l)
end_dobosiewicz = time.perf_counter()
print("Temps pour le trie de Dobosiewicz :",end_dobosiewicz-start_dobosiewicz)

#-----TESTS

#Python sort
# start_py = time.perf_counter()
# trie = sorted(l)
# end_py = time.perf_counter()
# print("Temps pour le trie de pyton :",end_py-start_py)


#PARTIE 2

#Question 1
class Noeud:
    def __init__(self):
        self.sg = None
        self.sd = None
        self.racine = None

#Question 2



