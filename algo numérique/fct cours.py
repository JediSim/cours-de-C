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
    
    # def at(self,i,j):
    #     for k in range(self.indptrr[i],self.indptrr[i+1]):
    #         if self.indices[k] == j:
    #             return self.data[k]
    #         elif (self.indices[k] > j) # petite opti si on depasse la colonne on s'arrete
    #             return 0
    #     return 0

    def at(self,i,j):
        """
        renvoie la valeur en i,j de la matrice
        On utilise une optimisation de dichotomie pour aller plus vite
        """
        k = self.indptrr[i]
        l = self.indptrr[i+1]
        while k < l:
            m = (k+l)//2
            if self.indices[m] == j:
                return self.data[m]
            elif self.indices[m] < j:
                k = m
            else:
                l = m
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