### Just another python script

import numpy as np
import matplotlib.pyplot as plt
import scipy.special as sc

data=np.loadtxt('results.txt')

hist=np.histogram(data,bins=np.arange(1,10000),density=True)

plt.loglog(hist[1][:-1],hist[0])
x=np.linspace(0.1,1e4,100)
plt.loglog(x,x**(-1.3)/sc.zeta(1.3))
plt.show()

print(a)

