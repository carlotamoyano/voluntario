# -*- coding: utf-8 -*-
"""
Created on Fri Jun  2 18:39:35 2023

@author: carlo
"""

from pylab import*
from numpy import*
import numpy as np
from numpy.linalg import*

import scipy.optimize as so

import matplotlib.pyplot as plt


# Datos
T = np.array([1.500000, 1.700000, 1.900000, 2.100000, 2.300000, 2.500000, 2.700000, 2.900000, 3.100000, 3.300000, 3.500000])
mN = np.array ([0.986507, 0.485121, 0.312836, 0.217274, 0.000401, 0.000018, -0.000087, -0.000073, 0.000026, 0.000037, 0.000016])
def ajustecuadratico(x,y,sy):
    nx=len(x); ny=len(y)
    def fun(t,A,B,C):
        yy=A*t**2+B*t+C
        return yy
    uy=sy
    par=[1,1,0]
    sol=so.curve_fit(fun,x,y,p0=(par),sigma=uy,absolute_sigma=True)
    A,B,C=sol[0]; sA,sB,sC=np.sqrt(np.diag(sol[1]))
    yEst=fun(x,A,B,C)
    print('para una función de la forma: Ax^2 + Bx + C')
    print('A= ',A,'+/-',sA);print('B= ',B,'+/-',sB); print('C= ',C,'+/-',sC)
    return[A,B,C,yEst]

#def ajusteexponencial(x,y,sx,sy):
 #   nx=len(x);ny=len(y)
  #  def fun(t,A,B,D):
   #     y=A+B*e**(D*t)
    #    return y
  #  uy=sy; par=[0,1,1]
   # sol = so.curve_fit(fun, x, y, p0=(par), sigma=uy, absolute_sigma=True, maxfev=10000000)
    #A,B,D=sol[0]; sA,sB,sD=np.sqrt(np.diag(sol[1]))
 #   yEst=fun(x,A,B,D)
  #  print('para una función de la forma: A+Be^(Dx)')
   # print('A= ',A,'+/-',sA);print('B= ',B,'+/-',sB); print('D= ',D,'+/-',sD)
    #return[A,B,D,yEst]
def ajustecubico(x,y,sx,sy):
    nx=len(x); ny=len(y)
    def fun(t,A,B,C,D):
        y=A*t**3+B*t**2+C*t+D
        return y
    uy=sy
    par=[1,1,1,0]
    sol=so.curve_fit(fun,x,y,p0=(par),sigma=uy,absolute_sigma=True)
    A,B,C,D=sol[0]; sA,sB,sC,sD=np.sqrt(np.diag(sol[1]))
    yEst=fun(x,A,B,C,D)
    print('para una función de la forma: Ax^2 + Bx + C')
    print('A= ',A,'+/-',sA);print('B= ',B,'+/-',sB); print('C= ',C,'+/-',sC);print('D',D,'+/-',sD)
    return[A,B,C,D,yEst]
sx=np.array([0.0001,0.0001,0.0001,0.0001,0.0001,0.0001,0.0001,0.0001,0.0001,0.0001,0.0001])
sy=sx
[A,B,C,D,yEst] = ajustecubico(T, mN,sx, sy)

y=A*T**3+B*T**2+C*T+D

plt.plot(T,y,"g")


from sympy import symbols, Eq, solve

T = symbols('T')
equation = Eq(A * T**3 + B * T**2 + C * T + D, 0)
solution = solve(equation, T)

print("El valor de T cuando y = 0 es:")
print(solution)