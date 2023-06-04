# -*- coding: utf-8 -*-
"""
Created on Sat Jun  3 18:15:21 2023

@author: carlo
"""

import numpy as np
from scipy.optimize import curve_fit

# Datos
t = np.array([1.500000, 1.700000, 1.900000, 2.100000, 2.300000, 2.500000, 2.700000, 2.900000, 3.100000, 3.300000, 3.500000])
correl = np.array([0.973199, 0.470621, 0.293657, 0.189937, 0.075088, 0.025061, 0.010669, 0.005071, 0.002617, 0.001459, 0.000845]
)

def leyescala(t, a, b):
    return a * np.power(t, -b)

#ajuste
params, _ = curve_fit(leyescala, t, correl)

a1 = params[0]
b1 = params[1]

#longitud de correlación
x = 1 / a1

#exponente crítico
exp = b1


print("Longitud de correlación:", x)
print("Exponente crítico característico:", exp)
