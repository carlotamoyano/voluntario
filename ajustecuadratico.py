# -*- coding: utf-8 -*-
"""
Created on Sun Jun  4 13:11:01 2023

@author: carlo
"""
from pylab import*
from numpy import*
import numpy as np
from numpy.linalg import*

import scipy.optimize as so

import matplotlib.pyplot as plt

c16=np.array([0.287630, 135.961203, 98.472562, 63.650999, 35.933851, 18.729069, 11.124955, 7.302149, 5.107240, 3.651164, 2.729240])
c32=np.array([0.297037, 542.844629, 392.685155, 253.293634, 135.698537, 70.089832, 43.388168, 28.723067, 19.963009, 14.316301, 10.602495])
c64=np.array([0.298697, 2170.796332, 1569.210607, 1010.382013, 525.451247, 278.838039, 172.836066, 114.386313, 79.430685, 57.152146, 42.153753])
c128=np.array([0.293322, 8682.019472, 6277.146001, 4043.608478, 2060.526387, 1114.499534, 690.701307, 456.827227, 317.159134, 228.048055, 168.603617])

T=np.array([1.500000, 1.700000, 1.900000, 2.100000, 2.300000, 2.500000, 2.700000, 2.900000, 3.100000, 3.300000, 3.500000])
sy=np.array([0.0001,0.0001,0.0001,0.0001,0.0001,0.0001,0.0001,0.0001,0.0001,0.0001,0.0001])
#pongo ese sy pq sin él mi programa da error, pues lo tengo diseñado para calcular incertidumbres también, simplemente las ignoro al final
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

def ajustecuadratico2(x,y,sy):
    nx=len(x); ny=len(y)
    def fun(t,A,B,C):
        yy=A*t**2+B*t+C
        return yy
    uy=sy
    par=[1,1,0]
    sol=so.curve_fit(fun,x,y,p0=(par),sigma=uy,absolute_sigma=True)
    A2,B2,C2=sol[0]; sA,sB,sC=np.sqrt(np.diag(sol[1]))
    yEst=fun(x,A,B,C)
    print('para una función de la forma: Ax^2 + Bx + C')
    print('A2= ',A2,'+/-',sA);print('B2= ',B2,'+/-',sB); print('C2= ',C2,'+/-',sC)
    return[A2,B2,C2,yEst]

def ajustecuadratico3(x,y,sy):
    nx=len(x); ny=len(y)
    def fun(t,A,B,C):
        yy=A*t**2+B*t+C
        return yy
    uy=sy
    par=[1,1,0]
    sol=so.curve_fit(fun,x,y,p0=(par),sigma=uy,absolute_sigma=True)
    A3,B3,C3=sol[0]; sA,sB,sC=np.sqrt(np.diag(sol[1]))
    yEst=fun(x,A,B,C)
    print('para una función de la forma: Ax^2 + Bx + C')
    print('A3= ',A3,'+/-',sA);print('B3= ',B3,'+/-',sB); print('C3= ',C3,'+/-',sC)
    return[A3,B3,C3,yEst]

def ajustecuadratico4(x,y,sy):
    nx=len(x); ny=len(y)
    def fun(t,A,B,C):
        yy=A*t**2+B*t+C
        return yy
    uy=sy
    par=[1,1,0]
    sol=so.curve_fit(fun,x,y,p0=(par),sigma=uy,absolute_sigma=True)
    A4,B4,C4=sol[0]; sA,sB,sC=np.sqrt(np.diag(sol[1]))
    yEst=fun(x,A,B,C)
    print('para una función de la forma: Ax^2 + Bx + C')
    print('A4= ',A4,'+/-',sA);print('B4= ',B4,'+/-',sB); print('C4= ',C4,'+/-',sC)
    return[A4,B4,C4,yEst]
plt.xlabel("T")
plt.ylabel("$c_N$")
[A,B,C,yEst]=ajustecuadratico(T,c16,sy)
[A2,B2,C2,yEst]=ajustecuadratico2(T,c32,sy)
[A3,B3,C3,yEst]=ajustecuadratico3(T,c64,sy)
[A4,B4,C4,yEst]=ajustecuadratico4(T,c128,sy)
y=A*T**2+B*T+C
y2=A2*T**2+B2*T+C2
y3=A3*T**2+B3*T+C3
y4=A4*T**2+B4*T+C4
plt.plot(T,y,"aquamarine", label="N=16")
plt.plot(T,y2,"violet", label="N=32")
plt.plot(T,y3,"sandybrown", label="N=64")
plt.plot(T,y4,"cornflowerblue", label="N=128")
plt.legend()
