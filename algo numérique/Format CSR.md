# Format CSR

1. ecrire `sommeLigne(A)` avec une representation matrice creuse

$A = \begin{bmatrix}
0 & 3 & 0 & 0 & 1 \\ 
1 & 0 & 0 & 2 & 0 \\
0 & 0 & 2 & 0 & 0 \\
0 & 0 & 4 & 2 & 0 \\
0 & 1 & 0 & 0 & 0 \\
\end{bmatrix}$

```py
class CSR:
    def __init__(self,data,indices,indptrr):
        self.data = data
        self.indices = indices
        self.indptrr = indptrr

    def sommeLigne(self,i):
        sum = 0
        for j in range(self.indptrr[i],self.indptrr[i+1]):
            sum += self.data[j]
        return sum
        
    def at(self,i,j):
        for k in range(self.indptrr[i],self.indptrr[i+1]):
            if self.indices[k] == j:
                return self.data[k]
        return 0

    def produit(self,v):
        """
        produit d'une matrice avec un vecteur
        """
        res = []
        for k in range(len(self.indptrr)-1):
            sum = 0
            for q in range(self.indptrr[k],self.indptrr[k+1]):
                indice = self.indices[q]
                sum += self.data[q] * v[indice]
            res.append(sum)
        return res

data = [3,1,1,2,2,4,2,1]
indices = [1,4,0,3,2,2,3,1]
indptrr = [0,2,4,5,7,8] # le dernier élément est set avec le nombre d'élément
matrice = CSR(data,indices,indptrr)
print(matrice.sommeLigne(4),"")
print(matrice.at(3,2),"")
print(matrice.produit([1,1,1,1,1]))
```

