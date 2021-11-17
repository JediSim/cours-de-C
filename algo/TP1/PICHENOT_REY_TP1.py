# TP1 Algorithmique info503

import random

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

# arbre_test = [1,0,2,3,4,2]

# liste_fusion = []

def init(n,s):
    print("\nles monotonies sont choisis aléatoirement\n")
    monotonies=[]
    for i in range(n):
        sizeMonotonie=random.randint(2,s)
        monotonies.append(sorted([random.randint(0,100) for i in range(sizeMonotonie)]))

    return monotonies

def arbre_pas_vide(arbre):
    """ test si l'abre en parametre est vide
    return : [bool]
    """
    return arbre[0]!=None

def printNiveau(a,nb,feuille,n,listes):

    debut_feuilles=len(a)-len(listes)
    for i in range(0,2*n):
        print(" "*2,end="")
    if feuille:
        print(f"{bcolors.OKBLUE}{a[nb]}{bcolors.ENDC}",f"{bcolors.OKCYAN}{listes[nb-debut_feuilles]}{bcolors.ENDC}")
    else:
        print(a[nb])

def affiche_arbre2(a,i,niveau,nbf,listes):

    if i < len(a):
        affiche_arbre2(a,i*2+1,niveau+1,nbf,listes)
        printNiveau(a,i,i>=len(a)-nbf,niveau,listes)
        affiche_arbre2(a,i*2+2,niveau+1,nbf,listes)


def affiche_arbre(arbre,n):
    """
    Procédure qui affiche l'arbre dans la console
    param : [list] arbre
    """
    # position de la fin de l'étage courant
    end_level=0
    nbespace=(n/2)*10
    line=""
    # on parcourt l'arbre
    for i in range(len(arbre)):
        line+=" "*int(nbespace/2)+str(arbre[i])+" "*int(nbespace/2)
        if i == end_level:
            # retour a la ligne si on est a la fin de l'étage
            print(line)#.center(n*10))
            line=""
            # calcul de l'indice de l'étage suivant
            end_level =(end_level+1)*2
            nbespace=(nbespace)/2
    print(line)

def affiche(arbre,listes,liste_fusion):
    """"
    Procédure qui affiche la liste de fusion, la liste des monotonies et l'arbre
    param :
    - arbre [list]
    - listes [list][list]
    - liste_fusion [list]
    """
    print("############ LISTE DE FUSION ############")
    print(liste_fusion)
    print("################# ARBRE #################")
    if (arbre_pas_vide(arbre)):
        affiche_arbre(arbre)
    else:
        print("Arbre Vide")
    print("############### MONOTONIES ##############")
    for l in listes:
        if l[0]!=None:
            print(l)
        else:
            print("Vide")

def calc_mini(sd,sg):
    """
    Fonction qui renvoie l'élément le plus petit entre sd et sg
    param :
    - sd [int]
    - sg [int]
    return :
    - [int] les plus petit entre sd et sg
    """
    if sd != None and sg!=None:
        # Si il y a une valeur dans le fils droit et le fils gauche
        mini=min(sd,sg)
    elif sd==None and sg!=None:
        # Si il y a une valeur uniquement dans le fils gauche
        mini=sg
    elif sg==None and sd!=None:
        # Si il y a une valeur uniquement dans le fils droit
        mini=sd
    else:
        # Si il n'y a pas de valeur dans les fils
        mini=None
    
    return mini

def update(arbre,listes):
    """
    Fonction qui remonte la bonne valeur dans l'arbre
    param : 
        - arbre [list] l'arbre ou il faut faire remonter le bonne élément
        - listes [list][list] liste des monotonies
    return :
        - arbre [list]
    """
    debut_feuilles=len(arbre)-len(listes)
    #on parcourt l'arbre (sauf la racine) en partant de l'étage le plus bas (juste au dessus des feuilles)
    for i in range(debut_feuilles-1,0,-1):
        #on regarde le minimum entre les sous arbres
        mini=calc_mini(arbre[i*2+1],arbre[i*2+2])
        arbre[i]=mini
    #on met a jour le minium pour la racine
    arbre[0]=calc_mini(arbre[1],arbre[2])

    return arbre

def initArbre(listes):
    """entrée :
        - listes : liste de liste
       return :
        - arbre : arbre sous forme de liste
    """
    arbre = [None]*(len(listes)*2-1)
    #on rempli les feuilles
    debut_feuilles=len(arbre)-len(listes)
    for i in range(debut_feuilles,len(arbre)):
        l = listes[i-debut_feuilles]
        if len(l)==1:
            val=listes[i-debut_feuilles][0]
            listes[i-debut_feuilles][0]=None
        #si liste vide
        elif l[0]==None:
            val=None
        #sinon
        else:
            val =listes[i-debut_feuilles][0]
            del listes[i-debut_feuilles][0]
        arbre[i] = val
    arbre=update(arbre,listes)
    return arbre

def remonte(arbre,listes,r):
    """ met a jour la feuille correspondante à la valeur r (remonte le minimum de la liste)
    paramètres :
        - arbre
        - listes (monotonies)
        - r valeur de la racine qui viens d'être ajouté 
    return : 
        - arbre
    """
    debut_feuilles=len(arbre)-len(listes)
    done=False
    #on parcourt toutes les feuilles
    for i in range(debut_feuilles,len(arbre)):
        #si la valeur de la feuille correspond à celle qu'on doit mettre a jour et qu'on as pas déjà mis a jour une feuille
        if arbre[i]==r and not done:
            l=listes[i-debut_feuilles]
            #si dernier élément de la liste
            if len(l)==1:
                val=listes[i-debut_feuilles][0]
                listes[i-debut_feuilles][0]=None
            #si liste vide
            elif l[0]==None:
                val=None
            #sinon
            else:
                val = listes[i-debut_feuilles][0]
                del listes[i-debut_feuilles][0]
            #on met a jour la feuille
            arbre[i]=val
            done=True
    return arbre


        

def fusion(listes):

    #init
    liste_fusion = []
    arbre = initArbre(listes)
    #affiche(arbre,listes,liste_fusion) #affiche avant trie
    print("################# ARBRE INITIAL #################")

    affiche_arbre2(arbre,0,1,len(listes),listes)
    cptIteration = 0

    #tant que l'arbre n'est pas vide
    while(arbre_pas_vide(arbre)):        
        #ajoute la racine dans la liste de fusion
        r=arbre[0]
        liste_fusion.append(r)
        #et met a jour la feuille correspondante
        arbre=remonte(arbre,listes,r)
        #met a jour l'arbre
        arbre= update(arbre,listes)
        
        cptIteration+=1
        print("################# ARBRE ITERATION " + str(cptIteration) + " #################")
        affiche_arbre2(arbre,0,1,len(listes),listes)
# affiche_arbre2(arbre,len(listes))


    return liste_fusion
    
    
    
   
# fusion(listes)

if __name__ == '__main__':
    	
    nbMonotonies = int(input("Entrez le nombre de monotonies que vous voulez : "))
    size = int(input("Entrez le taille maximale des monotonies : "))
    monotonies = init(nbMonotonies,size)

    mbefore=[]
    sortedOk=[]
    for m in monotonies:
        mbefore.append(m.copy())
        sortedOk+=m.copy()
    
    #verif sort
    sortedOk.sort()

    # listes = [[6,7,8,68,90],[5,16,52,80,90],[1,4,9,10,20,56],[6,8,10,17,25,33,48,56,61,70]]

    

    liste_fusion=fusion(monotonies)

    print("\n\n########### FIN DU TRAITEMENT & VERIFICATIONS ###########")
    #trie
    if liste_fusion==sortedOk:
        print(f"{bcolors.OKGREEN}{liste_fusion}{bcolors.ENDC}")
        print(f"Liste triée ? {bcolors.OKGREEN}OK{bcolors.ENDC}")
    else:
        print(f"{bcolors.WARNING}{liste_fusion}{bcolors.ENDC}")
        print(f"Liste triée ? {bcolors.WARNING}NON{bcolors.ENDC}")

    #monotonies
    for i in range(nbMonotonies):
        print("Monotonie",i,":",mbefore[i])

    # listes = init()