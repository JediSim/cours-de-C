"""
VISI601_CMI TP1
Florian Dufaure - Simon Pichenot
CMI INFO
"""

import numpy as np
#import numpy.matlib.matrix as mat
import numpy.linalg as lin
import scipy
import matplotlib.pyplot as plt
import scipy.sparse as sp
import time

#Test de vérification
A = np.asmatrix( np.array( [ [1., 3., -2.], [4., -1., 5.], [2., 5., 10.] ] ) )
# determinant
#print( "det(A)=", lin.det(A) )
# conditionnement
#print( "cond(A)=", lin.cond(A) )
# inverse
#print( "A^-1=", lin.inv(A) )

# II
# II.1 
def hilbert(n):
    """
    Retourne la matrice de Hilbert dont les coefficients sont de la forme 1/(i+j+1)
    """
    #On définit une matrice de taille n
    H = np.asmatrix( np.zeros((n,n)) )
    # On parcours la matrice
    for i in range(0,n):
        for j in range(0,n):
            H[i,j] = 1/(i+j+1)
    return H

# Test de hilbert
# tailleMatrice = 3
# print("Matrice de Hibler")
# print(hilbert(tailleMatrice),"")
# print("cond : ")
# print(lin.cond(hilbert(tailleMatrice)),"")

def order( A ):
    """
      Retourne l'ordre d'une matrice carr�e A
      :param A: une matrice n x n
      :return:  son ordre n
    """
    assert A.shape[ 0 ] == A.shape[ 1 ], "[order] matrix A is not square"
    return A.shape[ 0 ]


# II.2
def solveL(L,b):
    """
    résoud un système triangulaire inférieur
    """
    x = np.zeros( (len(b),1) )
    x[0,0] = b[0]/L[0,0]
    for i in range(0,len(b)):
        somme = 0
        for j in range(0,i):
            somme += L[i,j]*x[j]
        x[i,0] = 1/L[i,i]*(b[i]-somme)
    return x

def solveU(u,b):
    """
    résoud un système triangulaire supérieur
    """
    x = np.zeros( (len(b),1) )
    tailleb = len(b)-1
    x[tailleb,0] = b[tailleb]/u[tailleb, tailleb]    
    for i in range(tailleb-1,-1,-1): # faire attention aux indices
        somme = 0
        for j in range(i,tailleb+1):
            somme += u[i,j]*x[j]
        x[i,0] = 1/u[i,i]*(b[i]-somme)
    return x


# # Test solveL
# L=np.asmatrix( [[ 1.,0., 0., 0.],[0.33333333,1.,0.,0.],[0.5,1.,1.,0.],[0.25,0.9,-0.6,1.]] )
# b=np.asmatrix( [[1.],[3.],[2.],[4.]])
# y=solveL(L,b)
# print("y=",y)
# print("L*y=", L*y)
# print("b=", b)
# print(lin.norm(L*y-b,2))

# # Test de solveU
# U = np.asmatrix(
#     [[1.,1.,2.],
#      [0.,-3.,-2.],
#      [0.,0.,1.]
#     ]
# )
# c = np.asmatrix([[-1.],[-2.],[-2.]])
# z= solveU(U,c)
# print("z=",z)
# print("U*z=", U*z)
# print("c=", c)
# print(lin.norm(U*z-c,2))

# III Décomposition LU

# III.1 Elimination de Gauss avec pivot sur la diagonale

def LU( A ):
    """
    calcul la décomposition LU de A
    """
    L = np.asmatrix( np.eye( len( A ) ) )
    k =0;
    for i in range(0,len(A)):
        for j in range(i+1,len(A)):
            coeff = A[j,i]/A[i,i]
            if(coeff !=0):
                A[j:j+1] -= coeff*A[i:i+1]
                L[j,i] = coeff
            else:
                return L, A, k
        k += 1
    return L,A,k

def VDM(x):
    n = len(x)
    V = np.asmatrix( np.ones((n,n)) )
    for i in range(0,n):
        for j in range(1,n):
            V[i,j] = V[i,j-1]*x[i]
    return V

# Test de la décomposition LU
# V=VDM([1.5, 2.8, 4.0, 7.3])
# L,P,k=LU(V)
# print("L : ",L)
# print("P : ",P)
            
# III.2 Résolution Ax=b par LU

def solveByLu( A, b):
    L,P,k = LU(A)

    if(k != len(A)):
        return -1
    
    y = solveL(L,b)
    x = solveU(P,y)
    return x

# Test de solveByLu
# A = np.asmatrix(
#     [[1.,1.,2.],
#      [2.,-1.,2.],
#      [4.,1.,4.]
#     ]
# )
# b = np.asmatrix([[-1.],[-4.],[-2.]])
# x= solveByLu(A,b)
# print("x : ",x)

# X = [1.5, 2.8, 4.0, 7.3]
# Y = [3.2, 1.4, 1.0, 2.7]
# V = VDM(X)
# b = np.asmatrix(Y).transpose()
# C = solveByLu(V,b)
# print(C)


# ax=plt.subplot()
# xvals = np.arange(0, 10, 0.01)
# yvals = [C[0].item()+C[1].item()*x+C[2].item()*x*x+C[3].item()*x*x*x for x in xvals]
# ax.plot(xvals, yvals)
# ax.plot(X,Y,color="red")
# plt.show()

# III.3 Application à l’interpolation polynomiale
def tracePolynomeLagrange(X,Y):
    #Calcul le polynome de Lagrange
    V = VDM(X)
    b = np.asmatrix(Y).transpose()
    C = solveByLu(V,b)
    yvals = []
    xvals = np.arange(0, len(X)-1, 0.01)
    for j in range(len(xvals)):
        y_val = 0
        for i in range(len(C)):
            y_val += C[i].item()*(xvals[j]**i)
        yvals.append(y_val)

    #print(yvals)
    #yvals = [C[0].item()+C[1].item()*x+C[2].item()*x*x+C[3].item()*x*x*x for x in X]
    ax=plt.subplot()
    ax.plot(xvals, yvals)
    ax.plot(X,Y,color="red")
    plt.show()

# X = [1.5, 2.8, 4.0, 7.3]
# Y = [3.2, 1.4, 1.0, 2.7]
X = [0. , 1. , 2. , 3. , 4. , 5. , 6. , 7. , 8. , 9.]
Y = [0.1, 0.0, 0.05,0.1, 0.0,0.1,0.02,0.07,0.0,0.05 ]
#tracePolynomeLagrange(X,Y)

# III.4
# H=hilbert(100)
# L,U,k=LU(H)
# b=np.asmatrix( np.ones( (order(H),1) ) )
# x=solveByLu(H,b)
# print(lin.det(H))
# print(lin.cond(H))
# print(lin.norm(H*x-b))
# le résidu Ax-b est linéaire à n, les 2 valeurs sont presque tout le temps égale

## III.5
def inverseByLU( A ):
    L,U,k = LU(A)
    I = np.asmatrix( np.eye(len(A)) )
    X = np.zeros((len(A),len(A)))

    if(k != len(A)):
        return -1
    
    for i in range(0,len(A)):
        y = solveL(L,I[:,i])
        X[:,i] = solveU(U,y).transpose()

    return X

# n=20
# H=hilbert(n)
# invA=inverseByLU(H)
# b=np.asmatrix( np.ones( (order(H),1) ) )
# for i in range(1,n):
#     b[i] = b[i-1]/2
# print(lin.det(H))
# print(lin.cond(H))
# x = invA*b
# print(lin.norm(H*x-b))
"""
Le résidu est bien plus faible avec cette méthode
"""

## III.6
# H=np.asmatrix( np.array( [[1e-20,1.],[1.,1.]]))
# b=np.asmatrix( np.ones( (order(H),1) ) )
# L,U,k=LU(H)
# # LU - H est tr\u00e8s diff\u00e9rent de 0
# print(L*U-H)
# # la solution reste correcte
# x=solveByLu(H,b)
# print(x)

#! Cette fonction ne marche pas, nous avons un problème entre l'indice de permutation et j
def rechercheMeilleurCoef(A,j):
    """
    Fonction qui cherche le meilleur coeff pour le pivot
    """
    best_pivot = abs(A[0])
    indice_permutation = j
    for i in range(j,len(A)):
        if(best_pivot < abs(A[i])):
            best_pivot = abs(A[i])
            indice_permutation += 1
    return best_pivot, indice_permutation
 

def permutationLignes(A,i,j):
    tempo = A[j:j+1].copy()
    A[j:j+1] = A[i:i+1]
    A[i:i+1][:] = tempo
    return A

#! La fonction marche correctement mais dans nos test, pour la valeur en postion [3,2] (version python) s'affiche
#! avec une valeur de 8.8*10^(-16) au lieu de 0, mais on voit bien que c'est juste un problème d'approximation que nous n'avons pas réussi à gérer
def LUP( A ):
    """
    calcul la décomposition LU de A
    """
    L = np.asmatrix( np.eye(len(A)) )
    k =0
    #Matrice de permutation
    P = np.asmatrix( np.eye(len(A)) )
    for i in range(0,len(A)):
        coeff, indice = rechercheMeilleurCoef(A[i:len(A),i],i)
        P = permutationLignes(P,indice,i)
        A = permutationLignes(A,indice,i)
        for j in range(i+1,len(A)):
            if(coeff !=0):
                coeffRatio = A[j,i]/coeff
                vraiCoeff = coeffRatio*A[i:i+1]
                if(A[j,i] <0 and vraiCoeff[0,i] > 0):
                    A[j:j+1] += vraiCoeff
                    L[j,i] = -coeffRatio
                else:
                    A[j:j+1] -= vraiCoeff
                    L[j,i] = coeffRatio
            else:
                return L, A, P, k
        k += 1
    return L,A,P,k

# X = [1.5, 2.8, 4.0, 7.3]
# Y = [3.2, 1.4, 1.0, 2.7]
# V = VDM(X)
# Vbis = V.copy()
# L,U,P,k = LUP(Vbis)
# print("L : ",L)
# print("U : ",U)
# print("P : ",P)
# print("L*U : ",L*U)
# print("P*V : ",P*V)

## III.7
def solveByLUP( A, b):
    L,U,P,k = LUP(A)

    if(k != len(A)):
        return -1
    
    Abis = P*A
    y = solveL(L,P*b)
    x = solveU(U,y)
    return P*x #Normalement faut pas faire ca et faut juste renvoyer x

#Test de solveByLu
# A = np.asmatrix(
#     [[1.,1.,2.],
#      [2.,-1.,2.],
#      [4.,1.,4.]
#     ]
# )
# b = np.asmatrix([[-1.],[-4.],[-2.]])
# x= solveByLUP(A,b)
# print("x : ",x)

# B=hilbert(420)
# start=time.time()
# L,U,P,k=LUP(B)
# end=time.time()
# print(end-start)

# Générateur de matrice Laplacienne
def gridCooMatrix( n, random=True ):
    """Returns a Laplacian-like matrix. If random=True, indices of
    vertices are randomly chosen.
    """
    V = [] # values
    R = [] # rows
    C = [] # columns
    N=n*n
    A = [i for i in range(N)]
    if (random):
        A = np.random.permutation( N )
    for r in range(n*n):
        V.append(-4.)
        R.append(A[r])
        C.append(A[r])
        V.append(1.)
        R.append(A[(r+1)%N])
        C.append(A[r])
        V.append(1.)
        R.append(A[(r+N-1)%N])
        C.append(A[r])
        V.append(1.)
        R.append(A[(r+n)%N])
        C.append(A[r])
        V.append(1.)
        R.append(A[(r+N-n)%N])
        C.append(A[r])
    return sp.coo_matrix( (V,(R,C)), shape=(N,N))


def structure( M ):
    n = M.shape[0]
    A = np.asmatrix( np.zeros((n,n)))
    for i in range(len(M.indptr)-1):
        print("i",i)
        for j in range(M.indptr[i],M.indptr[i+1]):
            print("j",j)
            A[i, M.indices[j]] = M.data[j]
    print("fini")
    return A

def occupancy(M):
    plt.imshow( structure(M) )
    plt.show()
M_coo = gridCooMatrix( 10 )
M     = M_coo.tocsc()
# M_coo.todense()
# print(structure(M_coo))
occupancy(M)