from tqdm import tqdm
import os
import build.module_DiscreteWalker
from build.module_DiscreteWalker import *
import time
import numpy as np

#print(round(time.time()))

#n=int(input("nb of simulations : "))
#x0=int(input("starting position : "))
#
#a=time.time()
#results=np.zeros(n)
#seed=round(time.time())
#
#for k in tqdm(range(n)):
#    seed+=1
#    #print(seed)
#    myWalker=pyDiscreteWalker("mon marcheur", x0,seed)
#    myWalker.move_til_death()
#    results[k]=myWalker.get_max()
#
#print("elapsed time : {0} seconds".format(time.time()-a))


n=int(input("nb of simulations : "))
x0=int(input("starting position : "))
xmax=int(input("max pos : "))

results=[]
seed=round(time.time())

for k in tqdm(range(n)):
    seed+=1
    myWalker=pyDiscreteWalker("mon marcheur", x0,seed)
    m=myWalker.move_fixed_max(xmax)
    if(m==0):
        results.append(myWalker.get_lifetime())

print(len(results))
print(results)


tmax=int(input("max time : "))

results=[]
seed=round(time.time())

for k in tqdm(range(n)):
    seed+=1
    myWalker=pyDiscreteWalker("mon marcheur", x0,seed)
    m=myWalker.move_fixed_time(tmax)
    if(m==0):
        results.append(myWalker.get_max())

print(len(results))
print(results)






