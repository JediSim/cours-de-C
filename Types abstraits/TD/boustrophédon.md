```algo
fonction sans retour triBulleBoustrophédon(entier tab[])
    entier i,j,k,temp;
    booléen trié;
début
    trié <- faux; j <- tab.longueur; i <- -1;
    tantque ((non trié) et (j > i)) faire
        trié <- vrai;
        pour (k allant de i+1 à j-2 pas 1) faire
            si (tab[k] > tab[k+1]) alors
                temp <- tab[k]; tab[k] <- tab[k+1]; tab[k+1] <- temp;
                trié <- faux;
            finsi
        finpour
        j <- j-1;
        pour (k allant de j-1 à i+2 pas -1) faire
            si (tab[k] < tab[k-1]) alors
                temp <- tab[k]; tab[k] <- tab[k-1]; tab[k-1] <- temp;
                trié <- faux;
            finsi
        finpour
        i <- i+1;
    fintantque
fin
```