# TD 1

## exo 1

- question 1 :

```c++
    int distance_code(T,t)
    {
        int dist_min = 64;
        for (int i = 0; i < t; i++)
        {
            for (j = i+1;j < l; j++)
            {
                if(tmp = dist_hamming(T[i],T[j]) < dist_min)
                {
                    d = tmp;
                }
            }
        }
        return dist_min;
    }

    int dist_hamming(x,y)
    {
        int count = 0;
        int compare = x ^ y;
        for (int i = 0; i < 64; i++)
        {
            count += (compare >> i) & 1;
        }
        return count;
    }
```

- question 2 :

Pour obtenir toutes les mots possibles du code on fait le $\oplus$ de chaque ligne de la matrice.

$\begin{bmatrix}
0 & 1 & 1 & 0\\
1 & 1 & 0 & 0\\
1 & 1 & 1 & 1
\end{bmatrix}$

Avec cette matrice ca donne :

0000
0110 $L_1$
1111 $L_2$
1100 $L_3$
1010 $L_1 \oplus L_2$
1001 $L_1 \oplus L_3$
0011 $L2 \oplus L_3$
0101 $L_1 \oplus L_2 \oplus L_3$

- question 3 :



## exo 2

- question 1 :

Matrice génératrice du code 3-répétitions

$G = \begin{bmatrix}
1 & 0 & 0 & 1 & 0 & 0 & 1 & 0 & 0\\
0 & 1 & 0 & 0 & 1 & 0 & 0 & 1 & 0\\
0 & 0 & 1 & 0 & 0 & 1 & 0 & 0 & 1
\end{bmatrix}$

Matrice de parité du code 3-répétitions

$P = \begin{bmatrix}
1 & 0 & 0 & 1 & 0 & 0\\
0 & 1 & 0 & 0 & 1 & 0\\
0 & 0 & 1 & 0 & 0 & 1\\
1 & 0 & 0 & 0 & 0 & 0\\
0 & 1 & 0 & 0 & 0 & 0\\
0 & 0 & 1 & 0 & 0 & 0\\
0 & 0 & 0 & 1 & 0 & 0\\
0 & 0 & 0 & 0 & 1 & 0\\
0 & 0 & 0 & 0 & 0 & 1
\end{bmatrix}$

nb de mots : $2^{lignes} = 8$
distance : 3
nb d'erreurs detetées : 2
nb d'erreurs corrigées : 1

- question 2 :

    - avec 0 erreur : $0,9^{3} = 0,729 = 72,9 \%$
    - avec 1 erreur : $0,9^{2} \times 0,1 \times 3 = 0,243 = 24,3\%$
    - avec 2 erreurs : $3 \times 0,1^2 \times 0,9 = 0,027 = 2,7\%$
    - avec 3 erreurs : $0,1^3 = 0,001 = 0,1\%$

proba d'erreur après correction : proba 2 erreurs + proba 3 erreurs = $2,8\%$

- question 3 :
Avec le code "5-répétitions" on à les mêmes calcul mes avec des proba plus faible.

## exo 3

## exo 4 code de Hamming, variante

- question 1 :

- question 2 :

$G = n \times k$

permet de coder des mots de taille k en mots de taille n.


## exo 5