# TP2 Algorithmique info503
import random
import time
from math import log,ceil
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

list_size=500
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

def printNiveau(a,nb,n):
    for i in range(0,2*n):
        print(" "*2,end="")
    print(a[nb])

def affiche_arbre(a,i,niveau):
    if i < len(a):
        affiche_arbre(a,i*2+1,niveau+1)
        printNiveau(a,i,niveau)
        affiche_arbre(a,i*2+2,niveau+1)

#Question 1
class Arbre:

    #Question 2
    def updateDroit(self):
        i = len(self.sd)-1
        while(i != 1):
            indice_pere = i//2
            if i/2<1:
                indice_pere=0
            # Si le fils est plus grand que le père,
            if self.sd[i] > self.sd[indice_pere] :
                self.swap(self.sd,i,indice_pere)
            if i < len(self.sd):
                if self.sg[i] >= self.sd[i]:
                    self.swapInterArbre(i,i)
                    self.updateGauche()
            else:
                if self.sg[i] >= self.sd[i//2]:
                    self.swapInterArbre(i,i//2)
                    self.updateGauche()
            i = i-1

    def updateGauche(self):
        i=len(self.sg)-1
        while(i != 1):
            # si le fils est plus petit que son père, 
            if self.sg[i] < self.sg[i//2] :
                self.swap(self.sg,i,i//2)

            if i < len(self.sd):
                if self.sg[i] >= self.sd[i]:
                    self.swapInterArbre(i,i)
                    self.updateDroit()
            else:
                if self.sg[i] >= self.sd[i//2]:
                    self.swapInterArbre(i,i//2)
                    self.updateDroit()
            i = i-1
    

    def __init__(self,sg,sd):
        self.sg = [-1]+sg
        self.sd = [-1]+sd

        self.updateGauche()
        self.updateDroit()

    def swap(self,a,i,j):
        a[i],a[j] = a[j],a[i] # on permute

    def swapInterArbre(self,ig,id):
        temp = self.sg[ig]
        self.sg[ig] = self.sd[id]
        self.sd[id] = temp

    
    def hauteur(self,arbre):
        epsilon=0.0000001
        return ceil(log(len(arbre))/log(2)+epsilon)

    def insert(self,n):
        if len(self.sg) == 0:
            self.sg.append(n)
        if (self.hauteur(self.sd) == self.hauteur(self.sg)):
            self.sg.append(n)

            self.updateGauche()
        elif (self.hauteur(self.sd) < self.hauteur(self.sg)):
            self.sd.append(n)
            self.updateDroit()

         

if __name__ == '__main__':
    inp = ""
    sArbreG = [random.randint(1,100)]
    sArbreD = [random.randint(1,100)]
    a = Arbre(sArbreG,sArbreD)
    a.insert(2)
    a.insert(1)
    a.insert(3)
    a.insert(4)
    a.insert(8)
    a.insert(42)
    for i in range(0,15):
        nb = random.randint(1,100)
        a.insert(nb)
        print("a inserer : ",nb)
        print("########## sous arbre gauche ##########")
        # print(a.sg)
        affiche_arbre(a.sg[1::],0,1)
        print("########## sous arbre droit ##########")
        # print(a.sd)
        affiche_arbre(a.sd[1::],0,1)
        if inp != "all":
            inp = input()


    
    