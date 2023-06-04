import numpy as np
import scipy.optimize as so
import matplotlib.pyplot as plt
import math
#N=16
# Datos
Tc=2.269
#trabajaremos con la magnetización en valor absoluta porque los q nos interesa es cuanto dista de 0, no con que sentido.
T = [1.500000, 1.700000, 1.900000, 2.100000, 2.300000, 2.500000, 2.700000, 2.900000, 3.100000, 3.300000, 3.500000]
mN = [0.986507, 0.485121, 0.312836, 0.217274, 0.000401, 0.000018, -0.000087, -0.000073, 0.000026, 0.000037, 0.000016]

beta=np.zeros(len(T))
x=np.zeros(len(T))
for i in range (len(T)):
    x[i]=(T[i]-Tc)/Tc
    if x[i]>0 and mN[i]>0:
        beta[i]=-math.log(mN[i]+(T[i]-Tc)/Tc)
    if x[i]<0 and mN[i]>0:
        beta[i]=-math.log(mN[i]-(T[i]-Tc)/Tc)
    if x[i]<0 and mN[i]<0:
        beta[i]=-math.log(-mN[i]-(T[i]-Tc)/Tc)
    if x[i]>0 and mN[i]<0:
        beta[i]=-math.log(-mN[i]+(T[i]-Tc)/Tc)  
        
media=sum(beta)/len(beta)
