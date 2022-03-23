```
procédure tri_insertion(tableau T)
  
    pour i de 1 à taille(T) - 1
    {trié de 1 a i-1}
        # mémoriser T[i] dans x
        x ← T[i]                            

        # décaler les éléments T[0]..T[i-1] qui sont plus grands que x, en partant de T[i-1]
        j ← i                               
        tant que j > 0 et T[j - 1] > x
                    T[j] ← T[j - 1]
                    j ← j - 1

        # placer x dans le "trou" laissé par le décalage
        T[j] ← x 
```
