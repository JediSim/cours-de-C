# TP1 Algorithmique info503

listes = [[6,7,8,68,90],[5,16,52,80,90],[1,4,9,10,20,56],[6,8,10,17,25,33,48,56,61,70]]

# arbre_test = [1,0,2,3,4,2]

liste_fusion = []


def affiche_arbre(arbre):
    end_level=0
    for i in range(len(arbre)):
        print(arbre[i],"",end="")
        if i == end_level:
            print("")
            end_level =(end_level+1)*2
    print("")

def affiche(arbre,listes,liste_fusion):
    print("La liste de fusion : ",end=" ")
    print(liste_fusion)
    print("L'arbre : ")
    affiche_arbre(arbre)
    print("Listes : ")
    print(listes)

def update(arbre,listes):
    debut_feuilles=len(arbre)-len(listes)
    for i in range(debut_feuilles-1,0,-1):
        print(i,i*2,i*2+1)
        if arbre[i*2] != None and arbre[i*2+1]!=None:
            mini=min(arbre[i*2],arbre[i*2+1])
        elif arbre[i*2]==None:
            mini=arbre[i*2+1]
        else:
            mini=arbre[i*2]
        arbre[i]=mini
    arbre[0]=min(arbre[1],arbre[2])

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


def remonte(arbre,listes):
    res=arbre[0]
    debut_feuilles=len(arbre)-len(listes)
    done=False
    for i in range(debut_feuilles,len(arbre)):
        if arbre[i]==res and not done:
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
            arbre[i]=val
            done=True
    return res,arbre

def listes_pas_vide(listes):
    for l in listes:
        if l!=[None]:
            return True
    return False
        

def fusion(listes):
    liste_fusion = []
    arbre = initArbre(listes)
    while(listes_pas_vide(listes)):
    #for i in range(5):
        print("DEBUT DE LA REMONTE (MAJ FEUILLE)")    
        to_append,arbre=remonte(arbre,listes)
        print("FIN REMONTE")
        print("a ajouter",to_append)
        liste_fusion.append(to_append)
        print("DEBUT DE LA MISE A JOUR")
        affiche(arbre,listes,liste_fusion)
        arbre= update(arbre,listes)
        print("FIN DE LA MISE A JOUR")
        affiche(arbre,listes,liste_fusion)
    return ...

# arbre = initArbre(listes)
# affiche(arbre,listes,liste_fusion)
fusion(listes)

