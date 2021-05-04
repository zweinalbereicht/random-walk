### Just another python script

from tqdm import tqdm
import numpy as np
import os
import matplotlib.pyplot as plt

from build.module_SATWWalker import *
from concurrent.futures import ThreadPoolExecutor


n=10000000
s0=1
s=100

def simu(seed):
    walker=SATWWalker("mywalker",s0,1/3,seed)
    if(walker.move_fixed_max(s)==0):
        return walker.get_lifetime()
    else:
        return 0

seeds=np.random.randint(0,10*n,n)

with ThreadPoolExecutor(4) as ex:
    results=ex.map(simu,seeds)



#for k in tqdm(range(n)):
#    walker=SATWWalker("mywalker",s0,1/3,seeds[k])
#    if(walker.move_fixed_max(s)==0):
#        result.append(walker.get_lifetime())
#
results=np.array(list(results))
results=results[results>0]
print("max proba : {0}".format(len(results)/n))
print("nb of successes : {0}".format(len(results)))
