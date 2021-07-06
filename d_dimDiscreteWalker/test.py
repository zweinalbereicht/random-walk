import numpy as np
import sys
import build.module_d_dimDiscreteWalker as md

walker=md.DiscreteWalker("lala",3,[1,0,0],np.random.randint(100000))
#walker.print_details()

a=int(sys.argv[1])
nb_sites = md.fpt_arrival_bounded_global_mean([10,10,10],walker,a)

#print("nb od sites visited : \n")
print(nb_sites)
