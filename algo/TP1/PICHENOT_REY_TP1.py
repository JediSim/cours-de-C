# TP1 Algorithmique info503

listes = [[6,7,8,68,90],[5,16,52,80,90],[1,4,9,10,20,56],[6,8,10,17,25,33,48,56,61,70]]

# arbre_test = [1,0,2,3,4,2]

liste_fusion = []


def affiche_arbre(arbre):
    """
    Procédure qui affiche l'arbre dans la console
    param : [list] arbre
    """
    end_level=0
    for i in range(len(arbre)):
        print(arbre[i],"",end="")
        if i == end_level:
            print("")
            end_level =(end_level+1)*2
    print("")

def affiche(arbre,listes,liste_fusion):
    """"
    Procédure qui affiche la liste de fusion, la liste des monotonies et l'arbre
    param :
    - arbre [list]
    - listes [list][list]
    - liste_fusion [list]
    """
    print("La liste de fusion : ",end=" ")
    print(liste_fusion)
    print("L'arbre : ")
    affiche_arbre(arbre)
    print("Listes : ")
    print(listes)

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

def arbre_pas_vide(arbre):
    """ test si l'abre en parametre est vide
    return : [bool]
    """
    return arbre[0]!=None
        

def fusion(listes):
    #init
    liste_fusion = []
    arbre = initArbre(listes)
    affiche(arbre,listes,liste_fusion) #affiche avant trie
    #tant que l'arbre n'est pas vide
    while(arbre_pas_vide(arbre)):        
        #ajoute la racine dans la liste de fusion
        r=arbre[0]
        liste_fusion.append(r)
        #et met a jour la feuille correspondante
        arbre=remonte(arbre,listes,r)
        #met a jour l'arbre
        arbre= update(arbre,listes)
    affiche(arbre,listes,liste_fusion) #affiche arpès trie
    
    
fusion(listes)

