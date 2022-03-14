# TD1

### 2 determination de post-conditions à partir de pré-conditions

${(x = 10) \land (y > 0)} a := (x = 10) \rightarrow a \land (y > 0)$
$(t = 3x + 2y)\ x := x+3y \rightarrow $

### 3.1 pgcd

```
fonction pgcd(in a,b : entier);
var
    x,y : entier;

debut
    x:=a;
    y:=b;
    tantque x!=y faire
        si x>y alors
            x:=x-y;
        sinon
            y:=y-x;
    fintantque
    pgcd:=x;
fin;
```

### 3.2 Recherche d'un élément dans un tableau

```
fontion recherche(in e:element, in t:tableau de element); 1..n (ou vide)
var 
    k:1..n+1;

debut
    k:=1;
    tantque t[k]!=e et k<=n faire
        k:=k+1;
    fintantque;
    si k<=n alors
        retourne k;
    sinon
        retourne vide;
    finsi;
fin;
```

## Exo n trie par selection : 

```
fonction tri_selection(in t:tableau de entier); 1..n (ou vide)
    i:=1;
    tantque i<n faire
        j:=i;
        pour k:=i+1 jusqua n faire
            si t[k]<t[j] alors
                j:=k;
            finsi;
            <!-- {} -->
        finpour;
        permuter(T[i],T[j]);
        i:=i+1;
    fintantque;
fin;
```