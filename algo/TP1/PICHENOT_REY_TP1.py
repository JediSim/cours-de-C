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

def calc_mini(sd,sg):
    if sd != None and sg!=None:
        # print("on compre la mini entre les deux")
        mini=min(sd,sg)
    elif sd==None and sg!=None:
        # print("sg est None donc on renvoie sd")
        mini=sg
    elif sg==None and sd!=None:
        # print("sd est None donc on renvoie sg")
        mini=sd
    else:
        mini=None
    
    return mini

def update(arbre,listes):
    debut_feuilles=len(arbre)-len(listes)
    # print("ARBRE LISTE : ",arbre)

    for i in range(debut_feuilles-1,0,-1):
        # print("INDICES noeud:",i,"sg : ",i*2+1,"sd : ",i*2+2)
        # print("VALUES  noeud:",arbre[i],"sg : ",arbre[i*2+1],"sd : ",arbre[i*2+2])
        mini=calc_mini(arbre[i*2+1],arbre[i*2+2])
        # print("minimum : ",mini)
        arbre[i]=mini
    
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

def arbre_pas_vide(arbre):
    return arbre[0]!=None
        

def fusion(listes):
    liste_fusion = []
    arbre = initArbre(listes)
    affiche(arbre,listes,liste_fusion)
    while(arbre_pas_vide(arbre)): 
        
        to_append,arbre=remonte(arbre,listes)
        liste_fusion.append(to_append)
        arbre= update(arbre,listes)
    affiche(arbre,listes,liste_fusion)
    
    
fusion(listes)

