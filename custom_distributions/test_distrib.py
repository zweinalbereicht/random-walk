### Just another python script

import numpy as np
import matplotlib.pyplot as plt

data=np.loadtxt('results.txt')

a,b=np.histogram(data,bins=max(data),density=True)

print(a)

