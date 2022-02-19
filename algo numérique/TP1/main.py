"""
VISI601_CMI TP1
Florian Dufaure - Simon Pichenot
CMI INFO
"""

import numpy as np
import numpy.matrix as mat
import numpy.linalg as lin
#from numpy import *
import scipy

A = np.asmatrix( np.array( [ [1., 3., -2.], [4., -1., 5.], [2., 5., 10.] ] ) )
# determinant
print( "det(A)=", lin.det(A) )
# conditionnement
print( "cond(A)=", lin.cond(A) )
# inverse
print( "A^-1=", lin.inv(A) )