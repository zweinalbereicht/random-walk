from tqdm import tqdm
import os
import time
a=time.time()
import numpy as np

def simu(x0):
    pos=x0
    max_val=pos
    while(pos>0):
        pos+=np.random.choice([-1,1])
        if pos>max_val:
            max_val=pos
    return max_val

print("elapsed time : {0} seconds".format(time.time()-a))



n=int(input("nb of simulations : "))
x0=int(input("starting position : "))

a=time.time()

results=np.zeros(n)
seed=round(time.time())

for k in tqdm(range(n)):
    results[k]=simu(x0)

print("elapsed time : {0} seconds".format(time.time()-a))
