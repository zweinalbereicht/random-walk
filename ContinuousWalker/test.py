# Just another python script
import ContinuousWalker as md
import numpy as np
import matplotlib.pyplot as plt

walker=md.RTPpotentialWalker("linear",0.02, "gamma", 2, 1.0)
# walker.print_details()



Ls=np.linspace(0,100,30)
nbsimus=10000
splits=[]
for l in Ls:
    splits.append(md.splitting_probability(0,l,walker,nbsimus))


plt.scatter(Ls,splits)
plt.yscale('log')
plt.show()
